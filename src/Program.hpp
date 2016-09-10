/**
 * \file Program.hpp
 * Contains the static Program class.
 */

#ifndef PROGRAM_HPP_
#define PROGRAM_HPP_

#include "Options.hpp"

/**
 * \class Program
 * This static class contains the main function of the program.
 * It handles the options parsing and the creation of the game engine.
 */
class Program
{
public:
  /**
   * \param argc Program argument's count.
   * \param argv Program's arguments.
   * \return the program's status code.
   */
  static int run(int argc, const char *argv[]);

private:
  Program();

  static int internalRun(const Options& options);
};

#endif
