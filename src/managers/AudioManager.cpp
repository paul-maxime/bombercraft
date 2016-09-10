#include <iostream>

#include "AudioManager.hpp"
#include "Utils.hpp"

AudioManager* AudioManager::m_instance = NULL;

AudioManager* AudioManager::getInstance()
{
  if (!m_instance)
    m_instance = new AudioManager();
  return (m_instance);
}

void AudioManager::destroy()
{
  if (m_instance)
    {
      delete (m_instance);
      m_instance = NULL;
    }
}

AudioManager::AudioManager()
{
  FMOD_System_Create(&m_fmod_system);
  FMOD_System_Init(m_fmod_system, SOUND_MAX + 1, FMOD_INIT_NORMAL, NULL);
  manageOptions();

  m_soundsName[EXPLOSION] = "explosion.wav";
  m_soundsName[DAMAGE] = "damage.wav";
  m_soundsName[BONUS] = "bonus.wav";
  m_soundsName[PUSH] = "push.wav";
  m_soundsName[CLICK] = "click.wav";


  for (std::map<SoundTrack, std::string>::iterator it = m_soundsName.begin();
       it != m_soundsName.end();
       ++it)
    m_sounds[it->first] = load(it->second, false);

  m_musicsName[INTRO] = "intro.mp3";
  m_musicsName[CREDIT] = "credit.mp3";
  m_musicsName[GAME] = "game.mp3";
  m_musicsName[MENU] = "menu.mp3";

  for (std::map<MusicTrack, std::string>::iterator it = m_musicsName.begin();
       it != m_musicsName.end();
       ++it)
    m_musics[it->first] = load(it->second, true);
}

void		AudioManager::refreshVolume()
{
  FMOD_CHANNELGROUP *channelMaster;
  FMOD_CHANNEL *channel;

  FMOD_System_GetMasterChannelGroup(m_fmod_system, &channelMaster);
  FMOD_ChannelGroup_SetVolume(channelMaster, m_masterVolume / 10.0);
  for (int i = 0; i <= SOUND_MAX; ++i)
    {
      if (i < SOUND_MAX)
	{
	  FMOD_System_GetChannel(m_fmod_system, i, &channel);
          FMOD_Channel_SetVolume(channel, m_sfxVolume / 10.0);
	}
      else
	{
	  FMOD_System_GetChannel(m_fmod_system, i, &channel);
          FMOD_Channel_SetVolume(channel, m_musicVolume / 10.0);
	}
    }
}

void		AudioManager::saveOptions(int masterVolume, int musicVolume, int sfxVolume)
{
  m_masterVolume = masterVolume;
  m_musicVolume = musicVolume;
  m_sfxVolume = sfxVolume;
  std::ofstream newFile("./soundOptions.txt");
  if (newFile.is_open())
    newFile << masterVolume << "\n" << musicVolume << "\n" << sfxVolume;
  newFile.close();
  refreshVolume();
}

void		AudioManager::manageOptions()
{
  std::ifstream file("./soundOptions.txt");

  m_masterVolume = 5;
  m_musicVolume = 5;
  m_sfxVolume = 5;
  if (!file.is_open())
    saveOptions(5, 5, 5);
  else
    {
      std::string line;

      if (getline(file, line) &&
	  ((m_masterVolume = Utils::toInt(line)) > 10 || m_masterVolume < 0))
	m_masterVolume = 5;
      if (getline(file, line) &&
	  ((m_musicVolume = Utils::toInt(line)) > 10 || m_musicVolume < 0))
	m_musicVolume = 5;
      if (getline(file, line) &&
	  ((m_sfxVolume = Utils::toInt(line)) > 10 || m_sfxVolume < 0))
	m_sfxVolume = 5;
      refreshVolume();
    }
}

FMOD_SOUND*	AudioManager::load(const std::string &filename, bool music) const
{
  const std::string root = "./data/music/";
  std::string tmp_string = root + filename;
  FMOD_RESULT result;
  FMOD_SOUND* track = NULL;
  int flags;

  flags = FMOD_CREATESAMPLE;
  if (music)
    flags = FMOD_SOFTWARE | FMOD_2D | FMOD_CREATESTREAM | FMOD_LOOP_NORMAL;
  std::cout << "Loading track " << tmp_string << "... ";
  result = FMOD_System_CreateSound(m_fmod_system, tmp_string.c_str(), flags, NULL, &track);
  if (result != FMOD_OK)
    std::cout << "[\033[31;1mFAIL\033[0m]" << std::endl;
  else
    std::cout << "[\033[32;1mOK\033[0m]" << std::endl;
  if (music)
    FMOD_Sound_SetLoopCount(track, -1);

  return track;
}

void	AudioManager::playMusic(MusicTrack track)
{
  std::map<MusicTrack, FMOD_SOUND*>::iterator it;
  FMOD_CHANNEL *channel;

  FMOD_System_GetChannel(m_fmod_system, SOUND_MAX, &channel);
  if ((it = m_musics.find(track)) != m_musics.end())
    {
      FMOD_System_PlaySound(m_fmod_system, FMOD_CHANNEL_REUSE, it->second, 0, &channel);
      FMOD_System_Update(m_fmod_system);
    }
  refreshVolume();
}

void	AudioManager::playSound(SoundTrack track)
{
  std::map<SoundTrack, FMOD_SOUND*>::iterator it;
  FMOD_CHANNEL *channel;

  FMOD_System_GetChannel(m_fmod_system, track, &channel);
  if ((it = m_sounds.find(track)) != m_sounds.end())
    {
      FMOD_System_PlaySound(m_fmod_system, FMOD_CHANNEL_REUSE, it->second, 0, &channel);
      FMOD_System_Update(m_fmod_system);
    }
  refreshVolume();
}

int	AudioManager::getMasterVolume() const
{
  return (m_masterVolume);
}

int	AudioManager::getMusicVolume() const
{
  return (m_musicVolume);
}

int	AudioManager::getSfxVolume() const
{
  return (m_sfxVolume);
}

AudioManager::~AudioManager()
{
  for (std::map<MusicTrack, FMOD_SOUND*>::iterator it = m_musics.begin();
       it != m_musics.end();
       ++it)
    {
      if (it->second)
	FMOD_Sound_Release(it->second);
    }
  for (std::map<SoundTrack, FMOD_SOUND*>::iterator it = m_sounds.begin();
       it != m_sounds.end();
       ++it)
    {
      if (it->second)
	FMOD_Sound_Release(it->second);
    }
  FMOD_System_Close(m_fmod_system);
  FMOD_System_Release(m_fmod_system);
}
