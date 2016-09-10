/**
 * \file BitmapFont.hpp
 * Contains the BitmapFont class.
 */

#ifndef BITMAP_FONT_HPP_
#define BITMAP_FONT_HPP_

#include <fstream>
#include <map>
#include <vector>
#include "../src/Utils.hpp"

/**
 * \class BitmapFont
 * Contains every informations about a bitmap font, generated
 * using BMFont: http://www.angelcode.com/products/bmfont/
 */
class BitmapFont
{
public:
  /**
   * Holds the main file header.
   */
  struct __attribute__ ((__packed__))
  Header
  {
    int8	magic[3];
    int8	version;
  };

  /**
   * Holds information about a block.
   */
  struct __attribute__ ((__packed__))
  BlockHeader
  {
    uint8	type;
    uint32	length;
  };

  /**
   * This tag holds information on how the font was generated.
   */
  struct __attribute__ ((__packed__))
  BlockInfo
  {
    int16	fontSize;
    uint8	bitField;
    uint8	charSet;
    uint16	stretchH;
    uint8	aa;
    uint8	paddingUp;
    uint8	paddingRight;
    uint8	paddingDown;
    uint8	paddingLeft;
    uint8	spacingHoriz;
    uint8	spacingVert;
    char	fontName;
  };

  /**
   * This tag holds information common to all characters.
   */
  struct __attribute__ ((__packed__))
  BlockCommon
  {
    uint16	lineHeight;
    uint16	base;
    uint16	scaleW;
    uint16	scaleH;
    uint16	pages;
    uint8	bitField;
    uint8	alphaChnl;
    uint8	redChnl;
    uint8	greenChnl;
    uint8	blueChnl;
  };

  /**
   * This tag describes one character in the font.
   * There is one for each included character in the font.
   */
  struct __attribute__ ((__packed__))
  BlockChar
  {
    uint32	id;
    uint16	x;
    uint16	y;
    uint16	width;
    uint16	height;
    int16	xoffset;
    int16	yoffset;
    int16	xadvance;
    uint8	page;
    uint8	chnl;
  };

  /**
   * The kerning information is used to adjust the distance between
   * certain characters.
   * eg. some characters should be placed closer to each other than others.
   */
  struct __attribute__ ((__packed__))
  BlockKerningPair
  {
    uint32	first;
    uint32	second;
    int16	amount;
  };

  /**
   * Loads a bitmap font from the specified name.
   * The font shall be in the /data/fonts/ directory.
   * \param name Font's name, eg. arial for /data/fonts/arial.fnt
   */
  BitmapFont(const std::string& name);

  /**
   * Frees the memory used by the bitmap informations.
   * Does not free the texture associated with the font.
   */
  virtual ~BitmapFont();

  /**
   * \return the font name, specified at construction.
   */
  const std::string&			getName() const;

  /**
   * \return the texture file's path.
   */
  const std::string&			getTexturePath() const;

  /**
   * \return font's informations.
   */
  const BlockInfo&			getInfo() const;

  /**
   * \return font's common variables.
   */
  const BlockCommon&			getCommon() const;

  /**
   * \param id Character's code. (eg. ascii code)
   * \return the character informations if it does exist, NULL otherwise.
   */
  const BlockChar*			getChar(uint32 id) const;

  /**
   * \param first First character's code.
   * \param second Second character's code.
   * \return the kerning informations between those two characters if it
   *         exists, NULL otherwise.
   */
  const BlockKerningPair*		getKerning(uint32 first, uint32 second) const;

private:
  typedef void (BitmapFont::*t_read_handler)(const int8*, uint32);

  std::string				m_name;
  std::string				m_texturePath;
  BlockInfo				m_info;
  BlockCommon				m_common;
  std::map<uint32, BlockChar>		m_chars;
  std::vector<BlockKerningPair>		m_kernings;
  std::map<uint8, t_read_handler>	m_handlers;

  void					loadFile(const std::string& filename);
  void					readHeader(std::ifstream& file);
  bool					readBlock(std::ifstream& file);
  void					readInfo(const int8* bytes, uint32 length);
  void					readCommon(const int8* bytes, uint32 length);
  void					readChars(const int8* bytes, uint32 length);
  void					readKernings(const int8* bytes, uint32 length);
};

#endif
