#ifndef commonvars_h
#define commonvars_h

#include <32blit.hpp>
#include <stdint.h>
#include <assets.hpp>

using namespace blit;

constexpr uint8_t maxBoardWidth = 12U;
constexpr uint8_t maxBoardHeight = 14U;

constexpr uint8_t maxBoardBgWidth = 14U;
constexpr uint8_t maxBoardBgHeight = 16U;

constexpr uint8_t screenWidth = 160;
constexpr uint8_t screenHeight = 128;

constexpr uint8_t maxBoardSize = maxBoardWidth * maxBoardHeight;

constexpr float_t tileSize = 8.0f;

constexpr uint8_t gsGame = 0;
constexpr uint8_t gsTitle = 1;
constexpr uint8_t gsLevelSelect = 2;
constexpr uint8_t gsLevelsCleared = 3;
constexpr uint8_t gsHelpRotate = 4;
constexpr uint8_t gsHelpRotate2 = 5;
constexpr uint8_t gsHelpRotateSlide = 6;
constexpr uint8_t gsHelpRotateSlide2 = 7;
constexpr uint8_t gsHelpSlide = 8;
constexpr uint8_t gsHelpSlide2 = 9;
constexpr uint8_t gsIntro = 10;

constexpr uint8_t gsInitDiff = 50;

constexpr uint8_t gsInitGame = gsInitDiff + gsGame;
constexpr uint8_t gsInitTitle = gsInitDiff + gsTitle;
constexpr uint8_t gsInitLevelSelect = gsInitDiff + gsLevelSelect;
constexpr uint8_t gsInitLevelsCleared = gsInitDiff + gsLevelsCleared;
constexpr uint8_t gsInitHelpRotate = gsInitDiff + gsHelpRotate;
constexpr uint8_t gsInitHelpRotate2 = gsInitDiff + gsHelpRotate2;
constexpr uint8_t gsInitHelpRotateSlide = gsInitDiff + gsHelpRotateSlide;
constexpr uint8_t gsInitHelpRotateSlide2 = gsInitDiff + gsHelpRotateSlide2;
constexpr uint8_t gsInitHelpSlide = gsInitDiff + gsHelpSlide;
constexpr uint8_t gsInitHelpSlide2 = gsInitDiff + gsHelpSlide2;
constexpr uint8_t gsInitIntro = gsInitDiff + gsIntro;


constexpr uint8_t diffVeryEasy = 0;
constexpr uint8_t diffEasy = 1;
constexpr uint8_t diffNormal = 2;
constexpr uint8_t diffHard = 3;
constexpr uint8_t diffVeryHard = 4;
constexpr uint8_t diffRandom = 5;
constexpr uint8_t diffCount = 6;

constexpr uint8_t gmRotate = 0;
constexpr uint8_t gmSlide = 1;
constexpr uint8_t gmRotateSlide = 2;
constexpr uint8_t gmCount = 3;

constexpr uint8_t mmStartGame = 0;
constexpr uint8_t mmHelp = 1;
constexpr uint8_t mmOptions = 2;
constexpr uint8_t mmCredits = 3;
constexpr uint8_t mmCount = 4;

constexpr uint8_t opMusic = 0;
constexpr uint8_t opSound = 1;
constexpr uint8_t opColor = 2;
constexpr uint8_t opColorInvert = 3;
#ifdef DISABLE_READ_ONLY_SURFACES
constexpr uint8_t opCount = 4;
#else
constexpr uint8_t opCount = 2;
#endif

constexpr uint8_t tsMainMenu = 0;
constexpr uint8_t tsGameMode = 1;
constexpr uint8_t tsDifficulty = 2;
constexpr uint8_t tsOptions = 3;
constexpr uint8_t tsCredits = 4;

constexpr uint8_t levelCount = 25;

constexpr uint8_t arrowDown = 122;
constexpr uint8_t arrowUp = 120;
constexpr uint8_t arrowLeft = 123;
constexpr uint8_t arrowRight = 121;
constexpr uint8_t leftMenu = 118;

constexpr uint8_t frameRate = 18;

extern uint8_t startPos, menuPos, 
        maxLevel, selectedLevel, boardX, boardY, difficulty, 
        gameState, boardWidth, boardHeight, boardSize,
        levelDone, titleStep, gameMode, posAdd, 
        debugMode, mainMenu, option, needRedraw;
        
extern int16_t selectionX, selectionY;
extern uint16_t moves;
extern uint32_t randomSeedGame;
extern unsigned char level[maxBoardSize];
extern Surface *blockTiles;
extern Surface *titlescreen;
extern Surface *selectorTiles;
extern Surface *congratsMap;
extern Surface *selectorTiles;
extern Surface *congratsScreenTiles;
extern Surface *fullTitlescreenMap;
extern float scale;
extern int xoffset;
extern int yoffset;
#endif