#include "lib.h"
#include "Utils.h"

//게임 시작후 나오는 스토리 화면
void StoryPrint()
{
	int x = 8, y = 5;
	int _frames = 0; //frame을 재는 변수
	char _command = 0; // 유저 커맨드를 받는 변수

	int _posOfChoice = 0;
	bool _startFlag = false;
	bool _Cursor = false;

	GoToXY(x + 15, y + 4);
	printf("              /＼_________/＼\n");
	GoToXY(x + 15, y + 5);
	printf("             ／｀         ＇｜  \n");
	GoToXY(x + 15, y + 6);
	printf("         =======  0    0   ======= \n");
	GoToXY(x + 15, y + 7);
	printf("              ＼    --      /\n");
	GoToXY(x + 15, y + 8);
	printf("               /            ＼\n");
	GoToXY(x + 15, y + 9);
	printf("              /              ｜\n");
	GoToXY(x + 15, y + 10);
	printf("             ｜   ｜｜ ｜｜  ｜\n");
	GoToXY(x + 15, y + 11);
	printf("              ＼  ｜｜ ｜｜  / \n");
	GoToXY(x + 15, y + 12);
	printf("               ＼_００_００_/#########０\n");



	GoToXY(x + 15, y + 14);
	printf("고양이는 매일 코딩하는 집사가 밉습니다.......\n");
	GoToXY(x + 13, y + 15);
	printf("이런 슬픔을 떨쳐내고자 새로운 집사를 찾으려고 합니다.\n");
	GoToXY(x + 14, y + 16);
	printf("여러분이 고양이가 새로운 집사를 찾게 도와주세요.\n");

	while (!_startFlag)
	{
		GoToXY(x + 35, y + 18);
		if (!_Cursor)
		{
			printf("▼");
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
