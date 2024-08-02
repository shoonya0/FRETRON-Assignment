#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

struct Person
{
  string name;
  int contribution;
  vector<int> apples;
};

void distributeApples(vector<int> &weights, vector<Person> &people)
{
  int totalAmount = 0;
  for (int i = 0; i < people.size(); i++)
    totalAmount += people[i].contribution;

  int totalWeight = accumulate(weights.begin(), weights.end(), 0);

  vector<double> targetWeights;
  for (int i = 0; i < people.size(); i++)
    targetWeights.push_back(((double)(people[i].contribution) / totalAmount) * totalWeight);

  sort(weights.rbegin(), weights.rend());

  for (int w = 0; w < weights.size(); w++)
  {
    // Find the person who needs the most weight to reach their target
    int personToGive = 0;
    double maxDifference = -1;
    for (int i = 0; i < people.size(); ++i)
    {
      double currentWeight = accumulate(people[i].apples.begin(), people[i].apples.end(), 0);
      double difference = targetWeights[i] - currentWeight;
      if (difference > maxDifference)
      {
        maxDifference = difference;
        personToGive = i;
      }
    }
    people[personToGive].apples.push_back(weights[w]);
  }
}

int main()
{
  vector<Person> people = {
      {"Ram", 50, {}},
      {"Sham", 30, {}},
      {"Rahim", 20, {}}};

  vector<int> weights;
  int weight;
  cout << "Enter apple weight in gram (-1 to stop): ";
  while (cin >> weight && weight != -1)
  {
    weights.push_back(weight);
    cout << "Enter apple weight in gram (-1 to stop): ";
  }

  distributeApples(weights, people);

  cout << "Distribution Result:" << endl;
  for (const auto &person : people)
  {
    cout << person.name << ": ";
    for (size_t i = 0; i < person.apples.size(); ++i)
    {
      cout << person.apples[i];
      if (i < person.apples.size() - 1)
        cout << ", ";
    }
    cout << endl;
  }
  return 0;
}
