#include <queue>
#include <chrono>
#include <random>
#include <vector>
#include <string>
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>

namespace treeGenerator {
typedef std::pair<int, int> pii;
using namespace std;

// Set seed here
// std::mt19937 defaultRNG(std::chrono::steady_clock::now().time_since_epoch().count());
std::mt19937 defaultRNG(6969420);

int defaultRandInt(int l, int r) {
  assert(l <= r);
  int out = defaultRNG() % (r - l + 1) + l;
  return out;
}

int (*randint)(int, int) = defaultRandInt;

class Tree {
  // id is the tree index or numbering

 public:
  std::vector<int> p, label;
  int root = 0;
  void initialize() {
    p.push_back(-1);
    label.push_back(0);
  }

  Tree() {
    initialize();
  }
  Tree(int n) {
    if (n == 0) return;
    initialize();
    if (n > 0) random(n - 1, 0);
  }
  bool isInsideCurrentTree(int node) {
    return (node >= 0 && node < size()) || (node == -1 && size() == 0);
  }
  int size() const { return p.size(); }
  int addNode(int attachedParent) {
    assert(isInsideCurrentTree(attachedParent));
    label.push_back(size());
    p.push_back(attachedParent);
    return label.back();
  }
  void addRandomNode() {
    addNode(randint(0, size() - 1));
  }
  void random(int amountToAdd, int attachedParent) {
    assert(isInsideCurrentTree(attachedParent));
    if (amountToAdd == 1) {
      addNode(attachedParent);
      return;
    }
    amountToAdd++;
    int treeLastSize = size();
    std::vector<int> prufer, cnt;
    std::vector<std::vector<int> > g;
    g.resize(amountToAdd);
    cnt.resize(amountToAdd, 0);
    for (int i = 0; i < amountToAdd - 2; ++i) {
      int x = randint(0, amountToAdd - 1);
      prufer.push_back(x);
      ++cnt[x];
    }
    std::priority_queue<int> q;
    for (int i = 0; i < amountToAdd; ++i) if (!cnt[i]) q.push(i);
    for (auto v : prufer) {
      int u = q.top();
      g[u].push_back(v);
      g[v].push_back(u);
      q.pop();
      if (--cnt[v] == 0) q.push(v);
    }
    int x = q.top();
    q.pop();
    int y = q.top();
    g[x].push_back(y);
    g[y].push_back(x);

    std::queue<int> bfs;

    bfs.push(0);
    int _id = attachedParent;

    while (!bfs.empty()) {
      int u = bfs.front();
      cnt[u] = 1;
      bfs.pop();
      for (auto v : g[u]) {
        if (cnt[v] == 0) {
          addNode(_id);
          bfs.push(v);
        }
      }
      if (_id == attachedParent) _id = treeLastSize;
      else ++_id;
    }
  }
  void lowhigh(int n, double low, double high, int pa) {
    int sz = size();
    assert(n > 0);
    assert(low >= 0);
    assert(high <= 1);
    assert(high >= low);
    assert(pa >= 0);
    assert(pa < sz);
    addNode(pa);
    for (int i = 1; i < n; ++i) addNode(randint(round((i - 1) * low), round((i - 1) * high)) + sz);
  }
  void tall(int n, int k, int pa) {
    int sz = size();
    assert(n > 0);
    assert(k > 0);
    assert(isInsideCurrentTree(pa));
    addNode(pa);
    for (int i = sz + 1; i < sz + n; ++i) addNode(randint(std::max(sz - 1, i - k), i - 1));
  }
  void chain(int n, int pa) {
    assert(isInsideCurrentTree(pa));
    tall(n, 1, pa);
  }
  void star(int n, int pa) {
    int sz = size();
    assert(isInsideCurrentTree(pa));
    for (int i = sz + 1; i < sz + n; ++i) addNode(pa);
  }
  void flower(int n, int pa) {
    int sz = size();
    addNode(pa);
    star(n - 1, sz);
  }

