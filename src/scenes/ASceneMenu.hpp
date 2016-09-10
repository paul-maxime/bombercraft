#ifndef ASCENEMENU_H_
# define ASCENEMENU_H_

# include <vector>

# include "AScene.hpp"
# include "Sprite.hpp"
# include "ScoreManager.hpp"

class AFormCallback;
class AFormInput;

class ASceneMenu : public AScene
{
public:
  ASceneMenu(GameEngine* game, unsigned int menuIndex);
  virtual ~ASceneMenu();

  virtual void		update(gdl::Clock const &clock);
  virtual void		draw(gdl::AShader &shader, gdl::Clock const &clock);

private:
  ASceneMenu(const ASceneMenu &);
  ASceneMenu		&operator=(const ASceneMenu &);

  void				onKeyEscape();
  void				onKeyArrowDown();
  void				onKeyArrowUp();


protected:
  std::vector<AFormInput *>					m_buttons;
  unsigned int							m_buttonIndex;
  std::map<PlayersKeysManager::Actions, AFormCallback *>	m_keys;
};

#endif /* !ASCENEMENU_H_ */
