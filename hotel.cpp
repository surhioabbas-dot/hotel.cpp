#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Guest {
    string name;
    int roomNumber;
    int days;
    string roomType;
    float rentPerDay;
    bool isBooked;
};

Guest hotel[51];   // Rooms 100–150

// Function prototypes
void hotelDesign() {
    cout << "\n\n";
    cout << "+=============================================================+\n";
    cout << "|                     WELCOME TO BROTHER  HOTEL               |\n";
    cout << "|=============================================================|\n";
    cout << "|                      ________||________                     |\n";                   
    cout << "|                   ____|   BROTHER    |____                  |\n";
    cout << "|                    | []  []  []  []  [] |                   |\n";
    cout << "|                    | []  []  []  []  [] |                   |\n";
    cout << "|                    | []  []  []  []  [] |                   |\n";
    cout << "|                    |____________________|                   |\n";
    cout << "|=============================================================|\n";
    cout << "|                   BEST SERVICE IN THE DADU CITY             |\n";
    cout << "|                    OWNED BY GHULAM ABBAS                    |\n";
    cout << "+=============================================================+\n\n";
}

void initializeRooms();
void checkIn();
void displayBill();
void checkout();
void generateHTMLReceipt(Guest g);

	int main() {
    initializeRooms();
    hotelDesign();  
	int choice;

    while (true) {
        cout << "\n========= HOTEL MENU =========";
        cout << "\n1. Check-In";
        cout << "\n2. Show Bill";
        cout << "\n3. Check-Out";
        cout << "\n4. Exit";
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            checkIn();
            break;
        case 2:
            displayBill();
            break;
        case 3:
            checkout();
            break;
        case 4:
            cout << "\nExiting... Thank you for visiting!\n";
            return 0;
        default:
            cout << "\nInvalid choice! Try again.\n";
        }
    }
}

// ========================================================
// Initialize Rooms
// ========================================================
void initializeRooms() {
    for (int i = 100; i <= 150; i++) {
        int index = i - 100;
        hotel[index].roomNumber = i;
        hotel[index].isBooked = false;

        if (i >= 100 && i <= 120) { 
            hotel[index].roomType = "1 Bed Room";
            hotel[index].rentPerDay = 2500;
        }
        else if (i >= 121 && i <= 140) {
            hotel[index].roomType = "2 Bed Room";
            hotel[index].rentPerDay = 3500;
        }
        else {
            hotel[index].roomType = "Luxury Room";
            hotel[index].rentPerDay = 6000;
        }
    }
}

// ========================================================
// Check-In
// ========================================================
void checkIn() {
    int roomTypeChoice, room;

    cout << "\nSelect Room Type:\n";
    cout << "1. 1 Bed Room (Rs. 2500)\n";
    cout << "2. 2 Bed Room (Rs. 3500)\n";
    cout << "3. Luxury Room (Rs. 6000)\n";
    cout << "Enter option: ";
    cin >> roomTypeChoice;

    int start, end;

    if (roomTypeChoice == 1) { start = 100; end = 120; }
    else if (roomTypeChoice == 2) { start = 121; end = 140; }
    else if (roomTypeChoice == 3) { start = 141; end = 150; }
    else {
        cout << "\nInvalid type!\n";
        return;
    }

    cout << "\nAvailable Rooms:\n";
    for (int i = start; i <= end; i++) {
        if (!hotel[i - 100].isBooked)
            cout << "Room " << i << " (" << hotel[i - 100].roomType 
                 << ", Rs. " << hotel[i - 100].rentPerDay << ")\n";
    }

    cout << "\nEnter room number to book: ";
    cin >> room;

    if (room < start || room > end) {
        cout << "\nInvalid room number!\n";
        return;
    }

    int idx = room - 100;

    if (hotel[idx].isBooked) {
        cout << "\nRoom already booked!\n";
        return;
    }

    cin.ignore();
    cout << "Enter guest name: ";
    getline(cin, hotel[idx].name);

    cout << "Enter days to stay: ";
    cin >> hotel[idx].days;

    hotel[idx].isBooked = true;

    cout << "\nRoom booked successfully!\n";
}

// ========================================================
// Display Bill
// ========================================================
void displayBill() {
    int room;
    cout << "\nEnter room number: ";
    cin >> room;

    if (room < 100 || room > 150) {
        cout << "\nInvalid room number!\n";
        return;
    }

    int idx = room - 100;

    if (!hotel[idx].isBooked) {
        cout << "\nNo booking found!\n";
        return;
    }

    Guest g = hotel[idx];

    cout << "\n====== Hotel Bill ======";
    cout << "\nGuest Name: " << g.name;
    cout << "\nRoom Number: " << g.roomNumber;
    cout << "\nRoom Type: " << g.roomType;
    cout << "\nRent per day: Rs. " << g.rentPerDay;
    cout << "\nDays Stayed: " << g.days;
    cout << "\n-----------------------------";
    cout << "\nTotal Amount: Rs. " << g.rentPerDay * g.days;
    cout << "\n=============================\n";
}

// ========================================================
// Check-Out + Generate HTML Receipt
// ========================================================
void checkout() {
    int room;
    cout << "\nEnter room number for checkout: ";
    cin >> room;

    if (room < 100 || room > 150) {
        cout << "\nInvalid room number!\n";
        return;
    }

    int idx = room - 100;

    if (!hotel[idx].isBooked) {
        cout << "\nThis room is not booked!\n";
        return;
    }

    Guest g = hotel[idx];

    cout << "\nThank you, " << g.name << "! Generating your HTML receipt...\n";

    generateHTMLReceipt(g);

    hotel[idx].isBooked = false; // Clear booking
}

// ========================================================
// HTML Receipt Generator
// ========================================================
void generateHTMLReceipt(Guest g) {
    ofstream file("receipt.html");

    file << "<html><head><title>Hotel Receipt</title>";
    file << "<style>";
    file << "body{font-family:Arial;margin:50px;background:#f2f2f2;}";
    file << ".box{background:white;padding:20px;border-radius:10px;width:400px;"
            "box-shadow:0 0 10px #aaa;}";
    file << "h2{text-align:center;color:#333;}";
    file << "</style></head><body>";

    file << "<div class='box'>";
    file << "<h2>Hotel Receipt</h2>";
    file << "<p><b>Guest Name:</b> " << g.name << "</p>";
    file << "<p><b>Room Number:</b> " << g.roomNumber << "</p>";
    file << "<p><b>Room Type:</b> " << g.roomType << "</p>";
    file << "<p><b>Rent Per Day:</b> Rs. " << g.rentPerDay << "</p>";
    file << "<p><b>Days Stayed:</b> " << g.days << "</p>";
    file << "<hr>";
    file << "<p><b>Total Amount:</b> Rs. " << g.rentPerDay * g.days << "</p>";
    file << "</div></body></html>";

    file.close();

    cout << "\n? Receipt generated successfully: receipt.html\n";
}
