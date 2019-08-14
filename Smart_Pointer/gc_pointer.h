#include <iostream>
#include <list>
#include <typeinfo>
#include <cstdlib>
#include "gc_details.h"
#include "gc_iterator.h"
/*
    Pointer implements a pointer type that uses
    garbage collection to release unused memory.
    A Pointer must only be used to point to memory
    that was dynamically allocated using new.
    When used to refer to an allocated array,
    specify the array size.
*/
template <class T, int size = 0>
class Pointer{
private:
    // ref_countainer maintains the garbage collection list.
    static std::list<PtrDetails<T> > ref_countainer;
    // addr points to the allocated memory to which
    // this Pointer pointer currently points.
    T *addr;
    /*  is_array is true if this Pointer points
        to an allocated array. It is false
        otherwise. 
    */
    bool is_array; 
    // true if pointing to array
    // If this Pointer is pointing to an allocated
    // array, then array_size contains its size.
    unsigned array_size; // size of the array
    static bool first; // true when first Pointer is created
    // Return an iterator to pointer details in ref_countainer.
    typename std::list<PtrDetails<T> >::iterator findPtrInfo(T *ptr);
public:
    // Define an iterator type for Pointer<T>.
    typedef Iter<T> GCiterator;
    // Empty constructor
    // NOTE: templates aren't able to have prototypes with default arguments
    // this is why constructor is designed like this:
    Pointer(){
        Pointer(NULL);
    }
    Pointer(T*);
    // Copy constructor.
    Pointer(const Pointer &);
    // Destructor for Pointer.
    ~Pointer();
    // Collect garbage. Returns true if at least
    // one object was freed.
    static bool collect();
    // Overload assignment of pointer to Pointer.
    T *operator=(T *t);
    // Overload assignment of Pointer to Pointer.
    Pointer &operator=(Pointer &rv);
    // Return a reference to the object pointed
    // to by this Pointer.
    T &operator*(){
        return *addr;
    }
    // Return the address being pointed to.
    T *operator->() { return addr; }
    // Return a reference to the object at the
    // index specified by i.
    T &operator[](int i){ return addr[i];}
    // Conversion function to T *.
    operator T *() { return addr; }
    // Return an Iter to the start of the allocated memory.
    Iter<T> begin(){
        int _size;
        if (is_array)
            _size = array_size;
        else
            _size = 1;
        return Iter<T>(addr, addr, addr + _size);
    }
    // Return an Iter to one past the end of an allocated array.
    Iter<T> end(){
        int _size;
        if (is_array)
            _size = array_size;
        else
            _size = 1;
        return Iter<T>(addr + _size, addr, addr + _size);
    }
    // Return the size of ref_countainer for this type of Pointer.
    static int refContainerSize() { return ref_countainer.size(); }
    // A utility function that displays ref_countainer.
    static void showlist();
    // Clear ref_countainer when program exits.
    static void shutdown();
};

// STATIC INITIALIZATION
// Creates storage for the static variables
template <class T, int size>
std::list<PtrDetails<T> > Pointer<T, size>::ref_countainer;
template <class T, int size>
bool Pointer<T, size>::first = true;

// Constructor for both initialized and uninitialized objects. -> see class interface
template<class T, int size>
Pointer<T,size>::Pointer(T *t) {
    // Register shutdown() as an exit function.
    if (first)
        atexit(shutdown);
    first = false;

    // Implemented Pointer constructor
    typename std::list<PtrDetails<T> >::iterator p;
    p = findPtrInfo(t);

    // if t is already in gclist (<=> ref_countainer), then
    // increment its reference count.
    // Otherwise, add it to the list (<=> ref_countainer).
    if ( p != ref_countainer.end() )
        p->ref_count++; // increment ref count
    else {
        // create and store this entry
        PtrDetails<T> gcObj(t, size);
        ref_countainer.push_front(gcObj); // insert before the head of the list
    }

    addr = t;
    array_size = size;
    if (size > 0) is_array = true;
    else is_array = false;
    #ifdef DISPLAY
        std::cout << "Constructing Pointer (w/ garbage collector).";
        if (is_array)
            std::cout << " Size is " << array_size << std::endl;
        else
            std::cout << std::endl;
    #endif
}

// Copy constructor.
template< class T, int size>
Pointer<T,size>::Pointer(const Pointer &ob) {
    // Implemented Pointer copy constructor
    typename std::list<PtrDetails<T> >::iterator p;
    p = findPtrInfo(ob.addr);
    p->ref_count++; // increment ref count

    addr = ob.addr;
    array_size = ob.array_size;
    if (array_size > 0) is_array = true;
    else is_array = false;

    #ifdef DISPLAY
        std::cout << "Consturcting copy.";
        if (is_array)
            std::cout << " Size is " << array_size << endl;
        else
            std::cout << std::endl;
    #endif
}

