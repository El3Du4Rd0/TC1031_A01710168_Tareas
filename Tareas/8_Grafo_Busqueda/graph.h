#ifndef Graph_H_
#define Graph_H_

#include <algorithm>
#include <fstream>
#include <iostream>
#include <list>
#include <queue>
#include <sstream>
#include <stack>
#include <stdio.h>
#include <string>
#include <vector>

using namespace std;

class Graph {
private:
  int edgesList;
  int edgesMat;
  int nodes;
  vector<int> *adjList;
  int *adjMatrix;
  vector<bool> visited;
  int *pathMatrix;

public:
  void loadGraphMat(string, int, int);
  void loadGraphList(string, int, int);
  Graph(int);
  Graph();
  void addEdgeAdjMatrix(int, int);
  void addEdgeAdjList(int, int);
  string printAdjMat();
  string printAdjList();
  string printAdjMat_clean();
  bool contains(list<int>, int);
  void sortAdjList();

  string DFS(int inicio, int fin);
  string BFS(int inicio, int fin);
};

void Graph::loadGraphMat(string name, int a, int b) {
  adjMatrix = new int[a * b];
  nodes = a;
  for (int i = 0; i < a * b; i++)
    adjMatrix[i] = 0;
  string line;
  ifstream lee(name);
  int u, v;
  if (lee.is_open()) {
    while (getline(lee, line)) {
      u = stoi(line.substr(1, 1));
      v = stoi(line.substr(4, 1));
      addEdgeAdjMatrix(u, v);
    }
    lee.close();
  } else {
    cout << "Unable to open file";
  }
}

void Graph::loadGraphList(string name, int n, int m) {
  adjList = new vector<int>[n];
  nodes = n;
  string line;
  ifstream lee(name);
  int u, v;
  if (lee.is_open()) {
    while (getline(lee, line)) {
      u = stoi(line.substr(1, 1));
      v = stoi(line.substr(4, 1));
      addEdgeAdjList(u, v);
    }
    lee.close();
  }
}

Graph::Graph() {
  edgesList = edgesMat = 0;
  adjList = nullptr;
  pathMatrix = nullptr;
}

Graph::Graph(int n) {
  nodes = n;
  adjList = new vector<int>[nodes];
  adjMatrix = new int[nodes * nodes];
  for (int i = 0; i < nodes * nodes; i++)
    adjMatrix[i] = 0;
  edgesList = edgesMat = 0;
}

void Graph::addEdgeAdjMatrix(int u, int v) {
  adjMatrix[u * nodes + v] = 1;
  adjMatrix[v * nodes + u] = 1;
  edgesMat++;
}

void Graph::addEdgeAdjList(int u, int v) {
  adjList[u].push_back(v);
  adjList[v].push_back(u);
  edgesList++;
}

string Graph::printAdjList() {
  stringstream results;
  for (int i = 0; i < nodes; i++) {
    results << "vertex " << i << " :";

    sort(adjList[i].begin(), adjList[i].end());

    for (int j = 0; j < adjList[i].size(); j++) {
      results << " " << adjList[i][j];
    }
    results << " ";
  }
  return results.str();
}

string Graph::printAdjMat() {
  stringstream results;
  for (int i = 0; i < nodes; i++) {
    for (int j = 0; j < nodes; j++) {
      results << adjMatrix[i * nodes + j] << " ";
    }
  }
  return results.str();
}

string Graph::printAdjMat_clean() {
  stringstream results;
  results << "\n nodes \t|";
  for (int i = 0; i < nodes; i++) {
    results << "\t" << i;
  }
  results << "\n";
  for (int i = 0; i < nodes; i++) {
    results << "____";
  }
  results << "\n";
  for (int i = 0; i < nodes; i++) {
    results << i << "\t|";
    for (int j = 0; j < nodes; j++) {
      results << "\t" << adjMatrix[i * nodes + j];
    }
    results << "\n";
  }
  return results.str();
}

void Graph::sortAdjList() {
  for (int i = 0; i < nodes; i++)
    sort(adjList[i].begin(), adjList[i].end());
}

string Graph::DFS(int inicio, int end) {
  stringstream results;
  results << "visited: ";
  stack<int> stk;
  vector<bool> visit(nodes, false);
  vector<int> path(nodes, -1);
  int act;
  stk.push(inicio);
  while (!stk.empty()) {
    act = stk.top();
    stk.pop();
    if (!visit[act]) {
      visit[act] = true;
      results << act << " ";
      if (act == end) {
        break;
      }
      for (int i = 0; i < adjList[act].size(); i++) {
        if (!visit[adjList[act][i]]) {
          stk.push(adjList[act][i]);
          path[adjList[act][i]] = act;
        }
      }
    }
  }
  int node = path[end];
  stack<int> reverse;
  reverse.push(end);
  results << "path:";
  while (node != inicio) {
    reverse.push(node);
    node = path[node];
  }
  reverse.push(inicio);
  while (!reverse.empty()) {
    results << " " << reverse.top();
    reverse.pop();
  }
  return results.str();
}

string Graph::BFS(int inicio, int end) {
  stringstream results;
  results << "visited: ";
  queue<int> que;
  vector<bool> visit(nodes, false);
  vector<int> path(nodes, -1);
  int act;
  que.push(inicio);

  while (!que.empty()) {
    act = que.front();
    que.pop();

    if (!visit[act]) {
      visit[act] = true;
      results << act << " ";

      if (act == end) break;

      for (int i = 0; i < adjList[act].size(); i++) {
        if (!visit[adjList[act][i]]) {
          que.push(adjList[act][i]);
          if (path[adjList[act][i]] == -1)
            path[adjList[act][i]] = act;
        }
      }
    }
  }

  int node = path[end];
  stack<int> reverse;
  reverse.push(end);
  results << "path:";
  while (node != inicio) {
    reverse.push(node);
    node = path[node];
  }
  reverse.push(inicio);
  while (!reverse.empty()) {
    results << " " << reverse.top();
    reverse.pop();
  }
  return results.str();
}

#endif