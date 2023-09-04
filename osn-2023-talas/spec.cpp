#include <bits/stdc++.h>
#include <tcframe/spec.hpp>
#include "helper/treeGenerator.h"

using namespace std;
using namespace tcframe;
#define fi first
#define se second
#define pb push_back
typedef long long ll;
typedef long long LL;
typedef pair<LL, LL> PLL;


namespace consFull {
constexpr int N = 1e5;
constexpr ll K = 1e18L;
constexpr int Q = 1;
}

namespace cons1 {
constexpr int N = 7;
constexpr ll K = 7;
constexpr int Q = 1;
const vector <int> P = {1, 1, 3, 2, 5, 2};
}

namespace cons2 {
constexpr ll K = 0;
}

namespace cons3 {
constexpr int N = 8;
}

namespace cons4 {
constexpr int Q = 0;
// Line Tree
}

namespace cons5 {
constexpr int Q = 0;
// One Branch Tree
}

namespace cons6 {
constexpr int Q = 0;
}

namespace cons7 {
constexpr ll K = 1e5;
// Line Tree
}

namespace cons8 {
// Line Tree
}

namespace cons9 {
constexpr ll K = 1e5;
}

namespace solution {
int n;
ll ans = 0;
vector <vector<int>> edge;
void treeInit(const treeGenerator::Tree &tree) {
  n = tree.size();
  ans = 0;
  edge.assign(n, vector<int>());
  for (int i = 0; i < n; i++) {
    if (tree.p[i] == -1) continue;
    edge[tree.p[i]].pb(i);
  }
}

int dfs(int pos) {
  int height = 0;
  for (auto &nx : edge[pos]) {
    height = max(height, dfs(nx));
  }
  ans += height;
  ++height;
  return height;
}

ll countMaxHeapSwap(const treeGenerator::Tree &tree) {
  treeInit(tree);
  dfs(0);
  return ans;
}
}

class ProblemSpec : public BaseProblemSpec {
 protected:
  ll N, K;
  int Q;
  vector <int> P;

  string ANS;
  vector <int> PERMUTATION_ANSWER;

  void InputFormat() {
    LINE(N, K, Q);
    LINE(P % SIZE(N - 1));
  }

  void OutputFormat1() {
    LINE(ANS);
    LINE(PERMUTATION_ANSWER % SIZE(N));
  }

  void OutputFormat2() {
    LINE(ANS);
  }

  void GradingConfig() {
    TimeLimit(2);
    MemoryLimit(512);
  }

  void StyleConfig() {
    CustomScorer();
  }

  void Constraints() {
    CONS(1 <= N && N <= consFull::N);
    CONS(0 <= K && K <= consFull::K);
    CONS(0 <= Q && Q <= consFull::Q);
    CONS(N - 1 == P.size());
    CONS(validTree(P));
  }

  void Subtask1() {
    Points(7);
    CONS(N == cons1::N); CONS(K == cons1::K); CONS(Q == cons1::Q);
    CONS(P == cons1::P);
  }

  void Subtask2() {
    Points(7);
    CONS(K == cons2::K);
  }

  void Subtask3() {
    Points(6);
    CONS(1 <= N && N <= cons3::N);
  }

  void Subtask4() {
    Points(6);
    CONS(0 <= Q && Q <= cons4::Q);
    CONS(isLineTree(P));
  }

  void Subtask5() {
    Points(8);
    CONS(0 <= Q && Q <= cons5::Q);
    CONS(isOneBranchTree(P));
  }

  void Subtask6() {
    Points(9);
    CONS(0 <= Q && Q <= cons6::Q);
  }

  void Subtask7() {
    Points(11);
    CONS(0 <= K && K <= cons7::K);
    CONS(isLineTree(P));
  }

  void Subtask8() {
    Points(12);
    CONS(isLineTree(P));
  }

  void Subtask9() {
    Points(17);
    CONS(0 <= K && K <= cons9::K);
  }

  void Subtask10() {
    Points(17);
  }

 private:
  template <class T>
  bool eachElementBetween(const vector<T> &collection, const T low, const T high) {
    for (const T &element : collection) {
      if (!(low <= element && element <= high)) {
        return false;
      }
    }
    return true;
  }

  template <class T>
  bool eachElementOf(const vector<T> &collection, const set<T> &elementSet) {
    for (const T &element : collection) {
      if (!(elementSet.count(element))) {
        return false;
      }
    }
    return true;
  }

  bool validTree(const vector<int> &parents) {
    for (int i = 2; i <= N; i++) {
      if (!(1 <= parents[i - 2] && parents[i - 2] < i)) return false;
    }
    return true;
  }

  bool isLineTree(const vector<int> &parents) {
    return isTreeBranchCount(parents, 0);
  }

  bool isOneBranchTree(const vector<int> &parents) {
    return isTreeBranchCount(parents, 1);
  }

  bool isTreeBranchCount(const vector <int> &parents, const int matchBranchCount) {
    int n = parents.size(); n += 1;
    int treeBranchCount = 0;
    for (int i = 2; i <= n; i++) {
      if (parents[i - 2] != i - 1) {
        treeBranchCount++;
      }
    }
    return treeBranchCount == matchBranchCount;
  }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
 protected:
  void SampleTestCase1() {
    Subtasks({3, 9, 10});
    Input(loadManualFromFile("manual/sample01.in"));
    Output(loadManualFromFile("manual/sample01.out"));
  }

  void SampleTestCase2() {
    Subtasks({3, 6, 9, 10});
    Input(loadManualFromFile("manual/sample02.in"));
    Output(loadManualFromFile("manual/sample02.out"));
  }

  void SampleTestCase3() {
    Subtasks({3, 9, 10});
    Input(loadManualFromFile("manual/sample03.in"));
    Output(loadManualFromFile("manual/sample03.out"));
  }

  void BeforeTestCase() {
    P.clear();
  }



  void TestGroup1() {
    Subtasks({1, 3, 9, 10});
    CASE(N = cons1::N; K = cons1::K; Q = cons1::Q; P = cons1::P);
  }

  void TestGroup2() {
    Subtasks({2, 3, 9, 10});
    CASE(treeGenerator::Tree tree(cons3::N); tree.get(P); N = tree.size(); K = 0; Q = 1);
    CASE(treeGenerator::Tree tree(rnd.nextInt(1LL * cons3::N * 3 / 4, cons3::N)); tree.get(P); N = tree.size(); K = 0; Q = 1);
  }


  void TestGroup3() {
    Subtasks({2, 9, 10});
    CASE(treeGenerator::Tree tree(consFull::N); tree.get(P); N = tree.size(); K = 0; Q = 1);
    CASE(treeGenerator::Tree tree; tree.lowhighMaxDegree(consFull::N - 1, 10, 0, 0.2, 0); tree.get(P); N = tree.size(); K = 0; Q = 1);
    CASE(treeGenerator::Tree tree; tree.knary(20000, 2, 0); tree.chain(50000, 10000); tree.get(P); N = tree.size(); K = 0; Q = 1);
    CASE(treeGenerator::Tree tree(rnd.nextInt(1LL * consFull::N * 3 / 4, consFull::N)); tree.get(P); N = tree.size(); K = 0; Q = 1);
    CASE(treeGenerator::Tree tree; tree.knary(rnd.nextInt(1LL * consFull::N * 99 / 100, consFull::N), 9, 0); tree.get(P); N = tree.size(); K = 0; Q = 1);
    CASE(treeGenerator::Tree tree; tree.silkworm(rnd.nextInt(1LL * consFull::N * 99 / 100, consFull::N), 0); tree.get(P); N = tree.size(); K = 0; Q = 1);
    CASE(treeGenerator::Tree tree(0); tree.flower(rnd.nextInt(1LL * consFull::N * 99 / 100, consFull::N), -1); tree.get(P); N = tree.size(); K = 0; Q = 1);
    CASE(treeGenerator::Tree tree; tree.halvingDegree(rnd.nextInt(1LL * consFull::N * 99 / 100, consFull::N), 0); tree.get(P); N = tree.size(); K = 0; Q = 1);
    CASE(treeGenerator::Tree tree; tree.distinctDegree(rnd.nextInt(1LL * consFull::N * 99 / 100, consFull::N), 0); tree.get(P); N = tree.size(); K = 0; Q = 1);
  }

