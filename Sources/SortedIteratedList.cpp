#include "../Headers/ListIterator.h"
#include "../Headers/SortedIteratedList.h"
#include <iostream>
using namespace std;
#include <exception>

SortedIteratedList::SortedIteratedList(Relation r) 
{
	this->currentSize = 0;
	this->relationBetweenElements = r;
	this->capacity = 1;

	this->elements = new DLLANode[this->capacity];

	this->head = -1;
	this->tail = -1;
}

// Allocate new space and copy the values.
// Time complexity: Theta(n)
void SortedIteratedList::resize(float factor)
{
	DLLANode* newElements = new DLLANode[(int)(this->capacity * factor)];

	if (newElements == nullptr)
		return;

	this->capacity = (int)(this->capacity * factor);

	int currentIndex = this->head;

	while (currentIndex != -1)
	{
		newElements[currentIndex] = this->elements[currentIndex];
		currentIndex = this->elements[currentIndex].next;
	}

	delete[] this->elements;
	this->elements = newElements;
}

// Time complexity: Theta(1)
int SortedIteratedList::size() const 
{
	return this->currentSize;
}

// Time complexity: Theta(1)
bool SortedIteratedList::isEmpty() const 
{
	return this->currentSize == 0;
}

// Time complexity: Theta(1)
ListIterator SortedIteratedList::first() const 
{
	return ListIterator(*this);
}

// Time complexity: Theta(1)
TComp SortedIteratedList::getElement(ListIterator poz) const 
{
	if (!poz.valid())
		throw std::exception();

	return poz.getCurrent();
}

// Best case: The iterator is invalid or the element that has to be removed is the first one: Theta(1)
// Worst case: The element that has to be removed is on the last position(the tail): Theta(n)
// Average case: O(n) => Total time complexity: O(n)
TComp SortedIteratedList::remove(ListIterator& poz) 
{
	// If the iterator is invalid, throw an exception.
	if (!poz.valid())
		throw std::exception();

	// If the iterator points to the first element, remove it and change the head of the list.
	if (this->elements[this->head].data == poz.getCurrent())
	{
		TComp removedValue = this->elements[this->head].data;

		this->head = this->elements[this->head].next;
		poz.next();
		this->currentSize--;

		return removedValue;
	} 

	// Search the element that has to be removed.
	int currentIndex = this->head;
	while (currentIndex != -1)
	{
		if (this->elements[currentIndex].data == poz.getCurrent())
			break;

		currentIndex = this->elements[currentIndex].next;
	}

	// Remove the element found at the given position.
	TComp removedValue = this->elements[currentIndex].data;

	int previousIndex = this->elements[currentIndex].previous;
	int nextIndex = this->elements[currentIndex].next;

	this->elements[previousIndex].next = nextIndex;

	if (nextIndex != -1)
		this->elements[nextIndex].previous = previousIndex;
	else
		// If it is the tail, change the tail.
		this->tail = currentIndex;

	this->currentSize--;

	return removedValue;
}

// Parsing the n elements => O(n)
// Search the element in the list of elements to remove and then remove it => O(n + m)
// O(n * (n + m))
int SortedIteratedList::removeAll(SortedIteratedList& list)
{
	int removedElements = 0;

	ListIterator it = ListIterator(*this);

	while (it.valid())
	{
		ListIterator position = list.search(it.getCurrent());

		if (position.valid())
		{
			this->remove(position);
			removedElements++;
		}

		it.next();
	}	

	return removedElements;
}

// Best case: The searched element is the first one in the list: Theta(1)
// Worst case: The searched element is on the last position or does not exist in the list: Theta(n)
// Average case: O(n) => Total time complexity: O(n)
ListIterator SortedIteratedList::search(TComp e) const
{
	ListIterator it = ListIterator(*this);

	while (it.valid())
	{
		if (it.getCurrent() == e)
			break;

		it.next();
	}

	return it;
}

// Best case: The list is empty or the element has to be added at the beginning: Theta(1)
// Worst case: The element has to be added at the end or we need memory reallocation: Theta(n)
// Average case: O(n) => Total time complexity: O(n)
void SortedIteratedList::add(TComp e) 
{
	// If the list is full, allocate more space.
	if (this->currentSize == this->capacity)
		this->resize(2);

	// If the list is empty, add the element as the head.
	if (this->currentSize == 0)
	{
		this->elements[this->currentSize].data = e;
		this->elements[this->currentSize].next = -1;
		this->elements[this->currentSize].previous = -1;

		this->head = this->currentSize;
		this->tail = this->currentSize;

		this->currentSize++;

		return;
	}

	// Search where to insert the new element.
	int currentIndex = this->head;
	while (currentIndex != -1)
	{
		if (this->relationBetweenElements(e, this->elements[currentIndex].data))
			break;

		currentIndex = this->elements[currentIndex].next;
	}

	// If the position is the first one, change the head to the new element.
	if (currentIndex == this->head)
	{
		this->elements[this->currentSize].data = e;
		this->elements[this->currentSize].previous = -1;
		this->elements[this->head].previous = this->currentSize;
		this->elements[this->currentSize].next = this->head;
		this->head = this->currentSize;

		this->currentSize++;

		return;
	}

	// If the element must be added at the end, the tail will point to it.
	if (currentIndex == -1)
	{
		this->elements[this->currentSize].data = e;
		this->elements[this->tail].next = this->currentSize;
 		this->elements[this->currentSize].previous = this->tail;
		this->tail = this->currentSize;
		this->elements[this->currentSize].next = -1;

		this->currentSize++;

		return;
	}

	// Otherwise, insert it before the found position.
	int previousIndex = this->elements[currentIndex].previous;
	int nextIndex = currentIndex;

	this->elements[this->currentSize].data = e;

	this->elements[this->currentSize].previous = previousIndex;
	this->elements[this->currentSize].next = nextIndex;
	this->elements[previousIndex].next = this->currentSize;
	if (nextIndex != -1)
		this->elements[nextIndex].previous = this->currentSize;

	this->currentSize++;
}

SortedIteratedList::~SortedIteratedList() 
{
	delete[] this->elements;
}
