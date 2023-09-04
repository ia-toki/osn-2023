#include <bits/stdc++.h>
#include <tcframe/spec.hpp>

using namespace std;
using namespace tcframe;
typedef long long LL;
typedef pair<LL, LL> PLL;
#define fi first
#define se second
#define pb push_back
#define rep(i,a,b) for(int i = a;i < b;i++)

namespace consFull {
constexpr int N = 1e9;
constexpr int P = 200000;
constexpr int Q = 200000;
const set<int> T = {1, 2};
}

namespace cons1 {
constexpr int N = 7;
constexpr int P = 4;
constexpr int Q = 5;
const vector <int> T = {2, 1, 1, 2};
const vector <int> W = {4, 6, 4, 3};
const vector <int> X = {2, 3, 6, 4, 3};
const vector <int> Y = {6, 2, 3, 4, 7};
}

namespace cons2 {
// If T_i == 1, then W_i == N
// Otherwise, W_i == 1
}


namespace cons3 {
constexpr int N = 200;
constexpr int P = 200;
constexpr int Q = 200;
}

namespace cons4 {
constexpr int N = 2000;
constexpr int P = 2000;
constexpr int Q = 2000;
}

namespace cons5 {
constexpr int P = 1;
}

namespace cons6 {
constexpr int P = 2;
const vector <int> T = {1, 2};
// W1 == W2
}

namespace cons7 {
constexpr int N = 200000;
const set<int> T = {1};
}

namespace cons8 {
constexpr int N = 200000;
// X = Y
}

namespace cons9 {
constexpr int N = 200000;
}


class ProblemSpec : public BaseProblemSpec {
 protected:
  int N, P, Q;
  vector <int> T, W;
  vector <int> X, Y;
  vector <int> ANS;
  void InputFormat() {
    LINE(N, P);
    LINES(T, W) % SIZE(P);
    LINE(Q);
    LINES(X, Y) % SIZE(Q);
  }

  void OutputFormat() {
    LINES(ANS) % SIZE(Q);
  }

  void GradingConfig() {
    TimeLimit(2);
    MemoryLimit(512);
  }

  void Constraints() {
    CONS(1 <= N && N <= consFull::N);
    CONS(1 <= P && P <= consFull::P);
    CONS(1 <= Q && Q <= consFull::Q);

    CONS(P == T.size());
    CONS(P == W.size());
    CONS(T.size() == W.size());
    CONS(eachElementOf(T, consFull::T));
    CONS(eachElementBetween(W, 1, N));


    CONS(Q == X.size());
    CONS(Q == Y.size());
    CONS(X.size() == Y.size());
    CONS(eachElementBetween(X, 1, N));
    CONS(eachElementBetween(Y, 1, N));
  }

  void Subtask1() {
    Points(6);
    CONS(N == cons1::N); CONS(P == cons1::P); CONS(Q == cons1::Q);
    CONS(T == cons1::T); CONS(W == cons1::W);
    CONS(X == cons1::X); CONS(Y == cons1::Y);
  }

  void Subtask2() {
    Points(5);
    CONS(isOnlyEntireGridUpdate(N, T, W));
  }

  void Subtask3() {
    Points(8);
    CONS(1 <= N && N <= cons3::N);
    CONS(1 <= P && P <= cons3::P);
    CONS(1 <= Q && Q <= cons3::Q);
  }

  void Subtask4() {
    Points(10);
    CONS(1 <= N && N <= cons4::N);
    CONS(1 <= P && P <= cons4::P);
    CONS(1 <= Q && Q <= cons4::Q);
  }

  void Subtask5() {
    Points(7);
    CONS(P == cons5::P);
  }

  void Subtask6() {
    Points(11);
    CONS(P == cons6::P);
    CONS(T == cons6::T);
    CONS(W[0] == W[1]);
  }

  void Subtask7() {
    Points(15);
    CONS(1 <= N && N <= cons7::N);
    CONS(eachElementOf(T, cons7::T));
  }

