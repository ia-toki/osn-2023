#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n, k, q;
ll maxSwap = 0;
vector <int> permutationAnswer;
vector <vector<int>> edge;
vector <int> nextChain;
int dfs(int pos) {
  int height = 0;
  nextChain[pos] = -1;
  for (auto &nx : edge[pos]) {
    int currentHeight = dfs(nx);
    if (currentHeight > height) {
      height = currentHeight;
      nextChain[pos] = nx;
    }
  }
  maxSwap += height;
  height++;
  return height;
}

void answer(const vector <int> ans) {
  if (ans.empty()) {
    cout << "TIDAK" << endl;
    exit(0);
  }
  cout << "YA" << endl;
  if (q == 0) exit(0);
  for (auto &element : ans) cout << element << " ";
  cout << endl;
  exit(0);
}

int main() {
  cin >> n >> k >> q;
  nextChain.resize(n + 1);
  edge.resize(n + 1);
  for (int i = 2; i <= n; i++) {
    int p; cin >> p;
    edge[p].push_back(i);
  }

  dfs(1);
  if (maxSwap < k) answer({}); // check if not able to answer

  permutationAnswer.resize(n + 1);
  iota(begin(permutationAnswer), end(permutationAnswer), 0);
  for (int i = n; i >= 1; i--) {
    int pos = i;
    do {
      if (nextChain[pos] == -1 || k == 0) break;
      k--;
      swap(permutationAnswer[pos], permutationAnswer[nextChain[pos]]);
      pos = nextChain[pos];
    } while(1);
  }

  // Pop front
  reverse(begin(permutationAnswer), end(permutationAnswer));
  permutationAnswer.pop_back();
  reverse(begin(permutationAnswer), end(permutationAnswer));

  answer(permutationAnswer);
}