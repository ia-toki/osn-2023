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

std::optional<lint> memo_dp[105][2];

bool is_in_between(lint x, lint lo, lint hi) { return lo <= x && x <= hi; }

lint get_max_length_with(lint query, lint has_free_query) {
  if (query > 100) return INF;
  assert(is_in_between(query, 0, 100));
  assert(is_in_between(has_free_query, 0, 1));
  if (query + has_free_query <= 1) return -INF;  // can't do anything
  std::optional<lint>& memo = memo_dp[query][has_free_query];
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
  if (L > R) return 0;
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

pair<lint, lint> dp(lint L, lint R, lint X) {
  assert(L <= R);
  assert(X == 0 || (L <= X && X <= R));
  if (L == R && X != 0) return {1, L};
  lint ret = INF;
  lint best = 0;
  if (X == 0) {
    for (lint Y = L; Y <= R; Y++) {
      lint cur = 1 + get_dp_value(L, R, Y);
      if (cur < ret) {
        ret = cur;
        best = Y;
      }
    }
  } else {
    for (lint Y = L; Y <= R; Y++) {
      lint cur = 1 + max(get_dp_value(L, X - 1, Y), get_dp_value(X + 1, R, Y));
      if (cur < ret) {
        ret = cur;
        best = Y;
      }
    }
  }
  return {ret, best};
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
