#include <stdint.h>
#include <32blit.hpp>

#include "level.hpp"
#include "commonvars.hpp"
#include "helperfuncs.hpp"
#include "sound.hpp"
#include "printfuncs.hpp"
#include "cursor.hpp"
#include "savestate.hpp"
#include "palettes.hpp"

using namespace blit;

uint8_t paused, wasMusicOn, wasSoundOn,DrawLevelDoneBit, nextDrawWhat;
uint32_t levelDoneTime = 0;
constexpr uint8_t drwNone = 0;
constexpr uint8_t drwMoves = 1;
constexpr uint8_t drwUi = 2;
constexpr uint8_t drwLevel = 4;
constexpr uint8_t drwLevelDone = 8;
constexpr uint8_t drwPause = 16;
constexpr uint8_t drwPartialLevel = 32;
constexpr uint32_t maxLevelDoneTime = 750;


uint8_t drawGame(uint8_t drawWhat)
{
    if (drawWhat == drwNone)
        return drwNone;

    //background
    if(drawWhat & drwUi)
    {
        screen.pen = getColor(0);
        screen.rectangle(Rect((int32_t)((float)maxBoardBgWidth * tileSize *scale  +xoffset), yoffset, 
           (int32_t)((screenWidth - ((float)maxBoardBgWidth * tileSize)) * scale), (int32_t)((float)screenHeight*scale)));
         //LEVEL:
        printMessage(maxBoardBgWidth, 0, "LEVEL:");
        
        //[LEVEL NR] 2 chars
        printNumber(maxBoardBgWidth + 4, 1, selectedLevel, 2);
        
        //A:XXXXXX (XXXXXX="ROTATE" or XXXXXX="SLIDE " or XXXXXX="ROSLID")
        switch (gameMode)
        {
            case gmRotate:
                printMessage(maxBoardBgWidth, 4, "a:");
                printMessage(maxBoardBgWidth, 5, "ROTATE");
                break;
            case gmSlide:
                printMessage(maxBoardBgWidth, 4, "a:");
                printMessage(maxBoardBgWidth, 5, "SLIDE");
                break;
            case gmRotateSlide:
                printMessage(maxBoardBgWidth, 4, "a:");
                printMessage(maxBoardBgWidth, 5, "ROSLID");
                break;
        }

        //B:BACK
        printMessage(maxBoardBgWidth, 6, "b:");
        printMessage(maxBoardBgWidth, 7, "BACK");

        //MOVES:
        printMessage(maxBoardBgWidth, 2, "MOVES:");
    }

    if(drawWhat & drwMoves)
    {
        if(!(drawWhat & drwUi))
        {
             screen.pen = getColor(0);
             screen.rectangle(Rect((int32_t)((screenWidth - (5.0f*tileSize)) * scale) + xoffset, yoffset + (int32_t)(3.0f * tileSize * scale), 
                (int32_t)(5.0f*tileSize*scale), (int32_t)(tileSize*scale)));
        }
        printNumber(maxBoardBgWidth + 1, 3, moves, 5);
    }

    if(drawWhat & drwLevel)
    {
        drawLevel();
        drawCursors();
    }

    //used when redrawing cursor stuff for example (not full background)
    if((drawWhat & drwPartialLevel) && !(drawWhat & drwLevel))
    {
        drawLevel(boardX -1 - posAdd, boardY -1 - posAdd, boardX + boardWidth + 1 + posAdd, boardY + boardHeight + 1 + posAdd);
        drawCursors();
    }
    
    if(drawWhat & drwLevelDone)
    {
        screen.pen = getColor(0);
        screen.rectangle(Rect((int32_t)((float)(((16 - 13) >> 1) * tileSize) *scale + xoffset), 
            ((int32_t)((float)((maxBoardBgHeight >> 1) - 2) * tileSize) * scale + yoffset), 
            (int32_t) (14.0f*tileSize*scale), (int32_t) (5.0f*tileSize*scale)));
        printMessage(((16 - 13) >> 1), (maxBoardBgHeight >> 1) - 2, "[************]");
        printMessage(((16 - 13) >> 1), (maxBoardBgHeight >> 1) - 1, "| LEVEL DONE +");
        printMessage(((16 - 13) >> 1), (maxBoardBgHeight >> 1)    , "|            +");
        printMessage(((16 - 13) >> 1), (maxBoardBgHeight >> 1) + 1, "| a CONTINUE +");
        printMessage(((16 - 13) >> 1), (maxBoardBgHeight >> 1) + 2, "<############>");
    }

    if(drawWhat & drwPause)
    {
        screen.pen = getColor(0);
        screen.rectangle(Rect(xoffset,yoffset+ (int32_t)((float)((maxBoardBgHeight >> 1) - 3) * tileSize*scale), 
            (int32_t)(16.0f*tileSize*scale), (int32_t)6.0f*tileSize*scale));
        printMessage(0, (maxBoardBgHeight >> 1) - 3, "[**************]");
        printMessage(0, (maxBoardBgHeight >> 1) - 2, "|PLEASE CONFIRM+"); 
        printMessage(0, (maxBoardBgHeight >> 1) - 1, "|              +"); 
        printMessage(0, (maxBoardBgHeight >> 1) + 0, "|   a PLAY     +");
        printMessage(0, (maxBoardBgHeight >> 1) + 1, "|   b TO QUIT  +");
        printMessage(0, (maxBoardBgHeight >> 1) + 2, "<##############>");
    }
    
    return drawWhat;
}

