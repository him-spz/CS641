def add(a,b,m):
    return (a+b)%m

def mult(a,b,m):
    return (a*b)%m

def power(x,n,m):
    if n == 0:
        return 1
    elif n == 1:
        return x
    elif n == m - 1:
        return 1

    temp = power(x, n//2, m)
    temp = mult(temp, temp, m)
    if n%2 == 0:
        return temp
    else:
        return mult(temp, x, m)

def inverse(x,m):
    return power(x, m-2, m)

p = 19807040628566084398385987581
a1 = 324;   x1 = 11226815350263531814963336315
a2 = 2345;  x2 = 9190548667900274300830391220
a3 = 9513;  x3 = 4138652629655613570819000497

inv_x1 = inverse(x1,p)

print("inv_x1 =", inv_x1)

y_21 = mult(x2, inv_x1, p)
y_31 = mult(x3, inv_x1, p)
print("y_21 =  ", y_21)
print("y_31 =  ", y_31)

A = 0; B = 0

A_21 = int(a2-a1)
A_31 = int(a3-a1)
print("\na2-a1 =", A_21, "\ta3-a1 =", A_31)

for A_ in range(1,1000):
    B_ = (1 - A_21*A_)/A_31
    # print(y)
    if B_.is_integer():
        A = A_%(p-1); B = int(B_)%(p-1)           # As the calulated y is negative, the value of B we take is y (mod p-1)
        print("A =", A, "\tB =", B, '\n')
        break

g21 = power(y_21, A, p)
g31 = power(y_31, B, p)
print("g21 =\t  ", g21)
print("g31 =\t  ", g31)

g = mult(g21, g31, p)
print("g =\t  ", g)
g_inv = inverse(g,p)
print("g_inv =\t  ", g_inv)
g_inv_a1 = power(g_inv, a1, p)
print("g_inv_a1 =", g_inv_a1)
print("password =", mult(x1,g_inv_a1, p))