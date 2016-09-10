#ifndef INVALID_FILE_ERROR_HPP_
#define INVALID_FILE_ERROR_HPP_

#include <stdexcept>
#include <string>

class InvalidFileError : public std::runtime_error
{
public:
  InvalidFileError(const std::string& error);
  virtual ~InvalidFileError() throw();
};

#endif
