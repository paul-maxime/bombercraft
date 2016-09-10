#include <Model.hh>
#include "Model3DManager.hpp"
#include "ModelLoadError.hpp"

Model3DManager*	Model3DManager::_instance = NULL;

Model3DManager*	Model3DManager::getInstance()
{
  if (!_instance)
    _instance = new Model3DManager();
  return (_instance);
}

void Model3DManager::destroy()
{
  if (_instance)
    {
      delete (_instance);
      _instance = NULL;
    }
}

void Model3DManager::draw(ModelName model, gdl::AShader &shader,
			  const glm::mat4 &matrice, double deltaTime) const
{
  std::map< ModelName, gdl::Model* >::const_iterator it;

  if ((it = _models.find(model)) != _models.end())
    {
      it->second->draw(shader, matrice, deltaTime);
    }
}

gdl::Model* Model3DManager::create(ModelName model)
{
  std::map< ModelName, std::string >::const_iterator it;
  gdl::Model* loaded;

  if ((it = _modelsName.find(model)) != _modelsName.end())
    {
      loaded = load(it->second);
      createAnimations(loaded, model);
      setAnimation(loaded, model, STANDING);
      return loaded;
    }
  return NULL;
}

void Model3DManager::addAnimation(AnimationData& data, int start, int end,
				  float speed, bool loop = false)
{
  data.start = start;
  data.end = end;
  data.frames = end - start;
  data.speed = speed;
  data.loop = loop;
}

bool Model3DManager::endAnimation(ModelName name, AnimationName animation, float time)
{
  return (time * _animations[name][animation].speed > _animations[name][animation].frames * _models[name]->getFrameDuration());
}

void Model3DManager::createAnimations(gdl::Model* model, ModelName name)
{
  for (std::map< AnimationName, AnimationData >::iterator it = _animations[name].begin();
       it != _animations[name].end();
       ++it)
    model->createSubAnim(0, _convert[it->first], it->second.start, it->second.end);
}

void Model3DManager::setAnimation(gdl::Model* model, ModelName name, AnimationName animation)
{
  model->setCurrentSubAnim(_convert[animation], _animations[name][animation].loop);
}

float Model3DManager::getAnimationSpeed(ModelName name, AnimationName animation)
{
  return (_animations[name][animation].speed);
}

Model3DManager::Model3DManager()
{
  _convert[STANDING] = "STANDING";
  _convert[START_RUN] = "START_RUN";
  _convert[RUNNING] = "RUNNIG";
  _convert[WALKING] = "WALKING";
  _convert[STOP_RUN] = "STOP_RUN";
  _convert[PUNCHING] = "PUNCHING";
  _convert[LOOKING] = "LOOKING";

  _modelsName[STEVE] = "steve.fbx";
  _modelsName[STEVE_INTRO] = "steve_intro.fbx";
  _modelsName[MARVIN] = "marvin.fbx";
  _modelsName[MENU] = "menu.fbx";

  addAnimation(_animations[STEVE][STANDING], 0, 0, 0);
  addAnimation(_animations[STEVE][START_RUN], 0, 5, 1);
  addAnimation(_animations[STEVE][RUNNING], 5, 25, 1, true);
  addAnimation(_animations[STEVE][STOP_RUN], 25, 30, 1);

  addAnimation(_animations[STEVE_INTRO][STANDING], 0, 0, 0);
  addAnimation(_animations[STEVE_INTRO][START_RUN], 0, 5, 1);
  addAnimation(_animations[STEVE_INTRO][RUNNING], 5, 25, 1, true);
  addAnimation(_animations[STEVE_INTRO][STOP_RUN], 25, 30, 1);
  addAnimation(_animations[STEVE_INTRO][PUNCHING], 30, 40, 1);
  addAnimation(_animations[STEVE_INTRO][LOOKING], 40, 60, 0.4);

  addAnimation(_animations[MARVIN][STANDING], 0, 0, 0);
  addAnimation(_animations[MARVIN][START_RUN], 10, 30, 2);
  addAnimation(_animations[MARVIN][RUNNING], 35, 52, 1, true);
  addAnimation(_animations[MARVIN][WALKING], 35, 52, 0.7, true);
  addAnimation(_animations[MARVIN][STOP_RUN], 58, 120, 2);

  for (std::map< ModelName, std::string >::iterator it = _modelsName.begin();
       it != _modelsName.end();
       ++it)
    {
      _models[it->first] = load(it->second);
      createAnimations(_models[it->first], it->first);
    }
}

Model3DManager::~Model3DManager()
{
  for (std::map< ModelName, gdl::Model* >::iterator it = _models.begin();
       it != _models.end();
       ++it)
    delete (it->second);
}

gdl::Model* Model3DManager::load(const std::string &filename) const
{
  const std::string root = "./data/models/";

  gdl::Model* model = new gdl::Model;
  if (model->load(root + filename) == false)
    throw ModelLoadError(filename);
  return model;
}
