#pragma once

#include <stdint.h>
#include <MacTypes.h>
#include <string.h>

std::string GetBaseAppPath();
std::string GetSavePath();
int GetYOffset();
unsigned int GetSystemTimeTick();
unsigned int timeGetTime();
unsigned int GetFreeMemory();
void SwapBuffers();
void LogMsg(const char *lpFormat, ...);
int msleep(unsigned long milisec);