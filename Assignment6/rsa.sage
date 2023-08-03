def get_roots(R, K):
    global n
    R5 = R.change_ring(ZZ)
    P = R5.parent()
    x = P.gen()
    d = R.degree()

    N = 2*d

    polys = []
    for i in range(N):
        if i < d:
            polys.append(n*(K*x)**i)
        else:
            polys.append(R5(K*x)*(K*x)**(i-d))

    L = Matrix(ZZ,N)
    for i in range(N):
        for j in range(N):
            L[i,j] = polys[i][j]

    L = L.LLL()

    S = 0
    for i in range(N):
        S += L[0,i]*(x/K)**i
    
    pot_roots = S.roots()
    
    roots = []
    for root in pot_roots:
        if root[0].is_integer():
            roots.append(ZZ(root[0]))

    return roots

def break_RSA(p_str, max_size):
    global e, c, n
    ZmodN = Zmod(n)
    p_binary_str = ''.join(['{0:08b}'.format(ord(x)) for x in p_str])

    for size in range(0, max_size, 8):
        P.<x> = PolynomialRing(ZmodN)
        a = int(p_binary_str, base=2)
        a = a<<size
        K = 2**size
        R = (a + x)^e - c
        dd = R.degree() 

        roots = get_roots(R, K)


        if roots:
            m = roots[0]
            print("m is :", m)
            m_bin = format(m,'b').zfill(size)
            message = ""
            for i in range(0, len(m_bin)//8):
                s = 8*i
                e = s + 8
                num_bin = m_bin[s:e]
                d = int(num_bin, base=2)
                message += chr(d)
            print("Password is :", message, sep='')
            print("Size of m is :", size)
            return

    print('No solution found\n')

e = 5
n = 84364443735725034864402554533826279174703893439763343343863260342756678609216895093779263028809246505955647572176682669445270008816481771701417554768871285020442403001649254405058303439906229201909599348669565697534331652019516409514800265887388539283381053937433496994442146419682027649079704982600857517093
c = 23701787746829110396789094907319830305538180376427283226295906585301889543996533410539381779684366880970896279018807100530176651625086988655210858554133345906272561027798171440923147960165094891980452757852685707020289384698322665347609905744582248157246932007978339129630067022987966706955482598869800151693

padding = "You see a Gold-Bug in one corner. It is the key to a treasure found by"
break_RSA(padding, 10*8)