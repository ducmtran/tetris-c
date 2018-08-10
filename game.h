#ifndef GAME_H_
#define GAME_H_

// define direction
#define UP 0
#define RIGHT 1
#define DOWN 2
#define LEFT 3

// define game state
#define RUNNING 1
#define STOP 0

// screen size
#define W 10
#define H 24

// piece color
#define EMPTY 0
#define YELLOW 1
#define ORANGE 2
#define BLUE 3
#define TEAL 4
#define PURPLE 5
#define RED 6
#define GREEN 7

// piece type
#define O 1
#define L 2
#define J 3
#define I 4
#define T 5
#define Z 6
#define S 7

// negative color value for ongoing piece
typedef struct {
    int x;
    int y;
    int direction;
    int color;
    int type;
} piece_t;

typedef struct {
    int blk_0;
    int blk_1;
    int blk_2;
    int blk_3;
} blk_t;

typedef struct {
    int *screen;
    int state;
    int score;
    int speed;
    float delta;    
} game_t;

void move_left(game_t *game, piece_t *piece);
void move_right(game_t *game, piece_t *piece);
void rotate(game_t *game, piece_t *piece);
void drop(game_t *game, piece_t *piece);
void hard_drop(game_t *game, piece_t *piece);

piece_t random_piece();
blk_t get_piece_layout(int type, int dir);
blk_t get_piece_pos(piece_t *piece);
blk_t get_block(int type, int dir);

blk_t create_O(int direction);

blk_t create_L(int direction);

blk_t create_J(int direction);

blk_t create_I(int direction);

blk_t create_T(int direction);

blk_t create_Z(int direction);

blk_t create_S(int direction);

#endif
