#include "hash_table.h"

hash_table::hash_table(int table_size)
{
    table = std::vector<std::list<value_type> >(table_size,
                                                std::list<value_type>());
}

std::size_t hash_table::hash(const value_type & key) const
{
    std::size_t seed = 131;
    unsigned long hash = 1;
    for(std::size_t i = 0; i < key.length(); i++)
    {
        hash = (hash * seed) + key[i];
    }
    return hash % table.size();
}

bool hash_table::find(const value_type &key) const
{
    std::list<value_type> l = table[hash(key)];

    std::list<value_type>::const_iterator i;

    for (i = l.begin(); i != l.end(); ++i)
        if (*i == key)
            return true;

    return false;
}

void hash_table::insert(const value_type & key)
{
    if (find(key))
        return;

    table[hash(key)].push_front(key);


}


void hash_table::erase(const value_type & key)
{
    std::list<value_type> & l = table[hash(key)]; // note that l is a reference variable
    std::list<value_type>::iterator i;

    for (i = l.begin(); i != l.end(); ++i)
        if (*i == key)
        {
            l.erase(i);
            return;
        }

}
