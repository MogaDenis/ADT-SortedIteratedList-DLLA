#pragma once
//DO NOt INCLUDE LISTITERATOR

//DO NOT CHANGE THIS PART
class ListIterator;
typedef int TComp;
typedef bool (*Relation)(TComp, TComp);
#define NULL_TCOMP -11111


class DLLANode
{
public:
	int next;
	int previous;
	TComp data;

	bool operator == (const DLLANode& node)
	{
		if (this->next != node.next)
			return false;

		if (this->previous != node.previous)
			return false;

		if (this->data != node.data)
			return false;

		return true;
	}

	bool operator != (const DLLANode& node)
	{
		return !this->operator==(node);
	}
};


class SortedIteratedList {
private:
	friend class ListIterator;
private:
	//TODO - Representation

	DLLANode* elements;
	int head;
	int tail;

	int capacity;
	int currentSize;
	Relation relationBetweenElements;

	void resize(float factor);

public:
	// constructor
	SortedIteratedList(Relation r);

	// returns the number of elements from the list
	int size() const;

	// verifies if the list is empty
	bool isEmpty() const;

	// returns the first position from the list
	ListIterator first() const;

	// returns the element from the given position
	//throws an exception if the position is not valid
	TComp getElement(ListIterator pos) const;

	// adds a new element to the list
	void add(TComp e);

	// removes the element from position pos
	//returns the removed element
	//after removal pos is positioned on the next element (the one after the removed one) or it is invalid if the last element was removed
	//throws an exception if the position is not valid
	TComp remove(ListIterator& poz);

	int removeAll(SortedIteratedList& list);

	// searches for the first occurrence of an element 
	//returns an iterator that points to the element, if it appear in the list, or an invalid iterator if the element is not in the list
	ListIterator search(TComp e) const;

	//TODO elimina
	//void print();

	//destructor
	~SortedIteratedList();

};
