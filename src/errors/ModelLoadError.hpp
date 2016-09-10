/**
 * \file ModelLoadError.hpp
 * Contains the ModelLoadError class.
 */

#ifndef MODEL_LOAD_ERROR_HPP_
#define MODEL_LOAD_ERROR_HPP_

#include <stdexcept>
#include <string>

/**
 * \class ModelLoadError
 * Exception thrown when a model failed to load.
 */
class ModelLoadError : public std::runtime_error
{
public:
  /**
   * Contructs a new ModelLoadError instance.
   * \param name Model's name.
   */
  ModelLoadError(const std::string& name);

  /**
   * Frees the error.
   */
  virtual ~ModelLoadError() throw();
};

#endif
