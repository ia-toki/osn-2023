#include <bits/stdc++.h>
using namespace std;

using lint = long long;
const lint INF = 1e16;

void write(lint Y) { cout << Y << endl; }

lint read() {
  string s;
  cin >> s;
  if (s == "PAS") {
    return 0;
  } else if (s == "KEBESARAN") {
    return -1;
  } else if (s == "KEKECILAN") {
    return 1;
  } else {
    assert(false);
    return 0;
  }
}

std::optional<pair<lint, lint>> memo[55][55][55];

pair<lint, lint> dp(lint L, lint R, lint X) {
  if (L > R) return {-INF, 0};
  if (X != 0 && (X < L || R < X)) return dp(L, R, 0);
  if (L == R && X != 0) return {1, L};
  if (!memo[L][R][X].has_value()) {
    lint ret = INF;
    lint best = 0;
    if (X == 0) {
      for (lint Y = L; Y <= R; Y++) {
        lint cur = 1 + dp(L, R, Y).first;
        if (cur < ret) {
          ret = cur;
          best = Y;
        }
      }
    } else {
      for (lint Y = L; Y <= R; Y++) {
        lint cur = 1 + max(dp(L, X - 1, Y).first, dp(X + 1, R, Y).first);
        if (cur < ret) {
          ret = cur;
          best = Y;
        }
      }
    }
    assert(L <= best && best <= R);
    memo[L][R][X] = {ret, best};
  }
  return memo[L][R][X].value();
}

lint get_query_position(lint L, lint R, lint X) {
  if (X != 0 && (X < L || R < X)) {
    return get_query_position(L, R, 0);
  }
  return dp(L, R, X).second;
}

void interaction(lint L, lint R, lint X) {
  lint Y = get_query_position(L, R, X);
  assert(L <= Y && Y <= R);
  write(Y);
  if (X == 0) {  // first query
    return interaction(L, R, Y);
  }
  lint q = read();  // result of ask(X)
  if (q == 0) {
    return;  // done
  } else if (q < 0) {
    return interaction(L, min(R, X - 1), Y);
  } else if (q > 0) {
    return interaction(max(L, X + 1), R, Y);
  }
}

int main() {
  int N, T;
  cin >> N >> T;
  interaction(1, N, 0);
  return 0;
}
