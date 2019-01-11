#include "LinkedList.hpp"
#include <string>
#include <iostream>

/*
template<class T>
void LinkedList<T>::printList(){
Node<int>* temp = head;
std::cout<<"start of list:"<<std::endl;
    while (temp !=nullptr){
        std::cout<<std::to_string(temp->getItem())<<std::endl;
        temp=temp->getNext();
    }
}
*/
template<class T>
LinkedList<T>::LinkedList():head(nullptr),count(0) {}

template<class T>
LinkedList<T>::LinkedList(const LinkedList<T>& rhs)
{
    count = rhs.count;
    Node<T>* origChainPtr = rhs.head;
// std::cout<<"Executing copy constructor \n";
    if (origChainPtr == nullptr)
    {
        head = nullptr;
    }

    else
    {
        // Copy first node
//std::cout<<"rhs wasn't empty \n";

        head = new Node<T>();
        head->setItem(origChainPtr ->getItem());
// Copy remaining nodes
        Node<T>* newChainPtr = head; // Last-node pointer

        while (origChainPtr != nullptr)
        {
            //std::cout<<"advancing pointer \n";
            if (origChainPtr ->getNext()==nullptr)
            {
                break;
            }
            origChainPtr = origChainPtr ->getNext(); // Advance pointer
//std::cout<<"Pointer was "<<origChainPtr->getItem()<<std::endl;

// Get next item from original chain
            T nextItem = origChainPtr->getItem();
//std::cout<<"the item was "<<nextItem<<std::endl;

// Create a new node containing the next item
            Node<T>* newNodePtr = new Node<T>(nextItem);
//std::cout<<"new node "<<newNodePtr->getItem()<<std::endl;

            // Link new node to end of new chain
            newChainPtr->setNext(newNodePtr);
//std::cout<<"new chain "<<newChainPtr->getItem()<<std::endl;

// Advance pointer to new last node
            newChainPtr = newChainPtr->getNext();

//std::cout<<"advanced pointer to last node \n";
        } // end while
//std::cout<<"Finished while \n";
        newChainPtr->setNext(nullptr); // Flag end of new chain
//std::cout<<"set next to null pointer \n";
    }
}

template<typename T>
LinkedList<T>& LinkedList<T>::operator =(LinkedList <T> rhs)
{
    swap(*this,rhs);
    return *this;
}

template<class T>
Node<T>* LinkedList<T>::getNodeAt(int position) const
{
    if (position<=0 ||position>count)
    {
       return nullptr;
    }
    Node<T>* temp = head;
    for (int i=1; i<position; i++)
    {
        temp = temp->next;
    }
    return temp;
}

template <typename T>
bool LinkedList<T>::isEmpty() const
{
    return count==0;
}

template <typename T>
int LinkedList<T>::getLength() const
{
    return count;
}

template <typename T>
bool LinkedList<T>::insert(int newPosition, const T& newEntry)
{
    if (newPosition<=0 ||newPosition>count+1)
    {
      return false;
        }
   // std::cout<<"Executing linkedList insert. Count was "<<count<<std::endl;
   // std::cout<<"Inserting " << newEntry<<" into the list"<<std::endl;
    Node<T>* temp = new Node<T>(newEntry);
    if (newPosition==1)
    {
      // std::cout<<"Inserting at begin of list"<<std::endl;
        temp->setNext(head); // New node points to chain
        head = temp; // New node is now first node
        count++;
        return true;
    }
    Node<T>* curr = head;

    for (int i=1; i< newPosition-1; i++)
    {
        curr = curr->getNext();
    }

    if (newPosition == count+1)
    {
//for final element, merely set head's next to be this
      //  std::cout<<"Inserting at end of list with current "<<curr->getItem()<<std::endl;
        curr->setNext(temp);
        count++;
        return true;
    }
//for all non-final elements, set the node's next to head's next
   // std::cout<<"Inserting in middle of list"<<std::endl;
    Node<T>* nextNode = curr->getNext();
    curr->setNext(temp);
    temp->setNext(nextNode);
    count++;
    return true;
}

template <typename T>
bool LinkedList<T>::remove(int position)
{
    if (position<=0 ||position>count )
    {
      return false;
         }

    // account for 1 size
    if ((position == 1))
    {
        Node<T>* temp = head;
        head = head->getNext();
        delete temp;
        count--;
        return true;
    }
    Node<T>* current = head;
    //go to element before the one you want to remove
    for (int i=1; i< position-1; i++)
    {
        //std::cout<<"current is "<<current->getItem()<<std::endl;
        current = current->getNext();
    }

    if (position == count)
    {
//for final element, merely remove the final element
    //    std::cout<<"removing final element"<<std::endl;
        Node<T>* temp = current->getNext();
        current->setNext(nullptr);
        delete temp;
        count--;
        return true;
    }
//for all non-final elements, set the node's next to its next next.
   // std::cout<<"Non-final element removal"<<std::endl;
    Node<T>* newTemp = current->getNext();
  //  std::cout<<"newTemp was "<<newTemp->getItem()<<std::endl;

    Node<T>* newNext = current->getNext()->getNext();
   // std::cout<<"newNext was "<<newNext->getItem()<<std::endl;
    current->setNext(newNext);
    delete newTemp;
    count--;
    return true;
}

template <typename T>
T LinkedList<T>::getEntry(int position) const
{
    if (position<=0 ||position>count)
    {
       std::string err = "Error: Index out of bounds in GetEntry. Position was " + std::to_string(position) + " count was " + std::to_string(count);
        throw (std::logic_error(err));
    }
    Node<T>* temp = head;
    for (int i=1; i<position; i++)
    {
       // std::cout<<"tried to access next element in getEntry"<<std::endl;
        temp = temp->getNext();
    }
    return temp->getItem();
}


template <typename T>
void LinkedList<T>::clear()
{
    while (!isEmpty())
    {
        remove(1);
    }
}

template <typename T>
T LinkedList<T>::replace(int position, const T& newEntry)
{
    if (position<=0 ||position>count)
    {
       // std::cout<<"Position was "<< position<<std::endl;
        throw (std::logic_error("Error: Index out of bounds in replace"));
    }

    Node<T>* temp = head;
    for (int i=1; i< position; i++)
    {
        temp = temp->getNext();
    }
    T data = temp->getItem();
    temp->setItem(newEntry);
    return data;
}

template <typename T>
void LinkedList<T>::swap( LinkedList& lhs, LinkedList& rhs )
{

    std::swap(lhs.head,rhs.head);
    std::swap(lhs.count,rhs.count);
}

template <typename T>
LinkedList<T>::~LinkedList()
{
    clear();
}
