#include "room.h"


//empties the input room of residents by the chosen amount, returns 1 if successful, 0 otherwise.
int emptyRoom(RoomManager* roomMan, Room room, int numOfResidents)
{
	if (roomMan->numOfRooms == 0)
	{
		printf("Unable to remove residents\n");
		return 0;
	}

	for (int i = 0; i < roomMan->numOfRooms; i++)
	{
		if (roomMan->roomArr[i].roomNumber == room.roomNumber)
		{
			if (roomMan->roomArr[i].numOfResidents - numOfResidents >= 0)
			{
				roomMan->roomArr[i].numOfResidents -= numOfResidents;
				return 1;
			}

			printf("The number of residents you're requesting to remove from this room exceeds the amount of residents are actually in this room");
			return 0;
		}
	}
}
//Fills the room by the chosen amount with residents, returns 1 if successful, 0 otherwise.
int fillRoom(RoomManager* roomMan, Room room, int numOfResidents)
{
	if (roomMan->numOfRooms == 0)
	{
		return 0;
	}

	for (int i = 0; i < roomMan->numOfRooms; i++)
	{
		if (roomMan->roomArr[i].roomNumber == room.roomNumber)
		{
			if (roomMan->roomArr[i].numOfResidents += numOfResidents <= ROOMCAPACITY)
			{
				roomMan->roomArr[i].numOfResidents += numOfResidents;
				return 1;
			}
			printf("This room cannot fill that many residents");
			return 0;
		}
	}
}


//Adds a room to the room manager which is an array of rooms, returns 1 if successful, otherwise 0.
int addRoom(RoomManager* roomMan, Room room)
{

	if (isRoomNumberExists(roomMan, room.roomNumber) == 1)
	{
		printf("Room Number already exists!");
		return 0;
	}

	if (!roomMan || room.roomNumber <= 0 || room.floor < 0 || room.floor > 2 || room.numOfResidents < 0 || room.numOfResidents > ROOMCAPACITY)
	{
		return 0;
	}

	if (!roomMemoryAllocation(roomMan, 1))
	{
		return 0;
	}

	roomMan->roomArr[roomMan->numOfRooms - 1] = room;
	return 1;
}


//Removes a room from the room manager which is an array of rooms, returns 1 if successful, 0 otherwise.
int removeRoom(RoomManager* roomMan, Room room)
{
	if (!roomMan || room.roomNumber < 0 || room.floor < 0 || room.floor > 2)
	{
		printf("Unable to remove room\n");
		return 0;
	}

	for (int i = 0; i < roomMan->numOfRooms; i++)
	{
		if (roomMan->roomArr[i].roomNumber == room.roomNumber && room.floor == roomMan->roomArr[i].floor)
		{

			if (i < roomMan->numOfRooms - 1) {
				roomMan->roomArr[i] = roomMan->roomArr[roomMan->numOfRooms - 1];
			}

			if (!roomMemoryAllocation(roomMan, -1))
			{
				printf("Memory reallocation failed\n");
				return 0;
			}

			printf("Successfully removed room\n");
			return 1;
		}
	}

	printf("Unable to remove room\n");
	return 0;
}



//Method designed with handling memory allocation, can be input with negative or positive number to either remove or add a room respectively, returns 1 if successful, 0 otherwise.
int roomMemoryAllocation(RoomManager* roomMan, int n)
{
	if (!roomMan || (int)roomMan->numOfRooms + n < 0)
	{
		return 0; // Invalid input or would result in negative room count
	}

	int newSize = roomMan->numOfRooms + n;


	if (newSize == 0) {
		free(roomMan->roomArr);
		roomMan->roomArr = NULL;
		roomMan->capacity = 0;
		roomMan->numOfRooms = 0;
		return 1;
	}


	Room* newRoomArr = realloc(roomMan->roomArr, newSize * sizeof(Room));
	if (!newRoomArr && newSize > 0)
	{
		return 0;
	}

	roomMan->roomArr = newRoomArr;
	roomMan->capacity = newSize;
	roomMan->numOfRooms = newSize;

	return 1;
}


