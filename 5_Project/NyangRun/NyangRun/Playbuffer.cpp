#include "lib.h"
#include "Utils.h"
#include "Playbuffer.h"
#pragma warning(disable : 4996)

void DrawTimeCount();
extern  void PlayEffect();

enum class KEY_SATATUS
{
	KEY_NONE,
	KEY_DOWN,
	KEY_DOWN_ING,
	KEY_UP
}g_keyStatus;

HANDLE g_hBuffer[2];
int g_nScreenIndex;
bool g_Run = true;
bool g_GameOver = false;

//�ð����� ����
const int FRAMES_PER_SECOND = 30;
const int MSECS_PER_FRAME = 1000 / FRAMES_PER_SECOND;
const int TIME_COUNT = 10;
int g_elapedTimeArray[TIME_COUNT];
int g_FPS;

//ĳ���� ������ �����̵带 üũ�ϴ� ����
bool isJumping = false; // PrcessInput() UPŰ�� �޾��� �� �ö󰡴� ����
bool isHovering = false;
bool isDown = false;  // PrcessInput() ������ �ϰ� ������ �� �ʿ��� ���� 
bool isSlide = false;  // PrcessInput() DOWNŰ�� �޾��� �� ĳ���� �Ѿ��� ģ���� �׷��ִ� ����
bool isStand = true;  // PrcessInput() �Ѿ��� ģ���� �ٽ� �Ͼ�ִ� ������� �׷��ִ� ����
bool isJumpingCheck = true;

//���� üũ ����
int CatMove_Count = 0;
//�����̵� ��ȯ üũ ����
int CatSlide_Count = 0;
//Hovering üũ �Լ�
//int CatStay = 0;

//���� ����ϴ� ������ �����ϴ� �迭
int stage1MapPrint[10];
int stage2MapPrint[10];

//�ʿ� �������� ����
int g_mapMoveX;
int g_mapSpeed;
bool g_moveControl;

static char g_standCatArry[4][14] =
{
	{"      /|  /| "},
	{"     ( o_o ) "},
	{" @--(  u u ) "},
	{"       & &   "}
};

static char g_slideCatArry[4][14] =
{ {"             "},
   {"       /|  /|"},
   {"      ( >_< )" },
	{" @--(      )="}
};

_TileMap stage1Map[5];
_TileMap stage2Map[5];

//����� ��ġ
_Position catDefaultPos; //�ٲ�� �ȵǴ� ��
_Position catCurPos; //���� ��ġ

//�� ��ġ
_Position mapDefaultPos;
_Position mapCurPos;

char g_collisonMap[TILEMAP_Y][TILEMAP_X];
int g_EndTime;//ex

void Reset_CopyMazePlayBoard(char g_copyMazePlayBoard[TILEMAP_Y][TILEMAP_X])
{
	fill(&g_copyMazePlayBoard[0][0], &g_copyMazePlayBoard[TILEMAP_Y - 1][TILEMAP_X], '0');
}
//�ʱ�ȭ
void Init()
{
	while (_kbhit()) // Ű �Է� ���۸� ���
		_getch();
	g_Run = true;
	g_GameOver=false;
	Reset_CopyMazePlayBoard(g_collisonMap);
	g_EndTime = clock();
	g_mapMoveX = 0;
	g_mapSpeed = 4;
	srand((unsigned int)time(NULL));
	int randomnum = 0;
	LoadMap();
	g_moveControl = true;

	mapDefaultPos.x = 0;
	mapDefaultPos.y = 0;

	catDefaultPos.x = CAT_POSX;
	catDefaultPos.y = CAT_POSY;

	mapCurPos = mapDefaultPos;
	catCurPos = catDefaultPos;

	stage1MapPrint[0] = 2;
	//stage1MapPrint[1] = 1;
	//stage1MapPrint[2] = 4;
	//stage1MapPrint[3] = 1;
	//stage1MapPrint[4] = 4;
	//stage1MapPrint[5] = 1;
	//stage1MapPrint[6] = 3;
	//stage1MapPrint[7] = 4;
	//stage1MapPrint[8] = 0;
	//stage1MapPrint[9] = 2;


	for (int i = 1; i < 10; i++) //rand���� �ʱ�ȭ�Ҷ� 10���� �־���(stage1)
	{
		randomnum = rand() % 5; //0~4
		stage1MapPrint[i] = randomnum;
	}
	for (int i = 0; i < 10; i++) //rand���� �ʱ�ȭ �Ҷ� 10���� �־���(stage2)
	{
		randomnum = 5 + rand() % 5; //5~9
		stage2MapPrint[i] = randomnum;
	}

}

