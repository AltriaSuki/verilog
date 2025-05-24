Min
XD1 + 2XD2 + 3XD3 + 4XD4 + 5XD5 
subject to
unique:
XD5 = 1
Xg1 + Xg2 = 1
Xh1 = 1
Xi1 = 1
Xj1 = 1
Xk2 + Xk3 = 1
Xl2 = 1
Xm2 = 1
Xn3 = 1
Xo3 + Xo4 = 1
Xp2 + Xp3 + Xp4 = 1
Xq4 = 1
sequence:
5XD5 - 4Xq4 >= 1
5XD5 - 2Xp2 - 3Xp3 - 4Xp4 >= 1
5XD5 - 3Xo3 - 4Xo4 >= 1
2Xk2 + 3Xk3 - 1Xi1 >= 1
2Xk2 + 3Xk3 - 1Xh1 >= 1
2Xk2 + 3Xk3 - 1Xg1 - 2Xg2 >= 1
2Xl2 - 1Xj1 >= 1
2Xl2 - 1Xi1 >= 1
2Xl2 - 1Xh1 >= 1
2Xm2 - 1Xj1 >= 1
2Xm2 - 1Xi1 >= 1
3Xn3 - 2Xm2 >= 1
3Xn3 - 2Xl2 >= 1
3Xo3 + 4Xo4 - 2Xk2 - 3Xk3 >= 1
3Xo3 + 4Xo4 - 1Xh1 >= 1
2Xp2 + 3Xp3 + 4Xp4 - 1Xg1 - 2Xg2 >= 1
4Xq4 - 3Xn3 >= 1
resource:
Xh1 <= 2
Xi1 <= 2
Xg1 + Xj1 <= 1
Xl2 + Xm2 <= 2
Xp2 <= 2
Xg2 + Xk2 <= 1
Xn3 + Xo3 <= 2
Xp3 <= 2
Xk3 <= 1
Xo4 <= 2
Xp4 + Xq4 <= 2
binary
XD1
XD2
XD3
XD4
XD5
Xg1
Xg2
Xh1
Xi1
Xj1
Xk2
Xk3
Xl2
Xm2
Xn3
Xo3
Xo4
Xp2
Xp3
Xp4
Xq4
end
