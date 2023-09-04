#include <bits/stdc++.h>

#include <ext/pb_ds/assoc_container.hpp>

using namespace std;

using lint = long long;

template <typename T>
using ordered_set =
    __gnu_pbds::tree<T, __gnu_pbds::null_type, less<T>, __gnu_pbds::rb_tree_tag,
                     __gnu_pbds::tree_order_statistics_node_update>;

template <class F>
class YComb_ {
  F f_;

 public:
  template <class T>
  explicit YComb_(T&& f) : f_(forward<T>(f)) {}
  template <class... Args>
  decltype(auto) operator()(Args&&... args) {
    return f_(ref(*this), forward<Args>(args)...);
  }
};

template <class F>
decltype(auto) YComb(F&& f) {
  return YComb_<decay_t<F>>(forward<F>(f));
}

namespace checker {

pair<lint, vector<int>> solve_brute(int N, vector<int> P, vector<int> A) {
  long long K = 0;
  vector<vector<int>> chld(N + 1);
  for (int i = 1; i < N; i++) {
    chld[P[i]].push_back(i);
  }

  for (int i = N - 1; i >= 0; i--) {
    int j = i;
    while (!chld[j].empty()) {
      int pivot = j;
      for (int nex : chld[j]) {
        if (A[nex] < A[pivot]) {
          pivot = nex;
        }
      }

      if (pivot == j) break;
      swap(A[j], A[pivot]);
      j = pivot;
      K++;
    }
  }
  return {K, A};
}

pair<lint, vector<int>> solve_shiftup(int N, vector<int> P, vector<int> A) {
  lint K = 0;
  for (int i = 0; i < N; i++) {
    for (int u = 0; u < N; u++) {
      if (A[u] == i) {
        int cur = u;
        while (cur > 0 && A[cur] < A[P[cur]]) {
          swap(A[cur], A[P[cur]]);
          cur = P[cur];
          K += 1;
        }
      }
    }
  }
  return {K, A};
}

pair<lint, vector<int>> solve(int N, vector<int> P, vector<int> A) {
  vector<vector<int>> adj(N);
  for (int i = 1; i < N; i++) {
    adj[P[i]].emplace_back(i);
  }

  vector<int> siz(N);
  vector<int> dep(N);
  vector<int> head(N);
  vector<int> parent_pos(N);
  vector<deque<int>> chains(N);
  vector<ordered_set<pair<int, int>>> chains_value(N);

  YComb([&](auto self, int u) -> void {
    siz[u] = 1;
    for (auto& v : adj[u]) {
      dep[v] = dep[u] + 1;
      self(v);
      siz[u] += siz[v];
      if (siz[v] > siz[adj[u][0]]) {
        swap(v, adj[u][0]);
      }
    }
  })(0);

  vector<pair<int, int>> value(N);
  vector<int> root_of_value(N);
  for (int i = 0; i < N; i++) {
    value[A[i]] = {-dep[i], A[i]};
  }

  auto insert_to_chain = [&](int root, int u) {
    chains[root].emplace_back(u);
    chains_value[root].insert(value[A[u]]);
    root_of_value[A[u]] = root;
  };

  YComb([&](auto self, int u) -> void {
    insert_to_chain(u, u);
    for (int cur = u; !adj[cur].empty(); cur = adj[cur][0]) {
      insert_to_chain(u, adj[cur][0]);
    }
    for (int i = 0; i < int(chains[u].size()); i++) {
      int cur = chains[u][i];
      head[cur] = u;
      parent_pos[cur] = -1;
      for (auto v : adj[cur]) {
        if (v != adj[cur][0]) {
          self(v);
          parent_pos[v] = int(chains[u].size()) - 1 - i;
        }
      }
    }
  })(0);

  lint K = 0;
  for (int cur_iterate_value = 0; cur_iterate_value < N; cur_iterate_value++) {
    int cur_value = cur_iterate_value;
    int cur_root = root_of_value[cur_value];
    while (true) {
      int parent_root = P[cur_root] == -1 ? -1 : head[P[cur_root]];

      auto it = chains_value[cur_root].find(value[cur_value]);
      assert(it != end(chains_value[cur_root]));

      K += int(chains_value[cur_root].size()) - 1 -
           int(chains_value[cur_root].order_of_key(value[cur_value]));

      chains_value[cur_root].erase(it);

      if (parent_root == -1 ||
          parent_pos[cur_root] >= chains[parent_root].size()) {
        A[chains[cur_root].front()] = cur_iterate_value;
        chains[cur_root].pop_front();
        break;
      }

      auto it2 = chains_value[parent_root].find_by_order(parent_pos[cur_root]);
      assert(it2 != end(chains_value[parent_root]));
      int swapped_value = it2->second;

      K += 1;
      root_of_value[swapped_value] = cur_root;
      chains_value[cur_root].insert(value[swapped_value]);

      cur_root = parent_root;
      cur_value = swapped_value;
    }
  }

  return {K, A};
}

mt19937 rnd(chrono::high_resolution_clock::now().time_since_epoch().count());

void stress(int N) {
  for (int it = 0; it < 10000; it++) {
    vector<int> P(N, -1);
    for (int i = 1; i < N; i++) {
      // cin >> P[i];
      // P[i]--;
      P[i] = rnd() % i;
    }
    vector<int> A(N);
    for (int i = 0; i < N; i++) {
      // cin >> A[i];
      // A[i]--;
      A[i] = i;
    }
    shuffle(begin(A), end(A), rnd);
    auto [k1, ans1] = solve_shiftup(N, P, A);
    auto [k2, ans2] = solve(N, P, A);
    // cout << k1 << ' ' << k2 << '\n';
    if (ans1 != ans2 || k1 != k2) {
      cout << "WA on tc:\n";

      cout << N << '\n';
      P.erase(begin(P));
      for (auto i : P) cout << i + 1 << ' ';
      cout << '\n';
      for (auto i : A) cout << i + 1 << ' ';
      cout << '\n';

      cout << "Difference:\n";
      cout << k1 << ' ' << k2 << '\n';
      for (auto i : ans1) cout << i << ' ';
      cout << '\n';
      for (auto i : ans2) cout << i << ' ';
      cout << '\n';
      return;
    }
  }
  cout << "AC\n";
}

}  // namespace checker

