#ifndef __AUDIO_MANAGER_H__
#define __AUDIO_MANAGER_H__

#include "cocos2d.h"
#include "AudioEngine.h"
#include "SimpleAudioEngine.h"

#include "StartScene.h"
extern bool isAudioEnabled;//��¼�Ƿ�ѡ����Ч

extern int globalAudioId;  // ����ȫ����ƵID���� 

class AudioManager
{
public:

    //��Ч
    static void preloadEffect();//Ԥ����
    static void playEffect();//����һ����Ч
    static void stopAllEffects();//ֹͣȫ����Ч
    static void pauseAllEffects();//��ͣ
    static void resumeAllEffects();//����

};

#endif // __AUDIO_MANAGER_H__