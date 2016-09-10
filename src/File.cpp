#include <cctype>
#include <cstdio>
#include <sys/stat.h>
#include <dirent.h>
#include <stdexcept>

#include "File.hpp"

bool	File::fileExist(const std::string& file, bool isDir)
{
  struct stat buff;

  if (stat(file.c_str(), &buff) != 0)
    return (false);
  if (isDir)
    return (S_ISDIR(buff.st_mode));
  return (S_ISREG(buff.st_mode));
}

void	File::createDirectory(const std::string& name)
{
  if (File::fileExist(name, true))
    return ;
  if (mkdir(name.c_str(), 0777) == -1)
    throw std::runtime_error("Unable to create the " + name + " directory.");
}

void	File::removeFile(const std::string& path)
{
  if (remove(path.c_str()) == -1)
    throw std::runtime_error("Unable to remove " + path);
}

void		File::getAllFiles(const std::string& folder, const std::string& ext,
			  std::vector<std::string>& files)
{
  DIR		*dir;
  struct dirent	*ent;

  if ((dir = opendir(folder.c_str())))
    {
      while ((ent = readdir(dir)))
	{
	  std::string	file(ent->d_name);
	
	  if (file.size() >= ext.size() &&
	      file.substr(file.size() - ext.size()) == ext)
	    files.push_back(file);
	}
    }
}
