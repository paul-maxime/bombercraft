#include <stdexcept>
#include "InputsManager.hpp"
#include "GameEngine.hpp"
#include "SceneContainer.hpp"
#include "AScene.hpp"

AScene::AScene(GameEngine* game)
  : m_game(game),
    m_inputs(InputsManager::getInstance()),
    m_isBackground(false),
    m_opened(false),
    m_closing(false)
{}

AScene::~AScene() {}

void AScene::open()
{
  if (m_opened)
    throw std::runtime_error("tried to open an already-opened scene");
  m_opened = true;
  m_game->getScenes().push(this);
}

bool AScene::isClosed() const
{
  return m_closing;
}

void AScene::close()
{
  m_closing = true;
}

bool AScene::isBackground() const
{
  return m_isBackground;
}
