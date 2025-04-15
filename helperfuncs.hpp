#ifndef helperfuncs_h
#define helperfuncs_h

#include <32blit.hpp>
#include <stdint.h>

using namespace blit;

uint32_t getRandomSeed();
void setBlockTilesAsBackground();
void set_bkg_tile_xy(uint8_t x, uint8_t y, uint8_t tile);
void set_bkg_data(Surface *tiles);
Surface* get_bkg_data();
void set_bkg_tiles(uint8_t x, uint8_t y, Surface *map);
void loadGraphics();
#endif