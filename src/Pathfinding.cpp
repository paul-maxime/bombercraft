#include <algorithm>
#include "Pathfinding.hpp"

Pathfinding::Pathfinding(const ObstacleMap* map, const Node& from, const Node& to, bool isDanger)
  : m_map(map),
    m_from(from),
    m_to(to),
    m_isDanger(isDanger)
{
  m_solved = solve();
  if (m_solved)
    generatePath();
}

Pathfinding::~Pathfinding()
{
}

bool Pathfinding::isSolved() const
{
  return m_solved;
}

const Pathfinding::Node* Pathfinding::next(const Node& node) const
{
  std::map<Node, Node>::const_iterator it = m_path.find(node);
  if (it != m_path.end())
    return &(it->second);
  return 0;
}

const Pathfinding::Node& Pathfinding::getDestination() const
{
  return m_to;
}

bool Pathfinding::solve()
{
  m_opened.insert(m_from);
  m_scores[m_from] = 0;

  while (m_opened.size() > 0)
    {
      Node current = popOpenList();
      if (current == m_to ||
	  (m_isDanger && !isObstacle(current) &&
	   !m_map->isDangerAt(current.first, current.second)))
	{
	  m_to = current;
	  return true;
	}
      m_closed.insert(current);
      std::vector<Node> neighbors = getNeighbors(current);
      std::vector<Node>::iterator it;
      for (it = neighbors.begin(); it != neighbors.end(); ++it)
	addNeighbor(current, *it);
    }
  return false;
}

void Pathfinding::addNeighbor(const Node& parent, const Node& node)
{
  if (m_closed.find(node) != m_closed.end())
    return;
  int score = m_scores[parent] + 10;
  bool isopen = (m_opened.find(node) != m_opened.end());
  if (!isopen || score < m_scores[node])
    {
      m_links[node] = parent;
      m_scores[node] = score;
      if (!isopen)
	m_opened.insert(node);
    }
}

Pathfinding::Node Pathfinding::popOpenList()
{
  Node best;
  int min = -1;
  std::set<Node>::iterator it;
  for (it = m_opened.begin(); it != m_opened.end(); ++it)
    {
      const Node& current = *it;
      if (min == -1 || m_scores[current] < min)
	{
	  min = m_scores[current];
	  best = current;
	}
    }
  it = m_opened.find(best);
  if (it != m_opened.end())
    m_opened.erase(it);
  return best;
}

void Pathfinding::generatePath()
{
  Node current = m_to;
  while (current != m_from)
    {
      Node next = m_links[current];
      m_path[next] = current;
      current = next;
    }
}

std::vector<Pathfinding::Node> Pathfinding::getNeighbors(const Node& node) const
{
  std::vector<Pathfinding::Node> neighbors;

  neighbors.push_back(Node(node.first + 1, node.second));
  neighbors.push_back(Node(node.first - 1, node.second));
  neighbors.push_back(Node(node.first, node.second + 1));
  neighbors.push_back(Node(node.first, node.second - 1));

  neighbors.push_back(Node(node.first + 1, node.second + 1));
  neighbors.push_back(Node(node.first + 1, node.second - 1));
  neighbors.push_back(Node(node.first - 1, node.second + 1));
  neighbors.push_back(Node(node.first - 1, node.second - 1));

  std::vector<Pathfinding::Node>::iterator it = neighbors.begin();
  while (it != neighbors.end())
    {
      Node& current = *it;
      if (!isWalkable(node, current))
	it = neighbors.erase(it);
      else
	++it;
    }

  return neighbors;
}

bool Pathfinding::isWalkable(const Node& from, const Node& to) const
{
  return !isObstacle(to) && !isBlockingDiagonal(from, to);
}

bool Pathfinding::isObstacle(const Node& to) const
{
  int x = to.first;
  int y = to.second;
  int obstacles = m_map->get(x, y);
  if (!m_map->isInMinimap(x, y) ||
      (obstacles & ObstacleMap::EXPLOSION) ||
      (obstacles & ObstacleMap::SOLID) ||
      (!m_isDanger && m_map->isDangerAt(x, y)))
    return true;
  return false;
}

bool Pathfinding::isBlockingDiagonal(const Node& from, const Node& to) const
{
  if (from.first != to.first && from.second != to.second)
    {
      Node d1(from.first, to.second);
      Node d2(from.second, to.first);
      if (isObstacle(d1) && isObstacle(d2))
	return true;
    }
  return false;
}
