
#include "AudioManager.h"
using namespace CocosDenshion;
USING_NS_CC;


bool isAudioEnabled = true;// ������Ч���ر�������ʼ��Ϊ����״̬

int globalAudioId = cocos2d::experimental::AudioEngine::INVALID_AUDIO_ID;  // ��ʼ��Ϊ��Ч��ƵID

void playSoundEffect(const std::string& audioFilePath) {
    // ������Ч
    int globalSoundEffectId = cocos2d::experimental::AudioEngine::play2d(audioFilePath, false);
}
