//
// Created by bryanm on 10/26/24.
//

#include "Graph/graph.h"
#include "Generation/DungeonGen.h"

int main() {
  int numNodes = 6;


  Graph graph(numNodes);

  DungeonGeneration generation(50, 50, numNodes, graph);
  generation.GenerateRooms(8, 8);
  generation.CreateGraph();
  graph.printGraph();
  generation.ConnectRooms();
  generation.DisplayDungeon();


  return 0;
}