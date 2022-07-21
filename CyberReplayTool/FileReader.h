/**
 * Returns Pointer To Replay File Name Null-Terminated String
 * 
 * @param szPath      Pointer To Full File Name (Path) Null-Terminated String
 */
char* GetReplayFileName(char szPath[]);

/**
 * Returns Pointer To Map Name Null-Terminated String
 * 
 * @param szFileName  Pointer To File Name Null-Terminated String
 * @param style       Style (copyback)
 * @param bonus       Bonus (copyback)
 * @param stage       Stage (copyback)
 */
char* GetReplayMapName(char szFileName[], int& style, int& bonus, int& stage);

/**
 * Reads Replay File From Disk And Returns ReplayFile Object
 * 
 * @param szPath      Pointer To Full File Name (Path) Null-Terminated String
 */
ReplayFile LoadReplayFile(char szPath[]);

#include "FileReader.cpp"
