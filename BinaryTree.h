
//
// File: BinaryTree.h
// Author(s):
// DEBAJYOTI NANDY
// AVINASH SHRIVASTAVA
// PALLAV RAJ

/* --------- the definition of the BinaryTree class -------- */

/* THIS IS ALL THAT APPLICATION WRITERS GET TO SEE ABOUT BinaryTree */

struct bt_node;      // we promise this exists somewhere!

class BinaryTree {
public:
    BinaryTree();
    BinaryTree(const BinaryTree&);
    BinaryTree& operator=(const BinaryTree&);
    ~BinaryTree();
    void insert(int);
    void put();
    void put_pretty();
    int min();
	int max();											// part b
    int sum();
    int size();
    double mean();
	void put_to_ostream(ostream&);						// part c
	bool is_identical(const BinaryTree&);				// part d
	bool operator==(const BinaryTree&);					// part e
	bool operator!=(const BinaryTree& other);			// part f
	friend ostream& operator<<(ostream&, BinaryTree&);	// part g
private:
    bt_node *top;
};

