// AmrPlayer.cpp : ���� DLL Ӧ�ó���ĵ���������
//

#include "stdafx.h"
#include "WavePlayer.h"
IAmrPlayer *CreateAmrPlayer()
{
	return new WavePlayer();
}
void ReleaseAmrPlayer(IAmrPlayer * player)
{
	delete player;
}