	#include "StudentList.h"

	// Define a constructor to initialize the list. The list starts with no Students
    StudentList::StudentList() {
		head = nullptr;
		tail = nullptr;
		numStudents=0;
	}

	// return the number of students currently in the list
	int StudentList::listSize() {
		return numStudents;
	}

	//add a Node with a student to the front (head) of the list.
	void StudentList::addFront(Student s) {
		Node* n = new Node(s, head, nullptr);

		if(head != nullptr){
			head->prev = n;
		}
		else{
			tail=n;
		}

		head = n;
		numStudents=numStudents+1;
	}

	//add a Node with a student to the back (tail) of the list.
	void StudentList::addBack(Student s) {
		Node* n = new Node(s, nullptr,tail);

		if(tail!=nullptr){
			tail->next=n;
		}
		else{
			head = n;
		}

		tail = n;
		numStudents = numStudents+1;
	}

	//Print out the names of each student in the list.
	void StudentList::printList() {
		Node* cur = head;
		while(cur!= nullptr){
			cout<<cur->data.name<<endl;
			cur = cur->next;
		}
	}

	// Remove the Node with the student at the back (tail) of the list
	// should not fail if list is empty! Print an error message if this occurs
	// Don't forget that your head and tail pointers will be null pointers if the list is empty
	void StudentList::popBack() {
		if(tail==nullptr){
			cout<<"List is empty"<<endl;
		}
		else{
			Node* toDelete = tail;
			Node* newtail = tail->prev;

			if(newtail != nullptr){
				newtail->next = nullptr;
			}
			else{
				head = nullptr;
			}

			tail = newtail;
			delete toDelete;
			numStudents = numStudents -1;
		}

	}

	// Remove the Node with the student at the front (head) of the list
	// should not fail if list is empty! Print an error message if this occurs
	// Don't forget that your head and tail pointers will be null pointers if the list is empty
	void StudentList::popFront() {		
		if(head==nullptr){
			cout<<"List is empty"<<endl;

		}
		else{
			Node* toDelete = head;
			Node* newHead = head->next;

			if(newHead != nullptr){
				newHead->prev=nullptr;
			}
			else{
				tail = nullptr;
			}

			head = newHead;
			delete toDelete;
			numStudents = numStudents-1;
		}}

	//insert a student at the position "index".
	// for this list, count head as index 0
	// if index is outside of current list range, 
	// print a message and insert the student at the back of the list
	// the previous Node at your target index should be moved forward. "For exampe, Node with student at index i, becomes index i+1" 
	// Remember that you already have methods that can add students to the front or back of list if needed! Don't repeat this code.
	void StudentList::insertStudent(Student s, int index) {
		if(index<=0){
			addFront(s);

		}
		else if(index >= numStudents){
			if(index>numStudents){
				cout<<"Index out of range"<<endl;
			}
			addBack(s);
		}
		else{
			Node* cur = head;
			int i = 0;

			while(cur != nullptr && i < index){
				cur = cur->next;
				i++;
			}

			if(cur==nullptr){
				addBack(s);
			}
			else{
				Node* n = new Node(s, cur, cur->prev);

				if(cur->prev != nullptr){
					cur->prev->next = n;
				}
				else{
					head = n;
				}

				cur->prev=n;
				numStudents = numStudents+1;
			}
		}
	}

	//find the student with the given id number and return them
	// if no student matches, print a message 
	// and create and return a dummy student object
	Student StudentList::retrieveStudent(int idNum) {

		Node* cur = head;

		while(cur != nullptr){
			if(cur->data.id == idNum){
				return cur->data;
			}else{
				cur = cur->next;
			}

			
		}
		cout<<"Not student found with id:"<<idNum<<endl;
		Student dummy;
		return dummy;
	}

	// Remove a Node with a student from the list with a given id number
	// If no student matches, print a message and do nothing
	void StudentList::removeStudentById(int idNum) {
		if(head==nullptr){
			cout<<"List is empty"<<endl;
		}else{
			Node* cur = head;

			while(cur!= nullptr){
				if(cur->data.id == idNum){
					Node* left = cur->prev;
					Node* right = cur->next;

					if(left!= nullptr){
						left->next = right;
					}else{
						head = right;
					}

					if(right != nullptr){
						right->prev = left;
					}else{
						tail = left;
					}

					delete cur;
					numStudents = numStudents - 1;
					return;
				}else{
					cur = cur->next;
				}
			}
			cout<<"Not student found with id:"<<idNum<<endl;
		}


	}

	//Change the gpa of the student with given id number to newGPA
	void StudentList::updateGPA(int idNum, float newGPA) {
		Node* cur = head;

		while(cur!= nullptr){
			if(cur->data.id == idNum){
				cur->data.GPA = newGPA;
				return;
			}else{
				cur = cur->next;
			}
		}

		cout<<"Not student found with id:"<<idNum<<endl;

	}

	//Add all students from otherList to this list.
	//otherlist should be empty after this operation.
	/*
	For example, if the list has 3 students:
	s1 <-> s2 <-> s3
	and otherList has 2 students
	s4 <-> s5
	then after mergeList the currently list should have all 5 students
	s1 <-> s2 <-> s3 <-> s4 <-> s5
	and otherList should be empty and have zero students.
	*/
	void StudentList::mergeList(StudentList &otherList) {
		if(otherList.head == nullptr){

		}
		else if (head==nullptr){
			head = otherList.head;
			tail= otherList.tail;
			numStudents = otherList.numStudents;

			otherList.head = nullptr;
			otherList.tail = nullptr;
			otherList.numStudents = 0;
		}else{
			tail->next = otherList.head;
			otherList.head->prev = tail;
			tail = otherList.tail;
			numStudents = numStudents+otherList.numStudents;

			otherList.head = nullptr;
			otherList.tail = nullptr;
			otherList.numStudents = 0;
		}
	}

	//create a StudentList of students whose gpa is at least minGPA.
	//Return this list.  The original (current) list should
	//not be modified (do not remove the students from the original list).
	StudentList StudentList::honorRoll(float minGPA) {
		StudentList list;

		Node* cur = head;
		while(cur!= nullptr){
			if(cur->data.GPA>=minGPA){
				list.addBack(cur->data);
			}
			cur = cur->next;

		}

		return list;
	}

	//remove all students whose GPA is below a given threshold.
	// For example, if threshold = 3.0, all students with GPA less than 3.0
	// should be removed from the list. 
	// Be sure to correctly update both head and tail pointers when removing 
	// from the front or back, and adjust numStudents accordingly.
	// If the list is empty, print a message and do nothing.
	void StudentList::removeBelowGPA(float threshold) {

		if(head==nullptr){
			cout<<"List is empty"<<endl;
		}
		else{
			Node* cur = head;

			while(cur!=nullptr){
				Node* next = cur->next;

				if(cur->data.GPA<threshold){
					Node* left = cur->prev;
					Node* right = cur->next;

					if(left!=nullptr){
						left->next = right;
					}
					else{
						head = right;

						
					}

					if(right != nullptr){
						right->prev = left;
					}
					else{
						tail = left;
					}

					delete cur;
					numStudents = numStudents-1;
				}

				cur = next;
			}
		}

	}
