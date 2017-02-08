///////////////////////////////////////////////////////////////////////////////////////
//		Amr播放器头文件 AmrPlayer.h
///////////////////////////////////////////////////////////////////////////////////////
#ifndef _AMR_PLAYER_HEAD_FILE_
#define _AMR_PLAYER_HEAD_FILE_
#pragma once
struct __declspec(dllexport) IAmrPlayer
{
	virtual ~IAmrPlayer() {}
	//播放
	virtual void Play(LPCTSTR lpszFile, DWORD* pLength) = NULL;//lpszFile: 文件完整路径 pLength: 输出播放时间
	//暂停
	virtual void Pause() = NULL;								
	//继续
	virtual void Resume() = NULL;			
	//停止
	virtual void Stop() = NULL;									
	//播放时间
	virtual DWORD GetAudioLength(LPCTSTR lpszFile) = NULL;		//获取文件的播放时间
	//音量
	virtual void SetVolume(DWORD dwVolume) = NULL;				//Volume :0-1000
};
IAmrPlayer *CreateAmrPlayer();
void ReleaseAmrPlayer(IAmrPlayer * player);
#endif


/////////////////////////////////////////////////////////////////////////////////
//								AMR文件格式									   //
/////////////////////////////////////////////////////////////////////////////////

//AMR文件可以大致的分为两个部分：
//1、文件头
//2、语音帧
//具体如下：
//				----------------------------------------------
//              |	文件头	|  语音帧1  |  	语音帧2  |	...	 |
//				----------------------------------------------
//						   		  |	 
//								  |
//								  V
//				 -----------------------------------
//               | 帧头1byte | 辅助信息 | 音频数据 |    ------> AMR IF1
//				 -----------------------------------
//								  |				    \
//								  |					 \
//								  V                   \
//				 -----------------------------------   --------------------------------
//				 | 模式指示 | 模式需求 | 编码CRC   |   | Class A | Class B | Class C  |
//				 |   3bits	|  3bits   |   8bits   |   |							  |
//				 -----------------------------------   --------------------------------
//
//				 -----------------------------------
//               | 帧头1byte | 音频数据 | Bit位补充|    ------> AMR IF2
//				 -----------------------------------
//								   |
//                                 |
//				    ---------------------------------
//				    | Class A | Class B |  Class C  |
//				    ---------------------------------        