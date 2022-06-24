#define _MAIN_ false

#include <assert.h>
#include <stdio.h>

struct rational
{
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

int gcd(int __m, int __n)
{
    while (__n != 0)
    {
        int __t = __m % __n;
        __m = __n;
        __n = __t;
    }
    return __m;
}

void reduce(rational & r) 
{
    if (r.q == 1 || r.p == 0) return;
    else 
    {
        int d = gcd(abs(r.p), r.q);
        r.p /= d;
        r.q /= d;
    }
}

char * rstr(const rational & r, char * ret) 
{
    int i = 0;

    auto f = [&] (int n)
    {
        char * start = ret + i;
        while (n) 
        {
            ret[i++] = (n % 10) + '0';
            n /= 10;
        }

        char * end = ret + i - 1; 
        while (start < end)
        {
            char tmp = *start;
            *start = *end;
            *end = tmp;

            start++;
            end--;
        }
    };

    f(r.p);
    if (r.q > 1)
    {    
        ret[i++] = '/';
        f(r.q);
    }

    return ret;
}

#include <string.h>

#if _MAIN_ 
int main(int argc, char const *argv[])
{
    rational a = cons(10, 20);
    assert(a.p == 10 && a.q == 20);

    reduce(a);
    assert(a.p == 1 && a.q == 2);

    char tmp1[100] {};
    assert(!strcmp("1/2", rstr(a, tmp1)));

    rational b = cons(100, 20);
    assert(b.p == 100 && b.q == 20);

    reduce(b);
    assert(b.p == 5 && b.q == 1);

    char tmp2[100] {};
    assert(!strcmp("5", rstr(b, tmp2)));

    rational c = cons(9, 6);
    assert(c.p == 9 && c.q == 6);

    reduce(c);
    assert(c.p == 3 && c.q == 2);

    char tmp3[100] {};
    assert(!strcmp("3/2", rstr(c, tmp3)));

    rational d = cons(12, 37);
    assert(d.p == 12 && d.q == 37);

    reduce(d);
    assert(d.p == 12 && d.q == 37);

    char tmp4[100] {};
    assert(!strcmp("12/37", rstr(d, tmp4)));
}
#endif
