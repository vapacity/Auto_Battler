/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/
#include "HelloWorldScene.h"
#include "AudioManager.h"
using namespace CocosDenshion;
USING_NS_CC;

float g_slider_position = 50.0f;
bool lastCheckBoxState = true;
bool isAudioEnabled = true;// 定义音效开关变量并初始化为开启状态
void AudioManager::playBackgroundMusic()
{
    auto bgMusic = SimpleAudioEngine::getInstance();
    bgMusic->playBackgroundMusic("bgmusic.mp3", true);
}

void AudioManager::stopBackgroundMusic()
{
    auto bgMusic = SimpleAudioEngine::getInstance();
    bgMusic->stopBackgroundMusic();
}
void AudioManager::preloadBackgroundMusic()
{
    auto bgMusic = SimpleAudioEngine::getInstance();
    bgMusic->preloadBackgroundMusic("bgMusic.mp3");
}
void AudioManager::setBackgroundMusicVolume(float volume)
{
    auto bgMusic = SimpleAudioEngine::getInstance();
    bgMusic->setBackgroundMusicVolume(volume);
}
void AudioManager::pauseBackgroundMusic()
{
    auto bgMusic = SimpleAudioEngine::getInstance();
    bgMusic->pauseBackgroundMusic();
}
void AudioManager::resumeBackgroundMusic()
{
    auto bgMusic = SimpleAudioEngine::getInstance();
    bgMusic->resumeBackgroundMusic();
}



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

void AudioManager::setEffectsVolume(float volume)
{
    auto audio = SimpleAudioEngine::getInstance();
    audio->setEffectsVolume(volume);
}