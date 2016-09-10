#include <Model.hh>

#include "PlayersKeysManager.hpp"
#include "InputsManager.hpp"
#include "MatrixManager.hpp"
#include "Model3DManager.hpp"

#include "SceneIntro.hpp"
#include "GameEngine.hpp"
#include "SceneMenu.hpp"

SceneIntro::SceneIntro(GameEngine* game)
  : AScene(game),
    m_skipKeys(PlayersKeysManager::getInstance()->getActionsKeys(PlayersKeysManager::ACTION)),
    m_current(0),
    m_showMarvin(true),
    m_steve(Model3DManager::STEVE_INTRO),
    m_marvin(Model3DManager::MARVIN)
{
  m_scenes.push_back(&SceneIntro::scene1);
  m_scenes.push_back(&SceneIntro::scene2);
  m_scenes.push_back(&SceneIntro::scene3);
  m_scenes.push_back(&SceneIntro::scene4);
  m_scenes.push_back(&SceneIntro::scene5);

  m_background.init(TextureManager::INTRO_BACKGROUND, glm::vec2(game->getWidth(), game->getHeight()));
  m_title.init(TextureManager::TITLE);
  m_title.setTranslation(glm::vec3(61, -100, 0));

  m_marvin.setScale(glm::vec3(0.008, 0.008, 0.008));
  m_marvin.setTranslation(glm::vec3(0, -5, 11));
  m_marvin.rotate(glm::vec3(0, 1, 0), 180);
  m_marvin.setAnimation(Model3DManager::WALKING);
  m_steve.setScale(glm::vec3(0.2, 0.2, 0.2));
  m_steve.setTranslation(glm::vec3(0, -5, -11));
  m_steve.setAnimation(Model3DManager::RUNNING);
}

SceneIntro::~SceneIntro()
{
}

void SceneIntro::scene1(const gdl::Clock& clock)
{
  if (m_marvin.getPosition().z > 4)
    {
      m_marvin.translate(glm::vec3(0, 0, -clock.getElapsed() * 1.5));
    }
  else
    {
      m_marvin.setAnimation(Model3DManager::STANDING);
      ++m_current;
    }
}

void SceneIntro::scene2(const gdl::Clock& clock)
{
  if (m_steve.getPosition().z < 2.3)
    {
      m_steve.translate(glm::vec3(0, 0, clock.getElapsed() * 10));
    }
  else
    {
      m_steve.setAnimation(Model3DManager::PUNCHING);
      ++m_current;
    }
}

void SceneIntro::scene3(const gdl::Clock& clock)
{
  if (m_marvin.getPosition().y < 20)
    {
      m_marvin.translate(glm::vec3(0, clock.getElapsed() * 70, 0));
    }
  else
    {
      m_steve.rotate(glm::vec3(0, 1, 0), 45);
      m_steve.setAnimation(Model3DManager::LOOKING);
      m_marvin.rotate(glm::vec3(1, 0, 0), 180);
      m_marvin.setScale(glm::vec3(0.001, 0.001, 0.001));
      m_marvin.setTranslation(glm::vec3(5, 8, 8));
      ++m_current;
    }
}

void SceneIntro::scene4(const gdl::Clock& clock)
{
  if (m_marvin.getPosition().y > 4.5)
    {
      float elapsed = clock.getElapsed();
      m_marvin.translate(glm::vec3(0, -elapsed * 2, 0));
      m_marvin.addScale(glm::vec3(-elapsed * 0.0005, -elapsed * 0.0005, -elapsed * 0.0005));
    }
  else
    {
      m_showMarvin = false;
      m_steve.rotate(glm::vec3(0, 1, 0), -45);
      m_steve.setAnimation(Model3DManager::RUNNING);
      ++m_current;
    }
}

void SceneIntro::scene5(const gdl::Clock& clock)
{
  if (m_title.getPosition().y < 25)
    {
      m_title.translate(glm::vec3(0, clock.getElapsed() * 100, 0));
      m_steve.translate(glm::vec3(0, 0, clock.getElapsed() * 10));
    }
  else
    {
      ++m_current;
    }
}

void SceneIntro::update(gdl::Clock const& clock)
{
  (this->*m_scenes[m_current])(clock);
  if (m_inputs->keyIsPressed(m_skipKeys) ||
      m_current >= m_scenes.size())
    {
      AScene* menu = new SceneMenu(m_game);
      menu->open();
      close();
    }
}

void SceneIntro::draw(gdl::AShader& shader, const gdl::Clock& clock)
{
  MatrixManager* matrix = MatrixManager::getInstance();
  matrix->apply(MatrixManager::MATRIX_2D, shader);

  m_background.draw(shader, clock);
  m_title.draw(shader, clock);

  matrix->lookAt(glm::vec3(-10, 2, 0),
		 glm::vec3(0, 0, 0));
  matrix->apply(MatrixManager::MATRIX_3D, shader);

  m_steve.draw(shader, clock);
  if (m_showMarvin)
    m_marvin.draw(shader, clock);
}
