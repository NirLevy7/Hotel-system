#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 6031)
#pragma warning(disable : 6054)
#pragma warning(disable : 6067)
#pragma warning(disable : 6029)
#include "functions.h"
#include <stdlib.h>
#include "hotel.h"
#include "room.h"
#include "date.h"
#include <errno.h>


Hotel tmpHotel = { 0, "", "", NULL, NULL, { "", 0 }, { NULL, 0, 0 } };
HotelManager hotelManTmp = { NULL, NULL, 0 };
Room roomTmp = { 0, First, 0, 0 };
Staff staffTmp = { 0, General, "" };
Manager managerTmp = { "", 0 };
char* pAddress = NULL;
int tmpHotelID = 0;
int tmpInput = 0;
char tmpName[LENGTH] = { 0 };
Date productionDate = { 0, 0, 0 };
Date expirationDate = { 0, 0, 0 };


void case1()
{

	printf("\nPlease choose a hotel ID (It has to have 6 positive digits)\n");
	scanf("%d", &tmpHotelID);
	clearInputBuffer();

	while (validHotel(&hotelManTmp, tmpHotelID) == 0 || findHotelByID(&hotelManTmp, tmpHotelID) == 1)
	{
		printf("\nThe hotel ID is invalid, please enter a valid hotel ID (It has to have 6 positive digits\n");
		scanf("%d", &tmpHotelID);
		clearInputBuffer();
	}
	tmpHotel.hotelID = tmpHotelID;
	printf("\nPlease enter a name for the hotel\n");
	fgets(tmpHotel.hotelName, LENGTH, stdin);
	tmpHotel.hotelName[strcspn(tmpHotel.hotelName, "\n")] = '\0';
	printf("\nPlease enter an address for the hotel\n");
	fgets(tmpHotel.address, LENGTH, stdin);
	tmpHotel.address[strcspn(tmpHotel.address, "\n")] = '\0';
	printf("\nPlease enter any details you feel that is necessary for the hotel (You can leave empty)\n");
	fgets(tmpHotel.propertyDetails, LENGTH, stdin);
	tmpHotel.address[strcspn(tmpHotel.propertyDetails, "\n")] = '\0';
	tmpHotel.manager.name[0] = '\0';  // Initialize manager name as empty string
	tmpHotel.manager.phoneNum = 0;    // Initialize manager phone number as 0
	addHotel(&hotelManTmp, &tmpHotel, tmpHotel.propertyDetails);
	printf("\nHotel added successfully!\n");
}

void case2()
{
	printf("\nPlease choose the ID of the hotel to remove:\n");
	scanf("%d", &tmpHotelID);
	clearInputBuffer();
	if (findHotelByID(&hotelManTmp, tmpHotelID))
	{
		if (removeHotel(&hotelManTmp, tmpHotelID))
		{
			printf("Hotel successfully removed.\n");
		}
		else
		{
			printf("Failed to remove hotel.\n");
		}
	}
	else
	{
		printf("Hotel with ID %d not found.\n", tmpHotelID);
	}
}

void case3()
{
	printf("\nPlease type the ID of the hotel you'd like to add staff to\n");
	scanf("%d", &tmpHotelID);
	Hotel* hotel = returnHotelByID(&hotelManTmp, tmpHotelID);
	if (hotel == NULL) {
		printf("\nHotel not found.\n");
		return;
	}
	printf("\nPlease choose the new staff ID, 5 Digits\n");
	scanf("%d", &staffTmp.staffID);
	while (validID(staffTmp.staffID) == 0)
	{
		printf("\nPlease choose a valid ID with 5 digits exactly:\n");
		scanf("%d", &staffTmp.staffID);
	}
	clearInputBuffer();
	printf("\nPlease enter a name for the new staff\n");
	fgets(&staffTmp.name, LENGTH, stdin);
	staffTmp.name[strcspn(staffTmp.name, "\n")] = '\0';

	printf("\nPlease enter a role for the staff\n1) Cleaning\n2) Delivery\n3) General\n");
	scanf("%d", &tmpInput);
	while (tmpInput < 1 || tmpInput > 3)
	{
		printf("\nPlease enter a role for the staff\n1)Cleaning\n2)Delivery\n3)General\n");
		scanf("%d", &tmpInput);
		clearInputBuffer();
	}
	staffTmp.role = --tmpInput;
	addStaff(&returnHotelByID(&hotelManTmp, tmpHotelID)->hotelStaffManager, staffTmp);
	printf("\nStaff added successfully!\n");
}

