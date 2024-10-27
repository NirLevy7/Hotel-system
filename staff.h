#ifndef __STAFF_H
#define __STAFF_H
#define _CRT_SECURE_NO_WARNINGS
#define LENGTH 254
#define INITIAL_TODO_CAPACITY 5
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

typedef enum Role
{
	Cleaning,
	Delivery, //IE delivering towels, food & etc
	General //emergencies and etc

} Role;

typedef struct Staff
{
	int staffID;
	Role role;
	char name[LENGTH];

} Staff;

typedef struct ToDoList
{
	char** tasks;
	int size;
	int capacity;
} ToDoList;

typedef struct StaffManager
{
	struct Staff* staffArr;
	int numOfStaff;
	int staffCapacity;
	ToDoList* todoList;
} StaffManager;

int addToDoList(ToDoList* todoList, const char* task);
int removeToDoList(ToDoList* todoList, int taskNum);
int printToDoList(ToDoList* todoList);
int removeStaff(StaffManager* staffMan, int id);
int addStaff(StaffManager* staffMan, Staff staff);
int printStaffDetails(StaffManager* staffMan, Staff staff);
int printAllStaffDetails(StaffManager* staffMan);
int validID(int id);
int staffMemoryAllocation(StaffManager* staffMan, int n);
#endif // __STAFF_H_