  void TestGroup4() {
    Subtasks({3, 5, 6, 9, 10});
    CASE(treeGenerator::Tree tree; tree.chain(4, 0); tree.chain(3, 2); tree.get(P); N = tree.size(); K = solution::countMaxHeapSwap(tree); Q = 0);
    CASE(treeGenerator::Tree tree; tree.chain(5, 0); tree.chain(2, 0); tree.get(P); N = tree.size(); K = solution::countMaxHeapSwap(tree) - 1; Q = 0);
    CASE(treeGenerator::Tree tree; tree.chain(5, 0); tree.chain(2, 1); tree.get(P); N = tree.size(); K = solution::countMaxHeapSwap(tree) + 1; Q = 0);
    CASE(treeGenerator::Tree tree; tree.chain(1, 0); tree.chain(4, 0); tree.get(P); N = tree.size(); K = solution::countMaxHeapSwap(tree) + 1; Q = 0);
    CASE(treeGenerator::Tree tree; tree.chain(1, 0); tree.chain(4, 0); tree.get(P); N = tree.size(); K = solution::countMaxHeapSwap(tree) - 1; Q = 0);
    CASE(treeGenerator::Tree tree; tree.chain(1, 0); tree.chain(4, 0); tree.get(P); N = tree.size(); K = solution::countMaxHeapSwap(tree); Q = 0);
  }

  void TestGroup5() {
    Subtasks({3, 4, 6, 7, 8, 9, 10});
    CASE(treeGenerator::Tree tree; tree.chain(3, 0); tree.get(P); N = tree.size(); K = solution::countMaxHeapSwap(tree); Q = 0);
    CASE(treeGenerator::Tree tree; tree.chain(cons3::N - 1, 0); tree.get(P); N = tree.size(); K = solution::countMaxHeapSwap(tree) - 1; Q = 0);
    CASE(treeGenerator::Tree tree; tree.chain(cons3::N - 2, 0); tree.get(P); N = tree.size(); K = solution::countMaxHeapSwap(tree) + 1; Q = 0);
  }

  void TestGroup6() {
    Subtasks({3, 9, 10});
    CASE(treeGenerator::Tree tree; tree.knary(cons3::N, 2, 0); tree.get(P); N = tree.size(); K = 10; Q = 1);
    CASE(treeGenerator::Tree tree; tree.knary(cons3::N, 3, 0); tree.get(P); N = tree.size(); K = 3; Q = 1);

    CASE(treeGenerator::Tree tree; tree.lowhighMaxDegree(cons3::N - 1, 10, 0, 0.2, 0); tree.get(P); N = tree.size(); K = solution::countMaxHeapSwap(tree); Q = 1);
    CASE(treeGenerator::Tree tree; tree.knary(3, 2, 0); tree.chain(5, 2); tree.get(P); N = tree.size(); K = solution::countMaxHeapSwap(tree); Q = 1);
    CASE(treeGenerator::Tree tree(rnd.nextInt(1LL * cons3::N * 3 / 4, cons3::N)); tree.get(P); N = tree.size(); K = solution::countMaxHeapSwap(tree); Q = 1);
    CASE(treeGenerator::Tree tree; tree.knary(rnd.nextInt(cons3::N / 2, cons3::N), cons3::N / 3, 0); tree.get(P); N = tree.size(); K = solution::countMaxHeapSwap(tree); Q = 1);
    CASE(treeGenerator::Tree tree; tree.silkworm(rnd.nextInt(cons3::N / 2, cons3::N - 1), 0); tree.get(P); N = tree.size(); K = solution::countMaxHeapSwap(tree); Q = 1);
    CASE(treeGenerator::Tree tree(0); tree.flower(rnd.nextInt(cons3::N / 2, cons3::N), -1); tree.get(P); N = tree.size(); K = solution::countMaxHeapSwap(tree); Q = 1);
    CASE(treeGenerator::Tree tree; tree.halvingDegree(rnd.nextInt(cons3::N / 2, cons3::N), 0); tree.get(P); N = tree.size(); K = solution::countMaxHeapSwap(tree); Q = 1);
    CASE(treeGenerator::Tree tree; tree.distinctDegree(rnd.nextInt(cons3::N / 2, cons3::N), 0); tree.get(P); N = tree.size(); K = solution::countMaxHeapSwap(tree); Q = 1);



    CASE(treeGenerator::Tree tree; tree.lowhighMaxDegree(cons3::N - 1, 10, 0, 0.2, 0); tree.get(P); N = tree.size(); K = solution::countMaxHeapSwap(tree); Q = 1);
    CASE(treeGenerator::Tree tree; tree.knary(3, 2, 0); tree.chain(5, 2); tree.get(P); N = tree.size(); K = solution::countMaxHeapSwap(tree); Q = 1);
    CASE(treeGenerator::Tree tree(rnd.nextInt(1LL * cons3::N * 3 / 4, cons3::N)); tree.get(P); N = tree.size();
         K = randomWithinFraction({1, 2}, {3, 4}, solution::countMaxHeapSwap(tree)); Q = 1);
    CASE(treeGenerator::Tree tree; tree.knary(rnd.nextInt(cons3::N / 2, cons3::N), cons3::N / 3, 0); tree.get(P); N = tree.size(); K = randomWithinFraction({2, 10}, {4, 10}, solution::countMaxHeapSwap(tree)); Q = 1);
    CASE(treeGenerator::Tree tree; tree.silkworm(rnd.nextInt(cons3::N / 2, cons3::N - 1), 0); tree.get(P); N = tree.size();
         K = randomWithinFraction({2, 10}, {8, 10}, solution::countMaxHeapSwap(tree)); Q = 1);
    CASE(treeGenerator::Tree tree; tree.silkworm(cons3::N - 1, 0); tree.get(P); N = tree.size();
         K = randomWithinFraction({6, 10}, {9, 10}, solution::countMaxHeapSwap(tree)); Q = 1);
    CASE(treeGenerator::Tree tree; tree.halvingDegree(rnd.nextInt(cons3::N / 2, cons3::N), 0); tree.get(P); N = tree.size();
         K = randomWithinFraction({6, 10}, {8, 10}, solution::countMaxHeapSwap(tree)); Q = 1);
    CASE(treeGenerator::Tree tree; tree.distinctDegree(rnd.nextInt(cons3::N / 2, cons3::N), 0); tree.get(P); N = tree.size();
         K = randomWithinFraction({4, 10}, {6, 10}, solution::countMaxHeapSwap(tree));  Q = 1);

    CASE(treeGenerator::Tree tree; tree.lowhighMaxDegree(cons3::N - 1, 10, 0, 0.2, 0); tree.get(P); N = tree.size(); K = solution::countMaxHeapSwap(tree) - 2; Q = 1);
    CASE(treeGenerator::Tree tree; tree.knary(3, 2, 0); tree.chain(5, 1); tree.get(P); N = tree.size(); K = solution::countMaxHeapSwap(tree) - 1; Q = 1);
    CASE(treeGenerator::Tree tree(rnd.nextInt(1LL * cons3::N * 3 / 4, cons3::N - 1)); tree.get(P); N = tree.size(); K = solution::countMaxHeapSwap(tree) - 2; Q = 1);
    CASE(treeGenerator::Tree tree; tree.knary(rnd.nextInt(cons3::N / 2, cons3::N - 1), cons3::N / 3, 0); tree.get(P); N = tree.size(); K = solution::countMaxHeapSwap(tree); Q = 1);
    CASE(treeGenerator::Tree tree; tree.silkworm(rnd.nextInt(cons3::N / 2, cons3::N - 1), 0); tree.get(P); N = tree.size(); K = solution::countMaxHeapSwap(tree) + 2; Q = 1);
    CASE(treeGenerator::Tree tree(0); tree.flower(rnd.nextInt(cons3::N / 2, cons3::N), -1); tree.get(P); N = tree.size(); K = solution::countMaxHeapSwap(tree) + 1; Q = 1);
    CASE(treeGenerator::Tree tree; tree.halvingDegree(rnd.nextInt(cons3::N / 2, cons3::N - 1), 0); tree.get(P); N = tree.size(); K = solution::countMaxHeapSwap(tree) + 1; Q = 1);
    CASE(treeGenerator::Tree tree; tree.distinctDegree(rnd.nextInt(cons3::N / 2, cons3::N - 1), 0); tree.get(P); N = tree.size(); K = solution::countMaxHeapSwap(tree) + 1; Q = 1);
  }

