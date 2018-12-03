
//
//  File: FCI_Final_solutions.cpp (2016)
//  Author: SOLUTIONS
//

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cfloat>
#include <climits>
#include <limits>
#include <cmath>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
using namespace std;


///////////////////////  clist (pointer-to-cl_node) module /////////////////////////

/* --------- the definition of the cl_node struct -------- */

struct cl_node {
    char data;
    cl_node *next;
};

// (18) is_vowel
bool is_vowel(char c)
{
    switch (c) {
    case 'a': case 'e': case 'i': case 'o': case 'u':
    case 'A': case 'E': case 'I': case 'O': case 'U':
        return true;
    default:
        return false;
    }
}

// (18) clist_count_if
size_t clist_count_if(const cl_node *clist, bool (*pf)(char))
{
    size_t count(0);

    for ( ; clist; clist = clist->next)
        if (pf(clist->data))
            count += 1;

    return count;
}

// (15) overload << for clist
ostream& operator<<(ostream& os, const cl_node *clist)
{
    for ( ; clist; clist = clist->next)
        cout << clist->data;
    return os;
}

// (16) mk_clist_merge
cl_node *mk_clist_merge(const cl_node *clist1, const cl_node *clist2)
{
    cl_node *ret = nullptr;
    cl_node *last = nullptr;
    while (clist1 || clist2) {
        if (clist1) {
            if (!ret) {
                last = ret = new cl_node{clist1->data, nullptr};
            }
            else {
                last = last->next = new cl_node{clist1->data, nullptr};
            }
            clist1 = clist1->next;
        }
        if (clist2) {
            if (!ret) {
                last = ret = new cl_node{clist2->data, nullptr};
            }
            else {
                last = last->next = new cl_node{clist2->data, nullptr};
            }
            clist2 = clist2->next;
        }
    }
    return ret;
}

// (17) mk_clist_rev
cl_node *mk_clist_rev(const cl_node *clist)
{
    cl_node *first = nullptr;
    for ( ; clist; clist = clist->next) {
        first = new cl_node{clist->data,first};
    }
    return first;
}

// clist creation functions
cl_node *mk_clist_from_Cstring(const char *s)
{
   cl_node *first(nullptr);
   cl_node *last(nullptr);
   for ( ; *s; ++s) {
      cl_node *pnew = new cl_node{*s, nullptr};
      if (!last) {
         last = first = pnew;
      }
      else {
         last = last->next = pnew;
      }
   }
   return first;
}

// Very similar to mk_clist_from_Cstring
cl_node *mk_copy_clist(cl_node *cl)
{
    cl_node *first(nullptr);
    cl_node *last(nullptr);

    for ( ; cl; cl = cl->next)
    {
        cl_node *pnew = new cl_node{cl->data, nullptr};
        if (!last) {	// your compiler might need:  if (last == nullptr)
            last = first = pnew;
        }
        else {
            last = last->next = pnew;
        }
    }

    return first;
}

// You can essentially rewrite mk_clist_from_Cstring, or just call it!
cl_node *mk_clist_from_string(string s)
{
    return mk_clist_from_Cstring(s.c_str());
}

// This provides a consistent interface function for creating empty lists,
// even though the implementation is trivial.
cl_node *mk_empty_clist()
{
	return nullptr;
}

// clist access functions
size_t clist_size(const cl_node *cl)
{
   size_t size(0);
   for ( ; cl; cl = cl->next)
      size += 1;
   return size;
}

void clist_display_to_cout(const cl_node *cl)
{
   for ( ; cl; cl = cl->next)
      cout << cl->data;
}

// we return size_t because the count cannot be negative
size_t clist_count_char(const cl_node *cl, char c)
{
   size_t nc(0);

   for ( ; cl; cl = cl->next) {
      if (cl->data == c) {
         nc += 1;
      }
   }

   return nc;
}

// clist element modification functions
void clist_to_uppercase(cl_node *cl)
{
   // depends on ASCII character set
   for ( ; cl; cl = cl->next) {
      if ('a' <= cl->data && cl->data <= 'z') {
         cl->data -= 'a' - 'A';
      }
   }
}

// clist deletion function (a shape modifying function)
void clist_delete(cl_node **p_cl)
{
   while (*p_cl) {
      cl_node *tmp = *p_cl;
      *p_cl = (*p_cl)->next;
      delete tmp;
   }
}

void clist_append_char(cl_node **p_cl, char c)
{
   while (*p_cl) {              // while we have not found the end (nullptr)
      p_cl = &(*p_cl)->next;    // move p_cl to point to the next handle
   }
   *p_cl = new cl_node{ c, nullptr };  // and add the new node at the end
}

void clist_delete_dups(cl_node **p_cl)
{
   while (*p_cl) {              // while we have not found the end
      // if there is a next node and its data equals the current node's data ...
      if ((*p_cl)->next && (*p_cl)->data == (*p_cl)->next->data) {
         // save the address of the next node
         cl_node *tmp = (*p_cl)->next;
         // make the current node point to the next node's next node
         (*p_cl)->next = (*p_cl)->next->next;
         // delete the saved node
         delete tmp;
         // DO NOT bump p_cl, because the new next node might be another duplicate, like in "aaaaa"
      }
      else {
         // bump p_cl to point to the next node's handle
         p_cl = &(*p_cl)->next;
      }
   }
}

// we could make pos a size_t, but if the user made a mistake and entered a negative
// position, pos would be initialized to a large positive number
// it's better (perhaps) to check for that error inside the function
void clist_insert_clist(cl_node **p_cl_dst, cl_node *cl_src, int pos)
{
   // if pos is < 0, bail out
   if (pos < 0) {
      return;
   }
   // bump p_cl_dst forward pos times OR until we hit the end of the destination list
   while (pos && *p_cl_dst) {
      --pos;
      p_cl_dst = &(*p_cl_dst)->next;
   }
   // if we reached the end of the destination before pos steps, bail out
   if (pos > 0) {
      return;
   }

   // at this point, p_cl_dst points at the pointer-to-cl_node where we need to insert
   // a copy of the cl_src character list

   // save *p_cl_dst so we can re-attach it to the end of the copy of the source
   cl_node *rest = *p_cl_dst;  // the rest of the destination list
   // we can already make a copy of a character list, so do that
   *p_cl_dst = mk_copy_clist(cl_src);
   // now find the end of the copied part ...
   while (*p_cl_dst) {
      p_cl_dst = &(*p_cl_dst)->next;
   }
   // ... and re-attach the rest of the destination list at that point
   *p_cl_dst = rest;
}

