#include <algorithm>
#include <iostream>
#include <cstdlib>
template <typename T>
class Stack
{
    unsigned Length;
    unsigned Capacity;
    T *array;

    bool ok() const;
    void expand();
    void shrink();

public:
    Stack();                             // Construct an empty stack with capacity = 2
    Stack(const Stack &s);               // Copy constructor
    Stack(Stack &&s);                    // Move constructor
    Stack<T> &operator=(const Stack &s); // Copy assignment
    Stack<T> &operator=(Stack &&s);      // Move assignment
    ~Stack();                            // Destructor (free the allocated memory)

    unsigned size();
    unsigned capacity();
    template <typename... Args>
    void emplace(Args &&...args);

    void push(const T &value);
    void push(T &&value);
    void pop();
    T &top();

}; // class Stack

// Expand the stack
template <typename T>
void Stack<T>::expand()
{
    if (!this->ok())
    {
        std::cout << "ERROR: cannot allocate memory for invalid stack" << std::endl;
        exit(1);
    }

    Capacity *= 2;
    T *buffer;
    try
    {
        buffer = new T[Capacity];
    }
    catch (const std::exception &exc)
    {
        std::cout << "ERROR: unable to reallocate memory for push: " << exc.what() << std::endl;
        exit(1);
    }

    for (unsigned i = 0; i < Length; i++)
    {
        buffer[i] = std::move(array[i]);
    }
    delete[] array;
    array = buffer;
    buffer = nullptr;
}

// Shrink the stack
template <typename T>
void Stack<T>::shrink()
{
    if (!this->ok())
    {
        std::cout << "ERROR: cannot allocate memory for invalid stack" << std::endl;
        exit(1);
    }

    Capacity /= 2;
    T *buffer;
    try
    {
        buffer = new T[Capacity];
    }
    catch (const std::exception &exc)
    {
        std::cout << "ERROR: unable to reallocate memory for push: " << exc.what() << std::endl;
        exit(1);
    }

    for (unsigned i = 0; i < Length; i++)
    {
        buffer[i] = std::move(array[i]);
    }
    delete[] array;
    array = buffer;
    buffer = nullptr;
}

// Check if stack is valid
template <typename T>
bool Stack<T>::ok() const
{
    return (array != nullptr) && (Length <= Capacity) && (Capacity > 0U);
}

// Default constructor
template <typename T>
Stack<T>::Stack() : Length(0), Capacity(2)
{
    if (!std::is_default_constructible_v<T>)
    {
        std::cout << "ERROR: the type cannot be default constructed" << std::endl;
        exit(1);
    }
    array = new T[Capacity]; // Allocate memory
    if (!this->ok())
    {
        std::cout << "ERROR: cannot construct default stack" << std::endl;
        exit(1);
    }
}

// Copy constructor
template <typename T>
Stack<T>::Stack(const Stack<T> &s) : Length(s.Length), Capacity(s.Capacity)
{
    if (!s.ok())
    {
        std::cout << "ERROR: cannot copy stack from invalid origin" << std::endl;
        exit(1);
    }

    array = new T[s.Capacity]; // Allocate memory
    if (array == nullptr)
    {
        std::cout << "ERROR: cannot allocate memory for stack" << std::endl;
        exit(1);
    }

    std::copy_n(s.array, s.Length, array); // Copy all elements
    if (!this->ok())
    {
        std::cout << "ERROR: cannot construct stack by copying" << std::endl;
        exit(1);
    }
}

// Move constructor
template <typename T>
Stack<T>::Stack(Stack<T> &&s)
{
    if (!s.ok())
    {
        std::cout << "ERROR: cannot move stack from invalid origin" << std::endl;
        exit(1);
    }
    Length = s.Length;
    Capacity = s.Capacity;
    array = s.array;

    s.array = nullptr;
    s.Length = 0;
    s.Capacity = 0;

    if (!this->ok())
    {
        std::cout << "ERROR: cannot construct stack by moving" << std::endl;
        exit(1);
    }
}

// Destructor
template <typename T>
Stack<T>::~Stack()
{
    if (array != nullptr)
        delete[] array;
    array = nullptr;
    Length = 0;
    Capacity = 0;
    if (this->ok())
    {
        std::cout << "ERROR: cannot destruct stack" << std::endl;
        exit(1);
    }
}

