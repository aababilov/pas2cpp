Summary

A templatized class for handling sequences of character-like entities. string and wstring are specialized versions of basic_string for char’s and wchar_t’s, respectively.

typedef basic_string <char> string;
typedef basic_string <wchar_t> wstring;

Synopsis

#include <string>
template <class charT,
          class traits = char_traits<charT>,
          class Allocator = allocator<charT> >
class basic_string;

Description

basic_string<charT, traits, Allocator> is a homogeneous collection of character-like entities that includes string functions such as compare, append, assign, insert, remove, and replace, along with various searches. basic_string also functions as an STL sequence container that provides random access iterators. This allows some of the generic algorithms to apply to strings.

Any underlying character-like type may be used as long as an appropriate char_traits class is included or the default traits class is applicable. 

Interface

template <class charT,
          class traits = char_traits<charT>,
          class Allocator = allocator<charT> >
class basic_string {
public:
// Types
typedef traits                               traits_type;
typedef typename traits::char_type           value_type;
typedef Allocator                            allocator_type;
typedef typename Allocator::size_type        size_type;
typedef typename Allocator::difference_type difference_type;
typedef typename Allocator::reference        reference;

typedef typename Allocator::const_reference const_reference;
typedef typename Allocator::pointer          pointer;
typedef typename Allocator::const_pointer    const_pointer;
typedef typename Allocator::pointer          iterator;
typedef typename Allocator::const_pointer    const_iterator;
typedef std::reverse_iterator<const_iterator>
                                     const_reverse_iterator;
typedef std::reverse_iterator<iterator>      reverse_iterator;
static const size_type npos = -1;

// Constructors/Destructors
explicit basic_string(const Allocator& = Allocator());
basic_string (const basic_string<charT, traits,
              Allocator>&);
basic_string(const basic_string&, size_type, 
             size_type = npos, 
             const Allocator& a = Allocator());
basic_string(const charT*, size_type,
             const Allocator& = Allocator());
basic_string(const charT*, const Allocator& = Allocator());
basic_string(size_type, charT,
             const Allocator& = Allocator());

template <class InputIterator>
basic_string(InputIterator, InputIterator,
             const Allocator& = Allocator());
~basic_string();
// Assignment operators
 basic_string& operator=(const basic_string&);
 basic_string& operator=(const charT*);
 basic_string& operator=(charT);
// Iterators
 iterator       begin();
 const_iterator begin() const;
 iterator       end();
 const_iterator end() const;
 reverse_iterator       rbegin();
 const_reverse_iterator rbegin() const;

 reverse_iterator       rend();
 const_reverse_iterator rend() const;
// Capacity
   size_type       size() const;
   size_type       length() const;
   size_type       max_size() const;
   void            resize(size_type, charT);
   void            resize(size_type);
   size_type       capacity() const;
   void            reserve(size_type = 0);
   bool            empty() const;
// Element access
   const_reference operator[](size_type) const;
   reference       operator[](size_type);

   const_reference at(size_type) const;
   reference       at(size_type);
// Modifiers
   basic_string& operator+=(const basic_string&);
   basic_string& operator+=(const charT*);
   basic_string& operator+=(charT);
   
   basic_string& append(const basic_string&);
   basic_string& append(const basic_string&,
                        size_type, size_type);
   basic_string& append(const charT*, size_type);
   basic_string& append(const charT*);
   basic_string& append(size_type, charT);

   template<class InputIterator>
    basic_string& append(InputIterator, InputIterator);
   
   basic_string& assign(const basic_string&);
   basic_string& assign(const basic_string&,
                        size_type, size_type);
   basic_string& assign(const charT*, size_type);
   basic_string& assign(const charT*);
   basic_string& assign(size_type, charT);
   template<class InputIterator>
    basic_string& assign(InputIterator, InputIterator);
   
   basic_string& insert(size_type, const basic_string&);

   basic_string& insert(size_type, const basic_string&,
                        size_type, size_type);
   basic_string& insert(size_type, const charT*, size_type);
   basic_string& insert(size_type, const charT*);
   basic_string& insert(size_type, size_type, charT);
   iterator insert(iterator, charT = charT());
   void insert(iterator, size_type, charT);
   template<class InputIterator>
    void insert(iterator, InputIterator, InputIterator);
   basic_string& erase(size_type = 0, size_type= npos);