  void Subtask8() {
    Points(13);
    CONS(1 <= N && N <= cons8::N);
    CONS(X == Y);
  }

  void Subtask9() {
    Points(10);
    CONS(1 <= N && N <= cons9::N);
  }

  void Subtask10() {
    Points(15);

  }

 private:
  bool isOnlyEntireGridUpdate(const int &N_, const vector <int> &T_, const vector <int> &W_) {
    for (int i = 0; i < T_.size(); i++) {
      if (T_[i] == 1 && W_[i] != N_) return 0;
      if (T_[i] == 2 && W_[i] != 1) return 0;
    }
    return 1;
  }

  template <class T>
  bool eachElementBetween(vector<T> collection, T low, T high) {
    for (const T &element : collection) {
      if (!(low <= element && element <= high)) {
        return false;
      }
    }
    return true;
  }

  template <class T>
  bool eachElementOf(vector<T> collection, set<T> elementSet) {
    for (const T &element : collection) {
      if (!(elementSet.count(element))) {
        return false;
      }
    }
    return true;
  }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
 protected:
  void SampleTestCase1() {
    Subtasks({3, 4, 9, 10});
    Input(loadManualFromFile("manual/sample01.in"));
    Output(loadManualFromFile("manual/sample01.out"));
  }

  void BeforeTestCase() {
    T.clear();
    W.clear();
    X.clear();
    Y.clear();
  }

  void TestGroup1() {
    Subtasks({1, 3, 4, 9, 10});
    CASE(
      N = cons1::N; P = cons1::P; Q = cons1::Q;
      T = cons1::T; W = cons1::W;
      X = cons1::X; Y = cons1::Y;
    );
  }


  void TestGroup2() {

    Subtasks({2, 5, 10});
    CASE(N = consFull::N; P = cons5::P;
         T.pb(1);
         W.pb(N);
         Q = consFull::Q;
         fillXYWithRectangle({N - 5, N - 5}, {N, N});
         fillWithRandom(X, consFull::Q - X.size(), 1, N);
         fillWithRandom(Y, consFull::Q - Y.size(), 1, N);
        );

    CASE(N = consFull::N; P = cons5::P;
         T.pb(2);
         W.pb(1);
         Q = consFull::Q;
         fillXYWithRectangle({1, 1}, {3, 3});
         fillWithRandom(X, consFull::Q - X.size(), 1, N);
         fillWithRandom(Y, consFull::Q - Y.size(), 1, N);
        );


  }

  void TestGroup3() {
    Subtasks({2, 10});
    CASE(N = consFull::N; P = consFull::P; Q = consFull::Q;
         fillWithRandom(T, P, 1, 2);
         fillWithRandom(X, Q, 1, N);
         fillWithRandom(Y, Q, 1, N);
         implicateWSubtask2());

    CASE(N = consFull::N;
         P = randomWithinFraction({1, 2}, {1, 1}, consFull::P);
         P -= P % 2;
         assert(P % 2 == 0);
         // Pasti genap
         Q = consFull::Q;
         fillWithRandom(T, P, 1, 2);
         fillWithRandom(X, Q, 1, N);
         fillWithRandom(Y, Q, 1, N);
         implicateWSubtask2());

    CASE(N = consFull::N;
         P = randomWithinFraction({1, 2}, {1, 1}, consFull::P);
         P -= !(P % 2);
         assert(P % 2 == 1);
         // Pasti ganjil
         Q = consFull::Q;
         fillWithRandom(T, P, 1, 2);
         fillWithRandom(X, Q, 1, N);
         fillWithRandom(Y, Q, 1, N);
         implicateWSubtask2());
  }


  void TestGroup4() {
    Subtasks({3, 4, 7, 8, 9, 10});
    CASE(
      N = cons3::N;
      P = cons3::P;
      Q = cons3::Q;
      fillWithRandom(T, P, 1, 1);
      fillWithRandom(W, P, 1, N);
      fillWithRandom(X, Q, 1, N);
      Y = X;
    );
  }

