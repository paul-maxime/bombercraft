#include <AShader.hh>
#include <SDL_opengl.h>
#include <glm/gtc/matrix_transform.hpp>

#include "MatrixManager.hpp"

MatrixManager* MatrixManager::m_instance = NULL;

MatrixManager* MatrixManager::getInstance()
{
  if (!m_instance)
    m_instance = new MatrixManager();
  return (m_instance);
}

void MatrixManager::destroy()
{
  if (m_instance)
    {
      delete (m_instance);
      m_instance = NULL;
    }
}

void MatrixManager::perspective(float fov, float width, float height)
{
  m_perspective = glm::perspective(fov, width / height, 0.1f, 100.0f);
}

void MatrixManager::ortho(float width, float height)
{
  m_ortho = glm::ortho(0.0f, width, height, 0.0f, -1.0f, 1.0f);
}

void MatrixManager::lookAt(glm::vec3 loc, glm::vec3 at)
{
  m_view = glm::lookAt(loc, at, glm::vec3(0, 1, 0));
}

void MatrixManager::apply(Matrix matrix, gdl::AShader& shader) const
{
  if (matrix == MATRIX_3D)
    {
      glEnable(GL_DEPTH_TEST);
      shader.setUniform("view", m_view);
      shader.setUniform("projection", m_perspective);
    }
  else
    {
      glDisable(GL_DEPTH_TEST);
      shader.setUniform("view", glm::mat4(1));
      shader.setUniform("projection", m_ortho);
    }
  shader.setUniform("color", glm::vec4(1, 1, 1, 1));
}

MatrixManager::MatrixManager()
  : m_perspective(glm::mat4(1)),
    m_ortho(glm::mat4(1)),
    m_view(glm::mat4(1))
{
}

MatrixManager::~MatrixManager()
{
}
