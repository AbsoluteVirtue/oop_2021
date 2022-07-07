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

    rational(const int x = 1, const int y = 1)
    {
        assert(y != 0);

        if (y < 0)
        {
            p = -x;
            q = -y;
        }
        else
        {
            p = x;
            q = y;
        }
        if (x != 0)
            reduce(*this);
    }

    void set_p(int x)
    {
        p = x;
    }

    void set_q(int x)
    {
        q = x;
    }

    const int get_p() { return p; }

    const int get_q() { return q; }

private:
    int p;
    int q;
};

void cons(rational * _this, const int x, const int y)
{
    assert(y != 0);

    if (y < 0)
    {
        _this->set_p(-x);
        _this->set_q(-y);
    }
    else
    {
        _this->set_p(x);
        _this->set_q(y);
    }

    if (x != 0)
        rational::reduce(*_this);
}

int main(int argc, char const *argv[])
{
    rational a;
    cons(&a, 6, 9);
    assert(2 == a.get_p() && 3 == a.get_q());

    rational b(10, 50);
    assert(1 == b.get_p() && 5 == b.get_q());

    rational c = rational(9, 2);
    assert(9 == c.get_p() && 2 == c.get_q());
}
