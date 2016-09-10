/**
 * \file Utils.hpp
 * Contains useful functions and variables.
 */

#ifndef UTILS_HPP_
#define UTILS_HPP_

#include <sstream>

/**
 * Contains generic useful functions used by the program.
 */
class Utils
{
public:
  /**
   * Converts the specified value into a new string.
   * \tparam T Any type that can be sent to an ostringsteam.
   * \param value The value to convert into a string.
   * \return The newly converted string.
   */
  template <typename T>
  static std::string		toString(T value)
  {
    std::ostringstream oss;
    oss << value;
    return oss.str();
  }

  /**
   * Converts the specified string into an integer.
   * \param value The string to convert into a int.
   * \return The int value of the string.
   */
  static int			toInt(const std::string& value)
  {
    int ret;
    std::istringstream buff(value);
    buff >> ret;
    return ret;
  }

  /**
   * Compares a and b and returns the maximal value.
   * \tparam T Values type (probably a numeric one).
   * \param a First value.
   * \param b Second value.
   * \return a if a is greater than b, b otherwise.
   */
  template <typename T>
  static T			max(T a, T b)
  {
    if (a > b)
      return a;
    return b;
  }

  /**
   * Compares a and b and returns the minimal value.
   * \tparam T Values type (probably a numeric one).
   * \param a First value.
   * \param b Second value.
   * \return a if a is lesser than b, b otherwise.
   */
  template <typename T>
  static T			min(T a, T b)
  {
    if (a < b)
      return a;
    return b;
  }

private:
  Utils();
};

typedef unsigned char	uint8;
typedef char		int8;
typedef unsigned short	uint16;
typedef short		int16;
typedef unsigned int	uint32;
typedef int		int32;

#endif
