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
	String(){};
	String(const String& str);
	String(const char* str);
	~String();

	void clear();
	int size()const;
	String& operator =(const String& str);
	String& operator =(const char* str);
	char& operator [](int i);
	char operator [](int i)const;
	String operator +(const String& str);
	int find(const String& pattern)const;
	int find(const char* pattern)const;
	friend ostream& operator <<(ostream& out, String str);

	class iterator
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