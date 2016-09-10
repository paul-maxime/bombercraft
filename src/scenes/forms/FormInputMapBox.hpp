#ifndef FORMINPUT_MAPBOX_HPP_
#define FORMINPUT_MAPBOX_HPP_

#include <string>

#include "AFormInput.hpp"
#include "FormCallback.hpp"
#include "SceneChooseMap.hpp"
#include "Text.hpp"

namespace gdl
{
  class Texture;
}

class FormInputMapBox : public AFormInput
{
public:
  FormInputMapBox(GameEngine* game, const SceneChooseMap::AsciiMapInfo& infos);
  ~FormInputMapBox();

  template <class T>
  void	setCallback(T* instance, void (T::*fct)())
  {
    _callback = new FormCallback<T>(instance, fct);
  }

  virtual void	draw(gdl::AShader &shader, const gdl::Clock& clock);
  virtual void	update(const gdl::Clock&);

private:
  FormInputMapBox(const FormInputMapBox&);
  FormInputMapBox&	operator=(const FormInputMapBox&);

  void			createPreview(const SceneChooseMap::AsciiMapInfo& infos);

  const std::string	_tmp;

  glm::vec2		_size;
  glm::vec3		_position;
  AFormCallback*	_callback;
  Sprite		_icon;
  Sprite*		_preview;
  gdl::Texture*		_previewText;
  Text			_nbPlayers;
};

#endif
