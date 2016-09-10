#include "CorruptedFileError.hpp"

CorruptedFileError::CorruptedFileError(const std::string& error)
  : std::runtime_error("Failed to load the level: " + error)
{
}

CorruptedFileError::~CorruptedFileError() throw()
{
}