   iterator erase(iterator);
   iterator erase(iterator, iterator);
   basic_string& replace(size_type, size_type,
                         const basic_string&);
   basic_string& replace(size_type, size_type,
                         const basic_string&,
                         size_type, size_type);
   basic_string& replace(size_type, size_type,
                         const charT*, size_type);
   basic_string& replace(size_type, size_type,
                         const charT*);

   basic_string& replace(size_type, size_type,
                         size_type, charT);
   basic_string& replace(iterator, iterator,
                         const basic_string&);
   basic_string& replace(iterator, iterator,
                         const charT*, size_type);
   basic_string& replace(iterator, iterator,
                         const charT*);
   basic_string& replace(iterator, iterator,
                         size_type, charT);
   template<class InputIterator>

    basic_string& replace(iterator, iterator,
                         InputIterator, InputIterator);
   size_type copy(charT*, size_type, size_type = 0) const;
   void swap(basic_string<charT, traits, Allocator>&);
// String operations
   const charT* c_str() const;
   const charT* data() const;
   const allocator_type& get_allocator() const;
   
   size_type find(const basic_string&,
                  size_type = 0) const;
   size_type find(const charT*,
                  size_type, size_type) const;

   size_type find(const charT*, size_type = 0) const;
   size_type find(charT, size_type = 0) const;
   size_type rfind(const basic_string&,
                   size_type = npos) const;
   size_type rfind(const charT*,
                   size_type, size_type) const;
   size_type rfind(const charT*,
                   size_type = npos) const;
   size_type rfind(charT, size_type = npos) const;
   size_type find_first_of(const basic_string&,
                           size_type = 0) const;

   size_type find_first_of(const charT*,
                           size_type, size_type) const;
   size_type find_first_of(const charT*,
                           size_type = 0) const;
   size_type find_first_of(charT, size_type = 0) const;
   size_type find_last_of(const basic_string&,
                          size_type = npos) const;
   size_type find_last_of(const charT*,
                          size_type, size_type) const;
   size_type find_last_of(const charT*, size_type = npos)

                        const;
   size_type find_last_of(charT, size_type = npos) const;
   size_type find_first_not_of(const basic_string&,
                               size_type = 0) const;
   size_type find_first_not_of(const charT*,
                               size_type, size_type) const;
   size_type find_first_not_of(const charT*, size_type = 0)
                           const;
   size_type find_first_not_of(charT, size_type = 0) const;
   size_type find_last_not_of(const basic_string&,

                              size_type = npos) const;
   size_type find_last_not_of(const charT*,
                              size_type, size_type) const;
   size_type find_last_not_of(const charT*, 
                              size_type = npos) const;
   size_type find_last_not_of(charT, size_type = npos)
                             const;
   basic_string substr(size_type = 0, size_type = npos)
                      const;
   int compare(const basic_string&) const;

   int compare(size_type, size_type, const basic_string&)
              const;
   int compare(size_type, size_type, const basic_string&,
               size_type, size_type) const;
   int compare(size_type, size_type, charT*) const;
   int compare(charT*) const;
   int compare(size_type, size_type, const charT*,
               size_type) const;
};
// Non-member Operators
template <class charT, class traits, class Allocator>
 basic_string operator+ (const basic_string&,

                         const basic_string&);
template <class charT, class traits, class Allocator>
 basic_string operator+ (const charT*, const basic_string&);
template <class charT, class traits, class Allocator>
 basic_string operator+ (charT, const basic_string&);
template <class charT, class traits, class Allocator>
 basic_string operator+ (const basic_string&, const charT*);
template <class charT, class traits, class Allocator>
 basic_string operator+ (const basic_string&, charT);

template <class charT, class traits, class Allocator>
 bool operator== (const basic_string&, const basic_string&);
template <class charT, class traits, class Allocator>
 bool operator== (const charT*, const basic_string&);
template <class charT, class traits , class Allocator>
 bool operator== (const basic_string&, const charT*);
template <class charT, class traits, class Allocator>
 bool operator< (const basic_string&, const basic_string&);
template <class charT, class traits, class Allocator>

 bool operator< (const charT*, const basic_string&);
template <class charT, class traits, class Allocator>
 bool operator< (const basic_string&, const charT*);
template <class charT, class traits, class Allocator>
 bool operator!= (const basic_string&, const basic_string&);