void case4()
{
	printf("\nPlease type the ID of the hotel you'd like to remove staff from\n");
	scanf("%d6", &tmpHotelID);

	printf("\nPlease choose the staff ID that you want to remove\n");
	scanf("%d5", &staffTmp.staffID);

	while (validID(staffTmp.staffID) == 0)
	{
		printf("\nPlease choose a valid ID with 5 digits exactly\n");
		scanf("%d5", &staffTmp.staffID);
	}
	Hotel* tmpHotel = returnHotelByID(&hotelManTmp, tmpHotelID);
	if (tmpHotel != NULL)
		removeStaff(&tmpHotel->hotelStaffManager, staffTmp.staffID);
}

void case5()
{
	printf("\nPlease input the ID of the hotel you'd like to add/change a manager.\n");
	scanf("%d", &tmpHotelID);
	clearInputBuffer();
	Hotel* hotel = returnHotelByID(&hotelManTmp, tmpHotelID);
	if (hotel == NULL) {
		printf("Hotel not found.\n");
		return;
	}
	printf("\nPlease choose a name for the Manager\n");
	changeName(&hotel->manager);
	printf("\nPlease choose a phone number\n");
	changePhoneNumber(&hotel->manager);
	printManagerDetails(hotel->manager);
}

void case6()
{
	printf("\nPlease enter the ID of the hotel you'd like to add room to\n");
	scanf("%d", &tmpHotelID);
	clearInputBuffer();
	Hotel* hotel = returnHotelByID(&hotelManTmp, tmpHotelID);
	if (hotel == NULL) {
		printf("\nHotel not found.\n");
		return;
	}
	printf("\nPlease enter the room number\n");
	scanf("%d", &roomTmp.roomNumber);
	clearInputBuffer();
	printf("\nPlease choose the floor you'd like the room to be in\n1) First Floor\n2) Second Floor\n3) Third Floor\n");
	scanf("%d1", &roomTmp.floor);
	roomTmp.floor -= 1;
	printf("\nPlease choose how many residents will be staying in the room (Max 4)\n");
	scanf("%d", &roomTmp.numOfResidents);
	while (roomTmp.numOfResidents > 4 || roomTmp.numOfResidents < 1)
	{
		printf("\nError!\nThe number is wrong, please try again:\n");
		scanf("%d", &roomTmp.numOfResidents);
	}
	roomTmp.roomCapacity = ROOMCAPACITY;
	addRoom(&(returnHotelByID(&hotelManTmp, tmpHotelID)->hotelRoomManager), roomTmp);
	clearInputBuffer();
	printf("\nRoom added successfully!\n");
}

void case7()
{
	printf("\nPlease enter the ID of the hotel you'd like to remove a room from\n");
	scanf("%d", &tmpHotelID);
	if (printHotelDetails(returnHotelByID(&hotelManTmp, tmpHotelID)) == 0)
		return;
	printf("\nPlease enter the number of the floor you'd like to remove\n");
	scanf("%d1", &tmpInput);
	tmpInput -= 1;
	printf("\nPlease enter the room number you'd like to remove\n");
	scanf("%d", &roomTmp.roomNumber);
	Room* tmpRoom = returnRoom(&returnHotelByID(&hotelManTmp, tmpHotelID)->hotelRoomManager, roomTmp.roomNumber, tmpInput);
	if (tmpRoom != NULL)
		removeRoom(&returnHotelByID(&hotelManTmp, tmpHotelID)->hotelRoomManager, *tmpRoom);
	else {
		printf("\nThe room or the floor doesn't exist!\n");
	}
	clearInputBuffer();
}

