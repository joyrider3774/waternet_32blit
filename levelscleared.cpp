#include <stdint.h>

#include <32blit.hpp>

#include "helperfuncs.hpp"
#include "commonvars.hpp"
#include "printfuncs.hpp"
#include "sound.hpp"
#include "level.hpp"
#include "palettes.hpp"

using namespace blit;

void initLevelsCleared()
{
    setPaletteTitle();
    set_bkg_data(congratsScreenTiles);
    SelectMusic(musAllLevelsClear);
}

void levelsCleared_render()
{
    screen.pen = getColor(0);
    screen.stretch_blit(congratsMap, Rect(0,0, congratsMap->bounds.w, congratsMap->bounds.h), 
        Rect(xoffset,yoffset,(int32_t)((float)congratsMap->bounds.w*scale),(int32_t)((float) congratsMap->bounds.h*scale)));
    switch (difficulty)
    {
        case diffVeryEasy:
            printCongratsScreen(2, 6, "VERY EASY LEVELS");
            break;
        
        case diffEasy:
            printCongratsScreen(4, 6, "EASY LEVELS");
            break;
    
        case diffNormal:
            printCongratsScreen(3, 6, "NORMAL LEVELS");
            break;

        case diffHard:
            printCongratsScreen(4, 6, "HARD LEVELS");
            break;
    
        case diffVeryHard:
            printCongratsScreen(2, 6, "VERY HARD LEVELS");
            break;
    }
}

void levelsCleared_update() 
{  
    if(gameState == gsInitLevelsCleared)
    {
        initLevelsCleared();
        gameState -= gsInitDiff;
    }

    if ((buttons.pressed & Button::A) || 
        (buttons.pressed & Button::B))  
    {
        playMenuAcknowlege();
        titleStep = tsMainMenu;
        gameState = gsInitTitle;
    }
}