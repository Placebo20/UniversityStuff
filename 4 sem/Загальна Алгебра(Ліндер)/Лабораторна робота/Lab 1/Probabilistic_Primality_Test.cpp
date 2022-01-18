#include "Number.h"

#include <string>
#include <ctime>

using namespace LongArithmetic;

Number power(Number a, Number b, Number mod) {
  Number res("1");
  for (int i = 0; i < std::stoi(b.ToString()); i++) {
    res = res * a;
  }
  return res - (res / mod) * mod;
}

Number gcd(Number a, Number b) {
  if (a - (a / b) * b == Number("0"))
    return b;
  if (b - (b / a) * a == Number("0"))
    return a;
  if (a > b)
    return gcd(a - (a / b) * b, b);
  return gcd(a, b - (b / a) * a);
}

int jacobi(Number n, Number k) {
  n = n - (n / k) * k; 
  int t = 1;
  while (n > Number("0")) {
    while (n - (n / Number("2")) * Number("2") == Number("0")) {
      n = n / Number("2");
      Number r = k - (k / Number("8")) * Number("8");
      if (r == Number("3") || r == Number("5"))
        t = -t;
    }
    Number temp = n;
    n = k;
    k = temp;
    if (n - (n / Number("4")) * Number("4") == Number("3") && k - (k / Number("4")) * Number("4") == Number("3"))
      t = -t;
    n = n - (n / k) * k;
  }
  return k == Number("1") ? t : 0;
}

bool Solovay_Strassen(Number n, int t) {
  for (int i = 0; i < t; i++) {
    Number a = Number("2") + Number(std::to_string(std::rand() % (std::stoi(n.ToString()) - 2)));
    Number r = power(a, (n - Number("1")) / Number("2"), n);
    if (r > Number("1") && r < n - Number("1"))
      return false;
    int j = jacobi(a, n);
    if (j < 0) 
      j += std::stoi(n.ToString());
    if (r == Number(std::to_string(j))) {}
    else {
      return false;
    }
  }
  return true;
}