// extra post-TA session example function
void clist_delete_first_match(cl_node **p_cl, char c)
{
    while (*p_cl) {                  // we have not hit the end
        if ((*p_cl)->data == c) {    // we have found the first match
            cl_node *tmp = *p_cl;    // prepare to delete this node
            *p_cl = (*p_cl)->next;   // point past the node to delete
            delete tmp;              // delete the node with data == c
            return;                  // and we are out of here
        }
        p_cl = &(*p_cl)->next;       // point to next cl_node pointer
    }
}


/////////////////////// BinaryTree class /////////////////////////

/* --------- the definition of the BinaryTree class -------- */

struct bt_node;      // we promise this exists somewhere!

class BinaryTree {
public:
    BinaryTree();
    BinaryTree(const BinaryTree&);
// (22)
    BinaryTree(int *, size_t);
    BinaryTree& operator=(const BinaryTree&);
    ~BinaryTree();
    void insert(int);
    void put();
    void put_to_ostream(ostream&);
    void put_pretty();
    int min();
    int max();
    int sum();
    int size();
    double mean();
// (23)
    size_t depth();
// (24)
    bool is_balanced();
// (25)
    void operator+=(int);	// could return a BinaryTree or BinaryTree reference
// (26)
    void operator+=(const BinaryTree&);	// could return a BinaryTree or BinaryTree reference
// (27)
    void delete_greater_than(int);
// (28)
    void insert_random_values(int);
    bool is_identical(const BinaryTree&);
    bool operator==(const BinaryTree&);
    bool operator!=(const BinaryTree&);
    friend ostream& operator<<(ostream&, BinaryTree&);
private:
    bt_node *top;
};

/* --------- bt_node structure "helper" function declarations -------- */

bt_node *mk_binary_tree_copy(bt_node *top);
void binary_tree_insert_unique(bt_node **ptop, int);
void binary_tree_delete(bt_node **ptop);
void put_binary_tree(bt_node *top);
void put_binary_tree_to_ostream(bt_node *top, ostream& os);
void put_binary_tree_pretty(bt_node *top);
int binary_tree_min(bt_node *top);
int binary_tree_max(bt_node *top);
int binary_tree_sum(bt_node *top);
int binary_tree_size(bt_node *top);
double binary_tree_mean(bt_node *top);
bool binary_trees_are_identical(const bt_node *top1, const bt_node *top2);
void binary_tree_values_left_to_right(const bt_node *top, vector<int>& values);
// (23)
size_t binary_tree_depth(const bt_node *top);
// (24)
bool binary_tree_is_balanced(const bt_node *top);
// (25)
void binary_tree_add_int(bt_node *top, int);  // changes values, but not shape
// (26)
void binary_tree_add_tree(bt_node **ptop, const bt_node *other_top);
// (27)
void binary_tree_delete_greater_than(bt_node **ptop, int val);

/* --------- BinaryTree member function definitions --------- */

// (22)
BinaryTree::BinaryTree(int *a, size_t dim)
: top(nullptr)
{
    for (size_t i(0); i < dim; ++i)
        binary_tree_insert_unique(&top, a[i]);
}

// (23)
size_t BinaryTree::depth()
{
    return binary_tree_depth(top);
}

// (24)
bool BinaryTree::is_balanced()
{
    return binary_tree_is_balanced(top);
}

// (25)
void BinaryTree::operator+=(int val)
{
    binary_tree_add_int(top, val);
}

// (26)
void BinaryTree::operator+=(const BinaryTree& other)
{
    binary_tree_add_tree(&top, other.top);
}

// (27)
void BinaryTree::delete_greater_than(int val)
{
    binary_tree_delete_greater_than(&top, val);
}

// (28)
void BinaryTree::insert_random_values(int n)
{
    for (int i(0); i < n; ++i)
        insert(rand() % 201 - 100);
}

// default constructor
BinaryTree::BinaryTree()
: top(0)
{}

// copy constructor
BinaryTree::BinaryTree(const BinaryTree& other)
: top(mk_binary_tree_copy(other.top))
{
}

// assignment operator
BinaryTree& BinaryTree::operator=(const BinaryTree& other)
{
    if (this == &other)
        return *this;    // assign a tree to itself: nothing to do

    binary_tree_delete(&this->top);  // free the existing nodes

    this->top = mk_binary_tree_copy(other.top);

    return *this;
}

// is_identical
bool BinaryTree::is_identical(const BinaryTree& other)
{
    if (this == &other)
        return true;   // a tree is identical to itself
    return binary_trees_are_identical(this->top, other.top);
}

// destructor
BinaryTree::~BinaryTree()
{
    binary_tree_delete(&top);
}

void BinaryTree::insert(int value)
{
    binary_tree_insert_unique(&top, value);
}

void BinaryTree::put()
{
    put_binary_tree(top);
}

void BinaryTree::put_to_ostream(ostream& os)
{
    put_binary_tree_to_ostream(top, os);
}

void BinaryTree::put_pretty()
{
    put_binary_tree_pretty(top);
}

int BinaryTree::min()
{
    return binary_tree_min(top);
}

int BinaryTree::max()
{
    return binary_tree_max(top);
}

int BinaryTree::sum()
{
    return binary_tree_sum(top);
}

int BinaryTree::size()
{
    return binary_tree_size(top);
}

double BinaryTree::mean()
{
    return binary_tree_mean(top);
}

// equality test
bool BinaryTree::operator==(const BinaryTree& other)
{
    vector<int> this_values;
    binary_tree_values_left_to_right(this->top, this_values);

    vector<int> other_values;
    binary_tree_values_left_to_right(other.top, other_values);

    return this_values == other_values;
}

// inequality test
bool BinaryTree::operator!=(const BinaryTree& other)
{
    return !operator==(other);
}

/* --------- friend functions --------- */

// friend function "put to"
ostream& operator<<(ostream& os, BinaryTree& bt)  // (g)
{
    bt.put_to_ostream(os);
    return os;
}


/* --------- the definition of the bt_node structure -------- */

struct bt_node {
    int value;       // the current values
    bt_node *left;   // lower values to the left
    bt_node *right;  // higher values to the right
};

/* --------- helper functions for interacting with the tree -------- */

// (23)
size_t binary_tree_depth(const bt_node *top)
{
    if (!top) return 0;
    return 1 + max(binary_tree_depth(top->left), binary_tree_depth(top->right));
}

// (24)
bool binary_tree_is_balanced(const bt_node *top)
{
    if (!top) return true;  // an empty tree is balanced
    // are depths of subtrees within 1 at this level?
    size_t left_depth = binary_tree_depth(top->left);
    size_t right_depth = binary_tree_depth(top->right);
    if (left_depth != right_depth && left_depth != right_depth + 1 && left_depth + 1 != right_depth) {
        return false;
    }
    // are both subtrees also balanced?
    return binary_tree_is_balanced(top->left) && binary_tree_is_balanced(top->right);
}

