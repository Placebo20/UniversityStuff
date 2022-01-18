# Lab 3 Task 3 Variants 2, 3

def variant2
  sum = 0
  (0..9).each {
    |i|
    sum += 1.0 / (3 ** i)
  }

  return sum
end

def variant3(x)
  print "Enter n: "
  n = gets.chomp.to_i

  sum = 0
  fact = 1
  (0..n + 1).each {
    |i|
    sum += (x.to_f ** i) / fact
    fact *= (i + 1)
  }

  return sum
end

puts "Sum 1 + 1/3 + 1/3^2 + ... + 1/3^8 = #{variant2()}" , "\n"
print "Enter x for sum2: "
x = gets.chomp.to_f
puts "Sum 1 + x^1/1! + ... + x^n/n! = #{variant3(x)}"
