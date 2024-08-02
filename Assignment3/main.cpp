#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <set>

using namespace std;

const int N = 8;
vector<pair<int, int>> directions = {{0, 1}, {0, -1}, {-1, 0}, {1, 0}};

struct State
{
  pair<int, int> position;
  vector<pair<int, int>> path;
};

bool inBounds(int x, int y)
{
  return x >= 1 && x <= N && y >= 1 && y <= N;
}

void printPath(const vector<pair<int, int>> &path)
{
  cout << "Start (" << path[0].first << "," << path[0].second << ")\n";
  for (size_t i = 1; i < path.size() - 1; ++i)
  {
    cout << "Kill (" << path[i].first << "," << path[i].second << "). Turn Left\n";
  }
  cout << "Jump (" << path[path.size() - 1].first << "," << path[path.size() - 1].second << ").\n";
  cout << "Arrive (" << path[0].first << "," << path[0].second << ")\n";
}

// Function to find unique paths for the specialized castle
int findPaths(pair<int, int> start, vector<pair<int, int>> &soldiers)
{
  vector<vector<bool>> board(N + 1, vector<bool>(N + 1, false));
  for (auto &soldier : soldiers)
    board[soldier.first][soldier.second] = true;

  set<vector<pair<int, int>>> uniquePaths;
  queue<State> q;
  q.push({start, {start}});

  while (!q.empty())
  {
    State current = q.front();
    q.pop();

    auto pos = current.position;
    auto path = current.path;

    // Check if we returned to start position
    if (pos == start && path.size() > 1)
    {
      uniquePaths.insert(path);
      continue;
    }

    // Attempt to move right and then left
    for (const auto &dir : directions)
    {
      int newX = pos.first + dir.first;
      int newY = pos.second + dir.second;

      if (inBounds(newX, newY) && board[newX][newY])
      {
        // Simulate killing the soldier and turning left
        board[newX][newY] = false; // Remove soldier
        vector<pair<int, int>> newPath = path;
        newPath.push_back({newX, newY});

        // Attempt to move to next cell
        int nextX = newX + dir.second; // Turn left
        int nextY = newY - dir.first;

        if (inBounds(nextX, nextY))
        {
          q.push({{nextX, nextY}, newPath});
        }

        // Re-add soldier for further searches
        board[newX][newY] = true;
      }
    }
  }

  // Print all unique paths
  int pathNum = 1;
  for (const auto &path : uniquePaths)
  {
    cout << "Path " << pathNum++ << "\n";
    printPath(path);
    cout << "======\n";
  }

  return uniquePaths.size();
}

int main()
{
  int numSoldiers;
  cout << "Enter the number of soldiers: ";
  cin >> numSoldiers;

  vector<pair<int, int>> soldiers(numSoldiers);
  for (int i = 0; i < numSoldiers; ++i)
  {
    cout << "Enter coordinates for soldier " << i + 1 << ": ";
    cin >> soldiers[i].first >> soldiers[i].second;
  }

  pair<int, int> castle;
  cout << "Enter the coordinates for your 'special' castle: ";
  cin >> castle.first >> castle.second;

  int numPaths = findPaths(castle, soldiers);
  cout << "Thanks. There are " << numPaths << " unique paths for your 'special_castle'\n";

  return 0;
}
