cmake_minimum_required(VERSION 3.20)
project(DataStructures)

set(CMAKE_C_STANDARD 99)

set(LinkedList LinkedLists/SinglyLinkedList/LinkedList.c LinkedLists/SinglyLinkedList/LinkedList.h)

set(InsertionSortLinked Sorting/InsertionSortLinked.c Sorting/headers/InsertionSortLinked.h)

add_executable(InsertionSortLinkedExec Sorting/InsertionSortLinked.c ${LinkedList})

add_executable(BucketSortExec Sorting/BucketSort.c ${LinkedList} ${InsertionSortLinked})

add_executable(RadixSortExec Sorting/RadixSort.c ${LinkedList})