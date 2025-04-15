#ifndef palettedefines_h
#define palettedefines_h

#include <32blit.hpp>

using namespace blit;

constexpr uint8_t  maxColorSelections = 5;

extern const Pen GB_PALETTE[];
extern const Pen BLACK_WHITE_PALETTE_TITLE[];
extern const Pen GBC_PALETTE_TITLE[];
extern const Pen RED_PALETTE_TITLE[];
extern const Pen WHITE_BLUE_PALETTE_TITLE[];
extern const Pen TROPICAL_PALETTE_TITLE[];

extern const Pen BLACK_WHITE_PALETTE_GAME[];
extern const Pen GBC_PALETTE_GAME[];
extern const Pen RED_PALETTE_GAME[];
extern const Pen WHITE_BLUE_PALETTE_GAME[];
extern const Pen TROPICAL_PALETTE_GAME[];

#endif