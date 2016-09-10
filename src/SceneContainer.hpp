/**
 * \file SceneContainer.hpp
 * Contains the SceneContainer class.
 */

#ifndef SCENE_CONTAINER_HPP_
#define SCENE_CONTAINER_HPP_

#include <list>
#include "IDrawable.hpp"

class AScene;

/**
 * \class SceneContainer
 * Contains a stack of the opened scenes.
 */
class SceneContainer : public IDrawable
{
public:
  /**
   * Public constructor.
   */
  SceneContainer();

  /**
   * Virtual destructor.
   */
  virtual ~SceneContainer();

  /**
   * @return true if there is no scene in this container, false otherwise.
   */
  bool isEmpty();

  /**
   * Updates the scenes stack and the scenes themselves.
   * Checks for the opened scenes and destroys the closed ones.
   * Inherited from IDrawable.
   * \param clock Main clock, used to retrieve the elapsed time.
   */
  virtual void update(gdl::Clock const &clock);

  /**
   * Draws every scenes on the screen, starting from the oldest one.
   * Inherited from IDrawable.
   * \param shader The shader which should be used to draw the scenes.
   * \param clock Main clock, used to retrieve the elapsed time.
   */
  virtual void draw(gdl::AShader &shader, gdl::Clock const &clock);

  /**
   * Adds a new scene into the stack.
   * @param scene The already created scene to add.
   */
  void push(AScene* scene);

private:
  SceneContainer(const SceneContainer&);
  SceneContainer& operator=(const SceneContainer&);

  std::list<AScene*> m_scenes;
};

#endif
