#pragma once
#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN_ = 10;
const int INF_ = 1e9;

std::vector<std::vector<int>> graph_;
int n_; // количество вершин

void tsp_bfs(int start) {
    vector<int> path;
    int min_cost = INF_;
    queue<pair<int, vector<int>>> q;
    q.push({ start, {start} });

    while (!q.empty()) {
        int v = q.front().first;
        path = q.front().second;
        q.pop();

        if (path.size() == n_) {
            int cost = 0;
            for (int i = 0; i < n_ - 1; i++) {
                cost += graph_[path[i]][path[i + 1]];
            }
            cost += graph_[path[n_ - 1]][start];

            if (cost < min_cost) {
                min_cost = cost;
            }
        }

        for (int i = 0; i < n_; i++) {
            if (graph_[v][i] != 0 && find(path.begin(), path.end(), i) == path.end()) {
                vector<int> new_path = path;
                new_path.push_back(i);
                q.push({ i, new_path });
            }
        }
    }

    cout << "Оптимальное расстояние: " << min_cost << endl;
}

void obhod_gr() {
    n_ = graph_.size();

    tsp_bfs(0);

}

void obhod_v_shirinu(vector<vector<int>>& arr) {
    graph_ = arr;
    obhod_gr();
}
