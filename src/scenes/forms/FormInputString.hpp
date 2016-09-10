#ifndef FORMINPUTSTRING_H_
#define FORMINPUTSTRING_H_

#include <string>
#include "Text.hpp"
#include "AFormInput.hpp"

class FormInputString : public AFormInput
{
public:
  FormInputString(GameEngine *game,
		  const int posX, const int posY,
		  const int sizeX, const int sizeY,
		  const std::string &value, const std::string &label);
  virtual ~FormInputString();

  virtual void	draw(gdl::AShader &shader, gdl::Clock const &clock);
  virtual void	update(gdl::Clock const &);

  const std::string	&getString() const;

private:
  FormInputString(const FormInputString &);
  FormInputString &operator=(const FormInputString &);

private:
  std::string		_value;
  Text			_label;
  int			_heigthPadding;
};

#endif