template <class charT, class traits, class Allocator>
 bool operator!= (const charT*, const basic_string&);
template <class charT, class traits, class Allocator>
 bool operator!= (const basic_string&, const charT*);

template <class charT, class traits, class Allocator>
 bool operator> (const basic_string&, const basic_string&);
template <class charT, class traits, class Allocator>
 bool operator> (const charT*, const basic_string&);
template <class charT, class traits, class Allocator>
 bool operator> (const basic_string&, const charT*);
template <class charT, class traits, class Allocator>
 bool operator<= (const basic_string&, const basic_string&);
template <class charT, class traits, class Allocator>

 bool operator<= (const charT*, const basic_string&);
template <class charT, class traits, class Allocator>
 bool operator<= (const basic_string&, const charT*);

template <class charT, class traits, class Allocator>
 bool operator>= (const basic_string&, const basic_string&);
template <class charT, class traits, class Allocator>
 bool operator>= (const charT*, const basic_string&);
template <class charT, class traits, class Allocator>
 bool operator>= (const basic_string&, const charT*);

template <class charT, class traits, class Allocator>
void swap(basic_string<charT,traits,Allocator>& a, 
          basic_string<charT,traits,Allocator>& b);
template<class charT, class traits, class Allocator>
 basic_istream<charT, traits>& operator>> 
                            (istream&, basic_string&);
template <class charT, class traits, class Allocator>
 basic_ostream<charT, traits>& operator<< 
                            (ostream&, const basic_string&);
template <class Stream, class charT, 

          class traits, class Allocator>
 basic_istream<charT, traits>& getline 
                            (Stream&, basic_string&, charT);

Constructors 

In all cases, the Allocator parameter is used for storage management.

explicit 
basic_string (const Allocator& a = Allocator());

The default constructor. Creates a basic_string with the following effects:

data()	a non-null pointer that is copyable and can have 0 added to it
size()	0
capacity()	an unspecified value

basic_string (const basic_string<T, traits, 
               Allocator>& str);

Creates a string that is a copy of str.

basic_string (const basic_string& str, size_type pos,
              size_type n= npos, const allocator&
              a=allocator());

Creates a string of pos<=size() and determines length rlen of the initial string value as the smaller of n and str.size() - pos. This has the following effects:

data()	points to the first element of an allocated copy of rlen elements of the string controlled by str beginning at position pos
size()	rlen
capacity()	a value at least as large as size()
get_allocator()	str.get_allocator()

An out_of_range exception is thrown if pos>str.size().

basic_string (const charT* s, size_type n,
              const Allocator& a = Allocator());

Creates a string that contains the first n characters of s. s must not be a NULL pointer. The effects of this constructor are:

data()	points to the first element of an allocated copy of the array whose first element is pointed to by s
size()	n
capacity()	a value at least as large as size()

A length_error exception is thrown if n == npos.

basic_string (const charT * s, 
              const Allocator& a = Allocator());

Constructs a string containing all characters in s up to, but not including, a traits::eos() character. s must not be a null pointer. The effects of this constructor are:

data()	points to the first element of an allocated copy of the array whose first element is pointed to by s
size()	traits::length(s)
capacity()	a value at least as large as size()

basic_string (size_type n, charT c, 
              const Allocator& a = Allocator());

Constructs a string containing n repetitions of c. A length_error exception is thrown if n == npos. The effects of this constructor are:

data()	points to the first element of an allocated array of n elements, each storing the initial value c
size()	n
capacity()	a value at least as large as size()

template <class InputIterator>
basic_string (InputIterator first, InputIterator last,
               const Allocator& a = Allocator());

Creates a basic_string of length last - first filled with all values obtained by dereferencing the InputIterators on the range [first, last). The effects of this constructor are:

data()	points to the first element of an allocated copy of the elements in the range [first,last)
size()	distance between first and last
capacity()	a value at least as large as size()

Destructors

~basic_string ();

Releases any allocated memory for this basic_string.

Operators

basic_string&
operator= (const basic_string& str);

Sets the contents of this string to be the same as str. The effects of operator= are:

data()	points to the first element of an allocated copy of the array whose first element is pointed to by str.size()
size()	str.size()
capacity()	a value at least as large as size()

basic_string& 
operator= (const charT * s);

Sets the contents of this string to be the same as s up to, but not including, the traits::eos() character.

basic_string& 
operator= (charT c);

