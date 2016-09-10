/**
 * \file Model3DManager.hpp
 * Contains the 3d models manager.
 */

#ifndef MODEL3D_MANAGER_HPP_
#define MODEL3D_MANAGER_HPP_

#include <map>
#include <string>

namespace gdl
{
  class Model;
  class AShader;
}

class AnimationData
{
public:
  int start;
  int end;
  int frames;
  float speed;
  bool loop;
};

class Model3DManager
{
public:
  enum ModelName
    {
      STEVE,
      STEVE_INTRO,
      MARVIN,
      MENU
    };

  enum AnimationName
    {
      STANDING,
      START_RUN,
      RUNNING,
      WALKING,
      STOP_RUN,
      PUNCHING,
      LOOKING
    };

public:
  static Model3DManager*	getInstance();
  static void			destroy();

  void				draw(ModelName model, gdl::AShader &shader,
				     const glm::mat4 &matrice, double deltaTime) const;

  gdl::Model*			create(ModelName model);

  bool				endAnimation(ModelName name, AnimationName animation, float time);
  void				createAnimations(gdl::Model* model, ModelName name);
  void				setAnimation(gdl::Model* model, ModelName name, AnimationName animation);
  float				getAnimationSpeed(ModelName name, AnimationName animation);

private:
  Model3DManager();
  Model3DManager(const Model3DManager&);
  virtual ~Model3DManager();
  Model3DManager&	operator=(const Model3DManager&);

  gdl::Model*			load(const std::string &filename) const;
  void				addAnimation(AnimationData& data, int start, int end,
					     float speed, bool loop);

  static Model3DManager* _instance;
  std::map< ModelName, std::string > _modelsName;
  std::map< ModelName, gdl::Model* > _models;
  std::map< AnimationName, std::string > _convert;
  std::map< ModelName, std::map< AnimationName, AnimationData > > _animations;
};

#endif /* !MODEL3D_MANAGER_HPP_ */
