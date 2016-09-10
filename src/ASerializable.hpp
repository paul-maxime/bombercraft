/**
 * \file ASerializable.hpp
 * Contains the ASerializable class.
 */

#ifndef A_SERIALIZABLE_HPP_
#define A_SERIALIZABLE_HPP_

#include <iostream>

#include "InvalidFileError.hpp"
#include "CorruptedFileError.hpp"

/**
 * \class ASerializable.
 * Represents something that can be serialized into a stream.
 * Provides useful functions usable when inherited.
 */
class ASerializable
{
public:
  /**
   * Empty constructor.
   */
  ASerializable() {};

  /**
   * Virtual destructor.
   */
  virtual ~ASerializable() {};

  /**
   * Serializes the current object into the specified stream.
   * \param out Output stream.
   */
  virtual void	serialize(std::ostream& out) const = 0;

  /**
   * Unserialize the current object from the specified stream.
   * \param in Input stream.
   */
  virtual void	unserialize(std::istream& in) = 0;

protected:
  /**
   * Writes the specified data to the stream as bytes.
   * \param data Data to write.
   * \param out Output stream.
   */
  template<typename T>
  void	writeInFile(const T& data, std::ostream& out) const
  {
    if (!out.write(reinterpret_cast<const char*>(&data), sizeof data))
      throw InvalidFileError("Write error");
  };

  /**
   * Reads the specified data from the stream.
   * \param data Data to read.
   * \param in Input stream.
   */
  template<typename T>
  void	readFromFile(T& data, std::istream& in) const
  {
    if (!in.read(reinterpret_cast<char*>(&data), sizeof data))
      throw CorruptedFileError("Read error");
  };

  /**
   * Writes the specified vec3 to the stream as bytes.
   * \param vector Vector to write.
   * \param out Output stream.
   */
  void	serializeVec3(const glm::vec3& vector, std::ostream& out) const
  {
    writeInFile<float>(vector.x, out);
    writeInFile<float>(vector.y, out);
    writeInFile<float>(vector.z, out);
  };

  /**
   * Reads the specified vec3 from the stream.
   * \param vector Vector to read.
   * \param in Input stream.
   */
  void	unserializeVec3(glm::vec3& vector, std::istream& in) const
  {
    readFromFile<float>(vector.x, in);
    readFromFile<float>(vector.y, in);
    readFromFile<float>(vector.z, in);
  };

  /**
   * Writes the specified vec4 to the stream as bytes.
   * \param vector Vector to write.
   * \param out Output stream.
   */
  void	serializeVec4(const glm::vec4& vector, std::ostream& out) const
  {
    writeInFile<float>(vector.x, out);
    writeInFile<float>(vector.y, out);
    writeInFile<float>(vector.z, out);
    writeInFile<float>(vector.w, out);
  };

  /**
   * Reads the specified vec4 from the stream.
   * \param vector Vector to read.
   * \param in Input stream.
   */
  void	unserializeVec4(glm::vec4& vector, std::istream& in) const
  {
    readFromFile<float>(vector.x, in);
    readFromFile<float>(vector.y, in);
    readFromFile<float>(vector.z, in);
    readFromFile<float>(vector.w, in);
  };
};

#endif