  void TestGroup7() {
    Subtasks({3, 10});
    CASE(treeGenerator::Tree tree; tree.knary(cons3::N, 2, 0); tree.get(P); N = tree.size(); K = consFull::K; Q = 1);
    CASE(treeGenerator::Tree tree; tree.knary(cons3::N, 2, 0); tree.get(P); N = tree.size(); K = consFull::K; Q = 1);
    CASE(treeGenerator::Tree tree(0); tree.flower(rnd.nextInt(cons3::N / 2, cons3::N), -1); tree.get(P);
         N = tree.size(); K = cons9::K + 1; Q = 1);
    CASE(treeGenerator::Tree tree; tree.halvingDegree(rnd.nextInt(cons3::N / 2, cons3::N), 0); tree.get(P);
         N = tree.size(); K = cons9::K + 1; Q = 1);
    CASE(treeGenerator::Tree tree; tree.distinctDegree(rnd.nextInt(cons3::N / 2, cons3::N), 0); tree.get(P);
         N = tree.size(); K = cons9::K + 1; Q = 1);
  }

  void TestGroup8() {
    Subtasks({4, 6, 8, 10});
    CASE(treeGenerator::Tree tree;
         tree.chain(consFull::N - 1, 0);
         tree.get(P);
         N = tree.size();
         LL cursol = solution::countMaxHeapSwap(tree);
         K = randomWithinFraction({1, 2}, {1, 1}, cursol);
         Q = 0);

    CASE(treeGenerator::Tree tree(0);
         tree.chain(randomWithinFraction({4, 5}, {1, 1}, consFull::N), -1);
         tree.get(P);
         N = tree.size();
         LL cursol = solution::countMaxHeapSwap(tree);
         K = randomWithinFraction({1, 2}, {3, 4}, cursol);
         Q = 0);

    CASE(treeGenerator::Tree tree(0);
         tree.chain(randomWithinFraction({4, 5}, {1, 1}, consFull::N), -1);
         tree.get(P);
         N = tree.size();
         LL cursol = solution::countMaxHeapSwap(tree);
         K = cursol;
         Q = 0);

    CASE(treeGenerator::Tree tree(0);
         tree.chain(randomWithinFraction({4, 5}, {1, 1}, consFull::N), -1);
         tree.get(P);
         N = tree.size();
         LL cursol = solution::countMaxHeapSwap(tree);
         K = cursol + 1;
         Q = 0);

    CASE(treeGenerator::Tree tree(0);
         tree.chain(randomWithinFraction({4, 5}, {1, 1}, consFull::N), -1);
         tree.get(P);
         N = tree.size();
         LL cursol = solution::countMaxHeapSwap(tree);
         K = cursol + 2;
         Q = 0);

    CASE(treeGenerator::Tree tree; tree.chain(consFull::N - 4, 0); tree.get(P); N = tree.size();
         K = consFull::K; Q = 0);


    CASE(treeGenerator::Tree tree;
         tree.chain(consFull::N - 1, 0);
         tree.get(P);
         N = tree.size();
         LL cursol = solution::countMaxHeapSwap(tree);
         K = randomWithinFraction({1, 2}, {1, 1}, cursol);
         Q = 0);

    CASE(treeGenerator::Tree tree(0);
         tree.chain(randomWithinFraction({4, 5}, {1, 1}, consFull::N), -1);
         tree.get(P);
         N = tree.size();
         LL cursol = solution::countMaxHeapSwap(tree);
         K = randomWithinFraction({1, 2}, {3, 4}, cursol);
         Q = 0);

    CASE(treeGenerator::Tree tree(0);
         tree.chain(randomWithinFraction({4, 5}, {1, 1}, consFull::N), -1);
         tree.get(P);
         N = tree.size();
         LL cursol = solution::countMaxHeapSwap(tree);
         K = randomWithinFraction({2, 10}, {4, 10}, cursol);
         Q = 0);

    CASE(treeGenerator::Tree tree(0);
         tree.chain(randomWithinFraction({4, 5}, {1, 1}, consFull::N), -1);
         tree.get(P);
         N = tree.size();
         LL cursol = solution::countMaxHeapSwap(tree);
         K = randomWithinFraction({1, 10}, {2, 10}, cursol);
         Q = 0);

    CASE(treeGenerator::Tree tree(0);
         tree.chain(randomWithinFraction({4, 5}, {1, 1}, consFull::N), -1);
         tree.get(P);
         N = tree.size();
         LL cursol = solution::countMaxHeapSwap(tree);
         K = randomWithinFraction({1, 10}, {2, 10}, cursol);
         Q = 0);

    CASE(treeGenerator::Tree tree; tree.chain(consFull::N - 4, 0); tree.get(P); N = tree.size();
         K = consFull::K; Q = 0);
  }


  void TestGroup9() {
    Subtasks({5, 6, 10});
    CASE(treeGenerator::Tree tree(0);
         LL chain1 = randomWithinFraction({1, 2}, {1, 1}, consFull::N) - 1;
         LL chain2 = consFull::N - chain1;
         tree.chain(chain1, -1);
         tree.chain(chain2, rnd.nextLongLong(0, chain1 - 2)); tree.get(P);
         N = tree.size(); K = solution::countMaxHeapSwap(tree); Q = 0);

    CASE(treeGenerator::Tree tree(0);
         LL chain1 = randomWithinFraction({3, 4}, {1, 1}, consFull::N) - 1;
         LL chain2 = consFull::N - chain1;
         tree.chain(chain1, -1);
         tree.chain(chain2, rnd.nextLongLong(0, chain1 - 2)); tree.get(P);
         N = tree.size(); K = solution::countMaxHeapSwap(tree) - 1; Q = 0);
    CASE(treeGenerator::Tree tree(0);
         LL chain1 = randomWithinFraction({1, 10}, {3, 10}, consFull::N) - 1;
         LL chain2 = consFull::N - chain1;
         tree.chain(chain1, -1);
         tree.chain(chain2, rnd.nextLongLong(0, chain1 - 2)); tree.get(P);
         N = tree.size(); K = solution::countMaxHeapSwap(tree) + 1; Q = 0);
    CASE(treeGenerator::Tree tree(0);
         LL chain1 = randomWithinFraction({1, 10}, {3, 10}, consFull::N) - 1;
         LL chain2 = consFull::N - chain1;
         tree.chain(chain1, -1);
         tree.chain(chain2, 0); tree.get(P);
         N = tree.size(); K = solution::countMaxHeapSwap(tree); Q = 0);
    CASE(treeGenerator::Tree tree(0);
         LL chain1 = randomWithinFraction({7, 10}, {10, 10}, consFull::N) - 1;
         LL chain2 = consFull::N - chain1;
         tree.chain(chain1, -1);
         tree.chain(chain2, 0); tree.get(P);
         N = tree.size(); K = solution::countMaxHeapSwap(tree) + 1; Q = 0);
    CASE(treeGenerator::Tree tree(0);
         LL chain1 = randomWithinFraction({7, 10}, {10, 10}, consFull::N) - 1;
         LL chain2 = consFull::N - chain1;
         tree.chain(chain1, -1);
         tree.chain(chain2, chain1 - 2); tree.get(P);
         N = tree.size(); K = solution::countMaxHeapSwap(tree); Q = 0);
    CASE(treeGenerator::Tree tree(0);
         LL chain1 = randomWithinFraction({1, 10}, {3, 10}, consFull::N) - 1;
         LL chain2 = consFull::N - chain1;
         tree.chain(chain1, -1);
         tree.chain(chain2, chain1 - 2); tree.get(P);
         N = tree.size(); K = solution::countMaxHeapSwap(tree) + 1; Q = 0);
    CASE(treeGenerator::Tree tree(0);
         LL chain1 = randomWithinFraction({3, 10}, {7, 10}, consFull::N) - 1;
         LL chain2 = consFull::N - chain1;
         tree.chain(chain1, -1);
         tree.chain(chain2, chain1 - 2); tree.get(P);
         N = tree.size(); K = consFull::K; Q = 0);

    CASE(treeGenerator::Tree tree(0);
         LL chain1 = randomWithinFraction({3, 10}, {7, 10}, consFull::N) - 1;
         LL chain2 = consFull::N - chain1;
         tree.chain(chain1, -1);
         tree.chain(chain2, chain1 - 2); tree.get(P);
         N = tree.size(); K = cons9::K + 1; Q = 0);


    CASE(treeGenerator::Tree tree(0);
         LL chain1 = randomWithinFraction({7, 10}, {10, 10}, consFull::N) - 1;
         LL chain2 = consFull::N - chain1;
         tree.chain(chain1, -1);
         tree.chain(chain2, 0); tree.get(P);
         N = tree.size();
         LL cursol = solution::countMaxHeapSwap(tree);
         K = randomWithinFraction({1, 10}, {2, 10}, cursol);
         Q = 0);
    CASE(treeGenerator::Tree tree(0);
         LL chain1 = randomWithinFraction({7, 10}, {10, 10}, consFull::N) - 1;
         LL chain2 = consFull::N - chain1;
         tree.chain(chain1, -1);
         tree.chain(chain2, chain1 - 2); tree.get(P);
         N = tree.size();
         LL cursol = solution::countMaxHeapSwap(tree);
         K = randomWithinFraction({2, 10}, {4, 10}, cursol);
         Q = 0);
    CASE(treeGenerator::Tree tree(0);
         LL chain1 = randomWithinFraction({1, 10}, {3, 10}, consFull::N) - 1;
         LL chain2 = consFull::N - chain1;
         tree.chain(chain1, -1);
         tree.chain(chain2, chain1 - 2); tree.get(P);
         N = tree.size();
         LL cursol = solution::countMaxHeapSwap(tree);
         K = randomWithinFraction({4, 10}, {7, 10}, cursol);
         Q = 0);
    CASE(treeGenerator::Tree tree(0);
         LL chain1 = randomWithinFraction({3, 10}, {7, 10}, consFull::N) - 1;
         LL chain2 = consFull::N - chain1;
         tree.chain(chain1, -1);
         tree.chain(chain2, chain1 - 2); tree.get(P);
         N = tree.size();
         LL cursol = solution::countMaxHeapSwap(tree);
         K = randomWithinFraction({8, 10}, {9, 10}, cursol);
         Q = 0);
  }


