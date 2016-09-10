#include <Geometry.hh>
#include <Texture.hh>
#include <glm/gtc/matrix_transform.hpp>

#include "FontsManager.hpp"
#include "AssetNotFoundError.hpp"
#include "TextureLoadError.hpp"

FontsManager* FontsManager::m_instance = NULL;

FontsManager* FontsManager::getInstance()
{
  if (!m_instance)
    m_instance = new FontsManager();
  return (m_instance);
}

void FontsManager::destroy()
{
  if (m_instance)
    {
      delete (m_instance);
      m_instance = NULL;
    }
}

void FontsManager::create(gdl::Geometry& geo,
			  const gdl::Texture*& texture,
			  glm::vec2& size,
			  FontType type,
			  const std::string& text)
{
  std::map<FontType, BitmapFont*>::const_iterator itf = m_fonts.find(type);
  std::map<FontType, gdl::Texture*>::const_iterator itt = m_textures.find(type);
  if (itf != m_fonts.end() && itt != m_textures.end())
    {
      const BitmapFont* font = itf->second;
      texture = itt->second;
      generateGeometry(geo, text, size, font, texture);
    }
  else
    throw AssetNotFoundError();
}

FontsManager::FontsManager()
{
  registerFont(DEFAULT, "arial");
}

FontsManager::~FontsManager()
{
  for (std::map<FontType, BitmapFont*>::iterator it = m_fonts.begin();
       it != m_fonts.end(); ++it)
    delete it->second;

  for (std::map<FontType, gdl::Texture*>::iterator it = m_textures.begin();
       it != m_textures.end(); ++it)
    delete it->second;
}

void FontsManager::registerFont(FontType type, const std::string& name)
{
  m_fonts[type] = new BitmapFont(name);
  m_textures[type] = new gdl::Texture;
  std::string path = m_fonts[type]->getTexturePath();
  if (!m_textures[type]->load(path))
    throw TextureLoadError(path);
}

void FontsManager::generateGeometry(gdl::Geometry& geo,
				    const std::string& text,
				    glm::vec2& size,
				    const BitmapFont* font,
				    const gdl::Texture* texture)
{
  m_delta_x = 0;
  m_delta_y = 0;
  size.x = 0;
  for (unsigned int i = 0; i < text.length(); ++i)
    {
      if (text[i] == '\n')
	{
	  if (m_delta_x > size.x)
	    size.x = m_delta_x;
	  m_delta_x = 0;
	  m_delta_y += font->getCommon().lineHeight;
	}
      else
	{
	  const BitmapFont::BlockChar* shape = font->getChar(text[i]);
	  if (shape)
	    generateLetter(geo, shape, texture);
	}
    }
  if (m_delta_x > size.x)
    size.x = m_delta_x;
  size.x = m_delta_x;
  size.y = m_delta_y + font->getCommon().lineHeight;
  geo.build();
}

void FontsManager::generateLetter(gdl::Geometry& geo,
				  const BitmapFont::BlockChar* shape,
				  const gdl::Texture* texture)
{
  int start_x = shape->xoffset + m_delta_x;
  int start_y = shape->yoffset + m_delta_y;
  int end_x = start_x + shape->width;
  int end_y = start_y + shape->height;

  geo.pushVertex(glm::vec3(start_x, start_y, 0));
  geo.pushVertex(glm::vec3(start_x, end_y, 0));
  geo.pushVertex(glm::vec3(end_x, end_y, 0));
  geo.pushVertex(glm::vec3(end_x, start_y, 0));

  float tex_x = static_cast<float>(shape->x) /
    static_cast<float>(texture->getWidth());
  float tex_y = static_cast<float>(shape->y) /
    static_cast<float>(texture->getHeight());
  float tex_end_x = static_cast<float>(shape->x + shape->width) /
    static_cast<float>(texture->getWidth());
  float tex_end_y = static_cast<float>(shape->y + shape->height) /
    static_cast<float>(texture->getHeight());

  geo.pushUv(glm::vec2(tex_x, 1 - tex_y));
  geo.pushUv(glm::vec2(tex_x, 1 - tex_end_y));
  geo.pushUv(glm::vec2(tex_end_x, 1 - tex_end_y));
  geo.pushUv(glm::vec2(tex_end_x, 1 - tex_y));

  m_delta_x += shape->xadvance;
}
