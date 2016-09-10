/**
 * \file MatrixManager.hpp
 * Contains the matrix manager.
 */

#ifndef MATRIX_MANAGER_HPP_
#define MATRIX_MANAGER_HPP_

#include <glm/glm.hpp>

namespace gdl
{
  class AShader;
}

class MatrixManager
{
public:
  /**
   * List of the stored matrixes.
   */
  enum Matrix
    {
      MATRIX_2D,
      MATRIX_3D
    };

  /**
   * \return the matrix manager instance. Creates it if it doesn't exist.
   */
  static MatrixManager*		getInstance();

  /**
   * Frees the memory used by the matrix manager.
   */
  static void			destroy();

  /**
   * Initializes the 3d perspective matrix using the specified parameters.
   * \param fovy Field of view angle.
   * \param width Window width.
   * \param height Window height.
   */
  void				perspective(float fov, float width, float height);

  /**
   * Initializes the 2d orthogonal matrix using the specified parameters.
   * \param width Window width.
   * \param height Window height.
   */
  void				ortho(float width, float height);

  /**
   * Initializes the 3d view matrix using the specified parameters.
   * \param loc Camera's location.
   * \param at Camera's target point.
   */
  void				lookAt(glm::vec3 loc, glm::vec3 at);

  /**
   * Applies the specified matrix to the shader.
   * \param matrix 2d or 3d.
   * \param shader Shader to update.
   */
  void				apply(Matrix matrix, gdl::AShader& shader) const;

private:
  MatrixManager();
  virtual ~MatrixManager();

  MatrixManager&		operator=(const MatrixManager&);

  static MatrixManager*		m_instance;
  glm::mat4			m_perspective;
  glm::mat4			m_ortho;
  glm::mat4			m_view;
};

#endif
