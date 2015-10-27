#pragma once
template <typename N>
struct _iterator
{
    public:
        typedef ptrdiff_t difference_type;
        typedef size_t size_type;
        typedef N value_type;
        typedef N* pointer;
        typedef N& reference;
        typedef _iterator<N> self_type;

        _iterator():pos(NULL){}
        _iterator (self_type const& n):pos(n.pos){}
        _iterator (N *n):pos(n){}
        ~_iterator(){}
        reference operator*() { return *pos; }
        pointer operator->() { return pos; }
        self_type operator++() { pos++; return *this; }
        self_type operator--() { pos--; return *this; }
        self_type operator+(size_type n) { pos+n; return *this; }
        self_type operator-(size_type n) { pos-n; return *this; }
        friend difference_type operator-(_iterator const &l, _iterator const &r) { return difference_type(l.pos - r.pos); }
        friend bool operator == (_iterator const &l, _iterator const &r) { return l.pos == r.pos; }
        friend bool operator != (_iterator const &l, _iterator const &r) { return l.pos != r.pos; }
    private:
        pointer pos;
};

template <typename N>
struct _iterator <N*>
{
    public:
        typedef ptrdiff_t difference_type;
        typedef size_t size_type;
        typedef N value_type;
        typedef N* pointer;
        typedef N& reference;
        typedef _iterator<pointer> self_type;

        _iterator():pos(NULL){}
        _iterator (self_type const& n):pos(n.pos){}
        _iterator (pointer n):pos(n){}
        ~_iterator(){}
        reference operator*() { return *pos; }
        pointer operator->() { return pos; }
        self_type operator++() { pos++; return *this; }
        self_type operator--() { pos--; return *this; }
        self_type operator+(size_type n) { pos+n; return *this; }
        self_type operator-(size_type n) { pos-n; return *this; }
        friend difference_type operator-(_iterator const &l, _iterator const &r) { return difference_type(l.pos - r.pos); }
        friend bool operator == (_iterator const &l, _iterator const &r) { return l.pos == r.pos; }
        friend bool operator != (_iterator const &l, _iterator const &r) { return l.pos != r.pos; }
    private:
        pointer pos;
};

template <typename N>
struct _iterator <const N*>
{
    public:
        typedef ptrdiff_t difference_type;
        typedef size_t size_type;
        typedef N value_type;
        typedef const N* pointer;
        typedef const N& reference;
        typedef _iterator<pointer> self_type;

        _iterator():pos(NULL){}
        _iterator (self_type const& n):pos(n.pos){}
        _iterator (pointer n):pos(n){}
        ~_iterator(){}
        reference operator*() { return *pos; }
        pointer operator->() { return pos; }
        self_type operator++() { pos++; return *this; }
        self_type operator--() { pos--; return *this; }
        self_type operator+(size_type n) { pos+n; return *this; }
        self_type operator-(size_type n) { pos-n; return *this; }
        friend difference_type operator-(_iterator const &l, _iterator const &r) { return difference_type(l.pos - r.pos); }
        friend bool operator == (_iterator const &l, _iterator const &r) { return l.pos == r.pos; }
        friend bool operator != (_iterator const &l, _iterator const &r) { return l.pos != r.pos; }
    private:
        pointer pos;
};
template <typename iterator>
struct reverse_iterator
{
    typedef typename iterator::difference_type difference_type;
    typedef typename iterator::value_type value_type;
    typedef typename iterator::pointer pointer;
    typedef typename iterator::reference reference;
    typedef reverse_iterator<iterator> self_type;

    reverse_iterator(iterator &it):pos(it){}
    reverse_iterator(self_type const &it):pos(it.pos){}
    reverse_iterator & operator++() { --pos; return *this; }
    reverse_iterator & operator--() { ++pos; return *this; }
    reference operator*(){ return *pos; }
    pointer operator->(){ return pos; }
    friend difference_type operator-(reverse_iterator const &l, reverse_iterator const &r) { return difference_type(l.pos - r.pos); }
    friend bool operator == (reverse_iterator const &l, reverse_iterator const &r) { return l.pos == r.pos; }
    friend bool operator != (reverse_iterator const &l, reverse_iterator const &r) { return l.pos != r.pos; }
    private:
        iterator pos;
};
