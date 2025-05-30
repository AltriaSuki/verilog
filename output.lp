\* Problem: ILP *\

Minimize
 obj: + 2 X1 + X2 + 3 X3

Subject To
 r_1: + XD7 + XD6 + XD5 = 1
 r_2: + Xg4 + Xg3 + Xg2 + Xg1 = 1
 r_3: + Xh3 + Xh2 + Xh1 = 1
 r_4: + Xi3 + Xi2 + Xi1 = 1
 r_5: + Xj3 + Xj2 + Xj1 = 1
 r_6: + Xk5 + Xk4 + Xk3 + Xk2 = 1
 r_7: + Xl4 + Xl3 + Xl2 = 1
 r_8: + Xm4 + Xm3 + Xm2 = 1
 r_9: + Xn5 + Xn4 + Xn3 = 1
 r_10: + Xo6 + Xo5 + Xo4 + Xo3 = 1
 r_11: + Xp6 + Xp5 + Xp4 + Xp3 + Xp2 = 1
 r_12: + Xq6 + Xq5 + Xq4 = 1
 r_13: - 6 Xq6 - 5 Xq5 - 4 Xq4 + 7 XD7 + 6 XD6 + 5 XD5 >= 1
 r_14: - 6 Xp6 - 5 Xp5 - 4 Xp4 - 3 Xp3 - 2 Xp2 + 7 XD7 + 6 XD6 + 5 XD5
 >= 1
 r_15: - 6 Xo6 - 5 Xo5 - 4 Xo4 - 3 Xo3 + 7 XD7 + 6 XD6 + 5 XD5 >= 1
 r_16: - 3 Xi3 - 2 Xi2 - Xi1 + 5 Xk5 + 4 Xk4 + 3 Xk3 + 2 Xk2 >= 1
 r_17: - 3 Xh3 - 2 Xh2 - Xh1 + 5 Xk5 + 4 Xk4 + 3 Xk3 + 2 Xk2 >= 1
 r_18: - 4 Xg4 - 3 Xg3 - 2 Xg2 - Xg1 + 5 Xk5 + 4 Xk4 + 3 Xk3 + 2 Xk2
 >= 1
 r_19: - 3 Xj3 - 2 Xj2 - Xj1 + 4 Xl4 + 3 Xl3 + 2 Xl2 >= 1
 r_20: - 3 Xi3 - 2 Xi2 - Xi1 + 4 Xl4 + 3 Xl3 + 2 Xl2 >= 1
 r_21: - 3 Xh3 - 2 Xh2 - Xh1 + 4 Xl4 + 3 Xl3 + 2 Xl2 >= 1
 r_22: - 3 Xj3 - 2 Xj2 - Xj1 + 4 Xm4 + 3 Xm3 + 2 Xm2 >= 1
 r_23: - 3 Xi3 - 2 Xi2 - Xi1 + 4 Xm4 + 3 Xm3 + 2 Xm2 >= 1
 r_24: - 4 Xm4 - 3 Xm3 - 2 Xm2 + 5 Xn5 + 4 Xn4 + 3 Xn3 >= 1
 r_25: - 4 Xl4 - 3 Xl3 - 2 Xl2 + 5 Xn5 + 4 Xn4 + 3 Xn3 >= 1
 r_26: - 5 Xk5 - 4 Xk4 - 3 Xk3 - 2 Xk2 + 6 Xo6 + 5 Xo5 + 4 Xo4 + 3 Xo3
 >= 1
 r_27: - 3 Xh3 - 2 Xh2 - Xh1 + 6 Xo6 + 5 Xo5 + 4 Xo4 + 3 Xo3 >= 1
 r_28: - 4 Xg4 - 3 Xg3 - 2 Xg2 - Xg1 + 6 Xp6 + 5 Xp5 + 4 Xp4 + 3 Xp3
 + 2 Xp2 >= 1
 r_29: - 5 Xn5 - 4 Xn4 - 3 Xn3 + 6 Xq6 + 5 Xq5 + 4 Xq4 >= 1
 r_30: - X1 + Xh1 <= 0
 r_31: - X2 + Xi1 <= 0
 r_32: - X3 + Xj1 + Xg1 <= 0
 r_33: - X1 + Xm2 + Xl2 + Xh2 <= 0
 r_34: - X2 + Xp2 + Xi2 <= 0
 r_35: - X3 + Xk2 + Xj2 + Xg2 <= 0
 r_36: - X1 + Xo3 + Xn3 + Xm3 + Xl3 + Xh3 <= 0
 r_37: - X2 + Xp3 + Xi3 <= 0
 r_38: - X3 + Xk3 + Xj3 + Xg3 <= 0
 r_39: - X1 + Xo4 + Xn4 + Xm4 + Xl4 <= 0
 r_40: - X2 + Xq4 + Xp4 <= 0
 r_41: - X3 + Xk4 + Xg4 <= 0
 r_42: - X1 + Xo5 + Xn5 <= 0
 r_43: - X2 + Xq5 + Xp5 <= 0
 r_44: - X3 + Xk5 <= 0
 r_45: - X1 + Xo6 <= 0
 r_46: - X2 + Xq6 + Xp6 <= 0

Bounds
 0 <= X1 <= 1
 0 <= X2 <= 1
 0 <= X3 <= 1
 0 <= XD5 <= 1
 0 <= XD6 <= 1
 0 <= XD7 <= 1
 0 <= Xg1 <= 1
 0 <= Xg2 <= 1
 0 <= Xg3 <= 1
 0 <= Xg4 <= 1
 0 <= Xh1 <= 1
 0 <= Xh2 <= 1
 0 <= Xh3 <= 1
 0 <= Xi1 <= 1
 0 <= Xi2 <= 1
 0 <= Xi3 <= 1
 0 <= Xj1 <= 1
 0 <= Xj2 <= 1
 0 <= Xj3 <= 1
 0 <= Xk2 <= 1
 0 <= Xk3 <= 1
 0 <= Xk4 <= 1
 0 <= Xk5 <= 1
 0 <= Xl2 <= 1
 0 <= Xl3 <= 1
 0 <= Xl4 <= 1
 0 <= Xm2 <= 1
 0 <= Xm3 <= 1
 0 <= Xm4 <= 1
 0 <= Xn3 <= 1
 0 <= Xn4 <= 1
 0 <= Xn5 <= 1
 0 <= Xo3 <= 1
 0 <= Xo4 <= 1
 0 <= Xo5 <= 1
 0 <= Xo6 <= 1
 0 <= Xp2 <= 1
 0 <= Xp3 <= 1
 0 <= Xp4 <= 1
 0 <= Xp5 <= 1
 0 <= Xp6 <= 1
 0 <= Xq4 <= 1
 0 <= Xq5 <= 1
 0 <= Xq6 <= 1

Generals
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

End
