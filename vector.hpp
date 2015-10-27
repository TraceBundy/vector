#pragma once
#include <new>
#include <memory>
#include <algorithm>
#include "iterator.hpp"
#include "traits.hpp"
#include "allocator.hpp"

template<typename T, typename Alloc>
class vector;

template<typename T, typename Alloc>
bool operator == (const vector<T, Alloc> &l, const vector<T, Alloc> &r);
template<typename T, typename Alloc>
bool operator != (const vector<T, Alloc> &l, const vector<T, Alloc> &r);
template<typename T, typename Alloc>
bool operator > (const vector<T, Alloc> &l, const vector<T, Alloc> &r);
template<typename T, typename Alloc>
bool operator < (const vector<T, Alloc> &l, const vector<T, Alloc> &r);
template<typename T, typename Alloc>
bool operator >= (const vector<T, Alloc> &l, const vector<T, Alloc> &r);
template<typename T, typename Alloc>
bool operator <= (const vector<T, Alloc> &l, const vector<T, Alloc> &r);


template <typename T, typename Alloc = allocator<T> >
class vector
{
    friend bool operator == <T,Alloc> (const vector<T, Alloc> &l, const vector<T, Alloc> &r);
    friend bool operator != <T,Alloc> (const vector<T, Alloc> &l, const vector<T, Alloc> &r);
    friend bool operator >  <T,Alloc> (const vector<T, Alloc> &l, const vector<T, Alloc> &r);
    friend bool operator <  <T,Alloc> (const vector<T, Alloc> &l, const vector<T, Alloc> &r);
    friend bool operator >= <T,Alloc> (const vector<T, Alloc> &l, const vector<T, Alloc> &r);
    friend bool operator <= <T,Alloc> (const vector<T, Alloc> &l, const vector<T, Alloc> &r);
    public:
        typedef Alloc  allocator_type;
        typedef ptrdiff_t difference_type;
        typedef typename allocator_type::value_type value_type;
        typedef typename allocator_type::pointer pointer;
        typedef typename allocator_type::const_pointer const_pointer;
        typedef typename allocator_type::reference reference;
        typedef typename allocator_type::const_reference const_reference;
        typedef typename allocator_type::size_type size_type;
        typedef _iterator<const_pointer>const_iterator;
        typedef _iterator<pointer> iterator;
        typedef reverse_iterator<const_iterator> const_reverse_iterator;
        typedef reverse_iterator<iterator> reverse_iterator;
        allocator_type A_;

        pointer start_;
        pointer finish_;
        pointer end_;

    public:
        vector(size_type count = 0){
            init(count);
        }
        vector(size_type count, const value_type& value,
                const allocator_type& = allocator_type()){
            init(count, value);
        }
        vector(vector<T>& other){
            initialize_dispath(other.begin(), other.end(), false_type());
        }
        template <typename InputIter >
        vector(InputIter begin, InputIter end, const allocator_type& = allocator_type())
        {
            typedef typename is_integer<InputIter>::type integer_type;
            initialize_dispath(begin, end, integer_type());
        }
        ~vector(){
            destroy(start_, finish_);
            deallocate(start_, capacity());
        }
        void push_back(const_reference &c)
        {
            if (start_ == NULL){
                start_ = allocate(1);
                finish_ = start_;
                end_ = start_+1;
            } else if (finish_ == end_) {
                size_type len = capacity();
                size_type cur_len = size();
                pointer new_start = allocate(len*2);
                std::uninitialized_copy(start_, finish_, new_start);
                destroy(start_, end_);
                deallocate(start_, len);
                start_ = new_start;
                finish_ = start_+cur_len;
                end_ = start_+len*2;
            }
            construct(finish_++, c);
        }

        void pop_back(){
            destroy(--finish_);
        }
        reference operator[] (size_type i) const {
            return *(start_+i);
        }

        iterator begin() const {
            return iterator(start_);
        }

        const_iterator cbegin() const{
            return const_iterator(start_);
        }

        iterator end() const {
            return iterator(finish_);
        }

        const_iterator cend() const {
            return const_iterator(finish_);
        }
        reverse_iterator rbegin() const {
            iterator it = iterator(finish_-1);
            return reverse_iterator(it);
        }
        const_reverse_iterator crbegin() const {
            const_iterator it = const_iterator(finish_-1);
            return const_reverse_iterator(it);
        }
        reverse_iterator rend() const {
            iterator it = iterator(start_-1);
            return reverse_iterator(it);
        }
        const_reverse_iterator crend() const {
            const_iterator it = const_iterator(start_-1);
            return const_reverse_iterator(it);
        }
        reference at(size_type n) { return start_[n]; }
        reference front() { return *begin(); }
        reference back() { return *rbegin(); }

        bool empty() const { return start_ == finish_; }
        size_type max_size() const { return size_type(-1) / sizeof(value_type); }
        size_type capacity() const { return end_ - start_; }
        size_type size() const { return finish_ - start_; }
    private:
        void init(size_type n){
            if (n > 0){
                start_ = allocate(n);
                finish_ = start_;
                end_ = start_ + n;
            } else {
                start_ = NULL;
                finish_ = NULL;
                end_ = NULL;
            }
        }
        void init(size_type n, const value_type &value){
            start_ = allocate(n);
            finish_ = start_+n;
            end_ = start_+n;
            std::uninitialized_fill(start_, finish_, value);
        }
        pointer allocate(size_type n){
            return static_cast<pointer>(A_.allocate(n*sizeof(T)));
        }
        void destroy(pointer start, pointer end){
            while (start != end){
                A_.destroy(start++);
            }
        }
        void deallocate(pointer p, size_type n){
            A_.deallocate(p, n*sizeof(T));
        }
        void construct(pointer finish, const_reference &c){
            A_.construct(finish, c);
        }
    template <typename Integer>
        void initialize_dispath(Integer count, Integer value, true_type)
        {
            init(count, value);
        }
    template <typename InputIter>
        void initialize_dispath(InputIter begin, InputIter end, false_type)
        {
            difference_type len = end - begin;
            start_ = allocate(len);
            std::uninitialized_copy(begin, end, start_);
            finish_ = start_+len;
            end_ = start_+len;
        }
};

template<typename T, typename Alloc>
bool operator == (const vector<T, Alloc> &l, const vector<T, Alloc> &r){
    return l.size() == r.size() && std::equal(l.begin(), r.end(), r.begin());
}

template<typename T, typename Alloc>
bool operator != (const vector<T, Alloc> &l, const vector<T, Alloc> &r){ return !(l == r); }

template<typename T, typename Alloc>
bool operator > (const vector<T, Alloc> &l, const vector<T, Alloc> &r){
    typedef typename vector<T, Alloc>::size_type size_type;
    size_type lsize = l.size();
    size_type rsize = r.size();
    size_type min_size = lsize < rsize ? lsize : rsize;
    for (size_type i = 0; i < min_size; ++i){
        if (l[i] <= r[i])
            return false;
    }
    if (min_size != rsize) return true;
    return false;
}

template<typename T, typename Alloc>
bool operator < (const vector<T, Alloc> &l, const vector<T, Alloc> &r){ return r > l; }

template<typename T, typename Alloc>
bool operator >= (const vector<T, Alloc> &l, const vector<T, Alloc> &r){ return !(l < r); }

template<typename T, typename Alloc>
bool operator <= (const vector<T, Alloc> &l, const vector<T, Alloc> &r){ return !(l > r); }
