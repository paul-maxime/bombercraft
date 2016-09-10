/**
 * \file TextureLoadError.hpp
 * Contains the TextureLoadError class.
 */

#ifndef TEXTURE_LOAD_ERROR_HPP_
#define TEXTURE_LOAD_ERROR_HPP_

#include <stdexcept>
#include <string>

/**
 * Exception thrown when a texture failed to load.
 */
class TextureLoadError : public std::runtime_error
{
public:
  /**
   * Contructs a new TextureLoadError instance.
   * \param name Texture's name.
   */
  TextureLoadError(const std::string& name);

  /**
   * Frees the error.
   */
  virtual ~TextureLoadError() throw();
};

#endif
