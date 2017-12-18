#include<iostream>
#include "picosha2.h"
using namespace std;

class Block
{
public:
	string header;
	int data;
	Block *previous;
};
class Blockchain
{
private:
	Block *head, *tail;

	Block *getNewBlock(int _value)
	{
		Block *tmp = new Block;
		tmp->data = _value;
		tmp->previous = NULL;
		return tmp;
	}
public:
	Blockchain()
	{
		head = NULL;
		tail = NULL;
	}
	string makeHeader(Block *_block)
	{
		string res = "000000000000";
		if (_block != NULL)
		{
			res = to_string(_block->data);
			res.append(_block->header);
			res = picosha2::hash256_hex_string(res);
		}
		return res;
	}
	void add(int _value)
	{
		Block *tmp = getNewBlock(_value);

		if(head == NULL)
		{
			head = tmp;
			tail = tmp;
			tmp = NULL;
		}
		else
		{
			tmp->previous = head;
			head = tmp;
		}

		head->header = makeHeader(head->previous);

	}
	void display()
	{
		Block *tmp = new Block;
		tmp = head;
		while(tmp != NULL)
		{
			cout<<tmp->data<<"\t"<<tmp->header<<endl;
			tmp = tmp->previous;
		}
		cout<<endl;
	}
	void deleteFirst()
	{
		Block *tmp = new Block;
		tmp = head;
		head = head->previous;
		delete tmp;
	}
	void deleteLast()
	{
		Block *current = new Block;
		Block *previous = new Block;
		current = head;
		while(current->previous != NULL)
		{
			previous = current;
			current = current->previous;	
		}
		tail = previous;
		previous->previous = NULL;
		delete current;
	}
	bool verify()
	{
		bool res = true;
		cout << "Verifying ....\n\n";
		Block *tmp = new Block;
		tmp = head;
		while(tmp != NULL)
		{
			cout<<tmp->data<<"\t"<<tmp->header<<"\t";
			if( makeHeader(tmp->previous).compare(tmp->header) != 0 )
			{
				cout<<"BROKEN";
				res = false;
			}
			cout<<endl;
			tmp = tmp->previous;
		}
		cout<<endl;
		return res;
	}
	void insertAt(int pos, int value)
	{
		Block *pre = new Block;
		Block *cur = new Block;
		Block *tmp = new Block;
		cur=head;
		for(int i = 1; i<pos; i++)
		{
			pre = cur;
			cur = cur->previous;
		}
		tmp->data = value;
		pre->previous = tmp;	
		tmp->previous = cur;
	}
	void deleteAt(int pos)
	{
		Block *current = new Block;
		Block *previous = new Block;
		current=head;
		for(int i = 1; i<pos; i++)
		{
			previous = current;
			current = current->previous;
		}
		previous->previous = current->previous;
	}
	void updateFrom(int pos)
	{
	}
};

int main(int argc, const char * argv[]) 
{
	Blockchain bl;

	for (int i=0; i<=10; i++)
	{
		bl.add(i);
	}

	bl.display();
	bl.deleteLast();
	bl.deleteAt(4);
	if ( bl.verify() )
	{
		cout << "Vefified succesfully\n";
	}
	else
	{
		cout << "Broken blockchain\n";
	}
	cout<<endl;
	return 0;
}
