#include "InputsManager.hpp"
#include "MatrixManager.hpp"
#include "AudioManager.hpp"

#include "SceneChooseCmd.hpp"
#include "SceneGame.hpp"
#include "FormInputButton.hpp"
#include "FormInputJoystick.hpp"
#include "MapGenerator.hpp"
#include "Map.hpp"

SceneChooseCmd::SceneChooseCmd(GameEngine* game, SceneChooseMap::AsciiMapInfo* infos)
  : ASceneMenu(game, 0),
    _infos(infos)
{
  const std::vector<int> order = PlayersKeysManager::getInstance()->getOrder();
  for (int i = 0; i < m_game->getMapParams().nbPlayers; ++i)
    {
      std::stringstream ss;

      ss << "Manette du joueur " << (i + 1);
      m_buttons.push_back(new FormInputJoystick(game, 50, 20 + i * 70, 700, 60, ss.str(), order[i]));
    }

  FormInputButton* button = new FormInputButton(game, 100, 520, 600, 50, "Jouer !");
  button->setCallback(this, &SceneChooseCmd::onClick);
  m_buttons.push_back(button);

  _background.init(TextureManager::BACKGROUND, glm::vec2(game->getWidth(), game->getHeight()));
}

SceneChooseCmd::~SceneChooseCmd()
{
  if (_infos)
    delete (_infos);
}

void		SceneChooseCmd::update(gdl::Clock const &clock)
{
  ASceneMenu::update(clock);
}

void		SceneChooseCmd::draw(gdl::AShader &shader, gdl::Clock const &clock)
{
  _background.draw(shader, clock);
  ASceneMenu::draw(shader, clock);
}

void		SceneChooseCmd::onClick()
{
  PlayersKeysManager* keyManager = PlayersKeysManager::getInstance();

  for (int i = 0; i < m_game->getMapParams().nbPlayers; ++i)
    keyManager->setOrder(i, m_buttons[i]->getValue());
  close();

  GameEngine::MapParameters& params = m_game->getMapParams();
  Map* map = NULL;
  if (_infos)
    map = MapGenerator::generate(*_infos, params);
  AScene* game = new SceneGame(m_game, map);
  game->open();
}
