#ifndef FORMINPUT_H_
#define FORMINPUT_H_

#include <string>
#include "Text.hpp"
#include "AFormInput.hpp"
#include "TextureManager.hpp"
#include "FormCallback.hpp"

class FormInputButton : public AFormInput
{
public:
  FormInputButton(GameEngine* game, const int posX, const int posY,
		  const int sizeX, const int sizeY, const std::string &value);

  template <class T>
  void		setCallback(T* instance, void (T::*fct)())
  {
    _callback = new FormCallback<T>(instance, fct);
  }

  virtual ~FormInputButton();
  virtual void	draw(gdl::AShader &shader, gdl::Clock const &clock);
  virtual void	update(gdl::Clock const &);

private:
  void		placeText();

private:
  FormInputButton(const FormInputButton &);
  FormInputButton &operator=(const FormInputButton &);

protected:
  std::string		_value;
  Text			_text;
  int			_heigthPadding;
  AFormCallback*	_callback;
};

#endif
