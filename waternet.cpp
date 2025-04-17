
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <32blit.hpp>

#include "palettes.hpp"
#include "commonvars.hpp"
#include "intro.hpp"
#include "levelselect.hpp"
#include "helpscreens.hpp"
#include "sound.hpp"
#include "cursor.hpp"
#include "printfuncs.hpp"
#include "game.hpp"
#include "titlescreen.hpp"
#include "levelscleared.hpp"
#include "savestate.hpp"
#include "level.hpp"
#include "helperfuncs.hpp"

using namespace blit;

uint32_t prevTime = 0;

//intialisation of game & global variables
void init()
{
    set_screen_mode(ScreenMode::hires);
    scale = (float)screen.bounds.w / screenWidth;
    if ((float)screenHeight * scale > screen.bounds.h)
        scale = (float)screen.bounds.h / screenHeight;
    xoffset = (screen.bounds.w - ((float)screenWidth*scale)) / 2;
    yoffset = (screen.bounds.h - ((float)screenHeight*scale)) / 2;
    loadGraphics();
  
    option = 0;
    debugMode = 0;
    difficulty = diffNormal;
    selectedLevel = 1;
    mainMenu = mmStartGame;
    gameState = gsInitIntro;
    titleStep = tsMainMenu;
    gameMode = gmRotate;
    
    //has to be called first because initsound and initmusic read savestate sound to set intial flags
    initSaveState();
    initSound();
    initMusic();
    setMusicOn(isMusicOnSaveState());
    setSoundOn(isSoundOnSaveState());
    setPalInverse(getInverseColorSaveState());
    setPalIndex(getActiveColorSaveState());
 }

void render(uint32_t time) 
{
    musicTimer();
    if ((prevTime != 0) && ((time - prevTime) < (1000 / frameRate)))
        return;

    prevTime = time;

    //gamestate handling
    switch (gameState)
    {
        case gsTitle:
            titleScreen_render();
            break;
        case gsLevelSelect:
            levelSelect_render();
            break;
        case gsGame:
            game_render();
            break;
        case gsLevelsCleared:
            levelsCleared_render();
            break;
        case gsHelpSlide:
            helpSlide_render();
            break;
        case gsHelpSlide2:
            helpSlide2_render();
            break;
        case gsHelpRotateSlide:
            helpRotateSlide_render();
            break;
        case gsHelpRotateSlide2:
            helpRotateSlide2_render();
            break;
        case gsHelpRotate:
            helpRotate_render();
            break;
        case gsHelpRotate2:
            helpRotate2_render();
            break;
        case gsIntro:
            intro_render();
            break;
    }

    printDebugCpuRamLoad();
 }

 void update(uint32_t time) {
    //gamestate handling
    switch (gameState)
    {
        case gsInitTitle:
        case gsTitle:
            titleScreen_update();
            break;
        case gsInitLevelSelect:
        case gsLevelSelect:
            levelSelect_update();
            break;
        case gsInitGame:
        case gsGame:
            game_update();
            break;
        case gsInitLevelsCleared:
        case gsLevelsCleared:
            levelsCleared_update();
            break;
        case gsInitHelpSlide:
        case gsHelpSlide:
            helpSlide_update();
            break;
        case gsInitHelpSlide2:
        case gsHelpSlide2:
            helpSlide2_update();
            break;
        case gsHelpRotateSlide:
        case gsInitHelpRotateSlide:
            helpRotateSlide_update();
            break;
        case gsInitHelpRotateSlide2:
        case gsHelpRotateSlide2:
            helpRotateSlide2_update();
            break;
        case gsInitHelpRotate:
        case gsHelpRotate:
            helpRotate_update();
            break;
        case gsInitHelpRotate2:
        case gsHelpRotate2:
            helpRotate2_update();
            break;
        case gsInitIntro:
        case gsIntro:
            intro_update();
            break;
    }    
}