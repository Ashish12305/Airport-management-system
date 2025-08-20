#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


void getCurrentDate(char *dateStr){
	time_t t= time(NULL);
	struct tm tm = *localtime(&t);
	sprintf(dateStr, "%02d-%02d-%04d", tm.tm_mday, tm.tm_mon+ 1, tm.tm_year +1900);
}

#define MAX 100

// Structures
typedef struct {
    int flightNumber;
    char from[50];
    char to[50];
    char departureTime[20];
    char arrivalTime[20];
    int seatsAvailable;
} Flight;


typedef struct {
	char name[50];
    int  age;
    char gender[10];
    char dob[15];
    char aadhaar[20];
    char address[100];
    char mobile[15];
    char gmail[50];
    char passport[20];
    int flightNumber;
} Passenger;

typedef struct {
    char passportNumber[20];
    int flightNumber;
    char bookingDate[20];
} Booking;

// Global arrays
Flight flights[MAX];
Passenger passengers[MAX];
Booking bookings[MAX];
int flightCount = 0, passengerCount = 0, bookingCount = 0;

// Admin credentials
const char adminUser[] = "admin";
const char adminPass[] = "1234";

// Function declarations
void adminLogin();
void flightMenu();
void passengerMenu();
void bookingMenu();
void generateReports();

// Flight functions
void addFlight();
void updateFlight();
void deleteFlight();
void viewFlights();

// Passenger functions
void addPassenger();
void updatePassenger();
void deletePassenger();
void searchPassenger();

// Booking functions
void bookTicket();
void cancelBooking();
void viewBookings();

int main() {
    int choice;
    adminLogin();

    while (1) {
        printf("\n****************** Welcome to Airport Management System ********************\n");
        printf("\n============================================================================\n");
        printf("1. Flight Management\n");
        printf("2. Passenger Management\n");
        printf("3. Booking Management\n");
        printf("4. Administrative Reports\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1: flightMenu(); break;
            case 2: passengerMenu(); break;
            case 3: bookingMenu(); break;
            case 4: generateReports(); break;
            case 5: exit(0);
            default: printf("Invalid choice!\n");
        }
    }
    return 0;
}

// Admin login
void adminLogin() {
    char user[20], pass[20];
    printf("Admin Login\nUsername: ");
    scanf("%s", user);
    printf("Password: ");
    scanf("%s", pass);
    if (strcmp(user, adminUser) != 0 || strcmp(pass, adminPass) != 0) {
        printf("Access Denied!\n");
        exit(0);
    }
}

// Flight Management
void flightMenu() {
    int choice;
    printf("\n--- Flight Management ---\n");
    printf("1. Add Flight\n2. Update Flight\n3. Delete Flight\n4. View Flights\nEnter choice: ");
    scanf("%d", &choice);
    switch (choice) {
        case 1: addFlight(); break;
        case 2: updateFlight(); break;
        case 3: deleteFlight(); break;
        case 4: viewFlights(); break;
        default: printf("Invalid choice!\n");
    }
}

void addFlight() {
    printf("Enter flight number: ");
    scanf("%d", &flights[flightCount].flightNumber);
    printf("from: ");
    scanf("%s", flights[flightCount].from);
    printf("to:");
    scanf("%s", flights[flightCount].to);
    printf("Departure Time: ");
    scanf("%s", flights[flightCount].departureTime);
    printf("Arrival Time: ");
    scanf("%s", flights[flightCount].arrivalTime);
    printf("Seats Available: ");
    scanf("%d", &flights[flightCount].seatsAvailable);
    flightCount++;
    printf("Flight added successfully!\n");
}

void updateFlight() {
    int num, i, found = 0;
    printf("Enter flight number to update: ");
    scanf("%d", &num);
    for (i = 0; i < flightCount; i++) {
        if (flights[i].flightNumber == num) {
            printf("New from: ");
            scanf("%s", flights[i].from);
             printf("New to: ");
            scanf("%s", flights[i].to);
            printf("New Departure Time: ");
            scanf("%s", flights[i].departureTime);
            printf("New Arrival Time: ");
            scanf("%s", flights[i].arrivalTime);
            printf("New Seats Available: ");
            scanf("%d", &flights[i].seatsAvailable);
            found = 1;
            printf("Flight updated!\n");
            break;
        }
    }
    if (!found) printf("Flight not found!\n");
}

void deleteFlight() {
    int num, i, j;
    printf("Enter flight number to delete: ");
    scanf("%d", &num);
    for (i = 0; i < flightCount; i++) {
        if (flights[i].flightNumber == num) {
            for (j = i; j < flightCount - 1; j++)
                flights[j] = flights[j + 1];
            flightCount--;
            printf("Flight deleted!\n");
            return;
        }
    }
    printf("Flight not found!\n");
}

void viewFlights() {
    printf("\n================================================================================================================\n");
    printf("                                               ??  Available Flights\n");
    printf("================================================================================================================\n");

    if (flightCount == 0) {
        printf("??  No flights available at the moment.\n");
        return;
    }

    printf("%-12s %-20s %-20s %-20s %-20s %-10s\n", 
           "Flight No", "From", "To", "Departure Time", "Arrival Time", "Seats");
    printf("----------------------------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < flightCount; i++) {
        printf("%-12d %-20s %-20s %-20s %-20s %-10d\n",
               flights[i].flightNumber,
               flights[i].from,
               flights[i].to,
               flights[i].departureTime,
               flights[i].arrivalTime,
               flights[i].seatsAvailable);
    }

    printf("================================================================================================================\n");
}