  void TestGroup5() {
    Subtasks({3, 4, 7, 9, 10});
    CASE(
      N = cons3::N,
      P = 2,
      Q = cons3::Q / 2,
      T = {1, 1};
      W = {1, 1};
      fillWithRandom(X, Q, 1, N);
      fillWithRandom(Y, Q, 1, N);
    );
  }



  void TestGroup6() {

    Subtasks({3, 4, 9, 10});
    CASE(
      N = cons3::N;
      Q = cons3::Q;
      fillWithUniqueTW(cons3::P);
      shufflePairs(T, W);
      P = T.size();
      fillWithRandom(X, Q, 1, N);
      fillWithRandom(Y, Q, 1, N);
    );

    CASE(
      N = randomWithinFraction({3, 4}, {4, 4}, cons3::N);
      fillWithUniqueTW(cons3::P);
      shufflePairs(T, W);
      Q = cons3::Q;
      P = T.size();
      fillWithRandom(X, Q, 1, N);
      fillWithRandom(Y, Q, 1, N);
    );

    CASE(
      N = randomWithinFraction({3, 4}, {4, 4}, cons3::N);
      fillWithUniqueTW(randomWithinFraction({3, 4}, {4, 4}, cons3::P));
      shufflePairs(T, W);
      Q = cons3::Q;
      P = T.size();
      fillWithRandom(X, Q, 1, N);
      fillWithRandom(Y, Q, 1, N);
    );

    CASE(
      N = cons3::N;
      Q = cons3::Q;
      P = cons3::P;
      fillWithRandom(T, P, {1, 2});
      fillWWithCollisionOnly();
      fillWithRandom(X, Q, 1, N);
      fillWithRandom(Y, Q, 1, N);
    );


    CASE(
      N = randomWithinFraction({3, 4}, {4, 4}, cons3::N);
      Q = cons3::Q;
      P = randomWithinFraction({3, 4}, {4, 4}, cons3::P);
      fillWithRandom(T, P, {1, 2});
      fillWWithCollisionOnly();
      fillWithRandom(X, Q, 1, N);
      fillWithRandom(Y, Q, 1, N);
    );

    CASE(
      N = randomWithinFraction({3, 4}, {4, 4}, cons3::N);
      Q = cons3::Q;
      P = randomWithinFraction({3, 4}, {4, 4}, cons3::P);
      fillWithRandom(T, P - 1, {1});
      T.pb(2);
      fillWWithCollisionOnly();
      shufflePairs(T, W);
      fillWithRandom(X, Q, 1, N);
      fillWithRandom(Y, Q, 1, N);
    );


    CASE(
      N = randomWithinFraction({3, 4}, {4, 4}, cons3::N);
      Q = cons3::Q;
      P = randomWithinFraction({3, 4}, {4, 4}, cons3::P);
      fillWithRandom(T, P - 1, {2});
      T.pb(1);
      fillWWithCollisionOnly();
      shufflePairs(T, W);
      fillWithRandom(X, Q, 1, N);
      fillWithRandom(Y, Q, 1, N);
    );
  }



