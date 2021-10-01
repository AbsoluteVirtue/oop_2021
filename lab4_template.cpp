#include <iostream>
 
// реализация класса Vector

// реализация класса Queue

class Feed
{
    Queue numbers;
    unsigned int size{0};
public:
    void
    push(int val)
    {
        // реализация
    }

    void
    pop()
    {
        // реализация
    }

    const int &
    head()
    { 
        // реализация
    }

    const int &
    tail() 
    {
        // реализация
    }

    bool
    empty()
    {
        // реализация
    }
};

class Producer
{
    Vector values;
    unsigned int size{0};
public:
    Producer()
    {
        int val = 0;
        std::cin >> val;

        if (val > 0)
        {
            this->size = val;
            for (unsigned int i = 0; i < this->size; i++)
            {
                std::cin >> val;
                this->values += val;
            }
        }
    }

    bool produce(Feed & feed)
    {
        if (!this->size) return false;

        feed.push(this->values--);
        --this->size;

        return true;
    }
};

class Consumer
{
    Vector values;
public:
    Consumer() {}

    bool consume(Feed & feed)
    {
        if (feed.empty()) return false;

        this->values += feed.head();
        feed.pop();

        return true;
    }

    void report_status()
    {
        std::cout << this->values;
    }
};

int main(int argc, char const *argv[])
{
    Producer pro;
    Consumer con;
    Feed feed;

    while (pro.produce(feed));

    while (con.consume(feed));

    con.report_status();

    return 0;
}
