
#include "AudioManager.h"
using namespace CocosDenshion;
USING_NS_CC;


bool isAudioEnabled = true;// 定义音效开关变量并初始化为开启状态

int globalAudioId = cocos2d::experimental::AudioEngine::INVALID_AUDIO_ID;  // 初始化为无效音频ID


void AudioManager::preloadEffect()
{
    auto audio = SimpleAudioEngine::getInstance();
    audio->preloadEffect("myEffect.mp3");
}

void AudioManager::playEffect()
{
    auto audio = SimpleAudioEngine::getInstance();
    audio->playEffect("myEffect.mp3", false, 1.0f, 1.0f, 1.0f);
}

void AudioManager::stopAllEffects()
{
    auto audio = SimpleAudioEngine::getInstance();
    audio->stopAllEffects();
}

void AudioManager::pauseAllEffects()
{
    auto audio = SimpleAudioEngine::getInstance();
    audio->pauseAllEffects();
}

void AudioManager::resumeAllEffects()
{
    auto audio = SimpleAudioEngine::getInstance();
    audio->resumeAllEffects();
}
