#include "AGeometric.hpp"
#include "Cube.hpp"
#include "Tnt.hpp"
#include "GeometricManager.hpp"

GeometricManager*	GeometricManager::_instance = NULL;

GeometricManager::GeometricManager()
{
  _models[CUBE] = new Cube(1);
  _models[TNT] = new Tnt(1);
}

GeometricManager::~GeometricManager()
{
  for (std::map< GeometricManager::Name, AGeometric* >::iterator it = _models.begin();
       it != _models.end();
       ++it)
    delete (it->second);
}

GeometricManager*	GeometricManager::getInstance()
{
  if (!_instance)
    _instance = new GeometricManager();
  return (_instance);
}

void	GeometricManager::destroy()
{
  if (_instance)
    {
      delete (_instance);
      _instance = NULL;
    }
}

void	GeometricManager::draw(GeometricManager::Name model, gdl::AShader &shader, const glm::mat4 &matrice)
{
  std::map< GeometricManager::Name, AGeometric* >::iterator it;

  if ((it = _models.find(model)) != _models.end())
    it->second->draw(shader, matrice);
}
