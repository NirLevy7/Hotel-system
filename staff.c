#pragma warning(disable : 6067)
#pragma warning(disable : 6001)
#include "staff.h"

//Prints all the staff's details, return 1 if successful, 0 otherwise.
int printAllStaffDetails(StaffManager* staffMan)
{

	if (staffMan->numOfStaff == 0) {
		printf("No staff members available.\n");
		return 0;
	}

	for (int i = 0; i < staffMan->numOfStaff; i++) {
		printf("Staff Member %d:\n", i + 1);
		printStaffDetails(staffMan, staffMan->staffArr[i]);
		printf("\n");
	}

	return 1;

}

//Checks whether a number is exactly 5 numbers, returns 1 if true, else 0.
int validID(int id)
{

	if (id >= 10000 && id <= 99999)
	{
		return 1;
	}
	else {
		return 0;
	}

}

//Method meant to handle memory allocation, returns 1 if successful, else 0.
int staffMemoryAllocation(StaffManager* staffMan, int n)
{
	if (!staffMan || n < 0 || staffMan->numOfStaff + n < 0)
	{
		return 0;
	}

	Staff* newStaffArr;



	newStaffArr = realloc(staffMan->staffArr, (staffMan->staffCapacity + n) * sizeof(Staff));


	if (!newStaffArr)
	{
		return 0;
	}

	staffMan->staffArr = newStaffArr;




	return 1;
}

//Method that allows the user to add a new staff, returns 1 if successful, 0 otherwise.
int addStaff(StaffManager* staffMan, Staff staff)
{

	if (staffMemoryAllocation(staffMan, 1) == 1 && validID(staff.staffID) == 1)
	{
		staffMan->numOfStaff++;
		staffMan->staffCapacity++;
		staffMan->staffArr[staffMan->numOfStaff - 1] = staff;

		return 1;
	}

	return 0;
}

//Returns a specific staff's details, returns 1 if successful, 0 otherwise.
int printStaffDetails(StaffManager* staffMan, Staff staff) {


	for (int i = 0; i < staffMan->numOfStaff; i++)
	{
		if (staffMan->staffArr[i].staffID == staff.staffID)
		{
			printf("Staff ID: %d\n", staff.staffID);
			printf("Name: %s\n", staff.name);


			switch (staff.role) {
			case Cleaning:
				printf("Role: Cleaning\n");
				break;
			case Delivery:
				printf("Role: Delivery\n");
				break;
			case General:
				printf("Role: General\n");
				break;
			default:
				printf("Role: None\n");
				break;
			}
			return 1;
		}
	}

	return 0;
}

//Allows the user to remove a staff from the array, returns 1 if successful, 0 otherwise.
int removeStaff(StaffManager* staffMan, int id)
{
	for (int i = 0; i < staffMan->numOfStaff; i++)
	{
		if (staffMan->staffArr[i].staffID == id)
		{

			staffMan->staffArr[i] = staffMan->staffArr[staffMan->numOfStaff - 1];
			staffMemoryAllocation(staffMan, -1);
			staffMan->numOfStaff--;
			staffMan->staffCapacity--;
			printf("\nThis staff member has been removed successfully!\n");
			return 1;
		}
	}
	printf("\nThis staff member doesn't found!\n");
	return 0;
}


//Adds a task to the task array, returns 1 if successful, 0 otherwise.
int addToDoList(ToDoList* todoList, const char* task) {
	if (todoList->capacity == 0) {
		// If capacity is 0, initialize with INITIAL_TODO_CAPACITY
		todoList->tasks = (char**)malloc(INITIAL_TODO_CAPACITY * sizeof(char*));
		if (todoList->tasks == NULL) {
			return -1;
		}
		todoList->capacity = INITIAL_TODO_CAPACITY;
	}
	else if (todoList->size == todoList->capacity) {
		int newCapacity = todoList->capacity * 2;
		char** newList = realloc(todoList->tasks, newCapacity * sizeof(char*));
		if (newList == NULL) {
			return -1;
		}
		todoList->tasks = newList;
		todoList->capacity = newCapacity;
	}

	todoList->tasks[todoList->size] = strdup(task);
	if (todoList->tasks[todoList->size] == NULL) {
		return -1;
	}

	todoList->size++;

	return todoList->size - 1;
}

//Removes a task from the task array, returns 1 if successful, 0 otherwise.
int removeToDoList(ToDoList* todoList, int taskNum) {
	if (taskNum < 0 || taskNum >= todoList->size || todoList->size == 0) {
		return -1;
	}
	free(todoList->tasks[taskNum]);

	for (int i = taskNum; i < todoList->size - 1; i++) {
		todoList->tasks[i] = todoList->tasks[i + 1];
	}
	todoList->size--;
	return 0;
}

//Prints all the tasks available, returns 1 if successful, 0 otherwise.
int printToDoList(ToDoList* todoList)
{
	for (int i = 0; i < todoList->size; i++)
	{
		printf("%d) %s\n", i + 1, todoList->tasks[i]);
	}
	return 1;
}

