//
// Ахо-Корасик без сжатых суффссылок
// Если построить на одной строке, то получим автомат префикс функции
// Позволяет использовать вершину как состояние дп, добавить символ -- getNxt
// Author: Kon567889
// https://codeforces.com/group/k5zYjxKFjA/contest/348918/my
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
  vector <Node> aho;
  int add(const string &s, int ptr = 0, int v = 0) {
    if (ptr == s.size()) {
      aho[v].isTerm = true;
      return v;
    }
    int to = s[ptr] - 'A';
    if (aho[v].to[to] == -1) {
      aho[v].to[to] = (int) aho.size();
      aho.emplace_back();
      aho.back().parent = v, aho.back().c = to;
    }
    return add(s, ptr + 1, aho[v].to[to], addCock);
  }
  int getSuff(int);
  int getNxt(int v, int c) {
    if (aho[v].nxt[c] != -1) {
      return aho[v].nxt[c];
    } else if (aho[v].to[c] != -1) {
      return aho[v].nxt[c] = aho[v].to[c];
    } else if (v == 0) {
      return aho[v].nxt[c] = 0;
    } else {
      return aho[v].nxt[c] = getNxt(getSuff(v), c);
    }
  }
  int getSuff(int v) {
    if (aho[v].suff != -1) {
      return aho[v].suff;
    } else if (aho[v].parent == 0) {
      return aho[v].suff = 0;
    } else {
      return aho[v].suff = getNxt(getSuff(aho[v].parent), aho[v].c);
    }
  }
};