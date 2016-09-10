#include "InvalidFontError.hpp"

InvalidFontError::InvalidFontError(const std::string& name)
  : std::runtime_error("could not load font " + name)
{
}

InvalidFontError::~InvalidFontError() throw()
{
}
