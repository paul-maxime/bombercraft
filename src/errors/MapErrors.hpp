#ifndef MAP_ERRORS_HPP_
#define MAP_ERRORS_HPP_

#include <stdexcept>

class MapException : public std::runtime_error
{
public:
  MapException(std::string const &msg);
  virtual ~MapException() throw();
};

#endif
