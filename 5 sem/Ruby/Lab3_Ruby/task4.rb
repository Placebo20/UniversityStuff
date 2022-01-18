# Lab 3 Task 4 Variant 8
def task_1
  res = 0
  factorial = 2

  (2..10).each { |i|
    res += ((factorial / (i - 1)) / (factorial * (i + 1))) ** (i * (i + 1))
    factorial *= (i + 1)
  }

  res
end

def task_2(x)
  res = 0
  factorial = 1

  (0..10).each{ |i|
    res += (x.to_f ** i) / factorial
    factorial *= (i + 1)
  }

  res
end

# sum diverges
def task_3
  res = 0
  factorials = [6, 1, 6, 1]

  (1..10).each{ |i|
    res += (factorials[0] * factorials[1]) / (factorials[2] * (3 ** (2 * i)) * factorials[3])
    factorials[0] *= (4*i) * (4*i + 1) * (4*i + 2) * (4*i + 3)
    factorials[1] *= (2 * i) * (2 * i + 1)
    factorials[2] *= (3 * i + 1) * (3 * i + 2) * (3 * i + 3)
    factorials[3] *= i

  }

  res
end

print task_1.to_s + "\n"
print Math.exp(1).to_s + " " + task_2(1).to_s + "\n"
print task_3.to_s + "\n"