  void TestGroup7() {

    Subtasks({4, 9, 10});
    CASE(
      N = cons4::N;
      Q = cons4::Q;
      fillWithUniqueTW(cons4::P);
      shufflePairs(T, W);
      P = T.size();
      fillWithRandom(X, Q, 1, N);
      fillWithRandom(Y, Q, 1, N);
    );


    CASE(
      N = randomWithinFraction({3, 4}, {4, 4}, cons4::N);
      fillWithUniqueTW(cons4::P);
      shufflePairs(T, W);
      Q = cons4::Q;
      P = T.size();
      fillWithRandom(X, Q, 1, N);
      fillWithRandom(Y, Q, 1, N);
    );

    CASE(
      N = randomWithinFraction({3, 4}, {4, 4}, cons4::N);
      fillWithUniqueTW(randomWithinFraction({3, 4}, {4, 4}, cons4::P));
      shufflePairs(T, W);
      Q = cons4::Q;
      P = T.size();
      fillWithRandom(X, Q, 1, N);
      fillWithRandom(Y, Q, 1, N);
    );


    CASE(
      N = cons4::N;
      Q = cons4::Q;
      P = cons4::P;
      fillWithRandom(T, P, {1, 2});
      fillWWithCollisionOnly();
      fillWithRandom(X, Q, 1, N);
      fillWithRandom(Y, Q, 1, N);
    );



    CASE(
      N = randomWithinFraction({3, 4}, {4, 4}, cons4::N);
      Q = cons4::Q;
      P = randomWithinFraction({3, 4}, {4, 4}, cons4::P);
      fillWithRandom(T, P, {1, 2});
      fillWWithCollisionOnly();
      fillWithRandom(X, Q, 1, N);
      fillWithRandom(Y, Q, 1, N);
    );

    CASE(
      N = randomWithinFraction({3, 4}, {4, 4}, cons4::N);
      Q = cons4::Q;
      P = randomWithinFraction({3, 4}, {4, 4}, cons4::P);
      fillWithRandom(T, P - 1, {1});
      T.pb(2);
      fillWWithCollisionOnly();
      shufflePairs(T, W);
      fillWithRandom(X, Q, 1, N);
      fillWithRandom(Y, Q, 1, N);
    );


    CASE(
      N = randomWithinFraction({3, 4}, {4, 4}, cons4::N);
      Q = cons4::Q;
      P = randomWithinFraction({3, 4}, {4, 4}, cons4::P);
      fillWithRandom(T, P - 1, {2});
      T.pb(1);
      fillWWithCollisionOnly();
      shufflePairs(T, W);
      fillWithRandom(X, Q, 1, N);
      fillWithRandom(Y, Q, 1, N);
    );
  }

  void TestGroup8() {
    Subtasks({5, 10});
    CASE(N = consFull::N; P = cons5::P; Q = consFull::Q;
         T.pb(1);
         fillWithRandom(W, P, N / 4, (int)(3LL * N / 4));
         fillWithRandom(X, Q, 1, N);
         fillWithRandom(Y, Q, 1, N);
        );

    CASE(N = consFull::N; P = cons5::P; Q = consFull::Q;
         T.pb(2);
         fillWithRandom(W, P, N / 4, (int)(3LL * N / 4));
         fillWithRandom(X, Q, 1, N);
         fillWithRandom(Y, Q, 1, N);
        );



    CASE(N = consFull::N; P = cons5::P; Q = consFull::Q;
         T.pb(1);
         W.pb(N / 2);
         fillXYWithRectangle({N / 2 - 10, N / 2 - 10}, {N / 2 + 10, N / 2 + 10});;
         fillWithRandom(X, Q - X.size(), 1, N);
         fillWithRandom(Y, Q - Y.size(), 1, N);
        );

    CASE(N = consFull::N; P = cons5::P; Q = consFull::Q;
         T.pb(2);
         W.pb(N / 2);
         fillXYWithRectangle({N / 2 - 10, N / 2 - 10}, {N / 2 + 10, N / 2 + 10});
         fillWithRandom(X, Q - X.size(), 1, N);
         fillWithRandom(Y, Q - Y.size(), 1, N);
        );


    CASE(N = consFull::N; P = cons5::P;
         T.pb(1);
         W.pb(1);
         Q = consFull::Q;
         fillXYWithRectangle({1, 1}, {3, 3});
         fillWithRandom(X, consFull::Q - X.size(), 1, N);
         fillWithRandom(Y, consFull::Q - Y.size(), 1, N);
        );

    CASE(N = consFull::N; P = cons5::P;
         T.pb(1);
         W.pb(2);
         Q = consFull::Q;
         fillXYWithRectangle({1, 1}, {3, 3});
         fillWithRandom(X, consFull::Q - X.size(), 1, N);
         fillWithRandom(Y, consFull::Q - Y.size(), 1, N);
        );


    CASE(N = consFull::N; P = cons5::P;
         T.pb(1);
         W.pb(N - 1);
         Q = consFull::Q;
         fillXYWithRectangle({N - 5, N - 5}, {N, N});
         fillWithRandom(X, consFull::Q - X.size(), 1, N);
         fillWithRandom(Y, consFull::Q - Y.size(), 1, N);
        );

    CASE(N = consFull::N; P = cons5::P;
         T.pb(2);
         W.pb(2);
         Q = consFull::Q;
         fillXYWithRectangle({1, 1}, {3, 3});
         fillWithRandom(X, consFull::Q - X.size(), 1, N);
         fillWithRandom(Y, consFull::Q - Y.size(), 1, N);
        );


    CASE(N = consFull::N; P = cons5::P;
         T.pb(2);
         W.pb(N - 1);
         Q = consFull::Q;
         fillXYWithRectangle({N - 5, N - 5}, {N, N});
         fillWithRandom(X, consFull::Q - X.size(), 1, N);
         fillWithRandom(Y, consFull::Q - Y.size(), 1, N);
        );

    CASE(N = consFull::N; P = cons5::P;
         T.pb(2);
         W.pb(N);
         Q = consFull::Q;
         fillXYWithRectangle({N - 5, N - 5}, {N, N});
         fillWithRandom(X, consFull::Q - X.size(), 1, N);
         fillWithRandom(Y, consFull::Q - Y.size(), 1, N);
        );
  }



