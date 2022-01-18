# Lab 4 Task 2 Variant 9

def genMatr(n)
  m = []

  n.times {
    |i|
    row = []
    n.times {
      |j|
      if (i == j)
        row.push(1)
      else
        row.push(rand(10))
      end
    }
    m.push(row)
  }
  return m
end

def genVec(n)
  vec = []
  n.times {
    vec.push(rand(10))
  }
  return vec
end

def printVec(vec, vertical = false)
  vec.each {
    |el|
    if (vertical)
      puts "#{el} "
    else
      print "#{el} "
    end
  }
  print "\n"
end

def printMatr(matr)
  matr.each {
    |row|
    printVec(row)
  }
  print "\n"
end

def multMatrVec(matr, vec)
  res = []
  matr.each_with_index {
    |row, idx|
    sum = 0
    row.each_with_index {
      |el, idx|
      sum += el * vec[idx]
    }
    res[idx] = sum
  }
  return res
end

matr = genMatr(8)
vec = genVec(8)
res = multMatrVec(matr, vec)
puts printMatr(matr)
puts printVec(vec, true)
puts printVec(res, true)
