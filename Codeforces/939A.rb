def solve(n, f)
  n = n.to_i
  f = f.split(&:to_i)
  for i in 0...n
    x = f[i].to_i
    y = f[x - 1].to_i
    return true if f[y - 1].to_i == i.to_i + 1
  end

  return false
end

n = gets.chomp
f = gets.chomp

if solve(n, f)
  puts "YES"
else
  puts "NO"
end
