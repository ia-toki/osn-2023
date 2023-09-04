#include <algorithm>
#include <iostream>
#include <fstream>
#include <cassert>
#include <iomanip>
#include <vector>
#include <cmath>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define rrep(i, a, b) for(int i = a; i > (b); --i)
#define trav(a, x) for(auto& a : x)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define pb push_back

ifstream input, judgeOut, contestantOut;
typedef long long LL;
typedef long double LD;

void ac() {
  cout << "AC" << endl;
  exit(0);
}

void wa(string reason = "Wrong answer") {
  cout << "WA" << endl;
  cerr << reason << endl;
  exit(0);
}

template <class T>
void wa(string reason, T actual, T expected) {
  cout << "WA" << endl;
  cerr << reason << endl;
  cerr << "Actual: " << actual << endl;
  cerr << "Expected: " << expected << endl;
  exit(0);
}

void ok(double score) {
  cout << "OK" << endl;
  cout << fixed << setprecision(10) << score << endl;
}

void checkAC() {
  string dummy;
  if (contestantOut >> dummy) wa("Output after given answer");
  else ac();
}

void checkOK(double score) {
  string dummy;
  if (contestantOut >> dummy) wa("Output after given answer");
  else ok(score);
}

namespace contestant {
string ans;
vector <int> permutationAnswer;
long long K = 0;
}

template <class T>
inline void getInput(T &a) { if (!(contestantOut >> a)) wa("Input can't be parsed"); }

int main(int argc, char** argv) {

  input = ifstream(argv[1]);
  judgeOut = ifstream(argv[2]);
  contestantOut = ifstream(argv[3]);

  int N; input >> N;
  long long K; input >> K;
  int Q; input >> Q;

  vector<int> P(N + 1);
  for (int i = 2 ; i <= N ; i++) {
    input >> P[i];
  }

  string ans; judgeOut >> ans;
  getInput(contestant::ans);

  if (ans != contestant::ans) wa("Answer is not the same", contestant::ans, ans);
  if (Q == 0) checkAC();
  if (ans == "TIDAK") checkAC();

  vector<int> A(N + 1);
  for (int i = 1; i <= N; i++) {
    getInput(A[i]);
  }
  vector<vector<int>> chld(N + 1);
  for (int i = 2 ; i <= N ; i++) {
    input >> P[i];
    chld[P[i]].push_back(i);
  }

  for (int i = N; i >= 1; i--) {
    int j = i;
    while (!chld[j].empty()) {
      int pivot = j;
      for (int nex : chld[j]) {
        if (A[nex] < A[pivot]) {
          pivot = nex;
        }
      }

      if (pivot == j) break;
      swap(A[j], A[pivot]);
      contestant::K++;
      j = pivot;
    }
  }

  if (contestant::K != K) wa("K count is different", contestant::K, K);

  checkAC();

  return 0;
}