  void TestGroup9() {
    Subtasks({6, 9, 10});
    CASE(
      N = cons9::N; P = cons6::P;
      T = cons6::T;
      W.assign(P, rnd.nextInt(4LL * N / 5, 6LL * N / 7));
      int sq = sqrt(consFull::Q) / 2;
      int mini = max(1, W[0] - sq + 1);
      int maxi = min(N, W[0] + sq - 1);
      rep(i, mini, maxi) rep(j, mini, maxi) X.pb(i), Y.pb(j);
      Q = X.size();
      shufflePairs(X, Y);
    );
  }

  void TestGroup10() {
    Subtasks({6, 10});
    CASE(
      N = consFull::N; P = cons6::P; Q = consFull::Q;
      T = cons6::T;
      W.assign(P, rnd.nextInt(N / 4, 3LL * N / 4));
      fillWithRandom(X, Q, 1, N);
      fillWithRandom(Y, Q, 1, N);
      for (int i = 0; i < 5; i++) X[i] = Y[i] = W[0];
      shufflePairs(X, Y);
    );

    CASE(
      N = consFull::N; P = cons6::P;
      T = cons6::T;
      W.assign(P, rnd.nextInt(N / 2, 3LL * N / 4));
      int sq = sqrt(consFull::Q) / 2;
      int mini = max(1, W[0] - sq + 1);
      int maxi = min(N, W[0] + sq - 1);
      fillXYWithRectangle({mini, maxi}, {mini, maxi});
      Q = X.size();
      shufflePairs(X, Y);
    );


    CASE(
      N = consFull::N; P = cons6::P;
      T = cons6::T;
      W.assign(P, rnd.nextInt(N / 4, N / 2));
      int sq = sqrt(consFull::Q) / 2;
      int mini = max(1, W[0] - sq + 1);
      int maxi = min(N, W[0] + sq - 1);
      fillXYWithRectangle({mini, maxi}, {mini, maxi});
      Q = X.size();
      shufflePairs(X, Y);
    );
  }

