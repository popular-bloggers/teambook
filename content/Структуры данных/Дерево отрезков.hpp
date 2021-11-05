//
//  Дерево отрезков снизу
//  Поддерживает любые запросы, не требующие отложенных операций.
//  Источник: https://codeforces.com/blog/entry/18051
//

struct SegmentTree {
  int n;
  vector<int> t;
  SegmentTree(int n) : n(n), t(2 * n, 0) {}
  void update(int i, int d) {
    for (i += n; i > 0; i >>= 1) t[i] += d;
  }
  void get(int l, int r) {  // сумма на интервале [l; r)
    int left_res = 0, right_res = 0;
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
      if (l & 1) left_res += t[l++];
      if (r & 1) right_res += t[--r];
    }
    return left_res + right_res;
  }
};