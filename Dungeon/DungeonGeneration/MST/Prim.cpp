#include "Prim.h"
#include <iostream>
#include <vector>
#include <climits>

PrimMST::PrimMST(int vertices) : V(vertices) {}

int PrimMST::minKey(std::vector<int>& key, std::vector<bool>& mstSet){
  int min = INT_MAX, min_index;

  for (int v = 0; v < V; v++)
    if (mstSet[v] == false && key[v] < min)
      min = key[v], min_index = v;

  return min_index;
}

void PrimMST::printMST(std::vector<int>& parent, const vector<vector<int>> &graph){
  cout << "Edge \tWeight\n";
  for (int i = 1; i < V; i++)
    cout << parent[i] << " - " << i << " \t"
         << graph[i][parent[i]] << " \n";
}

void PrimMST::findMST(const vector<vector<int>>& graph) {
  vector<int> parent(V);

  vector<int> key(V);

  vector<bool> mstSet(V);

  for (int i = 0; i < V; i++)
    key[i] = INT_MAX, mstSet[i] = false;

  key[0] = 0;

  parent[0] = -1;

  for (int count = 0; count < V - 1; count++) {
    int u = minKey(key, mstSet);
    mstSet[u] = true;

    for (int v = 0; v < V; v++)
      if (graph[u][v] && mstSet[v] == false
          && graph[u][v] < key[v])
          parent[v] = u, key[v] = graph[u][v];
  }

  mstParent = parent;

  printMST(parent, graph);
}

const std::vector<int>& PrimMST::getMSTParent() {
  return mstParent;
}