  // This will make a tree with each node is a leaf or has degrees (degree + 1)
  void customDegree(int n, int pa, const std::vector<int> &degrees) {
    assert(n > 0); assert(pa >= 0); assert(pa < size());
    __gnu_pbds::tree<int, __gnu_pbds::null_type, std::less<int>, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update> remain;
    remain.insert(pa);
    n--;
    for (int degree : degrees) {
      auto it = remain.find_by_order(randint(0, remain.size() - 1));
      int u = *it;
      remain.erase(it);
      int used = std::min(n, degree);
      if (used == 0) break;
      n -= used;
      assert(degree > 0);
      for (int i = 0; i < used; ++i) {
        addNode(u);
        remain.insert(size() - 1);
      }
    }
    assert(n == 0);
  }
  // Author's gen_distinct, number 3 idea
  void distinctDegree(int n, int pa) {
    assert(n > 0); assert(pa >= 0); assert(pa < size());
    std::vector <int> degrees;
    int cnt = 0;
    for (int i = 1; cnt <= n; ++i) {
      degrees.push_back(i);
      cnt += i;
    }
    customDegree(n, pa, degrees);
  }

  // Author's gen_halving, number 4 idea
  void halvingDegree(int n, int pa) {
    assert(n > 0); assert(pa >= 0); assert(pa < size());
    std::vector <int> degrees;
    int cnt = 0;
    for (int i = n / 2; cnt <= n; i >>= 1) {
      if (i == 0) i = 1;
      degrees.push_back(i);
      cnt += i;
    }
    customDegree(n, pa, degrees);
  }

  // Author's gen_halving, number 4 idea
  void minDegree(int n, int k, int offset, int pa) {
    assert(n > 0); assert(pa >= 0); assert(pa < size());
    std::vector <int> degrees;
    for (int i = 1; i <= n; i++) {
      degrees.push_back(std::min(n - 1, randint(k, k + offset)));
    }
    customDegree(n, pa, degrees);
  }

