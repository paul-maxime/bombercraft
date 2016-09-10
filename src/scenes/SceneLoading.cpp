#include "InputsManager.hpp"
#include "MatrixManager.hpp"

#include "AudioManager.hpp"
#include "TextureManager.hpp"
#include "Model3DManager.hpp"
#include "SceneLoading.hpp"
#include "GameEngine.hpp"
#include "SceneIntro.hpp"
#include "Text.hpp"
#include "Utils.hpp"

SceneLoading::SceneLoading(GameEngine* game)
  : AScene(game)
{
  m_text = "";
  m_end = false;
  m_background_ready = false;
}

SceneLoading::~SceneLoading()
{}

void		SceneLoading::loading(void)
{
  this->m_text = "Chargement de l'audio...";
  m_game->draw();
  AudioManager::getInstance()->playMusic(AudioManager::INTRO);
  this->m_text = "Chargement des textures...";
  m_game->draw();
  TextureManager::getInstance();
  m_background.init(TextureManager::LOADING_SCREEN);
  m_background_ready = true;
  this->m_text = "Chargement des models 3D...";
  m_game->draw();
  Model3DManager::getInstance();
  this->m_end = true;
}

void SceneLoading::update(gdl::Clock const&)
{
  if (m_end)
    {
      AScene* intro = new SceneIntro(m_game);
      intro->open();
      close();
    }
  else
    loading();
}

void SceneLoading::draw(gdl::AShader& shader, const gdl::Clock& clock)
{
  MatrixManager* matrix = MatrixManager::getInstance();
  matrix->apply(MatrixManager::MATRIX_2D, shader);
  if (m_background_ready)
    m_background.draw(shader, clock);
  if (m_text != "")
    {
      Text text(FontsManager::DEFAULT, m_text);
      text.draw(shader, clock);
    }
}
