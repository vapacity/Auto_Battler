#ifndef __AUDIO_MANAGER_H__
#define __AUDIO_MANAGER_H__

#include "cocos2d.h"
#include "AudioEngine.h"

#include "StartScene.h"
extern bool isAudioEnabled;//记录是否选择音效

extern int globalAudioId;  // 声明全局音频ID变量 

void playSoundEffect(const std::string& audioFilePath);
#endif // __AUDIO_MANAGER_H__