void case8()
{
	printf("\nPlease enter the hotel ID you'd like to host residents\n");
	scanf("%d6", &tmpHotelID);
	Hotel* hotel = returnHotelByID(&hotelManTmp, tmpHotelID);
	if (hotel == NULL) {
		printf("\nHotel not found.\n");
		return;
	}
	printf("\nPlease enter the number of the floor you'd like to host residents\n");
	scanf("%d1", &tmpInput);
	printf("\nPlease enter the room number you'd like to host residents\n");
	scanf("%d1", &roomTmp.roomNumber);
	if ((isRoomNumberExists(&(returnHotelByID(&hotelManTmp, tmpHotelID)->hotelRoomManager), roomTmp.roomNumber) == 0))
	{
		printf("This room doesn't exist!");
		return;
	}
	printf("\nPlease choose the amount of residents you'd like to host\n");
	scanf("%d", &roomTmp.numOfResidents);
	fillRoom(&returnHotelByID(&hotelManTmp, tmpHotelID)->hotelRoomManager, *returnRoom(&returnHotelByID(&hotelManTmp, tmpHotelID)->hotelRoomManager, roomTmp.roomNumber, tmpInput), roomTmp.numOfResidents);
	clearInputBuffer();
}

void case9()
{
	printf("\nPlease enter the hotel ID you'd like to remove residents from\n");
	scanf("%d6", &tmpHotelID);
	printf("\nPlease enter the number of the floor you'd like to remove residents from\n1)First\n2)Second\n3)Third\n");
	scanf("%d1", &tmpInput);
	tmpInput -= 1;
	printf("\nPlease enter the room number you'd like to remove residents from\n");
	scanf("%d1", &roomTmp.roomNumber);
	printf("\nPlease choose the amount of residents you'd like to remove\n");
	scanf("%d", &roomTmp.numOfResidents);
	emptyRoom(&returnHotelByID(&hotelManTmp, tmpHotelID)->hotelRoomManager, *returnRoom(&returnHotelByID(&hotelManTmp, tmpHotelID)->hotelRoomManager, roomTmp.roomNumber, tmpInput), roomTmp.numOfResidents);
	clearInputBuffer();
}


void case10()
{
	int hotelID, staffID;
	char task[LENGTH];
	Date startDate, endDate;
	char dateStr[LENGTH];

	printf("\nPlease enter the hotel ID: ");
	scanf("%d", &hotelID);
	clearInputBuffer();

	Hotel* hotel = returnHotelByID(&hotelManTmp, hotelID);
	if (hotel == NULL) {
		printf("Hotel not found.\n");
		return;
	}

	printf("Please enter the staff ID: ");
	scanf("%d", &staffID);
	clearInputBuffer();

	// Check if staff exists
	int staffIndex = -1;
	for (int i = 0; i < hotel->hotelStaffManager.numOfStaff; i++) {
		if (hotel->hotelStaffManager.staffArr[i].staffID == staffID) {
			staffIndex = i;
			break;
		}
	}

	if (staffIndex == -1) {
		printf("Staff not found.\n");
		return;
	}

	printf("Enter the task description: ");
	fgets(task, LENGTH, stdin);
	task[strcspn(task, "\n")] = 0; // Remove newline

	printf("Enter the start date (dd^^mm^^yyyy): ");
	fgets(dateStr, LENGTH, stdin);
	dateStr[strcspn(dateStr, "\n")] = 0; // Remove newline
	convertToDate(dateStr, &startDate);

	printf("Enter the end date (dd^^mm^^yyyy): ");
	fgets(dateStr, LENGTH, stdin);
	dateStr[strcspn(dateStr, "\n")] = 0; // Remove newline
	convertToDate(dateStr, &endDate);

	if (!ValidDate(&startDate) || !ValidDate(&endDate)) {
		printf("Invalid date format. Task not added.\n");
		return;
	}

	if (!checkDepartureDateAfterArrivalDate(&startDate, &endDate)) {
		printf("End date must be after start date. Task not added.\n");
		return;
	}

	// Check if todoList exists, if not, initialize it
	if (hotel->hotelStaffManager.todoList == NULL) {
		hotel->hotelStaffManager.todoList = (ToDoList*)malloc(sizeof(ToDoList));
		if (hotel->hotelStaffManager.todoList == NULL) {
			printf("Failed to allocate memory for ToDoList. Task not added.\n");
			return;
		}
		hotel->hotelStaffManager.todoList->tasks = (char**)malloc(INITIAL_TODO_CAPACITY * sizeof(char*));
		if (hotel->hotelStaffManager.todoList->tasks == NULL) {
			printf("Failed to allocate memory for ToDoList tasks. Task not added.\n");
			free(hotel->hotelStaffManager.todoList);
			hotel->hotelStaffManager.todoList = NULL;
			return;
		}
		hotel->hotelStaffManager.todoList->size = 0;
		hotel->hotelStaffManager.todoList->capacity = INITIAL_TODO_CAPACITY;
	}

	// Create the task string with dates
	char fullTask[LENGTH * 2];
	snprintf(fullTask, sizeof(fullTask), "[%02d/%02d/%04d - %02d/%02d/%04d] %s (Assigned to: %s)",
		startDate.day, startDate.month, startDate.year,
		endDate.day, endDate.month, endDate.year,
		task, hotel->hotelStaffManager.staffArr[staffIndex].name);

	// Add the task to the to-do list
	if (addToDoList(hotel->hotelStaffManager.todoList, fullTask) != -1) {
		printf("Task added successfully.\n");
	}
	else {
		printf("Failed to add task. To-do list might be full.\n");
	}
}

