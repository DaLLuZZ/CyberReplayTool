#include "CyberReplayTool/definitions.h"
#include "CyberReplayTool/config.h"

int main(int argc, char* argv[])
{
	if (argc != 2)
		Error("File Was Not Opened! (Check ReadMe)");

	char *szFileName = GetReplayFileName(argv[1]);

	int style, bonus, stage;
	char *szMap = GetReplayMapName(szFileName, style, bonus, stage);

	ReplayFile RFile = LoadReplayFile(argv[1]);
	strcpy(RFile.Path, argv[1]);
	strcpy(RFile.Map, szMap);
	RFile.Style = style;
	RFile.Bonus = bonus;
	RFile.Stage = stage;

// Do Stuff Here

	delete[] RFile.Frames;
	return 0;
}
