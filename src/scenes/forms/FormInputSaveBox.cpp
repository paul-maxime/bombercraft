#include <iostream>
#include <Texture.hh>

#include "FormInputSaveBox.hpp"
#include "InputsManager.hpp"
#include "TextureManager.hpp"
#include "GameEngine.hpp"

FormInputSaveBox::FormInputSaveBox(GameEngine* game, int posX, int posY,
				   int sizeX, int sizeY, bool empty, const std::string& img)
  : AFormInput(game, posX, posY, sizeX, sizeY,
	       TextureManager::SAVEBOX,
	       TextureManager::SAVEBOX_FOCUSED),
    _img(img),
    _border(4),
    _empty(empty),
    _callback(NULL),
    _preview(NULL),
    _previewText(NULL),
    _size(sizeX - _border * 2, sizeY - _border * 2),
    _position(posX + _border, posY + _border, 0)
{
  _icon.init(TextureManager::BOMB);
  _icon.resize(_size);
  _icon.translate(_position);
  loadPreview();
}

FormInputSaveBox::~FormInputSaveBox()
{
  if (_callback)
    delete _callback;
  if (_preview)
    delete _preview;
  if (_previewText)
    delete _previewText;
}

void	FormInputSaveBox::setEmpty(bool empty)
{
  _empty = empty;
}

void	FormInputSaveBox::loadPreview()
{
  if (_preview)
    {
      delete _preview;
      _preview = NULL;
    }
  if (_previewText)
    delete _previewText;
  _previewText = new gdl::Texture;
  if (!_previewText->load(_img))
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
}

void	FormInputSaveBox::draw(gdl::AShader& shader, const gdl::Clock& clock)
{
  _sprite.draw(shader, clock);
  if (!_empty)
    {
      if (_preview)
	{
	  _previewText->bind();
	  _preview->drawCustom(shader, clock);
	}
      else
	_icon.draw(shader, clock);
    }
}

void	FormInputSaveBox::update(const gdl::Clock&)
{
  if (_focused && (m_inputs->keyIsPressed(SDLK_RETURN) ||
		   m_inputs->keyIsPressed(PlayersKeysManager::getInstance()->getActionsKeys(PlayersKeysManager::ACTION))))
    {
      if (_callback)
	(*_callback)();
    }
}
