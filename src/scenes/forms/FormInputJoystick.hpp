#ifndef FORMINPUTJOYSTICK_H_
# define FORMINPUTJOYSTICK_H_

# include	<string>
# include	"Text.hpp"
# include	"AFormInput.hpp"
# include	"TextureManager.hpp"

class FormInputJoystick : public AFormInput
{
public:
  FormInputJoystick(GameEngine* game,
		    const int posX, const int posY,
		    const int sizeX, const int sizeY,
		    const std::string &value,
		    const int currentValue);
  virtual ~FormInputJoystick();
  virtual void	draw(gdl::AShader &shader, gdl::Clock const &clock);
  virtual void	update(gdl::Clock const &);
  virtual int	getValue() const;

private:
  FormInputJoystick(const FormInputJoystick &);
  FormInputJoystick &operator=(const FormInputJoystick &);

private:
  std::string			_value;
  int				_heigthPadding;
  int				_currentValue;
  int				_minValue;
  int				_maxValue;
  float				_time;
  std::vector<std::string>	_controllerNames;
};

#endif
