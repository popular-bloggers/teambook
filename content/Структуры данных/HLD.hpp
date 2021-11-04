//
// HLD на одном дереве (дерево отрезков на !отрезках!)
// Author: Kon567889
// https://codeforces.com/group/9MnDgcj9Ka/contest/321438/submission/110920615

void dfs1(int v, int p) {
  pred[v] = p;
  if (count(all(g[v]), p)) g[v].erase(find(all(g[v]), p));
  sz[v] = 1;
  for (auto &i : g[v]) {
    dfs1(i, v);
    sz[v] += sz[i];
    if (sz[i] > sz[g[v][0]]) swap(i, g[v][0]);
  }
}
void dfs2(int v, int p) {
  tin[v] = timer++;
  order.push_back(v);
  for (auto &i : g[v]) {
    up[i] = (i == g[v][0] ? up[v] : i);
    dfs2(i, v);
  }
}
void updVertical(int from, int add) { // upd path from -> 0
  ll ans = 0;
  while (true) {
    if (up[from] == 0) {
      tree.upd(1, tin[0], tin[from], add);
      break;
    }
    tree.upd(1, tin[up[from]], tin[from], add);
    from = pred[up[from]];
  }
}
void updDeep(int v, int add) { // upd subtree of v
  tree.upd(1, tin[v], tin[v] + sz[v] - 1, add); // tree -- дерево отрезков
}
// build hld
for(int i = 0; i < n; i++) {
  b[tin[i]] = a[i];
}
build(n, b);