Sets the contents of this string to be equal to the single charT c.

const_reference 
operator[] (size_type pos) const;
reference 
operator[] (size_type pos);

If pos < size(), returns the element at position pos in this string. If pos == size(), the const version returns charT(), the behavior of the non-const version is undefined. The reference returned by either version is invalidated by any call to c_str(), data(), or any non-const member function for the object.

basic_string& 
operator+= (const basic_string& s);
basic_string& 
operator+= (const charT* s);
basic_string& 
operator+= (charT c);

Concatenates a string onto the current contents of this string. The second member operator uses traits::length() to determine the number of elements from s to add. The third member operator adds the single character c. All return a reference to this string after completion.

Iterators

iterator begin ();
const_iterator begin () const;

Returns an iterator initialized to the first element of the string.

iterator end ();
const_iterator end () const;

Returns an iterator initialized to the position after the last element of the string.

reverse_iterator rbegin ();
const_reverse_iterator rbegin () const;

Returns an iterator equivalent to reverse_iterator(end()).

reverse_iterator rend ();
const_reverse_iterator rend () const;

Returns an iterator equivalent to reverse_iterator(begin()).

Allocator

const allocator_type get_allocator () const;

Returns a copy of the allocator used by self for storage management.

Member Functions

basic_string& 
append (const basic_string& s, size_type pos, 
        size_type npos);
basic_string&
append (const basic_string& s);
basic_string& 
append (const charT* s, size_type n);
basic_string& 
append (const charT* s);
basic_string& 
append (size_type n, charT c );
template<class InputIterator>
basic_string& 
append (InputIterator first, InputIterator last);

Append another string to the end of this string. The first two functions append the lesser of n and s.size() - pos characters of s, beginning at position pos to this string.  The second member throws an out_of_range exception if pos > str.size(). The third member appends n characters of the array pointed to by s. The fourth variation appends elements from the array pointed to by s up to, but not including, a charT() character. The fifth variation appends n repetitions of c. The final append function appends the elements specified in the range [first, last). 

All functions throw a length_error exception if the resulting lengths exceed max_size(). All return a reference to this string after completion.

basic_string&
assign (const basic_string& s);
basic_string& 
assign (const basic_string& s,
        size_type pos, size_type n);
basic_string& 
assign (const charT* s, size_type n);
basic_string&
assign (const charT* s);
basic_string&
assign (size_type n, charT c );
template<class InputIterator>
basic_string& 
assign (InputIterator first, InputIterator last);

Replace the value of this string with the value of another.  

All versions of the function assign values to this string. The first two variations assign the lesser of n and s.size() - pos characters of s, beginning at position pos. The second variation throws an out_of_range exception if pos > str.size(). The third version of the function assigns n characters of the array pointed to by s. The fourth version assigns elements from the array pointed to by s up to, but not including, a charT() character. The fifth assigns one or n repetitions of c. The last variation assigns the members specified by the range [first, last). 

All functions throw a length_error exception if the resulting lengths exceed max_size(). All return a reference to this string after completion.

const_reference 
at (size_type pos) const;
reference 
at (size_type pos);

If pos < size(), returns the element at position pos in this string. Otherwise, an out_of_range exception is thrown.

size_type 
capacity () const;

Returns the current storage capacity of the string. This is guaranteed to be at least as large as size().

int 
compare (const basic_string& str);

Returns the result of a lexicographical comparison between elements of this string and elements of str. The return value is: 

<0	if size() < str.size()
0	if size() == str.size()
>0	if size() > str.size()

int
compare (size_type pos1, size_type n1, 
         const basic_string& str) const;
int
compare (size_type pos1, size_type n1, 
         const basic_string& str,
         size_type pos2, size_type n2) const;
int 
compare (charT* s) const;
int
compare (size_type pos, size_type n1, charT* s) const;
int
compare (size_type pos, size_type n1, charT* s, 
         size_type n2) const;

Returns the result of a lexicographical comparison between elements of this string and a given comparison string. The members return, respectively:

basic_string(*this,pos1,n1).compare (str)
basic_string(*this,pos1,n1).compare (basic_string 
                                     (str, pos2, n2))
*this.compare (basic_string(s))
basic_string(*this,pos,n1).compare (basic_string
                                    (s, npos))
basic_string(*this,pos,n1).compare (basic_string (s,n2))
size_type 
copy (charT* s, size_type n, size_type pos = 0) const;

