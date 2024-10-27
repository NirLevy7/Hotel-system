#include "hotel.h"
#include <stdlib.h>


//Checks if the hotel ID is valid, returns 1 if true, 0 otherwise.
int validHotel(HotelManager* hotelMan, int hotelID) {

	if (hotelID < 100000 || hotelID > 999999) {
		return 0;
	}


	Hotel* current = hotelMan->head;
	while (current != NULL) {
		if (current->hotelID == hotelID) {
			return 0;
		}
		current = current->next;
	}

	return 1;
}

//Returns pointer to the hotel found by ID (int), otherwise NULL.
Hotel* returnHotelByID(HotelManager* hotelMan, int hotelID) {
	if (hotelMan == NULL || hotelMan->head == NULL) {
		printf("\nError!\nNo hotel found!\n");
		return NULL;
	}

	Hotel* current = hotelMan->head;
	while (current != NULL) {
		if (current->hotelID == hotelID) {
			return current;
		}
		current = current->next;
	}
	printf("\nError!\n No hotel found!\n");
	return NULL;
}
//Returns 1 if the hotel was found, else 0.
int findHotelByID(HotelManager* hotelMan, int hotelID) {
	if (hotelMan == NULL || hotelMan->head == NULL) {
		return 0;  // Hotel manager is empty or NULL
	}

	Hotel* current = hotelMan->head;
	while (current != NULL) {
		if (current->hotelID == hotelID) {
			return 1;
		}
		current = current->next;
	}

	return 0;  // Hotel not found
}


//Adds a hotel to a hotel linked list, returns 0 if unsuccessful.
int addHotel(HotelManager* hotelMan, Hotel* hotel, void* propertyDetails) {
	if (!validHotel(hotelMan, hotel->hotelID) || findHotelByID(hotelMan, hotel->hotelID) == 1) {
		return 0;
	}

	Hotel* newHotel = (Hotel*)malloc(sizeof(Hotel));
	if (newHotel == NULL) {
		return 0;
	}

	*newHotel = *hotel;
	*newHotel->propertyDetails = propertyDetails;
	newHotel->next = NULL;
	newHotel->previous = NULL;

	if (hotelMan->head == NULL) {
		hotelMan->head = newHotel;
		hotelMan->tail = newHotel;
	}
	else {
		hotelMan->tail->next = newHotel;
		newHotel->previous = hotelMan->tail;
		hotelMan->tail = newHotel;
	}

	hotelMan->numOfHotels++;
	newHotel->hotelRoomManager.sort = notSorted;
	return 1;
}


//Removes the hotel after finding it by ID returns 1 if true, otherwise 0.
int removeHotel(HotelManager* hotelMan, int hotelID) {
	if (hotelMan == NULL || hotelMan->head == NULL) {
		return 0;
	}

	Hotel* current = hotelMan->head;

	while (current != NULL && current->hotelID != hotelID) {
		current = current->next;
	}

	if (current == NULL) {
		return 0;  // Hotel not found
	}

	if (current->previous != NULL) {
		current->previous->next = current->next;
	}
	else {
		hotelMan->head = current->next;
	}

	if (current->next != NULL) {
		current->next->previous = current->previous;
	}
	else {
		hotelMan->tail = current->previous;
	}


	hotelMan->numOfHotels--;
	return 1;
}


//Prints all the hotel's details in the linked list returns 1 if successful, otherwise 0.
int printAllHotelDetails(HotelManager* hotelMan) {
	if (hotelMan == NULL || hotelMan->head == NULL) {
		printf("No hotels available.\n");
		return 0;
	}

	Hotel* current = hotelMan->head;
	int hotelCount = 0;

	while (current != NULL) {
		hotelCount++;
		printf("\n--- Hotel %d Details ---\n", hotelCount);
		printf("Hotel ID: %d\n", current->hotelID);
		printf("Hotel Name: %s\n", current->hotelName);
		printf("Address: %s\n", current->address);

		// Print manager details
		printf("Manager Name: %s\n", *current->manager.name);
		printf("Manager Phone: %d\n", current->manager.phoneNum);

		printf("Property Details: ");
		if (strlen(current->propertyDetails) > 0) {
			printf("%s\n", (char*)*current->propertyDetails);
		}

		// Print room details
		printf("\nRoom Details:\n");
		if (current->hotelRoomManager.roomArr != NULL) {
			printf("Total Rooms: %d\n", current->hotelRoomManager.numOfRooms);
			printf("Available Rooms: %d\n", getNumOfAvailableRooms(&current->hotelRoomManager));
			printf("Room Details:\n");
			printAllRoomsDetails(&current->hotelRoomManager);
		}
		else {
			printf("No room information available.\n");
		}

		// Print staff details
		printf("\nStaff Details:\n");
		if (current->hotelStaffManager.staffArr != NULL) {
			printf("Total Staff: %d\n", current->hotelStaffManager.numOfStaff);
			printAllStaffDetails(&current->hotelStaffManager);
		}
		else {
			printf("No staff information available.\n");
		}

		// Print ToDo list
		printf("\nTo-Do List:\n");
		if (current->hotelStaffManager.todoList != NULL) {
			printToDoList(current->hotelStaffManager.todoList);
		}
		else {
			printf("No to-do list available.\n");
		}

		printf("\n--- End of Hotel %d Details ---\n", hotelCount);

		current = current->next;
	}

	printf("\nTotal number of hotels: %d\n", hotelMan->numOfHotels);
	return 1;
}




//Prints a hotel's details, returns 1 if true otherwise 0.
int printHotelDetails(Hotel* hotel)
{
	if (hotel == NULL) {
		printf("Invalid hotel.\n");
		return 0;
	}

	printf("Hotel ID: %d\n", hotel->hotelID);
	printf("Hotel Name: %s\n", hotel->hotelName);
	printf("Address: %s\n", hotel->address);

	// Print manager details
	printf("Manager Name: %s\n", *hotel->manager.name);
	printf("Manager Phone: %d\n", hotel->manager.phoneNum);

	printf("Property Details: %s\n", (char*)*hotel->propertyDetails);

	// Print room details
	printf("\nRoom Details:\n");
	if (hotel->hotelRoomManager.roomArr != NULL) {
		printf("Total Rooms: %d\n", hotel->hotelRoomManager.numOfRooms);
		printf("Available Rooms: %d\n", getNumOfAvailableRooms(&hotel->hotelRoomManager));
		printf("Room Details:\n");
		printAllRoomsDetails(&hotel->hotelRoomManager);
	}
	else {
		printf("No room information available.\n");
	}

	// Print staff details
	printf("\nStaff Details:\n");
	if (hotel->hotelStaffManager.staffArr != NULL) {
		printf("Total Staff: %d\n", hotel->hotelStaffManager.numOfStaff);
		printAllStaffDetails(&hotel->hotelStaffManager);
	}
	else {
		printf("No staff information available.\n");
	}

	// Print ToDo list
	printf("\nTo-Do List:\n");
	if (hotel->hotelStaffManager.todoList != NULL) {
		printToDoList(hotel->hotelStaffManager.todoList);
	}
	else {
		printf("No to-do list available.\n");
	}

	printf("\n");
	return 1;
}