#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <utility>


/**
    *  @brief  Convert a value to an rvalue.
    *  @param  __t  A thing of arbitrary type.
    *  @return The parameter cast to an rvalue-reference to allow moving it.

    template<typename _Tp>
    constexpr typename std::remove_reference<_Tp>::type&&
    move(_Tp&& __t) noexcept
    { return static_cast<typename std::remove_reference<_Tp>::type&&>(__t); }
*/

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

    rational() {};

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

    rational(rational && other) : p(other.p), q(other.q)
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

    rational & operator=(const rational & other)
    {
        if (this != &other)
        {
            this->p = other.p;
            this->q = other.q;
        }
        return *this;
    }

    rational & operator=(rational && other)
    {
        if (this != &other)
        {
            this->p = other.p;
            this->q = other.q;
            other.p = 1;
            other.q = 1;
        }
        return *this;
    }

    bool eq(int __p, int __q)
    {
        return this->p == __p && this->q == __q;
    }

    bool eq(const rational & other)
    {
        return this->p == other.p && this->q == other.q;
    }

    bool gte(const rational & other)
    {
        if (this->q == other.q)
        {
            return this->p > other.p || this->p == other.p;
        }
        else
        {
            int c = this->q * other.q;
            // can't use constructors due to reduce function, causes infinite recursion loop
            rational x, y;
            x.p = this->p * other.q;
            x.q = c;
            y.p = other.p * this->q;
            y.q = c;

            return x.gte(y);
        }
    }

    static bool t(const rational & lhs, const rational & rhs, bool (*f)(const rational & a, const rational & b))
    {
        int c = lhs.q * rhs.q;
        // can't use constructors due to reduce function, causes infinite recursion loop
        rational x, y;
        x.p = lhs.p * rhs.q;
        x.q = c;
        y.p = rhs.p * lhs.q;
        y.q = c;

        return f(x, y);
    }

    static bool lte(const rational & lhs, const rational & rhs)
    {
        if (lhs.q == rhs.q)
        {
            return lhs.p < rhs.p || lhs.p == rhs.p;
        }
        else 
        {
            return t(lhs, rhs, lte);
        }
    }

    bool ne(const rational & other)
    {
        return !this->eq(other);
    }

    bool gt(const rational & other)
    {
        return !lte(*this, other);
    }

    bool lt(const rational & other)
    {
        return !(this->gte(other));
    }

private:
    int p{1};
    int q{1};
};

void swap(rational& a, rational& b)
{
    rational tmp(std::move(a));
    a = std::move(b);   
    b = std::move(tmp);
}

int main(int argc, char const *argv[])
{
    rational a(2, 3);
    rational b = std::move(a);
    assert(a.eq(1, 1));
    assert(b.eq(rational(2, 3)));
    
    rational c(3, 4);
    assert(b.lt(c));
    assert(c.gt(b));
}