// (25)
void binary_tree_add_int(bt_node *top, int val)
{
    if (top) {
        top->value += val;
        binary_tree_add_int(top->left, val);
        binary_tree_add_int(top->right, val);
    }
}

// (26)
void binary_tree_add_tree(bt_node **ptop, const bt_node *other_top)
{
    if (other_top) {
        binary_tree_insert_unique(ptop, other_top->value);
        binary_tree_add_tree(ptop, other_top->left);
        binary_tree_add_tree(ptop, other_top->right);
    }
}

// (27)
void binary_tree_delete_greater_than(bt_node **ptop, int val)
{
    if (!*ptop) return;  // nothing to do
    binary_tree_delete_greater_than(&(*ptop)->left, val);
    binary_tree_delete_greater_than(&(*ptop)->right, val);
    if ((*ptop)->value > val) {
        // save the node to delete
        bt_node *tmp = *ptop;
        // find the right-most leaf of left subtree
        bt_node **pr_of_l = &(*ptop)->left;
        while (*pr_of_l) {
            pr_of_l = &(*pr_of_l)->right;
        }
        // attach the right subtree there
        *pr_of_l = (*ptop)->right;
        // make *ptop point at left subtree
        *ptop = (*ptop)->left;
        // delete node
        delete tmp;
    }
}


void binary_tree_values_left_to_right(const bt_node *top, vector<int>& values)
{
    if (!top)  // nothing to do
        return;

    // left-hand values, followed by top value, followed by
    // right-hand values
    binary_tree_values_left_to_right(top->left, values);
    values.push_back(top->value);
    binary_tree_values_left_to_right(top->right, values);
}

// put_binary_tree does NOT change the tree, so we only
// need to pass it a COPY of the top pointer from main
void put_binary_tree(bt_node *top)
{
    if (top) {
        put_binary_tree(top->left);
        cout << top->value << " ";
        put_binary_tree(top->right);
    }
}

void put_binary_tree_to_ostream(bt_node *top, ostream& os)
{
    if (top) {
        put_binary_tree_to_ostream(top->left, os);
        os << top->value << " ";
        put_binary_tree_to_ostream(top->right, os);
    }
}

void put_binary_tree_pretty_with_indent(bt_node *top, int level)
{
    if (!top)
        return;

    put_binary_tree_pretty_with_indent(top->right, level + 1);
    for (int i(0); i < level; ++i)
        cout << '\t';
    cout << top->value << '\n';
    put_binary_tree_pretty_with_indent(top->left, level + 1);
}

void put_binary_tree_pretty(bt_node *top)
{
    if (!top)
        return;

    put_binary_tree_pretty_with_indent(top, 0);
}

void put_binary_tree_rev(bt_node *top)
{
    if (top) {
        put_binary_tree_rev(top->right);
        cout << top->value << " ";
        put_binary_tree_rev(top->left);
    }
}

int binary_tree_max(bt_node *top)
{
    if (!top)
        return 0;

    int max(top->value);
    for (bt_node *p(top->right); p; p = p->right)
        max = p->value;

    return max;
}

int binary_tree_min(bt_node *top)
{
    if (!top)
        return 0;

    int min(top->value);
    for (bt_node *p(top->left); p; p = p->left)
        min = p->value;

    return min;
}

int binary_tree_sum(bt_node *top)
{
    if (!top)
        return 0;

    return binary_tree_sum(top->left)
           + top->value
           + binary_tree_sum(top->right);
}

int binary_tree_size(bt_node *top)
{
    if (!top)
        return 0;

    return binary_tree_size(top->left)
           + 1
           + binary_tree_size(top->right);
}

double binary_tree_mean(bt_node *top)
{
    if (!top)
        return DBL_MIN;

    return 1.0 * binary_tree_sum(top) / binary_tree_size(top);
}

bt_node *mk_binary_tree_copy(bt_node *top)
{
    if (!top)
        return nullptr;

    return new bt_node{ top->value,
                        mk_binary_tree_copy(top->left),
                        mk_binary_tree_copy(top->right) };
}

bool binary_trees_are_identical(const bt_node *top1, const bt_node *top2)
{
    if (top1 == 0 && top2 == 0)
        return true;    // empty trees are identical
    if (top1 == 0) // && top2 != 0
        return false;   // empty and non-empty trees are not identical
    if (top2 == 0) // && top1 != 0
        return false;   // empty and non-empty trees are not identical
    if (top1->value != top2->value)
        return false;   // if top values differ, trees are not identical

    // else, top values are equal, so
    // return whether both left subtrees and right subtrees are identical
    return binary_trees_are_identical(top1->left, top2->left)
           && binary_trees_are_identical(top1->right, top2->right);
}


// binary_tree_insert_unique DOES change the tree, so we must pass
// in a POINTER to the top pointer.  That is, ptop is a
// pointer-to pointer-to-bt_node.
void binary_tree_insert_unique(bt_node **ptop, int val)
{
    if (*ptop) {  // we are not at the bottom yet
        if (val < (*ptop)->value) // left for <
            binary_tree_insert_unique(&(*ptop)->left, val);
        else if (val > (*ptop)->value)  // right for >
            binary_tree_insert_unique(&(*ptop)->right, val);
    } else {
        *ptop = new bt_node{val, nullptr, nullptr};
    }
}

// binary_tree_delete DOES change the tree (by deleting all
// the individual nodes) so we must pass in a POINTER to the
// top pointer.  That is, ptop is a pointer-to
// pointer-to-bt_node.
void binary_tree_delete(bt_node **ptop)
{
    if (*ptop) {
        binary_tree_delete(&(*ptop)->left);
        binary_tree_delete(&(*ptop)->right);
        delete *ptop;
        *ptop = 0;
    }
}


/////////////////////// DoublyLinkedList class /////////////////////////

/* --------- the definition of the DoublyLinkedList class -------- */

class DoublyLinkedList {
public:
    DoublyLinkedList();        // default constructor
    DoublyLinkedList(int);     // construct a one-node list
    DoublyLinkedList(int,int); // construct a two-node list
    ~DoublyLinkedList();       // destructor
    void put_rev(ostream &) const;   // display the list in reverse
                                     // to some ostream
    void push_back(int);
    void pop_back();
    void push_front(int);
    void pop_front();
    int front() const;
    int back() const;

    DoublyLinkedList(const DoublyLinkedList&);
    DoublyLinkedList& operator=(const DoublyLinkedList&);