// Destructor for Pointer.
template <class T, int size>
Pointer<T, size>::~Pointer()
{
    // Implemented Pointer destructor
    typename std::list<PtrDetails<T> >::iterator p;

    p = findPtrInfo(addr);
    if (p->ref_count) p->ref_count--; // decrement ref_count

    #ifdef DISPLAY
        std::cout "Pointer (w/ garbage collection) going out of scope.\n";
    #endif

    // Collect garbage when a pointer goes out of scope.
    collect();

    // For real use, you might want to collect
    // unused memory less frequently, such as after
    // gclist (<=> ref_countainer) has reached a 
    // certain size, after a certain number of
    // Pointers have gone out of scope, or
    // when memory is low.
}

// Collect garbage. Returns true if at least
// one object was freed.
template <class T, int size>
bool Pointer<T, size>::collect(){

    // Implemented collect function
    // Note: collect() will be called in the destructor
    bool mem_freed = false;

    #ifdef DISPLAY
        std::cout << "Before garbage collection for ";
        showlist();
    #endif

    typename std::list<PtrDetails<T> >::iterator p;
    do {

        // Scan ref_container looking for unreferenced pointers.
        for (p = ref_countainer.begin(); p != ref_countainer.end(); p++) {
            // If in-use, skip.
            if (p->ref_count > 0) continue;

            mem_freed = true;

            // Remove unused entry from ref_container.
            ref_countainer.remove(*p);

            // Free memory unless the Pointer is null.
            if (p->mem_ptr) {
                if (p->is_array) {
                    #ifdef DISPLAY
                        std::cout << "Deleting array of size "
                                  << p->array_size << std::endl;
                    #endif
                    delete[] p->mem_ptr; // delete array
                }
                else {
                    #ifdef DISPLAY
                        std::cout << "Deleting: "
                                  << *(T *) p->mem_ptr << std::endl;
                    #endif
                    delete p->mem_ptr;    // delete signle element 
                }
            }

            // Restart the search.
            break;
        }

    } while ( p != ref_countainer.end() );

    #ifdef DISPLAY
        std::cout << "After garbage collection for ";
        showlist();
    #endif

    return mem_freed;
}

/* THE OVERLOADED ASSIGNMENT OPERATORS */
// Pointer overloads operator=() twice:
// once for the assignment of a new address to a Pointer pointer,
// and once for the assignment of on Pointer pointer to another.
// Both versions will be implemented below:

// Overload assignment of pointer (regular) to Pointer (w/ gc). (i.e, Ptr = ptr)
template <class T, int size>
T* Pointer<T, size>::operator=(T *t)
{
    // Implemented operator=
    typename std::list<PtrDetails<T> >::iterator p;

    // Firstly, decrement the ref count
    // for the memory currently being pointed to.
    p = findPtrInfo(addr);
    p->ref_count--;

    // Next, if the new address is already
    // existent in the system, increment its
    // count. Otherwise, create a new entry
    // for the list.
    p = findPtrInfo(t);
    if ( p != ref_countainer.end() )
        p->ref_count++;
    else {
        // Create and store this entry.
        PtrDetails<T> gcObj(t, size);
        ref_countainer.push_front(gcObj);
    }

    addr = t; // store the address

    return t;
}

// Overload assignment of Pointer (w/ gc) to Pointer (w/ gc). (i.e, Ptr = Ptr)
template <class T, int size>
Pointer<T, size>& Pointer<T, size>::operator=(Pointer &rv)
{
    // Implemented operator=
    typename std::list<PtrDetails<T> >::iterator p;

    // First, decrement the reference count
    // for the memory currently being pointed to.
    p = findPtrInfo(addr);
    p->ref_count--;

    // Next, increment the reference count of
    // the next address.
    p = findPtrInfo(rv.addr);
    p->ref_count++; // increment ref count

    addr = rv.addr;

    return rv;
}

// A utility function that displays ref_countainer.
template <class T, int size>
void Pointer<T, size>::showlist(){
    typename std::list<PtrDetails<T> >::iterator p;
    std::cout << "ref_countainer<" << typeid(T).name() << ", " << size << ">:\n";
    std::cout << "memPtr refcount value\n ";
    if (ref_countainer.begin() == ref_countainer.end())
    {
        std::cout << " Container is empty!\n\n ";
    }
    for (p = ref_countainer.begin(); p != ref_countainer.end(); p++)
    {
        std::cout << "[" << (void *)p->memPtr << "]"
             << " " << p->refcount << " ";
        if (p->memPtr)
            std::cout << " " << *p->memPtr;
        else
            std::cout << "---";
        std::cout << std::endl;
    }
    std::cout << std::endl;
}
// Find a pointer in ref_countainer.
template <class T, int size>
typename std::list<PtrDetails<T> >::iterator
Pointer<T, size>::findPtrInfo(T *ptr){
    typename std::list<PtrDetails<T> >::iterator p;
    // Find ptr in ref_countainer.
    for (p = ref_countainer.begin(); p != ref_countainer.end(); p++)
        if (p->mem_ptr == ptr)
            return p;
    return p;
}

// Clear ref_countainer when program exits.
template <class T, int size>
void Pointer<T, size>::shutdown(){
    if (refContainerSize() == 0)
        return; // list is empty
    typename std::list<PtrDetails<T> >::iterator p;
    for (p = ref_countainer.begin(); p != ref_countainer.end(); p++)
    {
        // Set all reference counts to zero
        p->ref_count = 0;
    }
    collect();
}