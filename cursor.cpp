#include <stdint.h>
#include <32blit.hpp>

#include "cursor.hpp"
#include "commonvars.hpp"
#include "helperfuncs.hpp"

using namespace blit;

constexpr uint8_t maxCursors = 4;
constexpr uint8_t maxCursorFrameCount = 3;
constexpr uint8_t cursorAnimCount = 2; //blink on & off
constexpr uint8_t cursorNumTiles = maxCursors * 8; //for the max 4 cursors shown at once (on help screens) 
constexpr uint32_t cursorBlinktime = 75;

uint32_t prevBlinkUpdate = 0;
uint8_t cursorFrameCount, cursorFrame, showCursor;
uint8_t spritePos[cursorNumTiles][2];
uint8_t disableBlinking = 0;

void move_sprite(uint8_t sprite, uint8_t x, uint8_t y)
{
    spritePos[sprite][0] = x;
    spritePos[sprite][1] = y;
}

void drawCursors()
{
    if((showCursor == 0) || (cursorFrame & 1)) // 2nd or to add blink effect, it will skip drawing if bit 1 is set
         return;
    
    uint8_t height = screenHeight;
    for (uint8_t i=0; i != cursorNumTiles; i++)
        if (spritePos[i][1] < height)
        {
            screen.stretch_blit(selectorTiles, Rect(0,i%8*tileSize,tileSize, tileSize),
                Rect(xoffset + (int32_t)((float)spritePos[i][0]*scale),yoffset + (int32_t)((float)spritePos[i][1]*scale), 
                (int32_t)(tileSize*scale),(int32_t)(tileSize*scale)));
        }
}

//returns 1 if cursor has changed / needs redraw
uint8_t updateCursorFrame()
{
    if (disableBlinking || (showCursor == 0))
        return 0;

    if (now()-prevBlinkUpdate < cursorBlinktime)
        return 0;
    
    prevBlinkUpdate = now();
    ++cursorFrameCount;
    if (cursorFrameCount == maxCursorFrameCount)
    {        
        cursorFrameCount = 0;
        ++cursorFrame;
        if (cursorFrame == cursorAnimCount)
            cursorFrame = 0;
        return 1; 
    }
    return 0;
}

void hideCursors()
{
    //HIDE CURSOR SPRITES
    for (uint8_t i = 0; i < maxCursors; i++)
        setCursorPos(i, 0, (screenHeight / 8) + 1);
    
    showCursor = 0;
}

void showCursors()
{
    showCursor = 1;
}

void setCursorPos(uint8_t cursorNr, uint8_t xPos, uint8_t yPos)
{
    if (cursorNr >= maxCursors)
        return;

    move_sprite((cursorNr<<3) + 0, ((xPos) << 3),  ((yPos - 1) << 3));
    move_sprite((cursorNr<<3) + 1,  ((xPos + 1) << 3),  ((yPos) << 3));
    move_sprite((cursorNr<<3) + 2,  ((xPos) << 3),  ((yPos + 1) << 3));
    move_sprite((cursorNr<<3) + 3,  ((xPos - 1) << 3),  ((yPos) << 3)); 
    //corners
    move_sprite((cursorNr<<3) + 4, ((xPos + 1) << 3),  ((yPos - 1) << 3));
    move_sprite((cursorNr<<3) + 5, ((xPos + 1) << 3),  ((yPos + 1) << 3));
    move_sprite((cursorNr<<3) + 6, ((xPos - 1) << 3),  ((yPos - 1) << 3));
    move_sprite((cursorNr<<3) + 7, ((xPos - 1) << 3),  ((yPos + 1) << 3)); 
}

void initCursors()
{
    hideCursors();

    cursorFrameCount = 0;
    cursorFrame = 0;
}