Replaces elements in memory with copies of elements from this string. An out_of_range exception is thrown if pos > size(). The lesser of n and size() - pos elements of this string, starting at position pos, are copied into the array pointed to by s. No terminating null is appended to s.

const charT* 
c_str () const;
const charT* 
data () const;

Returns a pointer to the initial element of an array whose first size() elements are copies of the elements in this string. A charT() element is appended to the end. The elements of the array may not be altered, and the returned pointer is only valid until a non-const member function of this string is called. If size() is zero, the data() function returns a non-NULL pointer.

bool empty () const;

Returns size() == 0.

basic_string& 
erase (size_type pos = 0, size_type n = npos);
iterator 
erase (iterator p);
iterator 
erase (iterator first, iterator last);

This function removes elements from the string, collapsing the remaining elements, as necessary, to remove any space left empty.

 The first version of the function removes the smaller of n and size() - pos starting at position pos. An out_of_range exception is thrown if pos > size(). 

For the second version, p must be a valid iterator on the string, and the function removes the character referred to by p. 

For the last version of erase, both first and last must be valid iterators on the string, and the function removes the characters defined by the range [first, last). The destructors for all removed characters are called.  

All versions of erase return a reference to the string after completion.

size_type 
find (const basic_string& str, size_type pos = 0) const;

Searches for the first occurrence of the substring specified by str in this string, starting at position pos. If found, it returns the index of the first character of the matching substring. If not found, returns npos. Equality is defined by traits::eq().

size_type
find (const charT* s, size_type pos, size_type n) const;
size_type 
find (const charT* s, size_type pos = 0) const;
size_type 
find (charT c, size_type pos = 0) const;

Searches for the first sequence of characters in this string that match a specified string. The variations of this function return, respectively:

find(basic_string(s,n), pos)
find(basic_string(s), pos)
find(basic_string(1, c), pos)
size_type
find_first_not_of (const basic_string& str,
                   size_type pos = 0) const;

Searches for the first element of this string at or after position pos that is not equal to any element of str. If found, find_first_not_of returns the index of the non-matching character. If all of the characters match, the function returns npos. Equality is defined by traits::eq().

size_type 
find_first_not_of (const charT* s, 
                   size_type pos, size_type n) const;
size_type 
find_first_not_of (const charT* s, 
                   size_type pos = 0) const;
size_type 
find_first_not_of (charT c, size_type pos = 0) const;

Searches for the first element in this string at or after position pos that is not equal to any element of a given set of characters. The members return, respectively:

find_first_not_of(basic_string(s,n), pos)
find_first_not_of(basic_string(s), pos)
find_first_not_of(basic_string(1, c), pos)
size_type
find_first_of(const basic_string& str,
              size_type pos = 0) const;

Searches for the first occurrence at or after position pos of any element of str in this string. If found, the index of this matching character is returned. If not found, npos is returned. Equality is defined by traits::eq().

size_type 
find_first_of(const charT* s, size_type pos,
              size_type n) const;
size_type 
find_first_of(const charT* s, size_type pos = 0) const;
size_type
find_first_of (charT c, size_type pos = 0) const;

Searches for the first occurrence in this string of any element in a specified string. The find_first_of variations return, respectively:

find_first_of(basic_string(s,n), pos)
find_first_of(basic_string(s), pos)
find_first_of(basic_string(1, c), pos)
size_type 
find_last_not_of(const basic_string& str,
                 size_type pos = npos) const;

Searches for the last element of this string at or before position pos that is not equal to any element of str. If find_last_not_of finds a non-matching element, it returns the index of the character. If all the elements match, the function returns npos. Equality is defined by traits::eq().

size_type 
find_last_not_of(const charT* s,
                 size_type pos, size_type n) const;
size_type 
find_last_not_of(const charT* s, size_type pos = npos) const;
size_type 
find_last_not_of(charT c, size_type pos = npos) const;

Searches for the last element in this string at or before position pos that is not equal to any element of a given set of characters. The members return, respectively:

find_last_not_of(basic_string(s,n), pos)
find_last_not_of(basic_string(s), pos)
find_last_not_of(basic_string(1, c), pos)
size_type 
find_last_of(const basic_string& str,
             size_type pos = npos) const; 

