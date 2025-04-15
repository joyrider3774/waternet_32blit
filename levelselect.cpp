#include <stdint.h>

#include <32blit.hpp>

#include "helperfuncs.hpp"
#include "commonvars.hpp"
#include "printfuncs.hpp"
#include "savestate.hpp"
#include "sound.hpp"
#include "level.hpp"
#include "palettes.hpp"

using namespace blit;

void drawLevelSelect() 
{
    screen.pen = getColor(0);
    screen.rectangle(Rect(maxBoardBgWidth * 8, 0, screenWidth - (maxBoardBgWidth * 8), screenHeight));
    //LEVEL:
    printMessage(maxBoardBgWidth  , 0 , "LEVEL:");
    
    //[LEVEL NR] 2 chars
    printNumber(maxBoardBgWidth + 4 , 1 , selectedLevel, 2);
    
    //B:BACK
    printMessage(maxBoardBgWidth  , 6 , "b:");
    printMessage(maxBoardBgWidth  , 7 , "BACK");
    
    //A:PLAY
    printMessage(maxBoardBgWidth  , 4 , "a:");
    printMessage(maxBoardBgWidth  , 5 , "PLAY");
    
    //Locked & Unlocked keywoard
    uint8_t tmpUnlocked = levelUnlocked(gameMode, difficulty, selectedLevel -1);
    if(!tmpUnlocked)
        printMessage(maxBoardBgWidth , 2 , "LOCKED");
    else
        printMessage(maxBoardBgWidth , 2 , "OPEN");
    
    drawLevel();

}


void initLevelSelect()
{
    setBlockTilesAsBackground();
    SelectMusic(musTitle);
    setPaletteGame();
    needRedraw = 1;
}

void levelSelect_render()
{
    if(needRedraw)
    {
        drawLevelSelect();
        needRedraw = 0;
    }
}

void levelSelect_update()
{
    if(gameState == gsInitLevelSelect)
    {
        initLevelSelect();
        gameState -= gsInitDiff;
    }
        
    uint8_t tmpUnlocked = levelUnlocked(gameMode, difficulty, selectedLevel -1);


    if (buttons.pressed & Button::B)
    {
        playMenuBackSound();
        gameState = gsInitTitle;
    }
    if (buttons.pressed & Button::A)
    {
        if(tmpUnlocked)
        {
            gameState = gsInitGame;
            playMenuAcknowlege();
        }
        else
        {
            playErrorSound();
        }
    }
    if (buttons.pressed & Button::DPAD_LEFT)
    {
        if (difficulty == diffRandom)
        {
            playMenuSelectSound();
            randomSeedGame = getRandomSeed();
            initLevel(randomSeedGame);
            needRedraw = 1;
        }
        else
        {
            if (selectedLevel > 1)
            {
                playMenuSelectSound();
                selectedLevel--;
                initLevel(randomSeedGame);
                needRedraw = 1;
            }
        } 
    }
    if (buttons.pressed & Button::DPAD_RIGHT)
    {
        if (difficulty == diffRandom)
        {
            playMenuSelectSound();
            //need new seed based on time
            randomSeedGame = getRandomSeed();
            initLevel(randomSeedGame);
            needRedraw = 1;
        }
        else
        {
            if (selectedLevel < maxLevel)
            {
                playMenuSelectSound();
                selectedLevel++;
                initLevel(randomSeedGame);
                needRedraw = 1;
            }
        }
    }
}
