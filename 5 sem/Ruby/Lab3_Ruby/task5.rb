require 'bigdecimal'

def Y(x, n)
  return (((2 * x**(-1/3))/(x**(2/3) - 3 * x**(-1/3))) - ((x**(2/n))/((x**(5/3)) - x**(2/n))) - ((x+1)/(x**2 - 4 * x + 3)))
end

def Z(x, n, c)
  return (Math.sin(9/8 * Math::PI + x/4)**2 - Math.sin(7/n * Math::PI + x/c**x)**2 + Math::tan(2*x - 1)**(-1/x))
end

def F(x, n, c)
  case x
  when 2...n
    return Y(x, n)
  when n...2*n
    return Z(x, n, c)
  else
    return Y(x, n) + Z(x, n, c)
  end
end

def subtask1(c, n)
  x = 1.0
  step = (n - 1)/(n + c)
  puts "step is #{step}"
  while x <= n
    puts "#{x} | #{Y(x, n).round(10)}"
    x += step
  end
end

def subtask2(c, n)
  x = Math::PI / n
  step = (Math::PI - x)/((3/2)*n + c)
  puts "step is #{step}"
  while x <= Math::PI
    puts "#{x} | #{Z(x, n, c)}"
    x += step
  end
end

def subtask3(c, n)
  x = 2.0
  step = (c - 2)/(2 * n)
  puts "step is #{step}"
  while x <= c
    puts "#{x} | #{F(x, n, c)}"
    x += step
    return if x == c && step == 0
  end
end

puts "Task 5"
print "Enter N: "
n = gets.chomp.to_f

print "Enter c: "
c = gets.chomp.to_f

puts "Subtask 1:"
puts "x  |  Y"
subtask1(c, n)


puts "\nSubtask 2:"
puts "x  |  Z"
subtask2(c, n)

puts "\nSubtask 3:"
puts "x  |  F"
subtask3(c, n)