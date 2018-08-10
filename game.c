#include "./game.h"
#include <SDL2/SDL.h>

// ongoing piece uses negative values of color
// 'dead' blocks use positive values
void update(game_t *game, piece_t *piece, unsigned int elapsed) {
    float step = (float) 1/(game->speed);
    float time = (float) elapsed/1000;

    // update piece state
    game->delta = game->delta + time;
    if (game->delta > step) {
        clear_lines(game);
        game->delta = game->delta - step;
        drop(game, piece);
    }
}

void rotate(game_t *game, piece_t *piece) {
    int dir = piece->direction;
    if (dir == 3) {
        dir = 0;
    } else {
        dir++;
    }
    // simulate moving the temporary piece to rotate
    piece_t p_temp = *piece;
    p_temp.direction = dir;

    clear_prev_block(game, piece);
    if (can_rotate(game, &p_temp, 0)) {
        piece->direction = dir;
    } else if (can_rotate(game, &p_temp, 1)) {
        piece->x++;
        piece->direction = dir;
    } else if (can_rotate(game, &p_temp, -1)) {
        piece->x--;
        piece->direction = dir;
    } else if (can_rotate(game, &p_temp, 2)) {
        // +- 2 is only for I piece
        piece->x += 2;
        piece->direction = dir;
    } else if (can_rotate(game, &p_temp, -2)) {
        piece->x -= 2;
        piece->direction = dir;
    }
    update_array(game, piece);
}

void move_left(game_t *game, piece_t *piece) {
    if (bounded_left(piece, -1)) {
        return;
    }
    if (occupied(game, piece, -1)) {
        return;
    }
    clear_prev_block(game, piece);
    piece->x--;
    update_array(game, piece);
}

void move_right(game_t *game, piece_t *piece) {
    if (bounded_right(piece, 1)) {
        return;
    }
    if (occupied(game, piece, 1)) {
        return;
    }
    clear_prev_block(game, piece);
    piece->x++;
    update_array(game, piece);
}

void drop(game_t *game, piece_t *piece) {
    if (occupied(game, piece, -10) || screen_end(piece)) {
        // TODO: do nothing with current piece in array
        // get new random piece
        piece->color = -piece->color;
        update_array(game, piece);
        *piece = random_piece();
        return;
    } 
    clear_prev_block(game, piece);
    piece->y -= 1;
    update_array(game, piece);
}

void hard_drop(game_t *game, piece_t *piece) {
    piece_t temp = *piece;
    while (!(occupied(game, &temp, -10) || screen_end(&temp))) {
        temp.y--;
    }
    clear_prev_block(game, piece);
    piece->y = temp.y;
    piece->color = -piece->color;
    update_array(game, piece);
    *piece = random_piece();
    return;
}

void clear_lines(game_t *game) {
    int row = 0;
    while (row < 23) {
        for (int i=0; i<10; i++) {
            if (game->screen[row*10 + i] <= 0 ) {
                row++;
                break;
            } else if (i == 9) {
                clear_row(game, row);
                break;
            }
        }
    }
}

void clear_row(game_t *game, int row) {
    for (int i=row*10; i<240; i++) {
        int blk = game->screen[i+10];
        if (blk < 0) {
            blk = 0;
        }
        game->screen[i] = blk;
    }
}

int can_rotate(game_t *game, piece_t *piece, int offset) {
    if (!occupied(game, piece, offset) &&
        !(bounded_left(piece, offset) || bounded_right(piece, offset)) &&
        !screen_end(piece))
    {
        return 1;
    }
    return 0;
}

// offset to check left/right/below, right: +1, left: -1, below: -10
int occupied(game_t *game, piece_t *piece, int offset) {
    blk_t blk = get_piece_pos(piece);

    if (game->screen[blk.blk_0 + offset] > 0 ||
        game->screen[blk.blk_1 + offset] > 0 ||
        game->screen[blk.blk_2 + offset] > 0 ||
        game->screen[blk.blk_3 + offset] > 0)
    {
        return 1;
    }
    return 0;
}

int bounded_left(piece_t *piece, int offset) {
    blk_t blk = get_piece_layout(piece->type, piece->direction);

    if (piece->x + blk.blk_0 % 4 + offset < 0 ||
        piece->x + blk.blk_1 % 4 + offset < 0 ||
        piece->x + blk.blk_2 % 4 + offset < 0 ||
        piece->x + blk.blk_3 % 4 + offset < 0)
    {
        return 1;
    }
    return 0;
}

int bounded_right(piece_t *piece, int offset) {
    blk_t blk = get_piece_layout(piece->type, piece->direction);

    if (piece->x + blk.blk_0 % 4 + offset > 9 ||
        piece->x + blk.blk_1 % 4 + offset > 9 ||
        piece->x + blk.blk_2 % 4 + offset > 9 ||
        piece->x + blk.blk_3 % 4 + offset > 9)
    {
        return 1;
    }
    return 0;
}

int screen_end(piece_t *piece) {
    blk_t blk = get_piece_pos(piece);
    if (blk.blk_0 - 10 < 0 ||
        blk.blk_1 - 10 < 0 ||
        blk.blk_2 - 10 < 0 ||
        blk.blk_3 - 10 < 0) 
    {
        return 1;
    }
    return 0;
}

void clear_prev_block(game_t *game, piece_t *piece) {
    blk_t blk;
    blk = get_piece_pos(piece);

    game->screen[blk.blk_0] = 0;
    game->screen[blk.blk_1] = 0;
    game->screen[blk.blk_2] = 0;
    game->screen[blk.blk_3] = 0;
}

void update_array(game_t *game, piece_t *piece) {
    blk_t blk = get_piece_pos(piece);

    game->screen[blk.blk_0] = piece->color;
    game->screen[blk.blk_1] = piece->color;
    game->screen[blk.blk_2] = piece->color;
    game->screen[blk.blk_3] = piece->color;
}