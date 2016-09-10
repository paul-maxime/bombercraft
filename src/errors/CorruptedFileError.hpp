#ifndef CORRUPTED_FILE_ERROR_HPP_
#define CORRUPTED_FILE_ERROR_HPP_

#include <stdexcept>
#include <string>

class CorruptedFileError : public std::runtime_error
{
public:
  CorruptedFileError(const std::string& error);
  virtual ~CorruptedFileError() throw();
};

#endif
