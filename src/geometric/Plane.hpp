/**
 * \file Plane.hpp
 * Defines the Plane geometry.
 */

#ifndef PLANE_HPP_
#define PLANE_HPP_

#include "AGeometric.hpp"

class Plane : public AGeometric
{
private:
  int _width;
  int _height;

public:
  Plane(int x, int y);
  virtual ~Plane();

  int getWidth() const;
  int getHeight() const;
};

#endif