//������Ʈ
void Update(int elapedTime)
{
	static int UpdateTick = 0;
	UpdateTick += elapedTime;

	if (isJumping || isDown || isStand || isHovering)
	{
		if (PlayerCollison(catCurPos, true))
			g_GameOver = true;
	}
	else
	{
		if (PlayerCollison(catCurPos, false))
			g_GameOver = true;
	}
	if (g_GameOver)
	{
		//Sleep(30000);
		g_Run = false;
	}
}


//���� ������ ������ ���丮 ȭ��
void StoryPrint()
{
	int x = 8, y = 5;
	int _frames = 0; //frame�� ��� ����
	char _command = 0; // ���� Ŀ�ǵ带 �޴� ����

	int _posOfChoice = 0;
	bool _startFlag = false;
	bool _Cursor = false;

	GoToXY(x + 15, y + 4);
	printf("              /��_________/��\n");
	GoToXY(x + 15, y + 5);
	printf("             ����         ����  \n");
	GoToXY(x + 15, y + 6);
	printf("         =======  0    0   ======= \n");
	GoToXY(x + 15, y + 7);
	printf("              ��    --      /\n");
	GoToXY(x + 15, y + 8);
	printf("               /            ��\n");
	GoToXY(x + 15, y + 9);
	printf("              /              ��\n");
	GoToXY(x + 15, y + 10);
	printf("             ��   ���� ����  ��\n");
	GoToXY(x + 15, y + 11);
	printf("              ��  ���� ����  / \n");
	GoToXY(x + 15, y + 12);
	printf("               ��_����_����_/#########��\n");

	GoToXY(x + 15, y + 14);
	printf("����̴� ���� �ڵ��ϴ� ���簡 �ӽ��ϴ�.......\n");
	GoToXY(x + 13, y + 15);
	printf("�̷� ������ ���ĳ����� ���ο� ���縦 ã������ �մϴ�.\n");
	GoToXY(x + 14, y + 16);
	printf("�������� ����̰� ���ο� ���縦 ã�� �����ּ���.\n");

	while (!_startFlag)
	{
		GoToXY(x + 35, y + 18);
		if (_kbhit())
		{
			if (_getch() == SPACE)
				_startFlag = true;
		}
		if (!_Cursor)
		{
			printf("��");
			_Cursor = !_Cursor;
		}
		else
		{
			GoToXY(x + 35, y + 18);
			printf("  ");
			_Cursor = !_Cursor;

		}
		Sleep(100); //Sleep�� ���߱⶧���� �ð����� �����ͼ� �װɷ� �����̰� �����(���߿� ����)
	}

}

//���� ����
void CreatBuffer()
{
	COORD size = { MAP_SIZEX, MAP_SIZEY }; //�ʻ�����
	CONSOLE_CURSOR_INFO cci; //Ŀ�������� �ҷ��´�.

	SMALL_RECT rect;
	rect.Bottom = 0;
	rect.Left = 0;
	rect.Right = MAP_SIZEX - 1;
	rect.Top = MAP_SIZEY - 1;


	g_hBuffer[0] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleScreenBufferSize(g_hBuffer[0], size);
	SetConsoleWindowInfo(g_hBuffer[0], TRUE, &rect);

	g_hBuffer[1] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleScreenBufferSize(g_hBuffer[1], size);
	SetConsoleWindowInfo(g_hBuffer[1], TRUE, &rect);

	cci.dwSize = 1;
	cci.bVisible = FALSE;
	SetConsoleCursorInfo(g_hBuffer[0], &cci);
	SetConsoleCursorInfo(g_hBuffer[1], &cci);
}

//���� ����
void ClearBuffer()//���۸� ����
{
	COORD Coor = { 0,0 };
	DWORD dw;
	FillConsoleOutputCharacter(g_hBuffer[g_nScreenIndex], ' ', MAP_SIZEX * MAP_SIZEY, Coor, &dw);
}

//���� �׸�
void WriteBuffer(int x, int y, char str[])
{
	DWORD dw;
	COORD CursorPosition = { x, y };
	SetConsoleCursorPosition(g_hBuffer[g_nScreenIndex], CursorPosition);
	WriteFile(g_hBuffer[g_nScreenIndex], str, strlen(str), &dw, NULL);
}

