//
//  Heavy-Light Decomposition
//  Позволяет выполнять запросы на путях в дереве.
//  Источник: https://codeforces.com/blog/entry/53170
//

struct HLD {
  int n, t = 0;
  vector<vector<int>> g;
  vector<int> tin, siz, par, h, up;
  SegmentTree st;
  HLD(int n, const vector<vector<int>> &g)
      : n(n), g(g), tin(n), siz(n, 1), par(n), h(n), up(n), st(n) {
    par[0] = -1, h[0] = 0, up[0] = 0;
    dfs_sz(0);
    dfs_up(0);
  }
  void dfs_sz(int v) {
    if (par[v] != -1) g[v].erase(find(all(g[v]), par[v]));
    for (int &u : g[v]) {
      par[u] = v, h[u] = h[v] + 1;
      dfs_sz(u);
      siz[v] += siz[u];
      if (siz[u] > siz[g[v][0]]) swap(u, g[v][0]);
    }
  }
  void dfs_up(int v) {
    tin[v] = t++;
    for (int u : g[v]) {
      if (u == g[v][0])
        up[u] = up[v];
      else
        up[u] = u;
      dfs_up(u);
    }
  }
  int get_path(int v, int u) {  // запрос на пути от v до u
    int res = 0;
    for (; up[v] != up[u]; v = par[up[v]]) {
      if (h[up[v]] < h[up[u]]) swap(v, u);
      res += st.get(tin[up[v]], tin[v] + 1);
      // если значения на рёбрах, прибавить к левой границе +1
    }
    if (h[v] > h[u]) swap(v, u);
    res += st.get(tin[v], tin[u] + 1);
    return res;
  }
  int get_subtree(int v) { return st.get(tin[v], tin[v] + siz[v]); }
};