  void TestGroup11() {
    Subtasks({7, 9, 10});
    CASE(
      N = cons7::N,
      P = consFull::P / 2,
      Q = consFull::Q,
      fillWithRandom(T, P, 1, 1);
      fillWithRandom(W, P, 1, N);
      fillWithRandom(X, Q, 1, N);
      fillWithRandom(Y, Q, 1, N);
    );

    CASE(
      N = 10000,
      P = consFull::P,
      fillWithRandom(T, P, 1, 1);
      fillWithRandom(W, P, 1, N);
      int sq = sqrt(consFull::Q) / 2;
      int mini = max(1, N / 2 - sq + 1);
      int maxi = min(N, N / 2 + sq - 1);
      fillXYWithRectangle({mini, maxi}, {mini, maxi});
      shufflePairs(X, Y);
      Q = X.size();
    );

    CASE(
      N = randomWithinFraction({9, 10}, {10, 10}, cons7::N),
      P = consFull::P,
      fillWithRandom(T, P, 1, 1);
      fillWithRandom(W, P, 1, N);
      int sq = sqrt(consFull::Q) / 2;
      int mini = max(1, N / 2 - sq + 1);
      int maxi = min(N, N / 2 + sq - 1);
      fillXYWithRectangle({mini, maxi}, {mini, maxi});
      shufflePairs(X, Y);
      Q = X.size();
    );

    CASE(
      N = randomWithinFraction({9, 10}, {10, 10}, cons7::N),
      fillWithSpaced(W, 100, {1, N});
      P = W.size();
      T.assign(P, 1);
      shufflePairs(T, W);

      int sq = sqrt(consFull::Q) / 2;
      int mini = max(1, N / 2 - sq + 1);
      int maxi = min(N, N / 2 + sq - 1);
      fillXYWithRectangle({mini, maxi}, {mini, maxi});
      shufflePairs(X, Y);
      Q = X.size();
    );

    CASE(
      N = randomWithinFraction({9, 10}, {10, 10}, cons7::N),
      fillWithSpaced(W, 3, {1, N});
      P = W.size();
      T.assign(P, 1);
      shufflePairs(T, W);
      Q = consFull::Q;
      fillWithRandom(X, Q, 1, N);
      fillWithRandom(Y, Q, 1, N);

    );

    CASE(
      N = randomWithinFraction({9, 10}, {10, 10}, cons7::N),
      fillWithSpaced(W, 2, {1, N});
      P = W.size();
      T.assign(P, 1);
      shufflePairs(T, W);
      int sq = sqrt(consFull::Q) / 2;
      int mini = max(1, N / 2 - sq + 1);
      int maxi = min(N, N / 2 + sq - 1);
      fillXYWithRectangle({mini, maxi}, {mini, maxi});
      shufflePairs(X, Y);
      Q = X.size();
    );

    CASE(
      N = randomWithinFraction({9, 10}, {10, 10}, cons7::N),
      Q = consFull::Q,
      fillWithSpaced(W, 1, {1, N});
      P = W.size();
      T.assign(P, 1);
      shufflePairs(T, W);
      fillWithRandom(X, Q, 1, N);
      fillWithRandom(Y, Q, 1, N);
    );
  }


  void TestGroup12() {
    Subtasks({8, 9, 10});

    CASE(
      N = cons8::N;
      Q = consFull::Q;
      P = consFull::P;
      fillWithRandom(T, P, {1, 2});
      fillWWithCollisionOnly();
      fillWithSpaced(X, 1, {1, N});
      Y = X;
      Q = X.size();
      shufflePairs(X, Y);
    );

    CASE(
      N = randomWithinFraction({9, 10}, {10, 10}, cons8::N),
      P = consFull::P,
      fillWithRandom(T, P, 1, 2);
      fillWithRandom(W, P, 1, N);
      fillWithSpaced(X, 1, {1, N});
      Y = X;
      Q = X.size();
      shufflePairs(X, Y);
    );

    CASE(
      N = randomWithinFraction({9, 10}, {10, 10}, cons8::N),
      fillWithSpaced(W, 100, {1, N});
      fillWithSpaced(W, 100, {1, N});
      P = W.size();
      T.assign(P / 2, 1);
      T.resize(P, 2);
      shufflePairs(T, W);

      fillWithSpaced(X, 1, {1, N});
      Y = X;
      Q = X.size();
      shufflePairs(X, Y);
    );

    CASE(
      N = randomWithinFraction({9, 10}, {10, 10}, cons8::N),
      fillWithSpaced(W, 2, {1, N});
      fillWithSpaced(W, 2, {1, N});
      P = W.size();
      T.assign(P / 2, 1);
      T.resize(P, 2);
      shufflePairs(T, W);

      fillWithSpaced(X, 1, {1, N});
      Y = X;
      Q = X.size();
      shufflePairs(X, Y);
    );

    CASE(
      N = cons8::N,
      P = consFull::P,
      Q = consFull::Q,
      fillWithRandom(T, P, {1, 2});
      fillWithRandom(W, P, 1, N);
      fillWithRandom(X, Q, 1, N);
      Y = X;
    );

  }

