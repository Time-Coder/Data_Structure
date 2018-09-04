#include <iostream>

using namespace std;

#define BLOCK_SIZE 4
class String
{
private:
	class Block
	{
	public:
		char* data = new char[BLOCK_SIZE];
		Block *link = NULL;

	public:
		Block& operator =(const Block& block);
	};

	Block* creat_block();

	Block *first = NULL;
	Block *last = NULL;
	int length = 0;

public:
	String(){}; // finished
	String(const String& str); // finished
	String(const char* str); // finished
	~String(); // finished

	void clear(); // finished
	int size()const; // finished
	String& operator =(const String& str); // finished
	String& operator =(const char* str); // finished
	char& operator [](int i); // finished
	char operator [](int i)const; // finished
	String operator +(const String& str);
	int find(const String& pattern);
	friend ostream& operator <<(ostream& out, String str); // finished

	class iterator // finished
	{
	public:
		Block* current_block = NULL;
		char* ptr = NULL;
		int i_inner = 0;

	public:
	    iterator& operator =(const iterator& it);
	    bool operator !=(const iterator& it);
	    bool operator ==(const iterator& it);
	    iterator& operator ++();
	    iterator operator ++(int);
	    char& operator *();
	};

	iterator begin();
	iterator end();
};