#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <32blit.hpp>

#include "commonvars.hpp"
#include "printfuncs.hpp"
#include "helperfuncs.hpp"


using namespace blit;

// function provided by @Pharap
// If the array is not big enough,
// this will cause an error message at compile time.
template<size_t size>
size_t formatInteger(char (&array)[size], uint16_t integer )
{
    constexpr size_t maxDigits = 10; 
    constexpr size_t maxCharacters = (maxDigits + 1);

    // Check the array size at compile time
    static_assert(size >= maxCharacters, "array is too small");

    constexpr size_t lastIndex = (maxCharacters - 1);

    array[lastIndex] = '\0';

    if(integer == 0)
    {
        array[lastIndex - 1] = '0';
        return 1;
    }

    size_t digits = 0;

    do
    {
        uint8_t digit = integer % 10;
        integer /= 10;

        ++digits;

        array[lastIndex - digits] = ('0' + digit);
    }
    while(integer > 0);

    return digits;
}

//print a number on levelselect or game screen
void printNumber(uint8_t ax, uint8_t ay, uint16_t aNumber, size_t maxDigits)
{
    constexpr size_t buffSize = 10; 
    char number[buffSize + 1];
    size_t digits = formatInteger(number, aNumber);
    size_t maxFor = digits;
    if (digits > maxDigits)
        maxFor = maxDigits;
    for (size_t c=0; c < maxFor; c++)
    {
        if (number[buffSize - digits + c] == '\0')
            return;
        
        set_bkg_tile_xy(ax + (maxDigits-digits) + c, ay, number[buffSize - digits + c] + 32);
    }
}

// void printDebug(uint8_t ax, uint8_t ay, const __FlashStringHelper* amsg)
//  {
//     if(debugMode)
//     {
//         //rememvber current tiles
//         Image* tiles = get_bkg_data();
//         setBlockTilesAsBackground();
//         gb.display.clear(INDEX_BLACK);
//         printMessage(ax, ay, amsg);
//         gb.updateDisplay();
//         delay(2500);
//         //restore the previous tiles
//         set_bkg_data(tiles);
//     }
//  }

// //print a cpuload debug message anywhere on ax,ay using title tiles
// void printDebugCpuRamLoad()    
// {
//     if(debugMode)
//     {
//         //rememvber current tiles
//         Image* tiles = get_bkg_data();
//         setBlockTilesAsBackground();
        
//         //get cpuload
//         char debuginfo[16];
//         sprintf(debuginfo, "C:%3d R:%5d", gb.getCpuLoad(), gb.getFreeRam());

//         //get digits
//         size_t len = strlen(debuginfo);

//         //clear space for max 3 digits (i assume 100 is max or at least 999)
//         gb.display.setColor(INDEX_BLACK);
//         gb.display.fillRect(0, 0, 13*8, 8);
    
//         //print debug info
//         for (uint8_t c = 0; c < len; c++)
//         {
//             uint8_t tile = 61U;
//             switch(debuginfo[c])
//             {
//                 case '\0':
//                     //restore the previous tiles
//                     set_bkg_data(tiles);
//                     return;
                
//                 case ':':
//                     tile = 116U;
//                     break;
                       
//                 default:
//                     if ((debuginfo[c] >= 'A') && (debuginfo[c] <= 'Z'))
//                         tile = debuginfo[c] + 25U;
                    
//                     if ((debuginfo[c] >= '0') && (debuginfo[c] <= '9'))
//                         tile = debuginfo[c] + 32U;
//                     break;
//             }

//             set_bkg_tile_xy(c , 0, tile);
//         }
//         //restore the previous tiles
//         set_bkg_data(tiles);
//     }
// }

//print a message on the title screen on ax,ay, the tileset from titlescreen contains an alphabet
void printMessage(uint8_t ax, uint8_t ay, const char* amsg)
{
    size_t p = 0, index = 0;

    while (1)
    {
        char fChar = amsg[p++];
        uint8_t tile = 61U;
        switch (fChar)
        { 
            case '\0':
                return;

            case '[':
                tile = 70U;
                break;

            case ']':
                tile = 64U;
                break;

            case '<':
                tile = 73U;
                break;

            case '>':
                tile = 67U;
                break;

            case '+':
                tile = 63U;
                break;

            case '*':
                tile = 62U;
                break;

            case '|':
                tile = 69U;
                break;

            case '#':
                tile = 65U;
                break;

            case ':':
                tile = 116U;
                break;

            case 'a':
                tile = 119U;
                break;

            case 'b':
                tile = 117U;
                break;
            
            default:
                if ((fChar >= 'A') &&  (fChar <= 'Z'))
                    tile = fChar + 25U;
                
                if ((fChar >= '0') && (fChar <= '9'))
                    tile = fChar + 32U;
                break;
        }
        set_bkg_tile_xy(ax + index, ay, tile);
        ++index;
    }
}

//print a message on the CongratsScreen on ax,ay, the tileset from Congrats Screen contains an alphabet in another font
void printCongratsScreen(uint8_t ax, uint8_t ay, const char* amsg)
{
    size_t p = 0, index = 0;

    while (1)
    {
        char fChar = amsg[p++];
        uint8_t tile = 26U;
        switch (fChar) 
        {
            case '\0':
               return;

            default:
                if ((fChar >= 'A') &&  (fChar <= 'Z'))
                    tile =  fChar - 'A';
                break;
        }
        set_bkg_tile_xy(ax + index, ay, tile);
        ++index;
    }
}