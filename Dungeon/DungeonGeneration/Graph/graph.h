//
// Created by bryanm on 10/26/24.
//

#ifndef GRAPH_H
#define GRAPH_H

#include <vector>

struct Room {
  int width, height; // size of room
  int x, y; // position in grid

  // equality operator for comparison
  bool operator==(const Room& other) const {
    return (width == other.width && height == other.height && x == other.x && y == other.y);
   }
};

class Graph {
    public:
      int numNodes;

      // constructor - initialize adjacency matrix
      Graph(int numNodes);

      // adds edge between node u and node v
      void addEdge(const Room& room1, const Room& room2);

      void printGraph() const;

      const std::vector<std::vector<int>>& getAdjMatrix() const;

      // return the index of the room
      int getRoomIndex(const Room& room) const;

      void setRooms(const std::vector<Room>& roomsVector);


    private:
        // Vector of rooms (nodes in the graph)
        std::vector<Room> rooms;

        // 2D array of weights between rooms (Adjacency Matrix)
        std::vector<std::vector<int>> adjMatrix;


};



#endif //GRAPH_H
