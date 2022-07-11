#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <queue>
using namespace std;

vector<string> V; //words from wordlist05.txt
//Global variables for bfs distance, bfs predecessor, and neighboring nodes
//Should be unordered_map type
unordered_map<string, int> dist;
unordered_map<string, string> pred;
unordered_map<string, bool> visited;
unordered_map<string, vector<string> > nbrs;

//Loads a textfile into vector V
void loadTextFile(string fileName)
{
  ifstream inFile;
  string word;
  inFile.open(fileName);
  if(inFile.is_open())
  {
    while(getline(inFile, word))
    {
      if(word.length() > 0)
      {
        V.push_back(word);
      }
    }
    inFile.close();
  }
}

//Builds a graph of words with neighbors being words with a one character difference
void buildGraph()
{
  for(int i = 0; i < V.size(); i++)
  {
    string currentString = V[i];
    for(int j = 0; j < V.size(); j++)
    {
      if(i != j)
      {
        int numCharsEqual = 0;
        for(int k = 0; k < 5; k++)
        {
          if(V[j][k] == currentString[k])
          {
            numCharsEqual++;
          }
        }
        if(numCharsEqual == 4)
        {
          nbrs[currentString].push_back(V[j]);
        }
      }
    }
  }
}

//Gets the path from string s to string t and puts it in inputVec
void getPath(string s, string t, vector<string> &inputVec)
{
  if(s != t)
  {
    if(pred.find(t) == pred.end()) return;
    getPath(s, pred[t], inputVec);
    inputVec.push_back(t);
  }
  else
  {
    inputVec.push_back(s);
  }
}

//Given string s and string t, finds a word ladder path and loads it into p
void wordLadder(string s, string t, int &steps, vector<string> &p)
{
  loadTextFile("wordlist05.txt");
  buildGraph();

  queue<string> to_visit;
  to_visit.push(s);
  visited[s] = true;
  dist[s] = 0;
  
  while (!to_visit.empty()) 
  {
    string curnode = to_visit.front();
    to_visit.pop();
    for (string n : nbrs[curnode])
    {
      if (!visited[n]) 
      {
        pred[n] = curnode;
        dist[n] = 1 + dist[curnode];
        visited[n] = true;
        to_visit.push(n);
      }
    }
  }
  getPath(s, t, p);
  if(p.size() > 0) steps = p.size() - 1;
}

int main(void)
{
  int steps = 0;
  string s, t;
  vector<string> path;

  cout << "Source: ";
  cin >> s;

  cout << "Target: ";
  cin >> t;

  wordLadder(s, t, steps, path);

  if (steps == 0)
  {
      cout << "No path!\n";
  }
  else
  {
      cout << "Steps: " << steps << "\n\n";
      for (int i=0; i<path.size(); i++)
      {
          cout << path[i] << endl;
      }
  }
  return 0;
}