    int size() const;
    int min() const;
    int max() const;
    int sum() const;
    double mean() const;

// (29)
    bool operator==(const DoublyLinkedList&);
    bool operator!=(const DoublyLinkedList&);
// (30)
    void operator+=(int);                         // could return a DoublyLinkedList or reference
// (31)
    void operator+=(const DoublyLinkedList&);     // could return a DoublyLinkedList or reference
// (32)
    void rotate(int);
// (33)
    void delete_if(bool (*pf)(int));        // could return a DoublyLinkedList or reference

    friend ostream& operator<<(ostream&, const DoublyLinkedList&);
    struct Data;
private:
    Data *d_ptr;               // a pointer to some Data
};

/* --------- the definitions of the DoublyLinkedList member functions -------- */

// define what each node looks like
struct DoublyLinkedList::Data {
    int value;
    DoublyLinkedList::Data *next;
    DoublyLinkedList::Data *prev;
};

// define a type with a more familiar name, "dll_node"
typedef DoublyLinkedList::Data dll_node;

// Now we can pretend we have:
// struct dll_node {
//     int value;
//     dll_node *next;
//     dll_node *prev;
// };

// (29)
bool DoublyLinkedList::operator==(const DoublyLinkedList& other)
{
    if (this == &other) return true;          // a list equals itself

    if (!d_ptr && !other.d_ptr) return true;  // empty lists are equal

    if (!d_ptr || !other.d_ptr) return false; // an empty list is not equal to a non-empty list

    int sz = size();
    if (sz != other.size()) return false;     // different size lists are not equal

    // lists are non-empty and the same size, so check the values
    dll_node *this_ptr = d_ptr;
    dll_node *other_ptr = other.d_ptr;
    while (sz--) {
        if (this_ptr->value != other_ptr->value) {
            return false;                     // values differ
        }
        this_ptr = this_ptr->next;
        other_ptr = other_ptr->next;
    }

    // all the values must be the same
    return true;
}

bool DoublyLinkedList::operator!=(const DoublyLinkedList& other)
{
    return !operator==(other);
}

// (30)
void DoublyLinkedList::operator+=(int i)
{
    push_back(i);
}

// (31)
void DoublyLinkedList::operator+=(const DoublyLinkedList& other)
{
    int sz = other.size();	// does not matter if this == &other
    for (const dll_node *other_ptr(other.d_ptr); sz--; other_ptr = other_ptr->next) {
        push_back(other_ptr->value);
    }
}

// (32)
void DoublyLinkedList::rotate(int i)
{
    if (d_ptr) {
        if (i > 0) {
            while (i--) {
                d_ptr = d_ptr->prev;
            }
        }
        else if (i < 0) {
            while (i++) {
                d_ptr = d_ptr->next;
            }
        }
    }
}

// (33)
void DoublyLinkedList::delete_if(bool (*pf)(int))
{
    // delete matching values at the front of the list
    while (d_ptr && pf(d_ptr->value)) {
        dll_node *tmp = d_ptr;
        if (d_ptr == d_ptr->next) {    // one-node list
            d_ptr = 0;
        }
        else {
            d_ptr->next->prev = d_ptr->prev;
            d_ptr->prev->next = d_ptr->next;
            d_ptr = d_ptr->next;
        }
        delete tmp;
    }
    if (!d_ptr) return; // empty list: nothing left to do

    // delete matching values from the rest of the list
    for (dll_node *pn = d_ptr->next; pn != d_ptr; ) {
        if (pf(pn->value)) {
            dll_node *tmp = pn;
            pn->next->prev = pn->prev;
            pn->prev->next = pn->next;
            pn = pn->next;
            delete tmp;
        }
        else {
            pn = pn->next;
        }
    }
}


// default constructor: empty list
DoublyLinkedList::DoublyLinkedList()
: d_ptr(0)  // sets d_ptr to point nowhere
{ }

// constructor for a one-node (one value) list
DoublyLinkedList::DoublyLinkedList(int val)
: d_ptr(new dll_node)  // allocate one new node
{
    d_ptr->value = val;
    d_ptr->next = d_ptr;
    d_ptr->prev = d_ptr;
}

// constructor for a two-node (two value) list
DoublyLinkedList::DoublyLinkedList(int val1, int val2)
: d_ptr(new dll_node)  // allocate first node
{
    d_ptr->value = val1;
    d_ptr->next = new dll_node;  // allocate second node
    d_ptr->prev = d_ptr->next;   // which is both next AND
                                 // prev of first node

    d_ptr->next->value = val2;   // second node's value
    d_ptr->next->next = d_ptr;   // first node is both next
    d_ptr->next->prev = d_ptr;   // AND prev of second node
}

// destructor
DoublyLinkedList::~DoublyLinkedList()
{
    if (!d_ptr)  // list is empty: nothing to do
        return;

    // delete from last to (but not including) first
    for (dll_node *last = d_ptr->prev; last != d_ptr; ) {
        dll_node *second_to_last = last->prev;
        delete last;
        last = second_to_last;
    }

    // delete first
    delete d_ptr;
    d_ptr = 0;    // okay, but not needed, since the
                  // DoublyLinkedList object itself will
                  // be deallocated as soon as the
                  // destructor is finished
}

// size
int DoublyLinkedList::size() const
{
    if (!d_ptr)
        return 0;

    // count from first to last
    int count = 1;
    for (dll_node *p(d_ptr->next); p != d_ptr; p = p->next)
        ++count;

    return count;
}

// min
int DoublyLinkedList::min() const
{
    if (!d_ptr)
        return 0.0;  // undefined

    // check from first to last
    int min = d_ptr->value;
    for (dll_node *p(d_ptr->next); p != d_ptr; p = p->next)
        if (p->value < min)
            min = p->value;

    return min;
}

// max
int DoublyLinkedList::max() const
{
    if (!d_ptr)
        return 0.0;  // undefined

    // check from first to last
    int max = d_ptr->value;
    for (dll_node *p(d_ptr->next); p != d_ptr; p = p->next)
        if (p->value > max)
            max = p->value;

    return max;
}

// sum
int DoublyLinkedList::sum() const
{
    if (!d_ptr)
        return 0.0;  // undefined

    // sum from first to last
    int sum = d_ptr->value;
    for (dll_node *p(d_ptr->next); p != d_ptr; p = p->next)
        sum += p->value;

    return sum;
}

// mean
double DoublyLinkedList::mean() const
{
    if (!d_ptr)
        return 0.0;  // undefined

    return 1.0 * sum() / size();
}

