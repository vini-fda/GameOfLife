#include "GOL.h"
#include <time.h>

void initialize_cells(uint16_t w, uint16_t h, bit** cells) {
    //Seed for the random distribution
    srand(time(NULL));
    //n: how many cells(including dead cells at border for padding)
    size_t n = ((uint32_t)w + 2) * ((uint32_t)h + 2);
    *cells = (bit*) malloc(sizeof(bit) * n); // added padding
    for(int16_t i=0; i < n; i++) {
        (*cells)[i] = 0;
    }
    for(int16_t i=0; i < w; i++) {
        for (int16_t j = 0; j < h; j++) {
            _set_cell_value(i, j, (bit)(rand() % 2), w, cells);
        }
    }
}

void cleanup_world(world_state* world) {
    free(world->cells);
    world->cells = NULL;
    free(world->_cells);
    world->_cells = NULL;
}

void set_cell_value(int16_t i, int16_t j, bit desired_value, world_state* world) {
    //Padding
    i++;j++;
    if(!world->invert_buf)
        world->cells[i + world->w*j] = desired_value;
    else
        world->_cells[i + world->w*j] = desired_value;

}

bit get_cell_value(int16_t i, int16_t j, world_state *world) {
    //Padding
    i++;j++;
    if(!world->invert_buf)
        return world->cells[i + world->w*j];
    else
        return world->_cells[i + world->w*j];
}

void initialize_world(world_state* world) {
    world->invert_buf = false;
    initialize_cells(world->w, world->h, &world->cells);
    initialize_cells(world->w, world->h, &world->_cells);
}

void update_world(world_state *world) {
    //TODO: Comment code
    bit** fixed_cells = &world->cells;
    bit** new_cells = &world->_cells;
    uint8_t temp = 0;
    if(world->invert_buf) {
        fixed_cells = &world->_cells;
        new_cells = &world->cells;
    }
    uint16_t w = world->w;
    for(int16_t i=0; i < w; i++) {
        for(int16_t j=0; j < world->h; j++) {
            //TODO:Improve this algorithm
            temp =  _get_cell_value(i-1, j-1, w, fixed_cells) +
                    _get_cell_value(i, j-1, w, fixed_cells) +
                    _get_cell_value(i+1, j-1, w, fixed_cells) +
                    _get_cell_value(i-1, j, w, fixed_cells) +
                    _get_cell_value(i, j, w, fixed_cells) * 7 +
                    _get_cell_value(i+1, j, w, fixed_cells) +
                    _get_cell_value(i-1, j+1, w, fixed_cells) +
                    _get_cell_value(i, j+1, w, fixed_cells) +
                    _get_cell_value(i+1, j+1, w, fixed_cells);
            //TODO:Fix Valgrind Memcheck warning here
            //Conditional jump or move depends on unitialised value(s) (temp <- fixed_cells)
            temp = (temp == 3) || (temp == 9) || (temp == 10); //TODO:Optimize this?
            _set_cell_value(i, j, temp, w, new_cells);
        }
    }

    world->invert_buf = !world->invert_buf;
}

void _set_cell_value(int16_t i, int16_t j, bit desired_value, uint16_t w, bit **cells) {
    //Padding
    i++;j++;
    (*cells)[i + w*j] = desired_value;
}

bit _get_cell_value(int16_t i, int16_t j, uint16_t w, bit **cells) {
    //Padding
    i++;j++;
    return (*cells)[i + w*j];
}



