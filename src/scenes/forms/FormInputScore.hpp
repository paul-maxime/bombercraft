#ifndef FORMINPUTSCORE_H_
# define FORMINPUTSCORE_H_

# include	"FormInputButton.hpp"
# include	"ScoreManager.hpp"

class FormInputScore : public FormInputButton
{
public:
  FormInputScore(GameEngine* game, const int posX, const int posY,
		 const int sizeX, const int sizeY, const std::string &value,
		 const ScoreManager::playerScore *playerScore);

  virtual ~FormInputScore();

  virtual void	draw(gdl::AShader &shader, gdl::Clock const &clock);
  virtual void	update(gdl::Clock const &);

private:
  FormInputScore(const FormInputScore &);
  FormInputScore &operator=(const FormInputScore &);

  const ScoreManager::playerScore	*_playerScore;
};

#endif /* !FORMINPUTSCORE_H_ */