  void TestGroup10() {
    Subtasks({6, 9, 10});
    CASE(treeGenerator::Tree tree; tree.knary(consFull::N, 2, 0); tree.get(P); N = tree.size(); K = 10; Q = 0);
    CASE(treeGenerator::Tree tree; tree.knary(consFull::N, 3, 0); tree.get(P); N = tree.size(); K = 3; Q = 0);

    CASE(treeGenerator::Tree tree; tree.knary(consFull::N, 2, 0); tree.get(P); N = tree.size();
         K = solution::countMaxHeapSwap(tree); Q = 0);
    CASE(treeGenerator::Tree tree; tree.knary(consFull::N, 3, 0); tree.get(P); N = tree.size();
         K = solution::countMaxHeapSwap(tree) + 1; Q = 0);

    CASE(treeGenerator::Tree tree; tree.lowhighMaxDegree(consFull::N - 1, 10, 0, 0.2, 0); tree.get(P); N = tree.size(); K = solution::countMaxHeapSwap(tree); Q = 0);
    CASE(treeGenerator::Tree tree;
         tree.knary(rnd.nextInt(consFull::N / 2, consFull::N), consFull::N / 3, 0); tree.get(P);
         N = tree.size(); K = solution::countMaxHeapSwap(tree); Q = 0);
    CASE(treeGenerator::Tree tree(0); tree.flower(rnd.nextInt(consFull::N / 2, consFull::N), -1); tree.get(P);
         N = tree.size(); K = solution::countMaxHeapSwap(tree); Q = 0);
    CASE(treeGenerator::Tree tree; tree.halvingDegree(rnd.nextInt(consFull::N / 2, consFull::N), 0); tree.get(P);
         N = tree.size(); K = solution::countMaxHeapSwap(tree); Q = 0);
    CASE(treeGenerator::Tree tree; tree.distinctDegree(rnd.nextInt(consFull::N / 2, consFull::N), 0); tree.get(P);
         N = tree.size(); K = solution::countMaxHeapSwap(tree); Q = 0);



    CASE(treeGenerator::Tree tree; tree.lowhighMaxDegree(consFull::N - 1, 10, 0, 0.2, 0); tree.get(P); N = tree.size();
         LL cursol = solution::countMaxHeapSwap(tree);
         K = randomWithinFraction({2, 10}, {4, 10}, cursol);
         Q = 0);
    CASE(treeGenerator::Tree tree;
         tree.knary(rnd.nextInt(consFull::N / 2, consFull::N), consFull::N / 3, 0); tree.get(P);
         N = tree.size();
         LL cursol = solution::countMaxHeapSwap(tree);
         K = randomWithinFraction({4, 10}, {7, 10}, cursol);
         Q = 0);
    CASE(treeGenerator::Tree tree; tree.halvingDegree(rnd.nextInt(consFull::N / 2, consFull::N), 0); tree.get(P);
         N = tree.size();
         LL cursol = solution::countMaxHeapSwap(tree);
         K = randomWithinFraction({6, 10}, {9, 10}, cursol);
         Q = 0);
    CASE(treeGenerator::Tree tree; tree.distinctDegree(rnd.nextInt(consFull::N / 2, consFull::N), 0); tree.get(P);
         N = tree.size();
         LL cursol = solution::countMaxHeapSwap(tree);
         K = randomWithinFraction({5, 10}, {8, 10}, cursol);
         Q = 0);

    CASE(treeGenerator::Tree tree;
         tree.knary(rnd.nextInt(consFull::N / 2, consFull::N), consFull::N / 3, 0); tree.get(P);
         N = tree.size(); K = solution::countMaxHeapSwap(tree) + 1; Q = 0);
    CASE(treeGenerator::Tree tree; tree.lowhighMaxDegree(consFull::N - 1, 10, 0, 0.2, 0); tree.get(P); N = tree.size(); K = solution::countMaxHeapSwap(tree) - 2; Q = 0);
    CASE(treeGenerator::Tree tree(0); tree.flower(rnd.nextInt(consFull::N / 2, consFull::N), -1); tree.get(P);
         N = tree.size(); K = solution::countMaxHeapSwap(tree) + 1; Q = 0);
    CASE(treeGenerator::Tree tree; tree.halvingDegree(rnd.nextInt(consFull::N / 2, consFull::N), 0); tree.get(P);
         N = tree.size(); K = solution::countMaxHeapSwap(tree) + 1; Q = 0);
    CASE(treeGenerator::Tree tree; tree.distinctDegree(rnd.nextInt(consFull::N / 2, consFull::N), 0); tree.get(P);
         N = tree.size(); K = solution::countMaxHeapSwap(tree) + 1; Q = 0);
    CASE(treeGenerator::Tree tree;
         tree.knary(1000, consFull::N, 0); tree.get(P);
         N = tree.size(); K = solution::countMaxHeapSwap(tree) + 1; Q = 0);


  }


