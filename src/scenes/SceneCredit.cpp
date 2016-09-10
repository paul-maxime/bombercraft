#include "PlayersKeysManager.hpp"
#include "InputsManager.hpp"
#include "AudioManager.hpp"
#include "GameEngine.hpp"
#include "MatrixManager.hpp"
#include "SceneCredit.hpp"

SceneCredit::SceneCredit(GameEngine* game)
  : AScene(game)
{
  AudioManager::getInstance()->playMusic(AudioManager::CREDIT);
  _background.init(TextureManager::BACKGROUND, glm::vec2(game->getWidth(), game->getHeight()));
  _created_by.init(TextureManager::CREATED_BY);
  _created_by.setTranslation(glm::vec3(37.0f, 10.0f, 0.0f));
  _duval_h.init(TextureManager::DUVAL_H);
  _duval_h.setTranslation(glm::vec3(301.0f, 170.0f, 0.0f));
  _caudou_j.init(TextureManager::CAUDOU_J);
  _caudou_j.setTranslation(glm::vec3(287.0f, 238.0f, 0.0f));
  _drain_a.init(TextureManager::DRAIN_A);
  _drain_a.setTranslation(glm::vec3(309.0f, 306.0f, 0.0f));
  _leduc_p.init(TextureManager::LEDUC_P);
  _leduc_p.setTranslation(glm::vec3(301.0f, 374.0f, 0.0f));
  _morphe_h.init(TextureManager::MORPHE_H);
  _morphe_h.setTranslation(glm::vec3(284.0f, 442.0f, 0.0f));
}

SceneCredit::~SceneCredit()
{
  AudioManager::getInstance()->playMusic(AudioManager::MENU);
}

void SceneCredit::update(gdl::Clock const &)
{
  if (m_inputs->keyIsPressed(PlayersKeysManager::getInstance()->getActionsKeys(PlayersKeysManager::ESCAPE)))
    {
      AudioManager::getInstance()->playSound(AudioManager::CLICK);
      close();
    }
}

void SceneCredit::draw(gdl::AShader &shader, gdl::Clock const &clock)
{
  MatrixManager* matrix = MatrixManager::getInstance();
  matrix->apply(MatrixManager::MATRIX_2D, shader);

  _background.draw(shader, clock);
  _created_by.draw(shader, clock);
  _duval_h.draw(shader, clock);
  _caudou_j.draw(shader, clock);
  _drain_a.draw(shader, clock);
  _leduc_p.draw(shader, clock);
  _morphe_h.draw(shader, clock);
}