// Passenger Management
void passengerMenu() {
    int choice; 
    printf("\n--- Passenger Management ---\n");
    printf("1. Add Passenger\n2. Update Passenger\n3. Delete Passenger\n4. Search Passenger\nEnter choice: ");
    scanf("%d", &choice);
    switch (choice) {
        case 1: addPassenger(); break;
        case 2: updatePassenger(); break;
        case 3: deletePassenger(); break;
        case 4: searchPassenger(); break;
        default: printf("Invalid choice!\n");
    }
}

void addPassenger() {
    if (passengerCount >= MAX) {
        printf("? Cannot add more passengers. Limit reached.\n");
        return;
    }

    printf("\n====================================\n");
    printf("        ?? Add New Passenger\n");
    printf("====================================\n");

    printf("Name               : ");
    scanf(" %[^\n]", passengers[passengerCount].name);

    printf("Age                : ");
    scanf("%d", &passengers[passengerCount].age);

    printf("Gender             : ");
    scanf("%s", passengers[passengerCount].gender);

    printf("Aadhaar Number     : ");
    scanf("%s", passengers[passengerCount].aadhaar);

    printf("Passport Number    : ");
    scanf("%s", passengers[passengerCount].passport);  // ??

    printf("Permanent Address  : ");
    scanf(" %[^\n]", passengers[passengerCount].address);

    printf("Mobile Number      : ");
    scanf("%s", passengers[passengerCount].mobile);

    printf("Gmail              : ");
    scanf("%s", passengers[passengerCount].gmail);

    printf("Date of Birth (DD-MM-YYYY): ");
    scanf("%s", passengers[passengerCount].dob);

    passengerCount++;
    printf("? Passenger added successfully!\n", passengers[passengerCount - 1].flightNumber);
}

void updatePassenger() {
    char passport[20];
    int i, found = 0;
    printf("Enter passport number to update: ");
    scanf("%s", passport);
    for (i = 0; i < passengerCount; i++) {
        if (strcmp(passengers[i].passport, passport) == 0) {
            printf("New Name: ");
            scanf("%s", passengers[i].name);
            printf("New Age: ");
            scanf("%d", &passengers[i].age);
            printf("New Gender: ");
            scanf("%s", passengers[i].gender);
            found = 1;
            printf("Passenger updated!\n");
            break;
        }
    }
    if (!found) printf("Passenger not found!\n");
}

void deletePassenger() {
    char passport[20];
    int i, j;
    printf("Enter passport number to delete: ");
    scanf("%s", passport);
    for (i = 0; i < passengerCount; i++) {
        if (strcmp(passengers[i].passport, passport) == 0) {
            for (j = i; j < passengerCount - 1; j++)
                passengers[j] = passengers[j + 1];
            passengerCount--;
            printf("Passenger deleted!\n");
            return;
        }
    }
    printf("Passenger not found!\n");
}

void searchPassenger() {
    char passport[20];
    int i;
    printf("Enter passport number to search: ");
    scanf("%s", passport);
    for (i = 0; i < passengerCount; i++) {
        if (strcmp(passengers[i].passport, passport) == 0) {
            printf("Name: %s | Age: %d | Gender: %s\n",
                   passengers[i].name, passengers[i].age, passengers[i].gender);
            return;
        }
    }
    printf("Passenger not found!\n");
}

// Booking Management
void bookingMenu() {
    int choice;
    printf("\n--- Booking Management ---\n");
    printf("1. Book Ticket\n2. Cancel Booking\n3. View Bookings\nEnter choice: ");
    scanf("%d", &choice);
    switch (choice) {
        case 1: bookTicket(); break;
        case 2: cancelBooking(); break;
        case 3: viewBookings(); break;
        default: printf("Invalid choice!\n");
    }
}

void bookTicket() {
    Booking b;
    printf("\nEnter Passport Number: ");
    scanf("%s", b.passportNumber);
   
    printf("Enter Flight Number: ");
    scanf("%d", &b.flightNumber);

    getCurrentDate(b.bookingDate);  // Auto-fill today's date

    // Save booking to array or file (example assumes array)
    bookings[bookingCount++] = b;

    printf("\n Booking Successful!");
    printf("\n Booking Date: %s", b.bookingDate);
    printf("\n Flight Number: %d", b.flightNumber);
    printf("\n Passport Number: %s\n", b.passportNumber);
}


void viewBookings() {
    printf("\n--- Booking History ---\n");
    if (bookingCount == 0) {
        printf("No bookings found.\n");
        return;
    }

    for (int i = 0; i < bookingCount; i++) {
        printf("Passport: %s | Flight: %d | Date: %s\n",
               bookings[i].passportNumber,
               bookings[i].flightNumber,
               bookings[i].bookingDate);
    }
}

// Booking Management - Cancel Booking
void cancelBooking() {
    char passport[20];
    int found = 0;
    printf("Enter passport number to cancel booking: ");
    scanf("%s", passport);

    for (int i = 0; i < bookingCount; i++) {
        if (strcmp(bookings[i].passportNumber, passport) == 0) {
            for (int j = i; j < bookingCount - 1; j++)
                bookings[j] = bookings[j + 1];
            bookingCount--;
            found = 1;
            printf("Booking cancelled.\n");
            break;
        }
    }

    if (!found)
        printf("Booking not found.\n");
}

// Administrative - Generate Reports
void generateReports() {
    printf("\n--- Administrative Reports ---\n");

    printf("\nFlight Schedule:\n");
    viewFlights();

    printf("\nPassenger List:\n");
    for (int i = 0; i < passengerCount; i++) {
        printf("Name: %s | Age: %d | Gender: %s | Passport: %s\n",
               passengers[i].name,
               passengers[i].age,
               passengers[i].gender,
               passengers[i].passport);
    }
}



