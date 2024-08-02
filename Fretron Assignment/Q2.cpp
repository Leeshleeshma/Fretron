#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Function to print the distribution result
void printDistribution(const vector<int>& ram, const vector<int>& sham, const vector<int>& rahim) {
    cout << "Distribution Result :" << endl;
    cout << "Ram : ";
    for (int weight : ram) cout << weight << " ";
    cout << endl;

    cout << "Sham : ";
    for (int weight : sham) cout << weight << " ";
    cout << endl;

    cout << "Rahim : ";
    for (int weight : rahim) cout << weight << " ";
    cout << endl;
}

int main() {
    vector<int> apples;
    int weight;
    while (true) {
        cout << "Enter apple weight in gram (-1 to stop) : ";
        cin >> weight;
        if (weight == -1) break;
        apples.push_back(weight);
    }

    // Calculate total weight
    int totalWeight = 0;
    for (int w : apples) totalWeight += w;

    // Proportional weights for each person
    int ramWeight = totalWeight * 50 / 100;
    int shamWeight = totalWeight * 30 / 100;
    int rahimWeight = totalWeight * 20 / 100;

    // Sort apples in descending order for better distribution
    sort(apples.rbegin(), apples.rend());

    vector<int> ram, sham, rahim;
    int ramCurrentWeight = 0, shamCurrentWeight = 0, rahimCurrentWeight = 0;

    // Greedy allocation
    for (int w : apples) {
        if (ramCurrentWeight < ramWeight) {
            ram.push_back(w);
            ramCurrentWeight += w;
        } else if (shamCurrentWeight < shamWeight) {
            sham.push_back(w);
            shamCurrentWeight += w;
        } else if (rahimCurrentWeight < rahimWeight) {
            rahim.push_back(w);
            rahimCurrentWeight += w;
        }
    }

    // Print the distribution result
    printDistribution(ram, sham, rahim);

    return 0;
}
