#include "lib.h"
#include "Playbuffer.h"
#include "Utils.h"

extern void WriteBuffer(int x, int y, char str[]);
extern char g_collisonMap[TILEMAP_Y][TILEMAP_X];
char standCatArry[5][16] =
{
	{"          11111"},
	{"           1111"},
	{"           1111"},
	{"         111111"},
	{"         11111 "}
};

char slideCatArry[4][14] =
{ {"             "},
  {"       11  11"},
  {"      1     1" },
	{"    1      11"}
};

int catCollisonbuffer[TILEMAP_Y][TILEMAP_X];
int mapCollisonbuffer[TILEMAP_Y][TILEMAP_X];

//cat의 충돌위치를 체크
void CatPosCheck(_Position catpos, bool Check)
{
	int standCatX = 0;
	int standCatY = 0;

	std::string strTemp;
	for (int y = 0; y < TILEMAP_Y; y++)
	{
		for (int x = 0; x < TILEMAP_X; x++)
		{
			if (Check)
			{
				if ((x >= catpos.x  && catpos.x + 14 >= x) && (y >= catpos.y-4 && catpos.y >= y))
				{
					if (standCatArry[standCatY][standCatX] == '1') //y,x를 별도로 줘야한다. 안그러면 지금 over된 값이 들어가게 됨.
					{
						catCollisonbuffer[y][x] = 1;
						strTemp += " X ";
					}
					else
					{
						catCollisonbuffer[y][x] = 0;
						strTemp += " O ";
					}
					standCatX++;
					if (standCatX >= 16)
					{
						standCatX = 0;
						standCatY++;
					}
				}
				else
				{
					catCollisonbuffer[y][x] = 0;
					strTemp += " . ";
				}
			}
			else
			{
				if ((x >= catpos.x + 1 && catpos.x + 13 >= x) && (y >= catpos.y && catpos.y - 4 >= y))
				{
					if (slideCatArry[y][x] != ' ')
					{
						catCollisonbuffer[y][x] = 1;
						strTemp += " X ";
					}
					else
					{
						catCollisonbuffer[y][x] = 0;
						strTemp += " O ";
					}

				}
				else
				{
					catCollisonbuffer[y][x] = 0;
					strTemp += " . ";
				}
			}
		}
		strTemp += "\n";
		OutputDebugStringA(strTemp.c_str());
		strTemp = "";
	}

}

void MapPosCheck()
{
	std::string strTemp;
	for (int y = 0; y < TILEMAP_Y; y++)
	{
		for (int x = 0; x < TILEMAP_X; x++)
		{
			if (g_collisonMap[y][x] == '#')
			{
				mapCollisonbuffer[y][x] = 1;
				strTemp += " X ";
			}
			else
			{
				mapCollisonbuffer[y][x] = 0;
				strTemp += " O ";
			}
		}
		strTemp += "\n";
		OutputDebugStringA(strTemp.c_str());
		strTemp = "";
	}
}

bool PlayerCollison(_Position catpos, bool check)
{
	char buffer[50] = "";
	sprintf_s(buffer, 50, "(%d,%d)\n", catpos.x, catpos.y); //맵을 버퍼에 넣어준다.
	OutputDebugStringA(buffer);

	CatPosCheck(catpos, check);

	MapPosCheck();

	for (int y = 0; y < TILEMAP_Y; y++)
	{
		for (int x = 0; x < TILEMAP_X; x++)
		{
			if ((catCollisonbuffer[y][x] == 1) && (mapCollisonbuffer[y][x] == 1))
			{
				//sprintf_s(buffer, 50, "(%d,%d)\n", x, y); //맵을 버퍼에 넣어준다.
				OutputDebugStringA(buffer);
				return true; 
			}
		}
	}

	return false;
}