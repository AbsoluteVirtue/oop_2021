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

    bool operator==(const int x)
    {
        return this->p == x && this->q == x;
    }

    friend bool operator==(const int lhs, const rational & rhs)
    {
        return rhs.p == lhs && rhs.q == lhs;
    }

    bool operator==(const rational & other)
    {
        return this->p == other.p && this->q == other.q;
    }

    bool operator!=(const rational & other)
    {
        return !(*this == other);
    }

    friend bool operator<(const rational & lhs, const rational & rhs)
    {
        if (lhs.q == rhs.q)
        {
            return lhs.p < rhs.p;
        }
        else 
        {
            int c = lhs.q * rhs.q;
            // can't use constructors due to reduce function, causes infinite recursion loop
            rational x, y;
            x.p = lhs.p * rhs.q;
            x.q = c;
            y.p = rhs.p * lhs.q;
            y.q = c;
            return x < y;
        }
    }

    friend bool operator>(const rational & lhs, const rational & rhs)
    {
        return rhs < lhs;
    }

    friend bool operator>=(const rational & lhs, const rational & rhs)
    {
        return !(lhs < rhs);
    }

    friend bool operator<=(const rational & lhs, const rational & rhs)
    {
        return !(rhs < lhs);
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
    assert(a == 1);
    assert(1 == a);
    assert(b == rational(2, 3));
    assert(rational(2, 3) == b);

    assert(a >= b);

    rational c(3, 4);
    assert(b < c);
    assert(c > b);

    rational d(c);
    assert(c <= d);
}