// Copy assignment
template <typename T>
Stack<T> &Stack<T>::operator=(const Stack<T> &s)
{
    VERIFY_CONTRACT(this->ok(), "ERROR: left operand of copy assignment is invalid");
    VERIFY_CONTRACT(s.ok(), "ERROR: right operand of copy assignment is invalid");

    // Handle self-assignment
    if (*this == s)
        return *this;

    // Delete previous data
    delete[] array;

    // Allocate new memory
    array = new T[s.Capacity];

    // Copy
    Length = s.Length;
    Capacity = s.Capacity;
    std::copy_n(s.array, s.Length, array); // Copy all elements

    VERIFY_CONTRACT(this->ok(), "ERROR: cannot copy stack from assignment (probable memory allocation fault)");
    return *this;
}

// Move assignment
template <typename T>
Stack<T> &Stack<T>::operator=(Stack<T> &&s)
{
    VERIFY_CONTRACT(this->ok(), "ERROR: left operand of move assignment is invalid");
    VERIFY_CONTRACT(s.ok(), "ERROR: right operand of move assignment is invalid");

    // Handle self-assignment
    if (*this == s)
        return *this;

    // Delete previous data
    delete[] array;

    // Move
    array = s, array;
    Length = s.Length;
    Capacity = s.Capacity;

    // Clear origin
    s.array = nullptr;
    s.Length = 0;
    s.Capacity = 0;

    if (!this->ok())
    {
        std::cout << "ERROR: cannot move stack from assignment" << std::endl;
        exit(1);
    }
    if (s.ok())
    {
        std::cout << "ERROR: move assignment is not destructive for origin" << std::endl;
        exit(1);
    }
    return *this;
}

/////////////
// Getters //
/////////////
template <typename T>
unsigned Stack<T>::size()
{
    if (!this->ok())
    {
        std::cout << "ERROR: cannot get size because stack is invalid" << std::endl;
        exit(1);
    }
    return Length;
}

template <typename T>
unsigned Stack<T>::capacity()
{
    if (!this->ok())
    {
        std::cout << "ERROR: cannot get capacity because stack is invalid" << std::endl;
        exit(1);
    }
    return Capacity;
}

// Copy push
template <typename T>
void Stack<T>::push(const T &value)
{
    if (!this->ok())
    {
        std::cout << "ERROR: cannot push to invalid stack" << std::endl;
        exit(1);
    }

    // reallocate
    if (Length == Capacity)
    {
        expand();
    }

    array[Length] = value;
    ++Length;
    if (!this->ok())
    {
        std::cout << "ERROR: push failed, resulting stack is invalid" << std::endl;
        exit(1);
    }
}

// Move push
template <typename T>
void Stack<T>::push(T &&value)
{
    if (!this->ok())
    {
        std::cout << "ERROR: cannot push to invalid stack" << std::endl;
        exit(1);
    }

    // reallocate
    if (Length == Capacity)
    {
        expand();
    }

    array[Length] = std::move(value);
    ++Length;
    if (!this->ok())
    {
        std::cout << "ERROR: push failed, resulting stack is invalid" << std::endl;
        exit(1);
    }
}

// Constructing in-place
template <typename T>
template <typename... Args>
void Stack<T>::emplace(Args &&...args)
{
    if (!this->ok)
    {
        std::cout << "ERROR: cannot emplace to invalid stack" << std::endl;
        exit(1);
    }
    // reallocate
    if (Length == Capacity)
    {
        expand();
    }
    array[Length] = T(std::forward<Args>(args)...);
    ++Length;
}

// Pop
template <typename T>
void Stack<T>::pop()
{
    if (!this->ok())
    {
        std::cout << "ERROR: cannot pop from invalid stack" << std::endl;
        exit(1);
    }

    if (Length == 0U)
        return;

    // reallocate
    if (4 * Length < Capacity)
    {
        shrink();
    }

    --Length;
    if (!this->ok())
    {
        std::cout << "ERROR: pop failed, resulting stack is invalid" << std::endl;
        exit(1);
    }
}

// Top
template <typename T>
T &Stack<T>::top()
{
    if (!this->ok())
    {
        std::cout << "ERROR: cannot get top element from invalid stack" << std::endl;
        exit(1);
    }
    if (Length == 0U)
    {
        std::cout << "ERROR: cannot read top element of empty stack" << std::endl;
        exit(1);
    }
    return array[Length - 1];
}
