#include <assert.h>
#include <iostream>

// Define class List
template <class _Tc> class List {
  public:
    List() : head_(nullptr), tail_(nullptr) {}
    ~List();
    void PushFront(_Tc);
    void PushBack(_Tc);
    _Tc PopFront();
    _Tc PopBack();
    int Size() const;
    bool Empty() const { return (head_ == nullptr); }
    void Print() const;

  private:
    struct Node {
      _Tc val;
      Node* prev;
      Node* next;
      Node(_Tc val, Node* prev, Node* next) : val(val), prev(prev), next(next) {}
    };

    Node* head_;
    Node* tail_;
};

// Define List::~List
template <class _Tc> List<_Tc>::~List() {
  while (head_) {
    // use the copy constructor to create a new pointer
    Node* current(head_);
    head_ = head_->next;
    // delete the Node that is no longer on the List
    delete current;
  }
}

// Define List::PushFront()
template <class _Tc> void List<_Tc>::PushFront(_Tc val) {
  Node* front_node = new Node(val, nullptr, head_);
  // corner case:
  if (tail_ == nullptr) { // which means head_ is also nullptr
    tail_ = front_node;
    head_ = front_node;
  }
  else { // both head_ and tail_ are not nullptr
    head_->prev = front_node;
    head_ = front_node;
  }
}

// Declare List::PushBack()
template <class _Tc> void List<_Tc>::PushBack(_Tc val) {
  Node* back_node = new Node(val, tail_, nullptr);
  // corner case:
  if (head_ == nullptr) { // which means tail_ is also nullptr
    head_ = back_node;
    tail_ = back_node;
  }
  else { // both head_ and tail_ are not nullptr
    tail_->next = back_node;
    tail_ = back_node;
  }
}

// Declare List::PopFront()
template <class _Tc> _Tc List<_Tc>::PopFront() {
  if ( this->Empty() )
    throw( "Cannot List::PopFront() when List::Empty() is true" );

  Node* temp(head_); // again, copy ctor
  _Tc val = head_->val;
  head_ = head_->next;
  if (head_) head_->prev = nullptr;
  else tail_ = nullptr;

  delete temp;
  return val;
}
// Declare List::PopBack()
template <class _Tc> _Tc List<_Tc>::PopBack() {
  if ( this->Empty() )
    throw( "Cannot List::PopBack() when List::Empty() is true" );

  Node* temp(tail_); // agin, copy ctor
  _Tc val = tail_->val;
  tail_ = tail_->prev;
  if (tail_) tail_->next = nullptr;
  else head_ = nullptr;

  delete temp;
  return val;
}

// Define List::Size()
template <class _Tc> int List<_Tc>::Size() const {
  int size = 0;
  Node* current(head_); // again, copy ctor
  while (current) {
    size++;
    current = current->next;
  }
  return size;
}

// Define List::Print()
template <class _Tc> void List<_Tc>::Print() const {
  Node* current(head_);
  while ( current ) {
    std::cout << "list current val = " << current->val << std::endl;
    current = current->next;
  }
}

// Design a doubly linked list to pass these tests
int main() {
  // Sanity test
  List<int> list1;
  list1.PushBack(9); // list1.Print();
  assert(list1.Size() == 1);

  // Deeper test
  List<int> list2;
  list2.PushFront(9); // list2.Print();
  list2.PushBack(10); // list2.Print();
  assert(list2.Size() == 2);
  assert(list2.PopBack() == 10);
  assert(list2.PopFront() == 9);
  assert(list2.Size() == 0);

  // print out to check
  // list1.Print();
  // list2.Print();

  return 0;
}