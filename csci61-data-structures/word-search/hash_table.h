#ifndef HASH_TABLE_H
#define HASH_TABLE_H
#include <vector>
#include <iostream>
#include <list>

// CHAIN HASHING
// WANT:    maintain a collection of items hat supports the following operations
//          find(x): true iff x is in collection (n/m where m is the size of the table)
//          insert(x): adds x to collection (constant time)
//          delete(x): remove x from collection (n/m where m is the size of the table)

// WANT: support a collection of n items and
//       fast implementation of the following operations
//       FIND(x): returns true iff x is in collection
//       INSERT(x): x is added to collection
//       DELETE(x): x is removed from collection

class hash_table
{
public:

    // constants and types
    static const int DEFAULT_TABLE_SIZE = 300000;
    typedef std::string value_type;

    // constructors
    hash_table(int table_size = DEFAULT_TABLE_SIZE);

    // constant members
    // pre:
    // post: returns yes iff key is in this hash table
    bool find(const value_type & key) const;

    // pre:
    // post: key has been added to this hash table
    //       if it was not this hash table
    //       else do nothing
    void insert(const value_type &key);

    // pre:
    // post: key has been deleted from this hash table
    //       if it was in this table; otherwise do nothing
    void erase(const value_type & key);

private:
    std::vector<std::list<value_type> > table;

    // pre:
    // post: returns a table index corresponding to key
    std::size_t hash(const value_type & key) const;
};

#endif // HASH_TABLE_H
