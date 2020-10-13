#include <stdexcept>
#include <string>
#include<iostream>
#include "LinkedList.h"

using namespace std;

void LinkedList::reset_list()
{
	head = nullptr;
	tail = nullptr;
	size = 0;
}

LinkedList::LinkedList()
{
	//reset_list();
	head = nullptr;
	tail = nullptr;
	size = 0;
}

void LinkedList::add_first(int newElem)
{
	head = new Node(newElem);
	tail = head;
}

void LinkedList::push_back(int newElem) // add in the end
{
	if (size == 0) {
		add_first(newElem);
	}
	else {
		Node* tmp = new Node(newElem);
		tmp->prev = tail;
		tail->next = tmp;
		tail = tmp;
	}
	size++;
}

void LinkedList::push_front(int newElem) // add in the beginning
{
	if (size == 0) {
		add_first(newElem);
	}
	else {
		Node* tmp = new Node(newElem, head);
		head->prev = tmp;
		head = tmp;
	}
	size++;
}

void LinkedList::pop_back() // delete last
{
	if (size == 0) return;

	if (size == 1) {
		delete head;
		reset_list();
	}
	else {
		Node* current = head;
		while (current->next != tail) {
			current = current->next;
		}
		current->next = nullptr;
		delete tail;
		tail = current;
	}
	size--;
}

void LinkedList::pop_front() // delete first
{
	if (size == 0) return;  //error (?)
	else {
		head = head->next;
		delete head->prev;
		size--;
	}
}

void LinkedList::insert(int newElem, int index) // add #index
{
	Node* add = new Node(newElem);
	Node* tmp = head;
	if (index > size - 1) {
		throw out_of_range("Index is greater than list size");
	}
	else if (index < 0) {
		throw out_of_range("Index is less than zero");
	}
	else if (index == 0) { // newElem - new head
		push_front(newElem);
	}
	else if (index == size - 1) { // newElem - new tail
		push_back(newElem);
	}
	else {
		for (int i = 1; i < index - 1; i++) {
			tmp = tmp->next;
		} // tmp - before adding
		add->prev = tmp;
		add->next = tmp->next;
		tmp->next = add;
	}
}

int LinkedList::at(size_t index) const // find data from #index
{
	if (index >= size) {
		throw out_of_range("Index is greater than list size");
	}
	else if (index < 0) {
		throw out_of_range("Index is less than zero");
	}
	else {
		size_t counter = 0;
		Node* current = head;
		while (counter != index) {
			current = current->next;
			counter++;
		}
		return current->data;
	}
}

void LinkedList::remove(int index)
{
	Node* tmp = head;
	if (index > size - 1) {
		throw out_of_range("Index is greater than list size");
	}
	else if (index < 0) {
		throw out_of_range("Index is less than zero");
	}
	else if (index == 0) { // delete head
		pop_front();
	}
	else if (index == size - 1) { // delete tail
		pop_back();
	}
	else {
		for (int i = 0; i < index; i++) {
			tmp = tmp->next;
		} // tmp should be deleted
		tmp->prev->next = tmp->next;
		tmp->next->prev = tmp->prev;
		delete tmp;
	}
}

size_t LinkedList::get_size() const
{
	return size;
}

void LinkedList::print_to_console()
{
	if (size != 0) {
		Node* tmp = head;
		do {
			cout << tmp->data << endl;
			tmp = tmp->next;
		} while (tmp->next);
		cout << tmp->data << endl;
		cout << "....." << endl;
	}
	else cout << "nothing to print" << endl;
}

void LinkedList::clear()
{
	if (head) {
		while (head->next) {
			head = head->next;
			delete head->prev;
		}
		reset_list();
	}
}

void LinkedList::set(int index, int newElem)
{
	Node* tmp = head;
	if (index > size - 1) {
		throw out_of_range("Index is greater than list size");
	}
	else if (index < 0) {
		throw out_of_range("Index is less than zero");
	}
	else {
		for (int i = 0; i < index; i++) {
			tmp = tmp->next;
		}
		tmp->data = newElem;
	}
}

bool LinkedList::isEmpty()
{
	if (head == nullptr) return true;
	else return false;
}

void LinkedList::insert(LinkedList newList, int index)
{
	if (index > size - 1) {
		throw out_of_range("Index is greater than list size");
	}
	else if (index < 0) {
		throw out_of_range("Index is less than zero");
	}
	else if (index == 0) {
		newList.tail->next = head;
		head->prev = newList.tail;
		head = newList.head;
		size = size + newList.get_size();
	}
	else {
		Node* tmp = head;
		int counter = index;
		while (counter - 1)
		{
			tmp = tmp->next;
			counter--;
		} // add after tmp
		newList.tail->next = tmp->next;
		tmp->next->prev = newList.tail;
		tmp->next = newList.head;
		newList.head->prev = head;
		size = size + newList.get_size();
	}
}