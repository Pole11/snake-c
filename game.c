#include <stdio.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include "pole.h"

#define DEBUGGING 0

ptr_node_t head = NULL;

int score = 0;
food_t food;

int main(void) {

    int w = 0,
        h = 0;
    char input = 0;

    food.x = 6;
    food.y = 6;

    head = append(head, 8, 8);
    head = append(head, 8, 8);

#if(DEBUGGING == 1)
    head = append(head, 10, 6);
    head = append(head, 8, 9);
    head = append(head, 5, 6);
#endif

    struct winsize win;
    
    for (;;) {
        // get the size of the screen
        ioctl(1, TIOCGWINSZ, &win);
        w = (win.ws_col % 2 == 0 ? win.ws_col - 1 : win.ws_col - 2) - 2;
        h = (win.ws_row % 2 == 0 ? win.ws_row : win.ws_row - 1) - 10;

        // adjust the frame rate
        sleep(REFRESH_DELTA);

        // clear screen
        clear_screen();

        // print the screen
        printf("Score: %d\n", score);
        printf("w: %d\th: %d\n", w, h);
        printf("Food: %d, %d\n", food.x, food.y);
        print_screen(w, h, head);

        // get the input
        input = get_input();

        // handle the input
        input_handler(input, head, w, h);

        // handle the food
        food_handler(head, w, h);

        // print the debugging stuff
#if(DEBUGGING == 1)
        print_list(head);
        printf("Input: %d %c\n", input, (char) input);
#endif
    }

    return 0;
}

