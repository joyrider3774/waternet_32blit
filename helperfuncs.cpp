#include <32blit.hpp>
#include <stdint.h>

#include "commonvars.hpp"
#include "helperfuncs.hpp"

using namespace blit;

uint32_t getRandomSeed()
{
   return now_us() * now_us();
}

void set_bkg_tile_xy(uint8_t x, uint8_t y, uint8_t tile)
{
  screen.stretch_blit(screen.sprites, Rect((int32_t)((tile % 16) * tileSize), (int32_t)((tile / 16) * tileSize), (int32_t)tileSize, (int32_t)tileSize), 
    Rect((int32_t)(xoffset + ((float)x * tileSize * scale)), yoffset + ((float)y * tileSize * scale), (int32_t)(tileSize * scale), (int32_t)(tileSize * scale)));
}

void set_bkg_data(Surface *tiles)
{
  screen.sprites = tiles;
}

Surface* get_bkg_data()
{
  return screen.sprites;
}

void set_bkg_tiles(uint8_t x, uint8_t y, Surface *map)
{
  screen.stretch_blit(map, Rect(0,0,map->bounds.w, map->bounds.h), 
    Rect((int32_t)((float)x * tileSize * scale) + xoffset,
    (int32_t)(((float)y * tileSize * scale) + yoffset), 
    (int32_t)((float)map->bounds.w *scale), 
    (int32_t)((float)map->bounds.h * scale)));
}

void setBlockTilesAsBackground()
{
  set_bkg_data(blockTiles);
}

void loadGraphics()
{
#ifdef DISABLE_READ_ONLY_SURFACES
  titlescreen = Surface::load(titlescreen_8x8);
  blockTiles = Surface::load(blocktiles_8x8);
  fullTitlescreenMap = Surface::load(titlescreen2_8x8);
  selectorTiles = Surface::load(selectortiles_8x8);
  congratsMap = Surface::load(congratsscreen_8x8);
  congratsScreenTiles = Surface::load(congratstiles_8x8);
#else
  titlescreen = Surface::load_read_only(titlescreen_8x8);
  blockTiles = Surface::load_read_only(blocktiles_8x8);
  fullTitlescreenMap = Surface::load_read_only(titlescreen2_8x8);
  selectorTiles = Surface::load_read_only(selectortiles_8x8);
  congratsMap = Surface::load_read_only(congratsscreen_8x8);
  congratsScreenTiles = Surface::load_read_only(congratstiles_8x8);
#endif
}