void case11()
{
	//printAllHotelDetails(&hotelManTmp);
	if (hotelManTmp.numOfHotels == 0) {
		printf("No hotels available.\n");
		return;
	}

	printf("\n--- All Hotel Details ---\n");

	// Create an array of hotels from the linked list
	Hotel* hotelArray = malloc(hotelManTmp.numOfHotels * sizeof(Hotel));
	if (hotelArray == NULL) {
		printf("Memory allocation failed.\n");
		return;
	}

	Hotel* current = hotelManTmp.head;
	int index = 0;
	while (current != NULL) {
		hotelArray[index++] = *current;
		current = current->next;
	}

	// Use generalArrayFunction to print all hotel details
	generalArrayFunction(hotelArray, hotelManTmp.numOfHotels, sizeof(Hotel), printHotelElement);

	free(hotelArray);
	printf("\nTotal number of hotels: %d\n", hotelManTmp.numOfHotels);
}

void case12()
{
	printf("\nPlease enter the ID of the hotel you'd like to print details of\n");
	scanf("%d", &tmpHotelID);
	printHotelDetails(returnHotelByID(&hotelManTmp, tmpHotelID));
	clearInputBuffer();
}

void case13()
{
	int hotelID, searchMethod, searchKey;

	printf("\nEnter the hotel ID to search rooms: ");
	scanf("%d", &hotelID);
	clearInputBuffer();

	Hotel* hotel = returnHotelByID(&hotelManTmp, hotelID);
	if (hotel == NULL) {
		printf("Hotel not found.\n");
		return;
	}

	RoomManager* roomManager = &(hotel->hotelRoomManager);
	if (roomManager->numOfRooms == 0) {
		printf("No rooms available for search.\n");
		return;
	}

	if (roomManager->sort == notSorted) {
		printf("The room array is not sorted. Please sort the rooms first.\n");
		return;
	}

	printf("\nChoose search method:\n");
	printf("1. Room Number\n");
	printf("2. Floor\n");
	printf("3. Number of Residents\n");
	printf("Enter your choice (1-3): ");
	scanf("%d", &searchMethod);
	clearInputBuffer();

	if (searchMethod < 1 || searchMethod > 3) {
		printf("Invalid choice. Exiting search.\n");
		return;
	}

	printf("\nEnter the search key: ");
	scanf("%d", &searchKey);
	clearInputBuffer();

	Room* result = NULL;
	handleRoomSearch(roomManager, searchMethod, searchKey, &result);

	if (result != NULL) {
		printf("Room found:\n");
		printf("Room Number: %d\n", result->roomNumber);
		printf("Floor: %d\n", result->floor + 1);
		printf("Number of Residents: %d\n", result->numOfResidents);
		printf("Room Capacity: %d\n", result->roomCapacity);
	}
	else {
		printf("Room not found.\n");
	}
}

