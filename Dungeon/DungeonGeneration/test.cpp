//
// Created by bryanm on 10/26/24.
//

#include "Graph/graph.h"
#include "Generation/DungeonGen.h"
#include "MST/Prim.h"

int main() {
  int numNodes = 12;


  Graph graph(numNodes);

  DungeonGeneration generation(50, 50, numNodes, graph);
  generation.GenerateRooms(12, 12);
  generation.CreateGraph();
  graph.printGraph();
  generation.ConnectRooms();
  generation.DisplayDungeon();


  return 0;
}