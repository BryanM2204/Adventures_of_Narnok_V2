//
// Created by bryanm on 11/13/24.
//

#ifndef GENERATION_H
#define GENERATION_H

#include <vector>
#include "../Graph/graph.h"
#include "../MST/Prim.h"

class DungeonGeneration {
public:
  DungeonGeneration(int gridWidth, int gridHeight, int numRooms, Graph& graph);
  bool overlapCheck(const Room& room);                       // helper function to check if rooms are overlapping
  void GenerateRooms(int maxWidth, int maxHeight);           // Randomly places rooms on the grid
  void CreateGraph();                                        // Creates a graph representation of rooms
  void ConnectRooms();                                       // Creates corridors between rooms
  void DisplayDungeon();                                     // Prints the dungeon layout
  void CreateHallway(int u, int v);

private:
  int gridWidth, gridHeight, numRooms;
  vector<vector<char>> dungeonGrid;  // 2D grid representing the dungeon
  vector<Room> rooms;               // List of rooms (position, size, etc.)
  Graph& graph;
  vector<int> mstParent;
};





#endif //GENERATION_H
