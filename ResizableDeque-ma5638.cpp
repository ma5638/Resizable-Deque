//============================================================================
// Name         : assignment2.cpp
// Author       : Muhammad Ali
// Version      : 1.0
// Date Created : 01-04-2020
// Date Modified: 02-04-2020 
// Copyright    : All rights are reserved
// Description  : Array Implementation of a Resizable_Deque 
//============================================================================
#include<iostream>
#include<iomanip> //for setw() manipulator
#include<string>
using namespace std;


// Global Variables
#define MAX_DEQUES 10		// Max Number of Deques the System can hold




template <typename T>
class Resizable_Deque
{
	private:
		T *array;
		int front;
		int back;
		int deque_size;
		int capacity;
		int initial_capacity;

		// function to be used in void swap method
		template <class R>
		void swap_variable(R& a, R& b){		// swaps values of 2 variables
			R temp = b;
			b = a;
			a = temp;
		}

	public:
		Resizable_Deque(int n = 10);
		~Resizable_Deque();	//

		//========================== Acccessors ==========================
		bool isEmpty() const;
		bool isFull() const;
		int size() const;
		int getCapacity() const;
		T getFront();	//
		T getBack();	//

		//========================== Mutators ==========================
		void swap(Resizable_Deque &rd); //
		Resizable_Deque operator=(const Resizable_Deque rd); //
		void push_front(const T element);
		void push_back(const T element);
		void pop_front();
		void pop_back();
		void pop_front_back();
		void clear();
		//========================== Other ==========================
		void display();
		void doubleCap();			// double capacity
		void reduceCap();			// reduce capacity by factor 1/4
		void refresh();				// reorder deque to make front at index 0
	public:
		
		// underflow exception
		class underflow_exception: public runtime_error{
			public:
			underflow_exception(): runtime_error("Underflow Exception: Resizable_Deque is Empty"){};
		};


};


//===========================================
template<typename T> 
Resizable_Deque<T>::Resizable_Deque(int n)
{

	if(n<=10){ 			// default capacity if less is entered
		capacity = 10;
		initial_capacity = 10;
	} else{
		capacity = n;
		initial_capacity = n;
	}
	deque_size = 0;
	array = new T[capacity];
	front = 0;
	back = 0;
}
//===========================================
template<typename T> 
Resizable_Deque<T>::~Resizable_Deque()
{
	delete[] array;
	delete array;
}
//===========================================
template<typename T> 
void Resizable_Deque<T>::swap(Resizable_Deque &rd)		// swap variables using a function in class
{
	//
	swap_variable<int>(capacity, rd.capacity);
	swap_variable<int>(initial_capacity, rd.initial_capacity);
	swap_variable<int>(front, rd.front);
	swap_variable<int>(back, rd.back);
	swap_variable<int>(deque_size, rd.deque_size);
	swap_variable<T*>(array, rd.array);

}
//===========================================
template<typename T> 
Resizable_Deque<T> Resizable_Deque<T>::operator=(const Resizable_Deque rd)
{
	// creating a local copy of resizable deque
	Resizable_Deque<T> copy(rd.initial_capacity);
	copy.capacity = rd.capacity;
	copy.front = rd.front;
	copy.back = rd.back;
	copy.deque_size	= rd.deque_size;
	delete[] copy.array;
	copy.array = new T[copy.capacity];
	for(int i = 0; i < capacity;i++)
	{
		copy.array[i] = rd.array[i];
	}

	//swap copy with current deque
	swap(copy);
}


