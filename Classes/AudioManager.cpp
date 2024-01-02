
#include "AudioManager.h"
using namespace CocosDenshion;
USING_NS_CC;


bool isAudioEnabled = true;// 定义音效开关变量并初始化为开启状态

int globalAudioId = cocos2d::experimental::AudioEngine::INVALID_AUDIO_ID;  // 初始化为无效音频ID

void playSoundEffect(const std::string& audioFilePath) {
    // 播放音效
    int globalSoundEffectId = cocos2d::experimental::AudioEngine::play2d(audioFilePath, false);
}
