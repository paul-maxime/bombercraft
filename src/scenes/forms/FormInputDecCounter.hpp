#ifndef FORMINPUTDECCOUNTER_H_
# define FORMINPUTDECCOUNTER_H_

# include	<string>
# include	"Text.hpp"
# include	"AFormInput.hpp"
# include	"TextureManager.hpp"

class FormInputDecCounter : public AFormInput
{
public:
  FormInputDecCounter(GameEngine* game,
		      const int posX, const int posY,
		      const int sizeX, const int sizeY,
		      const std::string &value,
		      const int minValue, const int maxValue, const int currentValue);
  virtual ~FormInputDecCounter();

  virtual void	draw(gdl::AShader &shader, gdl::Clock const &clock);
  virtual void	update(gdl::Clock const &);
  virtual int	getValue() const;

  void		changeMaxValue(int maxValue);

private:
  FormInputDecCounter(const FormInputDecCounter &);
  FormInputDecCounter &operator=(const FormInputDecCounter &);

private:
  std::string	_value;
  int		_heigthPadding;
  int		_currentValue;
  int		_minValue;
  int		_maxValue;
  float		_time;
};

#endif /* !FORMINPUTDECCOUNTER_H_ */
