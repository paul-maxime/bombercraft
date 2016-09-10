/**
 * \file AssetNotFoundError.hpp
 * Contains the AssetNotFoundError class.
 */

#ifndef INVALID_FONT_ERROR_HPP_
#define INVALID_FONT_ERROR_HPP_

#include <stdexcept>
#include <string>

/**
 * \class AssetNotFoundError.
 * Exception thrown when we tried to access/draw a non-existant asset.
 */
class AssetNotFoundError : public std::runtime_error
{
public:
  /*
   * Contructs a new AssetNotFoundError instance.
   */
  AssetNotFoundError();

  /*
   * Frees the error.
   */
  virtual ~AssetNotFoundError() throw();
};

#endif
