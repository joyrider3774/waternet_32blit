#include <stdint.h>
#include <32blit.hpp>
#include "helperfuncs.hpp"
#include "commonvars.hpp"
#include "printfuncs.hpp"
#include "palettes.hpp"

using namespace blit;

uint16_t frames;
float titlePosY;
constexpr uint8_t frameDelay = 16 * frameRate / 15;    


void initIntro()
{
    setPaletteTitle();
    setBlockTilesAsBackground();
    titlePosY = screenHeight;
    frames = 0;   
}

void intro_render()
{
    frames++;

    screen.pen = getColor(0);
    screen.clear();

    if (frames < frameDelay)
    {
        //20-12
        printMessage(8 >> 1, 7, "WILLEMS DAVY");
    }
    else
    {
        if (frames < frameDelay *2)
        {
            //20-8
            printMessage(12 >> 1, 7, "PRESENTS");
        }
        else
        {
            screen.blit(titlescreen, titlescreen->clip, Point(0, titlePosY));
            if(titlePosY > 0)
            {
                titlePosY -= (float)60/(float)frameRate;
            }
            else
            {
                gameState = gsInitTitle;
            }
        }
    }
}

void intro_update() 
{
    if (gameState == gsInitIntro)
    {
        initIntro();
        gameState -= gsInitDiff;
    }
    
    if ((buttons.pressed & Button::A) || 
        (buttons.pressed & Button::B)) 
    {            
        gameState = gsInitTitle;
    }
    if(buttons.pressed & Button::DPAD_UP)
    {
        debugMode = 1;
    }
}
