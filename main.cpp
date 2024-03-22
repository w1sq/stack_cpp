#include "stack.hpp"
#include <iostream>

int main()
{

    Stack<int> s = Stack<int>();
    s.push(1);
    s.push(2);
    std::cout << s.top() << '\n';
    s.pop();
    std::cout << s.top() << '\n';
    s.pop();
    s.push(2);
    std::cout << s.top() << '\n';

    return 0;
}