#include <bits/stdc++.h>

#include <tcframe/spec.hpp>

using namespace std;
using namespace tcframe;

using lint = long long;

const lint MAXN = 1e9;

const lint MAXN_SUB_0 = 5;
const lint QUERY_SUB_0 = 6;

const lint MAXN_SUB_1 = 7;
const lint QUERY_SUB_1 = 5;

const lint MAXN_SUB_2 = 50;
const lint QUERY_SUB_2 = 9;

const lint MAXN_SUB_3 = 350;
const lint QUERY_SUB_3 = 13;

const lint MAXN_SUB_4 = 2500;
const lint QUERY_SUB_4 = 17;

const lint MAXN_SUB_5 = 300'000;
const lint QUERY_SUB_5 = 27;

const lint MAXN_SUB_6 = 1'000'000'000;
const lint QUERY_SUB_6 = 100;

namespace communicator {

#include "communicator.cpp"

}

class ProblemSpec : public BaseProblemSpec {
 protected:
  lint SEED;
  lint N;
  lint ANSWER;
  lint QUERY_LIMIT;
  double if_left_edge_then_end;
  double if_right_edge_then_end;
  double if_tie_go_left;
  double if_not_tie_temperature;

  void InputFormat() {
    LINE(SEED);
    LINE(N, ANSWER, QUERY_LIMIT);
    LINE(if_left_edge_then_end, if_right_edge_then_end, if_tie_go_left,
         if_not_tie_temperature);
  }

  void GradingConfig() {
    TimeLimit(2);
    MemoryLimit(512);
  }

  void StyleConfig() { InteractiveEvaluator(); }

  void Constraints() {
    CONS(1 <= N && N <= MAXN);
    CONS(ANSWER == -1 || (1 <= ANSWER && ANSWER <= N));
    CONS(communicator::interaction::get_dp_value(1, N, -1) <= QUERY_LIMIT);
  }

  void Subtask1() {
    Points(6);
    CONS(N == MAXN_SUB_0);
    CONS(QUERY_LIMIT == QUERY_SUB_0);
  }

  void Subtask2() {
    Points(6);
    CONS(N == MAXN_SUB_1);
    CONS(QUERY_LIMIT == QUERY_SUB_1);
    CONS(QUERY_LIMIT == communicator::interaction::get_dp_value(1, N, -1));
  }

  void Subtask3() {
    Points(21);
    CONS(N == MAXN_SUB_2);
    CONS(QUERY_LIMIT == QUERY_SUB_2);
    CONS(QUERY_LIMIT == communicator::interaction::get_dp_value(1, N, -1));
  }

  void Subtask4() {
    Points(9);
    CONS(N == MAXN_SUB_3);
    CONS(QUERY_LIMIT == QUERY_SUB_3);
    CONS(QUERY_LIMIT == communicator::interaction::get_dp_value(1, N, -1));
  }

  void Subtask5() {
    Points(12);
    CONS(N == MAXN_SUB_4);
    CONS(QUERY_LIMIT == QUERY_SUB_4);
    CONS(QUERY_LIMIT == communicator::interaction::get_dp_value(1, N, -1));
  }

  void Subtask6() {
    Points(20);
    CONS(N == MAXN_SUB_5);
    CONS(QUERY_LIMIT == QUERY_SUB_5);
    CONS(QUERY_LIMIT == communicator::interaction::get_dp_value(1, N, -1));
  }

  void Subtask7() {
    Points(26);
    CONS(N == MAXN_SUB_6);
    CONS(QUERY_LIMIT == QUERY_SUB_6);
  }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
 protected:
  void SampleTestCase1() {
    Subtasks({1});
    Input({
        "42",
        "5 4 6",
        "-1 -1 -1 -1",
    });
  }

  void BeforeTestCase() {
    SEED = 42;
    N = -1;
    ANSWER = -1;
    QUERY_LIMIT = 0;
    if_left_edge_then_end = -1;
    if_right_edge_then_end = -1;
    if_tie_go_left = -1;
    if_not_tie_temperature = -1;
  }

  void TestGroup1() {
    Subtasks({1});
    for (int j = 0; j < 2; j++) {
      for (int i = 1; i <= MAXN_SUB_0; i++) {
        CASE(initTest(0); ANSWER = i);
      }
    }
  }

  void TestGroup2() {
    Subtasks({2});
    for (int j = 0; j < 2; j++) {
      for (int i = 1; i <= MAXN_SUB_1; i++) {
        CASE(initTest(1); ANSWER = i);
      }
    }
  }

  void TestGroup3() {
    Subtasks({3});
    for (int j = 0; j < 5; j++) {
      CASE(initTest(2); ANSWER = -1);
    }
    for (int i = 1; i <= MAXN_SUB_2; i++) {
      CASE(initTest(2); ANSWER = i);
    }
  }

