#include <assert.h>


struct rational
{
    rational() {}

    rational(const int x, const int y)
    {
        assert(y != 0);

        if (x == 0) 
        {
            this->p = 0;
            this->q = 0;
        }
        else if (y < 0)
        {
            this->p = -x;
            this->q = -y;
        }
        else
        {
            this->p = x;
            this->q = y;
        }
    }

    static rational cons(const int x, const int y)
    {
        assert(y != 0);

        if (x == 0) return {0, 0};

        rational r;
        if (y < 0)
        {
            r.p = -x;
            r.q = -y;
        }
        else
        {
            r.p = x;
            r.q = y;
        }
        return r;
    }

    void set_p(int x)
    {
        this->p = x;
    }

    void set_q(int x)
    {
        this->q = x;
    }

private:
    int p;
    int q;
};

rational cons(const int x, const int y)
{
    assert(y != 0);

    rational r;
    if (x == 0) return {0, 0};
    if (y < 0)
    {
        r.set_p(-x);
        r.set_q(-y);
    }
    else
    {
        r.set_p(x);
        r.set_q(y);
    }

    return r;
}

int main(int argc, char const *argv[])
{
    rational a = cons(5, 10);
    rational b = rational::cons(10, 50);
    rational c = rational(2, 3);
}
