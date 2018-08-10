#include "./game.h"

blk_t get_piece_pos(piece_t *piece) {
    blk_t block = get_piece_layout(piece->type, piece->direction);
    
    block.blk_0 = (piece->y + block.blk_0/4)*10 + piece->x + block.blk_0%4;
    block.blk_1 = (piece->y + block.blk_1/4)*10 + piece->x + block.blk_1%4;
    block.blk_2 = (piece->y + block.blk_2/4)*10 + piece->x + block.blk_2%4;
    block.blk_3 = (piece->y + block.blk_3/4)*10 + piece->x + block.blk_3%4;

    return block;
}

piece_t random_piece() {
    int type = 1 + rand() % 7;
    // int type = 5;
    int dir = rand() % 4;
    // int dir = 1;
    piece_t piece = {
        .x = rand() % 7,
        .y = 24,
        .direction = dir,
        .color = -type,
        .type = type
    };
    return piece;
}

blk_t get_piece_layout(int type, int dir) {
    switch (type) {
        case 1:
            return create_O(dir);
        case 2:
            return create_L(dir);
        case 3:
            return create_J(dir);
        case 4:
            return create_I(dir);
        case 5:
            return create_T(dir);
        case 6:
            return create_Z(dir);
        case 7:
            return create_S(dir);
    }
}


// each piece enclosed in a 4x4 box with 4 values determining location of 4 blocks

blk_t create_piece(int blk_0, int blk_1, int blk_2, int blk_3) {
    blk_t blk = {
        .blk_0 = blk_0,
        .blk_1 = blk_1,
        .blk_2 = blk_2,
        .blk_3 = blk_3};
    return blk;
}

blk_t create_O(int direction) {
    return create_piece(8, 9, 12, 13);
}

blk_t create_L(int direction) {
    switch (direction) {
        case 0:
            return create_piece(5, 6, 9, 13);
        case 1:
            return create_piece(4, 8, 9, 10);
        case 2:
            return create_piece(5, 9, 12, 13);
        case 3:
            return create_piece(8, 9, 10, 14);
    }
}

blk_t create_J(int direction) {
    switch (direction) {
        case 0:
            return create_piece(4, 5, 9, 13);
        case 1:
            return create_piece(8, 9, 10, 12);
        case 2:
            return create_piece(5, 9, 13, 14);
        case 3:
            return create_piece(6, 8, 9, 10);
    }
}

blk_t create_I(int direction) {
    switch (direction) {
        case 0:
            return create_piece(1, 5, 9, 13);
        case 1:
            return create_piece(8, 9, 10, 11);
        case 2:
            return create_piece(2, 6, 10, 14);
        case 3:
            return create_piece(4, 5, 6, 7);
    }
}

blk_t create_T(int direction) {
    switch (direction) {
        // start with T
        case 0:
            return create_piece(5, 8, 9, 10);
        case 1:
            return create_piece(5, 8, 9, 13);
        case 2:
            return create_piece(8, 9, 10, 13);
        case 3:
            return create_piece(5, 9, 10, 13);
    }
}

blk_t create_Z(int direction) {
    switch (direction) {
        case 0:
            return create_piece(5, 6, 8, 9);
        case 1:
            return create_piece(4, 8, 9, 13);
        case 2:
            return create_piece(9, 10, 12, 13);
        case 3:
            return create_piece(5, 9, 10, 14);
    }
}

blk_t create_S(int direction) {
    switch (direction) {
        case 0:
            return create_piece(4, 5, 9, 10);
        case 1:
            return create_piece(5, 8, 9, 12);
        case 2:
            return create_piece(8, 9, 13, 14);
        case 3:
            return create_piece(6, 9, 10, 13);
    }
}