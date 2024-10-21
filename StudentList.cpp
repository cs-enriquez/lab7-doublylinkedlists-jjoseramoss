	#include "StudentList.h"

	// Define a constructor to initialize the list. The list starts with no Students
    StudentList::StudentList() {
		head = nullptr;
		tail = nullptr;
		numStudents = 0;
	}

	// return the number of students currently in the list
	int StudentList::listSize() {
		return numStudents;
	}

	//add a Node with a student to the front (head) of the list.
	void StudentList::addFront(Student s) {
		Node *newNode = new Node(s);
		if(numStudents == 0){
			head = newNode;
			tail = newNode;
			numStudents ++;
			return;
		}
		newNode->next = head;
		head->prev = newNode;
		head = newNode;
		numStudents++;
		

	}

	//add a Node with a student to the back (tail) of the list.
	void StudentList::addBack(Student s) {
		Node *newNode = new Node(s);
		if(numStudents == 0){
			head = newNode;
			tail = newNode;
			numStudents += 1;
			return;
		} 
		newNode->prev = tail;
		tail->next = newNode;
		tail = newNode;
		numStudents ++;

	}

	//Print out the names of each student in the list.
	void StudentList::printList() {
		Node *temp = head;
		cout << "Names: "<< endl;
		while(temp != NULL){
			cout << temp->data.name << endl;
			temp = temp->next;
		}

	}

	// Remove the Node with the student at the back (tail) of the list
	// should not fail if list is empty! Print an error message if this occurs
	// Don't forget that your head and tail pointers will be null pointers if the list is empty
	void StudentList::popBack() {
		if(numStudents == 0){
			cout << "Error: There are no students in the list!" << endl;
			return;
		}else if(numStudents == 1){

			Node *temp = tail;
			head = nullptr;
			tail = nullptr;
			delete temp;
			numStudents -= 1;
		}
		else{
			Node *temp = tail;
			tail = tail->prev;
			tail->next = nullptr;
			delete temp;
			numStudents -= 1;
		}
	}

	// Remove the Node with the student at the front (head) of the list
	// should not fail if list is empty! Print an error message if this occurs
	// Don't forget that your head and tail pointers will be null pointers if the list is empty
	void StudentList::popFront() {
		if(numStudents == 0){
			cout << "Error: There are no students in the list!" << endl;
			return;
		}
		else if(numStudents == 1){
			Node * temp = head;
			head = nullptr;
			tail = nullptr;
			numStudents --;
		}
		else{
			Node *temp = head;
			head = head->next;
			head->prev = nullptr;
			numStudents --;
		}
	}

	//insert a student at the position "index".
	// for this list, count head as index 0
	// if index is outside of current list range, 
	// print a message and insert the student at the back of the list
	// the previous Node at your target index should be moved forward. "For exampe, Node with student at index i, becomes index i+1" 
	// Remember that you already have methods that can add students to the front or back of list if needed! Don't repeat this code.
	void StudentList::insertStudent(Student s, int index) {
		if(index > numStudents){
			cout << "The index is out of bounds from the list: inserting student at the end of the list" << endl;
			addBack(s);
			return;
		}
		else{
			Node *temp = head;
			int i = 0;
			while(temp != NULL && i < index-1){
				i++;
				temp = temp->next;
			}
			Node * newNode = new Node(s,temp->next,temp);
			temp->next = newNode;
			temp = nullptr;
			numStudents++;
		}
	}

	//find the student with the given id number and return them
	// if no student matches, print a message 
	// and create and return a dummy student object
	Student StudentList::retrieveStudent(int idNum) {
		Student dummy;
		Node *temp = head;
		while(temp != NULL){
			//student matches
			if(temp->data.id == idNum){
				return temp->data;
			}
			temp = temp->next;
		}
		// No student matches
		cout <<"No student matches  ID number." << endl;
		return dummy;
	}

	// Remove a Node with a student from the list with a given id number
	// If no student matches, print a message and do nothing
	void StudentList::removeStudentById(int idNum) {
		Node *temp = head;
		while (temp != nullptr) {
        // If the student matches the ID
			if (temp->data.id == idNum) {
				numStudents--;

				// If the node is the head
				if (temp == head) {
					head = temp->next;
					if (head != nullptr) {
						head->prev = nullptr;
					}
				}
				// If the node is the tail
				else if (temp->next == nullptr) {
					temp->prev->next = nullptr;
				}
				// If the node is in the middle
				else {
					temp->prev->next = temp->next;
					temp->next->prev = temp->prev;
				}

				// If the list is now empty, update the tail
				if (head == nullptr) {
					tail = nullptr;
				}

				// Delete the node and set it to nullptr
				delete temp;
				temp = nullptr;
				return;
			}
			temp = temp->next;
    }


		cout << "No student matches ID given" << endl;


	}

	//Change the gpa of the student with given id number to newGPA
	void StudentList::updateGPA(int idNum, float newGPA) {
		Node *temp = head;
		while(temp != NULL){
			if(temp->data.id == idNum){
				temp->data.GPA = newGPA;
			}
			temp = temp->next;
		}
		

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
		if(otherList.numStudents == 0){
			return;
		}

		//Node *temp = new Node(otherList.head.data, otherList.head.next, nullptr);
		Node *temp = otherList.head;
		while(temp != NULL){
			tail->next = temp;
			temp->prev = tail;
			temp = temp->next;
			//updates number of students for each list
			otherList.numStudents -= 1;
			numStudents += 1;
			if(otherList.numStudents == 0){
				otherList.head = nullptr;
				otherList.tail = nullptr;
			}
		}		
		

	}

	//create a StudentList of students whose gpa is at least minGPA. (GPA >= minGPA)
	//Return this list.  The original (current) list should
	//not be modified (do not remove the students from the original list).
	StudentList StudentList::honorRoll(float minGPA) {
		StudentList gpaList;
		Node *temp = head;
		while(temp != NULL){
			if(temp->data.GPA >= minGPA){
				Node *newNode = new Node(temp->data);

				if(gpaList.numStudents == 0){
					gpaList.numStudents += 1;
					gpaList.head = newNode;
					gpaList.tail = newNode;
					
				}else{
					gpaList.numStudents += 1;
					newNode->prev = gpaList.tail;
					gpaList.tail->next = newNode;
					gpaList.tail = newNode;
					
				}
				

			}
			temp = temp->next;
		}

		

		return gpaList;
	}