// copy constructor
DoublyLinkedList::DoublyLinkedList(const DoublyLinkedList& other)
: d_ptr(0)
{
    // if other is empty, set this empty
    if (other.d_ptr == 0) {
        return;
    }

    // loop through the other list's nodes in reverse, until we
    // have circled back to the first node again, pushing
    // each node's value in front
    for (dll_node *p(other.d_ptr->prev); p != other.d_ptr; p = p->prev)
        push_front(p->value);

    // finally, push the other list's first node in front
    push_front(other.d_ptr->value);
}

// assignment
DoublyLinkedList& DoublyLinkedList::operator=(const DoublyLinkedList& other)
{
    if (this == &other)
        return *this;     // self assignment: do nothing

    // delete this list first (we could be smarter about
    // trying to re-use existing nodes, but....)
    while (d_ptr)
        pop_back();

    // loop through the other list's nodes in reverse, until we
    // have circled back to the first node again, pushing
    // each node's value in front
    for (dll_node *p(other.d_ptr->prev); p != other.d_ptr; p = p->prev)
        push_front(p->value);

    // finally, push the other list's first node in front
    push_front(other.d_ptr->value);

    return *this;
}


// push_back()
void DoublyLinkedList::push_back(int val)
{
    if (d_ptr == 0) {
        // create and initialize first node
        d_ptr = new dll_node{val, 0, 0};
        d_ptr->next = d_ptr;
        d_ptr->prev = d_ptr;
    }
    else {
        // create and initialize new node
        dll_node *new_dll_node = new dll_node{val, 0, 0};
        new_dll_node->next = d_ptr;
        new_dll_node->prev = d_ptr->prev;

        // new node is former last node's next node
        d_ptr->prev->next = new_dll_node;
        // new node is first node's prev node
        d_ptr->prev = new_dll_node;
    }
}

// pop_back()
void DoublyLinkedList::pop_back()
{
    if (d_ptr == 0)     // or if (!d_ptr)
        return;         // empty list: do nothing

    if (d_ptr == d_ptr->next) { // single node
        delete d_ptr;   // delete it
        d_ptr = 0;      // and set list to empty
    }
    else {       // >1 nodes
    
        // save address of second-to-last node
        dll_node *second_to_last(d_ptr->prev->prev);
    
        delete d_ptr->prev;    // delete last node
    
        // fix up first->prev, last->next
        d_ptr->prev = second_to_last;
        second_to_last->next = d_ptr;
    }
}

// push_front(int)
void DoublyLinkedList::push_front(int val)
{
    if (d_ptr == 0) {
        // create and initialize first node
        d_ptr = new dll_node{val, 0, 0};
        d_ptr->next = d_ptr;
        d_ptr->prev = d_ptr;
    }
    else {
        // create and initialize new node
        dll_node *new_dll_node = new dll_node{val, 0, 0};
        new_dll_node->next = d_ptr;
        new_dll_node->prev = d_ptr->prev;

        // new node is last node's next node
        d_ptr->prev->next = new_dll_node;
        // new node is former first node's prev node
        d_ptr->prev = new_dll_node;
        // new node is new first node
        d_ptr = new_dll_node;
    }
}

// pop_front()
void DoublyLinkedList::pop_front()
{
    if (d_ptr == 0)     // or if (!d_ptr)
        return;         // empty list: do nothing

    if (d_ptr == d_ptr->next) { // single node
        delete d_ptr;   // delete it
        d_ptr = 0;      // and set list to empty
    }
    else {       // >1 nodes
    
        // save address of second node
        dll_node *second(d_ptr->next);

        // make second node's prev be last node
        second->prev = d_ptr->prev;
        // make last node's next be second node
        d_ptr->prev->next = second;
    
        delete d_ptr;    // delete first node

        d_ptr = second;  // second node is now first
    }
}

// front()
int DoublyLinkedList::front() const
{
    if (!d_ptr)
        return 0;     // undefined

    return d_ptr->value;
}

// back()
int DoublyLinkedList::back() const
{
    if (!d_ptr)
        return 0;     // undefined

    // Notice how easy this is, because the list is circular.
    // We don't have to use a loop to get to the end.
    return d_ptr->prev->value;
}

// display the list in reverse
void DoublyLinkedList::put_rev(ostream& os) const
{
    if (!d_ptr) return;  // empty list: do nothing

    // display the rest of the nodes in reverse, until we
    // have circled back to the first node again
    for (dll_node *p(d_ptr->prev); p != d_ptr; p = p->prev)
        os << p->value << " ";

    // finally, display the first node's value
    os << d_ptr->value;
}

// overload operator<<
ostream& operator<<(ostream& os, const DoublyLinkedList& dll)
{
    // if the list is not empty...
    if (dll.d_ptr) {

        // display first through second-to-last values
        for (dll_node *p(dll.d_ptr); p != dll.d_ptr->prev; p = p->next)
            os << p->value << " ";

        // display last value
        os << dll.d_ptr->prev->value;
    }

    return os;
}


/////////////////////// DoubleVector class /////////////////////////

/* --------- the definition of the DoubleVector class -------- */

class DoubleVector {
public:
    DoubleVector();          // default constructor
    ~DoubleVector();         // destructor
    void push_back(double);  // insert value at back
    void pop_back();         // erase value at back
    double front();          // return value from front
    double back();           // return value from back

    DoubleVector(const DoubleVector&);
    DoubleVector& operator=(const DoubleVector&);
    friend ostream& operator<<(ostream&, const DoubleVector&);

private:
    double *pa;	// pointer to array of doubles
    int dim;	// dimension of the array, that
    		// is, the number of values
    		// currently stored in the array
    int cap;	// the total capacity of the array,
    		// that is, the total number of values
    		// that can be stored in the array
    		// before it becomes necessary to
    		// allocate additional space
    		// 0 <= dim <= cap
};

/* --------- the definitions of the DoubleVector member functions -------- */

// default constructor
DoubleVector::DoubleVector()
: pa(0), dim(0), cap(0)
{}

// OR
// DoubleVector::DoubleVector()
// {
//     pa = 0;
//     dim = 0;
//     cap = 0;
// }


// copy constructor
DoubleVector::DoubleVector(const DoubleVector& other)
{
    this->pa = new double[other.cap];
    this->cap = other.cap;
    this->dim = other.dim;
    for (int i(0); i < other.dim; ++i)
    	this->pa[i] = other.pa[i];
}

// copy constructor: alternative implementation
// DoubleVector::DoubleVector(const DoubleVector& other)
// : pa(new double[other.cap], cap(other.cap), dim(other.dim)
// {
//     for (int i(0); i < other.dim; ++i)
//     	this->pa[i] = other.pa[i];
// }


