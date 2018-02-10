#include <iostream>
#include <assert.h>
#include <stdarg.h>
#include <ctype.h>
#include <string>
#include <vector>
#include "strlib.h" 

const int MAX = 255;

using namespace std;

String::String() { _sz = 0; }
String::String(char *instr) {
	if (instr){
		_sz = strlen(instr);
		assert(_sz < MAX);
		strcpy_s(_storage, instr);
	}
	else
		_sz = 0;
}
String::~String() { _sz = 0; }

//overload the [] for bounds checking
char &String::operator [](int index){
	assert(index < _sz);
	assert(index >= 0);
	return _storage[index];
}

void String::oldcopy(char *instr){
	int len = 0, i = 0;
	char *sptr = _storage;
	if (instr){
		len = strlen(instr);
		assert(len < MAX);
		_sz = len;
		while ((*sptr++ = *instr++) != '\0');
	}
}

String &String::operator = (String &inobj){
	int i = 0;
	char *sptr = _storage;
	char *instr = inobj._storage;

	_sz = inobj._sz;
	while ((*sptr++ = *instr++) != '\0');
	return *this;
}
String &String::operator = (char *instr){
	int len = 0, i = 0;
	char *sptr = _storage;
	if (instr){
		len = strlen(instr);
		assert(len < MAX);
		_sz = len;
		while ((*sptr++ = *instr++) != '\0');
	}
	return *this;
}

void String::pad(char pad_char, int pad_len){
	int i = 0;
	assert(pad_len < MAX);
	for (i = _sz; i < pad_len; i++)
		_storage[i] = pad_char;
	_storage[pad_len] = '\0\;'
}
int String::slen() {
	int i;
	for (i = 0; *(_storage + 1); ++i);
	return(i);
}
int String::search(char *word){
	int idx, i, j;
	char *searchstr = _storage;
	for (i = 0; searchstr[i]; i++){
		if (searchstr[i] == word[j]){
			if (!j) idx = i;
			j++;
		}
		else
			j = 0;
		if (word[j] == '\0')
			break;
	}

	if (word[j] != '\0')
		return(-1);
	else
		return(idx);
}
String String::reverse(){
	int i = 0, len = 0;
	String temp;
	char *reverse = temp._storage;
	char *instr = _storage;
	len = _sz;
	reverse[len] = '\0';
	while (instr[i] != '\0')
		reverse[-len] = instr[i++];
	return temp;
}

void main() {
	String newstr("Mary");
	char oldstr[] = "John";

	cout << "newstr holds <" << newstr << " > " << endl;
	cout << "oldstr holds <" << oldstr << ">" << endl;

	//test overrun
	newstr.oldcopy("This is too long");
	cout << "newstr holds <" << newstr << ">" << endl;

	//test assignment
	newstr = oldstr;
	cout << "newstr holds <" << newstr << ">" << endl;

	vector<int> a;
	a.push_back(4);
	cout << a.size() << endl;
}
