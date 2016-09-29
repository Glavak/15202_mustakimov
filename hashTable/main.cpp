#include <iostream>
#include "HashTable.h"

using namespace std;

HashTable<int> getArray()
{
    return HashTable<int>(5);
}

int main()
{
    HashTable<int> array;
    array = getArray();
    array.add(42);

    cout << "Hello from main.cpp!" << endl << array[0] << endl;
    return 0;
}
