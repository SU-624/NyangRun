#include "lib.h"
#include "Utils.h"

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
		Sleep(300);
	}

}
