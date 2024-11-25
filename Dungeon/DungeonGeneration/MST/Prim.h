//
// Created by bryanm on 11/6/24.
//

#ifndef PRIM_H
#define PRIM_H

#include <vector>
using namespace std;
class PrimMST {
    public:
      PrimMST(int vertices);
      void findMST(const vector<vector<int>>& graph);
      const vector<int>& getMSTParent();

    private:
      int minKey(vector<int>& key, vector<bool>& mstSet);
      void printMST(vector<int>& parent, const vector<vector<int>> &graph);
      vector<int> mstParent;
      int V; // Number of vertices
};



#endif //PRIM_H
