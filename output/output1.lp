Min
2X1 + X2 + 3X3 
subject to
unique:
XD5 + XD6 + XD7 = 1
Xg1 + Xg2 + Xg3 + Xg4 = 1
Xh1 + Xh2 + Xh3 = 1
Xi1 + Xi2 + Xi3 = 1
Xj1 + Xj2 + Xj3 = 1
Xk2 + Xk3 + Xk4 + Xk5 = 1
Xl2 + Xl3 + Xl4 = 1
Xm2 + Xm3 + Xm4 = 1
Xn3 + Xn4 + Xn5 = 1
Xo3 + Xo4 + Xo5 + Xo6 = 1
Xp2 + Xp3 + Xp4 + Xp5 + Xp6 = 1
Xq4 + Xq5 + Xq6 = 1
sequence:
5XD5 + 6XD6 + 7XD7 - 4Xq4 - 5Xq5 - 6Xq6 >= 1
5XD5 + 6XD6 + 7XD7 - 2Xp2 - 3Xp3 - 4Xp4 - 5Xp5 - 6Xp6 >= 1
5XD5 + 6XD6 + 7XD7 - 3Xo3 - 4Xo4 - 5Xo5 - 6Xo6 >= 1
2Xk2 + 3Xk3 + 4Xk4 + 5Xk5 - 1Xi1 - 2Xi2 - 3Xi3 >= 1
2Xk2 + 3Xk3 + 4Xk4 + 5Xk5 - 1Xh1 - 2Xh2 - 3Xh3 >= 1
2Xk2 + 3Xk3 + 4Xk4 + 5Xk5 - 1Xg1 - 2Xg2 - 3Xg3 - 4Xg4 >= 1
2Xl2 + 3Xl3 + 4Xl4 - 1Xj1 - 2Xj2 - 3Xj3 >= 1
2Xl2 + 3Xl3 + 4Xl4 - 1Xi1 - 2Xi2 - 3Xi3 >= 1
2Xl2 + 3Xl3 + 4Xl4 - 1Xh1 - 2Xh2 - 3Xh3 >= 1
2Xm2 + 3Xm3 + 4Xm4 - 1Xj1 - 2Xj2 - 3Xj3 >= 1
2Xm2 + 3Xm3 + 4Xm4 - 1Xi1 - 2Xi2 - 3Xi3 >= 1
3Xn3 + 4Xn4 + 5Xn5 - 2Xm2 - 3Xm3 - 4Xm4 >= 1
3Xn3 + 4Xn4 + 5Xn5 - 2Xl2 - 3Xl3 - 4Xl4 >= 1
3Xo3 + 4Xo4 + 5Xo5 + 6Xo6 - 2Xk2 - 3Xk3 - 4Xk4 - 5Xk5 >= 1
3Xo3 + 4Xo4 + 5Xo5 + 6Xo6 - 1Xh1 - 2Xh2 - 3Xh3 >= 1
2Xp2 + 3Xp3 + 4Xp4 + 5Xp5 + 6Xp6 - 1Xg1 - 2Xg2 - 3Xg3 - 4Xg4 >= 1
4Xq4 + 5Xq5 + 6Xq6 - 3Xn3 - 4Xn4 - 5Xn5 >= 1
resource:
Xh1 - X1 <= 0
Xi1 - X2 <= 0
Xg1 + Xj1 - X3 <= 0
Xh2 + Xl2 + Xm2 - X1 <= 0
Xi2 + Xp2 - X2 <= 0
Xg2 + Xj2 + Xk2 - X3 <= 0
Xh3 + Xl3 + Xm3 + Xn3 + Xo3 - X1 <= 0
Xi3 + Xp3 - X2 <= 0
Xg3 + Xj3 + Xk3 - X3 <= 0
Xl4 + Xm4 + Xn4 + Xo4 - X1 <= 0
Xp4 + Xq4 - X2 <= 0
Xg4 + Xk4 - X3 <= 0
Xn5 + Xo5 - X1 <= 0
Xp5 + Xq5 - X2 <= 0
Xk5 - X3 <= 0
Xo6 - X1 <= 0
Xp6 + Xq6 - X2 <= 0
binary
X1
X2
X3
XD5
XD6
XD7
Xg1
Xg2
Xg3
Xg4
Xh1
Xh2
Xh3
Xi1
Xi2
Xi3
Xj1
Xj2
Xj3
Xk2
Xk3
Xk4
Xk5
Xl2
Xl3
Xl4
Xm2
Xm3
Xm4
Xn3
Xn4
Xn5
Xo3
Xo4
Xo5
Xo6
Xp2
Xp3
Xp4
Xp5
Xp6
Xq4
Xq5
Xq6
end
