#include <Windows.h>
#include <stdio.h>
#include <mmsystem.h> // 사운드 파일 출력을 위한 헤더
#include "Playbuffer.h"
extern void SoundSystem();
extern void PlayBgm();
extern void Exit();
#pragma comment(lib,"winmm.lib")


int main()
{
	SoundSystem();
	PlayBgm();

	TilteText();


	Exit();
	return 0;
}