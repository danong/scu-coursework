#ifndef NODE_H
#define NODE_H

#include <iostream>

// WANT: a structure with two fields: data and address
//                                    of next block
namespace DONG
{
template <class T>
class node
{
public:
    // CONSTRUCTOR
    node(const T & = T(),
         node * = NULL);

    // pre:
    // post: sets the data field to given value
    void set_data(const T &);

    // pre:
    // post: sets the link field to given address
    void set_link(node *);

    // pre:
    // post: returns the data stored in this node
    T data() const;

    // pre:
    // post: returns the address stored in this node
    node * link();

    // this version of link returns a const pointer
    // which cannot be used to modify what it is pointing to
    const node * link() const;

private:
    T data_field;
    node * link_field;
};

// TOOLKIT FUNCTIONS TO MANIPULATE LINKED LISTS

// pre: head_ptr points to the first node of a list
// post: returns the number of nodes in this list
template <class T>
std::size_t list_length(const node<T> * head_ptr);

// pre: head_ptr is the address of the first node in a list
// post: a new node has been inserted at the front of
//       the list; head_ptr has been updated to the
//       address of the new node
template <class T>
void list_head_insert(node<T> * & head_ptr,
                      const node<T> & entry);


// pre: previous_ptr is the address of a node in a linked list
//      can't be NULL
// post: a new node whose data field is entry has been inserted
//       immediately after the given node in this list
template <class T>
void list_insert(node<T> * previous_pr,
                 const node<T> & entry);

// pre: head_ptr is the address of the head node in a linked list
// post: returns the address of the first node in this list
//       whose data field is entry
//       returns NULL if no such node exists
template <class T>
node<T> * list_search(node<T> * head_ptr,
                   const node<T> & entry);
template <class T>
const node<T> * list_search(const node<T> * head_ptr,
                         const node<T> & entry);

// pre: head_ptr is the address of the first node in a linked list
// post: returns the address of the node at position pos
//       in this list
//       if pos doesn't exist, then returns NULL
template <class T>
node<T> * list_locate(node<T> * head_ptr, std::size_t pos);
template <class T>
const node<T> * list_locate(const node<T> * head_ptr ,
                         std::size_t pos);

// pre: head_ptr is the address of the first node in a linked list
// post: the node has been removed; head_ptr has been
//       updated to the address of its successor
template <class T>
void list_head_remove(node<T> * & head_ptr);

// pre: previous_ptr is the address of a node in a linked list
// post: the node following the given node has been removed
//       from the linked list
template <class T>
void list_remove(node<T> * previous_ptr);

// pre: head_ptr is the address of the first node in a linked list
// post: the entire list has been removed
//       head_ptr has been updated to NULL
template <class T>
void list_clear(node<T> * & head_ptr);

// pre: source_ptr is the address of the first node in a linked list
// post: a copy of the linked list has been created
//       head_ptr is the address of the first node of the copy
//       tail_ptr is the address of the last node of the copy
template <class T>
void list_copy(node<T> * source_ptr,
               node<T> * & head_ptr,
               node<T> * & tail_ptr);
}

#endif // NODE_H
