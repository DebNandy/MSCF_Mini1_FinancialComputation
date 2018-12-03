
// File: hw2.4.cpp
// Author(s):
// DEBAJYOTI NANDY
// AVINASH SHRIVASTAVA
// PALLAV RAJ
// MSCF, Pittsburgh

#include <iostream>
using namespace std;

struct bt_node {
	int value;       // the current values
	bt_node *left;   // lower values to the left
	bt_node *right;  // higher values to the right
};

void put_binary_tree(const bt_node *top)
{
	if (top) {
		put_binary_tree(top->left);
		cout << top->value << " ";
		put_binary_tree(top->right);
	}
}

void binary_tree_insert(bt_node **ptop, int val)
{
	if (*ptop) {  // we are not at the bottom yet
		if (val < (*ptop)->value) // left for less than
			binary_tree_insert(&(*ptop)->left, val);
		else      // right for greater than or equal to
			binary_tree_insert(&(*ptop)->right, val);
	}
	else {
		*ptop = new bt_node{ val, 0, 0 };
	}
}

void binary_tree_delete(bt_node **ptop)
{
	if (*ptop) {
		if ((*ptop)->left)
			binary_tree_delete(&(*ptop)->left);
		if ((*ptop)->right)
			binary_tree_delete(&(*ptop)->right);
		delete *ptop;
		*ptop = 0;
	}
}

bool binary_tree_is_empty(const bt_node *top)
{
	return top == 0;    // or top == nullptr;
}

int binary_tree_min(const bt_node *top)
{
	if (binary_tree_is_empty(top))
		return 0;      // a reasonable default?
	for (; top->left; top = top->left)
		;
	return top->value;
}

void put_binary_tree_rev(const bt_node * top)
{
	if (top) {
		put_binary_tree_rev(top->right);
		cout << top->value << " ";
		put_binary_tree_rev(top->left);
	}
}

bool binary_tree_contains(const bt_node *top, int val)
{
	if (!top)
		return 0;
	else if (top->value == val)
		return 1;
	else if (top->value < val)
		return binary_tree_contains(top->right, val);
	else return binary_tree_contains(top->left, val);
}

void put_binary_tree_pretty_helper(const bt_node * top, int level)
{
	if (top)
	{
		put_binary_tree_pretty_helper(top->right, level + 1);
		int temp = level;
		while (temp--)
			cout << '\t';
		cout << top->value << '\n';
		put_binary_tree_pretty_helper(top->left, level + 1);
	}
}

void put_binary_tree_pretty(const bt_node * top)
{
	put_binary_tree_pretty_helper(top, 0);
}

void binary_tree_insert_unique(bt_node ** ptop, int val)
{
	if (*ptop) {  // we are not at the bottom yet
		if (val == (*ptop)->value)		// we already have this value
			return;
		else if (val < (*ptop)->value) // left for less than
			binary_tree_insert_unique(&(*ptop)->left, val);
		else      // right for greater than or equal to
			binary_tree_insert_unique(&(*ptop)->right, val);
	}
	else {
		*ptop = new bt_node{ val, 0, 0 };
	}
}

int binary_tree_size(const bt_node * top)
{
	if (top)
	{
		return(binary_tree_size(top->left) + binary_tree_size(top->right) + 1);
	}
	else return 0;
}

int binary_tree_sum(const bt_node * top)
{
	if (top)
	{
		return(binary_tree_sum(top->left) + binary_tree_sum(top->right) + top->value);
	}
	else return 0;
}

double binary_tree_mean(const bt_node * top)
{
	if (top)
	{
		double sum = binary_tree_sum(top);
		int size = binary_tree_size(top);
		return(sum / size);
	}
	else return DBL_MIN;
}

