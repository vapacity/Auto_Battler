#ifndef __AUDIO_MANAGER_H__
#define __AUDIO_MANAGER_H__

#include "cocos2d.h"
#include "AudioEngine.h"

#include "StartScene.h"
extern bool isAudioEnabled;//��¼�Ƿ�ѡ����Ч

extern int globalAudioId;  // ����ȫ����ƵID���� 

void playSoundEffect(const std::string& audioFilePath);
#endif // __AUDIO_MANAGER_H__