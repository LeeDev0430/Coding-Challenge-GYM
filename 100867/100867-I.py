def gcd(a, b):
    if b == 0:
        return a
    return gcd(b, a % b)

class F:
    def __init__(self, x, y):
        self.x = x
        self.y = y
        
    def __str__(self):
        return f"{self.x} {self.y}"

    def __mul__(self, num):
        new_a = self.x * num.x
        g = gcd(self.y, num.y)
        return F(new_a * g, self.y // g * (num.y // g))

    def __add__(self, num):
        return F(self.x + num.x, num.y)

def ope_fract(f, m):
    g = []
    while True:
        al = m[-1]
        h = False
        for k in f:
            if k.y % al == 0:
                h = True
        if h:
            break
        m.pop()
    al = m.pop()
    for v in f:
        if v.y % al == 0:
            g.append(v)
        else:
            g.append(F(-v.x, v.y))
    return g

def multiple(a, b):
    ans = {}
    for af in a:
        for bf in b:
            d = af * bf
            if d.y in ans:
                ans[d.y].x += d.x
            else:
                ans[d.y] = d
    return list(filter(lambda p: p.x != 0, ans.values()))

def Irrationality():
    n = int(input())
    f = list(map(lambda i: F(1, int(i)), input().split()))
    f = sorted(f, key=lambda f: -f.y)
    m = list(map(lambda f: f.y, f))
    ans = [F(1, 1)]
    
    while f[0].y > 1:
        pre = ope_fract(f, m)
        ans = multiple(ans, pre)
        f = sorted(multiple(f, pre), key=lambda f: -f.y)

    print(abs(f[0].x), len(ans))
    sgn = 1 if f[0].x > 0 else -1
    print(*map(lambda f: str(F(sgn * f.x, f.y)), sorted(ans, key=lambda f: f.y)), sep='\n')

Irrationality()