void binary_tree_delete_value(bt_node **ptop, int val)
{
	if (*ptop == nullptr)					// couldn't find the value or empty tree
		return;
	if ((*ptop)->value == val)
	{
		bt_node * temp = *ptop;
		if (!temp->left && !temp->right)	//leaf node
		{
			bt_node * newnull{ nullptr };
			*ptop = newnull;
			delete temp;
		}
		else if (!temp->left)		// no left node
		{
			*ptop = temp->right;
			delete temp;
			binary_tree_delete_value(ptop, val);
		}
		else if (!temp->right)		// no right node
		{
			*ptop = temp->left;
			delete temp;
			binary_tree_delete_value(ptop, val);
		}
		else						// both left and right subtree present
									// put right subtree to the right of 
									// rightmost node of left subtree
		{
			bt_node* right_most_of_left = (*ptop)->left;
			while (right_most_of_left->right)
				right_most_of_left = right_most_of_left->right;
			right_most_of_left->right = (*ptop)->right;
			*ptop = temp->left;
			delete temp;
			binary_tree_delete_value(ptop, val);
		}
	}
	else if ((*ptop)->value < val)
	{
		ptop = &(*ptop)->right;
		binary_tree_delete_value(ptop, val);
	}
	else
	{
		ptop = &(*ptop)->left;
		binary_tree_delete_value(ptop, val);
	}
}

int main()
{
	bt_node *top = 0;  // tree, initially empty

	binary_tree_insert(&top, 12);  // why &top?
	binary_tree_insert(&top, 7);
	binary_tree_insert(&top, -4);
	binary_tree_insert(&top, 13);
	binary_tree_insert(&top, 9);
	binary_tree_insert(&top, 29);

	put_binary_tree(top);
	cout << "\n";

	cout << "Is binary tree empty? ";
	if (binary_tree_is_empty(top)) {
		cout << "yes!\n";
	}
	else {
		cout << "no\n";
	}

	cout << "Minimum value in binary tree is: " << binary_tree_min(top) << "\n";

	/* code for part (b)*/
	cout << "binary tree values in reverse:\n";
	put_binary_tree_rev(top);
	cout << '\n';


	/* code for part (c)*/
	cout << boolalpha;
	cout << "binary tree contains 13: "
		<< binary_tree_contains(top, 13) << '\n';
	cout << "binary tree contains -7: "
		<< binary_tree_contains(top, -7) << '\n';


	/* code for part (d)*/
	cout << "pretty binary tree:\n";
	put_binary_tree_pretty(top);


	/* code for first half of part (e)*/
	cout << "three more 7s:\n";
	binary_tree_insert(&top, 7);
	binary_tree_insert(&top, 7);
	binary_tree_insert(&top, 7);
	put_binary_tree_pretty(top);


	/* code for second half of part (e)*/
	cout << "new tree, unique values:\n";
	bt_node *top2 = nullptr;
	binary_tree_insert_unique(&top2, 7);
	binary_tree_insert_unique(&top2, 4);
	binary_tree_insert_unique(&top2, 12);
	binary_tree_insert_unique(&top2, 7);
	binary_tree_insert_unique(&top2, 7);
	binary_tree_insert_unique(&top2, 9);
	binary_tree_insert_unique(&top2, 9);
	binary_tree_insert_unique(&top2, 12);
	binary_tree_insert_unique(&top2, 12);
	binary_tree_insert_unique(&top2, 4);
	binary_tree_insert_unique(&top2, 2);
	binary_tree_insert_unique(&top2, 2);
	put_binary_tree_pretty(top2);

	//code for part (f)
	bt_node *top3 = nullptr;
	cout << "top size: " << binary_tree_size(top) << "\n";
	cout << "top2 size: " << binary_tree_size(top2) << "\n";
	cout << "top3 size: " << binary_tree_size(top3) << "\n";

	// code for part (g)
	cout << "top sum: " << binary_tree_sum(top) << "\n";
	cout << "top2 sum: " << binary_tree_sum(top2) << "\n";
	cout << "top3 sum: " << binary_tree_sum(top3) << "\n";

	// code for part (h)
	cout << "top mean: " << binary_tree_mean(top) << "\n";
	cout << "top2 mean: " << binary_tree_mean(top2) << "\n";
	cout << "top3 mean: " << binary_tree_mean(top3) << "\n";

	// code for part (i)
	binary_tree_delete_value(&top, 7);
	binary_tree_delete_value(&top2, 7);
	cout << "top with 7 deleted:\n";
	put_binary_tree_pretty(top);
	cout << "top2 with 7 deleted:\n";
	put_binary_tree_pretty(top2);

	binary_tree_delete(&top3);  // properly deallocate top3


	binary_tree_delete(&top2);


	binary_tree_delete(&top);  // no memory leaks!
}

