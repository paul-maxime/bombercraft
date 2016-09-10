/**
 * \file Tnt.hpp
 * Defines the Tnt geometry.
 */

#ifndef TNT_HPP_
#define TNT_HPP_

#include "AGeometric.hpp"

class Tnt : public AGeometric
{
private:
  float _size;

public:
  Tnt(float size);
  virtual ~Tnt();

  float getSize() const;
};

#endif
