// Ian Rapoport
// irapopor
// 12B
// 9 May 2016
// QueueEmptyException.java
// QueueEmptyException error for Queue.java in pa4.

public class QueueEmptyException extends RuntimeException{
  public QueueEmptyException(String s){
    super(s);
  }
}
