#include <assert.h>

int gcd(int m, int n)
{
    while (n != 0)
    {
        int tmp = m % n;
        m = n;
        n = tmp;
    }
    return m;
}

struct rational
{
    static void reduce(rational &r)
    {
        if (r.q == 1 || r.p == 0)
            return;
        else
        {
            int d = gcd(abs(r.p), r.q);
            r.p /= d;
            r.q /= d;
        }
    }

    static rational cons(const int x, const int y)
    {
        assert(y != 0);

        rational r;
        if (x == 0)
        {
            r.p = 0;
            r.q = 0;
        }
        else if (y < 0)
        {
            r.p = -x;
            r.q = -y;
        }
        else
        {
            r.p = x;
            r.q = y;
        }
        reduce(r);
        return r;
    }

    void set_p(int x)
    {
        p = x;
    }

    void set_q(int x)
    {
        assert(x != 0);
        q = x;
    }

    const int get_p() { return p; }
    const int get_q() { return q; }

private:
    int p;
    int q;
};

int main(int argc, char const *argv[])
{
    rational a = rational::cons(10, 50);
    a.set_p(15);
    a.set_q(45);
    rational::reduce(a);
    assert(1 == a.get_p() && 3 == a.get_q());

    rational b = rational::cons(10, 50);
    assert(1 == b.get_p() && 5 == b.get_q());
}
