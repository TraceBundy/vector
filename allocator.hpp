#pragma once
template <typename T>
class allocator
{
    public:
        typedef T value_type;
        typedef T* pointer;
        typedef T const * const_pointer;
        typedef T& reference;
        typedef T const & const_reference;
        typedef ptrdiff_t difference_type;
        typedef size_t size_type;
        allocator() {}
        ~allocator() {}
        void* allocate(size_t n) throw (std::bad_alloc){
            if (n == 0) throw std::bad_alloc();
            return operator new (n);
        }
        void deallocate(void *p, size_t n){ operator delete (p); }
        pointer address(reference r) { return &r; }
        size_type max_size() { return size_t(-1) / sizeof(T); }
        void construct (pointer p, const_reference t) { new((void*)p)T(t); }
        void destroy(pointer p) { ((T*)p)->~T(); }
};
