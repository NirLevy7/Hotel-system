#ifndef __HOTEL_H
#define __HOTEL_H
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "manager.h"
#include "staff.h"
#include "room.h"
#define LENGTH 254

typedef struct Hotel
{
	int hotelID;
	char hotelName[LENGTH];
	char address[LENGTH];
	struct Hotel* next;
	struct Hotel* previous;
	struct Manager manager;
	void* propertyDetails[LENGTH];
	struct StaffManager hotelStaffManager;
	struct RoomManager hotelRoomManager;


} Hotel;

typedef struct HotelManager
{
	struct Hotel* head;
	struct Hotel* tail;
	int numOfHotels;

} HotelManager;

int printHotelDetails(Hotel* hotel);
int printAllHotelDetails(HotelManager* hotelMan);
int findHotelByID(HotelManager* hotelMan, int hotelID);
Hotel* returnHotelByID(HotelManager* hotelMan, int hotelID);
int addHotel(HotelManager* hotelMan, Hotel* hotel, void* propertyDetails);
int removeHotel(HotelManager* hotelMan, int hotelID);
int validHotel(HotelManager* hotelMan, int hotelID);
void initializeStaffManager(Hotel* hotel);

#endif // __HOTEL_H_