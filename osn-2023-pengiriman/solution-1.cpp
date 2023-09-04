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

int main(int argc, char* argv[]) {
  int N, T;
  cin >> N >> T;
  for (int i = 1; i <= N; i++) {
    if (write(i); i > 1 && read() == 0) {
      return 0;
    }
  }
  if (write(N); read() == 0) {
    return 0;
  }
  assert(false);
  return 0;
}
