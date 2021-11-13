//
//  Суффиксный автомат
//  Автомат, который принимает все подстроки строки s.
//  Каждая вершина отвечает за несколько последовательных суффиксов какого-то
//  префикса. Строится побуквенно, поддерживает построение от нескольких строк.
//

struct SuffixAutomaton {
  struct Node {
    int suf = -1, par = -1, nx[26];
    Node(int suf, int par) : suf(suf), par(par) { fill(nx, nx + 26, -1); }
  };
  vector<Node> nodes;
  int root = 0, last = 0;
  SuffixAutomaton() { nodes.emplace_back(-1, -1); }
  int addChar(int x) {
    int cur = sz(nodes);
    nodes.emplace_back(0, last);
    int p = last;
    for (; p != -1 && nodes[p].nx[x] == -1; p = nodes[p].suf)
      nodes[p].nx[x] = cur;
    if (p != -1) {
      int q = nodes[p].nx[x];
      if (nodes[q].par == p) {
        nodes[cur].suf = q;
      } else {
        int u = sz(nodes);
        nodes.push_back(nodes[q]);
        nodes[u].par = p;
        nodes[q].suf = nodes[cur].suf = u;
        for (; p != -1 && nodes[p].nx[x] == q; p = nodes[p].suf)
          nodes[p].nx[x] = u;
      }
    }
    return last = nodes[nodes[cur].par].nx[x];
  }
};
