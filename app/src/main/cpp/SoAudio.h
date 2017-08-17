//--------------------------------------------------------------------------------------------------
#ifndef _SoAudio_h_
#define _SoAudio_h_
//--------------------------------------------------------------------------------------------------
//初始化音频组件。
bool SoAudioCreate();
//释放音频组件。
//函数内部会妥善处理各种异常情况，包括正处于播放中的资源。
void SoAudioRelease();
//开始播放一个资源。
//--szResourceName 资源名
//--fVolume 音量，取值范围[0.0, 1.0]
//--bLoop 是否循环播放
//--bEndEvent 是否侦听播放结束的事件，只有在非循环播放的情况下有效。
//返回值为AudioID。
int  SoAudioPlay(const char* szResourceName, float fVolume, bool bLoop, bool bEndEvent);
void SoAudioStop(int nAudioId);
void SoAudioPause(int nAudioId);
void SoAudioResume(int nAudioId);
//设置音量
//--fVolume 音量，取值范围[0.0, 1.0]
void SoAudioVolume(int nAudioId, float fVolume);
//预先加载一个资源，这是为了保证播放的时候不会有延迟。
bool SoAudioPreloadResource(const char* szResourceName);
//移除一个资源。
//函数内部会妥善处理各种异常情况，包括正处于播放中的资源。
//如果该资源正在播放，会立即停止播放。
void SoAudioRemoveResource(const char* szResourceName);
//执行一次垃圾回收。
void SoAudioGC();
//--------------------------------------------------------------------------------------------------
#endif //_SoAudio_h_
//--------------------------------------------------------------------------------------------------
