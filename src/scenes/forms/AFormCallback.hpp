/**
 * \file AFormCallback.hpp
 * Contains the abstract form callback class.
 */

#ifndef A_FORM_CALLBACK_HPP_
#define A_FORM_CALLBACK_HPP_

#include <map>

#include "PlayersKeysManager.hpp"

/**
 * \class AFormCallBack
 * This abstract class represents a function that can be executed as a form
   callback. It is useful to hide the parent template class.
 */
class AFormCallback
{
public:
  /**
   ** Executes a function callback the specified key is pressed.
   * \param pair first:  the keycode of the event
		 second: the event's callback
   */
  static void call(const std::pair<int, AFormCallback *> & pair);
  static void call2(const std::pair<PlayersKeysManager::Actions, AFormCallback *> & pair);

  /**
   * Virtual operator that should call the callback function.
   */
  virtual void operator()() = 0;

  /**
   * Virtual destructor.
   */
  virtual ~AFormCallback() {}
};

#endif
