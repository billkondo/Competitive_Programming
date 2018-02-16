def ok(a, b, p)
  n = p.length
  x = 0
  y = 0
  for i in 0...n
    x += 1 if a[i] == p[i]
    y += 1 if b[i] == p[i]
  end
  return x == n - 1 && y == n - 1
end

def solve(a, b)
  x = -1
  y = -1
  n = a.length

  mrk = Hash.new(0)

  p = []
  for i in 0...n
    if a[i] != b[i]
      if x == -1
        x = i
        p.push(-1)
      else
        y = i
        p.push(-1)
      end
    else
      mrk[a[i]] = 1
      p.push(a[i])
    end
  end

  if y == -1
    for i in 1..n
      if mrk[i] == 0
        p[x] = i
      end
    end

    return p
  end

  lst = []
  for i in 1..n
    if mrk[i] == 0
      lst.push(i)
    end
  end

  p[x] = lst[0]
  p[y] = lst[1]

  return p if ok(a, b, p)

  p[x] = lst[1]
  p[y] = lst[0]
    
  return p
end

n = gets.split.map(&:to_i)

line = gets.chomp
a = line.split.map(&:to_i)

line = gets.chomp
b = line.split.map(&:to_i)

p = solve(a, b)
p.each { |x| print x.to_s + " " }
puts
