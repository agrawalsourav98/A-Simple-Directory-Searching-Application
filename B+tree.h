#pragma once
// B+ Tree Implementation

using namespace std;

#include<string>

const int m = 50;

struct nodetype
{
public:
	long long loc;
	std::string filename;
	nodetype() {
		loc = 0;
		filename = "null";
	}
	nodetype(long long a, std::string b) {
		loc = a;
		filename = b;
	}
};

ostream& operator <<(ostream & stream, nodetype& item);

class node
{
public:
	nodetype a[m];
	node* next[m];
	node* parent;
	int size;
	node();
};

class linkleaf
{
public:
	node* data;
	linkleaf* next;
	linkleaf();
};

class btree
{
public:
	node* root;
	linkleaf* head;
	int flag;
	node* findLeaf(std::string key, int& level);
	void updateKey(node* p, node* c, nodetype newKey);
	int search(std::string key,__int64 results []);
	void insert(nodetype key);
	void insertIntoNode(node* n, nodetype key, node* address);
	void promote(node* n, nodetype key, node* address);
	node* split(node* n);
	void traverse(node* ptr);
	void connectLeaf(node* n, node* newptr);
	void traverseleaf(ostream *stream);
	btree();
};