//===========================================
template<typename T> 
void Resizable_Deque<T>::push_front(const T element)
{
	// to check if we have to double capacity
	if(isFull()){
		refresh();
		doubleCap();
	}
	front = (front-1)%(capacity);
	front = front<0? (capacity+front):front; // to deal with negative values of front and translating them into positive values
	array[front] = element;
	deque_size++;




}
//===========================================
template<typename T> 
void Resizable_Deque<T>::push_back(const T element)
{
	// to check if we have to double capacity
	if(isFull()){
		refresh();
		doubleCap();
	}
	array[back] = element;
	back = (back+1)%(capacity);
	deque_size++;



}
//===========================================
template<typename T> 
void Resizable_Deque<T>::pop_front()
{
	
	if(isEmpty()){
		throw underflow_exception();
	} 
	else{
		front = (front+1)%(capacity);	// throw exception if deque is empty
		deque_size --;

		// check if the capacity has to be reduced by factor 4
		if(capacity>initial_capacity && deque_size<=capacity/4)
		{
			refresh();
			reduceCap();
		}
	}


}
//===========================================
template<typename T> 
void Resizable_Deque<T>::pop_back()
{
	
	if(isEmpty()){
		throw underflow_exception();	// throw exception if deque is empty
	}
	else
	{
		back = (back-1)%(capacity);
		back = back<0? (capacity+back):back;
		deque_size --;

		// check if the capacity has to be reduced by factor 4
		if(capacity>initial_capacity && deque_size<=capacity/4)
		{
			refresh();
			reduceCap();
		}
		
	}

}
//===========================================
template<typename T> 
void Resizable_Deque<T>::pop_front_back()
{
	// making sure the double pop only works with atleast 2 elements
	if(deque_size<2){
		throw runtime_error("Underflow Exception: Cannot double pop with less than 2 elements");
	}
	else
	{
		pop_front();
		pop_back();
		
	}

}
//===========================================
template<typename T> 
void Resizable_Deque<T>::clear()
{
	// destroy all elements of the array and return capacity to initial
	delete[] array;
	capacity = initial_capacity;
	array = new T[capacity];
	front = 0;
	back = 0;
	deque_size = 0;

}
//===========================================
template<typename T> bool Resizable_Deque<T>::isEmpty() const
{
	return deque_size == 0;
}
//===========================================
template<typename T> bool Resizable_Deque<T>::isFull() const
{
	return deque_size == capacity;
}
//===========================================
template<typename T> 
int Resizable_Deque<T>::size() const
{
	return deque_size;
}
// ===========================================
template<typename T> 
int Resizable_Deque<T>::getCapacity() const
{
	return capacity;
}
// ===========================================
template<typename T> 
T Resizable_Deque<T>::getFront()
{
	if(deque_size!= 0){
		return array[front];
	}
	else
		throw underflow_exception();
}
// ===========================================
template<typename T> 
T Resizable_Deque<T>::getBack()
{
	if(deque_size!= 0){	
		int last = (back-1)%capacity;
		last = last<0? (last+capacity):last;		// translating -values of last into +values
		return array[last];
	}
	else throw underflow_exception();
}

// ===========================================
template<typename T> 
void Resizable_Deque<T>::doubleCap()
{
	T* newArray = new T[capacity*2];
	for(int i = 0; i < capacity; i ++)
	{
		newArray[i] = array[i];
	}
	array = newArray;
	capacity *= 2;
	back = deque_size%capacity;
	cout << "New Size: " << deque_size << "\nNew capacity: " << capacity << endl;
}
// ===========================================
template<typename T> 
void Resizable_Deque<T>::reduceCap()
{
	int newCapacity = (capacity/4)<initial_capacity? initial_capacity:(capacity/4);

	T* newArray = new T[newCapacity];
	for(int i = 0; i < newCapacity; i ++)
	{
		newArray[i] = array[i];
	}
	array = newArray;
	capacity = newCapacity;
	back = deque_size%capacity;
}
// ===========================================
template<typename T> 
void Resizable_Deque<T>::refresh() // assigning front to be 0
{
	T* newArray = new T[capacity];
	int assignIndex = 0;

	if(deque_size>=1)
	{
		newArray[assignIndex] = array[front];
		assignIndex++;
	}

	for(int i = (front+1)%capacity; i != back; i = (i+1)%capacity)
	{
		newArray[assignIndex] = array[i];
		assignIndex++;
	}
	delete[] array;
	array = newArray;
	front = 0;
	back = deque_size%capacity;

}
// ===========================================
//============================================================================
// Name         : lab6.1.cpp
// Author       : Khalid Mengal
// Version      : 1.0
// Date Created : 04-11-2019
// Date Modified: 15-03-2020 
// Copyright    : All rights are reserved
// Description  : Array implmentation of Queue 
//============================================================================

// function to display
template<typename T> 
void Resizable_Deque<T>::display()
{
	
	cout<<"+";
	for(int i=0; i<capacity; i++)
		cout<<"---+";
	cout<<endl;
	for(int i=0; i<capacity; i++)
	{
		string str="|";
		if(i==front)
			str+="F";
		if(back==i)
			str+="R";
		str+=" ";
		cout<<left<<setw(4)<<str;

	}
	cout<<"|";
	cout<<endl<<"+";
	for(int i=0; i<capacity; i++)
		cout<<"---+";	
		cout<<endl;
	for(int i=0; i<capacity; i++)
	{
		if(((front<back) and (i>=front and i<back)) or ((front > back) and (i>=front or i<back )) or deque_size==capacity)
		{cout<<"|"<<setw(3)<<array[i];
		}
		else
			cout<<"|   ";	
	}
	cout<<"|"<<endl<<"+";
	for(int i=0; i<capacity; i++)
		cout<<"---+";	

	cout<<endl<<endl;

}

//===========================================


