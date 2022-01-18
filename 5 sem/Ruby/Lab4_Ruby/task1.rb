# Lab 4 Task 1 Variant 9

def task1(arr)
  zIdxs = []
  nIdxs = []
  pIdxs = []

  arr.each_with_index {
    |v, i|
    if (v < 0)
      nIdxs.push(i)
    elsif (v > 0)
      pIdxs.push(i)
    else
      zIdxs.push(i)
    end
  }

  return zIdxs + nIdxs + pIdxs
end

def genArr(len)
  prng = Random.new(Time.now.nsec)
  arr = []
  len.times {
    arr.push(prng.rand(-2..2))
  }
  return arr
end

arr = genArr(15)
puts "A(15): #{arr}"
puts "C(15): #{task1(arr)}"
