#include "lib.h"
#include "Playbuffer.h"
#include "Utils.h"
#pragma warning(disable : 4996)
	
void Rank(int remainTime)
{
	char name[51] = {0,};
	bool check = true;
	bool namecheck = true;
	while (_kbhit()) // 키 입력 버퍼를 비움
		_getch();

	system("cls");

	FILE* fp;
	int x = 25; int y = 12;
	while (check)
	{
		GoToXY(x, y); printf("☆★ 이름을 입력하세요 ★☆");
		GoToXY(x, y + 2); scanf("%s", name);

		for (int i = 0; i < 50; i++)
		{
			if (!(name[i] >= 'A' && name[i] <= 'Z'))
			{
				if (!(name[i] >= 'a' && name[i] <= 'z'))
				{
					if (name[i+1] == '\0')
						break;
					else if (!name[i] == ' ')
					{
						GoToXY(x, y + 2);
						printf("영어로 말해달라 냥");
					}
				}
			}
		}
		if (namecheck)
			check = false;
		else
			check = true;
	}
	fp = fopen("..\\4_Resources\\Rank\\Rank.txt", "at");
	if (fp == NULL) { fp = fopen("..\\4_Resources\\Rank\\Rank.txt", "wt"); }


	fprintf(fp, "%s %d \n", name, remainTime);
	fclose(fp);

	int _frames = 0;

	for (_frames = 0;; _frames++)
	{
		if (_kbhit())
			break;

		if (_frames % 100 == 0) // 200 프레임마다 띄움
		{
			GoToXY(x + 10, y + 20); printf("또 보자 냥"); // 반짝거리게 하고 싶은 욕심
		}
		else if ((_frames % 100 - 50) == 0) // 100 프레임 간격으로 지움 (1초 + @) 
		{
			GoToXY(x + 10, y + 20); printf("                                       "); // 반짝거리게 하고 싶은 욕심
		}

		Sleep(10);
	}
	while (_kbhit()) // 키 입력 버퍼를 비움
		_getch();

}