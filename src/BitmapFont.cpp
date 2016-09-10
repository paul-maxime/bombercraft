#include <algorithm>
#include "BitmapFont.hpp"
#include "InvalidFontError.hpp"

BitmapFont::BitmapFont(const std::string& name)
  : m_name(name)
{
  m_handlers[1] = &BitmapFont::readInfo;
  m_handlers[2] = &BitmapFont::readCommon;
  m_handlers[4] = &BitmapFont::readChars;
  m_handlers[5] = &BitmapFont::readKernings;

  std::string filename = "data/fonts/" + name + ".fnt";
  m_texturePath = "data/fonts/" + name + "_0.tga";
  loadFile(filename);
}

BitmapFont::~BitmapFont()
{
}

const std::string& BitmapFont::getName() const
{
  return m_name;
}

const std::string& BitmapFont::getTexturePath() const
{
  return m_texturePath;
}

const BitmapFont::BlockInfo& BitmapFont::getInfo() const
{
  return m_info;
}

const BitmapFont::BlockCommon& BitmapFont::getCommon() const
{
  return m_common;
}

const BitmapFont::BlockChar* BitmapFont::getChar(uint32 id) const
{
  std::map<uint32, BlockChar>::const_iterator it = m_chars.find(id);
  if (it == m_chars.end())
    return NULL;
  return &it->second;
}

const BitmapFont::BlockKerningPair* BitmapFont::getKerning(uint32 first, uint32 second) const
{
  std::vector<BlockKerningPair>::const_iterator it;
  for (it = m_kernings.begin(); it != m_kernings.end(); ++it)
    {
      if (it->first == first && it->second == second)
	return &(*it);
    }
  return NULL;
}

void BitmapFont::loadFile(const std::string& filename)
{
  std::ifstream file(filename.c_str(), std::ios::in | std::ios::binary);
  if (!file)
    throw InvalidFontError(m_name);
  readHeader(file);
  while (file && readBlock(file));
}

void BitmapFont::readHeader(std::ifstream& file)
{
  Header header;
  if (!file.read(reinterpret_cast<char*>(&header), sizeof header))
    throw InvalidFontError(m_name);
  std::string magic(header.magic, 3);
  if (magic != "BMF" || header.version != 3)
    throw InvalidFontError(m_name);
}

bool BitmapFont::readBlock(std::ifstream& file)
{
  BlockHeader header;
  if (!file.read(reinterpret_cast<char*>(&header), sizeof header))
    return false;
  if (header.length == 0 || header.length > 0xFFFF)
    throw InvalidFontError(m_name);
  int8* bytes = new int8[header.length];
  if (!file.read(bytes, header.length))
    throw InvalidFontError(m_name);

  std::map<uint8, t_read_handler>::iterator it = m_handlers.find(header.type);
  if (it != m_handlers.end())
    (this->*it->second)(bytes, header.length);

  delete[] bytes;
  return true;
}

void BitmapFont::readInfo(const int8* bytes, uint32 length)
{
  if (length < sizeof(BlockInfo))
    throw InvalidFontError(m_name);
  std::copy(bytes, bytes + sizeof(BlockInfo), reinterpret_cast<char*>(&m_info));
}

void BitmapFont::readCommon(const int8* bytes, uint32 length)
{
  if (length < sizeof(BlockCommon))
    throw InvalidFontError(m_name);
  std::copy(bytes, bytes + sizeof(BlockCommon), reinterpret_cast<char*>(&m_common));
}

void BitmapFont::readChars(const int8* bytes, uint32 length)
{
  uint32 size = sizeof(BlockChar);
  uint32 count = length / size;
  if (count == 0 || count > 0xFF)
    throw InvalidFontError(m_name);
  for (uint32 i = 0; i < count; ++i)
    {
      BlockChar infos;
      uint32 start = i * size;
      uint32 end = start + size;
      std::copy(bytes + start, bytes + end, reinterpret_cast<char*>(&infos));
      m_chars[infos.id] = infos;
    }
}

void BitmapFont::readKernings(const int8* bytes, uint32 length)
{
  const uint32 size = sizeof(BlockKerningPair);
  uint32 count = length / size;
  if (count == 0 || count > 0xFFFF)
    throw InvalidFontError(m_name);
  for (uint32 i = 0; i < count; ++i)
    {
      BlockKerningPair infos;
      uint32 start = i * size;
      uint32 end = start + size;
      std::copy(bytes + start, bytes + end, reinterpret_cast<char*>(&infos));
      m_kernings.push_back(infos);
    }
}
