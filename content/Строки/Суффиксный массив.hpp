//
//  Суффиксный массив
//  Возвращает список индексов в порядке возрастания соответствующих суффиксов.
//  sa[0] = n, потому что пустой суффикс считается минимальным.
//

vector<int> suffix_array(string s) {
  int n = sz(s) + 1, a, b, lim = 256;
  vector<int> x(all(s) + 1), y(n), ws(max(n, lim)), rank(n), sa(n);
  iota(all(sa), 0);
  for (int j = 0, p = 0; p < n; j = max(1, j * 2), lim = p) {
    p = j, iota(all(y), n - j);
    for (int i = 0; i < n; i++)
      if (sa[i] >= j) y[p++] = sa[i] - j;
    fill(all(ws), 0);
    for (int i = 0; i < n; i++) ws[x[i]]++;
    for (int i = 1; i < lim; i++) ws[i] += ws[i - 1];
    for (int i = n; i--;) sa[--ws[x[y[i]]]] = y[i];
    swap(x, y), p = 1, x[sa[0]] = 0;
    for (int i = 1; i < n; i++)
      a = sa[i - 1], b = sa[i],
      x[b] = (y[a] == y[b] && y[a + j] == y[b + j]) ? p - 1 : p++;
  }
  return sa;
}
