#include <stdint.h>
#include <32blit.hpp>
#include "helperfuncs.hpp"
#include "commonvars.hpp"
#include "printfuncs.hpp"
#include "palettes.hpp"

using namespace blit;

uint32_t startTime, prevTime = 0;
float titlePosY;
constexpr uint16_t frameDelay = 750;


void initIntro()
{
    setPaletteTitle();
    setBlockTilesAsBackground();
    titlePosY = screenHeight;
    startTime = now();
}

void intro_render()
{
    screen.pen = getColor(0);
    screen.clear();

    if (now() - startTime < frameDelay)
    {
        //20-12
        printMessage(8 >> 1, 7, "WILLEMS DAVY");
    }
    else
    {
        if (now() - startTime < frameDelay *2)
        {
            //20-8
            printMessage(12 >> 1, 7, "PRESENTS");
            prevTime = now();
        }
        else
        {
            screen.stretch_blit(titlescreen, 
                Rect(0,0,titlescreen->bounds.w, titlescreen->bounds.h), 
                Rect(xoffset,(int32_t)((float)yoffset + titlePosY*scale),
                (int32_t)((float)titlescreen->bounds.w*scale), 
                (int32_t)((float)titlescreen->bounds.h*scale)));
            if(titlePosY > 0)
            {
                titlePosY -=  1.0f/60.0f*3.33f * (now()-prevTime);
                prevTime = now();
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
