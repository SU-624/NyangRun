#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 4996)
#include "lib.h"
#include "Utils.h"
#include "Playbuffer.h"

void TilteText()
{
	system("mode con cols=130 lines=40");

	CONSOLE_CURSOR_INFO cursorInfo = { 0, };
	cursorInfo.dwSize = 1;
	cursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);


	int x = 13, y = 2;
	int _frames = 0; //frame�� ��� ����
	char _command = 0; // ���� Ŀ�ǵ带 �޴� ����

	int _posOfChoice = 0; //Ŀ�� ��ġ
	bool _enterCheck = false;
	bool _startFlag = false;
	FILE* fs = NULL;
	char _Name[20][65]; // �������� \n �� ���� 101 ĭ���� �߽��ϴ�.
	int i = 0;
	fs = fopen("..\\4_Resources\\title.txt", "r");
	for (int i = 0; i < 20; i++)
		fgets(_Name[i], 65, fs); //string���� ���پ� �޾ƿ´�.


	for (int i = 0; i < 20; i++)
	{
		GoToXY(x, y + i + 3);
		printf("%s", _Name[i]);
	}


	GoToXY(x + 1, y + 28); printf("##########");
	GoToXY(x + 2, y + 29); printf("  ##");
	GoToXY(x + 2, y + 30); printf("  ##");
	GoToXY(x + 1, y + 31); printf("  ######");
	GoToXY(x + 2, y + 32); printf("  ##");
	GoToXY(x + 2, y + 33); printf("  ##");
	GoToXY(x + 1, y + 34); printf("(CAT TOWER)");

	GoToXY(x + 29, y + 29 + _posOfChoice); printf("��");
	GoToXY(x + 31, y + 29); printf("GAME START");
	GoToXY(x + 31, y + 31); printf("RANK");
	GoToXY(x + 31, y + 33); printf("EXIT");
	GoToXY(x + 29, y + 29);

	for (_frames = 0;; _frames++)
	{
		if (_kbhit())
		{
			_command = _getch(); //�ϳ��� Ű�� �Է� �޴� �Լ�
			switch (_command)
			{
			case SPACE:
			{
				_enterCheck = true;
				break;
			}
			case ENTER:
			{
				_enterCheck = true;
				break;
			}
			case UP:
			{
				_enterCheck = false;
				GoToXY(x + 29, y + 29 + _posOfChoice); printf("  ");
				if (_posOfChoice == 0)
					_posOfChoice += 4;
				else
					_posOfChoice -= 2;
				GoToXY(x + 29, y + 29 + _posOfChoice); printf("��");
				break;
			}
			case DOWN:
			{
				_enterCheck = false;
				GoToXY(x + 29, y + 29 + _posOfChoice); printf("  ");
				if (_posOfChoice == 4)
					_posOfChoice -= 4;
				else
					_posOfChoice += 2;
				GoToXY(x + 29, y + 29 + _posOfChoice); printf("��");

				break;
			}
			default:
			{
				_enterCheck = false;
				break;
			}
			}

			if (_enterCheck)
			{
				if (_posOfChoice == 0) //0 :gamestart
				{
					while (_kbhit()) // Ű �Է� ���۸� ���
						_getch();
					system("cls");
					StoryPrint();
					GameLoop();
					TilteText(); //���� �ٲ����� ����̿� ���� ���� �Ƹ�...
					break;
				}
				else if (_posOfChoice == 2) //2 : Rank
				{
					system("cls");
					View_Ranking();
					break;
				}
				else if (_posOfChoice == 4) // 4 : Exit
				{
					exit(0);
				}

			}

		}//if
	}//for
}

void View_Ranking()
{
	system("cls");

	int x = 24; int y = 5;
	int _frames = 0;
	//SetColor(BLACK, WHITE);

	while (_kbhit()) // Ű �Է� ���۸� ���
		_getch();

	FILE* fp = fopen("..\\4_Resources\\Rank\\Rank.txt", "rt");
	multimap<int, string, greater<int>> mm;

	GoToXY(x, y - 2); printf("�١� RANKING �ڡ�"); Sleep(50);
	GoToXY(x - 3, y); printf("�ڡ� ���� 10���� ����� �١�"); Sleep(50);

	while (!feof(fp))
	{
		string str = "";
		char tempName[50] = { 0 };
		int tempScore = 0;

		fscanf(fp, "%s %d %d", tempName, &tempScore);  //���Ͽ��� �Է¹���
		str = tempName;

		if (str != "")
			mm.insert({ tempScore, str });
	}

	multimap<int, string, greater<int>>::iterator iter;


	GoToXY(x - 5, y + 2);
	cout << "[����]         " << "[�̸�]          " << "[����]";

	int idx = 1;

	if (mm.empty())
	{
		GoToXY(x - 1, y + 4); cout << "��ŷ ����� �����ϴ�.." << endl;
	}
	else
	{
		for (iter = mm.begin(); iter != mm.end(); iter++)
		{
			GoToXY(x - 4, y + idx + 3);  printf("%d", idx);
			GoToXY(x + 3, y + idx + 3);  cout << iter->second;
			GoToXY(x + 12, y + idx + 3); printf("%d", iter->first);
			idx++;

			if (idx == 11)
				break;
		}
	}


	for (_frames = 0;; _frames++)
	{
		if (_kbhit())
			break;
		if (_frames % 100 == 0) // 200 �����Ӹ��� ���
		{

			GoToXY(x, y + 28); printf("�������� ���ư��� ��.");
		}
		else if ((_frames % 100 - 50) == 0) // 100 ������ �������� ���� (1�� + @) 
		{
			GoToXY(x, y + 28); printf("                              "); // ��¦�Ÿ��� �ϰ� ���� ���
		}

		Sleep(10);
	}

	while (_kbhit()) // Ű �Է� ���۸� ���
		_getch();

	system("cls");
	TilteText();
}