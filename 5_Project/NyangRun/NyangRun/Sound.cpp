#include<iostream>
#include "Sound.h"

using namespace std;
using namespace FMOD;
System* pSystem;
Sound* pSound[2];//갯수
Channel* pBgm;
Channel* pEffect;
//백그라운드+효과음 채널

//사운드 시스템 함수
void SoundSystem()
{
	System_Create(&pSystem);

	pSystem->init(4, FMOD_INIT_NORMAL, NULL);


	/*pSystem->createSound("pacman_beginning.wav", FMOD_LOOP_NORMAL | FMOD_DEFAULT, NULL, &pSound[0]);*/
	pSystem->createSound("..\\4_Resources\\Sound\\catsong.wav", FMOD_LOOP_NORMAL, NULL, &pSound[0]);
	pSystem->createSound("..\\4_Resources\\Sound\\Nyang1.mp3", FMOD_DEFAULT, NULL, &pSound[1]);
}

//사운드 플레이
void PlayBgm()
{
	pSystem->playSound(pSound[0], NULL, 0, &pBgm);
}
void PlayEffect()
{
	pSystem->update();
	pSystem->playSound(pSound[1], NULL, 0, &pEffect);
}

void Exit()
{
	pSystem->release();
	pSystem->close();
}