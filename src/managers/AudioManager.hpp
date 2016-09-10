/**
 * \file AudioManager.hpp
 * Contains the audios manager.
 */

#ifndef AUDIO_MANAGER_HPP_
# define AUDIO_MANAGER_HPP_

# include <string>
# include <map>
# include <fstream>

# include "fmod.hpp"

/**
 * \class AudioManager
 * This singleton is used to manage sound and fx
 */
class AudioManager
{
public:
  /**
   * List of availables sound.
   */
  enum SoundTrack
    {
      EXPLOSION = 0,
      DAMAGE,
      BONUS,
      PUSH,
      CLICK,
      SOUND_MAX
    };

  /**
   * List of availables music.
   */
  enum MusicTrack
    {
      INTRO = 0,
      CREDIT,
      GAME,
      MENU
    };

  /**
   * \return the audio manager instance. Creates it if it doesn't exist.
   */
  static AudioManager*	getInstance();

  /**
   * Frees the memory used by the audio manager.
   */
  static void		destroy();

  /**
   * Play a music
   */
  void			playMusic(MusicTrack track);

  /**
   * Play a sound
   */
  void			playSound(SoundTrack track);

  /**
   * Getters
   */
  int			getMasterVolume() const;
  int			getMusicVolume() const;
  int			getSfxVolume() const;

  /**
   * Setter
   */
  void			saveOptions(int, int, int);

private:
  AudioManager();
  AudioManager(const AudioManager&);
  virtual ~AudioManager();
  AudioManager&	operator=(const AudioManager&);

  void manageOptions();
  void refreshVolume();
  FMOD_SOUND* load(const std::string &filename, bool music) const;

  static AudioManager*			m_instance;
  FMOD_SYSTEM*				m_fmod_system;
  std::map<MusicTrack, std::string>	m_musicsName;
  std::map<MusicTrack, FMOD_SOUND*>	m_musics;
  std::map<SoundTrack, std::string>	m_soundsName;
  std::map<SoundTrack, FMOD_SOUND*>	m_sounds;
  int					m_masterVolume;
  int					m_musicVolume;
  int					m_sfxVolume;
};

#endif
