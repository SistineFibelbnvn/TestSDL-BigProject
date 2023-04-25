#include "SoundManager.h"
SoundManager* SoundManager::s_Instance=nullptr;
SoundManager::SoundManager()
{
    Mix_OpenAudio(FREQ,MIX_DEFAULT_FORMAT,2,CHUNK_SIZE);
}

void SoundManager::PlayMusic(std::string id)
{
    Mix_PlayMusic(m_MusicMap[id],-1);
}

void SoundManager::PauseMusic()
{
    if( Mix_PausedMusic()==1)
        Mix_ResumeMusic();
    else
        Mix_PauseMusic();
}

void SoundManager::LoadMusic(std::string id, std::string source)
{
    Mix_Music* music =Mix_LoadMUS(source.c_str());
    if(music!=nullptr)
        m_MusicMap[id]=music;
}

void SoundManager::PlayEffect(std::string id)
{
    Mix_PlayChannel(-1,m_EffectMap[id],0);
}

void SoundManager::LoadEffect(std::string id, std::string source)
{
    Mix_Chunk* effect =Mix_LoadWAV(source.c_str());
    if(effect!=nullptr)
        m_EffectMap[id]=effect;
}
void SoundManager::Clean()
{
    for(MusicMap::iterator it=m_MusicMap.begin();it!=m_MusicMap.end();it++)
        Mix_FreeMusic(it->second);
    for(EffectMap::iterator it=m_EffectMap.begin();it!=m_EffectMap.end();it++)
        Mix_FreeChunk(it->second);
    m_MusicMap.clear();
    m_EffectMap.clear();
}

