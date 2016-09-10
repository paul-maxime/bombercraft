#include "SceneContainer.hpp"
#include "AScene.hpp"

SceneContainer::SceneContainer() {}

SceneContainer::~SceneContainer()
{
  std::list<AScene*>::iterator it;
  for (it = m_scenes.begin(); it != m_scenes.end(); ++it)
    delete *it;
}

void SceneContainer::push(AScene* scene)
{
  m_scenes.push_front(scene);
}

bool SceneContainer::isEmpty()
{
  return m_scenes.empty();
}

void SceneContainer::update(gdl::Clock const &clock)
{
  std::list<AScene*>::iterator it = m_scenes.begin();
  while (it != m_scenes.end())
    {
      if ((*it)->isClosed())
	{
	  delete *it;
	  it = m_scenes.erase(it);
	}
      else
	++it;
    }
  if (!m_scenes.empty())
    m_scenes.front()->update(clock);
}

void SceneContainer::draw(gdl::AShader &shader, gdl::Clock const &clock)
{
  if (m_scenes.size() >= 2)
    {
      AScene* back = *(++m_scenes.begin());
      if (back->isBackground())
	back->draw(shader, clock);
    }
  if (m_scenes.size() >= 1)
    m_scenes.front()->draw(shader, clock);
}
