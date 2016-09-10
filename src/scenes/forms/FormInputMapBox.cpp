#include <Texture.hh>

#include "Screenshot.hpp"
#include "FormInputMapBox.hpp"
#include "InputsManager.hpp"
#include "TextureManager.hpp"
#include "FontsManager.hpp"
#include "PlayersKeysManager.hpp"
#include "GameEngine.hpp"
#include "File.hpp"
#include "Utils.hpp"

FormInputMapBox::FormInputMapBox(GameEngine* game, const SceneChooseMap::AsciiMapInfo& infos)
  : AFormInput(game, 0, 0, game->getWidth(), game->getHeight(),
	       TextureManager::MENU_INPUT,
	       TextureManager::MENU_INPUT_FOCUSED),
    _tmp("tmpPreview"),
    _callback(0),
    _preview(0),
    _previewText(0)
{
  float	mult = infos.width > infos.height ? game->getWidth() / 1.5 / infos.width :
    game->getHeight() / 1.5 / infos.height;

  _size.x = infos.width * mult;
  _size.y = infos.height * mult;
  _position.x = (game->getWidth() - _size.x) / 2;
  _position.y = (game->getHeight() - _size.y) / 2;
  _position.z = 0;

  _icon.init(TextureManager::BOMB);
  _icon.resize(_size);
  _icon.translate(_position);
  createPreview(infos);
  _nbPlayers.init(FontsManager::DEFAULT, "Nombre de joueurs : " +
		  Utils::toString<int>(infos.spawns.size()));
  _nbPlayers.translate(glm::vec3((game->getWidth() - _nbPlayers.getWidth()) / 2,
				 game->getHeight() - 50, 0));
}

FormInputMapBox::~FormInputMapBox()
{
  if (_callback)
    delete _callback;
  if (_preview)
    delete _preview;
  if (_previewText)
    delete _previewText;
}

void FormInputMapBox::createPreview(const SceneChooseMap::AsciiMapInfo& infos)
{
  Screenshot	shot;

  shot.asciiMapToTGA(_tmp, infos.content, infos.width, infos.height,
		     _size.x, _size.y);
  _previewText = new gdl::Texture;
  if (!_previewText->load(_tmp + ".tga"))
    {
      delete _previewText;
      _previewText = NULL;
    }
  else
    {
      _preview = new Sprite(TextureManager::DEFAULT,
			    glm::vec2(_previewText->getWidth(), _previewText->getHeight()),
			    glm::vec4(0, 0, 1, 1));
      _preview->resize(_size, glm::vec2(_previewText->getWidth(), _previewText->getHeight()));
      _preview->translate(_position);
    }
  if (File::fileExist(_tmp + ".tga"))
    File::removeFile(_tmp + ".tga");
}

void FormInputMapBox::update(gdl::Clock const &)
{
  if (_focused && (m_inputs->keyIsPressed(SDLK_RETURN) ||
		   m_inputs->keyIsPressed(PlayersKeysManager::getInstance()->getActionsKeys(PlayersKeysManager::ACTION))))
    {
      if (_callback) (*_callback)();
    }
}

void FormInputMapBox::draw(gdl::AShader &shader, gdl::Clock const &clock)
{
  if (_focused)
    {
      if (_preview)
	{
	  _previewText->bind();
	  _preview->drawCustom(shader, clock);
	}
      else
	_icon.draw(shader, clock);
      _nbPlayers.draw(shader, clock);
    }
}