  void TestGroup13() {

    Subtasks({9, 10});
    CASE(
      N = cons9::N;
      Q = consFull::Q;
      fillWithUniqueTW(consFull::P);
      shufflePairs(T, W);
      P = T.size();
      fillWithRandom(X, Q, 1, N);
      fillWithRandom(Y, Q, 1, N);
    );

    CASE(
      N = cons9::N;
      Q = consFull::Q;
      P = consFull::P;
      fillWithRandom(T, P, {1, 2});
      fillWWithCollisionOnly();
      fillWithRandom(X, Q, 1, N);
      fillWithRandom(Y, Q, 1, N);
    );

    CASE(
      N = 10000,
      P = consFull::P,
      fillWithRandom(T, P, 1, 2);
      fillWithRandom(W, P, 1, N);
      int sq = sqrt(consFull::Q) / 2;
      int mini = max(1, N / 2 - sq + 1);
      int maxi = min(N, N / 2 + sq - 1);
      fillXYWithRectangle({mini, maxi}, {mini, maxi});
      shufflePairs(X, Y);
      Q = X.size();
    );

    CASE(
      N = randomWithinFraction({9, 10}, {10, 10}, cons9::N),
      fillWithSpaced(W, 100, {1, N});
      fillWithSpaced(W, 100, {1, N});
      P = W.size();
      T.assign(P / 2, 1);
      T.resize(P, 2);
      shufflePairs(T, W);

      int sq = sqrt(consFull::Q) / 2;
      int mini = max(1, N / 2 - sq + 1);
      int maxi = min(N, N / 2 + sq - 1);
      fillXYWithRectangle({mini, maxi}, {mini, maxi});
      shufflePairs(X, Y);
      Q = X.size();
    );

    CASE(
      N = randomWithinFraction({9, 10}, {10, 10}, cons9::N),
      fillWithSpaced(W, 3, {1, N});
      fillWithSpaced(W, 3, {1, N});
      P = W.size();
      T.assign(P / 2, 1);
      T.resize(P, 2);
      shufflePairs(T, W);

      Q = consFull::Q;
      fillWithRandom(X, Q, 1, N);
      fillWithRandom(Y, Q, 1, N);

    );

    CASE(
      N = randomWithinFraction({9, 10}, {10, 10}, cons9::N),
      fillWithSpaced(W, 100, {1, N});
      fillWithSpaced(W, 100, {1, N});
      P = W.size();
      T.assign(P / 2, 1);
      T.resize(P, 2);
      shufflePairs(T, W);
      int sq = sqrt(consFull::Q) / 2;
      int mini = max(1, N / 2 - sq + 1);
      int maxi = min(N, N / 2 + sq - 1);
      fillXYWithRectangle({mini, maxi}, {mini, maxi});
      shufflePairs(X, Y);
      Q = X.size();
    );
  }

