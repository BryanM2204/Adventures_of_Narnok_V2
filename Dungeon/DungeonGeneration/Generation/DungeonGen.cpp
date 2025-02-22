//
// Created by Bryan on 11/13/24.
//

#include "DungeonGen.h"
#include "../Graph/graph.h"
#include "../MST/Prim.h"
#include <random>
#include <iostream>

DungeonGeneration::DungeonGeneration(int gridWidth, int gridHeight, int numRooms, Graph& graph) : dungeonGrid(gridWidth, std::vector<char>(gridHeight, ' ')), graph(graph){
  this->numRooms = numRooms;
  this->gridWidth = gridWidth;
  this->gridHeight = gridHeight;
}

// Overload the << operator for Room struct
ostream& operator<<(ostream& os, const Room& room) {
  os << "Room(x: " << room.x << ", y: " << room.y
     << ", width: " << room.width << ", height: " << room.height << ")";
  return os;
}

void DungeonGeneration::GenerateRooms(int maxWidth, int maxHeight) {
  // generate random weight
  random_device rd;   // Seed for random number engine
  mt19937 gen(rd());  // Mersenne Twister random number engine
  uniform_int_distribution<int> widthDist(8, maxWidth);
  uniform_int_distribution<int> heightDist(8, maxHeight);
  uniform_int_distribution<int> xDist(1, gridWidth - maxWidth - 1);
  uniform_int_distribution<int> yDist(1, gridHeight - maxHeight - 1);

  for (int i = 0; i < numRooms; i++) {
    int x = xDist(gen);
    int y = yDist(gen);
    int width = widthDist(gen);
    int height = heightDist(gen);

    Room newRoom = {width, height, x, y};
    rooms.push_back(newRoom);
  }

  for (const Room& room: rooms) {
    for (int i = room.x; i < room.x + room.width; i++) {
      for (int j = room.y; j < room.y + room.height; j++) {
        // if the i and j values are within the grid's dimensions and are not the edges of the room
        if (i >= 0 && i < gridWidth && j >= 0 && j < gridHeight) {
          // add a floor tile
          dungeonGrid[i][j] = '.';
        }
        // if the x value is on the left side of the room
        if (i == room.x) {
          if (j == room.y) {
            dungeonGrid[i-1][j-1] = '|';
          } else if (j == room.y + room.height - 1) {
            dungeonGrid[i-1][j+1] = '|';
          }
          // add a wall i-1 from the room
          dungeonGrid[i-1][j] = '-';

          // if I value is at the edge of the room on the right
        } else if (i == room.x + room.width - 1){
          if (j == room.y){
            dungeonGrid[i+1][j-1] = '|';
          } else if (j == room.y + room.height - 1) {
            dungeonGrid[i+1][j+1] = '|';
          }
          // add a wall i+1 from the room
          dungeonGrid[i+1][j] = '-';
        }

        // if the y value is on the top of the room
        if (j == room.y) {
          // add a wall j-1 from the room
          dungeonGrid[i][j-1] = '|';

          // if the y value is on the bottom edge of the room
        } else if (j == room.y + room.height - 1) {
          // add a wall j+1 from the room
          dungeonGrid[i][j+1] = '|';
        }
      }
    }
  }

}

void DungeonGeneration::CreateGraph() {

  graph.setRooms(rooms);

  for (const Room& room: rooms)
  {
    cout << room << " \n";
  }
  cout << "\n";

  for (int i = 0; i < rooms.size(); i++) {
    Room& room1 = rooms[i];
    Room room2;
    if (i+1 < rooms.size()) {
      room2 = rooms[i+1];
    } else {
      room2 = rooms[i-1];
    }

    cout << room1 << " \n";
    cout << room2 << " \n";

    graph.addEdge(room1, room2);

  }
}

void DungeonGeneration::ConnectRooms()
{
  // Create MST
  PrimMST prim(numRooms);
  prim.findMST(graph.getAdjMatrix());

  // Get MST parent array
  mstParent = prim.getMSTParent();

  for (int i = 1; i < numRooms; i++) {
    int u = mstParent[i]; // u is parent
    int v = i;            // v is current room / child or u

    CreateHallway(u, v);
  }
}

void DungeonGeneration::CreateHallway(int u, int v)
{
  Room parent = rooms[u];
  Room child = rooms[v];

  // center coords for parent room
  int x1 = parent.x + (parent.width / 2);
  int y1 = parent.y + (parent.height / 2);

  cout << parent << "Has the midpoint of: " << x1 << ", " << y1 << endl;


  // center coords for child room
  int x2 = child.x + (child.width / 2);
  int y2 = child.y + (child.height / 2);


  cout << child << "Has the midpoint of: " << x2 << ", " << y2 << endl;

  // generate random weight
  random_device rd;   // Seed for random number engine
  mt19937 gen(rd());  // Mersenne Twister random number engine
  uniform_int_distribution<int> hallwayGen(0, 1);

  if(x1 > x2 && y1 > y2) {
    for(int i = x2; i <= x1; i++) {
      if(dungeonGrid[i][y2] != '.')
        dungeonGrid[i][y2] = 'X';
    }
    for(int i = y2; i <= y1; i++) {
      if(dungeonGrid[x1][i] != '.')
        dungeonGrid[x1][i] = 'Y';
    }
  } else if(x1 > x2 && y2 > y1) {
    for(int i = x2; i <= x1; i++) {
      if(dungeonGrid[i][y1] != '.')
        dungeonGrid[i][y1] = 'X';
    }
    for(int i = y1; i <= y2; i++) {
      if(dungeonGrid[x2][i] != '.')
        dungeonGrid[x2][i] = 'Y';
    }
  } else if(x2 > x1 && y1 > y2) {
    for(int i = x1; i <= x2; i++) {
      if(dungeonGrid[i][y1] != '.')
        dungeonGrid[i][y1] = 'X';
    }
    for(int i = y2; i <= y1; i++) {
      if(dungeonGrid[x2][i] != '.')
        dungeonGrid[x2][i] = 'Y';
    }
  }
  else if(x2 > x1 && y2 > y1) {
    for(int i = x1; i <= x2; i++) {
      if(dungeonGrid[i][y1] != '.')
        dungeonGrid[i][y1] = 'X';
    }
    for(int i = y1; i <= y2; i++) {
      if(dungeonGrid[x2][i] != '.')
        dungeonGrid[x2][i] = 'Y';
    }
  } else if (y1 == y2) {
    for(int i = std::min(x1, x2); i <= std::max(x1, x2); i++) {
      if(dungeonGrid[i][y1] != '.')
        dungeonGrid[i][y1] = 'X';
    }
  } else {
    for(int i = std::min(y1, y2); i <= std::max(y1, y2); i++) {
      if(dungeonGrid[x1][i] != '.')
        dungeonGrid[x1][i] = 'X';
    }
  }
}



void DungeonGeneration::DisplayDungeon() {
  // Print out the dungeon
  for (int i = 0; i < gridWidth; i++) {
    for (int j = 0; j < gridHeight; j++) {
      cout << dungeonGrid[i][j] << " ";
    }
    cout << endl;
  }
}