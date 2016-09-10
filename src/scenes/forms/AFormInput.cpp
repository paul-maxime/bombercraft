#include "InputsManager.hpp"
#include "AFormInput.hpp"

AFormInput::AFormInput(GameEngine *game,
		       const int posX, const int posY,
		       const int sizeX, const int sizeY,
		       const TextureManager::TextureName defaultTexture,
		       const TextureManager::TextureName onFocusTexture,
		       bool full)
  : m_inputs(InputsManager::getInstance()),
    _game(game),
    _posX(posX),
    _posY(posY),
    _sizeX(sizeX),
    _sizeY(sizeY),
    _defaultTexture(defaultTexture),
    _onFocusTexture(onFocusTexture),
    _focused(false)
{
  if (full)
    {
      _sprite.init(defaultTexture);
      _sprite.resize(glm::vec2(sizeX, sizeY));
    }
  else
    _sprite.init(defaultTexture, glm::vec2(sizeX, sizeY));
  _sprite.translate(glm::vec3(posX, posY, 0.0f));
}

AFormInput::~AFormInput()
{

}

void		AFormInput::setFocus(bool isFocused)
{
  if (isFocused)
    _sprite.setTexture(_onFocusTexture);
  else
    _sprite.setTexture(_defaultTexture);
  _focused = isFocused;
}

void	AFormInput::update(gdl::Clock const &)
{
}

void	AFormInput::draw(gdl::AShader &shader, gdl::Clock const &clock)
{
  _sprite.draw(shader, clock);
}

int	AFormInput::getValue() const
{
  return (0);
}
