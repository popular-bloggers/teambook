//
//  Ахо-Корасик без сжатых суффссылок
//  Если построить на одной строке, то получим автомат префикс функции
//  Позволяет использовать вершину как состояние дп, добавить символ -- getNxt
//

struct AhoCorasick {
  struct Node {
    int parent;
    int c;
    int to[MAXM]{};
    int suff;
    int nxt[MAXM]{};
    bool isTerm;
    Node() : parent(0), c(0), suff(-1), isTerm(false) {
      memset(to, -1, sizeof to), memset(nxt, -1, sizeof nxt);
    }
  };
  vector<Node> aho;
  int add(const string &s, int v = 0) {
    int cur = 0;
    for (char c : s) {
      int ch = c - 'a';
      if (aho[cur].to[ch] != -1) {
        cur = aho[cur].to[ch];
      } else {
        int nw = sz(aho);
        aho.push_back({cur, ch});
        cur = aho[cur].to[ch] = nw;
      }
    }
    aho[cur].isTerm = true;
    return cur;
  }
  int getNxt(int v, int c);
  int getSuff(int v) {
    if (aho[v].suff == -1) {
      if (v == 0 || aho[v].parent == 0)
        aho[v].suff = 0;
      else
        aho[v].suff = getNxt(getSuff(aho[v].parent), aho[v].c);
    }
    return aho[v].suff;
  }
  int getNxt(int v, int c) {
    if (aho[v].nxt[c] == -1) {
      if (aho[v].to[c] != -1)
        aho[v].nxt[c] = aho[v].to[c];
      else if (v == 0)
        aho[v].nxt[c] = 0;
      else if aho
        aho[v].nxt[c] = getNxt(getSuff(v), c);
    }
    return aho[v].nxt[c];
  }
};