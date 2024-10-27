#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 6067)
#include "manager.h"
#include <stdio.h>
#include <string.h>
#include "functions.h"

//Prints the hotel's manager details.
int printManagerDetails(Manager manager) {
	printf("Manager Name: %s\n", manager.name);
	printf("Phone Number: %d\n", manager.phoneNum);
	return 1;
}
//Allows the user to change the manager's name, returns 1 if true otherwise 0.
int changeName(Manager* manager) {
	char newName[LENGTH];
	printf("Enter new name: ");
	if (fgets(newName, LENGTH, stdin) == NULL) {
		printf("Error reading input.\n");
		return 1;
	}
	newName[strcspn(newName, "\n")] = 0;

	strncpy(manager->name, newName, LENGTH - 1);
	manager->name[LENGTH - 1] = '\0';
	printf("Name changed successfully.\n");
	return 0;
}
//Allows the user to change the manager's phone number, returns 1 if true, 0 otherwise.
int changePhoneNumber(Manager* manager) {
	int newPhoneNum;
	printf("Enter new phone number: ");
	if (scanf("%d", &newPhoneNum) != 1) {
		printf("Invalid input. Please enter a valid number.\n");
		while (getchar() != '\n');
		return 1;
	}
	manager->phoneNum = newPhoneNum;
	printf("Phone number changed successfully.\n");
	return 0;
}