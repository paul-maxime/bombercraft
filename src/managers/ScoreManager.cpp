#include	<fstream>
#include	<iostream>
#include	<cstdlib>

#include	"CorruptedFileError.hpp"
#include	"InvalidFileError.hpp"
#include	"ScoreManager.hpp"
#include	"Utils.hpp"

ScoreManager* ScoreManager::m_instance = NULL;

ScoreManager::ScoreManager()
  : _magic(0x424D4F43)
{
  try
    {
      _scoreSaves.nbGameSaves = 0;
      this->load("score_save.sb");
    }
  catch (InvalidFileError &)
    {
      std::cout << "ScoreManager : no save available" << std::endl;
    }
  catch (CorruptedFileError &err)
    {
      std::cout << "ScoreManager : " << err.what() << std::endl;
    }
}

ScoreManager::~ScoreManager()
{
}

ScoreManager*	ScoreManager::getInstance()
{
  if (!m_instance)
    m_instance = new ScoreManager();
  return (m_instance);
}

void			ScoreManager::destroy()
{
  if (m_instance)
    {
      delete (m_instance);
      m_instance = NULL;
    }
}

void	ScoreManager::delPlayerScore(const playerScore *playerScore)
{
  for (std::vector<ScoreManager::gameScore *>::iterator gameScore = _scoreSaves.gameSaves.begin();
       gameScore != _scoreSaves.gameSaves.end();
       ++gameScore)
    {
      for (std::vector<ScoreManager::playerScore *>::iterator player = (*gameScore)->playerScores.begin();
	   player != (*gameScore)->playerScores.end();
	   ++player)
	if ((*player) == playerScore)
	  {
	    --(*gameScore)->nbPlayerSaves;
	    (*gameScore)->playerScores.erase(player);
	    if (!(*gameScore)->playerScores.size())
	      {
		--_scoreSaves.nbGameSaves;
		_scoreSaves.gameSaves.erase(gameScore);
	      }
	    this->save("score_save.sb");
	    return ;
	  }
    }
}

void	ScoreManager::addScores(const std::vector<Player *>& players)
{
  gameScore	*gameScore;
  playerScore	*playerScore;

  gameScore = new ScoreManager::gameScore;
  for (std::vector<Player *>::const_iterator it = players.begin(); it != players.end(); ++it)
    if (!(*it)->isIA())
      {
	playerScore = new ScoreManager::playerScore;
	playerScore->name = (*it)->getName();
	playerScore->name.resize(32, '\0');
	playerScore->point = (*it)->getPoints();
	gameScore->playerScores.push_back(playerScore);
      }
  gameScore->nbPlayerSaves = gameScore->playerScores.size();
  _scoreSaves.gameSaves.push_back(gameScore);
  ++_scoreSaves.nbGameSaves;
  this->save("score_save.sb");
}

int	ScoreManager::nbGame() const
{
  int	count = 0;

  for (std::vector<ScoreManager::gameScore *>::const_iterator gameScore = _scoreSaves.gameSaves.begin();
       gameScore != _scoreSaves.gameSaves.end();
       ++gameScore)
    ++count;
  return count;
}

int	ScoreManager::nbScore() const
{
  int	count = 0;

  for (std::vector<ScoreManager::gameScore *>::const_iterator gameScore = _scoreSaves.gameSaves.begin();
       gameScore != _scoreSaves.gameSaves.end();
       ++gameScore)
    {
      for (std::vector<ScoreManager::playerScore *>::const_iterator player = (*gameScore)->playerScores.begin();
	   player != (*gameScore)->playerScores.end();
	   ++player)
	++count;
    }
  return count;
}


int	ScoreManager::getScoreAvg() const
{
  int	count = 0;
  int	sum = 0;

  for (std::vector<ScoreManager::gameScore *>::const_iterator gameScore = _scoreSaves.gameSaves.begin();
       gameScore != _scoreSaves.gameSaves.end();
       ++gameScore)
    {
      for (std::vector<ScoreManager::playerScore *>::const_iterator player = (*gameScore)->playerScores.begin();
	   player != (*gameScore)->playerScores.end();
	   ++player)
	{
	  ++count;
	  sum += (*player)->point;
	}
    }
  if (!count)
    return 0;
  return sum / count;
}