void LoadMap() //��� �ε���� Ȯ����.
{
	int _stage1map = 0;
	int _stage2map = 0;

	FILE* fs[20];
	fs[0] = fopen("..\\4_Resources\\Maptile\\Map0.txt", "r");
	fs[1] = fopen("..\\4_Resources\\Maptile\\Map1.txt", "r");
	fs[2] = fopen("..\\4_Resources\\Maptile\\Map2.txt", "r");
	fs[3] = fopen("..\\4_Resources\\Maptile\\Map3.txt", "r");
	fs[4] = fopen("..\\4_Resources\\Maptile\\Map4.txt", "r");
	fs[5] = fopen("..\\4_Resources\\Maptile\\Map5.txt", "r");
	fs[6] = fopen("..\\4_Resources\\Maptile\\Map6.txt", "r");
	fs[7] = fopen("..\\4_Resources\\Maptile\\Map7.txt", "r");
	fs[8] = fopen("..\\4_Resources\\Maptile\\Map8.txt", "r");
	fs[9] = fopen("..\\4_Resources\\Maptile\\Map9.txt", "r");

	fs[10] = fopen("..\\4_Resources\\Maptile\\CollisionMap0.txt", "r");
	fs[11] = fopen("..\\4_Resources\\Maptile\\CollisionMap1.txt", "r");
	fs[12] = fopen("..\\4_Resources\\Maptile\\CollisionMap2.txt", "r");
	fs[13] = fopen("..\\4_Resources\\Maptile\\CollisionMap3.txt", "r");
	fs[14] = fopen("..\\4_Resources\\Maptile\\CollisionMap4.txt", "r");
	fs[15] = fopen("..\\4_Resources\\Maptile\\CollisionMap5.txt", "r");
	fs[16] = fopen("..\\4_Resources\\Maptile\\CollisionMap6.txt", "r");
	fs[17] = fopen("..\\4_Resources\\Maptile\\CollisionMap7.txt", "r");
	fs[18] = fopen("..\\4_Resources\\Maptile\\CollisionMap8.txt", "r");
	fs[19] = fopen("..\\4_Resources\\Maptile\\CollisionMap9.txt", "r");

	for (int i = 0; i < 10; i++)
	{
		if (_stage1map < 5)
		{
			for (int j = 0; j < TILEMAP_Y; j++)
			{
				fgets(stage1Map[_stage1map].map[j], TILEMAP_X + 1, fs[i]); //string���� ���پ� �޾ƿ´�.
			}
			_stage1map++;
		}
		else
		{
			for (int j = 0; j < TILEMAP_Y; j++)
			{

				fgets(stage2Map[_stage2map].map[j], TILEMAP_X + 1, fs[i]); //string���� ���پ� �޾ƿ´�.
			}
			_stage2map++;
		}
	}
	_stage1map = 0;
	_stage2map = 0;

	for (int i = 10; i < 20; i++)
	{
		if (_stage1map < 5)
		{
			for (int j = 0; j < TILEMAP_Y; j++)
			{
				fgets(stage1Map[_stage1map].collisionmap[j], TILEMAP_X + 1, fs[i]); //string���� ���پ� �޾ƿ´�.
			}
			_stage1map++;
		}
		else
		{
			for (int j = 0; j < TILEMAP_Y; j++)
			{
				fgets(stage2Map[_stage2map].collisionmap[j], TILEMAP_X + 1, fs[i]); //string���� ���پ� �޾ƿ´�.
			}
			_stage2map++;
		}
	}

}

//�ð� �׷��ִ� �Լ�
void DrawCurTime()
{
	time_t t = time(NULL);
	struct tm tm;
	localtime_s(&tm, &t);

	char buffer[128] = "";
	sprintf_s(buffer, "now: %d-%d-%d %d:%d:%d\n",
		tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday,
		tm.tm_hour, tm.tm_min, tm.tm_sec); //���ۿ� �ִ°�

	WriteBuffer(1, 3, buffer);
}

//����� �׷���
void DrawCat(int start_x, int start_y)
{
	char Standbuffer[200] = "";
	if (isJumping || isDown || isStand || isHovering)
	{
		for (int i = 0; i < 4; i++)
		{
			sprintf_s(Standbuffer, "%s", g_standCatArry[i]);
			WriteBuffer(start_x, start_y + i, Standbuffer);
		}
		/*	if (PlayerCollison(catCurPos, true))
					g_GameOver = true;*/
	}
	char Slidebuffer[200] = "";
	if (isSlide)
	{
		for (int i = 0; i < 4; i++)
		{
			sprintf_s(Slidebuffer, "%s", g_slideCatArry[i]);
			WriteBuffer(start_x, start_y + i, Slidebuffer);
		}
		/*if (PlayerCollison(catCurPos, false))
			g_GameOver = true;*/
	}

}

