#include "TextureLoadError.hpp"

TextureLoadError::TextureLoadError(const std::string& name)
  : std::runtime_error("could not load texture " + name)
{
}

TextureLoadError::~TextureLoadError() throw()
{
}
