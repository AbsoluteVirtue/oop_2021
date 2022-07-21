#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <utility>


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

    rational() = delete;

    rational(const int x, const int y)
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

    rational(const rational & other) : p(other.p), q(other.q) {}

    rational(rational && other) : p(std::move(other.p)), q(std::move(other.q))
    {
        other.p = 1;
        other.q = 1;
    }

    rational(const char * str)
    {
        int __p = 1, __q = 1;
        if (sscanf(str, "%d/%d", &__p, &__q) >= 1)
        {
            this->p = __p;
            this->q = __q;
            if (this->p != 0)
                reduce(*this);
        } 
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
    int p{1};
    int q{1};
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
    rational a(2, 3);

    rational b(a); 
    cons(&b, 6, 9);
    assert(2 == b.get_p() && 3 == b.get_q());

    rational c = rational(9, 2);
    assert(9 == c.get_p() && 2 == c.get_q());

    rational d(10, 50);
    assert(1 == d.get_p() && 5 == d.get_q());

    rational e("3/15");
    assert(1 == e.get_p() && 5 == e.get_q());
    
    rational f("315");
    assert(315 == f.get_p() && 1 == f.get_q());

    rational g(std::move(e));
    assert(1 == e.get_p() && 1 == e.get_q());
    assert(1 == g.get_p() && 5 == g.get_q());
}
