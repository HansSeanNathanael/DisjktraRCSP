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
    int vertex_count = 0;
    int edge_count = 0;
    int constraint_count = 0;

    // input baris pertama adalah 3 angka yaitu jumlah vertex (V), jumlah edge (E), dan jumlah constraint (C)
    // input E (jumlah edge) baris selanjutnya adalah data vertex yang formatnya adalah
    // VERTEX_AWAL VERTEX_AKHIR kemudian diikuti oleh C + 1 input yaitu COST_JARAK COST_CONSTRAINT_1 COST_CONSTRAINT_2 ... COST_CONSTRAINT_C
    // input baris terakhir adalah maksimum cost setiap constraint, jadi ada C input angka maksimal cost constraint.
    FILE* file_input = fopen("input.txt", "r");
    fscanf(file_input, "%d %d %d", &vertex_count, &edge_count, &constraint_count);

    vector<int> constraint(constraint_count + 1);
    vector<unordered_map<int, vector<int>>> edges(vertex_count);

//    vector<unordered_map<int, vector<int>>> edges({
//        unordered_map<int, vector<int>>({
//            {1, vector<int>({11,4})},
//            {2, vector<int>({18,9})},
//            {3, vector<int>({4,4})}
//        }),
//        unordered_map<int, vector<int>>({
//            {0, vector<int>({10,6})},
//            {2, vector<int>({3,2})},
//            {5, vector<int>({14,7})}
//        }),
//        unordered_map<int, vector<int>>({
//            {0, vector<int>({8,6})},
//            {1, vector<int>({3,3})},
//            {4, vector<int>({4,3})}
//        }),
//        unordered_map<int, vector<int>>({
//            {0, vector<int>({5,3})},
//            {4, vector<int>({15,11})}
//        }),
//        unordered_map<int, vector<int>>({
//            {2, vector<int>({3,3})},
//            {3, vector<int>({15,12})},
//            {5, vector<int>({6,3})}
//        }),
//        unordered_map<int, vector<int>>({
//            {1, vector<int>({14,22})},
//            {2, vector<int>({7,6})},
//            {4, vector<int>({7,5})}
//        })
//    });

    for (int i = 0; i < edge_count; i++) {
        int awal, akhir;
        fscanf(file_input, "%d %d", &awal, &akhir);

        vector<int> costs;
        for (int j = 0; j < constraint_count + 1; j++) {
            int cost;
            fscanf(file_input, "%d", &cost);
            costs.push_back(cost);
        }

        edges[awal].insert({akhir, costs});
    }

    for (int i = 1; i < constraint_count + 1; i++) {
        int cost;
        fscanf(file_input, "%d", &cost);
        constraint[i] = cost;
    }


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
