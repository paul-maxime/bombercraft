/**
 * \file AObject.hpp
 * Contains the Object abstract class.
 */

#ifndef A_OBJECT_HPP_
#define A_OBJECT_HPP_

#include <glm/glm.hpp>
#include "IDrawable.hpp"
#include "ASerializable.hpp"

/**
 * \class AObject
 * A 3d game object, with a transformation containing the
 *   position, the rotation and the scale.
 * Inherits from IDrawable.
 */
class AObject : public IDrawable, public ASerializable
{
public:
  /**
   * Creates a new object with the default translation, rotation and scale.
   */
  AObject();

  /**
   * Destroys the current object.
   */
  virtual ~AObject();

  /**
   * May be overloaded. Updates the internal object state.
   * Inherited from IDrawable.
   * \param clock Main clock, used to retrieve the elapsed time.
   */
  virtual void		update(gdl::Clock const &clock);

  /**
   * Shall be overloaded. Draws the object on the screen.
   * \param shader The shader which should be used to draw the element.
   * \param clock Main clock, used to retrieve the elapsed time.
   */
  virtual void		draw(gdl::AShader &shader, gdl::Clock const &clock) = 0;

  /**
   * Resets the object translation, rotation and scale.
   */
  void			reset();

  /**
   * Sets the internal translation vector.
   * \param v The translation vector.
   */
  void			setTranslation(glm::vec3 const &v);

  /**
   * Sets the internal rotation vector.
   * \param v The rotation vector.
   */
  void			setRotation(glm::vec3 const &v);

  /**
   * Sets the internal scale vector.
   * \param v The scaling vector.
   */
  void			setScale(glm::vec3 const &v);

  /**
   * Sets the object center. Used for the rotation.
   * \param v Center location.
   */
  void			setCenter(glm::vec3 const &v);

  /**
   * Translates the object by the specified coordinates.
   * \param v The translation vector.
   */
  void			translate(glm::vec3 const &v);

  /**
   * Translates the object by the specified axis and angle.
   * \param v The rotation axis vector.
   * \param angle The angle (in degrees).
   */
  void			rotate(glm::vec3 const& axis, float angle);

  /**
   * Scales the object by the specified scale.
   * \param scale The scaling vector.
   */
  void			scale(glm::vec3 const& scale);

  /**
   * Add the specified scale to the object.
   * \param scale The scaling vector.
   */
  void			addScale(glm::vec3 const& scale);

  /**
   * Computes the position, the rotation and the scale into a single matrix.
   * \return a new matrix representing the whole transformation.
   */
  glm::mat4		getTransformation() const;

  /**
   * Return the position of the object.
   * \return A constant reference to the position.
   */
  const glm::vec3&	getPosition() const;

  /**
   * Serialize the variables of the classe.
   * \param out The stream to output the result.
   */
  virtual void			serialize(std::ostream& out) const;

  /**
   * Unserialize the variables of the classe from the in stream.
   * \param in The stream where the variables are stored.
   */
  virtual void			unserialize(std::istream& in);

protected:
  glm::vec3		_position;
  glm::vec3		_rotation;
  glm::vec3		_scale;
  glm::vec3		_center;
};

#endif
