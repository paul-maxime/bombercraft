/**
 * \file InvalidFontError.hpp
 * Contains the InvalidFontError class.
 */

#ifndef INVALID_FONT_ERROR_HPP_
#define INVALID_FONT_ERROR_HPP_

#include <stdexcept>
#include <string>

/**
 * Exception thrown when we failed to load a font.
 */
class InvalidFontError : public std::runtime_error
{
public:
  /**
   * Contructs a new InvalidFontError instance.
   * \param name Font's name.
   */
  InvalidFontError(const std::string& name);

  /**
   * Frees the error.
   */
  virtual ~InvalidFontError() throw();
};

#endif
