#include "bits/stdc++.h"
using namespace std;

struct Data {
    int cost;
    int next;
    int prev;

    Data(int cost, int next, int prev) : cost(cost), next(next), prev(prev) {}
};

struct DataComparator {
    bool operator()(const Data& d1, const Data& d2) {
        return d2.cost < d1.cost;
    }
};

pair<vector<int>, vector<int>> path(const vector<int>& constraint, vector<unordered_map<int, vector<int>>> edges, int source, int destination) {
    vector<int> path(edges.size(), -1);
    vector<vector<int>> costs(edges.size(), vector<int>(constraint.size()));
    vector<bool> visited(edges.size(), false);

    for (int i = 0; i < edges.size(); i++) {
        const auto& it = edges[i].find(source);
        if (it != edges[i].end()) {
            edges[i].erase(it);
        }
    }
    edges[destination].clear();

    priority_queue<Data, vector<Data>, DataComparator> pque;
    pque.push(Data(0, source, -1));

    while(!visited[destination] && !pque.empty()) {
        Data current = pque.top();
        pque.pop();

        if (!visited[current.next]) {
            visited[current.next] = true;
            path[current.next] = current.prev;

            if (current.prev != -1) {
                vector<int> edgesCost = edges[current.prev].find(current.next)->second;
                for (int i = 0; i < constraint.size(); i++) {
                    costs[current.next][i] = costs[current.prev][i] + edgesCost[i];
                }
            }

//            cout << "Node: " << current.next << " ";
//            for (int i = 0; i < constraint.size(); i++) {
//                cout << costs[current.next][i] << " ";
//            }
//            cout << endl;

            for (int i = 0; i < edges.size(); i++) {
                const auto& it = edges[i].find(current.next);
                if (it != edges[i].end()) {
                    edges[i].erase(it);
                }
            }
//            if (current.next == 2) {
//                cout << 2 << " " << edges[current.next].size() << endl;
//            }

            for (pair<const int, vector<int>>& it : edges[current.next]) {
                bool compatible = true;
                for (int i = 1; i < constraint.size(); i++) {
                    if (costs[current.next][i] + it.second[i] > constraint[i]) {
                        compatible = false;
                    }
                }
//                if (current.next == 1) {
//                    cout << "TES: " << 1 << " " << it.first << " " << compatible << endl;
//                }
                if (compatible) {
                    pque.push(Data(costs[current.next][0] + it.second[0], it.first, current.next));
                }
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
    vector<int> constraint = {0, 11};
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
