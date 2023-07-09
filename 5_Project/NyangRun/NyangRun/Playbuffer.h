#pragma once
#include <stdio.h>
#include "Utils.h"

void TilteText();
void StoryPrint();
void PrintRank();
void Render(int elapedTime);
void Update(int elapedTime);
void ClearBuffer();
void GameLoop();
void Init();
void FlipBuffer();
void WriteBuffer(int x, int y, char str[]);
void LoadMap();
void DrawCurTime();
void DrawMap(int x, int y, int StartX);
void DrawCat(int start_x, int start_y);
void MoveCharacter(int elapedTime);
void ProcessInput(int elapedTime);
struct _Position
{
	int x;
	int y;
};
struct _TileMap
{
	char map[TILEMAP_Y][TILEMAP_X]; //鸥老甘
	char collisionmap[TILEMAP_Y][TILEMAP_X]; //拱府面倒 鸥老甘
};
bool PlayerCollison(_Position catpos,bool check);
void Rank(int remainTime);
void View_Ranking();