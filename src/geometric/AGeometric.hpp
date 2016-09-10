/**
 * \file AGeometric.hpp
 * Defines the geometric abstract class.
 */

#ifndef A_GEOMETRIC_HPP_
#define A_GEOMETRIC_HPP_

#include <Geometry.hh>

class AGeometric
{
protected:
  gdl::Geometry _geometry;

public:
  AGeometric();
  virtual ~AGeometric();

  void draw(gdl::AShader &shader, const glm::mat4 &matrix);
};

#endif