  void TestGroup11() {
    Subtasks({6, 10});
    CASE(treeGenerator::Tree tree;
         tree.knary(1LL * consFull::N * 3 / 4, 2, 0);
         tree.chain(1LL * consFull::N / 4, rnd.nextInt(consFull::N / 2));
         tree.get(P);
         N = tree.size(); K = solution::countMaxHeapSwap(tree); Q = 0);

    CASE(treeGenerator::Tree tree(rnd.nextInt(1LL * consFull::N * 3 / 4, consFull::N)); tree.get(P);
         N = tree.size(); K = solution::countMaxHeapSwap(tree); Q = 0);
    CASE(treeGenerator::Tree tree; tree.silkworm(rnd.nextInt(consFull::N / 2, consFull::N), 0); tree.get(P);
         N = tree.size(); K = solution::countMaxHeapSwap(tree); Q = 0);


    CASE(treeGenerator::Tree tree; tree.knary(20000, 2, 0); tree.chain(50000, 10000); tree.get(P);
         N = tree.size();
         K = solution::countMaxHeapSwap(tree) + 1; Q = 0);
    CASE(treeGenerator::Tree tree; tree.knary(20000, 2, 0); tree.chain(50000, 10000); tree.get(P);
         N = tree.size();
         K = solution::countMaxHeapSwap(tree); Q = 0);
    CASE(treeGenerator::Tree tree(rnd.nextInt(1LL * consFull::N * 3 / 4, consFull::N)); tree.get(P);
         N = tree.size(); K = solution::countMaxHeapSwap(tree) - 2; Q = 0);

    CASE(treeGenerator::Tree tree; tree.silkworm(rnd.nextInt(consFull::N / 2, consFull::N), 0); tree.get(P);
         N = tree.size(); K = solution::countMaxHeapSwap(tree) + 2; Q = 0);

    CASE(treeGenerator::Tree tree(0);
         tree.chain(rnd.nextInt(1LL * consFull::N / 4, consFull::N / 2), -1);
         tree.forkUniform(consFull::N - tree.size(), sqrt(tree.size()), tree.size() - 1);
         tree.get(P);
         N = tree.size(); K = solution::countMaxHeapSwap(tree); Q = 0);

    CASE(treeGenerator::Tree tree(0);
         tree.chain(rnd.nextInt(1LL * consFull::N / 4, consFull::N / 2), -1);
         tree.forkUniform(consFull::N - tree.size(), sqrt(tree.size()), tree.size() - 1);
         tree.get(P);
         N = tree.size(); K = solution::countMaxHeapSwap(tree) + 1; Q = 0);

    CASE(treeGenerator::Tree tree(0);
         tree.chain(rnd.nextInt(1LL * consFull::N / 4, consFull::N / 2), -1);
         tree.forkSequentialLinearSequence(consFull::N - tree.size(), tree.size() - 1);
         tree.get(P);
         N = tree.size(); K = solution::countMaxHeapSwap(tree); Q = 0);

    CASE(treeGenerator::Tree tree(0);
         tree.chain(rnd.nextInt(1LL * consFull::N / 4, consFull::N / 2), -1);
         tree.forkSequentialLinearSequence(consFull::N - tree.size(), tree.size() - 1);
         tree.get(P);
         N = tree.size(); K = solution::countMaxHeapSwap(tree) + 1; Q = 0);


    CASE(treeGenerator::Tree tree;
         tree.chainyChainy(rnd.nextInt(3LL * consFull::N / 4, consFull::N - 1), {sqrt(consFull::N) - 10, sqrt(consFull::N) + 10}, 0);
         tree.get(P);
         N = tree.size(); K = solution::countMaxHeapSwap(tree); Q = 0);

    CASE(treeGenerator::Tree tree;
         tree.chainyChainy(rnd.nextInt(3LL * consFull::N / 4, consFull::N - 1), {sqrt(consFull::N) - 10, sqrt(consFull::N) + 10}, 0);
         tree.get(P);
         N = tree.size(); K = solution::countMaxHeapSwap(tree) + 1; Q = 0);


    CASE(treeGenerator::Tree tree(0);
         tree.chain(rnd.nextInt(1LL * consFull::N / 4, consFull::N / 2), -1);
         tree.forkUniform(consFull::N - tree.size(), sqrt(tree.size()), tree.size() - 1);
         tree.get(P);
         N = tree.size();
         LL cursol = solution::countMaxHeapSwap(tree);
         K = randomWithinFraction({5, 10}, {8, 10}, cursol);
         Q = 0);

    CASE(treeGenerator::Tree tree(0);
         tree.chain(rnd.nextInt(1LL * consFull::N / 4, consFull::N / 2), -1);
         tree.forkUniform(consFull::N - tree.size(), sqrt(tree.size()), tree.size() - 1);
         tree.get(P);
         N = tree.size();
         LL cursol = solution::countMaxHeapSwap(tree);
         K = randomWithinFraction({5, 10}, {8, 10}, cursol);
         Q = 0);

    CASE(treeGenerator::Tree tree(0);
         tree.chain(rnd.nextInt(1LL * consFull::N / 4, consFull::N / 2), -1);
         tree.forkSequentialLinearSequence(consFull::N - tree.size(), tree.size() - 1);
         tree.get(P);
         N = tree.size();
         LL cursol = solution::countMaxHeapSwap(tree);
         K = randomWithinFraction({5, 10}, {8, 10}, cursol);
         Q = 0);

    CASE(treeGenerator::Tree tree(0);
         tree.chain(rnd.nextInt(1LL * consFull::N / 4, consFull::N / 2), -1);
         tree.forkSequentialLinearSequence(consFull::N - tree.size(), tree.size() - 1);
         tree.get(P);
         N = tree.size();
         LL cursol = solution::countMaxHeapSwap(tree);
         K = randomWithinFraction({5, 10}, {8, 10}, cursol);
         Q = 0);


    CASE(treeGenerator::Tree tree;
         tree.chainyChainy(rnd.nextInt(3LL * consFull::N / 4, consFull::N - 1), {sqrt(consFull::N) - 10, sqrt(consFull::N) + 10}, 0);
         tree.get(P);
         N = tree.size();
         LL cursol = solution::countMaxHeapSwap(tree);
         K = randomWithinFraction({5, 10}, {8, 10}, cursol);
         Q = 0);

    CASE(treeGenerator::Tree tree;
         tree.chainyChainy(rnd.nextInt(3LL * consFull::N / 4, consFull::N - 1), {sqrt(consFull::N) - 10, sqrt(consFull::N) + 10}, 0);
         tree.get(P);
         N = tree.size();
         LL cursol = solution::countMaxHeapSwap(tree);
         K = randomWithinFraction({5, 10}, {8, 10}, cursol);
         Q = 0);

  }

  void TestGroup12() {
    Subtasks({7, 8, 9, 10});
    CASE(treeGenerator::Tree tree(0);
         tree.chain(447, -1);
         tree.get(P);
         N = tree.size();
         LL cursol = solution::countMaxHeapSwap(tree);
         K = cursol + 1;
         Q = 1);

    CASE(treeGenerator::Tree tree(0);
         tree.chain(447, -1);
         tree.get(P);
         N = tree.size();
         LL cursol = solution::countMaxHeapSwap(tree);
         K = cursol;
         Q = 1);

    CASE(treeGenerator::Tree tree(0);
         tree.chain(448, -1);
         tree.get(P);
         N = tree.size();
         K = cons7::K;
         Q = 1);


    CASE(treeGenerator::Tree tree(0);
         tree.chain(randomWithinFraction({4, 5}, {1, 1}, 447), -1);
         tree.get(P);
         N = tree.size();
         LL cursol = solution::countMaxHeapSwap(tree);
         K = randomWithinFraction({1, 2}, {3, 4}, cursol);
         Q = 1);

    CASE(treeGenerator::Tree tree(0);
         tree.chain(randomWithinFraction({4, 5}, {1, 1}, 447), -1);
         tree.get(P);
         N = tree.size();
         LL cursol = solution::countMaxHeapSwap(tree);
         K = cursol;
         Q = 1);

    CASE(treeGenerator::Tree tree(0);
         tree.chain(randomWithinFraction({4, 5}, {1, 1}, 447), -1);
         tree.get(P);
         N = tree.size();
         LL cursol = solution::countMaxHeapSwap(tree);
         K = cursol + 1;
         Q = 1);

    CASE(treeGenerator::Tree tree(0);
         tree.chain(randomWithinFraction({4, 5}, {1, 1}, consFull::N), -1);
         tree.get(P);
         N = tree.size();
         K = randomWithinFraction({1, 2}, {3, 4}, cons7::K);
         Q = 1);

    CASE(treeGenerator::Tree tree(0);
         tree.chain(randomWithinFraction({4, 5}, {1, 1}, consFull::N), -1);
         tree.get(P);
         N = tree.size();
         K = randomWithinFraction({1, 2}, {1, 1}, cons7::K);
         Q = 1);

    CASE(treeGenerator::Tree tree(0);
         tree.chain(randomWithinFraction({4, 5}, {1, 1}, consFull::N), -1);
         tree.get(P);
         N = tree.size();
         K = randomWithinFraction({1, 2}, {1, 1}, cons7::K);
         Q = 1);


    CASE(treeGenerator::Tree tree(0);
         tree.chain(447, -1);
         tree.get(P);
         N = tree.size();
         LL cursol = solution::countMaxHeapSwap(tree);
         K = randomWithinFraction({1, 2}, {3, 4}, cursol);
         Q = 1);

    CASE(treeGenerator::Tree tree(0);
         tree.chain(447, -1);
         tree.get(P);
         N = tree.size();
         LL cursol = solution::countMaxHeapSwap(tree);
         K = randomWithinFraction({1, 10}, {3, 10}, cursol);
         Q = 1);

    CASE(treeGenerator::Tree tree(0);
         tree.chain(448, -1);
         tree.get(P);
         N = tree.size();
         LL cursol = solution::countMaxHeapSwap(tree);
         K = randomWithinFraction({3, 10}, {5, 10}, cursol);
         Q = 1);


    CASE(treeGenerator::Tree tree(0);
         tree.chain(randomWithinFraction({4, 5}, {1, 1}, 447), -1);
         tree.get(P);
         N = tree.size();
         LL cursol = solution::countMaxHeapSwap(tree);
         K = randomWithinFraction({5, 10}, {7, 10}, cursol);
         Q = 1);

    CASE(treeGenerator::Tree tree(0);
         tree.chain(randomWithinFraction({4, 5}, {1, 1}, 447), -1);
         tree.get(P);
         N = tree.size();
         LL cursol = solution::countMaxHeapSwap(tree);
         K = randomWithinFraction({6, 10}, {8, 10}, cursol);
         Q = 1);

    CASE(treeGenerator::Tree tree(0);
         tree.chain(randomWithinFraction({4, 5}, {1, 1}, 447), -1);
         tree.get(P);
         N = tree.size();
         LL cursol = solution::countMaxHeapSwap(tree);
         K = randomWithinFraction({7, 10}, {9, 10}, cursol);
         Q = 1);

    CASE(treeGenerator::Tree tree(0);
         tree.chain(randomWithinFraction({4, 5}, {1, 1}, consFull::N), -1);
         tree.get(P);
         N = tree.size();
         LL cursol = solution::countMaxHeapSwap(tree);
         K = randomWithinFraction({9, 10}, {10, 10}, cons7::K);
         Q = 1);

  }