//Prints the room's details, returns 1 if successful, 0 otherwise.
int printAllRoomsDetails(RoomManager* roomMan) {
	if (roomMan == NULL || roomMan->roomArr == NULL) {
		printf("Invalid RoomManager or room array.\n");
		return 0;
	}

	printf("All Room Details:\n");
	printf("--------------------\n");
	for (int i = 0; i < roomMan->numOfRooms; i++) {
		PRINT_ROOM_DETAILS(&roomMan->roomArr[i]);
	}
	printf("--------------------\n");

	return 1;
}


//Prints the available rooms, rooms that aren't occupied at all, returns 1 if successful, 0 otherwise.
int printAvailableRooms(RoomManager* roomMan)
{

	for (int i = 0; i < roomMan->numOfRooms; i++)
	{
		if (roomMan->roomArr[i].numOfResidents == 0)
		{
			printf("%d\n", roomMan->roomArr[i].roomNumber);

		}
	}

	return 1;
}


//Returns the number of rooms that are available.
int getNumOfAvailableRooms(RoomManager* roomMan)
{
	int count = 0;

	for (int i = 0; i < roomMan->numOfRooms; i++)
	{
		if (roomMan->roomArr[i].numOfResidents == 0)
		{
			count++;
		}
	}

	return count;
}

//Returns a pointer to the room by floor nad room number if successful, returns NULL otherwise.
Room* returnRoom(RoomManager* roomMan, int roomNumber, int floor) {
	if (!roomMan || roomNumber < 0 || floor < 0 || floor > 2) {
		return NULL;
	}

	for (int i = 0; i < roomMan->numOfRooms; i++) {
		if (roomMan->roomArr[i].roomNumber == roomNumber && roomMan->roomArr[i].floor == floor) {
			return &roomMan->roomArr[i];
		}
	}

	return NULL;
}

//Compare two rooms room numbers which will allow the sorting method to sort by room number.
int compareRoomNumber(const void* a, const void* b) {
	return ((Room*)a)->roomNumber - ((Room*)b)->roomNumber;
}

//Compare two rooms floors which will allow the sorting method to sort by floors.
int compareFloorNumber(const void* a, const void* b) {
	return ((Room*)a)->floor - ((Room*)b)->floor;
}

//Compare two rooms by amount of residents which will allow the sorting method to sort by the least full rooms to most.
int compareNumResidents(const void* a, const void* b) {
	return ((Room*)a)->numOfResidents - ((Room*)b)->numOfResidents;
}


//Performs a binary search for a room in a sorted RoomManager array based on the specified search method (room number, floor number, or number of residents) and search key.
void handleRoomSearch(RoomManager* roomManager, int searchMethod, int searchKey, Room** result)
{
	if (roomManager == NULL || roomManager->numOfRooms == 0 || roomManager->sort == notSorted) {
		*result = NULL;
		return;
	}

	if (roomManager->sort != (searchMethod - 1)) {
		*result = NULL;
		return;
	}

	switch (searchMethod) {
	case 1:
		*result = bsearch(&searchKey, roomManager->roomArr, roomManager->numOfRooms, sizeof(Room), compareRoomNumber);
		break;
	case 2:
		*result = bsearch(&searchKey, roomManager->roomArr, roomManager->numOfRooms, sizeof(Room), compareFloorNumber);
		break;
	case 3:
		*result = bsearch(&searchKey, roomManager->roomArr, roomManager->numOfRooms, sizeof(Room), compareNumResidents);
		break;
	default:
		*result = NULL;
	}
}

//Checks if the room exists by room number, returns 0 otherwise.
int isRoomNumberExists(RoomManager* roomMan, int roomNumber)
{
	if (roomMan == NULL || roomMan->roomArr == NULL || roomMan->numOfRooms == 0)
	{
		return 0;
	}

	for (int i = 0; i < roomMan->numOfRooms; i++)
	{
		if (roomMan->roomArr[i].roomNumber == roomNumber)
		{
			return 1;
		}
	}

	return 0;
}