void DrawMap(int x, int y, int startidx)
{
	char totalmap[TILEMAP_Y][MAP_SIZEX]; //��� ���� ������ ���� �迭�� ����

	char buffer[200];
	int totalsize = 0;

	//if (collisonIdx >= TILEMAP_X)
	//	collisonIdx = 0;
	//���� ��� ���� ������ ��´�
	//ȭ�鿡 �ִ� 3�������� ȭ���� ������ �ȴ�.
	for (int mapY = 0; mapY < TILEMAP_Y; mapY++)
	{
		int totalMapX = 0;
		int tile1MapX = startidx;
		int collisonIdx = 0;

		for (; tile1MapX < TILEMAP_X;
			tile1MapX++, totalMapX++)
		{
			totalmap[mapY][totalMapX] = stage1Map[stage1MapPrint[0]].map[mapY][tile1MapX]; //�ؽ�Ʈ�� �����°� �ʹ� �翬�ϴ�. ���� ������ �� ¥�� �� �����̼��� �ߵɰŰ���.
			/*g_collisonMap[mapY][collisonIdx] = stage1Map[stage1MapPrint[0]].collisionmap[mapY][tile1MapX];
			collisonIdx++;*/
		}
		totalMapX--; //�̰� ������ ������ totalMap�� ++�� �Ǽ� ������ �ǹǷ� �߰��� ���� ���� �ʴ� x��ǥ? �ε���?�� �����.

		int tile2MapX = 0;

		for (; tile2MapX < TILEMAP_X && totalMapX < MAP_SIZEX;
			tile2MapX++, totalMapX++)
		{
			totalmap[mapY][totalMapX] = stage1Map[stage1MapPrint[1]].map[mapY][tile2MapX]; //�ؽ�Ʈ�� �����°� �ʹ� �翬�ϴ�. ���� ������ �� ¥�� �� �����̼��� �ߵɰŰ���.
		}
		totalMapX--;

		int tile3MapX = 0;

		for (; tile3MapX < TILEMAP_X && totalMapX < MAP_SIZEX;
			tile3MapX++, totalMapX++)
		{
			totalmap[mapY][totalMapX] = stage1Map[stage1MapPrint[2]].map[mapY][tile3MapX]; //�ؽ�Ʈ�� �����°� �ʹ� �翬�ϴ�. ���� ������ �� ¥�� �� �����̼��� �ߵɰŰ���.
		}
	}

	for (int y = 0; y < TILEMAP_Y; y++)
	{
		for (int x = 0; x < 60; x++)
		{
			g_collisonMap[y][x] = totalmap[y][x];
		}
	}

	//�׸��� �� ���� �迭�� buffer�� �ִ´�.
	// �װ� ����Ѵ�.
	for (int i = 0; i < TILEMAP_Y; i++)
	{
		for (int j = 0; j < MAP_SIZEX; j++)
		{
			sprintf_s(buffer, 200, "%c", totalmap[i][j]); //���� ���ۿ� �־��ش�.
			WriteBuffer(x + j, y + i, buffer); // ������ ��ǥ�� �����ش�. -> �ϴ� �� ���� ���߿� ���� �ʿ�
		}
	}
}

//�ð� üũ �Լ�
void DrawTimeCount()
{

	int current_time = 0;

	int elapedTime;
	elapedTime = clock() - g_EndTime;


	current_time = elapedTime / 1000;


	int second = current_time % 60;
	int min = current_time / 60;

	char timeStr[100];
	sprintf(timeStr, "%02d : %02d", min, second % 60);

	WriteBuffer(60, 0, timeStr);

}


