/**
 * \file Options.hpp
 * Contains the program's options.
 */

#ifndef OPTIONS_HPP_
#define OPTIONS_HPP_

/**
 * \class Options
 * Parses the program arguments (argc, argv).
 */
class Options
{
public:
  /**
   * Parses the specified arguments into a new Options object.
   * \param argc Arguments count.
   * \param argv Arguments list.
   */
  Options(int argc, const char *argv[]);

  /**
   * Releases the resources used by the options.
   */
  virtual ~Options();

  /**
   * \return true if the fullscreen option is set.
   */
  bool		isFullscreen() const;

private:
  bool		m_isFullscreen;
};

#endif
