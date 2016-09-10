###################
#                 #
# C++ / Bomberman #
#                 #
###################

CXX		= g++
RM		= rm -f

NAME		= bomberman

# /src/

SRC		= \
		main.cpp		\
		Program.cpp		\
		Options.cpp		\
		File.cpp		\
		Map.cpp			\
		MapGenerator.cpp	\
		AScene.cpp		\
		GameEngine.cpp		\
		SceneContainer.cpp	\
		Screenshot.cpp		\
		BitmapFont.cpp		\
		LuaContext.cpp		\
		Pathfinding.cpp		\
		ObstacleMap.cpp		\
		EntitiesFactory.cpp	\
		AI.cpp

VPATH		= src/
INCLUDE		= -I./src/

# /src/objects/

SRC		+= \
		AObject.cpp		\
		AnimatedModel.cpp	\
		Menu.cpp		\
		Text.cpp		\
		Sprite.cpp

VPATH		+= src/objects/
INCLUDE		+= -I./src/objects/

# /src/converter/

SRC		+= \
		CharToEntityConverter.cpp

VPATH		+= src/converter/
INCLUDE		+= -I./src/converter/

# /src/entities/

SRC		+= \
		AEntity.cpp		\
		Player.cpp		\
		LuaPlayer.cpp		\
		Bomb.cpp		\
		Explosion.cpp		\
		SolidWall.cpp		\
		Box.cpp			\
		Wall.cpp

VPATH		+= src/entities/
INCLUDE		+= -I./src/entities/

# /src/entities/bonus/

SRC		+= \
		ABonus.cpp 		\
		PlayerSpeedBonus.cpp	\
		BombRangeBonus.cpp	\
		BombQuantityBonus.cpp	\
		BombPushBonus.cpp

VPATH		+= src/entities/bonus/
INCLUDE		+= -I./src/entities/bonus/

# /src/geometric/

SRC		+= \
		AGeometric.cpp		\
		Cube.cpp		\
		Tnt.cpp			\
		Plane.cpp

VPATH		+= src/geometric/
INCLUDE		+= -I./src/geometric/

# /src/scenes/

SRC		+= \
		SceneNewGame.cpp	\
		SceneChooseMap.cpp	\
		SceneChoosePlayers.cpp	\
		SceneNewMap.cpp		\
		SceneIntro.cpp		\
		SceneMenu.cpp		\
		SceneGame.cpp		\
		SceneCredit.cpp		\
		SceneOptions.cpp	\
		SceneSave.cpp		\
		ScenePause.cpp		\
		SceneLoading.cpp	\
		SceneConfirmation.cpp	\
		SceneEndGame.cpp	\
		SceneShowScore.cpp	\
		SceneChooseCmd.cpp	\
		SceneSaveScore.cpp	\
		ASceneMenu.cpp

VPATH		+= src/scenes/
INCLUDE		+= -I./src/scenes/

# /src/scenes/forms

SRC		+= \
		AFormCallback.cpp	\
		AFormInput.cpp		\
		FormInputButton.cpp	\
		FormInputDecCounter.cpp	\
		FormInputSaveBox.cpp	\
		FormInputMapBox.cpp	\
		FormInputCheckBox.cpp	\
		FormInputString.cpp	\
		FormInputJoystick.cpp	\
		FormInputScore.cpp

VPATH		+= src/scenes/forms/
INCLUDE		+= -I./src/scenes/forms/

# /src/managers/

SRC		+= \
		InputsManager.cpp	\
		MatrixManager.cpp	\
		TextureManager.cpp	\
		Model3DManager.cpp	\
		GeometricManager.cpp	\
		FontsManager.cpp	\
		SaveManager.cpp		\
		PlayersKeysManager.cpp	\
		AudioManager.cpp	\
		JoystickManager.cpp	\
		ScoreManager.cpp

VPATH		+= src/managers/
INCLUDE		+= -I./src/managers/

# /src/errors/

SRC		+= \
		CorruptedFileError.cpp	\
		InvalidFileError.cpp	\
		TextureLoadError.cpp	\
		ModelLoadError.cpp	\
		InvalidFontError.cpp	\
		AssetNotFoundError.cpp	\
		MapErrors.cpp		\
		LuaError.cpp

VPATH		+= src/errors/
INCLUDE		+= -I./src/errors/

BUILD		= build

OBJ		= $(patsubst %.cpp,$(BUILD)/%.o,$(SRC))

ifeq ($(wildcard gdl), gdl)
	GDL_PATH	= ./gdl
else
	GDL_PATH	= .
endif

LIB		+= -lgdl_gl -lGL -lSDL2 -lGLEW -lfbxsdk -lpthread -ldl -lrt
LIBPATH		+= -L$(GDL_PATH)/libs/
INCLUDE		+= -I$(GDL_PATH)/includes/

LIB		+= -llua
LIBPATH		+= -L./libs/lua/
INCLUDE		+= -I./libs/lua/

LIB		+= -lfmodex64
LIBPATH		+= -L./libs/fmod/
INCLUDE		+= -I./libs/fmod/

CXXFLAGS	+= $(INCLUDE)
CXXFLAGS	+= -Wall -Wextra

LDFLAGS		+= $(LIBPATH) $(LIB)
LDFLAGS		+= -Wl,-rpath=$(GDL_PATH)/libs:./libs/fmod/

ifeq ($(DEBUG), 1)
	CXXFLAGS	+= -ggdb3
else
	CXXFLAGS	+= -O2
endif

ifeq ($(PROF), 1)
	CXXFLAGS	+= -pg
	LDFLAGS		+= -pg
endif

all: $(BUILD) $(NAME)

./libs/lua/liblua.a:
	$(MAKE) -C ./libs/lua/ posix

$(NAME): $(OBJ) ./libs/lua/liblua.a
	$(CXX) $(OBJ) -o $(NAME) $(LDFLAGS)

$(BUILD):
	mkdir -p $(BUILD)

$(BUILD)/%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
ifeq ($(wildcard $(BUILD)), $(BUILD))
	$(RM) $(OBJ)
	-rmdir $(BUILD)
endif

fclean:	clean
	$(MAKE) -C ./libs/lua/ clean
	$(RM) $(NAME)

re: fclean all

.PHONY:	all clean fclean re