void MoveCharacter(int elapedTime)
{
	static int UpdateTick = 0;
	UpdateTick += elapedTime;

	if (isJumping == true)
	{
		isJumpingCheck = false;
		if (CatMove_Count >= 13)
		{
			isJumping = false;
			isHovering = true;
			isDown = false;
		}
		else
		{ // ���� ���� �ڵ�
			if (UpdateTick >= 100)
			{
				UpdateTick = 0;
				CatMove_Count += 2;
				catCurPos.y -= 2;
			}
		}
	}
	else if (isHovering == true)
	{
		//500msec������ ȣ����
		static int SlidingTime = 0;

		if (isSlide == true)
		{
			SlidingTime = 1000;
			isSlide = false;
		}
		if (UpdateTick >= 1000 + SlidingTime)
		{
			isHovering = false;
			isDown = true;
		}
	}
	else if (isDown == true)
	{
		if (CatMove_Count <= 0)
		{
			isJumping = false;
			isDown = false;
			isStand = true;
			isJumpingCheck = true;
		}
		else
		{
			if (UpdateTick >= 100)
			{
				UpdateTick = 0;
				CatMove_Count -= 2;
				catCurPos.y += 2;
			}
		}
	}
}

int GetKey()
{
	char _command = ' ';
	if (_kbhit())
	{
		_command = _getch();
		return _getch();
	}
	return 0;
}

// Ű�Է� ó��
/*
0 (0x0000) ������ ���� ���� ���� ȣ�� �������� �ȴ��� ����
0x8000 ������ ���� ���� ���� ȣ�� �������� ���� ����
0x8001 ������ ���� ���� �ְ� ȣ�� �������� ���� ����
1 (0x0001) ������ ���� ���� �ְ� ȣ�� �������� �ȴ��� ����*
* */
void ProcessInput(int elapedTime)
{
	while (_kbhit()) // Ű �Է� ���۸� ���
		_getch();
	
	if ((GetAsyncKeyState(VK_UP) & 8001))
	{
		PlayEffect();
		if(isJumpingCheck)
		isJumping = true;
	}
	//else if (GetAsyncKeyState(VK_DOWN) & 8001)
	//{
	//	isSlide = true;
	//}
	MoveCharacter(elapedTime);
}

void PushMap()
{
	srand((unsigned int)time(NULL));
	int randomnum = 0;
	randomnum = rand() % 5;
	stage1MapPrint[9] = randomnum;
}

void PopMap()
{
	memcpy(stage1MapPrint, stage1MapPrint + 1, sizeof(int) * 9);
	PushMap();
}

void FlipBuffer()
{
	SetConsoleActiveScreenBuffer(g_hBuffer[g_nScreenIndex]);
	g_nScreenIndex = !g_nScreenIndex;
}



void Render(int elapedTime)
{
	ClearBuffer();
	//DrawFPS();
	//DrawCurTime();
	static int UpdateTick = 0;
	UpdateTick += elapedTime;

	if (g_mapMoveX >= TILEMAP_X)
	{
		PopMap();
		g_mapMoveX = 0;
	}

	DrawMap(mapCurPos.x, mapCurPos.y, g_mapMoveX);//1

	if (UpdateTick >= 0.1)
	{
		//printf("%d\n", UpdateTick);
		UpdateTick = 0;
		g_mapMoveX += g_mapSpeed ;
	}

	elapedTime =clock() - g_EndTime;
	if (elapedTime >= 60000 && g_moveControl)
	{
		g_mapSpeed += 2;
		g_moveControl = false;
	}

	DrawCat(catCurPos.x, catCurPos.y);
	DrawTimeCount();

	FlipBuffer();
	//DrawFPS();

}

void DeleteBuffer()
{
	CloseHandle(g_hBuffer[0]);
	CloseHandle(g_hBuffer[1]);
}

void GameLoop()
{
	Init();
	CreatBuffer();
	ULONGLONG curTime = GetTickCount64(); //����ð�
	ULONGLONG prevTime = GetTickCount64(); //���Žð�

	int diffTime = 0;
	int elapedTime = 0;

	while (g_Run)
	{
		curTime = GetTickCount64();
		elapedTime = curTime - prevTime;

		ProcessInput(elapedTime); //Ű�Է�(ĳ���� Ű�Է�)
		MoveCharacter(elapedTime);
		// �ʴ� ���� ȸ���� �����ϱ� ���� �ڵ�
		diffTime = MSECS_PER_FRAME - elapedTime;
		if (diffTime > 1)
		{
			Sleep(0);
			//Sleep(diffTime);
		}
		else
		{
			Update(elapedTime);

			prevTime = curTime;
		}
		Render(elapedTime);

	}

	DeleteBuffer();
	elapedTime = clock() - g_EndTime;

	Rank(elapedTime / 1000); //(�ȿ� ���� �ð� �־��ֱ�)

}