Searches for the last occurrence of any element of str at or before position pos in this string. If found, find_last_of returns the index of the matching character. If not found, find_last_of returns npos. Equality is defined by traits::eq().

size_type
find_last_of(const charT* s, size_type pos,
             size_type n) const;
size_type 
find_last_of(const charT* s, size_type pos = npos) const;
size_type 
find_last_of(charT c, size_type pos = npos) const;

Searches for the last occurrence in this string of any element in a specified string. The members return, respectively:

find_last_of(basic_string(s,n), pos)
find_last_of(basic_string(s), pos)
find_last_of(basic_string(1, c), pos)
basic_string&
insert(size_type pos1, const basic_string& s);
basic_string& 
insert(size_type pos, const basic_string& s,
       size_type pos2 = 0, size_type n = npos);
basic_string&
insert(size_type pos, const charT* s, size_type n);
basic_string&
insert(size_type pos, const charT* s);
basic_string& 
insert(size_type pos, size_type n, charT c);

Inserts additional elements at position pos in this string. All of the variants of this function throw an out_of_range exception if pos > size(). All variants also throw a length_error if the resulting strings exceed max_size(). Elements of this string are moved apart as necessary to accommodate the inserted elements. All return a reference to this string after completion.

The second variation of this function inserts the lesser of n and s.size() - pos2 characters of s, beginning at position pos2 in this string. This version throws an out_of_range exception if pos2 > s.size(). 

The third version inserts n characters of the array pointed to by s. 

The fourth inserts elements from the array pointed to by s up to, but not including, a charT() character. 

Finally, the fifth variation inserts n repetitions of c.

iterator 
insert(iterator p, charT);
void 
insert(iterator p, size_type n, charT c);
template<class InputIterator>
void
insert(iterator p, InputIterator first, InputIterator last);

Inserts additional elements in this string immediately before the character referred to by p. All of these versions of insert require that p is a valid iterator on this string. The first version inserts a copy of c. The second version inserts n repetitions of c. The third version inserts characters in the range [first, last). The first version returns p.

size_type 
length() const;

Returns the number of elements contained in this string.

size_type 
max_size() const;

Returns the maximum possible size of the string.

size_type 
rfind (const basic_string& str, size_type pos = npos) const;

Searches for the last occurrence of the substring specified by str in the string, where the index of the first character of the substring is less than pos. If found, the index of the first character that matches substring is returned. If not found, npos is returned. Equality is defined by traits::eq().

size_type 
rfind(const charT* s, size_type pos, size_type n) const;
size_type 
rfind(const charT* s, size_type pos = npos) const;
size_type 
rfind(charT c, size_type pos = npos) const;

Searches for the last sequence of characters in this string matching a specified string. The rfind variations return, respectively:

rfind(basic_string(s,n), pos)
rfind(basic_string(s), pos)
rfind(basic_string(1, c), pos)
basic_string&
replace(size_type pos, size_type n1, const basic_string& s);
basic_string& 
replace(size_type pos1, size_type n1, 
        const basic_string& str,
        size_type pos2, size_type n2);
basic_string& 
replace(size_type pos, size_type n1, const charT* s,
        size_type n2);
basic_string& 
replace(size_type pos, size_type n1, const charT* s);

basic_string& 
replace(size_type pos, size_type n1, size_type n2, charT c);

The replace function replaces selected elements of this string with an alternate set of elements. All of these versions insert the new elements in place of n1 elements in this string, starting at position pos. They each throw an out_of_range exception if pos1 > size() and a length_error exception if the resulting string size exceeds max_size().

The second version replaces elements of the original string with n2 characters from string s starting at position pos2. It throws the out_of_range exception if pos2 > s.size(). The third variation of the function replaces elements in the original string with n2 elements from the array pointed to by s. The fourth version replaces elements in the string with elements from the array pointed to by s, up to, but not including, a charT() character. The fifth replaces n elements with n2 repetitions of character c.

basic_string& 
replace(iterator i1, iterator i2, 
        const basic_string& str);
basic_string& 
replace(iterator i1, iterator i2, const charT* s,
        size_type n);
basic_string& 
replace(iterator i1, iterator i2, const charT* s);
basic_string& 
replace(iterator i1, iterator i2, size_type n,
        charT c);
template<class InputIterator>
basic_string& 
replace(iterator i1, iterator i2,
        InputIterator j1, InputIterator j2);

