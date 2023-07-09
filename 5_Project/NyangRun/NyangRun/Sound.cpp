#include<iostream>
#include "Sound.h"

using namespace std;
using namespace FMOD;
System* pSystem;
Sound* pSound[2];//����
Channel* pBgm;
Channel* pEffect;
//��׶���+ȿ���� ä��

//���� �ý��� �Լ�
void SoundSystem()
{
	System_Create(&pSystem);

	pSystem->init(4, FMOD_INIT_NORMAL, NULL);


	/*pSystem->createSound("pacman_beginning.wav", FMOD_LOOP_NORMAL | FMOD_DEFAULT, NULL, &pSound[0]);*/
	pSystem->createSound("..\\4_Resources\\Sound\\catsong.wav", FMOD_LOOP_NORMAL, NULL, &pSound[0]);
	pSystem->createSound("..\\4_Resources\\Sound\\Nyang1.mp3", FMOD_DEFAULT, NULL, &pSound[1]);
}

//���� �÷���
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