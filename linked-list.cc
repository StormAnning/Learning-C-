#include <iostream>

template<class T>
class ListItem{
public:
	ListItem(const T &value): next(NULL), data(value){}
	~ListItem(){}

	ListItem *getNext() const {return next;}
	const T& value() const{return data;}
	void setNext(ListItem *elem){ next = elem;}
	void setValue(const T &value) {data = value;}
private:
	ListItem *next;
	T data;
};

template<class T>
bool insertAtFront(ListItem<T> **head, const T &data){
	ListItem<T> *item = new ListItem<T>(data);
	if(!item) return false;
	item->setNext(*head);
	*head = item;
	return true;
}


template<class T>
bool deleteAtFront(ListItem<T> **head){
	ListItem<T> *temp = (*head)->getNext();
	delete(*head);
	*head = temp;
	return true;
}

template<class T>
void printList(ListItem<T> **head){
	if(head){
		ListItem<T> *elem = *head;
		while(elem){
			printf("%d\n", elem->value());
			elem = elem->getNext();
		}
	}
}

template<class T>
bool deleteItem(ListItem<T> **head, ListItem<T> *item){
	if(!head || !*head || !item) return false;
	ListItem<T> *elem = *head;

	if(*head == item){
		deleteAtFront(head);
	}

	while(elem->getNext()){
		if(elem->getNext() == item){
			elem->setNext(item->getNext());
			delete(item);
			return true;
		}
		elem = elem->getNext();
	}
	return false;
}

template<class T>
bool insertAfterItem(ListItem<T> **head, ListItem<T> *item, const T &data){
	if(!head || !*head) return false;
	ListItem<T> *newItem = new ListItem<T>(data);
	if(!newItem) return false;
	ListItem<T> *elem = *head;

	while(elem){
		if(elem == item){
			newItem->setNext(elem->getNext());
			elem->setNext(newItem);
			return true;
		}
		elem = elem->getNext();
	}
	delete(newItem);
	return false;

}

//just for test purposes
void setUpTestIntList(ListItem<int> **head, int nItems){
	for(int i=2; i <= nItems; i++){
		insertAtFront(head, i);
	}
}


int main(int argc, char const *argv[])
{
	/* code */
	ListItem<int> *head = new ListItem<int>(1);

	setUpTestIntList(&head, 10);
	//deleteAtFront(&head);
	
	//deleteItem(&head, head->getNext()->getNext()->getNext());
	insertAfterItem(&head, head->getNext(), 69);

	printList(&head);
	return 0;
}

