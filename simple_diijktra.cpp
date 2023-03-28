#include "bits/stdc++.h"
using namespace std;

pair<vector<int>, vector<int>> path(const vector<int>& constraint, vector<unordered_map<int, vector<int>>> edges, int source, int destination) {
    vector<int> path(edges.size(), -1);
    vector<vector<int>> costs(edges.size(), vector<int>(constraint.size(), INT_MAX));
    vector<bool> visited(edges.size(), false);
    int iteration = 0;

    int totalVisited = 0;
    int previouslyVisited = source;
    visited[previouslyVisited] = true;
    fill(&costs[source][0], &costs[source][0] + constraint.size(), 0);

    while(totalVisited < visited.size()) {

        int nextNode = -1;
        for (int i = 0; i < visited.size(); i++) {

            bool resourceMet = true;

            unordered_map<int, vector<int>>::iterator it = edges[previouslyVisited].find(i);

            if (it != edges[previouslyVisited].end()) {
                iteration++;

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
            if (!visited[i] && (nextNode == -1 || costs[i][0] < costs[nextNode][0])) {
                nextNode = i;
            }
        }

        totalVisited++;
        if (nextNode != -1) {
            visited[nextNode] = true;
            previouslyVisited = nextNode;
        }
    }

    vector<int> result;
    int traceback = destination;
    while(traceback != -1) {
        result.push_back(traceback );
        traceback = path[traceback ];
    }
    reverse(result.begin(), result.end());

    printf("iteration: %d\n", iteration);

    return {costs[destination], result};
}




int main() {
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

    int start, destination;
    fscanf(file_input, "%d %d", &start, &destination);


    pair<vector<int>, vector<int>> result = path(constraint, edges, start, destination);
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