  void TestGroup4() {
    const int SUBTASK = 4;
    Subtasks({SUBTASK});
    CASE(initTest(SUBTASK - 1); ANSWER = 1);
    CASE(initTest(SUBTASK - 1); ANSWER = N);
    CASE(initTest(SUBTASK - 1); ANSWER = rnd.nextInt(1, N));
    for (double temp : vector<double>{0., 1., 2.}) {
      for (double lft : vector<double>{0.2, 0.5, 0.8}) {
        CASE(initTest(SUBTASK - 1); ANSWER = -1; if_tie_go_left = lft;
             if_not_tie_temperature = temp);
        CASE(initTest(SUBTASK - 1); ANSWER = -1; if_tie_go_left = lft;
             if_not_tie_temperature = temp; if_left_edge_then_end = 0.2);
        CASE(initTest(SUBTASK - 1); ANSWER = -1; if_tie_go_left = lft;
             if_not_tie_temperature = temp; if_right_edge_then_end = 0.2);
      }
    }
  }

  void TestGroup5() {
    const int SUBTASK = 5;
    Subtasks({SUBTASK});
    CASE(initTest(SUBTASK - 1); ANSWER = 1);
    CASE(initTest(SUBTASK - 1); ANSWER = N);
    CASE(initTest(SUBTASK - 1); ANSWER = rnd.nextInt(1, N));
    for (double temp : vector<double>{0., 1., 2.}) {
      for (double lft : vector<double>{0.2, 0.5, 0.8}) {
        CASE(initTest(SUBTASK - 1); ANSWER = -1; if_tie_go_left = lft;
             if_not_tie_temperature = temp);
        CASE(initTest(SUBTASK - 1); ANSWER = -1; if_tie_go_left = lft;
             if_not_tie_temperature = temp; if_left_edge_then_end = 0.2);
        CASE(initTest(SUBTASK - 1); ANSWER = -1; if_tie_go_left = lft;
             if_not_tie_temperature = temp; if_right_edge_then_end = 0.2);
      }
    }
  }

  void TestGroup6() {
    const int SUBTASK = 6;
    Subtasks({SUBTASK});
    CASE(initTest(SUBTASK - 1); ANSWER = 1);
    CASE(initTest(SUBTASK - 1); ANSWER = N);
    CASE(initTest(SUBTASK - 1); ANSWER = rnd.nextInt(1, N));
    for (double temp : vector<double>{0., 1., 2.}) {
      for (double lft : vector<double>{0.2, 0.5, 0.8}) {
        CASE(initTest(SUBTASK - 1); ANSWER = -1; if_tie_go_left = lft;
             if_not_tie_temperature = temp);
        CASE(initTest(SUBTASK - 1); ANSWER = -1; if_tie_go_left = lft;
             if_not_tie_temperature = temp; if_left_edge_then_end = 0.2);
        CASE(initTest(SUBTASK - 1); ANSWER = -1; if_tie_go_left = lft;
             if_not_tie_temperature = temp; if_right_edge_then_end = 0.2);
      }
    }
  }

  void TestGroup7() {
    const int SUBTASK = 7;
    Subtasks({SUBTASK});
    CASE(initTest(SUBTASK - 1); ANSWER = 1);
    CASE(initTest(SUBTASK - 1); ANSWER = N);
    CASE(initTest(SUBTASK - 1); ANSWER = rnd.nextInt(1, N));
    for (double temp : vector<double>{0., 1., 2.}) {
      for (double lft : vector<double>{0.2, 0.5, 0.8}) {
        CASE(initTest(SUBTASK - 1); ANSWER = -1; if_tie_go_left = lft;
             if_not_tie_temperature = temp);
        CASE(initTest(SUBTASK - 1); ANSWER = -1; if_tie_go_left = lft;
             if_not_tie_temperature = temp; if_left_edge_then_end = 0.2);
        CASE(initTest(SUBTASK - 1); ANSWER = -1; if_tie_go_left = lft;
             if_not_tie_temperature = temp; if_right_edge_then_end = 0.2);
      }
    }
  }

 private:
  void initTest(int subtask) {
    SEED = rnd.nextInt(MAXN);
    if (subtask == 0) {
      N = MAXN_SUB_0;
      QUERY_LIMIT = QUERY_SUB_0;
    } else if (subtask == 1) {
      N = MAXN_SUB_1;
      QUERY_LIMIT = QUERY_SUB_1;
    } else if (subtask == 2) {
      N = MAXN_SUB_2;
      QUERY_LIMIT = QUERY_SUB_2;
    } else if (subtask == 3) {
      N = MAXN_SUB_3;
      QUERY_LIMIT = QUERY_SUB_3;
    } else if (subtask == 4) {
      N = MAXN_SUB_4;
      QUERY_LIMIT = QUERY_SUB_4;
    } else if (subtask == 5) {
      N = MAXN_SUB_5;
      QUERY_LIMIT = QUERY_SUB_5;
    } else if (subtask == 6) {
      N = MAXN_SUB_6;
      QUERY_LIMIT = QUERY_SUB_6;
    }
  }
};
