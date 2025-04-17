#ifndef PRINTFUNCS_H
#define PRINTFUNCS_H

#include <stdint.h>
#include <32blit.hpp>

using namespace blit;

void printDebugCpuRamFpsLoad(uint32_t start_frame, uint32_t end_frame);
void printDebug(uint8_t ax, uint8_t ay, const char* amsg);
void printNumber(uint8_t ax, uint8_t ay, uint16_t aNumber, size_t maxDigits);
void printMessage(uint8_t ax, uint8_t ay, const char* amsg);
void printCongratsScreen(uint8_t ax, uint8_t ay, const char* amsg);

#endif