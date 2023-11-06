
// Complete the functions (marked by ...)
// so that it passes all tests in DateTimeTest.

#include "PersonSet.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definition of the structure
struct _PersonSet_ {
  int capacity;    // the current capacity of the array
  int size;        // the number of elements currently stored
  Person **array;  // points to an array of pointers to persons
};

#define INITIAL_CAPACITY 4

// You may add auxiliary definitions and declarations here, if you need to.

// Create a PersonSet.
PersonSet *PersonSetCreate() {
  // You must allocate space for the struct and for the array.
  // The array should be created with INITIAL_CAPACITY elements.
  // (The array will be reallocated if necessary, when elements are appended.)

  // COMPLETE ...
  PersonSet* ps = (PersonSet*) malloc(sizeof(PersonSet));
  if (ps == NULL) return ps;
  ps->capacity = INITIAL_CAPACITY;
  ps->size = 0;

  ps->array = (Person **) (Person *) malloc(sizeof(Person *) * ps->capacity);
  if (ps->array == NULL){
      free(ps);
      return NULL;
  }

  return ps;
}

// Destroy PersonSet *pps
void PersonSetDestroy(PersonSet **pps) {
  assert(*pps != NULL);

  // COMPLETE ...
  PersonSet* ps;
  ps = *pps;

  free(ps->array);
  free(ps);
  *pps = NULL;
}

int PersonSetSize(const PersonSet *ps) { return ps->size; }

int PersonSetIsEmpty(const PersonSet *ps) { return ps->size == 0; }

void PersonSetPrint(const PersonSet *ps) {
  printf("{\n");
  for (int i = 0; i < ps->size; i++) {
    Person *p = ps->array[i];
    PersonPrintf(p, ";\n");
  }
  printf("}(size=%d, capacity=%d)\n", ps->size, ps->capacity);
}

// Find index in ps->array of person with given id.
// (INTERNAL function.)
static int search(const PersonSet *ps, int id) {
  // COMPLETE ...
  int left, right;
  for (int i = 0; i < ps->size/2; i++) {
      left = i;
      right = ps->size - 1 - i;

      if (ps->array[left]->id == id) return left;
      if (ps->array[right]->id == id) return right;
  }
  return -1;
}

// Append person *p to *ps, without verifying presence.
// Use only when sure that *p is not contained in *ps!
// (INTERNAL function.)
static void append(PersonSet *ps, Person *p) {
  // MODIFY the function so that if the array is full,
  // it uses realloc to double the array capacity!

  // COMPLETE ...
  if (ps->size == ps->capacity){
      Person** newArray = (Person**)(Person*)realloc(ps->array, sizeof(Person*) * ps->capacity*2);
      if (newArray == NULL) {
          free(ps->array);
          free(newArray);
      }
      ps->array = newArray;
  }
  ps->array[ps->size] = p;
  ps->size++;
}

// Add person *p to *ps.
// Do nothing if *ps already contains a person with the same id.
void PersonSetAdd(PersonSet *ps, Person *p) {
  // You may call the append function here!

  // COMPLETE ...
   if (search(ps, p->id) == -1){
       append(ps, p);
   }
}

// Pop one person out of *ps.
Person *PersonSetPop(PersonSet *ps) {
  assert(!PersonSetIsEmpty(ps));
  // It is easiest to pop and return the person in the last position!

  // COMPLETE ...
    Person* p = ps->array[ps->size-1];
    ps->array[ps->size-1] = NULL;
    ps->size--;
    return p;
}

// Remove the person with given id from *ps, and return it.
// If no such person is found, return NULL and leave set untouched.
Person *PersonSetRemove(PersonSet *ps, int id) {
  // You may call search here!
    int index = search(ps, id);
  // COMPLETE ...
  if (index == -1) return NULL;

  Person* removedPerson = ps->array[index];

  for (int i = index; i < ps->size-1; i++) {
      ps->array[i] = ps->array[i+1];
  }

  ps->size--;
  return removedPerson;
}

// Get the person with given id of *ps.
// return NULL if it is not in the set.
Person *PersonSetGet(const PersonSet *ps, int id) {
  // You may call search here!

  // COMPLETE ...
  int index = search(ps, id);
  if (index == -1) return NULL;

  return ps->array[index];
}

// Return true (!= 0) if set contains person wiht given id, false otherwise.
int PersonSetContains(const PersonSet *ps, int id) {
  return search(ps, id) >= 0;
}

// Return a NEW PersonSet with the union of *ps1 and *ps2.
// Return NULL if allocation fails.
// NOTE: memory is allocated.  Client must call PersonSetDestroy!
PersonSet *PersonSetUnion(const PersonSet *ps1, const PersonSet *ps2) {
  PersonSet *ps = PersonSetCreate();

  // COMPLETE ...
    ps->capacity = ps1->capacity + ps2->capacity;
    ps->array = (Person**)(Person*) malloc(sizeof(Person*) * ps->capacity);

    for (int i = 0; i < ps1->size; i++) {
        ps->array[i] = ps1->array[i];
    }
    ps->size = ps1->size;
    int size = ps->size;
    for (int i = size; i < size+ps2->size; i++) {
        PersonSetAdd(ps, ps2->array[i-size]);
    }


  return ps;
}

// Return a NEW PersonSet with the intersection of *ps1 and *ps2.
// Return NULL if allocation fails.
// NOTE: memory is allocated.  Client must call PersonSetDestroy!
PersonSet *PersonSetIntersection(const PersonSet *ps1, const PersonSet *ps2) {
  // COMPLETE ...

  return NULL;
}

// Return a NEW PersonSet with the set difference of *ps1 and *ps2.
// Return NULL if allocation fails.
// NOTE: memory is allocated.  Client must call PersonSetDestroy!
PersonSet *PersonSetDifference(const PersonSet *ps1, const PersonSet *ps2) {
  // COMPLETE ...

  return NULL;
}

// Return true iff *ps1 is a subset of *ps2.
int PersonSetIsSubset(const PersonSet *ps1, const PersonSet *ps2) {
  // COMPLETE ...

  return 0;
}

// Return true if the two sets contain exactly the same elements.
int PersonSetEquals(const PersonSet *ps1, const PersonSet *ps2) {
  // You may call PersonSetIsSubset here!

  // COMPLETE ...

  return 0;
}
