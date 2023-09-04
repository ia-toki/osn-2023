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

std::optional<pair<lint, lint>> memo[4005];

pair<lint, lint> dp(lint length, lint has_free_query) {
  if (has_free_query == 0) {
    auto ret = dp(length, 1);
    return {ret.first + 1, ret.second};
  }
  if (length == 0) return {0, 0};
  if (!memo[length].has_value()) {
    lint ret = INF;
    lint best = 0;
    for (lint Y = 1; Y <= length; Y++) {
      lint lft = max(dp(Y - 1, 0).first, dp(length - Y, 1).first);
      lint rgt = max(dp(Y - 1, 1).first, dp(length - Y, 0).first);
      lint cur = 1 + min(lft, rgt);
      if (cur < ret) {
        ret = cur;
        best = Y;
      }
    }
    assert(best != 0);
    memo[length] = {ret, best};
  }
  return memo[length].value();
}

pair<lint, lint> dp(lint L, lint R, lint X) {
  if (L > R) return {-INF, 0};
  if (X != 0 && (X < L || R < X)) return dp(L, R, 0);
  if (L == R && X != 0) return {1, L};
  if (X == 0) {
    auto ret = dp(R - L + 1, 0);
    return {ret.first, L - 1 + ret.second};
  }
  lint lft = 1 + max(dp(X - L, 1).first, dp(R - X, 0).first);
  lint rgt = 1 + max(dp(X - L, 0).first, dp(R - X, 1).first);
  if (lft <= rgt) {
    return {lft, L - 1 + dp(X - L, 1).second};
  } else {
    return {rgt, X + dp(R - X, 1).second};
  }
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