// assignment operator
DoubleVector& DoubleVector::operator=(const DoubleVector& other)
{
    // assignment to self?  Nothing to do
    if (this == &other)
    	return *this;

    if (this->cap < other.dim) {
        delete[] this->pa;
        this->pa = new double[other.cap];
        this->cap = other.cap;
    }
    this->dim = other.dim;
    for (int i(0); i < other.dim; ++i)
    	this->pa[i] = other.pa[i];

    // remember to return *this when done
    return *this;
}

// "put to" or insert operator: an example
// Yours can be much simpler than this
ostream& operator<<(ostream& os, const DoubleVector& dv)
{
    os << "[dim: " << dv.dim << ", cap: " << dv.cap << "] ";
    os << "{ ";
    for (int i(0); i < dv.dim; ++i)
    	os << dv.pa[i] << " ";
    os << "}";
    return os;
}

// destructor
DoubleVector::~DoubleVector()
{
    delete[] pa;
}

// push_back
void DoubleVector::push_back(double value)
{
    // make sure there is available capacity
    if (dim >= cap) {    // we need more capacity!
    	// increase cap by some arbitrary increment
    	cap += 5;
    	// allocate a new, larger array
    	double *new_pa = new double[cap];
    	// copy the values from the original array
    	for (int i(0); i < dim; ++i)
    		new_pa[i] = pa[i];
    	delete[] pa; // deallocate the original array
    	pa = new_pa; // use new, larger array instead
    }

    // store value at end of pa, then increment dim
    pa[dim++] = value;

}

// pop_back: behavior undefined if array is empty
void DoubleVector::pop_back()
{
    if (dim == 0) return; // nothing to pop: do nothing
    // else simply "forget" the final value ...
    --dim;  // ... by decrementing dim
}

// front: behavior undefined if array is empty
double DoubleVector::front() {
    if (dim == 0) return 0.0;  // undefined behavior
    return pa[0];
}

// back: behavior undefined if array is empty
double DoubleVector::back() {
    if (dim == 0) return 0.0;  // undefined behavior
    return pa[dim - 1];
}

/////////////////////// Employee struct and global array /////////////////////////

struct Employee { 
    int id;           // ID number
    char name[10];    // First name (a C-string) 
    double rate;      // Hourly rate 
}; 

void put_Emp(Employee e) {
    cout << "Name: " << e.name << ", ID: " << e.id
         << ", Rate: " << e.rate;
}

const int max_emps(10);
  
Employee company[max_emps] = {
        { 1, "Kevin", 57.5 },
        { 2, "John", 62.0 },
        { 3, "Youran", 58.25 },
        { 4, "Florian", 62.13 },
        { 5, "Beiming", 59.88 },
        { 6, "Prashanth", 61.50 },
        { 7, "Wenbin", 62.50 },
        { 8, "Hongchen", 61.05 }
};

// (3) counter function
size_t counter()
{
    static size_t count = 1;
    return count++;
}

// (8) rotate function
void rotate(int *pi, int *pj, int *pk)
{
    int temp = *pk;
    *pk = *pj;
    *pj = *pi;
    *pi = temp;
}

// (9) C-string comparison
int scomp(const char *s1, const char *s2)
{
    while (*s1 && *s1 == *s2) {
        ++s1;
        ++s2;
    }
    // now either *s1 == *s2 are both '\0', or *s1 != *s2
    if (*s1 < *s2) return -1;
    if (*s1 > *s2) return 1;
    return 0;
}

// (10) put_rev_str
void put_rev_str(const char *s)
{
    if (*s) {
        put_rev_str(s + 1);
        cout << *s;
    }
}

// (11) put_Emp2
void put_Emp2(const Employee& e) {
    cout << e.name << ' ' << e.id << ' ' << e.rate;
}

// (19) put_base_5, pb5_help
void pb5_help(unsigned u)
{
    if (u) {
        pb5_help(u / 5);
        cout << u % 5;
    }
}

void put_base_5(int i)
{
    if (i == 0) {
        cout << 0;
    }
    else if (i < 0) {
        cout << '-';
        pb5_help(-i);
    }
    else {
        pb5_help(i);
    }
}

// (20) Fib
int Fib(int i)
{
    if (i < 0)
        return -1;
    else if (i == 0)
        return 0;
    else if (i == 1)
        return 1;
    else
        return Fib(i - 2) + Fib(i - 1);
}

// (21) Part class
class Part {
public:
    Part(const string&, unsigned, double);
    Part(const Part&);
    Part& operator=(const Part&);
    ~Part();
    friend ostream& operator<<(ostream&, const Part&);
    void set_price(double);
private:
    Part();		// cannot be called (or just leave this out)
    string name;
    unsigned num;
    double price;
};

Part::Part(const string& n, unsigned i, double p)
: name(n), num(i), price(p)
{
    // optional stuff
    if (price < 0) {
        cout << "Part " << name << " has bogus price: " << price << '\n';
        price = 0.10;
        cout << "price set to 0.10\n";
    }
}

Part::Part(const Part& other)
: name(other.name), num(other.num), price(other.price)
{
    // or:
    // name = other.name;
    // num = other.num;
    // price = other.price;
}

Part& Part::operator=(const Part& other)
{
    if (this == &other)
        return *this;

    name = other.name;
    num = other.num;
    price = other.price;

    return *this;
}   

Part::~Part()
{
    cout << "Part destructor called\n";
}

ostream& operator<<(ostream& os, const Part& p)
{
    cout << "Part name: " << p.name << ", num: " << p.num
         << ", price: " << p.price;
}

void Part::set_price(double p)
{
    if (p > 0.0)
        price = p;
}

// (33) top-level functions
bool is_prime(int i)
{
    switch(i) {
    case 2:
    case 3:
    case 5:
    case 7:
    case 11:
    case 13:
    case 17:
    case 19:
        return true;
    default:
        return false;
    }
}

bool is_neg(int i)
{
    return i < 0;
}

bool is_ge_12(int i)
{
    return i >= 12;
}


/////////////////////// main function /////////////////////////