  void TestGroup13() {
    Subtasks({8, 10});
    CASE(treeGenerator::Tree tree;
         tree.chain(448, 0);
         tree.get(P);
         N = tree.size();
         LL cursol = solution::countMaxHeapSwap(tree);
         K = cursol;
         Q = 1);

    CASE(treeGenerator::Tree tree;
         tree.chain(448, 0);
         tree.get(P);
         N = tree.size();
         LL cursol = solution::countMaxHeapSwap(tree);
         K = cursol + 1;
         Q = 1);

    CASE(treeGenerator::Tree tree;
         tree.chain(randomWithinFraction({4, 5}, {1, 1}, consFull::N), 0);
         tree.get(P);
         N = tree.size();
         LL cursol = solution::countMaxHeapSwap(tree);
         K = randomWithinFraction({1, 2}, {3, 4}, cursol);
         Q = 1);

    CASE(treeGenerator::Tree tree;
         tree.chain(randomWithinFraction({4, 5}, {1, 1}, consFull::N), 0);
         tree.get(P);
         N = tree.size();
         LL cursol = solution::countMaxHeapSwap(tree);
         K = cursol;
         Q = 1);

    CASE(treeGenerator::Tree tree;
         tree.chain(randomWithinFraction({4, 5}, {1, 1}, consFull::N), 0);
         tree.get(P);
         N = tree.size();
         LL cursol = solution::countMaxHeapSwap(tree);
         K = cursol + 1;
         Q = 1);

    CASE(treeGenerator::Tree tree;
         tree.chain(randomWithinFraction({4, 5}, {1, 1}, consFull::N), 0);
         tree.get(P);
         N = tree.size();
         LL cursol = solution::countMaxHeapSwap(tree);
         K = cursol + 2;
         Q = 1);

    CASE(treeGenerator::Tree tree; tree.chain(consFull::N - 4, 0); tree.get(P); N = tree.size();
         K = consFull::K; Q = 1);

    CASE(treeGenerator::Tree tree;
         tree.chain(randomWithinFraction({4, 5}, {1, 1}, consFull::N), 0);
         tree.get(P);
         N = tree.size();
         LL cursol = solution::countMaxHeapSwap(tree);
         K = randomWithinFraction({1, 10}, {3, 10}, cursol);
         Q = 1);

    CASE(treeGenerator::Tree tree;
         tree.chain(randomWithinFraction({4, 5}, {1, 1}, consFull::N), 0);
         tree.get(P);
         N = tree.size();
         LL cursol = solution::countMaxHeapSwap(tree);
         K = randomWithinFraction({4, 10}, {7, 10}, cursol);
         Q = 1);

    CASE(treeGenerator::Tree tree;
         tree.chain(randomWithinFraction({4, 5}, {1, 1}, consFull::N), 0);
         tree.get(P);
         N = tree.size();
         LL cursol = solution::countMaxHeapSwap(tree);
         K = randomWithinFraction({7, 10}, {9, 10}, cursol);
         Q = 1);

    CASE(treeGenerator::Tree tree;
         tree.chain(randomWithinFraction({4, 5}, {1, 1}, consFull::N), 0);
         tree.get(P);
         N = tree.size();
         LL cursol = solution::countMaxHeapSwap(tree);
         K = randomWithinFraction({7, 10}, {9, 10}, cursol);
         Q = 1);
  }

