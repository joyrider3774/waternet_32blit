#ifndef palettes_h
#define palettes_h

#include <string>
#include <stdint.h>
#include <32blit.hpp>

using namespace blit;

Pen getColor(uint8_t index);
const char* getPaletteName();
void setPalIndex(uint8_t index);
void setPaletteGame();
void setPaletteTitle();
void setPalInverse(uint8_t value);
uint8_t getMaxPalettes();
uint8_t getPalIndex();
uint8_t getPalInverse();

#endif