#include <iostream>
#include <vector>

class base 
{
public:
    virtual std::string call() = 0;
    virtual void recv() = 0;
    virtual void login() = 0;
};

class myclass : public base 
{
    int code = 0;
public:
    std::string call() override;
    void recv() override;
    void login() override;

};

std::string myclass::call()
{
    return "Hello";
}

void myclass::recv()
{
    return;
}

void myclass::login()
{
    return;
}

class test : public base 
{
    int code = 0;
public:
    std::string call() override;
    void recv() override;
    void login() override;

};

std::string test::call()
{
    return "Goodbye";
}

void test::recv()
{
    return;
}

void test::login()
{
    return;
}

void print(base & obj)
{
    std::cout << obj.call() << "\n";
}


int main(int argc, char const *argv[])
{
    myclass m;
    print(m);

    test t;
    print(t);

    return 0;
}
