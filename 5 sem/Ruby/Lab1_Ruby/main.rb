# Lab 1 Variant 2

print "Enter x: \n"
$x = gets.chomp.to_f

print "Enter a,b,c,d:\n"
$a = gets.chomp.to_f
$b = gets.chomp.to_f
$c = gets.chomp.to_f
$d = gets.chomp.to_f

print "Enter s:\n"
$s = gets.chomp.to_f

$result = (Math.log($x**3)**2 + 0.375*$d)/(Math.exp($x**2) * Math.sqrt($c + $a)) + (Math.tan(Math::PI/6)**2 - $x**(3/$s))/(0.316 * $b * $c - $a**2).abs

print "Result = " + $result.to_s, "\n"