  void TestGroup14() {
    Subtasks({9, 10});
    CASE(N = 21; treeGenerator::Tree tree; tree.chain(10, 0); tree.random(10, 4); tree.get(P); K = 15; Q = 1);
    CASE(N = 10; treeGenerator::Tree tree(10); tree.get(P); K = 4; Q = 1);
    CASE(treeGenerator::Tree tree; tree.knary(consFull::N, 2, 0); tree.get(P); N = tree.size(); K = 10; Q = 1);
    CASE(treeGenerator::Tree tree; tree.knary(consFull::N, 3, 0); tree.get(P); N = tree.size(); K = 3; Q = 1);

    CASE(treeGenerator::Tree tree; tree.knary(consFull::N, 2, 0); tree.get(P); N = tree.size();
         K = solution::countMaxHeapSwap(tree); Q = 1);
    CASE(treeGenerator::Tree tree; tree.knary(consFull::N, 3, 0); tree.get(P); N = tree.size();
         K = solution::countMaxHeapSwap(tree) + 1; Q = 1);

    CASE(treeGenerator::Tree tree; tree.lowhighMaxDegree(consFull::N - 1, 10, 0, 0.2, 0); tree.get(P); N = tree.size(); K = solution::countMaxHeapSwap(tree); Q = 1);
    CASE(treeGenerator::Tree tree;
         tree.knary(rnd.nextInt(consFull::N / 2, consFull::N), consFull::N / 3, 0); tree.get(P);
         N = tree.size(); K = solution::countMaxHeapSwap(tree); Q = 1);
    CASE(treeGenerator::Tree tree; tree.halvingDegree(rnd.nextInt(consFull::N / 2, consFull::N), 0); tree.get(P);
         N = tree.size(); K = solution::countMaxHeapSwap(tree); Q = 1);
    CASE(treeGenerator::Tree tree; tree.distinctDegree(rnd.nextInt(consFull::N / 2, consFull::N), 0); tree.get(P);
         N = tree.size(); K = solution::countMaxHeapSwap(tree); Q = 1);

    CASE(treeGenerator::Tree tree; tree.lowhighMaxDegree(consFull::N - 1, 10, 0, 0.2, 0); tree.get(P); N = tree.size(); K = solution::countMaxHeapSwap(tree) - 2; Q = 1);
    CASE(treeGenerator::Tree tree; tree.halvingDegree(rnd.nextInt(consFull::N / 2, consFull::N), 0); tree.get(P);
         N = tree.size(); K = randomWithinFraction({5, 10}, {6, 10}, solution::countMaxHeapSwap(tree)); Q = 1);
    CASE(treeGenerator::Tree tree; tree.distinctDegree(rnd.nextInt(consFull::N / 2, consFull::N), 0); tree.get(P);
         N = tree.size(); K = randomWithinFraction({7, 10}, {8, 10}, solution::countMaxHeapSwap(tree)); Q = 1);

    CASE(treeGenerator::Tree tree;
         tree.knary(rnd.nextInt(consFull::N / 2, consFull::N), consFull::N / 3, 0); tree.get(P);
         N = tree.size(); K = solution::countMaxHeapSwap(tree) + 1; Q = 1);
    CASE(treeGenerator::Tree tree; tree.lowhighMaxDegree(consFull::N - 1, 10, 0, 0.2, 0); tree.get(P); N = tree.size(); K = solution::countMaxHeapSwap(tree) - 2; Q = 1);
    CASE(treeGenerator::Tree tree(0); tree.flower(rnd.nextInt(consFull::N / 2, consFull::N), -1); tree.get(P);
         N = tree.size(); K = solution::countMaxHeapSwap(tree) + 1; Q = 1);
    CASE(treeGenerator::Tree tree; tree.halvingDegree(rnd.nextInt(consFull::N / 2, consFull::N), 0); tree.get(P);
         N = tree.size(); K = solution::countMaxHeapSwap(tree) + 1; Q = 1);
    CASE(treeGenerator::Tree tree; tree.distinctDegree(rnd.nextInt(consFull::N / 2, consFull::N), 0); tree.get(P);
         N = tree.size(); K = solution::countMaxHeapSwap(tree) + 1; Q = 1);
    CASE(treeGenerator::Tree tree;
         tree.knary(1000, consFull::N, 0); tree.get(P);
         N = tree.size(); K = solution::countMaxHeapSwap(tree) + 1; Q = 1);




    CASE(treeGenerator::Tree tree;
         tree.knary(1LL * consFull::N * 3 / 4, 2, 0);
         tree.chain(1LL * consFull::N * 1 / 4, rnd.nextInt(consFull::N / 2));
         tree.get(P);
         N = tree.size(); K = randomWithinFraction({3, 5}, {1, 1}, cons9::K); Q = 1);

    CASE(treeGenerator::Tree tree(rnd.nextInt(1LL * consFull::N * 3 / 4, consFull::N)); tree.get(P);
         N = tree.size();  K = randomWithinFraction({3, 5}, {1, 1}, cons9::K); Q = 1);
    CASE(treeGenerator::Tree tree; tree.silkworm(rnd.nextInt(consFull::N / 2, consFull::N), 0); tree.get(P);
         N = tree.size();  K = randomWithinFraction({3, 5}, {1, 1}, cons9::K); Q = 1);


    CASE(treeGenerator::Tree tree(rnd.nextInt(1LL * consFull::N * 3 / 4, consFull::N)); tree.get(P);
         N = tree.size(); K = randomWithinFraction({7, 10}, {8, 10}, cons9::K); Q = 1);
    CASE(treeGenerator::Tree tree; tree.silkworm(rnd.nextInt(consFull::N / 2, consFull::N), 0); tree.get(P);
         N = tree.size(); K = randomWithinFraction({7, 10}, {8, 10}, cons9::K); Q = 1);


    CASE(treeGenerator::Tree tree; tree.knary(20000, 2, 0); tree.chain(50000, 10000); tree.get(P); N = tree.size();
         K = cons9::K; Q = 1);
    CASE(treeGenerator::Tree tree; tree.knary(20000, 2, 0); tree.chain(50000, 10000); tree.get(P); N = tree.size();
         K = cons9::K; Q = 1);
    CASE(treeGenerator::Tree tree(rnd.nextInt(1LL * consFull::N * 3 / 4, consFull::N)); tree.get(P); N = tree.size(); K = cons9::K; Q = 1);

    CASE(treeGenerator::Tree tree; tree.silkworm(rnd.nextInt(consFull::N / 2, consFull::N), 0); tree.get(P);
         N = tree.size(); K = cons9::K; Q = 1);


    CASE(treeGenerator::Tree tree(0);
         tree.chain(rnd.nextInt(1LL * consFull::N / 4, consFull::N / 2), -1);
         tree.forkUniform(consFull::N - tree.size(), sqrt(tree.size()), tree.size() - 1);
         tree.get(P);
         N = tree.size(); K = cons9::K; Q = 1);

    CASE(treeGenerator::Tree tree(0);
         tree.chain(rnd.nextInt(1LL * consFull::N / 4, consFull::N / 2), -1);
         tree.forkUniform(consFull::N - tree.size(), sqrt(tree.size()), tree.size() - 1);
         tree.get(P);
         N = tree.size(); K = randomWithinFraction({4, 5}, {1, 1}, cons9::K); Q = 1);

    CASE(treeGenerator::Tree tree(0);
         tree.chain(rnd.nextInt(1LL * consFull::N / 4, consFull::N / 2), -1);
         tree.forkSequentialLinearSequence(consFull::N - tree.size(), tree.size() - 1);
         tree.get(P);
         N = tree.size(); K = randomWithinFraction({4, 5}, {1, 1}, cons9::K); Q = 1);

    CASE(treeGenerator::Tree tree(0);
         tree.chain(rnd.nextInt(1LL * consFull::N / 4, consFull::N / 2), -1);
         tree.forkSequentialLinearSequence(consFull::N - tree.size(), tree.size() - 1);
         tree.get(P);
         N = tree.size(); K = randomWithinFraction({4, 5}, {1, 1}, cons9::K); Q = 1);


    CASE(treeGenerator::Tree tree;
         tree.chainyChainy(rnd.nextInt(3LL * consFull::N / 4, consFull::N - 1), {sqrt(consFull::N) - 10, sqrt(consFull::N) + 10}, 0);
         tree.get(P);
         N = tree.size(); K = randomWithinFraction({4, 5}, {1, 1}, cons9::K); Q = 1);

    CASE(treeGenerator::Tree tree;
         tree.chainyChainy(rnd.nextInt(3LL * consFull::N / 4, consFull::N - 1), {sqrt(consFull::N) - 10, sqrt(consFull::N) + 10}, 0);
         tree.get(P);
         N = tree.size(); K = randomWithinFraction({4, 5}, {1, 1}, cons9::K); Q = 1);



    CASE(treeGenerator::Tree tree;
         tree.chainyChainy(rnd.nextInt(3LL * consFull::N / 4, consFull::N - 1), {sqrt(consFull::N) - 10, sqrt(consFull::N) + 10}, 0);
         tree.get(P);
         N = tree.size(); K = randomWithinFraction({4, 5}, {1, 1}, cons9::K); Q = 1);

    CASE(treeGenerator::Tree tree;
         tree.chainyChainy(rnd.nextInt(3LL * consFull::N / 4, consFull::N - 1), {sqrt(consFull::N) - 10, sqrt(consFull::N) + 10}, 0);
         tree.get(P);
         N = tree.size(); K = randomWithinFraction({4, 5}, {1, 1}, cons9::K); Q = 1);

  }


