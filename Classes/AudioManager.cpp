
#include "AudioManager.h"
using namespace CocosDenshion;
USING_NS_CC;


bool isAudioEnabled = true;// ������Ч���ر�������ʼ��Ϊ����״̬

int globalAudioId = cocos2d::experimental::AudioEngine::INVALID_AUDIO_ID;  // ��ʼ��Ϊ��Ч��ƵID


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
