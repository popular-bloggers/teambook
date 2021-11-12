//
//  Дерево Фенвика
//  Позволяет выполнять запросы на префиксе массива.
//  В дереве используется 1-индексация.
//

struct FenwickTree {
  static int F(int x) { return x & -x; }
  int n;
  vector<int> t;
  FenwickTree(int n) : n(n), t(n + 1, 0) {}
  void update(int i, int d) {  // a[i] += d, i \in [1; n]
    for (; i <= n; i += F(i)) t[i] += d;
  }
  int get(int r) {  // сумма на отрезке [1; r]
    int res = 0;
    for (; r > 0; r -= F(r)) res += t[r];
    return res;
  }
  int lower_bound(int sum) {  // вернёт первое r такое, что get(r) >= sum
    // или n + 1, если такого r нет
    const int K = 20;
    int i = 0;
    for (int k = 1 << K; k > 0; k >>= 1) {
      if (i + k <= n && t[i + k] < sum) {
        sum -= t[i += k];
      }
    }
    return i + 1;
  }
};