#include "AGeometric.hpp"

AGeometric::AGeometric()
{
}

AGeometric::~AGeometric()
{
}

void	AGeometric::draw(gdl::AShader &shader, const glm::mat4 &matrice)
{
  _geometry.draw(shader, matrice, GL_QUADS);
}
