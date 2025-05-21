Min
XD1 + 2XD2 + 3XD3 + 4XD4 + 5XD5 + 6XD6 + 7XD7 
subject to
唯一约束:
XD6 + XD7 = 1
Xg1 + Xg2 = 1
Xh1 + Xh2 + Xh3 = 1
Xi1 + Xi2 + Xi3 = 1
Xj1 + Xj2 = 1
Xk3 + Xk4 = 1
Xl3 + Xl4 = 1
Xm3 + Xm4 = 1
Xn4 + Xn5 = 1
Xo5 + Xo6 = 1
Xp3 + Xp4 + Xp5 + Xp6 = 1
Xq5 + Xq6 = 1
顺序约束:
Xg1 + 2Xg2 - 3Xp3 - 4Xp4 - 5Xp5 - 6Xp6 <= 0
Xg1 + 2Xg2 - 3Xk3 - 4Xk4 <= 0
Xh1 + 2Xh2 + 3Xh3 - 5Xo5 - 6Xo6 <= 0
Xh1 + 2Xh2 + 3Xh3 - 3Xl3 - 4Xl4 <= 0
Xh1 + 2Xh2 + 3Xh3 - 3Xk3 - 4Xk4 <= 0
Xi1 + 2Xi2 + 3Xi3 - 3Xm3 - 4Xm4 <= 0
Xi1 + 2Xi2 + 3Xi3 - 3Xl3 - 4Xl4 <= 0
Xi1 + 2Xi2 + 3Xi3 - 3Xk3 - 4Xk4 <= 0
Xj1 + 2Xj2 - 3Xm3 - 4Xm4 <= 0
Xj1 + 2Xj2 - 3Xl3 - 4Xl4 <= 0
3Xk3 + 4Xk4 - 5Xo5 - 6Xo6 <= 0
3Xl3 + 4Xl4 - 4Xn4 - 5Xn5 <= 0
3Xm3 + 4Xm4 - 4Xn4 - 5Xn5 <= 0
4Xn4 + 5Xn5 - 5Xq5 - 6Xq6 <= 0
5Xo5 + 6Xo6 - 6XD6 - 7XD7 <= 0
3Xp3 + 4Xp4 + 5Xp5 + 6Xp6 - 6XD6 - 7XD7 <= 0
5Xq5 + 6Xq6 - 6XD6 - 7XD7 <= 0
资源约束:
Xh1 <= 2
Xi1 <= 1
Xg1 + Xj1 <= 2
Xh2 <= 2
Xi2 <= 1
Xg1 + Xj1 + Xg2 + Xj2 <= 2
Xh3 + Xl3 + Xm3 <= 2
Xi3 + Xp3 <= 1
Xg2 + Xj2 + Xk3 <= 2
Xl4 + Xm4 + Xn4 <= 2
Xp4 <= 1
Xk3 + Xk4 <= 2
Xn5 + Xo5 <= 2
Xp5 + Xq5 <= 1
Xk4 <= 2
Xo6 <= 2
Xp6 + Xq6 <= 1
