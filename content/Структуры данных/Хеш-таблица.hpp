struct HashMap {
  const uint64_t C = ll(4e18 * acos(0)) | 71;
  uint64_t hash(uint64_t x) const { return __builtin_bswap64(x * C); }
  int n;
  vector<uint64_t> keys;
  vector<int> values;
  HashMap(int n) : n(n), keys(n, -1), values(n) {}
  int position(uint64_t key) const {
    uint64_t h = hash(key);
    int i = h % n;
    while (keys[i] != -1 && keys[i] != key)
      if (++i == n) i = 0;
    return i;
  }
  int& operator[](uint64_t key) {
    int i = position(key);
    if (keys[i] == -1) keys[i] = key, values[i] = -1;
    return values[i];
  }
};
