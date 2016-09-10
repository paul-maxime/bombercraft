#include "AssetNotFoundError.hpp"

AssetNotFoundError::AssetNotFoundError()
  : std::runtime_error("tried to use an unknown asset")
{
}

AssetNotFoundError::~AssetNotFoundError() throw()
{
}
