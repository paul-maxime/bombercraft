#include <glm/glm.hpp>
#include <Texture.hh>
#include "Text.hpp"

Text::Text()
  : m_width(0),
    m_height(0)
{
}

Text::Text(FontsManager::FontType font, const std::string& text)
{
  init(font, text);
}

Text::~Text()
{
}

void Text::init(FontsManager::FontType font, const std::string& text)
{
  m_font = font;
  m_text = text;
  glm::vec2 size;
  FontsManager::getInstance()->create(m_geometry, m_texture, size, font, text);
  m_width = size.x;
  m_height = size.y;
}

void Text::draw(gdl::AShader& shader, const gdl::Clock&)
{
  m_texture->bind();
  m_geometry.draw(shader, getTransformation(), GL_QUADS);
}

int Text::getWidth() const
{
  return m_width;
}

int Text::getHeight() const
{
  return m_height;
}
