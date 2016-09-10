#ifndef ANIMATED_MODEL_HPP_
#define ANIMATED_MODEL_HPP_

#include "AObject.hpp"
#include "Model3DManager.hpp"

namespace gdl
{
  class Model;
};

class AnimatedModel : public AObject
{
public:
  AnimatedModel(Model3DManager::ModelName);
  virtual ~AnimatedModel();

  void	setAnimation(Model3DManager::AnimationName name);

  /**
   * Shall be overloaded. Draws the object on the screen.
   * \param shader The shader which should be used to draw the element.
   * \param clock Main clock, used to retrieve the elapsed time.
   */
  virtual void		draw(gdl::AShader& shader, const gdl::Clock& clock);

private:
  AnimatedModel(const AnimatedModel&);
  AnimatedModel&	operator=(const AnimatedModel&);

  gdl::Model*			_model;
  Model3DManager::ModelName	_modelName;
  Model3DManager::AnimationName	_animation;
};

#endif
