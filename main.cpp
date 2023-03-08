#include "bits/stdc++.h"
using namespace std;

struct Data {
    int cost;
    int next;
    int prev;

    Data(int cost, int next, int prev) : cost(cost), next(next), prev(prev) {}
};

pair<vector<int>, vector<int>> path(const vector<int>& constraint, vector<unordered_map<int, vector<int>>> edges, int source, int destination) {
    vector<int> path(edges.size(), -1);
    vector<vector<int>> costs(edges.size(), vector<int>(constraint.size(), INT_MAX));
    vector<bool> visited(edges.size(), false);

    // menghapus semua edge yang menuju ke node awal (source)
    for (int i = 0; i < edges.size(); i++) {
        const auto& it = edges[i].find(source);
        if (it != edges[i].end()) {
            edges[i].erase(it);
        }
    }

    // menghapus semua edge yang berasal dari node akhir (destination)
    edges[destination].clear();

    int previouslyVisited = source;
    visited[previouslyVisited] = true;
    fill(&costs[source][0], &costs[source][0] + constraint.size(), 0);

    while(!visited[destination]) {

        int nextNode = -1;
        for (int i = 0; i < costs.size(); i++) {

            if (!visited[i]) {
                bool resourceMet = true;

                unordered_map<int, vector<int>>::iterator it = edges[previouslyVisited].find(i);

                if (it != edges[previouslyVisited].end()) {

                    vector<int> newCost = costs[previouslyVisited];

                    for (int j = 0; j < it->second.size(); j++) {
                        newCost[j] += it->second[j];
                        if (j > 0 && newCost[j] > constraint[j]) {
                            resourceMet = false;
                        }
                    }

                    if (costs[i][0] == INT_MAX || (costs[i][0] > newCost[0] && resourceMet)) {
                        costs[i] = newCost;
                        path[i] = previouslyVisited;
                    }
                }

                if (nextNode == -1 || costs[i][0] < costs[nextNode][0]) {
                    nextNode = i;
                }
            }
        }

        visited[nextNode] = true;
        previouslyVisited = nextNode;

        for (int i = 0; i < edges.size(); i++) {
            const auto& it = edges[i].find(previouslyVisited);
            if (it != edges[i].end()) {
                edges[i].erase(it);
            }
        }
    }

    vector<int> result;
    int traceback = destination;
    while(traceback != -1) {
        result.push_back(traceback );
        traceback = path[traceback ];
    }
    reverse(result.begin(), result.end());

    return {costs[destination], result};
}


int main() {
//    const vector<int>& constraint, vector<unordered_map<int, vector<int>>> edges, int source, int destination
    vector<int> constraint = {0, 10};
    vector<unordered_map<int, vector<int>>> edges({
        unordered_map<int, vector<int>>({
            {1, vector<int>({11,4})},
            {2, vector<int>({18,9})},
            {3, vector<int>({4,4})}
        }),
        unordered_map<int, vector<int>>({
            {0, vector<int>({10,6})},
            {2, vector<int>({3,2})},
            {5, vector<int>({14,7})}
        }),
        unordered_map<int, vector<int>>({
            {0, vector<int>({8,6})},
            {1, vector<int>({3,3})},
            {4, vector<int>({4,3})}
        }),
        unordered_map<int, vector<int>>({
            {0, vector<int>({5,3})},
            {4, vector<int>({15,11})}
        }),
        unordered_map<int, vector<int>>({
            {2, vector<int>({3,3})},
            {3, vector<int>({15,12})},
            {5, vector<int>({6,3})}
        }),
        unordered_map<int, vector<int>>({
            {1, vector<int>({14,22})},
            {2, vector<int>({7,6})},
            {4, vector<int>({7,5})}
        })
    });


    pair<vector<int>, vector<int>> result = path(constraint, edges, 0, 5);
    cout << "Path: ";
    for (int i = 0; i < result.second.size(); i++) {
        cout << result.second[i] << " ";
    }
    cout << "\nCost: ";
    for (int i = 0; i < result.first.size(); i++) {
        cout << result.first[i] << " ";
    }

    return 0;
}