// Class for Running Program
template <typename T>
class System
{
private:
	Resizable_Deque<T>* list[MAX_DEQUES];	// list of deques
	bool present[MAX_DEQUES];				// variable that indicates the indices which have a deque inside
	int edit;								// variable that holds the deque number to edit
public:
	System();
	void systemLoop();
	void help();
	void helpDeque();
	void addDeque();
	void removeDeque();
	void editDeque();
	void dequeInterface();				// opens the deque interface for the ith deque
	void swapDeques();
};
//===========================================
template <typename T>
System<T>::System()
{
	for(int i = 0; i < MAX_DEQUES; i++){
		present[i] = false;					// there is no deque in the beginning, so all indices are false
	}
	edit = 0;
}


//===========================================
template <typename T>
void System<T>::systemLoop()
{
	string choice;
	bool loop = true;						// variable to determine whether the loop should continue
	while(loop)
	{

		try
		{
			help();
			cout<<"# ";
			getline(cin,choice);
			switch (stoi(choice.substr(0,choice.find(" "))))
			{
				case 1:
					addDeque();
					break;
				case 2:
					removeDeque();
					break;
				case 3:
					editDeque();
					break;
				case 4:
					swapDeques();
					break;
				case 0:
					loop = false;		// break loop
					break;
				default:
					break;

			}

			
		}
		catch(exception &ex)	// catch all exceptions
		{	cout<<ex.what()<<endl; }
	
	}
}
//===========================================

// instructions for the system
template <typename T>
void System<T>::help()
{
	cout << "===== System Interface =====" << endl 
	<< "Commands available (Type Number)"<<endl
	<< "1. Add New Deque" << endl
	<< "2. Remove Deque" << endl
	<< "3. Edit Deque" << endl
	<< "4. Swap Deques" << endl
	<< "0. Exit"<<endl;
}

//===========================================

// interface for when editing a deque (option 3)
template <typename T>
void System<T>::dequeInterface()
{
	string choiceDI;
	bool loop = true;
	while(loop)
	{


		try
		{
			T element;
			cout << "=====Deque Interface=====\n";
			list[edit]->display();
			helpDeque();
			cout<<"# ";
			cin >> choiceDI;

			if(choiceDI=="ab" || choiceDI == "af"){
				cout << "Type in element to add: " << endl;
				cout << "# ";
				cin >> element;
			}
			if(choiceDI.substr(0,choiceDI.find(" "))=="ab")
					list[edit]->push_back(element);
			else if(choiceDI.substr(0,choiceDI.find(" "))=="af")
					list[edit]->push_front(element);
			
			else if(choiceDI=="rb")		//
				list[edit]->pop_back();

			else if(choiceDI=="rf")		//
				list[edit]->pop_front();

			else if(choiceDI=="rfb")
				list[edit]->pop_front_back();

			else if(choiceDI=="clear")
				list[edit]->clear();

			else if(choiceDI=="f")
				cout << "Front: " << list[edit]->getFront() << endl;

			else if(choiceDI=="b")
				cout << "Back: " << list[edit]->getBack() << endl;
			else if(choiceDI=="s")
				cout << "Size: " << list[edit]->size() << endl;
			else if(choiceDI=="c")
				cout << "Capacity: " << list[edit]->getCapacity() << endl;

			
			else if(choiceDI == "exit")
				break;
			
			else
				cout<<"Invalid input !!! Please try again"<<endl;
		}
		catch(exception &ex)
		{	cout<<"Exception: " << ex.what()<<endl; }
	}
	
}
//===========================================


// instructions for deque interface
template <typename T>
void System<T>::helpDeque()
{
	cout<<"Commands available"<<endl
		<< "Add Back: \" ab \"" << endl
		<< "Add Front: \" af \"" << endl
		<< "Remove Back: \" rb \"" << endl
		<< "Remove Front: \" rf \"" << endl
		<< "Remove Front and Back: \" rfb \"" << endl
		<< "Clear Deque: \" clear \" " << endl
		<< "Get Front: \" f \" " << endl
		<< "Get Back: \" b \" " << endl
		<< "Get Size: \" s \" " << endl
		<< "Get Capacity: \" c \" " << endl
		<<"exit"<<endl;
}


//===========================================

// UI for adding deque
template <typename T>
void System<T>::addDeque()
{
	try
	{
	string capacity;
	int intCapacity;
	cout << "What is the initial capacity of your new deque?" << endl;
	cout << "NOTE: 10 is the minimum allowed and will be taken if a number smaller is given" << endl;
	cout << "# ";
	getline(cin, capacity);
	intCapacity = stoi(capacity);
	cout << "Where would you like to place the deque? (Type Number) \n";
	cout << "NOTE: Placing a deque over a \'Used\' deque replaces it\n";

	// displaying all deques
	for(int i = 0; i < MAX_DEQUES; i++)
	{
		cout << "# Deque " << i;
		if(present[i])
		{
			cout << " Used" << endl;		// Used = There is a deque in this position
		} else{
			cout << " Free" << endl;		// Free = There is no deque in this position
		}
	}
	string position;
	int intPosition;
	cout << "# ";
	getline(cin, position);
	intPosition = stoi(position);


	if(intPosition<0 || intPosition>=MAX_DEQUES)		// check for out of range
		throw out_of_range("");

	list[intPosition] = new Resizable_Deque<T>(intCapacity);	// adding deque
	present[intPosition] = true;	// indicating the index "intPosition" has a deque

	cout << "Action: Deque " << intPosition << " has just been added\n";

	} catch(exception &e) {
		cout << "Exception: " << e.what() << endl;
	}
}


