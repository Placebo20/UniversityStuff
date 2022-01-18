# Lab 5 Task 2 Variant 15

def fun(x, i)
  (-1) ** (i + 1) * (x ** (2 * i + 1)) / (4 * i ** 2 - 1)
end

def series(f, x, n)
  x_rage = 0.1..1
  n_range = 15..58
  error = 0.001

  unless x_rage.include? x
    raise "'x' is out of range"
  end

  res, i, cur = 0.0, n, error
  if n_range.include? n
    (1..n).each do |i|
      cur = f.call(x, i)
      res += cur
    end
  else
    i = 0
    while cur.abs >= error
      cur = f.call(x, i)
      res += cur
      i += 1
    end
  end
  [res, i, cur]
end

sum, iter, error = series(method(:fun), 0.5, 10)

puts "Sum: #{sum}"
puts "Iterations: #{iter}"
puts "Error: #{error}"