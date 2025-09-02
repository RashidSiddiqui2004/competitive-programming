#include<iostream>
using namespace std;

// N <= 8
// 1 <= len(s[i]) <= 10
// 1 <= L <= 100
// s[i]!=s[j] for i!=j

// a, b
// l = 2 -> {ab, ba}

// ab, d
// l = 3 => {abd, dab}

// ab, d
// l = 4 => {ab_d, abd_, dab_, d_ab, _abd, _dab}
