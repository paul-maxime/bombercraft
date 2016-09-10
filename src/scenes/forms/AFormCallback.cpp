#include "AFormCallback.hpp"
#include "InputsManager.hpp"

void AFormCallback::call(const std::pair<int, AFormCallback *> & pair)
{
  InputsManager* inputs = InputsManager::getInstance();
  if (inputs->keyIsPressed(pair.first))
    (*pair.second)();
}

void AFormCallback::call2(const std::pair<PlayersKeysManager::Actions, AFormCallback *> & pair)
{
  InputsManager* inputs = InputsManager::getInstance();
  if (inputs->keyIsPressed(PlayersKeysManager::getInstance()->getActionsKeys(pair.first)))
    (*pair.second)();
}
