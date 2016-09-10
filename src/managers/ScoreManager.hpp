#ifndef SCOREMANAGER_H_
# define SCOREMANAGER_H_

# include	<string>
# include	<ctime>
# include	<vector>

# include	"Player.hpp"

class ScoreManager
{

public:
  class						playerScore
  {
  public:
    int						point;
    std::string					name;
  };

  class						gameScore
  {
  public:
    unsigned int				nbPlayerSaves;
    std::vector<ScoreManager::playerScore *>	playerScores;
  };

  /*
  ** defines and variables
  */
private:
  class						dataPlayerScore
  {
  public:
    int						point;
    char					name[32];
  };

  class						scoreSaves
  {
  public:
    unsigned int				nbGameSaves;
    std::vector<ScoreManager::gameScore *>	gameSaves;
  };

  static ScoreManager				*m_instance;

  const int					_magic;
  ScoreManager::scoreSaves			_scoreSaves;

  /*
  ** Methods
  */
public:
  void	print() const;
  const std::vector<ScoreManager::gameScore *>&	getScores() const;
  void	addScores(const std::vector<Player *>&);


  static ScoreManager*		getInstance();
  static void			destroy();

  const ScoreManager::playerScore		*getBestPlayerScore() const;
  int						nbScore() const;
  int						nbGame() const;
  int						getScoreAvg() const;

  void						delPlayerScore(const playerScore *playerScore);

private:
  void				load(const std::string& file);
  void				save(const std::string& file) const;

  /*
  ** constructor and destructor
  */
private:
  ScoreManager();
  virtual ~ScoreManager();
  ScoreManager(const ScoreManager &);
  ScoreManager &operator=(const ScoreManager &);
};

#endif /* !SCOREMANAGER_H_ */
