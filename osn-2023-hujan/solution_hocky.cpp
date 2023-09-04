#include <bits/stdc++.h>
using namespace std;
#define pb push_back
typedef long long LL;
typedef vector <int> vi;
typedef pair<LL, LL> PLL;

const int MAX_N = 2000;
const LL MOD = 1000000007;

namespace ufds {
vector <list <int>> elements(MAX_N + 5);
int elementParents[MAX_N + 5];
int lastMerged[MAX_N + 5];
LL minimumElement[MAX_N + 5];

void init() {
  for (int i = 1; i <= MAX_N; i++) {
    minimumElement[i] = LLONG_MAX;
    elements[i].pb(i);
    elementParents[i] = i;
    lastMerged[i] = -1;
  }
}

int findpar(int pos) {
  return elementParents[pos];
};

// Log(N) amortized
bool join(int a, int b) {
  int parA = elementParents[a];
  int parB = elementParents[b];
  if (parA == parB) return 0;
  // Merge this two array elements[parA], elements[parB];
  if (elements[parA].size() < elements[parB].size()) swap(parA, parB);
  // Extend all elements of parB to parA
  for (const auto &var : elements[parB]) {
    elementParents[var] = parA;
  }
  // Constant
  elements[parA].splice(begin(elements[parA]), elements[parB]);
  return 1;
}

bool isSameElement(int a, int b) {
  return elementParents[a] == elementParents[b];
}
};

void forceQuit() {
  cout << 0 << endl;
  exit(0);
}


int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout.tie(0);
  int n; cin >> n;
  ufds::init();
  vector <vector<LL>> isi(n + 3, vector <LL> (n + 3));
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      cin >> isi[i][j];
    }
  }
  bool doneChecked[MAX_N + 5];
  for (int i = 1; i <= n; i++) {
    memset(doneChecked, 0, sizeof(doneChecked));
    vector <int> bucket;
    for (int j = 1; j <= n; j++) {
      if (isi[i][j] == -1) continue;
      if (doneChecked[j]) continue;
      int parentOfJ = ufds::elementParents[j];
      int lastCheckedRow = ufds::lastMerged[parentOfJ];
      bucket.pb(parentOfJ);
      // cout << parentOfJ << " " << lastCheckedRow << endl;
      if (lastCheckedRow == -1) continue;
      for (const auto &elementComponent : ufds::elements[parentOfJ]) {
        doneChecked[elementComponent] = 1;
        if (elementComponent == j) continue;
        // Check and fill -1
        LL curval = isi[i][j] + isi[lastCheckedRow][elementComponent] - isi[lastCheckedRow][j];
        // cout << elementComponent << " " << isi[i][elementComponent] << " " << curval << endl;
        if (curval < 0 || (isi[i][elementComponent] != -1 && isi[i][elementComponent] != curval)) {
          forceQuit();
        }
        isi[i][elementComponent] = curval;
      }
    }
    for (int j = 1; j < (int)bucket.size(); j++) {
      // cout << bucket[0] << " " << bucket[j] << endl;
      ufds::join(bucket[0], bucket[j]);
    }
    // Merge the buckets
    if (!bucket.empty()) {
      ufds::lastMerged[ufds::findpar(bucket.back())] = i;
    }
  }


  // Isi sisanya lagi dari atas
  for (int i = 1; i <= n; i++) {
    int firstFind = -1;
    for (int j = 1; j <= n; j++) {
      if (isi[i][j] > -1) {
        firstFind = j;
        break;
      }
    }
    if (firstFind == -1) continue;
    // Ini satu line -1 semua.. toxic
    int pivot = firstFind;
    firstFind = ufds::findpar(firstFind);
    // cout << pivot << " " << firstFind << endl;
    int lastCheckedRow = ufds::lastMerged[firstFind];
    // cout << i << " " << firstFind << endl;
    if (lastCheckedRow == i) continue;
    for (const auto &j : ufds::elements[firstFind]) {
      if (j == pivot) continue;
      // cout << j << " " << pivot << endl;
      LL curval = isi[i][pivot] + isi[lastCheckedRow][j] - isi[lastCheckedRow][pivot];
      // cout << curval << endl;
      if (curval < 0 || (isi[i][j] != -1 && isi[i][j] != curval)) {
        forceQuit();
      }
      isi[i][j] = curval;
    }
  }

  // for(int i = 1;i <= n;i++){
  //   for(int j = 1;j <= n;j++){
  //     cout << isi[i][j] << " ";
  //   }
  //   cout << endl;
  // }
  // cout << 1 << endl;
  vector <LL> compressedVals;
  for (int i = 1; i <= n; i++) {
    // Compressed
    bool ada = 0;
    for (int j = 1; j <= n; j++) {
      if (isi[i][j] == -1) continue;
      ada = 1;
      int head = ufds::elementParents[j];
      ufds::minimumElement[head] = min(ufds::minimumElement[head], isi[i][j]);
    }
    if (!ada) {
      cout << -1 << endl;
      return 0;
    }
  }
  for (int i = 1; i <= n; i++) {
    if (ufds::elements[i].empty()) continue;
    compressedVals.pb(ufds::minimumElement[i]);
    if (compressedVals.back() == LLONG_MAX) compressedVals.back() = -1;
    // cout << compressedVals.back() << " ";
  }
  // cout << endl;
  sort(begin(compressedVals), end(compressedVals));
  if (compressedVals[0] == -1) {
    cout << -1  << endl;
  } else {
    LL ans = 1;
    LL ans2 = 1;
    for (int i = 0; i < (int)(compressedVals.size()); i++) {
      ans = ans * (compressedVals[i] + 1) % MOD;
      ans2 = ans2 * (compressedVals[i]) % MOD;
    }
    cout << (ans - ans2 + MOD) % MOD << endl;
  }
  return 0;
}