void case14()
{
	int sortChoice;
	printf("\nChoose sorting criteria:\n");
	printf("1. Room Number\n");
	printf("2. Floor Number\n");
	printf("3. Number of Residents\n");
	printf("Enter your choice (1-3): ");
	scanf("%d", &sortChoice);
	clearInputBuffer();

	printf("\nEnter the hotel ID to sort rooms: ");
	int hotelID;
	scanf("%d", &hotelID);
	clearInputBuffer();

	Hotel* hotel = returnHotelByID(&hotelManTmp, hotelID);
	if (hotel == NULL) {
		printf("Hotel not found.\n");
		return;
	}

	RoomManager* roomMan = &(hotel->hotelRoomManager);
	if (roomMan->numOfRooms == 0) {
		printf("No rooms available to sort.\n");
		return;
	}
	switch (sortChoice) {
	case 1:
		qsort(roomMan->roomArr, roomMan->numOfRooms, sizeof(Room), compareRoomNumber);
		roomMan->sort = roomNumber;
		printf("Rooms sorted by Room Number.\n");
		break;
	case 2:
		qsort(roomMan->roomArr, roomMan->numOfRooms, sizeof(Room), compareFloorNumber);
		roomMan->sort = floor;
		printf("Rooms sorted by Floor Number.\n");
		break;
	case 3:
		qsort(roomMan->roomArr, roomMan->numOfRooms, sizeof(Room), compareNumResidents);
		roomMan->sort = numOfResidents;
		printf("Rooms sorted by Number of Residents.\n");
		break;
	default:
		printf("Invalid choice. No sorting performed.\n");
		return;
	}

	printf("\nSorted Room List:\n");
	printAllRoomsDetails(roomMan);
	return;
}

void case15()
{
	exportFileToText();
}

void case16()
{
	exportFileToBinary();
}

void case17()
{
	char filename[256];
	char fileType[5];
	printf("Enter the filename to import from: ");
	scanf("%255s", filename);

	printf("Enter file type (txt or bin): ");
	scanf("%4s", fileType);

	if (strcmp(fileType, "txt") == 0) {
		importFromTextFile(filename);
	}
	else if (strcmp(fileType, "bin") == 0) {
		importFromBinaryFile(filename);
	}
	else {
		printf("Invalid file type. Please enter 'txt' or 'bin'.\n");
	}
}

void clearInputBuffer()
{
	int c;
	while ((c = getchar()) != '\n' && c != EOF)
	{

	}
}

void exportFileToText()
{
	const char* filename = "hotel_export.txt";

	// Delete the existing file if it exists
	if (remove(filename) == 0) {
		printf("Previous export file deleted.\n");
	}
	else if (errno != ENOENT) {
		// ENOENT means file doesn't exist, which is fine
		perror("Error deleting previous export file");
		return;
	}

	FILE* file = fopen(filename, "w");
	if (file == NULL) {
		perror("Error opening file for writing");
		return;
	}

	fprintf(file, "Hotel Management System Export\n\n");

	Hotel* current = hotelManTmp.head;
	while (current != NULL) {
		fprintf(file, "--- Hotel Details ---\n");
		fprintf(file, "Hotel ID: %d\n", current->hotelID);
		fprintf(file, "Hotel Name: %s\n", current->hotelName);
		fprintf(file, "Address: %s\n", current->address);
		fprintf(file, "Property Details: %s\n", (char*)*current->propertyDetails);

		fprintf(file, "\nManager Details:\n");
		fprintf(file, "Name: %s\n", current->manager.name);
		fprintf(file, "Phone: %d\n", current->manager.phoneNum);

		fprintf(file, "\nStaff Details:\n");
		for (int i = 0; i < current->hotelStaffManager.numOfStaff; i++) {
			Staff staff = current->hotelStaffManager.staffArr[i];
			fprintf(file, "Staff ID: %d, Name: %s, Role: %d\n",
				staff.staffID, staff.name, staff.role);
		}

		fprintf(file, "\nRoom Details:\n");
		for (int i = 0; i < current->hotelRoomManager.numOfRooms; i++) {
			Room room = current->hotelRoomManager.roomArr[i];
			fprintf(file, "Room Number: %d, Floor: %d, Residents: %d\n",
				room.roomNumber, room.floor, room.numOfResidents);
		}

		fprintf(file, "\nTo-Do List:\n");
		for (int i = 0; i < current->hotelStaffManager.todoList; i++) {
			fprintf(file, "%d) %s\n", i + 1, *current->hotelStaffManager.todoList->tasks);
		}

		fprintf(file, "\n--------------------\n\n");
		current = current->next;
	}

	if (fclose(file) == EOF) {
		perror("Error closing file");
		return;
	}

	printf("Hotel information has been exported to '%s'.\n", filename);

}

