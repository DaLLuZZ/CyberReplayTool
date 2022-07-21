void GetButtonString(int buttons, char* szBuffer)
{
	int i = reinterpret_cast<int>(szBuffer);

	if (buttons & IN_MOVELEFT)
		strcat(szBuffer, "+A ");
	if (buttons & IN_FORWARD)
		strcat(szBuffer, "+W ");
	if (buttons & IN_BACK)
		strcat(szBuffer, "+S ");
	if (buttons & IN_MOVERIGHT)
		strcat(szBuffer, "+D ");
	if (buttons & IN_LEFT)
		strcat(szBuffer, "+L ");
	if (buttons & IN_RIGHT)
		strcat(szBuffer, "+R ");
	if (buttons & IN_JUMP)
		strcat(szBuffer, "+J ");
	if (buttons & IN_DUCK)
		strcat(szBuffer, "+C ");
	if (buttons & IN_SPEED)
		strcat(szBuffer, "+speed ");
	if (buttons & IN_ATTACK)
		strcat(szBuffer, "+attack ");
	if (buttons & IN_ATTACK2)
		strcat(szBuffer, "+attack2 ");

	szBuffer[strlen(szBuffer) - 1] = 0;
}

void PrintTickInfo(ReplayFile RFile, int iTick)
{
	if (iTick > RFile.TickCount - 1 || iTick < 0)
		Error("PrintTickInfo: Invalid Tick Number");

	char szSub[16];
	if (RFile.Bonus)
		sprintf(szSub, "Bonus: %i\n", RFile.Bonus);
	else if (RFile.Stage)
		sprintf(szSub, "Stage: %i\n", RFile.Stage);
	else
		szSub[0] = 0;

	char szButtons[64];
	GetButtonString(RFile.Frames[iTick].Buttons, szButtons);

	printf("Map: %s\n%sStyle: %i\n\nTick: %i/%i\n\nButtons: %s [%i]\nDir: %.2f %.2f %.2f\n\nXYZ: %.2f %.2f %.2f\nAng: %.2f %.2f\nVel: %.2f %.2f %.2f\nSpeedXY: %.2f\nSpeedXYZ: %.2f\n\nImpulse: %i\nNewWeapon: %i\nSubtype: %i\nSeed: %i\nPause: %i\n\n", RFile.Map, szSub, RFile.Style, iTick + 1, RFile.TickCount, szButtons, RFile.Frames[iTick].Buttons, RFile.Frames[iTick].PredictedVelocity[0], RFile.Frames[iTick].PredictedVelocity[1], RFile.Frames[iTick].PredictedVelocity[2], RFile.Frames[iTick].ActualOrigin[0], RFile.Frames[iTick].ActualOrigin[1], RFile.Frames[iTick].ActualOrigin[2], RFile.Frames[iTick].PredictedAngles[0], RFile.Frames[iTick].PredictedAngles[1], RFile.Frames[iTick].ActualVelocity[0], RFile.Frames[iTick].ActualVelocity[1], RFile.Frames[iTick].ActualVelocity[2], sqrt(RFile.Frames[iTick].ActualVelocity[0] * RFile.Frames[iTick].ActualVelocity[0] + RFile.Frames[iTick].ActualVelocity[1] * RFile.Frames[iTick].ActualVelocity[1]), sqrt(RFile.Frames[iTick].ActualVelocity[0] * RFile.Frames[iTick].ActualVelocity[0] + RFile.Frames[iTick].ActualVelocity[1] * RFile.Frames[iTick].ActualVelocity[1] + RFile.Frames[iTick].ActualVelocity[2] * RFile.Frames[iTick].ActualVelocity[2]), RFile.Frames[iTick].Impulse, RFile.Frames[iTick].NewWeapon, RFile.Frames[iTick].Subtype, RFile.Frames[iTick].Seed, RFile.Frames[iTick].Pause);
}
