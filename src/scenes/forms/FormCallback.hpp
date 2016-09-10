/**
 * \file FormCallback.hpp
 * Contains the templated-class FormCallback.
 */

#ifndef FORM_CALLBACK_HPP_
#define FORM_CALLBACK_HPP_

#include "AFormCallback.hpp"

template <class T>
class FormCallback : public AFormCallback
{
private:
  typedef void		(T::*t_handler)();

  T*			m_instance;
  t_handler		m_fct;

public:
  FormCallback(T* instance, t_handler fct)
    : m_instance(instance),
      m_fct(fct)
  {
  }

  virtual ~FormCallback() {}

  virtual void operator()()
  {
    (m_instance->*m_fct)();
  }
};

#endif
