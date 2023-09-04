#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define pb push_back
LL n, k, q;
LL maxSwap = 0;
vector <LL> permutationAnswer;
vector <vector<LL>> edge;
vector <LL> nextChain;
vector <vector<LL>> assignChain;

LL dfs(LL pos) {
  LL height = 0;
  nextChain[pos] = -1;
  for (auto &nx : edge[pos]) {
    LL currentHeight = dfs(nx);
    if (currentHeight > height) {
      height = currentHeight;
      nextChain[pos] = nx;
    }
  }
  maxSwap += height;
  height++;
  return height;
}

void answer(const vector <LL> ans) {
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

void dfsChain(int pos, int head = 1) {
  assignChain[head].pb(pos);
  for (auto &nx : edge[pos]) {
    if (nx == nextChain[pos]) dfsChain(nx, head);
    else dfsChain(nx, nx);
  }
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

  assignChain.resize(n + 1);
  dfsChain(1);

  permutationAnswer.resize(n + 1);
  iota(begin(permutationAnswer), end(permutationAnswer), 0);
  LL indexPermutation = 1;
  for (int i = 1; i <= n; i++) {
    if (assignChain[i].size() == 0) continue;
    LL chainLength = assignChain[i].size();
    pair<LL, LL> value = {indexPermutation, indexPermutation + chainLength - 1};
    indexPermutation = indexPermutation + chainLength;
    vector <LL> tmpAns;
    LL inversion = 0;

    for (LL j = chainLength; j >= 1; j--) {
      LL nextInversion = j - 1;
      if (inversion + nextInversion > k) {
        // insert here
        for (LL x = value.first; x <= value.first + j - 1; x++) {
          tmpAns.push_back(x);
        }
        for (LL x = chainLength - 1; x >= 0; x--) {
          if (inversion == k) break;
          inversion++;
          swap(tmpAns[x], tmpAns[x - 1]);
        }
        break;
      } else {
        tmpAns.push_back(value.first + j - 1);
      }
      inversion += nextInversion;
    }
    k -= inversion;
    for (int j = 0; j < (int) tmpAns.size(); j++) {
      permutationAnswer[assignChain[i][j]] = tmpAns[j];
    }
  }
  if(k != 0) answer({});
  // Pop front
  reverse(begin(permutationAnswer), end(permutationAnswer));
  permutationAnswer.pop_back();
  reverse(begin(permutationAnswer), end(permutationAnswer));

  answer(permutationAnswer);
}