#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define rrep(i, a, b) for (int i = a; i > (b); --i)
#define trav(a, x) for (auto& a : x)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define pb push_back

ifstream input, judgeOut, contestantOut;
typedef long long LL;
typedef long double LD;

void ac() {
  cout << "AC" << endl;
  exit(0);
}

void wa(string reason = "Wrong answer") {
  cout << "WA" << endl;
  cerr << reason << endl;
  exit(0);
}

template <class T>
void wa(string reason, T actual, T expected) {
  cout << "WA" << endl;
  cerr << reason << endl;
  cerr << "Actual: " << actual << endl;
  cerr << "Expected: " << expected << endl;
  exit(0);
}

void ok(double score) {
  cout << "OK" << endl;
  cout << fixed << setprecision(10) << score << endl;
}

void checkAC() {
  string dummy;
  if (contestantOut >> dummy)
    wa("Output after given answer");
  else
    ac();
}

void checkOK(double score) {
  string dummy;
  if (contestantOut >> dummy)
    wa("Output after given answer");
  else
    ok(score);
}

namespace contestant {

string ans;
vector<int> permutationAnswer;
long long K = 0;

}  // namespace contestant

template <class T>
inline void getInput(T& a) {
  if (!(contestantOut >> a)) wa("Input can't be parsed");
}

int main(int argc, char** argv) {
  input = ifstream(argv[1]);
  judgeOut = ifstream(argv[2]);
  contestantOut = ifstream(argv[3]);

  int N;
  input >> N;
  long long K;
  input >> K;
  int Q;
  input >> Q;

  vector<int> P(N, -1);
  for (int i = 1; i < N; i++) {
    input >> P[i];
    P[i]--;
  }

  string ans;
  judgeOut >> ans;
  getInput(contestant::ans);

  if (ans != contestant::ans)
    wa("Answer is not the same", contestant::ans, ans);
  if (Q == 0) checkAC();
  if (ans == "TIDAK") checkAC();

  vector<int> A(N);
  for (int i = 0; i < N; i++) {
    getInput(A[i]);
    A[i]--;
    if (!(0 <= A[i] && A[i] < N)) {
      wa("Contestant A[] does not satisfy constraint");
    }
  }

  auto checkPerm = A;
  sort(all(checkPerm));
  for (int i = 0; i < N; i++) {
    if (checkPerm[i] != i) {
      wa("Contestant A[] is not a permutation");
    }
  }

  contestant::K = checker::solve(N, P, A).first;
  if (contestant::K != K) {
    wa("K count is different", contestant::K, K);
  }

  checkAC();
  return 0;
}
