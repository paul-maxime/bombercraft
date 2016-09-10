#include <Model.hh>
#include <Clock.hh>

#include "AnimatedModel.hpp"

AnimatedModel::AnimatedModel(Model3DManager::ModelName model)
  : _model(Model3DManager::getInstance()->create(model)),
    _modelName(model),
    _animation(Model3DManager::STANDING)
{
}

AnimatedModel::~AnimatedModel()
{
  if (_model)
    delete (_model);
}

void	AnimatedModel::setAnimation(Model3DManager::AnimationName name)
{
  _animation = name;
  Model3DManager::getInstance()->setAnimation(_model, _modelName, name);
}

void	AnimatedModel::draw(gdl::AShader& shader, const gdl::Clock& clock)
{
  _model->draw(shader, getTransformation(), clock.getElapsed() *
	       Model3DManager::getInstance()->getAnimationSpeed(_modelName, _animation));
}
