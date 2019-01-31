#include <iostream>
#include <string>

using std::string;

class man {
public:
    man();

    man(string _name = "lili");

    man(const man &);

    man &operator=(const man &);

    ~man();

    string say_name();

    string say_sex();

    unsigned say_age();

private:
    string name;
    string sex;
    typedef unsigned date;
    date age;
};

struct Node {
    int i;
    Node *next;
};

int main()
{
    man m;
    m.say_name();
    int i = 2;
    return 0;
}

