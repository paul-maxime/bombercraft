/**
 * \file File.hpp
 * Defines the File static class.
 */

#ifndef FILE_HPP_
#define FILE_HPP_

#include <string>
#include <vector>

/**
 * \class File
 * A basic wrapper for various file-system operations.
 * This class contains only static functions and cannot be instancied.
 */
class File
{
public:
  /**
   * Checks whether the specified file exists and,
   * eventually, if it is a directory.
   * \param file Name of the file to check.
   * \param isDir Is the specified file a directory?
   * \return true if the file exists.
   */
  static bool	fileExist(const std::string& file, bool isDir = false);

  /**
   * Creates the specified directory.
   * \param name Directory's name.
   */
  static void	createDirectory(const std::string& name);

  /**
   * Deletes the specified file.
   * \param path File's path.
   */
  static void	removeFile(const std::string& path);

  /**
   * Get all files in a directory with
   * the specified extension
   * \param folder The folder where to get the files
   * \param ext The searched extension
   * \param files The vector where the results are stored
   */
  static void	getAllFiles(const std::string& folder, const std::string& ext,
			    std::vector<std::string>& files);

private:
  File();
};

#endif
