#include <32blit.hpp>
#include "commonvars.hpp"
#include "palettedefines.hpp"
#include "palettes.hpp"

using namespace blit;

uint8_t palIndex = 0;
uint8_t inverseColors = 0;
Pen pal[4];

#define setPal(Dest, Source, Count) for (int i = 0; i < Count; i++) Dest[i] = Source[i];

Pen getColor(uint8_t index)
{
    if (( index <= 3))
        return pal[index];
    return pal[0];
}

uint8_t getMaxPalettes()
{
    return maxColorSelections;
}

void setPalIndex(uint8_t index)
{
#ifdef DISABLE_READ_ONLY_SURFACES
  palIndex = index;
#else
  palIndex = 4;
#endif
  //only possible to change on title
  setPaletteTitle();
}

void setPalInverse(uint8_t value)
{
#ifdef DISABLE_READ_ONLY_SURFACES
    inverseColors = value;
#else
    inverseColors = 0;
#endif
    //only possible to change on title
    setPaletteTitle();
}

uint8_t getPalInverse()
{
    return inverseColors;
}

uint8_t getPalIndex()
{
  return palIndex;
}


void setPaletteTitle()
{
    switch(palIndex)
    {
        case 0: setPal(pal, GB_PALETTE, 4); break;
        case 1: setPal(pal, BLACK_WHITE_PALETTE_TITLE, 4); break;
        case 2: setPal(pal, GBC_PALETTE_TITLE, 4); break;
        case 3: setPal(pal, RED_PALETTE_TITLE, 4); break;
        case 4: setPal(pal, WHITE_BLUE_PALETTE_TITLE, 4); break;
        case 5: setPal(pal, TROPICAL_PALETTE_TITLE, 4); break;   
    }
    
    if(inverseColors)
    {
        Pen tmp0 = pal[0];
        Pen tmp1 = pal[1];
        Pen tmp2 = pal[2];
        Pen tmp3 = pal[3];

        pal[3] = tmp2;
        pal[2] = tmp3;
        pal[1] = tmp0;
        pal[0] = tmp1;
    }

#ifdef DISABLE_READ_ONLY_SURFACES
    for (int i=0; i < 4; i ++)
    {
        titlescreen->palette[i] = pal[i];
        blockTiles->palette[i] = pal[i];
        congratsMap->palette[i] = pal[i];
        congratsScreenTiles->palette[i] = pal[i];
        fullTitlescreenMap->palette[i] = pal[i];
    }
    selectorTiles->palette[1] = pal[1];
#endif
}

void setPaletteGame()
{

    switch(palIndex)
    {
        case 0: setPal(pal, GB_PALETTE, 4); break;
        case 1: setPal(pal, BLACK_WHITE_PALETTE_GAME, 4); break;
        case 2: setPal(pal, GBC_PALETTE_GAME, 4); break;
        case 3: setPal(pal, RED_PALETTE_GAME, 4); break;
        case 4: setPal(pal, WHITE_BLUE_PALETTE_GAME, 4); break;
        case 5: setPal(pal, TROPICAL_PALETTE_GAME, 4); break;
    }
    
    if(inverseColors)
    {
        Pen tmp0 = pal[0];
        Pen tmp1 = pal[1];
        Pen tmp2 = pal[2];
        Pen tmp3 = pal[3];

        pal[3] = tmp2;
        pal[2] = tmp3;
        pal[1] = tmp0;
        pal[0] = tmp1;
    }

#ifdef DISABLE_READ_ONLY_SURFACES
    for (int i=0; i < 4; i ++)
    {
        titlescreen->palette[i] = pal[i];
        blockTiles->palette[i] = pal[i];
        congratsMap->palette[i] = pal[i];
        congratsScreenTiles->palette[i] = pal[i];
        fullTitlescreenMap->palette[i] = pal[i];
    }
    selectorTiles->palette[1] = pal[1];
#endif
}

const char* getPaletteName()
{
  switch(palIndex)
  {
        case 0: return "COLOR  GB";
        case 1: return "COLOR  BW";
        case 2: return "COLOR  GBC";
        case 3: return "COLOR  RED";
        case 4: return "COLOR  BLUE";  
        case 5: return "COLOR  FIRE";
        default: return "";
  }   
}