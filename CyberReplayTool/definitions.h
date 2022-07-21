#include <iostream>
#include <fstream>
#include <math.h>
#include <windows.h>

#define BM_MAGIC 0xBAADF00D
#define BINARY_FORMAT_VERSION 0x01

#define IN_ATTACK (1 << 0)
#define IN_JUMP (1 << 1)
#define IN_DUCK (1 << 2)
#define IN_FORWARD (1 << 3)
#define IN_BACK (1 << 4)
#define IN_USE (1 << 5)
#define IN_CANCEL (1 << 6)
#define IN_LEFT (1 << 7)
#define IN_RIGHT (1 << 8)
#define IN_MOVELEFT (1 << 9)
#define IN_MOVERIGHT (1 << 10)
#define IN_ATTACK2 (1 << 11)
#define IN_RUN (1 << 12)
#define IN_RELOAD (1 << 13)
#define IN_ALT1 (1 << 14)
#define IN_ALT2 (1 << 15)
#define IN_SCORE (1 << 16)
#define IN_SPEED (1 << 17)
#define IN_WALK (1 << 18)
#define IN_ZOOM (1 << 19)
#define IN_WEAPON1 (1 << 20)
#define IN_WEAPON2 (1 << 21)
#define IN_BULLRUSH (1 << 22)
#define IN_GRENADE1 (1 << 23)
#define IN_GRENADE2 (1 << 24)
#define	IN_LOOKSPIN (1 << 25)

struct FrameInfo
{
	int Buttons;
	int Impulse;
	float ActualVelocity[3];
	float PredictedVelocity[3];
	float PredictedAngles[2];
	float ActualOrigin[3];
	float PredictedOrigin[3];
	int NewWeapon;
	int Subtype;
	int Seed;
	int Pause;
};

struct ReplayFile
{
	char Path[256];
	char Map[32];
	int Style;
	int Bonus;
	int Stage;
	int BinaryFormatVersion;
	char Time[32];
	char Name[128];
	int Checkpoints;
	int TickCount;
	float InitialPosition[3];
	float InitialAngles[3];
	FrameInfo *Frames;
};

void Error(char szError[] = "Unknown Error")
{
	HWND hConsoleWnd = GetForegroundWindow();
	ShowWindow(hConsoleWnd, SW_HIDE);
	MessageBox(hConsoleWnd, szError, "ERROR", MB_OK);
	exit(EXIT_FAILURE);
}
