def solve(a, b)
  n = a.length
  k = b.length

  b.sort! { |x, y| y <=> x } 
  pointer = 0
  i = 0

  while i < n
    if a[i] == 0
      a[i] = b[pointer]
      pointer += 1
    end
    i += 1
  end
  
  i = 1

  while i < n
    if a[i] < a[i - 1]
      return true
    end
    i += 1
  end
  
  return false
end

n, k = gets.split.map(&:to_i)

line = gets.chomp
a = line.split.map(&:to_i)

line = gets.chomp
b = line.split.map(&:to_i)

if solve(a, b)
  puts "Yes"
else
  puts "No"
end
