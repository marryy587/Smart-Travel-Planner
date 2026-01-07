#include <iostream>  // for standard input/output
#include <fstream>   // for file operations
#include <string>    // for string handling
#include <windows.h> // for console functions like gotoxy & setcolor
#include <cstring>   // for strlen() and string calculations
#include <conio.h>   // for getch() and other console functions
#include <regex>     // for validating email adresses
#include <iomanip>   // for formaing console output with setw, left etc
using namespace std;

// GLOBALS
// ADMIN VARIABLES
const int MAX_USERS = 100;        // Max admin/travelers allowed
string adminUsernames[MAX_USERS]; // admin usernaes
string adminPasswords[MAX_USERS]; // admin passwords
string adminEmails[MAX_USERS];    // admin emails
int adminCount = 0;               // Current no. of admin registeres

// TRAVELER VARIABLES
string travUsernames[MAX_USERS]; // traveler usernames
string travPasswords[MAX_USERS]; // traveler password
string travEmails[MAX_USERS];    // traveler emails
int travCount = 0;               // Current no. of traveler registered

// DESTINATION VARIABLES
const int MAX_DEST = 100;    // Max destination allowed
string destNames[MAX_DEST];  // destination names
string destCities[MAX_DEST]; // destination cities
int destPrices[MAX_DEST];    // destination prices
int destCount = 0;           // number of destinations stored

// BOOKING VARIABLES
const int MAX_BOOKINGS = 100;     // max bookings allowed
string bookingUser[MAX_BOOKINGS]; // username of booking owners
string bookingDest[MAX_BOOKINGS]; // destination booked
int bookingPrice[MAX_BOOKINGS];   // booking price
int bookingCount = 0;             // total bookings

// PACKAGES VARIABLES
const int MAX_PACKAGES = 100;     // max packages allowed
string packageName[MAX_PACKAGES]; // package names
string packageCity[MAX_PACKAGES]; // package cities
int packagePrice[MAX_PACKAGES];   // package prices
int packageCount = 0;             // total packages

// FEEDBACK VARIABLES
const int MAX_FEEDBACK = 100;      // max feedback allowed
string feedbackUser[MAX_FEEDBACK]; // user who gave feedback
string feedbackText[MAX_FEEDBACK]; // feedback messages
int feedbackCount = 0;             // total feedbacks

// CURRENT SESSION VARIABLES
string currentUser = ""; // logged-in username
string currentRole = ""; // logged-in role

// FOR GOTOXY
void gotoxy(int x, int y);

// FOR CENTRE-TEXT OUTPUT
void centertext(const char *text, int y);

// SAFE INPUT FUNCTIONS: get integer or string input safely with validation
int getSafeInt();
string getSafeWord();

// MENU
void mainMenu();
void adminTravelerMenu(string role);

// USER AUTHENTICATION FUNCTIONS: sign up and login
void signUp(string role);
void loginUser(string role);

// ADMIN DASHBOARD
void adminMenu();

// ADMIN DASHBOARD FUNCTIONS
void addDestination();
void viewDestinations();
void updateDestination();
void deleteDestination();
void searchDestination();
void viewAllTravelers();
void viewAllBookings();
void viewAllFeedback();
void addPackage();
void viewPackages();
void generateReport();

// FILE OPERATIONS
void loadPackages();
void savePackages();
void loadDestinations();
void saveDestinations();
void loadBookings();
void saveBookings();
void loadFeedback();
void saveFeedback();
void loadUsers();
void saveUsers();

// TRAVELER DASHBOARD
void travelerMenu();

// TRAVELER DASHBOARD FUNCTIONS
void travelerViewDestinations();
void travelerSearchDestination();
void bookTrip();
void viewMyBookings();
void cancelBooking();
void costCalculator();
void giveFeedback();
void recommendations();

// VALIDATIONS
bool isUsernameUnique(string role, string username);
bool isValidPassword(string pass);
bool isValidEmail(string email);
bool isValidUsername(string username);

