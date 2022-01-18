# Lab 2 Task 1 Variant 4

dots = [[114,146], [147,106], [167,84], [224,56], [277,47],
[373,41], [441,45], [456,101], [453,147], [453,213],
[425,245], [382,270], [330,273], [290,248], [300,199],
[238,195], [197,212], [151,209], [105,190], [104,163]]

$sum = 0

for i in 0..dots.size-1 do
  if i == dots.size-1
    $sum += (dots[i][0] + dots[0][0]) * (dots[0][1] - dots[i][1])
  else
    $sum += (dots[i][0]+dots[i+1][0])*(dots[i+1][1]-dots[i][1])
  end
end

$sum = $sum.abs/2
print "result = " + $sum.to_s, "\n"
