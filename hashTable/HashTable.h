#pragma once

#include <malloc.h>
#include <assert.h>
#include <string>
#include <utility>

typedef std::string Key;

struct Value
{
    unsigned age;
    unsigned weight;
};

struct ListItem
{
    Key key;
    Value value;
    ListItem * next;
};

class HashTable
{
public:
    HashTable();

    ~HashTable();

    // Copy constructor
    HashTable(const HashTable & b);

    // Move constructor
    HashTable(HashTable && b);


    // Обменивает значения двух хэш-таблиц.
    // Подумайте, зачем нужен этот метод, при наличии стандартной функции
    // std::swap.
    void swap(HashTable & b);

    HashTable & operator=(const HashTable & b);
    HashTable & operator=(HashTable && b);


    // Очищает контейнер.
    void clear();

    // Удаляет элемент по заданному ключу.
    bool erase(const Key & k);

    // Вставка в контейнер. Возвращаемое значение - успешность вставки.
    bool insert(const Key & k, const Value & v);

    // Проверка наличия значения по заданному ключу.
    bool contains(const Key & k) const;

    // Возвращает значение по ключу. Небезопасный метод.
    // В случае отсутствия ключа в контейнера следует вставить в контейнер
    // значение, созданное конструктором по умолчанию и вернуть ссылку на него.
    Value & operator[](const Key & k);

    // Возвращает значение по ключу. Бросает исключение при неудаче.
    Value & at(const Key & k);

    const Value & at(const Key & k) const;

    size_t size() const;

    bool empty() const;

    bool operator==(const HashTable & other) const;

    bool operator!=(const HashTable & other) const;

private:
    const int TABLE_SIZE = 256;
    ListItem ** table;

    int hash(const Key & key) const;
};