// set console text color using Windows API
void setcolor(int color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

// main program: load all data files then stat main menu
int main()
{
    loadUsers();
    loadDestinations();
    loadBookings();
    loadPackages();
    loadFeedback();

    mainMenu();
    return 0;
}

// move the console cursor to specific coordinates(x, y)
void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x; // coloumn
    coord.Y = y; // row
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// print text centered horizontally at given row y
void centertext(const char *text, int y)
{
    int x = (80 - strlen(text)) / 2; // calculate horizontal start point
    gotoxy(x, y);                    // move cursor to start position
    cout << text;                    // display text
}

// get integer input safely.... retry if invalid
int getSafeInt()
{
    string temp;
    cin >> temp;

    for (int i = 0; i < temp.length(); i++)
    {
        if (temp[i] < '0' || temp[i] > '9') // check if character is a digit
        {
            setcolor(12); // red color
            cout << "Invalid number! Try again: ";
            setcolor(7);
            return getSafeInt(); // recursive retry
        }
        setcolor(7); // reset color
    }
    return stoi(temp); // convert valid string to integer
}

// get a non-empty string input safely
string getSafeWord()
{
    string s;
    while (true)
    {
        getline(cin, s);
        if (!s.empty())
            return s; // return if input is valid
        setcolor(12);  // red 
        cout << "Invalid input! Try again: ";
        setcolor(7);// reset color(white)
    }
}

// Check whether destination exist or not
bool destinationExists(string name)
{
    for (int i = 0; i < destCount; i++)
    {
        if (destNames[i] == name)
            return true; // destination exist
    }
    return false; // not found
}

// MAIN
void mainMenu()
{
    int choice;
    do
    {

        system("cls"); // clear console

        // centre alligned header
        setcolor(12); // red
        centertext("==============================================================", 2);
        setcolor(11); // cyan
        centertext("                       WELCOME TO                              ", 4);
        setcolor(14); // yellow
        centertext("                   SMART TRAVEL PLANNER                       ", 6);
        setcolor(12); // red
        centertext("==============================================================", 8);
        setcolor(10); // green
        centertext("          Your Smart Companion For Every Journey :)           ", 10);
        setcolor(9); // blue
        centertext("--------------------------------------------------------------", 12);

        // MENU OPTIONS
        setcolor(13); // purple
        gotoxy(10, 14);
        cout << "1. Admin Sign Up";
        gotoxy(10, 15);
        cout << "2. Admin Login";
        gotoxy(10, 16);
        cout << "3. Traveler Sign Up";
        gotoxy(10, 17);
        cout << "4. Traveler Login";
        gotoxy(10, 18);
        cout << "5. Exit";
        setcolor(12); // red
        centertext("==============================================================", 20);

        // Input prompt in aqua
        setcolor(3);
        gotoxy(10, 22);
        cout << "Enter your choice: ";
        setcolor(7);

        // Input
        choice = getSafeInt();
        cin.ignore(1000, '\n');
        switch (choice)
        {
        case 1:
            signUp("admin"); // go to admin signup
            break;
        case 2:
            loginUser("admin"); // go to admin login
            break;
        case 3:
            signUp("traveler"); // go to traveler signup
            break;
        case 4:
            loginUser("traveler"); // go to traveler login
            break;
        case 5:
            setcolor(12); // red
            cout << "\nExiting Smart Travel Planner....... Goodbye!\n";
            break;
        default:
            setcolor(12); // red
            centertext("Invalid choice! Try again.", 24);
            setcolor(7);
            system("pause");
        }

    } while (choice != 5);
}

// SIGN UP
void signUp(string role)
{
    ofstream file;

    if (role == "admin")
        file.open("admins.txt", ios::app); // append admin
    else
        file.open("travelers.txt", ios::app); // append traveler

    if (!file)
    {
        cout << "Error opening user data file for " << role << ".\n";
        return;
    }
    string username, password, email;
    system("cls");

    setcolor(13); // purple
    cout << "\n---------------------- SIGN UP (" << role << ") --------------------\n";

    setcolor(7); // reset
    cout << "Enter username: ";
    username = getSafeWord();

    // Check validations for username, password & email

    if (!isUsernameUnique(role, username))
    {
        setcolor(14); // yellow
        cout << "Username already exists! Try again.\n";
        return;
    }
    while (!isValidUsername(username))
    {
        setcolor(12);
    cout<<"Invalid username! Only alphabets allowed.\n";
    cout<<"Enter username again: ";
    setcolor(7); // reset(white )
    username=getSafeWord();
    }
    cout << "Enter password (max 7 chars, must contain a digit and * # $ @): ";
    cin >> password;
    cin.ignore(1000, '\n');// clear input buffer

    while (!isValidPassword(password))
    {
        setcolor(12); // red
        cout << "Invalid password. Enter again: ";
        setcolor(7);
        cin >> password;
    }
    setcolor(7); // reset color
    cout << "Enter email: ";
    cin >> email;
    cin.ignore(1000, '\n'); // clear input bufer

    while (!isValidEmail(email))
    {
        setcolor(12); // red
        cout << "Invalid email format! Enter again: ";
        setcolor(7);
        cin >> email;
    }

    // store in file
    file << username << " " << password << " " << email << endl;
    if (role == "admin")
    {
        adminUsernames[adminCount] = username;
        adminPasswords[adminCount] = password;
        adminEmails[adminCount] = email;
        adminCount++;
    }
    else
    {
        travUsernames[travCount] = username;
        travPasswords[travCount] = password;
        travEmails[travCount] = email;
        travCount++;
    }
    file.close();
    setcolor(10); // green
    cout << "Signup successful!\n";

    setcolor(7); // reset
    getch();     // wait for key press
}

// CHECK USERNAME UNIQUENESS
bool isUsernameUnique(string role, string username)
{
    if (role == "admin")
    {
        for (int i = 0; i < adminCount; i++)
            if (adminUsernames[i] == username)
                return false; // admin username taken
    }
    else
    {
        for (int i = 0; i < travCount; i++)
            if (travUsernames[i] == username)
                return false; // traveler username taken
    }
    return true; // unique
}
bool isValidUsername(string username)
{
    // Empty username not allowed
if (username.empty())
        return false;
    for (int i=0;i<username.length();i++)
    {
        // Check if character is NOT an alphabet
    if (!((username[i]>='A'&&username[i]<='Z') ||(username[i]>='a'&&username[i]<='z')))
        {
         return false;
    }
    }
    return true; // All characters are alphabets
}
// PASSWORD VALIDATION
bool isValidPassword(string pass)
{
    if (pass.length() > 7)
        return false; // exceed max length

    bool hasDigit = false, hasSpecial = false;
    char sp[] = {'*', '#', '$', '@'};

    for (int i = 0; i < pass.length(); i++)
    {
        if (pass[i] >= '0' && pass[i] <= '9')
            hasDigit = true;

        for (int j = 0; j < 4; j++)
            if (pass[i] == sp[j])
                hasSpecial = true;
    }
    return hasDigit && hasSpecial; // must contain digit & special char
}

// EMAIL VALIDATION
bool isValidEmail(string email)
{
    // regex pattern for email format
    regex pattern(R"(^[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\.[A-Za-z]{2,}$)");
    return regex_match(email, pattern);
}

// LOGIN FUNCTION
void loginUser(string role)
{
    string inputUser, pass;
    system("cls"); // clear console screen
    setcolor(13);
    cout << "\n-------------------------- LOGIN (" << role << ") ---------------------\n";

    cin.ignore(1000, '\n'); // clear input buffer

    // Input username/email and password
    setcolor(7);
    cout << "Enter username or email: ";
    inputUser = getSafeWord(); // safely  read username/email
    cout << "Enter password: ";
    pass = getSafeWord(); // safely read password

    bool success = false; // flag to check login  success
    if (role == "admin")  // verify crenditals for admin
    {
        for (int i = 0; i < adminCount; i++)
        {
            if ((inputUser == adminUsernames[i] || inputUser == adminEmails[i]) && pass == adminPasswords[i])
            {
                success = true;
                currentUser = adminUsernames[i];
                currentRole = "admin";
                break;
            }
        }
    }
    else // verify crenditals for traveler
    {
        for (int i = 0; i < travCount; i++)
        {
            if ((inputUser == travUsernames[i] || inputUser == travEmails[i]) && pass == travPasswords[i])
            {
                success = true;
                currentUser = travUsernames[i];
                currentRole = "traveler";
                break;
            }
        }
    }

    if (success)
    {

        setcolor(10); // green
        cout << "Login successful! Welcome " << currentUser << ".\n";
        adminTravelerMenu(role); // redirect to respective dashboard
    }
    else
    {
        setcolor(12); // red
        cout << "Invalid credentials. Try again.\n";
    }
    setcolor(7);
    getch(); // wait for key press
}

// LOAD USERS FROM FILE
void loadUsers()
{
    // load admins
    ifstream adminFile("admins.txt");
    adminCount = 0;
    while (adminFile >> adminUsernames[adminCount] >> adminPasswords[adminCount] >> adminEmails[adminCount])
    {
        adminCount++;
        if (adminCount >= MAX_USERS) // prevent overflow
            break;
    }
    adminFile.close();

    // load travelers
    ifstream travFile("travelers.txt");
    travCount = 0;
    while (travFile >> travUsernames[travCount] >> travPasswords[travCount] >> travEmails[travCount])
    {
        travCount++;
        if (travCount >= MAX_USERS)
            break;
    }
    travFile.close();
}

// SAVE ALL USERS
void saveUsers()
{
    // save admins
    ofstream adminFile("admins.txt");
    for (int i = 0; i < adminCount; i++)
    {
        adminFile << adminUsernames[i] << " " << adminPasswords[i] << " " << adminEmails[i] << endl;
    }
    adminFile.close();

    // save travelers
    ofstream travFile("travelers.txt");
    for (int i = 0; i < travCount; i++)
    {
        travFile << travUsernames[i] << " " << travPasswords[i] << " " << travEmails[i] << endl;
    }
    travFile.close();
}

// LOAD DESTINATIONS FROM FILE
void loadDestinations()
{
    ifstream file("destinations.txt");
    destCount = 0;
    while (file >> destNames[destCount] >> destCities[destCount] >> destPrices[destCount])
    {
        destCount++;
        if (destCount >= MAX_DEST) // prevent overflow
            break;
    }
    file.close();
}

// SAVE DESTINATIONS TO FILE
void saveDestinations()
{
    ofstream file("destinations.txt");
    for (int i = 0; i < destCount; i++)
    {
        file << destNames[i] << " " << destCities[i] << " " << destPrices[i] << endl;
    }
    file.close();
}

// LOAD BOOKINGS FROM FILE
void loadBookings()
{
    ifstream file("bookings.txt");
    bookingCount = 0;
    while (file >> bookingUser[bookingCount] >> bookingDest[bookingCount] >> bookingPrice[bookingCount])
    {
        bookingCount++;
        if (bookingCount >= MAX_BOOKINGS) // prevent overflow
            break;
    }
    file.close();
}

// SAVE BOOKING TO FILE
void saveBookings()
{
    ofstream file("bookings.txt");
    for (int i = 0; i < bookingCount; i++)
    {
        file << bookingUser[i] << " " << bookingDest[i] << " " << bookingPrice[i] << endl;
    }
    file.close();
}

// LOAD FEEDBACKS FROM FILE
void loadFeedback()
{
    ifstream file("feedback.txt");
    feedbackCount = 0;
    while (getline(file, feedbackUser[feedbackCount])) // first line: user
    {
        getline(file, feedbackText[feedbackCount]); // second line: feedback msg
        feedbackCount++;
        if (feedbackCount >= MAX_FEEDBACK)
            break;
    }
    file.close();
}

// SAVE FEEDBACKS TO FILE
void saveFeedback()
{
    ofstream file("feedback.txt");
    for (int i = 0; i < feedbackCount; i++)
    {
        file << feedbackUser[i] << endl; // save username
        file << feedbackText[i] << endl; // save feedback
    }
}

// LOAD PACKAGES FROM FILE
void loadPackages()
{
    ifstream file("packages.txt");
    packageCount = 0;
    while (file >> packageName[packageCount] >> packageCity[packageCount] >> packagePrice[packageCount])
    {
        packageCount++;
        if (packageCount >= MAX_PACKAGES) // prevent overflow
            break;
    }
    file.close();
}

// SAVE PACKAGES TO FILE
void savePackages()
{
    ofstream file("packages.txt");

    for (int i = 0; i < packageCount; i++)
    {
        file << packageName[i] << " " << packageCity[i] << " " << packagePrice[i] << endl;
    }

    file.close();
}

// DASHBOARD REDIRECTION BASED  ON ROLE
void adminTravelerMenu(string role)
{
    if (role == "admin")
    {
        adminMenu(); // go to admin dashboord
    }
    else
    {
        travelerMenu(); // go to traveler dashboard
    }
}

// ADMIN DASHBOARD MENU
void adminMenu()
{
    int choice;

    do
    {
        system("cls"); // clear console
        setcolor(2);   // red
        centertext("========================================================", 2);
        setcolor(11); // cyan
        centertext("                   ADMIN DASHBOARD                    ", 4);
        setcolor(2); // red
        centertext("========================================================", 6);

        // display menu options
        setcolor(6); // yellow
        gotoxy(8, 9);
        cout << "1. Add Destination";
        gotoxy(8, 10);
        cout << "2. View Destinations";
        gotoxy(8, 11);
        cout << "3. Update Destination";
        gotoxy(8, 12);
        cout << "4. Delete Destination";
        gotoxy(8, 13);
        cout << "5. Search Destination";
        gotoxy(40, 9);
        cout << "6. View All Travelers";
        gotoxy(40, 10);
        cout << "7. View All Bookings";
        gotoxy(40, 11);
        cout << "8. View Feedback";
        gotoxy(40, 12);
        cout << "9. Add Package";
        gotoxy(40, 13);
        cout << "10. View Packages";
        gotoxy(40, 14);
        cout << "11. Generate Report";
        gotoxy(40, 15);
        cout << "12. Logout";

        setcolor(3); // aqua
        gotoxy(8, 17);
        cout << "Enter choice: "; 
        setcolor(7);              // reset

        choice = getSafeInt(); // safe int input
        cin.ignore(1000, '\n');// Clear leftover input from buffer

        // switch-case to handle user selection
        switch (choice)
        {
        case 1:
            addDestination();
            break;
        case 2:
            viewDestinations();
            break;
        case 3:
            updateDestination();
            break;
        case 4:
            deleteDestination();
            break;
        case 5:
            searchDestination();
            break;
        case 6:
            viewAllTravelers();
            break;
        case 7:
            viewAllBookings();
            break;
        case 8:
            viewAllFeedback();
            break;
        case 9:
            addPackage();
            break;
        case 10:
            viewPackages();
            break;
        case 11:
            generateReport();
            break;
        case 12:
            setcolor(2); // red
            gotoxy(8, 19);
            cout << "Logging out...\n";
            break;
        default:
            setcolor(12); // red
            gotoxy(8, 19);
            cout << "Invalid Choice! Try Again.\n";
            setcolor(7);
        }

        if (choice != 12)
            system("pause"); // pause before reloading  menu

    } while (choice != 12);
    getch(); // wait for key enter
}

// ADD NEW DESTINATIONS
void addDestination()
{
    if (destCount >= MAX_DEST) // check for max capacity
    {
        setcolor(12); // red
        cout << "Destination limit reached!\n";
        return;
    }
    setcolor(14); // yellow
    cout << "\n----------------------- ADD DESTINATION -----------------------\n";
    setcolor(7); // reset
    // get input for new destination
    cout << "Enter destination name: ";
    destNames[destCount] = getSafeWord();

    cout << "Enter City (one word): ";
    destCities[destCount] = getSafeWord();

    cout << "Enter price: ";
    destPrices[destCount] = getSafeInt();
    cin.ignore(1000, '\n');

    destCount++;        // increment total destinations
    saveDestinations(); // save to file

    setcolor(10); // green
    cout << "Destination Added Successfully!\n";
    getch();
}

// VIEW ALL DESTINATIONS
void viewDestinations()
{
    setcolor(11); // cyan
    cout << "\n================= LIST OF DESTINATIONS =================\n\n";

    if (destCount == 0) // no destination
    {
        setcolor(12); // red
        cout << "No destinations available!\n";
        return;
    }

    // display table header
    setcolor(14); // yellow
    cout << left
         << setw(5) << "No"
         << setw(20) << "Destination"
         << setw(20) << "City"
         << setw(10) << "Price"
         << endl;

    setcolor(0); // black
    cout << "--------------------------------------------------------\n";

    // display each destination
    for (int i = 0; i < destCount; i++)
    {
        setcolor(7); // reset
        cout << left
             << setw(5) << i + 1
             << setw(20) << destNames[i]
             << setw(20) << destCities[i]
             << setw(10) << destPrices[i]
             << endl;
    }
    setcolor(7);
    getch();
}

// UPDATE DESTINATION DETAILS
void updateDestination()
{
    if (destCount == 0)
    {
        setcolor(14); // yellow
        cout << "No destinations available to update.\n";
        return;
    }
    string target;
    setcolor(7); // reset
    cout << "\nEnter destination name to update: ";
    target = getSafeWord();

    bool found = false;
    // check if destination exist
    if (!destinationExists(target))
    {
        setcolor(2); // red
        cout << "Destination does not exist!\n";
        return;
    }
    for (int i = 0; i < destCount; i++)
    {
        if (destNames[i] == target)
        {
            // update destination info
            found = true;
            setcolor(7);
            cout << "Enter New Name: ";
            destNames[i] = getSafeWord();

            cout << "Enter New City: ";
            destCities[i] = getSafeWord();

            cout << "Enter New Price: ";
            destPrices[i] = getSafeInt();
            cin.ignore(1000, '\n');
            saveDestinations(); // save update data

            setcolor(10); // green
            cout << "Destination Updated!\n";
            break;
        }
    }
    if (!found)
    {
        setcolor(2); // red
        cout << "Destination not found!\n";
    }
    getch();
}

// DELETE DESTINATIONS
void deleteDestination()
{
    if (destCount == 0)
    {

        setcolor(14); // yellow
        cout << "No destinations to delete.\n";
        return;
    }

    string target;
    setcolor(7); // reset
    cout << "\nEnter destination name to delete: ";
    target = getSafeWord();

    bool found = false;

    if (!destinationExists(target))
    {
        setcolor(2); // red
        cout << "Destination not found!\n";
        return;
    }
    for (int i = 0; i < destCount; i++)
    {
        if (destNames[i] == target)
        {
            found = true;

            // shift remainig destinations left
            for (int j = i; j < destCount - 1; j++)
            {
                destNames[j] = destNames[j + 1];
                destCities[j] = destCities[j + 1];
                destPrices[j] = destPrices[j + 1];
            }

            destCount--;        // descrease count
            saveDestinations(); // save changes
            setcolor(10);       // green
            cout << "Destination Deleted!\n";
            break;
        }
    }
    if (!found)
    {
        setcolor(2); // red
        cout << "Destination not found!\n";
    }
    getch();
}

// SEARCH DESTINATION BY NAME OR CITY
void searchDestination()
{
    string key;
    setcolor(7); // reset
    cout << "\nEnter destination name or city to search: ";
    key = getSafeWord();

    bool found = false;
    setcolor(11); // cyan
    cout << "\n================ SEARCH RESULTS ================\n\n";

    // table header
    setcolor(14); // yellow
    cout << left
         << setw(20) << "Destination"
         << setw(20) << "City"
         << setw(10) << "Price"
         << endl;

    setcolor(0); // black
    cout << "------------------------------------------------\n";

    // search and display matches
    for (int i = 0; i < destCount; i++)
    {
        if (destNames[i] == key || destCities[i] == key)
        {
            setcolor(7); // reset color
            cout << left
                 << setw(20) << destNames[i]
                 << setw(20) << destCities[i]
                 << setw(10) << destPrices[i]
                 << endl;
            found = true;
        }
    }
    if (!found)
    {
        setcolor(2); // red
        cout << "No matching destination found!\n";
    }
    getch();
}

// VIEW ALL REGISTERED TRAVELERS
void viewAllTravelers()
{
    setcolor(11);
    cout << "\n================= ALL TRAVELERS =================\n\n";

    if (travCount == 0) // no travelers
    {
        setcolor(12); // Red
        cout << "No travelers available.\n";
        setcolor(7);
        return;
    }
    // table header
    setcolor(14); // Yellow
    cout << left
         << setw(5) << "No"
         << setw(20) << "Username"
         << setw(30) << "Email"
         << endl;

    cout << "-------------------------------------------------\n";

    for (int i = 0; i < travCount; i++)
    {
        // display all travelers
        setcolor(7); // reset(white)
        cout << left
             << setw(5) << i + 1
             << setw(20) << travUsernames[i]
             << setw(30) << travEmails[i]
             << endl;
    }
    getch();
}

// VIEW ALL BOOKING
void viewAllBookings()
{
    setcolor(11);
    cout << "\n================ ALL BOOKINGS ================\n\n";

    if (bookingCount == 0) // no booking
    {
        setcolor(2); // red
        cout << "No bookings available.\n";
        return;
    }
    // display header
    setcolor(14);
    cout << left
         << setw(20) << "User"
         << setw(20) << "Destination"
         << setw(10) << "Price"
         << endl;
    setcolor(0); // black
    cout << "---------------------------------------------\n";

    for (int i = 0; i < bookingCount; i++)
    {
        // display bookings
        setcolor(7); // reset
        cout << left
             << setw(20) << bookingUser[i]
             << setw(20) << bookingDest[i]
             << setw(10) << bookingPrice[i]
             << endl;
    }
    getch();
}
// VIEW ALL USER FEEDBACK
void viewAllFeedback()
{
    setcolor(11); // cyan
    cout << "\n================== USER FEEDBACK ==================\n\n";

    if (feedbackCount == 0)
    {
        setcolor(12); // red
        cout << "No feedback available.\n";
        setcolor(7);
        return;
    }
    // display each feedback
    for (int i = 0; i < feedbackCount; i++)
    {
        setcolor(7); // reset
        cout << "User: ";

        cout << feedbackUser[i] << endl;
        cout << "Feedback: ";
        cout << feedbackText[i] << endl;

        setcolor(0); // black
        cout << "--------------------------------------------------\n";
    }
    getch();
}

// ADD  NEW PACKAGES
void addPackage()
{
    if (packageCount >= MAX_PACKAGES)
    {
        setcolor(2);
        cout << "Package limit reached.\n";
        return;
    }
    setcolor(11); // cyan
    cout << "\n------------------- ADD PACKAGE -----------------------\n";
    // input
    setcolor(7);
    cout << "Enter Package Name (one word): ";
    packageName[packageCount] = getSafeWord();

    cout << "Enter City (one word): ";
    packageCity[packageCount] = getSafeWord();

    cout << "Enter Price: ";
    packagePrice[packageCount] = getSafeInt();

    packageCount++; // increment count
    savePackages(); // save to file
    setcolor(10);   // green
    cout << "Package Added Successfully!\n";
    getch();
}

// VIEW ALL PACKAGES
void viewPackages()
{

    setcolor(11); // cyan
    cout << "\n================ TRAVEL PACKAGES ================\n\n";

    if (packageCount == 0)
    {
        setcolor(12); // red
        cout << "No packages available.\n";
        setcolor(7); // reset
        return;
    }
    // table header
    setcolor(14);
    cout << left
         << setw(5) << "No"
         << setw(20) << "Package"
         << setw(20) << "City"
         << setw(10) << "Price"
         << endl;

    cout << "--------------------------------------------------------------\n";

    setcolor(7);

    for (int i = 0; i < packageCount; i++)
    {
        // display
        cout << left
             << setw(5) << i + 1
             << setw(20) << packageName[i]
             << setw(20) << packageCity[i]
             << setw(10) << packagePrice[i]
             << endl;
    }
    getch();
    setcolor(7);
}

// GENERATE SYSTEM REPORT(SUMMARY)
void generateReport()
{
    setcolor(11); // cyan

    cout << "\n------------------------ SYSTEM REPORT ------------------------\n";

    setcolor(7);
    cout << "Total Travelers: " << travCount << endl;
    cout << "Total Destinations: " << destCount << endl;
    cout << "Total Bookings: " << bookingCount << endl;
    // calculate total revenue
    int revenue = 0;
    for (int i = 0; i < bookingCount; i++)
    {
        revenue += bookingPrice[i];
    }

    setcolor(13); // purple
    cout << "Total Revenue from Bookings: Rs. " << revenue << endl;

    setcolor(0);
    cout << "------------------------------------------------------\n";
    getch();
}

// TRAVELER DASHBOARD MENU
void travelerMenu()
{
    int choice;
    do
    {
        system("cls"); // clear screen
        // display dashboard header
        setcolor(4); // red
        centertext("========================================================", 2);
        setcolor(11); // cyan
        centertext("                   TRAVELER DASHBOARD                  ", 4);
        setcolor(4); // red
        centertext("========================================================", 6);

        // menu options with coordinates
        setcolor(6); // yellow
        gotoxy(8, 9);
        cout << "1. View Destinations";
        gotoxy(8, 10);
        cout << "2. Search Destination";
        gotoxy(8, 11);
        cout << "3. Book Trip";
        gotoxy(8, 12);
        cout << "4. View My Bookings";
        gotoxy(8, 13);
        cout << "5. Cancel Booking";
        gotoxy(40, 9);
        cout << "6. Trip Cost Calculator";
        gotoxy(40, 10);
        cout << "7. Recommendations";
        gotoxy(40, 11);
        cout << "8. Give Feedback";
        gotoxy(40, 12);
        cout << "9. Logout";
        setcolor(3); // aqua
        gotoxy(8, 15);
        cout << "Enter choice: ";
        setcolor(7);
        choice = getSafeInt();  // safe int  input
        cin.ignore(1000, '\n'); // Clear leftover input from buffer

        // handle user selection
        switch (choice)
        {
        case 1:
            travelerViewDestinations();
            break;
        case 2:
            travelerSearchDestination();
            break;
        case 3:
            bookTrip();
            break;
        case 4:
            viewMyBookings();
            break;
        case 5:
            cancelBooking();
            break;
        case 6:
            costCalculator();
            break;
        case 7:
            recommendations();
            break;
        case 8:
            giveFeedback();
            break;
        case 9:
            setcolor(4); // red
            gotoxy(8, 17);
            cout << "Logging out......\n";
            break;
        default:
            setcolor(4);
            gotoxy(8, 17);
            cout << "Invalid Choice! Try Again.\n";
        }

        if (choice != 9)
            system("pause"); // pause before redisplaying menu

    } while (choice != 9);
    getch(); // wait for key press
}

// VIEW ALL DESTINATIONS
void travelerViewDestinations()
{
    viewDestinations(); // reuse admin function
}

// SEARCH DESTINATION
void travelerSearchDestination()
{
    searchDestination(); // reuse admin function
}

// BOOK A TRIP
void bookTrip()
{
    if (destCount == 0) // no destination
    {
        setcolor(2); // red
        cout << "No destinations available.\n";
        return;
    }
    string name;
    setcolor(7); // reset
    cout << "Enter destination name to book: ";
    name = getSafeWord();

    bool found = false;

    for (int i = 0; i < destCount; i++)
    {
        // search for destination
        if (destNames[i] == name)
        {
            found = true;

            if (bookingCount >= MAX_BOOKINGS) // check limit
            {
                setcolor(2);
                cout << "Booking limit reached!\n";
                return;
            }

            bookingUser[bookingCount] = currentUser;
            bookingDest[bookingCount] = name;
            bookingPrice[bookingCount] = destPrices[i];
            bookingCount++;

            saveBookings(); // save to file
            setcolor(10);   // green
            cout << "Booking successful!\n";
            break;
        }
    }
    if (!found)
    {
        setcolor(2);
        cout << "Destination not found!\n";
    }
    getch();
}

// VIEW CURRENT USER BOOKINGS
void viewMyBookings()
{
    setcolor(11); // cyan
    cout << "\n============================= MY BOOKINGS ==============================\n\n";

    bool any = false;
    // table header
    setcolor(14); // yellow
    cout << left
         << setw(5) << "No"
         << setw(20) << "Destination"
         << setw(10) << "Price"
         << endl;

    setcolor(0); // black
    cout << "-------------------------------------------------------------\n";
    setcolor(7); // reset

    // iterate through bookings and filter by current user
    for (int i = 0; i < bookingCount; i++)
    {
        if (bookingUser[i] == currentUser)
        {
            cout << left
                 << setw(5) << i + 1
                 << setw(20) << bookingDest[i]
                 << setw(10) << bookingPrice[i]
                 << endl;
            any = true;
        }
    }
    if (!any)
    {
        setcolor(12); // Red
        cout << "You have no bookings.\n";
    }
    setcolor(7);
    getch();
}

// CWNCEL A BOOKING
void cancelBooking()
{
    string name;
    setcolor(7);
    cout << "Enter destination name to cancel booking: ";
    name = getSafeWord();
    bool found = false;

    // search and remove booking
    for (int i = 0; i < bookingCount; i++)
    {
        if (bookingUser[i] == currentUser && bookingDest[i] == name)
        {
            found = true;
            // shift remaining bookings left
            for (int j = i; j < bookingCount - 1; j++)
            {
                bookingUser[j] = bookingUser[j + 1];
                bookingDest[j] = bookingDest[j + 1];
                bookingPrice[j] = bookingPrice[j + 1];
            }
            bookingCount--;
            saveBookings(); // save updated bookings
            setcolor(2);
            cout << "Booking cancelled.\n";
            break;
        }
    }

    if (!found)
    {
        setcolor(2);
        cout << "No such booking found.\n";
    }
    getch();
}

// TRIP COST CALCULATOR
void costCalculator()
{
    int base, days;
    setcolor(7);
    cout << "Enter base price of destination: ";
    base = getSafeInt();
    cout << "Enter number of days: ";
    days = getSafeInt();
    int total = base * days;
    cout << "Estimated Trip Cost = " << total << endl;
    getch();
}

// SMART RECOMMENDATIONS
void recommendations()
{
    setcolor(13);
    cout << "\n================================== SMART RECOMMENDATIONS ==================================\n";
    if (destCount == 0)
    {
        setcolor(14);
        cout << "No destinations available.\n";
        return;
    }
    // gather user prefrences
    int income;
    string interest;
    setcolor(7);
    cout << "Enter your monthly income: ";
    income = getSafeInt();

    cout << "Enter your interest (adventure / nature / beach / historical / shopping): ";

    cin.ignore(1000, '\n'); // Clear leftover input from buffer to avoid issues with next input
    interest = getSafeWord();

    setcolor(11); // cyan

    // header for recommendation table
    cout << "\n--------------------------- BEST DESTINATIONS FOR YOU ----------------------------\n";

    bool found = false;
    setcolor(10);
    cout << "Here are some popular destinations based on your interest and income. \n";
    cout << "You can still choose from the full list of destinations later.\n\n";
    setcolor(7);
    // sample destinations database
    string placeName[20] = {"Bali", "Dubai", "Istanbul", "Rome", "Phuket", "Maldives", "Switzerland", "Canada", "NewYork", "SaudiArabia", "Murree", "Hunza", "Skardu", "Naran", "Kaghan", "Karachi", "Lahore", "Islamabad", "Gwadar", "Turkey"};
    int placePrice[20] = {120000, 90000, 110000, 150000, 85000, 200000, 250000, 180000, 300000, 100000, 20000, 25000, 30000, 15000, 14000, 10000, 12000, 15000, 18000, 130000};
    string placeInterest[20] = {"beach", "shopping", "historical", "historical", "beach", "beach", "nature", "nature", "shopping", "historical", "nature", "nature", "nature", "nature", "nature", "shopping", "historical", "historical", "beach", "historical"};

    // display table header
    setcolor(14);
    cout << left
         << setw(15) << "Destination"
         << setw(15) << "Category"
         << setw(12) << "Price"
         << setw(12) << "Type"
         << endl;

    setcolor(0);
    cout << "---------------------------------------------------------------------------\n";
    setcolor(7);

    // FILTER: If all three match → recommend it
    for (int i = 0; i < 20; i++)
    {
        bool incomeOk = income >= placePrice[i] / 2;
        bool interestOk = (interest == placeInterest[i]);

        if (incomeOk && interestOk )
        {
            string type = (placePrice[i] <= 50000) ? "Domestic" : "International";

            cout << left
                 << setw(15) << placeName[i]
                 << setw(15) << placeInterest[i]
                 << setw(12) << placePrice[i]
                 << setw(12) << type
                 << endl;

            found = true;
        }
    }
    if (!found)
    {
        cout << "No perfect match found!\n";
        cout << "But here are some budget-friendly options:\n";

        // If no perfect match, show cheap destinations
        for (int i = 0; i < 20; i++)
        {
            if (placePrice[i] <= income / 2)
            {
                cout << "- " << placeName[i]
                     << " | Price: " << placePrice[i] << endl;
            }
        }
    }
    setcolor(0);
    cout << "=================================================================\n";
    getch();
}

// GIVE FEEDBACK
void giveFeedback()
{
    if (feedbackCount >= MAX_FEEDBACK) // check feedback limit
    {
        setcolor(14); // yellow
        cout << "Feedback limit reached.\n";
        return;
    }
    setcolor(7);           
    cin.ignore(1000, '\n'); // Clear leftover input from buffer to avoid issues with next input
    cout << "Enter your feedback: ";
    getline(cin, feedbackText[feedbackCount]); // store feedback text

    feedbackUser[feedbackCount] = currentUser;

    feedbackCount++; // increment feedback counter
    saveFeedback();  // save to file

    setcolor(10);
    cout << "Thank you for your feedback!\n";
    getch();
}