void exportFileToBinary()
{
	const char* filename = "hotel_export.bin";

	FILE* file = fopen(filename, "wb");
	if (file == NULL) {
		perror("Error opening file for writing");
		return;
	}


	int numHotels = hotelManTmp.numOfHotels;
	fwrite(&numHotels, sizeof(int), 1, file);

	Hotel* current = hotelManTmp.head;
	while (current != NULL) {

		fwrite(&current->hotelID, sizeof(int), 1, file);
		fwrite(current->hotelName, sizeof(char), LENGTH, file);
		fwrite(current->address, sizeof(char), LENGTH, file);
		fwrite(current->propertyDetails, sizeof(char), LENGTH, file);

		fwrite(&current->manager, sizeof(Manager), 1, file);

		fwrite(&current->hotelStaffManager.numOfStaff, sizeof(int), 1, file);
		for (int i = 0; i < current->hotelStaffManager.numOfStaff; i++) {
			fwrite(&current->hotelStaffManager.staffArr[i], sizeof(Staff), 1, file);
		}

		fwrite(&current->hotelRoomManager.numOfRooms, sizeof(int), 1, file);
		for (int i = 0; i < current->hotelRoomManager.numOfRooms; i++) {
			fwrite(&current->hotelRoomManager.roomArr[i], sizeof(Room), 1, file);
		}

		fwrite(&current->hotelStaffManager.todoList->size, sizeof(int), 1, file);
		for (int i = 0; i < current->hotelStaffManager.todoList->size; i++) {
			int len = strlen(current->hotelStaffManager.todoList->tasks[i]) + 1;
			fwrite(&len, sizeof(int), 1, file);
			fwrite(current->hotelStaffManager.todoList->tasks[i], sizeof(char), len, file);
		}

		current = current->next;
	}

	if (fclose(file) == EOF) {
		perror("Error closing file");
		return;
	}

	printf("Hotel information has been exported to '%s'.\n", filename);
}

