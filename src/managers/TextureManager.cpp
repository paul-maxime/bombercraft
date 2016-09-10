#include <Texture.hh>
#include "TextureManager.hpp"
#include "TextureLoadError.hpp"
#include "AssetNotFoundError.hpp"

TextureManager*	TextureManager::_instance = NULL;

TextureManager*	TextureManager::getInstance()
{
  if (!_instance)
    _instance = new TextureManager();
  return (_instance);
}

void TextureManager::destroy()
{
  if (_instance)
    {
      delete (_instance);
      _instance = NULL;
    }
}

void TextureManager::bind(TextureName texture, bool repeat) const
{
  std::map< TextureName, gdl::Texture* >::const_iterator it;

  if ((it = _textures.find(texture)) != _textures.end())
    {
      it->second->bind();
      if (repeat)
	{
	  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}
    }
  else
    throw AssetNotFoundError();
}

void TextureManager::getSize(TextureName texture, glm::vec2& vec) const
{
  std::map< TextureName, gdl::Texture* >::const_iterator it;

  if ((it = _textures.find(texture)) != _textures.end())
    {
      vec.x = it->second->getWidth();
      vec.y = it->second->getHeight();
    }
  else
    throw AssetNotFoundError();
}

TextureManager::TextureManager()
{
  const std::string root = "./data/textures/";

  _texturesName[DEFAULT] = "texture.tga";
  _texturesName[BOMB] = "bomb.tga";
  _texturesName[EXPLOSION] = "lava.tga";
  _texturesName[BACKGROUND] = "background.tga";
  _texturesName[SCORE_BACKGROUND] = "score_background.tga";
  _texturesName[INTRO_BACKGROUND] = "intro_background.tga";
  _texturesName[MAIN_MENU] = "menu.tga";
  _texturesName[MENU_INPUT] = "planks_big_oak.tga";
  _texturesName[MENU_INPUT_FOCUSED] = "planks_oak.tga";
  _texturesName[SAVEBOX] = "ice.tga";
  _texturesName[SAVEBOX_FOCUSED] = "ice_packed.tga";
  _texturesName[CHECKBOX_NOT_CHECKED] = "checkbox_not_checked.tga";
  _texturesName[CHECKBOX_CHECKED] = "checkbox_checked.tga";
  _texturesName[STONE] = "stone.tga";
  _texturesName[BEDROCK] = "bedrock.tga";
  _texturesName[TNT] = "tnt.tga";
  _texturesName[GRASS] = "grass.tga";
  _texturesName[LIVE] ="live.tga";
  _texturesName[DIRT] = "dirt.tga";
  _texturesName[COBBLESTONE] = "cobblestone.tga";
  _texturesName[REDSTONE_BLOCK] = "redstone_block.tga";
  _texturesName[BEACON] = "beacon.tga";
  _texturesName[TITLE] = "Bombercraft.tga";
  _texturesName[LOADING_SCREEN] = "LoadingScreen.tga";
  _texturesName[GAME_OVER] = "GameOver.tga";
  _texturesName[WIN] = "Win.tga";
  _texturesName[LOSE] = "Lose.tga";
  _texturesName[BOMBS] = "bombs.tga";
  _texturesName[PISTON] = "piston.tga";
  _texturesName[CREATED_BY] = "Created_by.tga";
  _texturesName[DUVAL_H] = "duval_h.tga";
  _texturesName[CAUDOU_J] = "caudou_j.tga";
  _texturesName[DRAIN_A] = "drain_a.tga";
  _texturesName[LEDUC_P] = "leduc_p.tga";
  _texturesName[MORPHE_H] = "morphe_h.tga";

  for (std::map< TextureName, std::string >::iterator it = _texturesName.begin();
       it != _texturesName.end();
       ++it)
    {
      gdl::Texture* texture = new gdl::Texture;
      if (!texture->load(root + it->second))
	throw TextureLoadError(it->second);
      _textures[it->first] = texture;
    }
}

TextureManager::~TextureManager()
{
  for (std::map< TextureName, gdl::Texture* >::iterator it = _textures.begin();
       it != _textures.end();
       ++it)
    delete (it->second);
}
