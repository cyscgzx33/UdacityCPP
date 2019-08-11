// This class defines an element that is stored
// in the garbage collection information list.

template <class T>
class PtrDetails
{
  public:
    unsigned ref_count; // current reference count
    T *mem_ptr;         // pointer to allocated memory
    
    // is_array is true if mem_ptr points to an allocated array. It is false otherwise. 
    bool is_array;

    // If mem_ptr is pointing to an allocated array, then array_size contains its size
    unsigned array_size;
    // Here, mPtr points to the allocated memory.
    // If this is an array, then size specifies
    // the size of the array.
    PtrDetails(T* m_pointer, unsigned mem_size = 0)
    {   
        ref_count = 1;
        mem_ptr = m_pointer;
        if (mem_size != 0)
            is_array = true;
        else
            is_array = false;
        
        array_size = mem_size;
    }
};

// Overloading operator== allows two class objects to be compared.
// This is needed by the STL list class.
template <class T>
bool operator==(const PtrDetails<T> &ob1,
                const PtrDetails<T> &ob2)
{
    // Implementation of operator==
    return ( ob1.mem_ptr == ob2.mem_ptr );
}