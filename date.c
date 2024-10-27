#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include "date.h"
#include "hotel.h"


//Validates a given date, ensuring it's after 2024 and follows correct calendar rules for days in each month.
int ValidDate(Date* pDate)
{
	if (pDate->year < 2024) //Checks that the input year is after 2024
	{
		return 0;
	}
	if (pDate->month < 1 || pDate->month > 12 || pDate->day < 1 || pDate->day > 31) //This next few 'if' conditions filter any non existent day-month cycles (IE:there is no 29/02)
	{
		return 0;
	}
	if (pDate->month == 2)
	{
		if (pDate->day < 1 || pDate->day > 28)
		{
			return 0;
		}
	}
	if (pDate->month == 4 || pDate->month == 6 || pDate->month == 9 || pDate->month == 11)
	{
		if (pDate->day < 1 || pDate->day > 30)
		{
			return 0;
		}
	}
	return 1;
}

//converts the inputted dd^^mm^^yyyy to the actual stored date
void convertToDate(char date[LENGTH], Date* pDate)
{
	char* token;
	char delim[] = "^^";

	token = strtok(date, delim);
	if (token == NULL)
		return;
	pDate->day = atoi(token);

	token = strtok(NULL, delim);
	if (token == NULL)
		return;
	pDate->month = atoi(token);

	token = strtok(NULL, delim);
	if (token == NULL)
		return;
	pDate->year = atoi(token);
}

//checks that the expiration date is AFTER the production date
int checkDepartureDateAfterArrivalDate(Date* arrivalDate, Date* departureDate)
{
	if (departureDate->year > arrivalDate->year)
	{
		return 1;
	}
	else if (departureDate->year == arrivalDate->year)
	{
		if (departureDate->month > arrivalDate->month)
		{
			return 1;
		}
		else if (departureDate->month == arrivalDate->month)
		{
			if (departureDate->day > arrivalDate->day)
			{
				return 1;
			}
		}
	}
	return 0;
}

