
// File: hw2.1.cpp
// Author(s):
// DEBAJYOTI NANDY
// AVINASH SHRIVASTAVA
// PALLAV RAJ
// MSCF, Pittsburgh

#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

// clist structure definition

struct cl_node {
	char data;
	cl_node *next;
};

// clist creation functions

cl_node *mk_clist_from_Cstring(const char *s)
{
	cl_node *first(nullptr);
	cl_node *last(nullptr);
	for (; *s; ++s) {
		cl_node *pnew = new cl_node{ *s, nullptr };
		if (!last) {
			last = first = pnew;
		}
		else {
			last = last->next = pnew;
		}
	}
	return first;
}

// clist access functions

size_t clist_size(const cl_node *cl)
{
	size_t size(0);
	for (; cl; cl = cl->next)
		size += 1;
	return size;
}

void clist_display_to_cout(const cl_node *cl)
{
	for (; cl; cl = cl->next)
		cout << cl->data;
}

// clist element modification functions

void clist_to_uppercase(cl_node *cl)
{
	// assumes ASCII character set
	for (; cl; cl = cl->next) {
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

//code for part (b)

cl_node *mk_copy_clist(const cl_node * cl)
{
	cl_node * new_cl{ nullptr };
	cl_node * current_node{ nullptr };
	for (; cl != nullptr; cl = cl->next)
	{
		if (!current_node)
			current_node = new_cl = new cl_node{ cl->data,nullptr };
		else
			current_node = current_node->next = new cl_node{ cl->data,nullptr };
	};

	return(new_cl);
}

//code for part (c)

cl_node *mk_clist_from_string(string s)
{
	cl_node *first{ nullptr };
	cl_node *last{ nullptr };

	for (size_t i(0); i < s.size(); i++)
	{
		cl_node *pnew = new cl_node{ s[i],nullptr };
		if (!last)
			last = first = pnew;
		else last = last->next = pnew;
	}
	return(first);
}

// code for part (d)

void clist_append_char(cl_node ** pcl, char c)
{
	cl_node * pnew = new cl_node{ c, nullptr };
	if (!(*pcl))
	{
		*pcl = pnew;
		return;
	}
	cl_node * temp = *pcl;
	while (temp->next != nullptr)
		temp = temp->next;
	temp->next = pnew;
}

//code for part (e)

size_t clist_count_char(const cl_node *cl, char c)
{
	size_t count(0);
	if (!cl)
		return count;
	while (cl)
	{
		if (cl->data == c)
			count++;
		cl = cl->next;
	};
	return count;
}

// code for part (f)

void clist_delete_dups(cl_node **pcl)
{
	cl_node * iter = *pcl;
	while (iter->next != nullptr)
	{
		while (iter->data == iter->next->data)
		{
			cl_node * tmp = iter->next;
			iter->next = tmp->next;
			delete tmp;
		}
		iter = iter->next;
	}
}

void clist_delete_val(cl_node **p_cl, char val)
{
	while (*p_cl) {
		cl_node *tmp = *p_cl;
		if (tmp->data == val)
		{
			*p_cl = (tmp->next);
			delete tmp;
		}
		else *p_cl = (*p_cl)->next;
	}
}


// code for part(g)

void clist_insert_clist(cl_node ** pcl, const cl_node *new_cl, size_t position)
{
	cl_node *firstcl = *pcl;
	cl_node *copy_new_cl = mk_copy_clist(new_cl);
	cl_node *secondclend = copy_new_cl;
	while (secondclend->next != nullptr)
		secondclend = secondclend->next;
	if (position == 0)
	{
		secondclend->next = firstcl;
		*pcl = copy_new_cl;
		return;
	}
	for (size_t i(0); i < position - 1; i++)
		firstcl = firstcl->next;

	secondclend->next = firstcl->next;
	firstcl->next = copy_new_cl;
}

// code for part(h)

cl_node * mk_empty_clist()
{
	cl_node * empty_cl_node{ nullptr };
	return empty_cl_node;
}

int main()
{
	cl_node *bob = mk_clist_from_Cstring("Boby");
	clist_display_to_cout(bob);    // Bob
	cout << '\n';
	cout << "list is " << clist_size(bob) << " chars long\n";
	clist_to_uppercase(bob);
	clist_display_to_cout(bob);    // BOB
	cout << '\n';
	clist_delete_val(&bob, 'y');
	clist_display_to_cout(bob);
	cout << '\n';
	clist_delete(&bob);
	clist_display_to_cout(bob);    // (empty -- no memory leak)

								   /* code for part (b)

	cl_node *hello = mk_clist_from_Cstring("hello");
	clist_display_to_cout(hello); cout << '\n';  // hello
	cl_node *hello2 = mk_copy_clist(hello);
	clist_display_to_cout(hello2); cout << '\n'; // hello
	clist_to_uppercase(hello2);
	clist_display_to_cout(hello); cout << '\n';  // hello
	clist_display_to_cout(hello2); cout << '\n'; // HELLO
	clist_delete(&hello);
	clist_delete(&hello2);
	clist_display_to_cout(hello);  // (empty)
	clist_display_to_cout(hello2); // (empty)

								   /* code for part (c)

	string s("howdy");
	cl_node *howdy = mk_clist_from_string(s);
	clist_display_to_cout(howdy); cout << '\n';  // howdy
	clist_delete(&howdy);
	clist_display_to_cout(howdy);  // (empty)

								   /* code for part (d)

	cl_node *cl = mk_clist_from_Cstring("Bell");
	clist_display_to_cout(cl); cout << '\n';     // Bell
	clist_append_char(&cl, 'a');
	clist_display_to_cout(cl); cout << '\n';     // Bella
	clist_delete(&cl);
	clist_display_to_cout(cl);                   // (empty)
	clist_append_char(&cl, 'X');
	clist_display_to_cout(cl); cout << '\n';     // X
	clist_delete(&cl);
	clist_display_to_cout(cl);                   // (empty)

												 /* code for part (e)

	cl_node *cl2 = mk_clist_from_Cstring("Mississippi");
	clist_display_to_cout(cl2); cout << '\n';    // Mississippi
	cout << clist_count_char(cl2, 'i') << '\n';  // 4

												 /* code for part (f)
	clist_display_to_cout(cl2); cout << '\n';    // Mississippi
	clist_delete_dups(&cl2);
	clist_display_to_cout(cl2); cout << '\n';    // Misisipi
	clist_delete(&cl2);
	clist_display_to_cout(cl2); cout << '\n';    // (empty)

												 /* code for part (g)

	cl_node *cl3 = mk_clist_from_Cstring("national");
	cl_node *cl4 = mk_clist_from_Cstring("ive fic");
	clist_insert_clist(&cl3, cl4, 2);
	clist_display_to_cout(cl3); cout << '\n'; // naive fictional
	clist_display_to_cout(cl4); cout << '\n'; // ive fic
	clist_delete(&cl3);
	clist_delete(&cl4);

	/* code for part (h)*/

	cl_node *cl5 = mk_empty_clist();
	clist_display_to_cout(cl5); cout << '\n'; // (empty)
	clist_append_char(&cl5, 'h');
	clist_append_char(&cl5, 'i');
	clist_display_to_cout(cl5); cout << '\n'; // hi
	clist_delete(&cl5);

}