void	ScoreManager::print() const
{
  std::cout << "Score saved :" << std::endl;
  for (std::vector<ScoreManager::gameScore *>::const_iterator gameScore = _scoreSaves.gameSaves.begin();
       gameScore != _scoreSaves.gameSaves.end();
       ++gameScore)
    {
      std::cout << "Game : " << std::endl;
      for (std::vector<ScoreManager::playerScore *>::const_iterator player = (*gameScore)->playerScores.begin();
	   player != (*gameScore)->playerScores.end();
	   ++player)
	{
	  std::cout << "Player : " << (*player)->name << ", point : " << (*player)->point << std::endl;
	}
    }
}

const std::vector<ScoreManager::gameScore *>&	ScoreManager::getScores() const
{
  return _scoreSaves.gameSaves;
}

const ScoreManager::playerScore	*ScoreManager::getBestPlayerScore() const
{
  ScoreManager::playerScore		*bestPlayerScore = NULL;

  for (std::vector<ScoreManager::gameScore *>::const_iterator gameScore = _scoreSaves.gameSaves.begin();
       gameScore != _scoreSaves.gameSaves.end();
       ++gameScore)
    {
      for (std::vector<ScoreManager::playerScore *>::const_iterator player = (*gameScore)->playerScores.begin();
	   player != (*gameScore)->playerScores.end();
	   ++player)
	{
	  if (bestPlayerScore == NULL || bestPlayerScore->point < (*player)->point)
	    bestPlayerScore = (*player);
	}
    }
  return bestPlayerScore;
}

void	ScoreManager::save(const std::string& file) const
{
  std::ofstream	out(file.c_str(), std::ios::trunc | std::ios::binary | std::ios::out);

  if (!out.is_open())
    throw InvalidFileError("Could not open file : ScoreManager save()");

  if (!out.write(reinterpret_cast<const char*>(&_magic), sizeof _magic))
    throw InvalidFileError("Write error");

  if (!out.write(reinterpret_cast<const char*>(&_scoreSaves.nbGameSaves),
		 sizeof _scoreSaves.nbGameSaves))
    throw InvalidFileError("Write error");
  for (std::vector<ScoreManager::gameScore *>::const_iterator gameScore = _scoreSaves.gameSaves.begin();
       gameScore != _scoreSaves.gameSaves.end();
       ++gameScore)
    {
      if (!out.write(reinterpret_cast<const char*>(&((*gameScore)->nbPlayerSaves)),
		     sizeof ((*gameScore)->nbPlayerSaves)))
	throw InvalidFileError("Write error");
      for (std::vector<ScoreManager::playerScore *>::const_iterator player = (*gameScore)->playerScores.begin();
	   player != (*gameScore)->playerScores.end();
	   ++player)
	{
	  if (!out.write(reinterpret_cast<const char*>(&((*player)->point)), sizeof ((*player)->point)))
	    throw InvalidFileError("Write error");
	  if (!out.write(reinterpret_cast<const char*>((*player)->name.c_str()), 32))
	    throw InvalidFileError("Write error");
	}
    }
  out.close();
}

void	ScoreManager::load(const std::string& file)
{
  std::ifstream			in(file.c_str(), std::ios::in | std::ios::binary);
  int				magic;
  ScoreManager::dataPlayerScore	dataPlayerScores;
  ScoreManager::playerScore	*playerScore;
  ScoreManager::gameScore	*gameScore;

  if (!in.is_open())
    throw InvalidFileError("Could not open file : ScoreManager load()");
  if (!in.read(reinterpret_cast<char*>(&magic), sizeof magic) || magic != _magic)
    throw CorruptedFileError("ScoreManager : Wrong magic number");
  if (!in.read(reinterpret_cast<char*>(&_scoreSaves.nbGameSaves), sizeof _scoreSaves.nbGameSaves))
    throw CorruptedFileError("Read failed");
  for (unsigned int i = 0; i < _scoreSaves.nbGameSaves; ++i)
    {
      gameScore = new ScoreManager::gameScore;
      if (!in.read(reinterpret_cast<char*>(&gameScore->nbPlayerSaves),
		   sizeof (gameScore->nbPlayerSaves)))
	throw CorruptedFileError("Read failed 1");
      for (unsigned int j = 0; j < gameScore->nbPlayerSaves; ++j)
	{
	  if (!in.read(reinterpret_cast<char*>(&dataPlayerScores),
		       sizeof(ScoreManager::dataPlayerScore)))
	    throw CorruptedFileError("Read failed  size to read : ");
	  playerScore = new ScoreManager::playerScore;
	  playerScore->point = dataPlayerScores.point;
	  playerScore->name = std::string(dataPlayerScores.name);
	  playerScore->name.resize(32, '\0');
	  gameScore->playerScores.push_back(playerScore);
	}
      _scoreSaves.gameSaves.push_back(gameScore);
    }
  in.close();
}
