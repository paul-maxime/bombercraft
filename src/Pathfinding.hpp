/**
 * \file Pathfinding.hpp
 * Contains the Pathfinding class.
 */

#ifndef PATHFINDING_HPP_
#define PATHFINDING_HPP_

#include <map>
#include <set>
#include <vector>
#include "ObstacleMap.hpp"

/**
 * \class Pathfinding
 * Move from a point to another using the Dijkstra algorithm.
 * This class is used by the AI.
 */
class Pathfinding
{
public:
  /**
   * A Node is a set of two coordinates (x, y).
   */
  typedef std::pair<int, int> Node;

  /**
   * Creates and solves a new path between from and to.
   * \param map The map containing the obstacles to avoid.
   * \param from Starting position.
   * \param to Ending position.
   * \param isDanger Can we walk through future dangers?
   */
  Pathfinding(const ObstacleMap* map, const Node& from, const Node& to, bool isDanger);

  /**
   * Frees the memory used by the pathfinder and the nodes.
   */
  virtual ~Pathfinding();

  /**
   * \return true if the pathfinder managed to find a path.
   */
  bool isSolved() const;

  /**
   * Returns the next cell based on the current cell.
   * \param node The current player location.
   * \return The next location.
   */
  const Node* next(const Node& node) const;

  /**
   * \return the generated path's destination.
   */
  const Node& getDestination() const;

private:
  Pathfinding(const Pathfinding&);
  Pathfinding& operator=(const Pathfinding&);

  bool solve();
  void addNeighbor(const Node& parent, const Node& node);
  Node popOpenList();
  void generatePath();

  std::vector<Node> getNeighbors(const Node& node) const;
  bool isWalkable(const Node& from, const Node& to) const;
  bool isObstacle(const Node& to) const;
  bool isBlockingDiagonal(const Node& from, const Node& to) const;

  const ObstacleMap*	m_map;
  Node			m_from;
  Node			m_to;
  bool			m_isDanger;
  std::set<Node>	m_opened;
  std::set<Node>	m_closed;
  std::map<Node, int>	m_scores;
  std::map<Node, Node>	m_links;
  std::map<Node, Node>	m_path;
  bool			m_solved;
};

#endif
