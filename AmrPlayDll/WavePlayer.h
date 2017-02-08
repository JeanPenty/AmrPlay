#pragma once
#include "WaveDef.h"
#include <vector>
//#include <atlmisc.h>
#include "AmrPlayer.h"

class AMRFileDecoder;
class __declspec(dllexport) WavePlayer: public IAmrPlayer
{
    /// messages
    typedef unsigned int            WaveMsg;     // wave messages
    typedef unsigned int            ThreadMsg;   // thread messages

	/*
	@	����״̬��
	@	1��ֹͣ
	@	2����ͣ
	@	3������
	*/
    enum PlayState
    {
        Play_Stop = 0,
        Play_Pause,
        Play_Playing,
    };

public:
    WavePlayer(void);
    virtual ~WavePlayer(void);

public:
    // ����
    virtual void Play(LPCTSTR lpszFile, DWORD* pLength);
    // ��ͣ
    virtual void Pause();
    // ����
    virtual void Resume();
    // ֹͣ
    virtual void Stop();
    // ����ʱ��
    virtual DWORD GetAudioLength(LPCTSTR lpszFile);
    // ����
    virtual void SetVolume(DWORD dwVolume); // volume: 0-1000

protected:
    static BOOL CALLBACK WaveOutProc(HWAVEOUT hwo, UINT uMsg, DWORD dwInstance, DWORD dwParam1, DWORD dwParam2);
    BOOL   WaveOutProcImpl(HWAVEOUT hwo, UINT uMsg, DWORD dwParam1, DWORD dwParam2);

    static unsigned int CALLBACK PlayThread( LPVOID lp );                // main play thread
    unsigned int PlayThreadProcImpl();

    static unsigned int CALLBACK DecodeThread(LPVOID lp);
    unsigned int DecodeThreadProcImpl();

    /// prototypes
    WAVEHDR*    allocBlocks( int size, int count );          /// alloc heap for wave header blocks
    void        freeBlocks( WAVEHDR* blockArray );           /// free heap

    void        UnInit();
    void        OnPlayFinished();

private: /// members
    /// thread
    HANDLE                 m_hThreadPlay;
    HANDLE                 m_hThreadDecode;

    PlayState              m_ePlayStat;                        /// ����״̬

    /// Event
    HANDLE                 m_hEventDecode;                     /// event for decoding

    /// device
    HWAVEOUT               m_hWaveoutDev;

    WaveBlock              m_wBlock;
    WaveData               m_waveData;

    ThreadMsg              m_msgPlayThread;                    // thread msg { 1,0 } alive / close
    ThreadMsg              m_msgDecodeThread;

    AMRFileDecoder*        m_pDecoder;

    CRITICAL_SECTION       m_cs;                                       // critical section
};
