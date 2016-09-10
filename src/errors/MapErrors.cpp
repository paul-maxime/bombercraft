#include "MapErrors.hpp"

MapException::MapException(std::string const &msg)
  : std::runtime_error(msg)
{
}

MapException::~MapException() throw()
{
}