  void TestGroup15() {
    Subtasks({10});
    CASE(treeGenerator::Tree tree;
         tree.knary(1LL * consFull::N * 3 / 4, 2, 0);
         tree.chain(1LL * consFull::N * 1 / 4, rnd.nextInt(consFull::N / 2));
         tree.get(P);
         N = tree.size(); K = solution::countMaxHeapSwap(tree); Q = 1);

    CASE(treeGenerator::Tree tree(rnd.nextInt(1LL * consFull::N * 3 / 4, consFull::N)); tree.get(P);
         N = tree.size(); K = solution::countMaxHeapSwap(tree); Q = 1);
    CASE(treeGenerator::Tree tree; tree.silkworm(rnd.nextInt(consFull::N / 2, consFull::N), 0); tree.get(P);
         N = tree.size(); K = solution::countMaxHeapSwap(tree); Q = 1);


    CASE(treeGenerator::Tree tree(rnd.nextInt(1LL * consFull::N * 3 / 4, consFull::N)); tree.get(P);
         N = tree.size(); K = randomWithinFraction({7, 10}, {8, 10}, solution::countMaxHeapSwap(tree)); Q = 1);
    CASE(treeGenerator::Tree tree; tree.silkworm(rnd.nextInt(consFull::N / 2, consFull::N), 0); tree.get(P);
         N = tree.size(); K = randomWithinFraction({7, 10}, {8, 10}, solution::countMaxHeapSwap(tree)); Q = 1);


    CASE(treeGenerator::Tree tree; tree.knary(20000, 2, 0); tree.chain(50000, 10000); tree.get(P); N = tree.size();
         K = solution::countMaxHeapSwap(tree) + 1; Q = 1);
    CASE(treeGenerator::Tree tree; tree.knary(20000, 2, 0); tree.chain(50000, 10000); tree.get(P); N = tree.size();
         K = solution::countMaxHeapSwap(tree); Q = 1);
    CASE(treeGenerator::Tree tree(rnd.nextInt(1LL * consFull::N * 3 / 4, consFull::N)); tree.get(P); N = tree.size(); K = solution::countMaxHeapSwap(tree) - 2; Q = 1);

    CASE(treeGenerator::Tree tree; tree.silkworm(rnd.nextInt(consFull::N / 2, consFull::N), 0); tree.get(P);
         N = tree.size(); K = solution::countMaxHeapSwap(tree) + 2; Q = 1);

    // TC 10
    CASE(treeGenerator::Tree tree(0);
         tree.chain(rnd.nextInt(1LL * consFull::N / 4, consFull::N / 2), -1);
         tree.forkUniform(consFull::N - tree.size(), sqrt(tree.size()), tree.size() - 1);
         tree.get(P);
         N = tree.size(); K = solution::countMaxHeapSwap(tree); Q = 1);

    CASE(treeGenerator::Tree tree(0);
         tree.chain(rnd.nextInt(1LL * consFull::N / 4, consFull::N / 2), -1);
         tree.forkUniform(consFull::N - tree.size(), sqrt(tree.size()), tree.size() - 1);
         tree.get(P);
         N = tree.size(); K = solution::countMaxHeapSwap(tree) + 1; Q = 1);

    CASE(treeGenerator::Tree tree(0);
         tree.chain(rnd.nextInt(1LL * consFull::N / 4, consFull::N / 2), -1);
         tree.forkSequentialLinearSequence(consFull::N - tree.size(), tree.size() - 1);
         tree.get(P);
         N = tree.size(); K = randomWithinFraction({4, 5}, {1, 1}, solution::countMaxHeapSwap(tree)); Q = 1);

    CASE(treeGenerator::Tree tree(0);
         tree.chain(rnd.nextInt(1LL * consFull::N / 4, consFull::N / 2), -1);
         tree.forkSequentialLinearSequence(consFull::N - tree.size(), tree.size() - 1);
         tree.get(P);
         N = tree.size(); K = solution::countMaxHeapSwap(tree) + 1; Q = 1);

    // TC 14-19
    CASE(treeGenerator::Tree tree;
         tree.chainyChainy(rnd.nextInt(3LL * consFull::N / 4, consFull::N - 1), {sqrt(consFull::N) - 10, sqrt(consFull::N) + 10}, 0);
         tree.get(P);
         N = tree.size(); K = randomWithinFraction({4, 5}, {1, 1}, solution::countMaxHeapSwap(tree)); Q = 1);

    CASE(treeGenerator::Tree tree;
         tree.chainyChainy(rnd.nextInt(3LL * consFull::N / 4, consFull::N - 1), {10, 15}, 0);
         tree.get(P);
         N = tree.size(); K = randomWithinFraction({4, 5}, {1, 1}, solution::countMaxHeapSwap(tree)); Q = 1);

    CASE(treeGenerator::Tree tree;
         tree.chainyChainy(rnd.nextInt(3LL * consFull::N / 4, consFull::N - 1), {50, 100}, 0);
         tree.get(P);
         N = tree.size(); K = randomWithinFraction({4, 5}, {1, 1}, solution::countMaxHeapSwap(tree)); Q = 1);

    CASE(treeGenerator::Tree tree;
         tree.chainyChainy(rnd.nextInt(3LL * consFull::N / 4, consFull::N - 1), {800, 900}, 0);
         tree.get(P);
         N = tree.size(); K = randomWithinFraction({4, 5}, {1, 1}, solution::countMaxHeapSwap(tree)); Q = 1);

    CASE(treeGenerator::Tree tree;
         tree.chainyChainy(rnd.nextInt(3LL * consFull::N / 4, consFull::N - 1), {3000, 4000}, 0);
         tree.get(P);
         N = tree.size();
         K = randomWithinFraction({4, 5}, {1, 1}, solution::countMaxHeapSwap(tree));
         Q = 1);


    CASE(treeGenerator::Tree tree;
         tree.chainyChainy(rnd.nextInt(3LL * consFull::N / 4, consFull::N - 1), {sqrt(consFull::N) - 10, sqrt(consFull::N) + 10}, 0);
         tree.get(P);
         N = tree.size(); K = solution::countMaxHeapSwap(tree) + 1; Q = 1);


    CASE(treeGenerator::Tree tree(0);
         tree.chain(rnd.nextInt(1LL * consFull::N / 4, consFull::N / 2), -1);
         tree.forkUniform(consFull::N - tree.size(), sqrt(tree.size()), tree.size() - 1);
         tree.get(P);
         N = tree.size();
         K = randomWithinFraction({5, 10}, {7, 10}, solution::countMaxHeapSwap(tree));
         Q = 1);

    CASE(treeGenerator::Tree tree(0);
         tree.chain(rnd.nextInt(1LL * consFull::N / 4, consFull::N / 2), -1);
         tree.forkUniform(consFull::N - tree.size(), sqrt(tree.size()), tree.size() - 1);
         tree.get(P);
         N = tree.size();
         K = randomWithinFraction({3, 10}, {6, 10}, solution::countMaxHeapSwap(tree));
         Q = 1);

    CASE(treeGenerator::Tree tree(0);
         tree.chain(rnd.nextInt(1LL * consFull::N / 4, consFull::N / 2), -1);
         tree.forkSequentialLinearSequence(consFull::N - tree.size(), tree.size() - 1);
         tree.get(P);
         N = tree.size(); K = randomWithinFraction({4, 5}, {1, 1}, solution::countMaxHeapSwap(tree)); Q = 1);

  }
 private:
  vector <string> loadManualFromFile(string filename) {
    ifstream file(filename);
    vector <string> lines;
    string line;
    while (getline(file, line)) {
      lines.push_back(line);
    }
    file.close();
    return lines;
  }

  LL randomWithinFraction(PLL fractionLowerBound, PLL fractionUpperBound, LL value) {
    LL lower = fractionLowerBound.fi * value / fractionLowerBound.se;
    assert(fractionLowerBound.fi <= fractionLowerBound.se);
    LL upper = fractionUpperBound.fi * value / fractionUpperBound.se;
    assert(fractionUpperBound.fi <= fractionUpperBound.se);
    assert(fractionLowerBound.fi * fractionUpperBound.se <= fractionUpperBound.fi * fractionLowerBound.se);
    return rnd.nextLongLong(lower, upper);
  }

  template <class T>
  void fillWithRandom(vector<T> &collection, int collectionSize, T low, T high) {
    collection.resize(collectionSize);
    generate(
      collection.begin(),
      collection.end(),
    [&]() {
      return rnd.nextLongLong(low, high);
    }
    );
  }

  template <class T>
  void fillWithRandom(vector<T> &collection, int collectionSize, vector<T> elementSet) {
    collection.resize(collectionSize);
    generate(
      collection.begin(),
      collection.end(),
    [&]() {
      const int index = rnd.nextInt(0, (int)(elementSet.size()) - 1);
      return elementSet[index];
    }
    );
  }

  template<class F, class S>
  void shufflePairs(vector<F> &pairFirst, vector <S> &pairSecond) {
    vector <pair<F, S>> zipped;
    assert(pairFirst.size() == pairSecond.size());
    for (int i = 0; i < pairFirst.size(); i++) {
      zipped.emplace_back(pairFirst[i], pairSecond[i]);
    }
    rnd.shuffle(begin(zipped), end(zipped));
    for (int i = 0; i < pairFirst.size(); i++) {
      pairFirst[i] = zipped[i].first;
      pairSecond[i] = zipped[i].second;
    }
  }

};