  void maxDegree(int n, int k, int pa) {
    int sz = size();
    assert(n > 0);
    assert(k >= 2);
    assert(pa >= 0);
    assert(pa < sz);
    __gnu_pbds::tree<pii, __gnu_pbds::null_type, std::less<pii>, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update> remain;
    remain.insert(pii(pa, k - 1));
    for (int i = sz; i < sz + n - 1; ++i) {
      auto it = remain.find_by_order(randint(0, remain.size() - 1));
      int u = it->first;
      int t = it->second;
      remain.erase(it);
      if (t > 1) remain.insert(pii(u, t - 1));
      addNode(u);
      remain.insert(pii(i, k - 1));
    }
  }
  /**
   * Generate a tree with max degree k, but the tree is branched more on the index on range of
   * [low, high], where low high is floating point [0, 1]
   */
  void lowhighMaxDegree(int n, int k, double low, double high, int pa) {
    int sz = size();
    assert(n > 0);
    assert(k >= 2);
    assert(low >= 0);
    assert(high <= 1);
    __gnu_pbds::tree<pii, __gnu_pbds::null_type, std::less<pii>, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update> remain;
    remain.insert(pii(pa, k - 1));
    for (int i = sz + 1; i < sz + n + 1; ++i) {
      auto it = remain.find_by_order(randint(round((remain.size() - 1) * low), round((remain.size() - 1) * high)));
      int u = it->first;
      int t = it->second;
      remain.erase(it);
      if (t > 1) remain.insert(pii(u, t - 1));
      addNode(u);
      remain.insert(pii(i, k - 1));
    }
  }
  void complete(int n, int k, int attachedParent, bool makeRoot = 0) {
    assert(isInsideCurrentTree(attachedParent));
    assert(n > 0);
    assert(k >= 2);
    int sz = size();
    for (int i = sz; i < sz + n - 1; ++i) {
      int currentIndex = i;
      if (!makeRoot) {
        currentIndex++;
      }
      int tmpParent = ceil(1.0 * (currentIndex - sz) / (k - 1) - 1e-9) - 1;
      int realParent = sz + tmpParent;
      if (makeRoot == 1 && tmpParent == -1) {
        realParent = attachedParent;
      }
      if (makeRoot == 0) {
        realParent--;
      }
      if (makeRoot == 0 && tmpParent == 0) {
        realParent = attachedParent;
      }
      addNode(realParent);
    }
  }
  void knary(int n, int k, int pa) {
    k++;
    complete(n, k, pa);
  }
  void flowerKnary(int n, int used, int k, int pa) {
    assert(used < n);
    complete(used, k, pa);
    for (int i = used; i < n; i++) addRandomNode();
  }
  void binary(int n, int pa) {
    assert(n > 0);
    assert(pa >= 0);
    assert(pa < size());
    maxDegree(n, 3, pa);
  }
  void completeBinary(int n, int pa) {
    assert(n > 0);
    assert(pa >= 0);
    assert(pa < size());
    complete(n, 3, pa);
  }
  void silkworm(int n, int pa) {
    int sz = size();
    assert(n > 0);
    assert(pa >= 0);
    assert(pa < sz);
    int chain_len = (n + 1) / 2;
    chain(chain_len, pa);
    for (int i = sz; i + chain_len < sz + n; ++i) addNode(i);
  }
  void fork(const vector<int> chainLength, int pa) {
    for (auto children : chainLength) {
      chain(children, pa);
    }
  }
  void forkUniform(int n, int chainCount, int pa) {
    vector <int> chains(chainCount, n / chainCount);
    int total = n % chainCount;
    for (int i = 0; i < total; i++) chains[i]++;
    fork(chains, pa);
  }
  void forkUniformExtraChain(int n, int chainCount, int pa) {
    vector <int> chains(chainCount, n / chainCount);
    chains.push_back(n % chainCount);
    fork(chains, pa);
  }
  void forkSequentialLinearSequence(int n, int pa) {
    vector <int> chains;
    for (int i = 1;; i++) {
      if (!n) break;
      int cur = min(i, n);
      n -= cur;
      chains.push_back(cur);
    }
    fork(chains, pa);
  }
  void chainyChainy(int n, pair<int, int> chainLengthRange, int pa) {
    int includedTreeIndex = size() - 1;
    for(int i = 1;;i++){
      if(!n) break;
      int chainLength = randint(chainLengthRange.first, chainLengthRange.second);
      chainLength = min(chainLength, n);
      n -= chainLength;
      int lastTreeIndex = size() - 1;
      int chosenParent = randint(includedTreeIndex, lastTreeIndex);
      if(chosenParent == includedTreeIndex) chosenParent = pa;
      chain(chainLength, chosenParent);
    }
  }
  /**
   * This add leaves for index l to r
   */
  void addLeaves(int n, int l, int r) {
    assert(n > 0);
    assert(l >= 0);
    assert(r < size());
    assert(l <= r);
    for (int i = 1; i <= n; ++i) addNode(randint(l, r));
  }
  /**
   * This resizes the tree to only size n, then relabel it to normal
   */
  void resize(int n) {
    assert(n > 0);
    if (size() < n) addLeaves(n - size(), 0, size() - 1);
    else if (size() > n) {
      p.resize(n);
      label.resize(n);
      for (int i = 0; i < n; ++i) label[i] = i;
    }
  }
  int parent(int u) const {
    return p[u];
  }
  void shuffleNodes(int from = 0) {
    for (int i = 0; i < from; ++i) label[i] = i;
    for (unsigned int i = from; i < size(); ++i) {
      label[i] = i;
      std::swap(label[i], label[randint(from, i)]);
    }
  }
  void get(std::vector <int> &U, std::vector <int> &V,
           bool shuffleV = 1, bool swapV = 0) {
    U.clear();
    V.clear();
    if (shuffleV) shuffleNodes();

    for (int i = 0; i < size(); i++) {
      if (i == root) continue;
      U.push_back(label[i]);
      V.push_back(label[p[i]]);
    }
  }
  void print() {
    vector <int> U, V;
    get(U, V, 0, 0);
    for (int i = 0; i < U.size(); i++) {
      cout << U[i] << " " << V[i] << endl;
    }
  }
  void get(std::vector <int> &P, bool oneBased = 1) {
    P.clear();
    for (int i = 1; i < size(); i++) {
      P.push_back(label[p[i]] + oneBased);
    }
  }
};
}

// using namespace std;
// int main() {
//   treeGenerator::Tree randomTree;
//   vector <int> U;
//   vector <int> V;
//   randomTree.random(10, 0);
//   randomTree.complete(20, 4, 5);
//   randomTree.get(U, V, 0);
//   for (int i = 0; i < U.size(); i++) {
//     cout << U[i] << " " << V[i] << endl;
//   }

//   return 0;
// }