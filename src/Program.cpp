#include <iostream>
#include <cstdlib>
#include <ctime>

#include "Program.hpp"
#include "GameEngine.hpp"

int Program::run(int argc, const char *argv[])
{
  try
    {
      Options options(argc, argv);
      return internalRun(options);
    }
  catch (const std::exception& e)
    {
      std::cerr << e.what() << std::endl;
      return EXIT_FAILURE;
    }
}

int Program::internalRun(const Options& options)
{
  std::srand(std::time(NULL));

  GameEngine engine(options);
  if (!engine.initialize())
    return EXIT_FAILURE;
  while (engine.update())
    engine.draw();
  return EXIT_SUCCESS;
}
