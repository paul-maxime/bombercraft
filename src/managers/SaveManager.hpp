#ifndef SAVE_MANAGER_HPP_
#define SAVE_MANAGER_HPP_

#include <string>

class Map;

class SaveManager
{
public:
  static SaveManager*	getInstance();
  static void		destroy();

  void			save(const std::string& file, const Map& map) const;
  Map*			load(const std::string& file) const;

private:
  SaveManager();
  ~SaveManager();

  SaveManager(const SaveManager&);
  SaveManager&	operator=(const SaveManager&);

  static SaveManager*	_instance;
  const int		_magic;
};

#endif