void initGame()
{
    paused = 0;
    SelectMusic(musGame);
    setPaletteGame();
    //set background tiles
    setBlockTilesAsBackground();
    //set sprite for selector / cursor
    initCursors();
    setCursorPos(0, boardX + selectionX, boardY + selectionY);
    showCursors();
    levelDoneTime = 0;
    levelDone = 0;
    nextDrawWhat = drwUi + drwLevel + drwMoves;
}

void doPause()
{
    paused = 1;
    playMenuBackSound();
    pauseMusic();
    hideCursors();
    nextDrawWhat = drwUi + drwLevel + drwMoves + drwPause;
}

void doUnPause()
{
    paused = 0;
    unpauseMusic();
    setCursorPos(0, boardX + selectionX, boardY + selectionY);
    showCursors();
    nextDrawWhat = drwUi + drwLevel + drwMoves;
}

void game_render()
{
    nextDrawWhat = drawGame(nextDrawWhat);
    
    if(levelDone)
    {
        if (now() - levelDoneTime > maxLevelDoneTime)
        {
            nextDrawWhat = drwUi + drwLevel + drwMoves + drwLevelDone;
        }
    }
    else
        updateCursorFrame();
}

void game_update()
{
    if(gameState == gsInitGame)
    {
        initGame();
        gameState -= gsInitDiff;
    }

    
    if (buttons.pressed & Button::DPAD_DOWN)
    {
        if(!levelDone && !paused)
        {
            playGameMoveSound();
            //if not touching border on bottom
            if (selectionY + 1 < boardHeight + posAdd)
                selectionY += 1;
            else
            //set to border on top
                selectionY = -posAdd;
            setCursorPos(0, boardX + selectionX, boardY + selectionY);
            //nextDrawWhat |= drwPartialLevel;
        }
    } 

    if (buttons.pressed & Button::DPAD_UP)
    {
        if (!levelDone && !paused)
        {
            //if not touching border on top
            playGameMoveSound();
            if (selectionY -1 >= -posAdd)
                selectionY -= 1;
            else
            //set to border on bottom
                selectionY = boardHeight -1 +posAdd;
            setCursorPos(0, boardX + selectionX, boardY + selectionY);
            //nextDrawWhat |= drwPartialLevel;
        }
    }

    if (buttons.pressed & Button::DPAD_RIGHT)
    {
        if (!levelDone && !paused)
        {
            playGameMoveSound();
            //if not touching border on right
            if(selectionX + 1 < boardWidth + posAdd)
                selectionX += 1;
            else
            //set to border on left
                selectionX = -posAdd;
            setCursorPos(0, boardX + selectionX, boardY + selectionY);
           // nextDrawWhat |= drwPartialLevel;
        }
    }

    if (buttons.pressed & Button::DPAD_LEFT)
    {
        if(!levelDone && !paused)
        {
            playGameMoveSound();
            //if not touching border on left
            if( selectionX -1 >= -posAdd)
                selectionX -= 1;
            //set to border on right
            else
                selectionX = boardWidth -1 + posAdd;
            setCursorPos(0, boardX + selectionX, boardY + selectionY);
            //nextDrawWhat |= drwPartialLevel;
        }
    }

    if (buttons.pressed & Button::A)
    {
        if(paused)
        {
            doUnPause();
            playMenuAcknowlege();
        }
        else
        {
            if(!levelDone)
            {
                if ((selectionX > -1) && (selectionX < boardWidth) &&
                    (selectionY > -1) && (selectionY < boardHeight))
                {   
                    if (gameMode != gmSlide)
                    {
                        rotateBlock((uint8_t)selectionX + ((uint8_t)selectionY * boardWidth));
                        moves++;
                        updateConnected();
                        playGameAction();
                        //nextDrawWhat |= (drwPartialLevel+drwMoves);
                    }
                    else
                    {
                        playErrorSound();
                    }
                }
                else
                {
                    if ((selectionX > -1) && (selectionX < boardWidth))
                    {
                        if (selectionY == -1)
                        {
                            moveBlockDown((uint8_t)selectionX + ((uint8_t)(selectionY+1) * boardWidth));
                            moves++;
                            updateConnected();
                            playGameAction();
                           // nextDrawWhat |= (drwPartialLevel+drwMoves);
                        }
                        else
                        {
                            if (selectionY == boardHeight)
                            {
                                moveBlockUp((uint8_t)selectionX + ((uint8_t)(selectionY-1) * boardWidth));
                                moves++;
                                updateConnected();
                                playGameAction();
                               // nextDrawWhat |= (drwPartialLevel+drwMoves);
                            }
                        }
                    }
                    else
                    {
                        if ((selectionY > -1) && (selectionY < boardHeight))    
                        {
                            if (selectionX == -1)
                            {
                                moveBlockRight((uint8_t)(selectionX + 1) + ((uint8_t)selectionY * boardWidth));
                                moves++;
                                updateConnected();
                                playGameAction();
                               // nextDrawWhat |= (drwPartialLevel+drwMoves);
                            }
                            else
                            {
                                if (selectionX == boardWidth)
                                {
                                    moveBlockLeft( (uint8_t)(selectionX - 1) + ((uint8_t)selectionY * boardWidth));
                                    updateConnected();
                                    moves++;
                                    playGameAction();
                                  //  nextDrawWhat |= (drwPartialLevel+drwMoves);
                                }
                            }
                        }
                        else
                        {
                            playErrorSound();
                        }
                    }
                }
                levelDone = isLevelDone(); 
                if(levelDone)
                {
                    levelDoneTime = now();
                    SelectMusic(musLevelClear);
                    //hide cursor it's only sprite we use
                    hideCursors();
                }
            }
            else
            {
                if (now() - levelDoneTime > maxLevelDoneTime)
                {
                    //goto next level
                    if (difficulty == diffRandom)
                    {
                        //ned new seed based on time
                        randomSeedGame = getRandomSeed();
                        initLevel(randomSeedGame);
                        SelectMusic(musGame);
                        //show cursor again (it's actually to early but i'm not fixing that)
                        setCursorPos(0, boardX + selectionX, boardY + selectionY);
                        showCursors();
                        nextDrawWhat = drwUi + drwLevel + drwMoves;
                    }
                    else
                    {   
                        //goto next level if any
                        if (selectedLevel < maxLevel)
                        {
                            selectedLevel++;
                            unlockLevel(gameMode, difficulty, selectedLevel-1);
                            initLevel(randomSeedGame);
                            SelectMusic(musGame);
                            //show cursor again (it's actually to early but i'm not fixing that)
                            setCursorPos(0, boardX + selectionX, boardY + selectionY);
                            showCursors();
                            nextDrawWhat = drwUi + drwLevel + drwMoves;
                        }
                        else //Goto some congrats screen
                        {
                            gameState = gsInitLevelsCleared;
                        }
                    }
                }
            }
        }
    }

    if(buttons.pressed & Button::B) 
    {
        if(!levelDone)
        {
            if(!paused)
            {
                doPause();
            }
            else
            {
                //need to enable early again to play backsound
                //normally unpause does it but we only unpause
                //after fade
                hideCursors();
                playMenuBackSound();
                gameState = gsInitLevelSelect;
                doUnPause();
                //unpause sets cursor visible !
                hideCursors();
                //need to reset the level to initial state when going back to level selector
                //could not find a better way unfortunatly
                //also we do not want to reset the randomseed used for random level generating
                //or a new level would have been created when going back we only want the level
                //with random to change when pressing left and right in the level selector
                //this way it stays consistent with the normal levels
                //and the player can replay the level if he wants to
                initLevel(randomSeedGame);
            }
        }
    }
}
