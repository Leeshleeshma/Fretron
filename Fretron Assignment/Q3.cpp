#include <iostream>
#include <vector>
#include <set>
#include <tuple>

using namespace std;

struct Position {
    int x, y;
    bool operator<(const Position& other) const {
        return tie(x, y) < tie(other.x, other.y);
    }
    bool operator==(const Position& other) const {
        return tie(x, y) == tie(other.x, other.y);
    }
};

void print_path(const vector<Position>& path) {
    cout << "Start: (" << path.front().x << "," << path.front().y << ")\n";
    for (size_t i = 1; i < path.size(); ++i) {
        cout << "Kill: (" << path[i].x << "," << path[i].y << "). Turn Left\n";
    }
    cout << "Arrive: (" << path.front().x << "," << path.front().y << ")\n";
}

vector<Position> get_next_moves(const Position& castle, const set<Position>& soldiers) {
    vector<Position> moves;

    // Move forward
    for (int dy = 1; dy <= 8 - castle.y; ++dy) {
        Position next_pos = {castle.x, castle.y + dy};
        if (soldiers.count(next_pos)) {
            moves.push_back(next_pos);
            break;
        }
    }

    // Move left after a kill
    for (int dx = 1; dx < castle.x; ++dx) {
        Position next_pos = {castle.x - dx, castle.y};
        if (soldiers.count(next_pos)) {
            moves.push_back(next_pos);
            break;
        }
    }

    // Check if any soldier can be killed by jumping over
    for (int dx = 1; dx < castle.x; ++dx) {
        for (int dy = 1; dy <= 8 - castle.y; ++dy) {
            Position jump_over = {castle.x, castle.y + dy};
            Position next_pos = {castle.x - dx, castle.y + dy};
            if (soldiers.count(jump_over) && !soldiers.count(next_pos)) {
                moves.push_back(next_pos);
                break;
            }
        }
    }

    return moves;
}

void find_paths(const Position& start, set<Position> soldiers, vector<Position> path, vector<vector<Position>>& all_paths) {
    Position current = path.back();

    if (current == start && path.size() > 1) {
        all_paths.push_back(path);
        return;
    }

    vector<Position> next_moves = get_next_moves(current, soldiers);
    for (const Position& move : next_moves) {
        if (!count(path.begin(), path.end(), move)) {
            soldiers.erase(move);
            path.push_back(move);
            find_paths(start, soldiers, path, all_paths);
            path.pop_back();
            soldiers.insert(move);
        }
    }
}

int main() {
    int n;
    cout << "Enter the number of soldiers: ";
    cin >> n;

    set<Position> soldiers;
    for (int i = 1; i <= n; ++i) {
        Position soldier;
        cout << "Enter coordinates for soldier " << i << ": ";
        cin >> soldier.x >> soldier.y;
        soldiers.insert(soldier);
    }

    Position castle;
    cout << "Enter the coordinates for your 'special' castle: ";
    cin >> castle.x >> castle.y;

    vector<vector<Position>> all_paths;
    vector<Position> path = {castle};
    find_paths(castle, soldiers, path, all_paths);

    cout << "Thanks. There are " << all_paths.size() << " unique paths for your 'special_castle'\n";
    for (size_t i = 0; i < all_paths.size(); ++i) {
        cout << "Path " << i + 1 << "\n=======\n";
        print_path(all_paths[i]);
    }

    return 0;
}