void importFromTextFile(const char* filename) {
	FILE* file = fopen(filename, "r");
	if (file == NULL) {
		perror("Error opening file for reading");
		return;
	}

	char line[LENGTH];
	Hotel* currentHotel = NULL;
	int inStaffSection = 0;
	int inRoomSection = 0;
	int inToDoSection = 0;

	while (fgets(line, sizeof(line), file)) {
		line[strcspn(line, "\n")] = 0; // Remove newline

		if (strstr(line, "--- Hotel Details ---")) {
			currentHotel = (Hotel*)malloc(sizeof(Hotel));
			if (currentHotel == NULL) {
				perror("Memory allocation failed");
				fclose(file);
				return;
			}
			memset(currentHotel, 0, sizeof(Hotel));
			currentHotel->hotelStaffManager.staffArr = NULL;
			currentHotel->hotelStaffManager.numOfStaff = 0;
			currentHotel->hotelStaffManager.todoList = (ToDoList*)malloc(sizeof(ToDoList));
			if (currentHotel->hotelStaffManager.todoList == NULL) {
				perror("Memory allocation failed for ToDoList");
				free(currentHotel);
				fclose(file);
				return;
			}
			currentHotel->hotelStaffManager.todoList->tasks = NULL;
			currentHotel->hotelStaffManager.todoList->size = 0;
			currentHotel->hotelStaffManager.todoList->capacity = 0;
			currentHotel->hotelRoomManager.roomArr = NULL;
			currentHotel->hotelRoomManager.numOfRooms = 0;
		}
		else if (currentHotel != NULL) {
			if (sscanf(line, "Hotel ID: %d", &currentHotel->hotelID) == 1) {
				// Hotel ID already parsed
			}
			else if (sscanf(line, "Hotel Name: %[^\n]", currentHotel->hotelName) == 1) {
				// Hotel Name already parsed
			}
			else if (sscanf(line, "Address: %[^\n]", currentHotel->address) == 1) {
				// Address already parsed
			}
			else if (sscanf(line, "Property Details: %[^\n]", currentHotel->propertyDetails) == 1) {
				// Property Details already parsed
			}
			else if (sscanf(line, "Name: %[^\n]", currentHotel->manager.name) == 1) {
				// Manager Name already parsed
			}
			else if (sscanf(line, "Phone: %d", &currentHotel->manager.phoneNum) == 1) {
				// Manager Phone already parsed
			}
			else if (strstr(line, "Staff Details:")) {
				inStaffSection = 1;
				inRoomSection = 0;
				inToDoSection = 0;
			}
			else if (strstr(line, "Room Details:")) {
				inStaffSection = 0;
				inRoomSection = 1;
				inToDoSection = 0;
			}
			else if (strstr(line, "To-Do List:")) {
				inStaffSection = 0;
				inRoomSection = 0;
				inToDoSection = 1;
			}
			else if (inStaffSection && strstr(line, "Staff ID:")) {
				Staff staff;
				sscanf(line, "Staff ID: %d, Name: %[^,], Role: %d",
					&staff.staffID, staff.name, &staff.role);
				addStaff(&currentHotel->hotelStaffManager, staff);
			}
			else if (inRoomSection && strstr(line, "Room Number:")) {
				Room room;
				sscanf(line, "Room Number: %d, Floor: %d, Residents: %d",
					&room.roomNumber, &room.floor, &room.numOfResidents);
				room.roomCapacity = ROOMCAPACITY;
				addRoom(&currentHotel->hotelRoomManager, room);
			}
			else if (inToDoSection && sscanf(line, "%*d) %[^\n]", line) == 1) {
				if (addToDoList(currentHotel->hotelStaffManager.todoList, line) == -1) {
					perror("Failed to add task to to-do list");
					continue;
				}
			}
			else if (strstr(line, "--------------------")) {
				addHotel(&hotelManTmp, currentHotel, currentHotel->propertyDetails);
				currentHotel = NULL;
				inStaffSection = 0;
				inRoomSection = 0;
				inToDoSection = 0;
			}
		}
	}

	fclose(file);
	printf("Data imported from text file successfully.\n");
}

