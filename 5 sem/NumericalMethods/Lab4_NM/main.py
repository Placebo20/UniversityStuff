import math
from tabulate import tabulate
import sympy
from sympy.plotting import plot


def all_equal(lst):
    ELE = values[d[lst[0]]][0]
    CHECK = True

    for item in lst:
        if ELE != values[d[item]][0]:
            CHECK = False
            break;

    if (CHECK == True):
        return True;
    else:
        return False;


def div_diff(z):
  if len(z) == 1:
    return values[d[z[0]]][1]
  else:
    if all_equal(z):
      return values[d[z[0]]][len(z)] / math.factorial(len(z)-1)
    else:
      first = z.copy();
      first.pop(0);
      second = z.copy();
      second.pop();
      return (div_diff(second) - div_diff(first)) / math.factorial(values[d[z[0]]][0] - values[d[z[len(z) - 1]]][0]);


def hermite():
    res = [];
    cur_z = [];
    for i in range(len(d)):
        cur_z.insert(0, i);
        res.append(div_diff(cur_z));
    return res;


values = [[-3, 7856, -18252], [-2, 671, -1728, 4256], [-1, 32, -132, 404, -912], [0, -1, 0, 0, 0, 816], [1, 32, 132, 404, 912], [2, 671, 1728, 4256], [3, 7856, 18252]];

d = {0: 0, 1: 0, 2: 1, 3: 1, 4: 1, 5: 2, 6: 2, 7: 2, 8: 2, 9: 3, 10: 3, 11: 3, 12: 3, 13: 3, 14: 4, 15: 4, 16: 4, 17: 4, 18: 5, 19: 5, 20: 5, 21: 6, 22: 6};

print_val = [["x", "f(x)", "f′(x)", "f′′(x)", "f′′′(x)", "f′′′′(x)"]] + values;
print(tabulate(print_val))

print(div_diff([5, 4, 3, 2, 1, 0]))

coef = hermite();

print(len(coef));

print(coef);

x = sympy.symbols('x')

int_func = sympy.simplify(coef[0] + coef[1] * (x + 1) + coef[2] * (x + 1) ** 2 + coef[3] * (x + 1) ** 3 +
                          coef[4] * x * (x + 1) ** 3 + coef[5] * x ** 2 * (x + 1) ** 3 + coef[6] * x ** 3 * (x + 1) ** 3 +
                          coef[7] * (x - 1) * x ** 3 * (x + 1) ** 3 + coef[8] * (x - 1) ** 2 * x ** 3 * (x + 1) ** 3 +
                          coef[9] * (x - 1) ** 3 * x ** 3 * (x + 1) ** 3 +
                          coef[10] * (x - 2) * (x - 1) ** 3 * x ** 3 * (x + 1) ** 3 + coef[11] * (x - 2) ** 2 * (x - 1) ** 3 * x ** 3 * (x + 1) ** 3 + coef[12] * (x - 2) ** 3 * (x - 1) ** 3 * x ** 3 * (x + 1) ** 3 +
                          coef[13] * (x - 3) * (x - 2) ** 3 * (x - 1) ** 3 * x ** 3 * (x + 1) ** 3 + coef[14] * (x - 3) ** 2 * (x - 2) ** 3 * (x - 1) ** 3 * x ** 3 * (x + 1) ** 3 + coef[15] * (x - 3) ** 3 * (x - 2) ** 3 * (x - 1) ** 3 * x ** 3 * (x + 1) ** 3 +
                          coef[16] * (x - 4) * (x - 3) ** 3 * (x - 2) ** 3 * (x - 1) ** 3 * x ** 3 * (x + 1) ** 3 +
                          coef[17] * (x - 4) ** 2 * (x - 3) ** 3 * (x - 2) ** 3 * (x - 1) ** 3 * x ** 3 * (x + 1) ** 3 +
                          coef[18] * (x - 4) ** 3 * (x - 3) ** 3 * (x - 2) ** 3 * (x - 1) ** 3 * x ** 3 * (x + 1) ** 3 +
                          coef[19] * (x - 5) * (x - 4) ** 3 * (x - 3) ** 3 * (x - 2) ** 3 * (x - 1) ** 3 * x ** 3 * (x + 1) ** 3 + coef[20] * (x - 5) ** 2 * (x - 4) ** 3 * (x - 3) ** 3 * (x - 2) ** 3 * (x - 1) ** 3 * x ** 3 * (x + 1) ** 3 + coef[21] * (x - 5) ** 3 * (x - 4) ** 3 * (x - 3) ** 3 * (x - 2) ** 3 * (x - 1) ** 3 * x ** 3 * (x + 1) ** 3 +
                          coef[22] * (x - 6) * (x - 5) ** 3 * (x - 4) ** 3 * (x - 3) ** 3 * (x - 2) ** 3 * (x - 1) ** 3 * x ** 3 * (x + 1) ** 3);

print(int_func);

p1 = plot(x ** 8 - 2 * x ** 6 + 34 * x ** 4 - 1, show=False);
p2 = plot(int_func, show=False);
p2.show();
p2.append(p1[0]);
p2.show();