  void TestGroup14() {

    Subtasks({10});
    CASE(
      N = consFull::N;
      Q = consFull::Q;
      fillWithUniqueTW(consFull::P);
      shufflePairs(T, W);
      P = T.size();
      fillWithRandom(X, Q, 1, N);
      fillWithRandom(Y, Q, 1, N);
    );

    CASE(
      N = consFull::N;
      Q = consFull::Q;
      P = consFull::P;
      fillWithRandom(T, P, {1, 2});
      fillWWithCollisionOnly();
      fillWithRandom(X, Q, 1, N);
      fillWithRandom(Y, Q, 1, N);
    );


    CASE(
      N = consFull::N;
      Q = consFull::Q;
      fillWithUniqueTW(consFull::P);
      shufflePairs(T, W);
      P = T.size();
      fillWithRandom(X, Q, 1, N);
      fillWithRandom(Y, Q, 1, N);
    );

    CASE(
      N = randomWithinFraction({9, 10}, {10, 10}, consFull::N),
      fillWithSpaced(W, 10000, {1, N});
      fillWithSpaced(W, 10000, {1, N});
      P = W.size();
      T.assign(P / 2, 1);
      T.resize(P, 2);
      shufflePairs(T, W);

      int sq = sqrt(consFull::Q) / 2;
      int mini = max(1, N / 2 - sq + 1);
      int maxi = min(N, N / 2 + sq - 1);
      fillXYWithRectangle({mini, maxi}, {mini, maxi});
      shufflePairs(X, Y);
      Q = X.size();
    );

    CASE(
      N = randomWithinFraction({9, 10}, {10, 10}, consFull::N),
      fillWithSpaced(W, 50000, {1, N});
      fillWithSpaced(W, 50000, {1, N});
      P = W.size();
      T.assign(P / 2, 1);
      T.resize(P, 2);
      shufflePairs(T, W);

      Q = consFull::Q;
      fillWithRandom(X, Q, 1, N);
      fillWithRandom(Y, Q, 1, N);

    );
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
    for (int i = 0; i < collectionSize; i++) {
      collection.pb(rnd.nextLongLong(low, high));
    }
  }

  template <class T>
  void fillWithRandom(vector<T> &collection, int collectionSize, vector<T> elementSet) {

    for (int i = 0; i < collectionSize; i++) {

      const int index = rnd.nextInt(0, (int)(elementSet.size()) - 1);
      collection.pb(elementSet[index]);
    }
  }

  template <class T>
  void fillWithSpaced(vector<T> &collection,
                      int space, PLL range) {
    for (int i = range.fi; i <= range.se; i += space) {
      collection.pb(i);
    }
  }

  void fillWithUniqueTW(int maxElement = INT_MAX) {
    const int elementLimit = 2000000;
    maxElement = min(elementLimit, maxElement / 2);
    maxElement = min(maxElement / 2, N);
    if (maxElement <= elementLimit) {
      for (int i = 1; i <= maxElement; i++) {
        T.push_back(1);
        W.push_back(i);
        T.push_back(2);
        W.push_back(i);
      }
    } else {
      set <pair<int, int>> avail;
      auto checkAndPut = [&](int a, int b) {
        if (avail.count({a, b})) {
          return;
          avail.insert({a, b});
        }
      };
      for (int i = 1; i <= maxElement; i++) {
        checkAndPut(1, rnd.nextLongLong(1, N));
        checkAndPut(2, rnd.nextLongLong(1, N));
      }
      for (auto availPair : avail) {
        T.push_back(availPair.first);
        W.push_back(availPair.second);
      }
    }
  }


  void fillWithSpacedQ(LL sqrtQ) {
    LL space = max(N / sqrtQ, 1LL);
    for (int i = 1; i <= N; i += space) {
      for (int j = 1; j <= N; j += space) {
        X.pb(i);
        Y.pb(j);
      }
    }
  }

  void fillXYWithRectangle(PLL topLeft, PLL bottomRight) {
    for (int i = topLeft.fi; i <= bottomRight.fi; i++) {
      for (int j = topLeft.se; j <= bottomRight.se; j++) {
        X.pb(i);
        Y.pb(j);
      }
    }
  }
  void fillWWithCollisionOnly() {
    W.resize(P);
    for (int i = 0; i < P; i++) {
      W[i] = rnd.nextLongLong(N / 2 + 1, N);
      if (T[i] == 2) W[i] = N - W[i] + 1;
    }
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

  void implicateWSubtask2() {
    W.resize(T.size());
    for (int i = 0; i < T.size(); i++) {
      W[i] = (T[i] == 1 ? N : 1);
    }
  }

};