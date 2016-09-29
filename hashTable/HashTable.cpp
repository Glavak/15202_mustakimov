#include "HashTable.h"

HashTable::HashTable()
{
    table = new ListItem * [TABLE_SIZE];
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        table[i] = nullptr;
    }
}

HashTable::~HashTable()
{
    this->clear();
    delete[] table;
}

HashTable::HashTable(const HashTable & b) : HashTable()
{
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        if (b.table[i] == nullptr) continue;

        ListItem * itemB = b.table[i];

        ListItem * newItem = new ListItem;

        newItem->key = itemB->key;
        newItem->value = itemB->value;
        newItem->next = nullptr;

        table[i] = newItem;
        ListItem * lastItemA = newItem;

        itemB = itemB->next;

        while (itemB != nullptr)
        {
            newItem = new ListItem;

            newItem->key = itemB->key;
            newItem->value = itemB->value;
            newItem->next = nullptr;

            lastItemA->next = newItem;
            lastItemA = newItem;

            itemB = itemB->next;
        }
    }
}

HashTable::HashTable(HashTable && b)
{
    std::swap(table, b.table);
}

void HashTable::swap(HashTable & b)
{
    std::swap(table, b.table);
}

HashTable & HashTable::operator=(const HashTable & b)
{
    this->clear();
    delete[] table;

    for (int i = 0; i < TABLE_SIZE; i++)
    {
        if (b.table[i] == nullptr)
        {
            table[i] = nullptr;
        }
        else
        {
            ListItem * itemB = b.table[i];

            ListItem * newItem = new ListItem;

            newItem->key = itemB->key;
            newItem->value = itemB->value;
            newItem->next = nullptr;

            table[i] = newItem;
            ListItem * lastItemA = newItem;

            itemB = itemB->next;

            while (itemB != nullptr)
            {
                newItem = new ListItem;

                newItem->key = itemB->key;
                newItem->value = itemB->value;
                newItem->next = nullptr;

                lastItemA->next = newItem;
                lastItemA = newItem;

                itemB = itemB->next;
            }
        }
    }

    return *this;
}

HashTable & HashTable::operator=(HashTable && b)
{
    std::swap(table, b.table);

    return *this;
}

void HashTable::clear()
{
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        if (table[i] == nullptr) continue;

        ListItem * item = table[i];
        ListItem * nextItem;

        while (true)
        {
            nextItem = item->next;
            delete item;

            if (nextItem == nullptr) break;
            item = nextItem;
        }

        table[i] = nullptr;
    }
}

bool HashTable::erase(const Key & k)
{
    int keyHash = hash(k);

    if (table[keyHash] == nullptr)
    {
        return false;
    }
    else
    {
        if (table[keyHash]->key == k)
        {
            // It's first item in list
            ListItem * second = table[keyHash]->next;
            delete table[keyHash];
            table[keyHash] = second;
            return true;
        }
        else
        {
            if (table[keyHash]->next == nullptr) return false;

            ListItem * prevItem = table[keyHash];
            ListItem * item = prevItem->next;

            while (true)
            {
                if (item->key == k)
                {
                    ListItem * next = item->next;
                    delete item;
                    prevItem->next = next;
                    return true;
                }

                if (item->next == nullptr) return false;
                prevItem = item;
                item = item->next;
            }
        }
    }
}

bool HashTable::insert(const Key & k, const Value & v)
{
    ListItem * newItem = new ListItem;

    newItem->key = k;
    newItem->value = v;
    newItem->next = nullptr;

    int keyHash = hash(k);

    if (table[keyHash] == nullptr)
    {
        table[keyHash] = newItem;
    }
    else
    {
        ListItem * lastItem = table[keyHash];
        while (lastItem->next != nullptr) lastItem = lastItem->next;

        lastItem->next = newItem;
    }

    return true;
}

bool HashTable::contains(const Key & k) const
{
    int keyHash = hash(k);

    if (table[keyHash] == nullptr)
    {
        return false;
    }
    else
    {
        ListItem * item = table[keyHash];

        while (true)
        {
            if (item->key == k) return true;

            if (item->next == nullptr) return false;
            item = item->next;
        }
    }
}

Value & HashTable::operator[](const Key & k)
{
    int keyHash = hash(k);

    if (table[keyHash] == nullptr)
    {
        ListItem * newItem = new ListItem;

        newItem->key = k;
        newItem->value = Value();
        newItem->next = nullptr;

        table[keyHash] = newItem;
        return newItem->value;
    }
    else
    {
        ListItem * item = table[keyHash];

        while (true)
        {
            if (item->key == k) return item->value;

            if (item->next == nullptr)
            {
                ListItem * newItem = new ListItem;

                newItem->key = k;
                newItem->value = Value();
                newItem->next = nullptr;

                item->next = newItem;
                return newItem->value;
            }
            item = item->next;
        }
    }
}

Value & HashTable::at(const Key & k)
{
    int keyHash = hash(k);

    if (table[keyHash] == nullptr)
    {
        throw "No such element";
    }
    else
    {
        ListItem * item = table[keyHash];

        while (true)
        {
            if (item->key == k) return item->value;

            if (item->next == nullptr) throw "No such element";
            item = item->next;
        }
    }
}

const Value & HashTable::at(const Key & k) const
{
    int keyHash = hash(k);

    if (table[keyHash] == nullptr)
    {
        throw "No such element";
    }
    else
    {
        ListItem * item = table[keyHash];

        while (true)
        {
            if (item->key == k) return item->value;

            if (item->next == nullptr) throw "No such element";
            item = item->next;
        }
    }
}

size_t HashTable::size() const
{
    size_t size = 0;

    for (int i = 0; i < TABLE_SIZE; i++)
    {
        ListItem * item = table[i];
        while (item != nullptr)
        {
            size++;
            item = item->next;
        }
    }

    return size;
}

bool HashTable::empty() const
{
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        if (table[i] != nullptr)
        {
            return false;
        }
    }

    return true;
}

int HashTable::hash(const Key & key) const
{
    int result = 0;
    for (int i = 0; i < key.length(); i++)
    {
        result += key[i];
    }
    return result % TABLE_SIZE;
}

bool HashTable::operator==(const HashTable & other) const
{
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        if (table[i] == nullptr && other.table[i] == nullptr)
        {
            continue;
        }
        if (table[i] == nullptr || other.table[i] == nullptr)
        {
            return false;
        }

        ListItem * item = table[i];

        while (item != nullptr)
        {
            ListItem * otherItem = other.table[i];

            while (!(otherItem == nullptr ||
                     (otherItem->value.age == item->value.age &&
                      otherItem->value.weight == item->value.weight)))
            {
                otherItem = otherItem->next;
            }
            if (otherItem == nullptr)
            {
                // item not found in other.table
                return false;
            }

            item = item->next;
        }
    }
    return true;
}

bool HashTable::operator!=(const HashTable & other) const
{
    return !(*this == other);
}
