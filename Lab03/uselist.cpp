// demoes list template usage
// 2/02/20
// Andrew Hughes

#include <iostream>
#include "list.hpp" // list template

using std::cout; using std::endl;

int main(){
  Node<int> *head, *currentPtr;

  // 
  // integer list manipulation
  // 

  // first Node
  head =new Node<int>;
  head->setData(1);


  currentPtr=new Node<int>;  // second Node
  currentPtr->setData(2);

  head->setNext(currentPtr); // list contains two Nodes

  cout << head->getData() << " "; // printing head Node

  // deallocating head Node
  currentPtr=head;
  head=head->getNext();
  delete currentPtr;

  // printing and deallocating the last element
  cout << head->getData() << endl;
  delete head;


  // 
  // character list manipulation
  // 
   
  // allocating head Node
  Node<char> *charHead = new Node<char>;
  Node<char> *current = charHead;
  current->setData('a');

  // creating list
  for(char letter = 'b'; letter <= 'z'; ++letter){
    Node<char> *const newNode = new Node<char>;
    newNode->setData(letter);
    current->setNext(newNode);
    current = newNode;
  }


  for(current = charHead; 
      current != nullptr; 
      current=current->getNext())
    cout << current->getData() << ' ';
  cout << endl;
}