Replaces selected elements of this string with an alternative set of elements. All of these versions of replace require iterators i1 and i2 to be valid iterators on this string. The elements specified by the range [i1, i2) are replaced by the new elements.

The first version shown here replaces all members in str. 

The second version starts at position i1, and replaces the next n characters with n characters of the array pointed to by s. 

The third variation replaces string elements with elements from the array pointed to by s up to, but not including, a charT() character.

The fourth version replaces string elements with n repetitions of c.

The last variation shown here replaces string elements with the members specified in the range [j1, j2).

void 
reserve(size_type res_arg=0);

Assures that the storage capacity is at least res_arg. Throws a length_error exception if res_arg > max_size().

void
resize(size_type n, charT c);
void
resize(size_type n);

Changes the capacity of this string to n. If the new capacity is smaller than the current size of the string, then the string is truncated. If the capacity is larger, then the string is padded with c characters. The latter resize member pads the string with default characters specified by charT(). Throws a length_error exception if n > max_size().

size type
size() const;

Return the number of elements contained in this string.

basic_string 
substr(size_type pos = 0, size_type n = npos) const;

Returns a string composed of copies of the lesser of n and size() characters in this string starting at index pos. Throws an out_of_range exception if pos > size().

void 
swap(basic_string& s);

Swaps the contents of this string with the contents of s.

Non-member Operators

template<class charT, class traits, class Allocator>
basic_string 
operator+(const basic_string& lhs, const basic_string& rhs);

Returns a string of length lhs.size() + rhs.size(), where the first lhs.size() elements are copies of the elements of lhs, and the next rhs.size() elements are copies of the elements of rhs.

template<class charT, class traits, class Allocator>
basic_string
operator+(const charT* lhs, const basic_string& rhs);
template<class charT, class traits, class Allocator>
basic_string
operator+(charT lhs, const basic_string& rhs);
template<class charT, class traits, class Allocator>
basic_string 
operator+(const basic_string& lhs, const charT* rhs);
template<class charT, class traits, class Allocator>
basic_string 
operator+(const basic_string& lhs, charT rhs);

Returns a string that represents the concatenation of two string-like entities. These functions return, respectively:

basic_string(lhs) + rhs
basic_string(1, lhs) + rhs
lhs + basic_string(rhs)
lhs + basic_string(1, rhs)
template<class charT, class traits, class Allocator>
bool 
operator==(const basic_string& lhs, 
           const basic_string& rhs);

Returns a boolean value of true if lhs and rhs are equal, and false if they are not. Equality is defined by the compare() member function.

template<class charT, class traits, class Allocator>
bool   
operator==(const charT* lhs, const basic_string& rhs);
template<class charT, class traits, class Allocator>
bool 
operator==(const basic_string& lhs, const charT* rhs);

Returns a boolean value indicating whether lhs and rhs are equal. Equality is defined by the compare() member function. These functions return, respectively:

basic_string(lhs) == rhs
lhs == basic_string(rhs)
template<class charT, class traits, class Allocator>
bool 
operator!=(const basic_string& lhs,
           const basic_string& rhs);

Returns a boolean value representing the inequality of lhs and rhs. Inequality is defined by the compare() member function.

template<class charT, class traits, class Allocator>
bool 
operator!=(const charT* lhs, const basic_string& rhs);
template<class charT, class traits, class Allocator>
bool 
operator!=(const basic_string& lhs, const charT* rhs);

Returns a boolean value representing the inequality of lhs and rhs. Inequality is defined by the compare() member function. The functions return, respectively:

basic_string(lhs) != rhs
lhs != basic_string(rhs)
template<class charT, class traits, class Allocator>
bool 
operator<(const basic_string& lhs, const basic_string& rhs);

Returns a boolean value representing the lexicographical less-than relationship of lhs and rhs. Less-than is defined by the compare() member.

template<class charT, class traits, class Allocator>
bool 
operator<(const charT* lhs, const basic_string& rhs);
template<class charT, class traits, class Allocator>
bool 
operator<(const basic_string& lhs, const charT* rhs);

Returns a boolean value representing the lexicographical less-than relationship of lhs and rhs. Less-than is defined by the compare() member function. These functions return, respectively:

basic_string(lhs) < rhs
lhs < basic_string(rhs)
template<class charT, class traits, class Allocator>
bool 
operator>(const basic_string& lhs, const basic_string& rhs);

