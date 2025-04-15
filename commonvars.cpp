#include <32blit.hpp>
#include <stdint.h>
#include "assets.hpp"
#include "commonvars.hpp"

using namespace blit;

uint8_t startPos, menuPos, 
        maxLevel, selectedLevel, boardX, boardY, difficulty, 
        gameState, boardWidth, boardHeight, boardSize,
        levelDone, titleStep, gameMode, posAdd, debugMode, 
        mainMenu, option, needRedraw;
 
int16_t selectionX, selectionY;
uint16_t moves;
unsigned char level[maxBoardSize];
uint32_t randomSeedGame;

Surface *blockTiles;
Surface *titlescreen;
Surface *congratsMap;
Surface *selectorTiles;
Surface *congratsScreenTiles;
Surface *fullTitlescreenMap;