//===========================================


// UI for selecting which deque to edit
template <typename T>
void System<T>::editDeque()
{
	string choice;
	try
	{
		cout << "Which deque would you like to edit? (Type Number) \n";

		// print positions with deques only
		for(int i = 0; i < MAX_DEQUES; i++)
		{
			if(present[i])
			{
				cout << "# Dequeu " << i << endl;
			}
		}

		cout << "# ";
		getline(cin, choice);
		edit = stoi(choice);		// set edit to the position where the deque will be edited

		if(edit <0 || edit >= MAX_DEQUES)	// making sure edit is in the ranges
			cout << "Error: Choice out of range!" << endl;
		else if (!present[edit])			// making sure there is a deque present at the position of edit
			cout << "Error: There is no deque in given position" << endl;
		else
			dequeInterface();		// call the deque interface to actually edit deque


	} catch(exception &e) {
		cout << "Exception: " << e.what() << endl;
	}
}

//===========================================


// to remove a deque
template <typename T>
void System<T>::removeDeque()
{
	string choice;
	int intChoice;
	try
	{
		cout << "Which deque would you like to remove? (Type Number) \n";
		for(int i = 0; i < MAX_DEQUES; i++)
		{
			cout << "# Deque " << i;
			if(present[i])
			{
				cout << " Used" << endl;
			} else{
				cout << " Free" << endl;
			}

		}

		cout << "# ";
		getline(cin, choice);
		intChoice = stoi(choice);

		if(present[intChoice])	// check if there exists a deque at given position
			delete list[intChoice];
		else
			cout << "There is no deque in given position" << endl;
		
		present[stoi(choice)] = false;


	} catch(exception &e) {
		cout << "Exception: " << e.what() << endl;
	}
}

//===========================================

template <typename T>
void System<T>::swapDeques()
{
	string choice1, choice2;
	int intChoice1, intChoice2;
	try
	{

		// select 1st deque
		cout << "Select first deque for swapping? (Type Number) \n";
		for(int i = 0; i < MAX_DEQUES; i++)
		{
			
			if(present[i])
			{
				cout << "# Deque " << i << endl;
			}

		}

		cout << "# ";
		getline(cin, choice1);
		intChoice1 = stoi(choice1);
		if(!present[intChoice1])					// making sure there is a deque at given position
			throw runtime_error("Deque not present");

		// select 2nd deque
		cout << "Select second deque for swapping? (Type Number) \n";
		for(int i = 0; i < MAX_DEQUES; i++)
		{
			
			if(present[i])
			{
				cout << "# Deque " << i << endl;
			}

		}

		cout << "# ";
		getline(cin, choice2);
		intChoice2 = stoi(choice2);
		if(!present[intChoice2])					// making sure there is a deque at given position
			throw runtime_error("Deque not present");
		else if(intChoice1 == intChoice2)			// making sure swap is not applied to same deques
			throw runtime_error("Cannot swap same deque");
		else
			(*list[intChoice1]).swap(*list[intChoice2]);


	} catch(exception &e) {
		cout << "Exception: " << e.what() << endl;
	}
}

//===========================================


// function for choosing type of variable for system and deque
string chooseType()
{
	string choice;
	bool chosen;
	cout<<"Please choose variable type for System: (Type Number)"<<endl
	<< "1. int" << endl
	<< "2. string" << endl
	<< "3. float" << endl;

	cout << "# ";
	getline(cin, choice);
	// cout << "Please enter to continue" << endl;
	while(!(choice== "1" || choice == "2" || choice == "3")) // ask again if choice is invalid
	{
		cout << "Please type in either 1, 2, or 3" << endl;
		getline(cin, choice);
	}

	return choice;
}


//===========================================
int main()
{
	cout << "===== Deque System =====\n";
	string dataChoice = chooseType();	// choose data type

	// deciding data type for the system
	if(dataChoice=="1")
	{
		System<int> sys;
		sys.systemLoop();
	}
	 else if(dataChoice == "2") {
		System<string> sys2;
		sys2.systemLoop();
	}
	else if(dataChoice == "3") {
		System<float> sys3;
		sys3.systemLoop();
	}

	return EXIT_SUCCESS;
}