Returns a boolean value representing the lexicographical greater-than relationship of lhs and rhs. Greater-than is defined by the compare() member function.

template<class charT, class traits, class Allocator>
bool 
operator>(const charT* lhs, const basic_string& rhs);
template<class charT, class traits, class Allocator>
bool 
operator>(const basic_string& lhs, const charT* rhs);

Returns a boolean value representing the lexicographical greater-than relationship of lhs and rhs. Greater-than is defined by the compare() member. The functions return, respectively:

basic_string(lhs) > rhs
lhs > basic_string(rhs)
template<class charT, class traits, class Allocator>
bool 
operator<=(const basic_string& lhs,
             const basic_string& rhs);

Returns a boolean value representing the lexicographical less-than-or-equal relationship of lhs and rhs. Less-than-or-equal is defined by the compare() member function.

template<class charT, class traits, class Allocator>
bool   
operator<=(const charT* lhs, const basic_string& rhs);
template<class charT, class traits, class Allocator>
bool 
operator<=(const basic_string& lhs, const charT* rhs);

Returns a boolean value representing the lexicographical less-than-or-equal relationship of lhs and rhs. Less-than-or-equal is defined by the compare() member function. These functions return, respectively:

basic_string(lhs) <= rhs
lhs <= basic_string(rhs)
template<class charT, class traits, class Allocator>
bool 
operator>=(const basic_string& lhs, 
           const basic_string& rhs);

Returns a boolean value representing the lexicographical greater-than-or-equal relationship of lhs and rhs. Greater-than-or-equal is defined by the compare() member function.

template<class charT, class traits, class Allocator>
bool 
operator>=(const charT* lhs, const basic_string& rhs);
template<class charT, class traits, class Allocator>
bool 
operator>=(const basic_string& lhs, const charT* rhs);

Returns a boolean value representing the lexicographical greater-than-or-equal relationship of lhs and rhs. Greater-than-or-equal is defined by the compare() member. The functions return, respectively:

basic_string(lhs) >= rhs
lhs >= basic_string(rhs)
template <class charT, class traits, class Allocator>
void swap(basic_string<charT,traits,Allocator>& a, 
          basic_string<charT,traits,Allocator>& b); 

Swaps the contents of a and b by calling a’s swap function on b.

template<class charT, class traits, class Allocator>
basic_istream<charT, traits>&
operator>>(basic_istream<charT, traits>& is, 
           basic_string& str);

Reads str from is using traits::char_in until a traits::is_del() element is read. All elements read, except the delimiter, are placed in str. After the read, the function returns is.

template<class charT, class traits, class Allocator>
basic_ostream<charT, traits>&
operator<<(basic_ostream <charT, traits>& os, 
           const<charT, traits allocator> str);

Writes all elements of str to os in order from first to last, using traits::char_out(). After the write, the function returns os.

Non-member Functions

template <class Stream, class charT, class traits,
          class Allocator>
basic_istream<charT, traits>
getline(basic_istream<charT, traits> is, 
        <charT, traits allocator> str, charT delim);

An unformatted input function that extracts characters from is into str until npos - 1 characters are read, the end of the input sequence is reached, or the character read is delim. The characters are read using traits::char_in(). 

Example

//
// string.cpp
//
 #include<string>
 #include <iostream>
 using namespace std;
 int main()
 {
   string test;
   //Type in a string over five characters long
   while(test.empty() || test.size() <= 5)
   {
     cout << "Type a string between 5 and 100 characters long. " << endl;
     cin >> test;
   }
   //Test operator[] access
   cout << "Changing the third character from " 
        << test[2] << " to * " << endl;
   test[2] = '*';
   cout << "now its: " << test << endl << endl;

   //Try the insertion member function
   cout << "Identifying the middle: ";
   test.insert(test.size() / 2, "(the middle is here!)");
   cout << test << endl << endl;

   //Try replacement
   cout << "I didn't like the word 'middle',so "
           "instead, I'll say:" << endl;
   test.replace(test.find("middle",0), 6, "center");
   cout << test << endl; 
   return 0;
 }

Program Output

Type a string between 5 and 100 characters long.
roguewave
Changing the third character from g to *
now its: ro*uewave
Identifying the middle: ro*u(the middle is here!)ewave
I didn't like the word 'middle', so instead, I'll say:
ro*u(the center is here!)ewave

See Also

allocator, string, wstring
 