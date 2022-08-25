def floyd(f, x0):
  # Main phase of algorithm: finding a repetition x_i = x_2i.
  tortoise = f(x0) #f(x0) is the element/node next to x0.
  hare = f(f(x0))
  while tortoise != hare:
      tortoise = f(tortoise)
      hare = f(f(hare))
  # Find the position mu of first repetition.    
  mu = 0
  tortoise = x0
  while tortoise != hare:
      tortoise = f(tortoise)
      hare = f(hare) #Hare and tortoise move at same speed
      mu += 1
  # Find the length of the shortest cycle starting from x_mu
  lam = 1
  hare = f(tortoise)
  while tortoise != hare:
      hare = f(hare)
      lam += 1
  return lam, mu
