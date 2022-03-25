#ifndef _POLE_H_
#define _POLE_H_

#define REFRESH_DELTA 0.9

typedef struct {
    int x;
    int y;
} food_t;

typedef struct _node_t {
    int x;
    int y;
    struct _node_t * next;
} node_t;

typedef node_t * ptr_node_t;

extern int score;
extern food_t food;

ptr_node_t append(ptr_node_t head, int x, int y);
char get_input(void);
void food_handler(ptr_node_t head, int w, int h);
void input_handler(char input, ptr_node_t head, int w, int h);
void print_screen(int w, int h, ptr_node_t head);
void clear_screen(void);
void print_list(ptr_node_t head);

#endif