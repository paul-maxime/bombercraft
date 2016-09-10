#include <iostream>
#include <fstream>
#include <istream>
#include <ostream>

#include "CorruptedFileError.hpp"
#include "InvalidFileError.hpp"
#include "SaveManager.hpp"
#include "Map.hpp"

SaveManager*	SaveManager::_instance = NULL;

SaveManager::SaveManager()
  : _magic(0x424D4F42)
{
}

SaveManager::~SaveManager()
{
}

SaveManager*	SaveManager::getInstance()
{
  if (!_instance)
    _instance = new SaveManager();
  return (_instance);
}

void	SaveManager::destroy()
{
  if (_instance)
    {
      delete (_instance);
      _instance = NULL;
    }
}

void	SaveManager::save(const std::string& file, const Map& map) const
{
  std::ofstream	out(file.c_str(), std::ios::trunc | std::ios::binary | std::ios::out);

  if (!out.is_open())
    throw InvalidFileError("Could not open file");
  if (!out.write(reinterpret_cast<const char*>(&_magic), sizeof _magic))
    throw InvalidFileError("Write error");
  map.serialize(out);
  out.close();
}

Map*	SaveManager::load(const std::string& file) const
{
  std::ifstream in(file.c_str(), std::ios::in | std::ios::binary);
  Map* map = new Map();
  int magic;

  if (!in.is_open())
    throw InvalidFileError("Could not open file");
  if (!in.read(reinterpret_cast<char*>(&magic), sizeof magic) || magic != _magic)
    throw CorruptedFileError("Wrong magic number");
  map->unserialize(in);
  in.close();
  return (map);
}
