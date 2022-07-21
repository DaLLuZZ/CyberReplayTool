/**
 * Prints Information About Specified Frame From Replay File To Console
 * 
 * @param RFile       ReplayFile Object
 * @param iTick       Tick Number To Print
 */
void PrintTickInfo(ReplayFile RFile, int iTick);

/**
 * Writes Buttons To Human-Readable String
 * 
 * @param buttons     Buttons Bits
 * @param szBuffer    String Buffer To Write Into
 */
void GetButtonString(int buttons, char* szBuffer);

#include "TickInfo.cpp"
