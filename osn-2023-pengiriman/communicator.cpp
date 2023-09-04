#include <bits/stdc++.h>
using namespace std;

using lint = long long;
mt19937_64 rnd;

// Constants
const lint INF = 1e16;
const double EPS = 1e-3;

namespace interaction {

// Verdicts
void ac() {
  cerr << "AC" << endl;
  exit(0);
}

void wa() {
  cerr << "WA" << endl;
  exit(0);
}

void ok(lint pts) {
  cerr << "OK" << endl;
  cerr << pts << endl;
  exit(0);
}

void eof() {
  if (string x; cin >> x) wa();
}

void output_score(lint N, lint Q) {
  if (N != lint(1e9)) {
    ac();
  } else {
    if (Q <= 44) {
      ac();
    } else {
      ok(2'250'000 / (Q * Q * Q));
    }
  }
}

// Parameters
lint SEED;
lint N;
lint ANSWER;
lint QUERY_LIMIT;
double if_left_edge_then_end;
double if_right_edge_then_end;
double if_tie_go_left;
double if_not_tie_temperature;

// Cache
std::optional<lint> memo_max_length_with_query[105][2];

// Utilities
bool succeed_with_probability(double x) {
  return (uniform_real_distribution<double>(0, 1)(rnd) < x);
}

bool is_in_between(lint x, lint lo, lint hi) { return lo <= x && x <= hi; }

lint string_to_int(string x) {
  if (x.empty()) wa();
  if (x == "0") return 0;
  if (x[0] == '0') wa();
  lint z = 0;
  for (char i : x) {
    if (!is_in_between(i, '0', '9')) wa();
    z = 10 * z + (i - '0');
    if (z > INF) wa();
  }
  return z;
}

// Input Output
lint read_contestant_query() {
  if (QUERY_LIMIT <= 0) wa();
  QUERY_LIMIT--;
  string x;
  if (!(cin >> x)) wa();
  lint y = string_to_int(x);
  if (!is_in_between(y, 1, N)) wa();
  return y;
}

void write_go_right() {
  cout << "KEKECILAN" << endl;
  if (QUERY_LIMIT <= 0) wa();
}

void write_go_left() {
  cout << "KEBESARAN" << endl;
  if (QUERY_LIMIT <= 0) wa();
}

void write_correct() { cout << "PAS" << endl; }

// Interactor
lint get_max_length_with(lint query, lint has_free_query) {
  if (query > 100) return INF;
  assert(is_in_between(query, 0, 100));
  assert(is_in_between(has_free_query, 0, 1));
  if (query + has_free_query <= 1) return -INF;  // can't do anything
  std::optional<lint>& memo = memo_max_length_with_query[query][has_free_query];
  if (memo.has_value()) {
    return memo.value();
  }
  lint ret = query + has_free_query - 1;
  if (has_free_query == 0) {
    ret = max(ret, get_max_length_with(query - 2, 0) +
                       get_max_length_with(query - 2, 1) + 1);
  } else {
    ret = max(ret, get_max_length_with(query - 1, 0) +
                       get_max_length_with(query - 1, 1) + 1);
  }
  memo = ret;
  return ret;
}

lint get_dp_value(lint length, lint has_free_query) {
  lint query = 0;
  while (get_max_length_with(query, has_free_query) < length) {
    query += 1;
  }
  return query;
}

lint get_dp_value(lint L, lint R, lint X) {
  if (X == -1) {
    return get_dp_value(R - L + 1, 0);
  }
  if (X < L || R < X) {
    return get_dp_value(R - L + 1, 0);
  }
  if (L == R) return 1;    // just need one more query to confirm
  if (L == X || X == R) {  // must fail in worst case
    return get_dp_value(R - L, 0);
  }
  assert(L < X && X < R);
  lint lft =
      1 + max(get_dp_value(X - L, 1), get_dp_value(R - X, 0));  // if L <= Y < X
  lint rgt =
      1 + max(get_dp_value(X - L, 0), get_dp_value(R - X, 1));  // if X < Y <= R
  return min(lft, rgt);
}

void interaction(lint L, lint R, lint X) {
  lint Y = read_contestant_query();
  if (X == -1) {  // first query
    return interaction(L, R, Y);
  }

  if (ANSWER != -1) {  // ANSWER is predetermined
    if (X == ANSWER) {
      return write_correct();
    } else if (X < ANSWER) {
      write_go_right();
      return interaction(L, R, Y);
    } else if (ANSWER < X) {
      write_go_left();
      return interaction(L, R, Y);
    }
  }

  if (X < L) {
    write_go_right();
    return interaction(L, R, Y);
  }

  if (R < X) {
    write_go_left();
    return interaction(L, R, Y);
  }

  assert(L <= X && X <= R);
  if (L == R) {
    return write_correct();
  }

  if (L == X) {
    if (succeed_with_probability(if_left_edge_then_end)) {
      return write_correct();
    }
    write_go_right();
    return interaction(L + 1, R, Y);
  }

  if (X == R) {
    if (succeed_with_probability(if_right_edge_then_end)) {
      return write_correct();
    }
    write_go_left();
    return interaction(L, R - 1, Y);
  }

  assert(L < X && X < R);
  lint lft = get_dp_value(L, X - 1, Y);
  lint rgt = get_dp_value(X + 1, R, Y);

  if (lft == rgt) {
    if (succeed_with_probability(if_tie_go_left)) {
      write_go_left();
      return interaction(L, X - 1, Y);
    } else {
      write_go_right();
      return interaction(X + 1, R, Y);
    }
  }

  assert(lft != rgt);
  bool take_smaller = false;
  if (if_not_tie_temperature > EPS) {
    double prob_of_success =
        exp(-1.0 * fabs(lft - rgt) / if_not_tie_temperature);
    if (succeed_with_probability(prob_of_success)) {
      take_smaller = true;
    }
  }

  if (lft < rgt) {
    if (take_smaller) {
      write_go_left();
      return interaction(L, X - 1, Y);
    } else {
      write_go_right();
      return interaction(X + 1, R, Y);
    }
  }

  if (lft > rgt) {
    if (take_smaller) {
      write_go_right();
      return interaction(X + 1, R, Y);
    } else {
      write_go_left();
      return interaction(L, X - 1, Y);
    }
  }

  // should never happen
  wa();
  return;
}

void run_interactor(ifstream& tc_in) {
  lint ORIGINAL_QUERY_LIMIT;
  // Read testcase
  tc_in >> SEED;
  tc_in >> N;
  tc_in >> ANSWER;
  tc_in >> QUERY_LIMIT;
  tc_in >> if_left_edge_then_end;
  tc_in >> if_right_edge_then_end;
  tc_in >> if_tie_go_left;
  tc_in >> if_not_tie_temperature;

  // Initialization
  rnd = mt19937_64(SEED);
  ORIGINAL_QUERY_LIMIT = QUERY_LIMIT;
  cout << N << ' ' << QUERY_LIMIT << endl;

  // Start interaction
  interaction(1, N, -1);
  lint QUERY_USED = ORIGINAL_QUERY_LIMIT - QUERY_LIMIT;

  eof();
  output_score(N, QUERY_USED);
}

}  // namespace interaction

int main(int argc, char* argv[]) {
  ifstream tc_in(argv[1]);
  interaction::run_interactor(tc_in);
  return 0;
}
