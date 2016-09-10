/**
 * \file GeometricManager.hpp
 * Contains the geomatric manager.
 */

#ifndef GEOMETRIC_MANAGER_HPP_
#define GEOMETRIC_MANAGER_HPP_

#include <map>

namespace gdl
{
  class AShader;
}

class	AGeometric;

class	GeometricManager
{
public:
  enum Name
    {
      CUBE,
      TNT,
      PLANE
    };

public:
  static GeometricManager*	getInstance();
  static void			destroy();

  void				draw(Name model, gdl::AShader &shader, const glm::mat4 &matrice);
private:
  GeometricManager();
  GeometricManager(const GeometricManager&);
  virtual ~GeometricManager();
  GeometricManager&	operator=(const GeometricManager&);

  static GeometricManager*	_instance;
  std::map< Name, AGeometric* >	_models;
};

#endif
