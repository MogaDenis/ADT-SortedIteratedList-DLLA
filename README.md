# ADT-SortedIteratedList-DLLA

  Sorted Iterated List abstract data type implemented on a doubly linked list over an array containing generic elements sorted based on a relation.
  
The elements are stored in a contiguous block in memory and each node, unlike in an usual linked list where pointers are used for parsing, has the
index of the previous and next elements in the linked list. This approach reduces fragmentation of memory and should, in theory, make traversing the whole 
list a bit faster thanks to caching.

The container has the following methods implemented:
  - Add
  - Remove
  - Search
  - GetElement
  - Size
  - IsEmpty

The ADT also has an iterator which gives the elements in the sorted order. The methods implemented are:
  - First
  - Next
  - GetCurrent
  - IsValid
