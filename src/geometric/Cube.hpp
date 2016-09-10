/**
 * \file Cube.hpp
 * Defines the Cube geometry.
 */

#ifndef CUBE_HPP_
#define CUBE_HPP_

#include "AGeometric.hpp"

class Cube : public AGeometric
{
private:
  float _size;

public:
  Cube(float size);
  virtual ~Cube();

  float getSize() const;
};

#endif
