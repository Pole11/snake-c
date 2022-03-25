#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "pole.h"

ptr_node_t append(ptr_node_t head, int x, int y) {
    ptr_node_t new = NULL,
               temp = head;

    new = (ptr_node_t) malloc(sizeof(node_t));
    new -> x = x;
    new -> y = y;
    new -> next = NULL;

    if (head == NULL)   
        return new;
    
    for (; temp -> next != NULL; temp = temp -> next)
        ;
    
    temp -> next = new;
    return head;
}

void shift(ptr_node_t head) {
    int x = head -> x,
        y = head -> y;

    if (head -> next == NULL)
        return;

    shift(head -> next);

    head -> next -> x = x;
    head -> next -> y = y;

    return;
}

char get_input(void) {
    char input = 0;
    system("/bin/stty raw");
    input = getc(stdin);
    input = 'A' <= input && input <= 'Z' ? input - ('a' - 'A') : input; // to lower case
    printf("\r"); // clear the input text
    fflush(stdin); 
    system("/bin/stty cooked");

    return input;
}

void input_handler(char input, ptr_node_t head, int w, int h) {
    if (input == 'q')
        exit(0);
    else if (input == 'w' && head -> y > 1)
        head -> y--;
    else if (input == 's' && head -> y < h - 1)
        head -> y++;
    else if (input == 'a' && head -> x > 2)
        head -> x-=2;
    else if (input == 'd' && head -> x < w - 3)
        head -> x+=2;
    
    if (input == 'e')
        append(head, 0, 0);
    
    shift(head); // shift the list

    return;
}

void food_handler(ptr_node_t head, int w, int h) {
    // check if is eaten
    if (head -> x == food.x && head -> y == food.y) {
        // spawn new food randomly
        srand(time(0));
        int x = (rand() % (w / 2 - 4)) * 2 + 4,
            y = rand() % (h - 4) + 2;

        food.x = x;
        food.y = y;

        append(head, 0, 0);

        // increase the score
        score++;
    }

    return;
}

void print_screen(int w, int h, ptr_node_t head) {  
    int full = 0; // check if is printed from the list
    ptr_node_t temp = head;

    // print first line
    for (int j = 0; j < w; j += 2)
        printf("+ ");
    printf("\n");

    for (int y = 1; y < h; y++) {
        for (int x = 1; x < w; x++) {
            full = 0;
            if (food.x == x && food.y == y) {
                printf("%c", '$');
                full = 1;
            } else {
                for (temp = head; temp != NULL && !full; temp = temp -> next) {
                    if (temp -> x == x && temp -> y == y) 
                        full = 1;
                }
                if (!full) {
                    if (x == 1 || x == w - 1)
                        printf("+");
                    printf(" ");
                } else {
                    if (temp != NULL && temp -> x == head -> x && temp -> y == head -> y) 
                        printf("%c", '@');
                    else
                        printf("%c", '#');
                }
            }
        }
        printf("\n");
    }

    // print last line
    for (int j = 0; j < w; j += 2)
        printf("+ ");
    printf("\n");

    return;
}

void clear_screen(void) {
    printf("\033[H\033[J"); 

    return;
}

void print_list(ptr_node_t head) {
    printf("Lista:\n");
    for (; head != NULL; head = head -> next)
        printf("%14p -> %14p: %d, %d\n", 
            head, 
            head -> next, 
            head -> x, 
            head -> y);
    return;
}
