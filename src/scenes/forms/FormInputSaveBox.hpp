#ifndef FORMINPUT_SAVEBOX_HPP_
#define FORMINPUT_SAVEBOX_HPP_

#include <string>

#include "AFormInput.hpp"
#include "FormCallback.hpp"

namespace gdl
{
  class Texture;
}

class FormInputSaveBox : public AFormInput
{
public:
  FormInputSaveBox(GameEngine* game, int posX, int posY, int sizeX, int sizeY, bool empty, const std::string& img);
  virtual ~FormInputSaveBox();

  template <class T>
  void		setCallback(T* instance, void (T::*fct)())
  {
    _callback = new FormCallback<T>(instance, fct);
  }

  void		setEmpty(bool empty);
  void		loadPreview();

  virtual void	draw(gdl::AShader &shader, const gdl::Clock& clock);
  virtual void	update(const gdl::Clock&);

private:
  FormInputSaveBox(const FormInputSaveBox&);
  FormInputSaveBox&	operator=(const FormInputSaveBox&);

  const std::string	_img;
  Sprite		_icon;
  const unsigned int	_border;
  bool			_empty;
  AFormCallback*	_callback;
  Sprite*		_preview;
  gdl::Texture*		_previewText;
  glm::vec2		_size;
  glm::vec3		_position;
};

#endif
