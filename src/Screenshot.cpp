#include <GL/gl.h>
#include <iostream>
#include <istream>
#include <fstream>
#include <cstring>

#include "Screenshot.hpp"
#include "InvalidFileError.hpp"
#include "CharToEntityConverter.hpp"

Screenshot::Screenshot()
  : _w(0), _h(0), _data(NULL)
{
  std::memset(_tgaHeader, 0, sizeof(_tgaHeader));
  _tgaHeader[2] = 2;
  _tgaHeader[16] = 24;
}

Screenshot::~Screenshot()
{
  if (_data)
    delete[] _data;
}

void	Screenshot::saveScreenBuffer(unsigned int w, unsigned int h)
{
  _w = w;
  _h = h;
  if (_data)
    delete[] _data;
  _data = new unsigned char[w * h * 3];

  glReadPixels(0, 0, w, h, GL_BGR, GL_UNSIGNED_BYTE, _data);
}

void	Screenshot::screenshotTGA(const std::string& name, unsigned int w, unsigned int h)
{
  unsigned char	*data = new unsigned char[w * h * 3];

  glReadPixels(0, 0, w, h, GL_BGR, GL_UNSIGNED_BYTE, data);
  writeTGAData(name + ".tga", w, h, data);
  delete[] data;
}

void	Screenshot::saveBufferTGA(const std::string& name)
{
  if (_data)
    writeTGAData(name + ".tga", _w, _h, _data);
}

void	Screenshot::asciiMapToTGA(const std::string& name, const std::string& map,
				  unsigned int w, unsigned int h,
				  unsigned int fw, unsigned int fh)
{
  if (map.size() != w * h)
    return ;

  std::string reverseMap;
  for (unsigned int l = 0; l < h; ++l)
    reverseMap.append(map.substr((h - l - 1) * w, w));

  glm::vec3 color;
  CharToEntityConverter	converter;
  unsigned int	i = 0, mult = w > h ? fw / w : fh / h;
  unsigned char	*data;

  mult = mult == 0 ? 1 : mult;
  w *= mult;
  h *= mult;
  data = new unsigned char[w * h * 3];

  for (std::string::const_iterator it = reverseMap.begin(); it != reverseMap.end(); ++it)
    {
      converter.convertEntityCharToColor((*it), color);
      for (unsigned int j = 0; j < mult; ++j)
	{
	  data[i++] = color.x;
	  data[i++] = color.y;
	  data[i++] = color.z;
	  for (unsigned int k = 1; k < mult; ++k)
	    {
	      unsigned int pos = i - 3 + w * 3 * k;
	      data[pos] = color.x;
	      data[pos + 1] = color.y;
	      data[pos + 2] = color.z;
	    }
	}
      if (i % (w * 3) == 0)
	i += w * 3 * (mult - 1);
    }
  writeTGAData(name + ".tga", w, h, data);
  delete[] data;
}

void	Screenshot::writeTGAData(const std::string& file, unsigned int w,
				 unsigned int h, const unsigned char *data)
{
  std::ofstream	img(file.c_str(), std::ios::out | std::ios::trunc | std::ios::binary);
  if (!img.is_open())
    return ;

  _tgaHeader[12] = w & 255;
  _tgaHeader[13] = w >> 8;
  _tgaHeader[14] = h & 255;
  _tgaHeader[15] = h >> 8;

  if (!img.write(reinterpret_cast<const char*>(_tgaHeader), sizeof(_tgaHeader)) ||
      !img.write(reinterpret_cast<const char*>(data), sizeof(*data) * w * h * 3))
    throw InvalidFileError("Write error");
  img.close();
}
