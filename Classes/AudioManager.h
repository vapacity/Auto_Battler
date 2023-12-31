#ifndef __AUDIO_MANAGER_H__
#define __AUDIO_MANAGER_H__

#include "cocos2d.h"
#include "AudioEngine.h"
#include "SimpleAudioEngine.h"

#include "StartScene.h"
extern bool isAudioEnabled;//记录是否选择音效

extern int globalAudioId;  // 声明全局音频ID变量 

class AudioManager
{
public:

    //音效
    static void preloadEffect();//预加载
    static void playEffect();//播放一次音效
    static void stopAllEffects();//停止全部音效
    static void pauseAllEffects();//暂停
    static void resumeAllEffects();//继续

};

#endif // __AUDIO_MANAGER_H__