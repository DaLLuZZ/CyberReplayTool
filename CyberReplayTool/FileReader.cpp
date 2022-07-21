char* GetReplayFileName(char szPath[])
{
	int iLen = strlen(szPath);

	if (szPath[iLen - 1] != 'c' || szPath[iLen - 2] != 'e' || szPath[iLen - 3] != 'r' || szPath[iLen - 4] != '.')
		Error("Unknown File Extension");

	static char szFileName[64];
	for (int i = iLen - 5; i > 0; i--)
	{
		if (szPath[i] == '\\')
		{
			for (int j = 0; i < iLen - 5; j++)
			{
				i++;
				szFileName[j] = szPath[i];
				szFileName[j + 1] = 0;
			}
			break;
		}
	}

	return szFileName;
}

char* GetReplayMapName(char szFileName[], int& style, int& bonus, int& stage)
{
	char* pos;
	static char szMap[32];
	style = 0;
	bonus = 0;
	stage = 0;

	if (pos = strstr(szFileName, "style_"))
		style = pos[6] - '0';

	if (pos = strstr(szFileName, "bonus_"))
	{
		pos += 6;
		char b[4];
		for (int i = 0; isdigit(pos[i]); i++)
			b[i] = pos[i];
		bonus = atoi(b);
	}
	else if (pos = strstr(szFileName, "stage_"))
	{
		pos += 6;
		char b[4];
		for (int i = 0; isdigit(pos[i]); i++)
			b[i] = pos[i];
		stage = atoi(b);
	}

	strcpy(szMap, strstr(szFileName, "surf_"));
	if (stage)
		szMap[strstr(szMap, "_stage_") - szMap] = 0;
	else if (bonus)
		szMap[strstr(szMap, "_bonus_") - szMap] = 0;
	else if (style)
		szMap[strstr(szMap, "_style_") - szMap] = 0;

	return szMap;
}

ReplayFile LoadReplayFile(char szPath[])
{
	std::ifstream hFile;
	hFile.open(szPath, std::ios::in | std::ios::binary);

	if (!hFile.is_open())
		Error("File Was Not Opened!");

	int iMagic;
	hFile.read(reinterpret_cast<char *>(&iMagic), sizeof(iMagic));
	if (iMagic != BM_MAGIC)
		Error("Unknown Magic Bytes Signature!");

	char iBinaryFormatVersion;
	hFile.read(&iBinaryFormatVersion, sizeof(iBinaryFormatVersion));
	if (iBinaryFormatVersion != BINARY_FORMAT_VERSION)
		Error("Unknown Replay File Format Version!");

	ReplayFile RFile;
	RFile.BinaryFormatVersion = static_cast<int>(iBinaryFormatVersion);

	char iLen;
	hFile.read(&iLen, sizeof(iLen));

	char szTime[16];
	hFile.read(szTime, iLen);
	szTime[iLen] = 0;
	strcpy(RFile.Time, szTime);

	char szName[128];
	hFile.read(&iLen, sizeof(iLen));
	hFile.read(szName, iLen);
	szName[iLen] = 0;
	strcpy(RFile.Name, szName);

	hFile.read(reinterpret_cast<char *>(&RFile.Checkpoints), sizeof(RFile.Checkpoints));
	hFile.read(reinterpret_cast<char *>(&RFile.InitialPosition), sizeof(RFile.InitialPosition));

	for (int i = 0; i < 2; i++)
		hFile.read(reinterpret_cast<char *>(&RFile.InitialAngles[i]), sizeof(RFile.InitialAngles[i]));

	hFile.read(reinterpret_cast<char *>(&RFile.TickCount), sizeof(RFile.TickCount));

	FrameInfo *Frames = new FrameInfo[RFile.TickCount];
	for (int i = 0; i < RFile.TickCount; i++)
	{
		hFile.read(reinterpret_cast<char *>(&Frames[i].Buttons), sizeof(Frames[i].Buttons));
		hFile.read(reinterpret_cast<char *>(&Frames[i].Impulse), sizeof(Frames[i].Impulse));
		hFile.read(reinterpret_cast<char *>(&Frames[i].ActualVelocity), sizeof(Frames[i].ActualVelocity));
		hFile.read(reinterpret_cast<char *>(&Frames[i].PredictedVelocity), sizeof(Frames[i].PredictedVelocity));
		hFile.read(reinterpret_cast<char *>(&Frames[i].PredictedAngles), sizeof(Frames[i].PredictedAngles));
		hFile.read(reinterpret_cast<char *>(&Frames[i].ActualOrigin), sizeof(Frames[i].ActualOrigin));
		hFile.read(reinterpret_cast<char *>(&Frames[i].PredictedOrigin), sizeof(Frames[i].PredictedOrigin));
		hFile.read(reinterpret_cast<char *>(&Frames[i].NewWeapon), sizeof(Frames[i].NewWeapon));
		hFile.read(reinterpret_cast<char *>(&Frames[i].Subtype), sizeof(Frames[i].Subtype));
		hFile.read(reinterpret_cast<char *>(&Frames[i].Seed), sizeof(Frames[i].Seed));
		hFile.read(reinterpret_cast<char *>(&Frames[i].Pause), sizeof(Frames[i].Pause));
	}

	RFile.Frames = Frames;

	hFile.close();
	return RFile;
}
