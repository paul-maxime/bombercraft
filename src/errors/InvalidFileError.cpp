#include "InvalidFileError.hpp"

InvalidFileError::InvalidFileError(const std::string& error)
  : std::runtime_error("Error while writing in file: " + error)
{
}

InvalidFileError::~InvalidFileError() throw()
{
}
