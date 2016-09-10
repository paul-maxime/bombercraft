#include "ModelLoadError.hpp"

ModelLoadError::ModelLoadError(const std::string& name)
  : std::runtime_error("could not load model " + name)
{
}

ModelLoadError::~ModelLoadError() throw()
{
}