int main()
{
    // clist module test code
    cl_node *clist1 = mk_clist_from_Cstring("hello");
    cl_node *clist2 = mk_empty_clist();
    cout << "clist1 contains: ";
    clist_display_to_cout(clist1);
    cout << "\n";
    cout << "clist2 contains: ";
    clist_display_to_cout(clist2);
    cout << "\n";
    clist_insert_clist(&clist2, clist1, 0);
    cout << "now clist2 contains: ";
    clist_display_to_cout(clist2);
    cout << "\n";
    clist_to_uppercase(clist2);
	clist_append_char(&clist2, '!');
    cout << "and now clist2 contains: ";
    clist_display_to_cout(clist2);
    cout << "\n";

    // BinaryTree class test code
    BinaryTree t1;

    cout << "t1 initially contains: [ ";
    t1.put();
    cout << " ]\n";

    t1.insert(12);
    t1.insert(7);
    t1.insert(-4);
    t1.insert(13);
    t1.insert(9);
    t1.insert(29);
    t1.insert(12);  // should not be inserted
    t1.insert(7);   // should not be inserted
    t1.insert(-4);  // should not be inserted
    t1.insert(-9);
    t1.insert(123);
    t1.insert(22);
    t1.insert(0);

    cout << "t1 contains: [ ";
    t1.put();
    cout << " ]\n";

    cout << "t1 contains: [ ";
    t1.put_to_ostream(cout);
    cout << " ]\n";

    cout << "t1 min: " << t1.min() << "\n";
    cout << "t1 max: " << t1.max() << "\n";
    cout << "t1 sum: " << t1.sum() << "\n";
    cout << "t1 size: " << t1.size() << "\n";
    cout << "t1 mean: " << t1.mean() << "\n";

    BinaryTree t2(t1);

    cout << "t2 initially contains: [ ";
    t2.put();
    cout << " ]\n";

    // NOTICE how to put " inside of a string literal!
    cout << "\"pretty print\" of t1:\n";
    t1.put_pretty();
    cout << "\n";

    cout << "\"pretty print\" of t2:\n";
    t2.put_pretty();
    cout << "\n";
    cout << "\nt1 and t2 should be identical!\n\n";

    BinaryTree t3;
    t3.insert(888);
    t3.insert(-888);
    cout << "t3 initially contains: [ ";
    t3.put();
    cout << " ]\n";

    t3 = t2;
    cout << "after t3 = t2, t3 contains: [ ";
    t3.put();
    cout << " ]\n";

    BinaryTree t4;
    t4.insert(12);  t4.insert(5);  t4.insert(30);

    BinaryTree t5(t4);

    BinaryTree t6;
    t6.insert(30);  t6.insert(12);  t6.insert(5);

    if (t4.is_identical(t5))
        cout << "t4 and t5 are identical\n";
    else
        cout << "t4 and t5 are NOT identical\n";

    if (t4.is_identical(t6))
        cout << "t4 and t6 are identical\n";
    else
        cout << "t4 and t6 are NOT identical\n";

    if (t4 == t5)
        cout << "t4 == t5\n";
    else
        cout << "t4 != t5\n";

    if (t4 != t1)
        cout << "t4 != t1\n";
    else
        cout << "t4 == t1\n";

    cout << "The values stored in t4 are\n[ "
         << t4
         << " ]\n\n";

    // DoublyLinkeList class test code

    DoublyLinkedList empty_list;
    DoublyLinkedList one_node_list(12);
    DoublyLinkedList two_node_list(4, -7);

    cout << "in reverse, empty_list contains: ";
    empty_list.put_rev(cout);
    cout << "\n";

    cout << "in reverse, one_node_list contains: ";
    one_node_list.put_rev(cout);
    cout << "\n";

    cout << "in reverse, two_node_list contains: ";
    two_node_list.put_rev(cout);
    cout << "\n";

    const DoublyLinkedList cdlist1(-2, 4);

    cout << "in reverse, cdlist1 contains: ";
    cdlist1.put_rev(cout);
    cout << "\n";

    cout << "in order, empty_list contains: "
         << empty_list << "\n";
    cout << "in order, one_node_list contains: "
         << one_node_list << "\n";
    cout << "in order, two_node_list contains: "
         << two_node_list << "\n";
    cout << "in order, cdlist1 contains: "
         << cdlist1 << "\n";

    const DoublyLinkedList cdlist2(7, 13);

    cout << "in order, cdlist2 contains: " << cdlist2 << "\n";
    cout << "cdlist2.front(): " << cdlist2.front() << "\n";
    cout << "cdlist2.back(): " << cdlist2.back() << "\n";

    empty_list.push_front(1);
    empty_list.push_front(2);
    empty_list.push_back(7);
    empty_list.push_front(-4);
    empty_list.push_back(-13);
    cout << "after 5 pushes, empty_list contains: "
         << empty_list << "\n";

    empty_list.pop_front();
    empty_list.pop_back();
    cout << "after 2 pops, empty_list contains: "
         << empty_list << "\n";

    DoublyLinkedList dlist4(cdlist2);

    cout << "dlist4 initially contains: " << dlist4 << "\n";
    cout << "dlist4.front(): " << dlist4.front() << "\n";

    dlist4.push_back(-6);
    dlist4.push_front(3);
    dlist4.push_back(1);
    cout << "after 3 pushes, dlist4 contains: "
         << dlist4 << "\n";

    empty_list = dlist4;
    cout << "after assignment, empty_list contains: "
         << empty_list << "\n";

    const DoublyLinkedList cdlist3(dlist4);

    cout << "cdlist3 initially contains: " << cdlist3 << "\n";
    cout << "cdlist3.size(): " << cdlist3.size() << "\n\n";

    // DoubleVector class test code

    DoubleVector dv1;
    dv1.push_back(12);
    dv1.push_back(9);
    dv1.push_back(-3);
    cout << "dv1 contains: " << dv1 << '\n';

cout << "// (3) counter function\n";
    cout << counter() << '\n';
    cout << counter() << '\n';
    cout << counter() << '\n';
    cout << '\n';

cout << "// (4) variable initialization\n";
    double x(sqrt(2.0)), y{exp(2.0)}, z = log(123);
    cout << x << ' ' << y << ' ' << z << '\n' ;
    cout << '\n';

cout << "// (5) manipulators\n";
    cout << fixed << setprecision(9);
    cout << setw(15) << 22.0/7 << setw(15) << 2.0/3 << setw(15) << sqrt(2) << '\n';
    cout << resetiosflags(ios::fixed) << setprecision(6);
    cout << setw(15) << 22.0/7 << setw(15) << 2.0/3 << setw(15) << sqrt(2) << '\n';
    cout << '\n';

cout << "// (6) string object\n";
    string s("monopolize");
    cout << s << '\n';
    size_t el_pos = s.find('i');
    if (el_pos != string::npos) {
        s.erase(el_pos, 2);
        cout << s << '\n';
    }
    s.insert(0, "magnetic ");
    cout << s << '\n';
    cout << '\n';

cout << "// (7) array of int\n";
    int a[10]{ 0 };  // all 0 now
    for (int el : a)
        cout << setw(10) << el;
    cout << '\n';
    a[0] = 1;
    for (int i(1); i < 10; ++i)
        a[i] = a[i-1] * 2;
    for (int el : a)
        cout << setw(10) << el;
    cout << '\n';
    cout << '\n';

cout << "// (8) pointer parameters\n";
    int i(9), j(3), k(5);
    cout << i << ' ' << j << ' ' << k << '\n';
    rotate(&i, &j, &k);
    cout << i << ' ' << j << ' ' << k << '\n';
    cout << '\n';

cout << "// (9) string comparison\n";
    cout << scomp("ape", "app") << '\n';
    cout << scomp("apple", "app") << '\n';
    cout << scomp("ape", "ape") << '\n';
    cout << '\n';

cout << "// (10) put_rev_str\n";
    const char *p = "hello, world!";
    cout << p << '\n';
    put_rev_str(p); cout << '\n';
    cout << '\n';

cout << "// (11) put_Emp2\n";
    put_Emp2(company[0]);
    cout << '\n';
    cout << '\n';

cout << "// (12) even id numbers\n";
    for (Employee el : company) {
        if (el.id && el.id % 2 == 0) {
            put_Emp2(el);
            cout << '\n';
        }
    }
    cout << '\n';

cout << "// (13) rate >= 60\n";
    for (Employee el : company) {
        if (el.rate >= 60.0) {
            put_Emp2(el);
            cout << '\n';
        }
    }
    cout << '\n';

cout << "// (14) name contains 'o'\n";
    for (Employee el : company) {
        bool found_it = false;
        for (char *pn = el.name; *pn && !found_it; ++pn) {
            if (*pn == 'o') {
                found_it = true;
                put_Emp2(el);
                cout << '\n';
            }
        }
    }
    cout << '\n';

cout << "// (15) overload << for clist\n";
    cl_node *clist6 = mk_clist_from_Cstring("Hello, world");
    cout << clist6 << '\n';
    cout << '\n';

cout << "// (16) mk_clist_merge\n";
    cl_node *clist7 = mk_clist_from_Cstring("leopard");
    cout << clist7 << '\n';
    cl_node *clist8 = mk_clist_merge(clist6, clist7);
    cout << clist8 << '\n';
    cl_node *clist9 = mk_clist_merge(clist7, clist6);
    cout << clist9 << '\n';
    cout << '\n';

cout << "// (17) mk_clist_rev\n";
    cl_node *clist10 = mk_clist_rev(clist7);
    cout << clist10 << '\n';
    cout << '\n';

cout << "// (18) clist_count_if\n";
    cout << clist_count_if(clist6, is_vowel) << '\n';
    cout << '\n';

cout << "// (19) put_base_5\n";
    put_base_5(0); cout << '\n';
    put_base_5(5); cout << '\n';
    put_base_5(26); cout << '\n';
    put_base_5(-26); cout << '\n';
    put_base_5(INT_MIN); cout << '\n';
    cout << '\n';

cout << "// (20) Fib\n";
    for (int i(0); i <= 30; ++i) {
        cout << Fib(i) << '\n';
    }
    cout << '\n';

cout << "// (21) Part class\n";
    Part part1("gear", 1, 0.25);
    Part part2("bolt", 2, 0.17);
    Part part3(part1);
    part1 = part2;
    part1.set_price(0.20);
    part1.set_price(-0.11);
    cout << part1 << '\n';
    cout << part2 << '\n';
    cout << part3 << '\n';
    cout << '\n';

cout << "// (22) BinaryTree from array-of-int\n";
    int ba1[8]{ 4, 1, -5, 3, 9, 2, 23, -8 };
    BinaryTree t10(ba1, 8);
    cout << '[' << t10 << ']' << '\n';
    cout << '\n';

cout << "// (23) BinaryTree::depth\n";
    BinaryTree t11;
    cout << t11.depth() << '\n';
    cout << t2.depth() << '\n';
    cout << '\n';

cout << "// (24) BinaryTree::is_balanced\n";
    if (t2.is_balanced())
        cout << "t2 is balanced\n";
    if (!t2.is_balanced())
        cout << "t2 is not balanced\n";
    if (t11.is_balanced())
        cout << "t11 is balanced\n";
    if (!t11.is_balanced())
        cout << "t11 is not balanced\n";
    cout << '\n';

cout << "// (25) BinaryTree::operator+=(int)\n";
    cout << '[' << t2 << ']' << '\n';
    t2 += 7;
    cout << '[' << t2 << ']' << '\n';
    cout << '\n';

cout << "// (26) BinaryTree::operator+=(const BinaryTree&)\n";
    t2 += t4;
    cout << '[' << t2 << ']' << '\n';
    cout << '\n';

cout << "// (27) BinaryTree::delete_greater_than(int)\n";
    t2.delete_greater_than(20);
    cout << '[' << t2 << ']' << '\n';
    cout << '\n';

cout << "// (28) BinaryTree::insert_random_vals(int)\n";
    t2.insert_random_values(20);
    cout << '[' << t2 << ']' << '\n';
    cout << '\n';

cout << "// (29) DoublyLinkedList::operator==, operator!=\n";
    cout << boolalpha;
    // I was missing the ( ... ) here, so I will give
    // generous partial credit if you get this far and have trouble
    cout << (empty_list == two_node_list) << '\n';
    cout << (empty_list != two_node_list) << '\n';
    cout << (empty_list == empty_list) << '\n';
    cout << '\n';

cout << "// (30) DoublyLinkedList::operator+=(int)\n";
    empty_list += 12;
    empty_list += -8;
    cout << empty_list << '\n';
    cout << '\n';

cout << "// (31) DoublyLinkedList::operator+=(const DoublyLinkedList&)\n";
    empty_list += two_node_list;
    cout << empty_list << '\n';
    empty_list += empty_list;
    cout << empty_list << '\n';
    cout << '\n';

cout << "// (32) DoublyLinkedList::rotate(int)\n";
    empty_list.rotate(1);
    cout << empty_list << '\n';
    empty_list.rotate(-5);
    cout << empty_list << '\n';
    cout << '\n';

cout << "// (33) DoublyLinkedList and function pointers\n";
    DoublyLinkedList dlist1;
    for (int i(0); i < 30; ++i) {
        dlist1.push_back(rand() % 41 - 20);
    }
    cout << dlist1 << '\n';
    cout << '\n';

    dlist1.delete_if(is_prime);
    cout << dlist1 << '\n';
    cout << '\n';
    dlist1.delete_if(is_neg);
    cout << dlist1 << '\n';
    cout << '\n';
    dlist1.delete_if(is_ge_12);
    cout << dlist1 << '\n';
    cout << '\n';

    return 0;
}
