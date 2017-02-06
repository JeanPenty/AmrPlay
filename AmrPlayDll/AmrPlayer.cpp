// AmrPlayer.cpp : 定义 DLL 应用程序的导出函数。
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