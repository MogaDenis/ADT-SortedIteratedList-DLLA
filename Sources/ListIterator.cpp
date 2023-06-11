#include "../Headers/ListIterator.h"
#include "../Headers/SortedIteratedList.h"
#include <exception>

using namespace std;

ListIterator::ListIterator(const SortedIteratedList& list) : list(list)
{
	this->currentIndex = list.head;
}

// Time complexity: Theta(1)
void ListIterator::first()
{
	this->currentIndex = list.head;
}

// Time complexity: Theta(1)
void ListIterator::next()
{
	if (!this->valid())
		throw std::exception();

	this->currentIndex = list.elements[this->currentIndex].next;
}

// Time complexity: Theta(1)
bool ListIterator::valid() const
{
	return this->currentIndex != -1;
}

// Time complexity: Theta(1)
TComp ListIterator::getCurrent() const
{
	if (!this->valid())
		throw std::exception();

	return list.elements[this->currentIndex].data;
}


