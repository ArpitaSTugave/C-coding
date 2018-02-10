#include<iostream>

const int MAX = 255;

class String{
protected:
	char _storage[MAX + 1];
	int _sz;
public:
	String();
	String(char *instr);
	~String();
	char &operator [](int index);
	friend std::ostream &operator <<  (std::ostream &stream, String &inobj);
	void oldcopy(char *instr);
	String &operator = (String &inobj);
	String &operator = (char *instr);
	void pad(char pad_char, int pad_len);
	int slen();
	int search(char *word);
	String reverse();
};
