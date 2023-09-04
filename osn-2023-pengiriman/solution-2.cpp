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

int main() {
  int N, T;
  cin >> N >> T;
  write(3);
  write(5);
  lint q = read();
  if (q == 0) {
    return 0;
  } else if (q < 0) {
    if (write(1); read() == 0) {
      return 0;
    }
    if (write(2); read() == 0) {
      return 0;
    }
    if (write(2); read() == 0) {
      return 0;
    }
  } else if (q > 0) {
    write(6);
    q = read();
    if (q == 0) {
      return 0;
    } else if (q < 0) {
      if (write(4); read() == 0) {
        return 0;
      }
      if (write(4); read() == 0) {
        return 0;
      }
    } else if (q > 0) {
      if (write(7); read() == 0) {
        return 0;
      }
      if (write(7); read() == 0) {
        return 0;
      }
    }
  }
  assert(false);
  return 0;
}
