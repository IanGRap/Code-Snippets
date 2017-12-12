// Ian Rapoport
// irapopor
// 12B
// 9 May 2016
// Queue.java
// A program for pa4 that utilizes a linked list structure to create a queue of
// objects

class Queue implements QueueInterface{

  // private variables
  private Node front;
  private Node back;
  private int physicalSize;

  // Node{}
  // Private class of Node that is used in
  private class Node{
    Object item;
    Node next;
    Node(Object item){
      this.item = item;
      this.next = null;
    }
  }

  // Constructor
  public Queue(){
    front = null;
    back = null;
    physicalSize = 0;
  }

  // isEmpty()
  // pre: none
  // post: returns true if this Queue is empty, false otherwise
  public boolean isEmpty(){
    return physicalSize == 0;
  }

  // length()
  // pre: none
  // post: returns the length of this Queue
  public int length(){
    return physicalSize;
  }

  // enqueue()
  // adds newitem to back of this Queue
  // pre: none
  // post: !isEmpty()
  public void enqueue(Object newItem){
    Node N = new Node(newItem);
    if (physicalSize == 0){
      front = N;
      back = N;
      physicalSize++;
    }else{
      N.next = back;
      back = N;
      N.next.next = N;
      N.next = null;
      physicalSize++;
    }
  }

  // dequeue()
  // deletes and returns item from front of this Queu
  // pre: !isEmpty()
  // post: this Queue will have one fewer element
  public Object dequeue() throws QueueEmptyException{
    if(this.isEmpty()){
      throw new QueueEmptyException( "Queue: dequeue() called on empty Queue" );
    }

    Object i = front.item;
    front = front.next;
    physicalSize--;
    return i;
  }

  // peek()
  // pre: !isEmpty()
  // post: returns item at front of Queue
  public Object peek() throws QueueEmptyException{
    if(this.isEmpty()){
      throw new QueueEmptyException( "Queue: peek() called on empty Queue" );
    }

    return front.item;
  }

  // dequeueAll()
  // sets this Queue to the empty state
  // pre: !isEmpty()
  // post: isEmpty()
  public void dequeueAll() throws QueueEmptyException{
    if(this.isEmpty()){
      throw new QueueEmptyException( "Queue: dequeueAll() called on empty Queue" );
    }

    front = null;
    physicalSize = 0;
  }

  // toString()
  // overrides Object's toString( method )
  public String toString(){
    String s = "";
    Node N = front;
    while(N != null){
      s = s + N.item.toString() + " ";
      N = N.next;
    }
    return s;
  }

}