void importFromBinaryFile(const char* filename) {
	FILE* file = fopen(filename, "rb");
	if (file == NULL) {
		perror("Error opening file for reading");
		return;
	}

	int numHotels;
	fread(&numHotels, sizeof(int), 1, file);

	for (int i = 0; i < numHotels; i++) {
		Hotel* hotel = (Hotel*)malloc(sizeof(Hotel));
		if (hotel == NULL) {
			perror("Memory allocation failed for Hotel");
			fclose(file);
			return;
		}

		// Read basic hotel information
		fread(&hotel->hotelID, sizeof(int), 1, file);
		fread(hotel->hotelName, sizeof(char), LENGTH, file);
		fread(hotel->address, sizeof(char), LENGTH, file);
		fread(hotel->propertyDetails, sizeof(char), LENGTH, file);

		// Read manager information
		fread(&hotel->manager, sizeof(Manager), 1, file);

		// Read staff information
		fread(&hotel->hotelStaffManager.numOfStaff, sizeof(int), 1, file);
		hotel->hotelStaffManager.staffArr = (Staff*)malloc(hotel->hotelStaffManager.numOfStaff * sizeof(Staff));
		if (hotel->hotelStaffManager.staffArr == NULL) {
			perror("Memory allocation failed for Staff array");
			free(hotel);
			fclose(file);
			return;
		}
		fread(hotel->hotelStaffManager.staffArr, sizeof(Staff), hotel->hotelStaffManager.numOfStaff, file);

		// Read room information
		fread(&hotel->hotelRoomManager.numOfRooms, sizeof(int), 1, file);
		hotel->hotelRoomManager.roomArr = (Room*)malloc(hotel->hotelRoomManager.numOfRooms * sizeof(Room));
		if (hotel->hotelRoomManager.roomArr == NULL) {
			perror("Memory allocation failed for Room array");
			free(hotel->hotelStaffManager.staffArr);
			free(hotel);
			fclose(file);
			return;
		}
		fread(hotel->hotelRoomManager.roomArr, sizeof(Room), hotel->hotelRoomManager.numOfRooms, file);

		// Read ToDoList information
		hotel->hotelStaffManager.todoList = (ToDoList*)malloc(sizeof(ToDoList));
		if (hotel->hotelStaffManager.todoList == NULL) {
			perror("Memory allocation failed for ToDoList");
			free(hotel->hotelRoomManager.roomArr);
			free(hotel->hotelStaffManager.staffArr);
			free(hotel);
			fclose(file);
			return;
		}

		fread(&hotel->hotelStaffManager.todoList->size, sizeof(int), 1, file);
		hotel->hotelStaffManager.todoList->capacity = hotel->hotelStaffManager.todoList->size;
		hotel->hotelStaffManager.todoList->tasks = (char**)malloc(hotel->hotelStaffManager.todoList->size * sizeof(char*));
		if (hotel->hotelStaffManager.todoList->tasks == NULL) {
			perror("Memory allocation failed for ToDoList tasks");
			free(hotel->hotelStaffManager.todoList);
			free(hotel->hotelRoomManager.roomArr);
			free(hotel->hotelStaffManager.staffArr);
			free(hotel);
			fclose(file);
			return;
		}

		for (int j = 0; j < hotel->hotelStaffManager.todoList->size; j++) {
			int len;
			fread(&len, sizeof(int), 1, file);
			hotel->hotelStaffManager.todoList->tasks[j] = (char*)malloc(len * sizeof(char));
			if (hotel->hotelStaffManager.todoList->tasks[j] == NULL) {
				perror("Memory allocation failed for ToDoList task");
				// Free previously allocated tasks
				for (int k = 0; k < j; k++) {
					free(hotel->hotelStaffManager.todoList->tasks[k]);
				}
				free(hotel->hotelStaffManager.todoList->tasks);
				free(hotel->hotelStaffManager.todoList);
				free(hotel->hotelRoomManager.roomArr);
				free(hotel->hotelStaffManager.staffArr);
				free(hotel);
				fclose(file);
				return;
			}
			fread(hotel->hotelStaffManager.todoList->tasks[j], sizeof(char), len, file);
		}

		addHotel(&hotelManTmp, hotel, hotel->propertyDetails);
	}

	fclose(file);
	printf("Data imported from binary file successfully.\n");
}

void printHotelElement(const void* element) {
	const Hotel* hotel = (const Hotel*)element;
	printHotelDetails((Hotel*)hotel);
}

void generalArrayFunction(void* array, int numElements, size_t elementSize, void (*f)(const void* element)) {
	char* ptr = (char*)array;

	for (int i = 0; i < numElements; i++) {
		f((const void*)ptr);
		ptr += elementSize;
	}
}

void initializeStaffManager(Hotel* hotel)
{
	// Initialize staff array
	hotel->hotelStaffManager.staffArr = NULL;
	hotel->hotelStaffManager.numOfStaff = 0;
	hotel->hotelStaffManager.staffCapacity = 0;

	// Initialize ToDoList
	hotel->hotelStaffManager.todoList = (ToDoList*)malloc(sizeof(ToDoList));
	if (hotel->hotelStaffManager.todoList != NULL) {
		hotel->hotelStaffManager.todoList->tasks = (char**)malloc(INITIAL_TODO_CAPACITY * sizeof(char*));
		if (hotel->hotelStaffManager.todoList->tasks != NULL) {
			hotel->hotelStaffManager.todoList->size = 0;
			hotel->hotelStaffManager.todoList->capacity = INITIAL_TODO_CAPACITY;
		}
		else {
			fprintf(stderr, "Failed to allocate memory for ToDoList tasks\n");
			free(hotel->hotelStaffManager.todoList);
			hotel->hotelStaffManager.todoList = NULL;
		}
	}
	else {
		fprintf(stderr, "Failed to allocate memory for ToDoList\n");
	}
}