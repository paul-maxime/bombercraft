#include <string>
#include "Options.hpp"

Options::Options(int argc, const char *argv[])
  : m_isFullscreen(false)
{
  if (argc >= 2)
    {
      std::string arg(argv[1]);
      m_isFullscreen = (arg == "--fullscreen");
    }
}

Options::~Options()
{
}

bool Options::isFullscreen() const
{
  return m_isFullscreen;
}
