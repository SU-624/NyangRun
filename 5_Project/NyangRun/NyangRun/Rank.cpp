#include "lib.h"
#include "Playbuffer.h"
#include "Utils.h"
#pragma warning(disable : 4996)
	
void Rank(int remainTime)
{
	char name[51] = {0,};
	bool check = true;
	bool namecheck = true;
	while (_kbhit()) // Ű �Է� ���۸� ���
		_getch();

	system("cls");

	FILE* fp;
	int x = 25; int y = 12;
	while (check)
	{
		GoToXY(x, y); printf("�١� �̸��� �Է��ϼ��� �ڡ�");
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
						printf("����� ���ش޶� ��");
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

		if (_frames % 100 == 0) // 200 �����Ӹ��� ���
		{
			GoToXY(x + 10, y + 20); printf("�� ���� ��"); // ��¦�Ÿ��� �ϰ� ���� ���
		}
		else if ((_frames % 100 - 50) == 0) // 100 ������ �������� ���� (1�� + @) 
		{
			GoToXY(x + 10, y + 20); printf("                                       "); // ��¦�Ÿ��� �ϰ� ���� ���
		}

		Sleep(10);
	}
	while (_kbhit()) // Ű �Է� ���۸� ���
		_getch();

}