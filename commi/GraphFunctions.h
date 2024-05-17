#pragma once
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 10;
const int INF = 1e9;

std::vector<std::vector<int>> graph;
bool visited[MAXN];
int n; // количество вершин
vector<int> path;
int min_cost = INF;

void dfs(int v, int cost, int len) {
    if (len == n) {
        if (graph[v][0]) {
            cost += graph[v][0];
            if (cost < min_cost) {
                min_cost = cost;
                path.push_back(0);
                cout << "Оптимальный путь: ";
                for (int i = 0; i < path.size(); i++) {
                    cout << path[i]+1;
                    if (i != path.size() - 1) cout << "->";
                }
                cout << ", Расстояние: " << min_cost << endl;
                path.pop_back();
            }
        }
        return;
    }

    visited[v] = true;
    path.push_back(v);

    for (int i = 0; i < n; i++) {
        if (graph[v][i] && !visited[i]) {
            dfs(i, cost + graph[v][i], len + 1);
        }
    }

    visited[v] = false;
    path.pop_back();
}

void obhod() {
    n = graph.size();


    for (int i = 0; i < n; i++) {
        visited[i] = false;
    }

    dfs(0, 0, 1);

    cout << "Оптимальное расстояние: " << min_cost << endl;

}

void obhod_v_glubiny(vector<vector<int>>& arr) {
    graph = arr;
    obhod();
}

