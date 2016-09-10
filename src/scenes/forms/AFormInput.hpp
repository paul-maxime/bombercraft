#ifndef AFORMINPUT_H_
#define AFORMINPUT_H_

#include <string>
#include "GameEngine.hpp"
#include "TextureManager.hpp"
#include "Sprite.hpp"

class AFormInput
{
public:
  AFormInput(GameEngine *game,
	     const int posX, const int posY,
	     const int sizeX, const int sizeY,
	     const TextureManager::TextureName defaultTexture,
	     const TextureManager::TextureName onFocusTexture,
	     bool full = false);
  virtual ~AFormInput();

  void		setFocus(bool isFocused);

  virtual void	update(gdl::Clock const &clock);
  virtual void	draw(gdl::AShader &shader, gdl::Clock const &clock);
  virtual int	getValue() const;

private:
  AFormInput(const AFormInput &);
  AFormInput &operator=(const AFormInput &);

protected:
  InputsManager*			m_inputs;
  GameEngine				*_game;
  Sprite				_sprite;
  int					_posX;
  int					_posY;
  int					_sizeX;
  int					_sizeY;
  const TextureManager::TextureName	_defaultTexture;
  const TextureManager::TextureName	_onFocusTexture;
  bool					_focused;
};

#endif
