#ifndef GAMEOFLIFE_GOL_H
#define GAMEOFLIFE_GOL_H

#include <stdlib.h>
#include <stdint.h>

typedef int bool;
typedef char bit;
#define true 1
#define false 0


typedef struct {
    bool invert_buf;
    bit* cells; //TODO:Optimize even further with a 'bit array' Abstract Data Type
    bit* _cells;
    uint16_t w;
    uint16_t h;
} world_state;

void initialize_cells(uint16_t w, uint16_t h, bit** cells);

void cleanup_world(world_state* world);

void initialize_world(world_state* world);

void set_cell_value(int16_t i, int16_t j, bit desired_value, world_state* world);

bit get_cell_value(int16_t i, int16_t j, world_state* world);

void _set_cell_value(int16_t i, int16_t j, bit desired_value, uint16_t w, bit** cells);

bit _get_cell_value(int16_t i, int16_t j, uint16_t w, bit** cells);

void update_world(world_state* world);


#endif //GAMEOFLIFE_GOL_H
