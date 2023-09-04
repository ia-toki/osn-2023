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

std::optional<pair<lint, lint>> memo_dp[105][2];

bool is_in_between(lint x, lint lo, lint hi) { return lo <= x && x <= hi; }

pair<lint, lint> get_max_length_with(lint query, lint has_free_query) {
  if (query > 100) return {INF, 0};
  assert(is_in_between(query, 0, 100));
  assert(is_in_between(has_free_query, 0, 1));
  if (query + has_free_query <= 1) return {-INF, 0};  // can't do anything
  std::optional<pair<lint, lint>>& memo = memo_dp[query][has_free_query];
  if (memo.has_value()) {
    return memo.value();
  }
  lint ret = query + has_free_query - 1;
  lint best = 1;
  if (has_free_query == 0) {
    lint cur = get_max_length_with(query - 2, 0).first + 1 +
               get_max_length_with(query - 2, 1).first;
    if (cur > ret) {
      ret = cur;
      best = get_max_length_with(query - 2, 0).first + 1;
    }
  } else {
    lint cur = get_max_length_with(query - 1, 0).first + 1 +
               get_max_length_with(query - 1, 1).first;
    if (cur > ret) {
      ret = cur;
      best = get_max_length_with(query - 1, 0).first + 1;
    }
  }
  memo = {ret, best};
  return memo.value();
}

pair<lint, lint> get_dp_value(lint length, lint has_free_query) {
  lint query = 0;
  while (get_max_length_with(query, has_free_query).first < length) {
    query += 1;
  }
  lint best = get_max_length_with(query, has_free_query).second;
  return {query, min(length, best)};
}

pair<lint, lint> dp(lint L, lint R, lint X) {
  assert(L <= R);
  if (X == 0 || X < L || R < X) {
    auto ret = get_dp_value(R - L + 1, 0);
    return {ret.first, L - 1 + ret.second};
  }
  if (L == R) return {1, L};  // just need one more query to confirm
  if (L == X) {
    auto ret = get_dp_value(R - L, 0);
    return {ret.first, L + ret.second};
  }
  if (X == R) {
    auto ret = get_dp_value(R - L, 0);
    return {ret.first, L - 1 + ret.second};
  }
  assert(L < X && X < R);
  lint lft = 1 + max(get_dp_value(X - L, 1).first,
                     get_dp_value(R - X, 0).first);  // if L <= Y < X
  lint rgt = 1 + max(get_dp_value(X - L, 0).first,
                     get_dp_value(R - X, 1).first);  // if X < Y <= R
  if (lft <= rgt) {
    return {lft, L - 1 + get_dp_value(X - L, 1).second};
  } else {
    return {rgt, X + get_dp_value(R - X, 1).second};
  }
}

lint get_query_position(lint L, lint R, lint X) {
  if (X != 0 && (X < L || R < X)) {
    return get_query_position(L, R, 0);
  }
  if (R - L + 1 <= 300000) {
    return dp(L, R, X).second;
  }
  lint length = R - L + 1;
  if (length <= 5) {
    if (X == 0) {
      return (L + R) / 2;
    }
    return X;
  }
  lint mid1 = lint(length / 2.315);
  lint mid2 = mid1 + (length - mid1) / 2;
  if (X == 0) {
    return mid1 + L - 1;
  } else {
    return mid2 + L - 1;
  }
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
