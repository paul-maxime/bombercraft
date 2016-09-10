#ifndef FORMINPUTCHECKBOX_H_
# define FORMINPUTCHECKBOX_H_

# include	<string>
# include	"Text.hpp"
# include	"AFormInput.hpp"
# include	"TextureManager.hpp"

class FormInputCheckBox : public AFormInput
{
public:
  FormInputCheckBox(GameEngine* game, const int posX, const int posY,
		    const int sizeX, const int sizeY, const std::string &value, bool checked);
  virtual ~FormInputCheckBox();
  virtual void	draw(gdl::AShader &shader, gdl::Clock const &clock);
  virtual void	update(gdl::Clock const &);
  virtual int	getValue() const;

private:
  void		placeText();

private:
  FormInputCheckBox(const FormInputCheckBox &);
  FormInputCheckBox &operator=(const FormInputCheckBox &);

private:
  Sprite	_checkBox;
  std::string	_value;
  Text		_text;
  int		_heigthPadding;
  bool		_checked;
};

#endif /* !FORMINPUTCHECKBOX_H_ */
