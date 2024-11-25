//
// Created by bryanm on 10/26/24.
//

#include "graph.h"
#include <vector>
#include <iostream>
#include <random>
#include <algorithm>

using namespace std;

Graph::Graph(int numNodes) : numNodes(numNodes), adjMatrix(numNodes, std::vector<int>(numNodes, 0)) {}

void Graph::addEdge(const Room& room1, const Room& room2) {
  // Get the index of the first room
  int room1Id = getRoomIndex(room1);
  int room2Id = getRoomIndex(room2);

  cout << room1Id << " " << room2Id << endl;

  // if the rooms exists
  if (room1Id != -1 && room2Id != -1) {
    // generate random weight
    random_device rd;   // Seed for random number engine
    mt19937 gen(rd());  // Mersenne Twister random number engine
    uniform_int_distribution<int> distr(1, 9);
    int randomNumber = distr(gen);

    // add rooms to the adjacency matrix with the random weights
    adjMatrix[room1Id][room2Id] = randomNumber;
    adjMatrix[room2Id][room1Id] = randomNumber;

  } else {
    cerr << "Error: One or both rooms do not exist\n";
  }
}

void Graph::printGraph() const{
  for (int i = 0; i < this->numNodes; ++i) {
    for (int j = 0; j < this->numNodes; ++j) {
      cout << adjMatrix[i][j] << " ";
    }
  	cout << endl;
  }
  cout << '\n';
}

const vector<vector<int>>& Graph::getAdjMatrix() const {
  return adjMatrix;
}

// helper function to obtain the index of the room in the rooms array
int Graph::getRoomIndex(const Room& room) const
{


  int idx;
  for (idx = 0; idx < this->rooms.size(); idx++) {
    if (rooms[idx] == room) {
      break;
    }
  }

  if (idx == -1) {
    return -1;
  }
  return idx;
}

void Graph::setRooms(const vector<Room>& roomsVector)
{
  this->rooms = roomsVector;
  numNodes = rooms.size();
  adjMatrix.resize(numNodes, std::vector<int>(numNodes, 0));
}

