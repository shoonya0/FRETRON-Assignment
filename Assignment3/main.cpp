
#include <bits/stdc++.h>
#include <vector>

using namespace std;

const int N = 9;
struct AllPath
{
  vector<string> path;
};

vector<AllPath> res;

vector<pair<int, int>> directions = {{1, 0}, {0, -1}, {-1, 0}, {0, 1}};

bool inBounds(int x, int y)
{
  return 1 <= x && x <= N && 1 <= y && y <= N;
}

string intToString(int x, int y)
{
  string res = "(";
  // Convert integer x to character
  res += (char)(x + '0');
  res += ",";
  // Convert integer y to character
  res += (char)(y + '0');
  res += ")";
  return res;
}

pair<pair<int, int>, int> castle;
// Function to find unique paths for the specialized castle
void findPaths(pair<pair<int, int>, int> castlePosition, vector<vector<bool>> &vis, vector<string> &castlePath, string dialog = "")
{
  if (castle.first == castlePosition.first)
  {
    if (!dialog.empty())
    {
      dialog.pop_back();
      dialog.pop_back();
      dialog += ". Return home";
    }
    else
    {
      dialog += "Go home to ";
      dialog += intToString(castle.first.first, castle.first.second);
    }

    castlePath.push_back(dialog);
    struct AllPath PossibleMove;
    PossibleMove.path = castlePath;
    castlePath.pop_back();

    res.push_back(PossibleMove);
    return;
  }

  if (!inBounds(castlePosition.first.first, castlePosition.first.second))
    return;

  int x = castlePosition.first.first;
  int y = castlePosition.first.second;

  // when we found an enemy
  if (vis[x][y] == true)
  {
    vis[x][y] = false;

    dialog += "Kill at ";
    dialog += intToString(x, y);
    dialog += ".Then, turn left.";

    castlePath.push_back(dialog);

    pair<pair<int, int>, int> newPosition;
    // updating the direction of the special castle
    newPosition.second = (castlePosition.second + 1) % 4;

    // moving to the updated direction by adding the direction of updated steps to the previous steps
    newPosition.first.first = castlePosition.first.first + directions[newPosition.second].first;
    newPosition.first.second = castlePosition.first.second + directions[newPosition.second].second;

    findPaths(newPosition, vis, castlePath);

    castlePath.pop_back();
    vis[x][y] = true;

    dialog.clear();

    dialog = "Jump over ";
    dialog += intToString(x, y);
    dialog += ", ";
  }

  // continously moving in the same direction until found an enemy
  castlePosition.first.first = castlePosition.first.first + directions[castlePosition.second].first;
  castlePosition.first.second = castlePosition.first.second + directions[castlePosition.second].second;

  findPaths(castlePosition, vis, castlePath, dialog);
}

void printSoldiersPos(vector<vector<bool>> &soldiers)
{
  for (auto it : soldiers)
  {
    for (auto itr : it)
      cout << itr << " ";
    cout << endl;
  }
}

void printPath()
{
  for (int i = 0; i < res.size(); i++)
  {
    cout << "Path : " << i + 1 << " -> " << endl;
    for (int j = 0; j < res[i].path.size(); j++)
    {
      cout << res[i].path[j] << endl;
    }
    cout << endl;
  }
}

int main()
{
  int numSoldiers;
  cout << "Enter the number of soldiers: ";
  cin >> numSoldiers;

  vector<vector<bool>> soldiers(N + 2, vector<bool>(N + 2, false));

  int soldirX, soldirY;
  for (int i = 0; i < numSoldiers; ++i)
  {
    cout << "Enter coordinates for soldier " << i + 1 << ": ";
    cin >> soldirX >> soldirY;
    soldiers[soldirX][soldirY] = true;
  }

  cout << "Enter the coordinates for your 'special' castle: ";
  cin >> castle.first.first >> castle.first.second;

  // printSoldiersPos(soldiers);
  // return 0;

  vector<string> castlePath;

  string s = "Starting cell: ";
  s += intToString(castle.first.first, castle.first.second);

  castlePath.push_back(s);

  for (int itr = 0; itr < directions.size(); itr++)
  {
    castle.second = itr;
    pair<pair<int, int>, int> temp = castle;
    temp.first.first = temp.first.first + directions[itr].first;
    temp.first.second = temp.first.second + directions[itr].second;
    findPaths(temp, soldiers, castlePath);
  }

  cout << "Thanks. There are " << res.size() << " unique paths for your 'special_castle'\n";
  printPath();

  return 0;
}
// testCase
// 11
// 1 1
// 8 9
// 1 9
// 4 1
// 4 2
// 4 8
// 2 6
// 5 6
// 8 2
// 5 9
// 2 8
// 1 2