#include <iostream>

/**
 * @class MyClass
 * @brief A simple class that outputs a message when constructed.
 *
 * The constructor prints "Constructor called" to the standard output.
 */
class MyClass {
public:
    MyClass() { std::cout << "Constructor called\n"; }
};

void testFunction() {
    MyClass obj;  // Implicit constructor invocation
}

int main() {
    testFunction();
    return 0;
}