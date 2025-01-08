#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <functional>
#include <queue>
#include <climits>
#include <unordered_map>
#include <conio.h> // For _getch() function

using namespace std;

// Class to represent a waste item
class WasteItem
{
public:
    int id;
    string type;
    float weight;

    // Constructor to initialize a waste item
    WasteItem(int id, string type, float weight) : id(id), type(type), weight(weight) {}

    // Convert waste item to string for file storage
    string toString() const
    {
        return to_string(id) + "," + type + "," + to_string(weight);
    }

    // Create a waste item from a string (read from file)
    static WasteItem fromString(const string& data)
    {
        size_t firstComma = data.find(',');
        size_t secondComma = data.find(',', firstComma + 1);

        int id = stoi(data.substr(0, firstComma));
        string type = data.substr(firstComma + 1, secondComma - firstComma - 1);
        float weight = stof(data.substr(secondComma + 1));

        return WasteItem(id, type, weight);
    }
};

// Class to manage waste items
class WasteManagementSystem
{
public:
    vector<WasteItem> waste_items;
    const string file_name = "C:\\Users\\Lenovo\\Desktop\\DAA PROJECT\\waste_items.txt";

    // Constructor loads waste items from file
    WasteManagementSystem()
    {
        loadFromFile();
    }

    // Destructor saves waste items to file
    ~WasteManagementSystem()
    {
        saveToFile();
    }

    // Add a new waste item to the system and save to file
    void addWasteItem(int id, string type, float weight)
    {
        WasteItem item(id, type, weight);
        waste_items.push_back(item);
        saveToFile();
    }

    // Sort waste items by their weight and display sorted weights
    void sortWasteItems()
    {
        vector<float> weights;
        for (const auto& item : waste_items)
        {
            weights.push_back(item.weight);
        }

        sort(weights.begin(), weights.end());

        cout << "Sorted Weights: ";
        for (const auto& weight : weights)
        {
            cout << weight << " ";
        }
        cout << endl;
    }

    // Display all waste items
    void displayItems()
    {
        for (const auto& item : waste_items)
        {
            cout << "ID: " << item.id << ", Type: " << item.type << ", Weight: " << item.weight << endl;
        }
    }

    // Search for a waste item by ID
    void searchWasteItem(int id)
    {
        for (const auto& item : waste_items)
        {
            if (item.id == id)
            {
                cout << "Found Waste Item - ID: " << item.id << ", Type: " << item.type << ", Weight: " << item.weight << endl;
                return;
            }
        }
        cout << "No Waste Item found with ID: " << id << endl;
    }

    // Delete a waste item by ID
    void deleteWasteItem(int id)
    {
        auto it = remove_if(waste_items.begin(), waste_items.end(), [id](const WasteItem& item)
        {
            return item.id == id;
        });

        if (it != waste_items.end())
        {
            waste_items.erase(it, waste_items.end());
            cout << "Waste Item with ID: " << id << " has been deleted.\n";
            saveToFile();
        }
        else
        {
            cout << "No Waste Item found with ID: " << id << endl;
        }
    }

    // Display the total weight of all waste items
    void displayTotalWeight()
    {
        float totalWeight = 0;
        for (const auto& item : waste_items)
        {
            totalWeight += item.weight;
        }
        cout << "Total Weight of All Waste Items: " << totalWeight << " kg" << endl;
    }

private:
    // Save waste items to file
    void saveToFile()
    {
        ofstream file(file_name, ios::trunc);
        if (!file.is_open())
        {
            cerr << "Failed to open file for writing: " << file_name << endl;
            return;
        }
        for (const auto& item : waste_items)
        {
            file << item.toString() << endl;
        }
        file.close();
    }

    // Load waste items from file
    void loadFromFile()
    {
        ifstream file(file_name);
        if (!file.is_open())
        {
            cerr << "Failed to open file for reading: " << file_name << endl;
            return;
        }
        string line;
        while (getline(file, line))
        {
            WasteItem item = WasteItem::fromString(line);
            waste_items.push_back(item);
        }
        file.close();
    }
};

// Class to manage users (for demonstration purposes)
class UserManager
{
public:

    // Function to manage users
    void manageUsers()
    {
        vector<string> userNames;
        ifstream inFile("C:\\Users\\Lenovo\\Desktop\\DAA PROJECT\\customer.txt");
        string user;

        if (inFile.is_open())
            {
            while (getline(inFile, user))
            {
                userNames.push_back(user);
            }
            inFile.close();
        }
        else
        {
            cout << "Error: Unable to open users file.\n";
        }

        while (true)
            {
            int choice;
            cout << "\n----------------\n";
            cout << "\n   Users Menu:  \n";
            cout << "\n----------------\n";
            cout << "1. Add Temporary user\n";
            cout << "2. View all users(register & login)\n";
            cout << "3. Exit\n";
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice)
            {
                case 1:
                    {
                    string newUser;
                    cout << "Enter the Temporary user name: ";
                    cin.ignore();
                    getline(cin, newUser);
                    userNames.push_back(newUser);

                    ofstream outFileNew("C:\\Users\\Lenovo\\Desktop\\DAA PROJECT\\customer.txt", ios::app);
                    if (outFileNew.is_open())
                    {
                        outFileNew << newUser << "\n";
                        outFileNew.close();
                        cout << "User added: " << newUser << "\n";
                    }
                    else
                    {
                        cout << "Error saving user.\n";
                    }
                    break;
                }

                case 2:
                    {
                    cout << "\nAll Users:\n";
                    for (size_t i = 0; i < userNames.size(); ++i)
                    {
                        cout << i + 1 << ". " << userNames[i] << "\n";
                    }
                    break;
                }

                case 3:
                    cout << "Exiting Manage Users Menu.\n";
                    return;

                default:
                    cout << "Invalid choice. Please try again.\n";
            }
        }
    }
};

// Function to get password input without displaying it
void getPassword(string& password) {
    char ch;
    password.clear();
    while (true) {
        ch = _getch();
        if (ch == 13) { // Enter key
            break;
        } else if (ch == 8 && !password.empty()) { // Backspace key
            password.pop_back();
            cout << "\b \b"; // Move the cursor back and erase the character
        } else {
            password.push_back(ch);
            cout << "*";
        }
    }
    cout << endl;
}

// Forward declaration for waste management system function
void wasteManagementSystem();
void demo();

class EWasteItem {
public:
    int id;
    string name;
    string category;
    float weight;
    bool isRecycled;

    EWasteItem(int id, string name, string category, float weight) {
        this->id = id;
        this->name = name;
        this->category = category;
        this->weight = weight;
        this->isRecycled = false;
    }

    void display() {
        cout << "ID: " << id << endl;
        cout << "Name: " << name << endl;
        cout << "Category: " << category << endl;
        cout << "Weight: " << weight << " kg" << endl;
        cout << "Status: " << (isRecycled ? "Recycled" : "Pending") << endl;
    }
};

class EWasteManagement {
private:
    vector<EWasteItem> items;

public:
    void addItem(int id, string name, string category, float weight) {
        items.push_back(EWasteItem(id, name, category, weight));
        cout << "E-Waste item added successfully!" << endl;
    }

    void recycleItem(int id) {
        for (auto &item : items) {
            if (item.id == id) {
                if (item.isRecycled) {
                    cout << "This item is already recycled!" << endl;
                } else {
                    item.isRecycled = true;
                    cout << "Item marked as recycled successfully!" << endl;
                }
                return;
            }
        }
        cout << "Item not found!" << endl;
    }

    void displayItems() {
        if (items.empty()) {
            cout << "No e-waste items recorded yet!" << endl;
        } else {
            for (auto &item : items) {
                cout << "--------------------------" << endl;
                item.display();
            }
        }
    }

    void totalRecycledWeight() {
        float totalWeight = 0.0;
        for (auto &item : items) {
            if (item.isRecycled) {
                totalWeight += item.weight;
            }
        }
        cout << "Total weight of recycled items: " << totalWeight << " kg" << endl;
    }
};

void demo() {
    EWasteManagement eWasteManagement;

    while (true) {
        cout << "\nE-Waste Management System\n";
        cout << "1. Add E-Waste Item\n";
        cout << "2. Mark Item as Recycled\n";
        cout << "3. Display All Items\n";
        cout << "4. Display Total Recycled Weight\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;

        switch (choice) {
        case 1: {
            int id;
            string name, category;
            float weight;
            cout << "Enter item ID: ";
            cin >> id;
            cin.ignore(); // Clear input buffer
            cout << "Enter item name: ";
            getline(cin, name);
            cout << "Enter item category (e.g., Mobile, Laptop, TV): ";
            getline(cin, category);
            cout << "Enter item weight (in kg): ";
            cin >> weight;
            eWasteManagement.addItem(id, name, category, weight);
            break;
        }
        case 2: {
            int id;
            cout << "Enter item ID to mark as recycled: ";
            cin >> id;
            eWasteManagement.recycleItem(id);
            break;
        }
        case 3:
            eWasteManagement.displayItems();
            break;
        case 4:
            eWasteManagement.totalRecycledWeight();
            break;
        case 5:
            cout << "Exiting the system. Thank you for managing e-waste responsibly!" << endl;
            return; // Exit the function, terminating the program
        default:
            cout << "Invalid choice! Please try again." << endl;
        }
    }
}

// Base class for user
class User
{
protected:
    string username;
    string password;

public:
    User(string uname, string pass) : username(uname), password(pass) {}
    virtual void menu() = 0;

    string getUsername() { return username; }
    string getPassword() { return password; }
};

// Admin class derived from User
class Admin : public User
{
public:
    Admin(string uname, string pass) : User(uname, pass) {}

    void menu() override
    {
        int choice = 0;
        cout << "\n-------------------------------\n";
        cout << "\n            Admin Menu         \n";
        cout << "\n-------------------------------\n";
        cout << "1. Check Users\n";
        cout << "2. Manage Waste Management System \n";
        cout << "3. Manage Bins\n";
        cout << "4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
                cout << "Users \n";
                UserManager userManager;
                userManager.manageUsers();
                break;

            case 2:
                cout << "Manage Waste Management System\n";
                wasteManagementSystem();
                break;

            case 3:
                cout << "Managing bins \n";
                manageBins();
                break;

            case 4:
                cout << "Exiting Admin Menu...\n";
                break;

            default:
                cout << "Invalid choice. Try again.\n";
        }
    }

    // Manage bins (for demonstration purposes)
    void manageBins()
    {
        vector<string> locationNames;
        ifstream inFile("C:\\Users\\Lenovo\\Desktop\\DAA PROJECT\\locations.txt");
        string location;

        if (inFile.is_open())
        {
            while (getline(inFile, location))
            {
                locationNames.push_back(location);
            }
            inFile.close();
        }
        else
        {
            cout << "Error: Unable to open locations file.\n";
        }

        while (true)
            {
            int choice;
            cout << "\n----------------\n";
            cout << "\n      Bins:    \n";
            cout << "\n----------------\n";
            cout << "1. Add new location\n";
            cout << "2. View all locations\n";
            cout << "3. Exit\n";
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice)
            {
                case 1:
                    {
                    string newLocation;
                    cout << "Enter the name of the location to add a bin: ";
                    cin.ignore();
                    getline(cin, newLocation);
                    locationNames.push_back(newLocation);

                    ofstream outFileNew("C:\\Users\\Lenovo\\Desktop\\DAA PROJECT\\locations.txt", ios::app);
                    if (outFileNew.is_open())
                    {
                        outFileNew << newLocation << "\n";
                        outFileNew.close();
                        cout << "Location added: " << newLocation << "\n";
                    }
                    else
                    {
                        cout << "Error saving location.\n";
                    }
                    break;
                }

                case 2:
                {
                    cout << "\nAll Locations:\n";
                    for (size_t i = 0; i < locationNames.size(); ++i)
                    {
                        cout << i + 1 << ". " << locationNames[i] << "\n";
                    }
                    break;
                }

                case 3:
                    cout << "Exiting Manage Bins Menu.\n";
                    return;

                default:
                    cout << "Invalid choice. Please try again.\n";
            }
        }
    }
};

struct Complaint
{
    string customerName;
    string complaintDetails;
    string status;
};

class SmartCityWasteManagement
{
private:
    vector<Complaint> complaints;

    void saveComplaintToFile(const Complaint &complaint)
    {
        ofstream outFile("C:\\Users\\Lenovo\\Desktop\\DAA PROJECT\\complaints.txt", ios::app);
        if (outFile.is_open())
        {
            outFile << complaint.customerName << "," << complaint.complaintDetails << "," << complaint.status << "\n";
            outFile.close();
        }
        else
        {
            cerr << "Error: Unable to open file for saving complaints.\n";
        }
    }

    void loadComplaintsFromFile()
    {
        ifstream inFile("C:\\Users\\Lenovo\\Desktop\\DAA PROJECT\\complaints.txt");
        if (inFile.is_open())
        {
            string line;
            while (getline(inFile, line))
            {
                size_t pos1 = line.find(',');
                size_t pos2 = line.find(',', pos1 + 1);

                Complaint complaint;
                complaint.customerName = line.substr(0, pos1);
                complaint.complaintDetails = line.substr(pos1 + 1, pos2 - pos1 - 1);
                complaint.status = line.substr(pos2 + 1);

                complaints.push_back(complaint);
            }
            inFile.close();
        }
        else
        {
            cerr << "No past complaints found.\n";
        }
    }

public:
    SmartCityWasteManagement()
    {
        loadComplaintsFromFile();
    }

    void ViewComplaintsSummary()
    {
        if (complaints.empty())
        {
            cout << "No complaints found.\n";
            return;
        }

        cout << "-----------------------------------------\n";
        cout << "\nComplaints Summary:\n";
        cout << "-----------------------------------------\n";
        for (const auto &complaint : complaints) {
            cout << "Customer Name: " << complaint.customerName << "\n";
            cout << "Complaint Details: " << complaint.complaintDetails << "\n";
            cout << "Status: " << complaint.status << "\n";
            cout << "-----------------------------------------\n";
        }
    }

    void resolveComplaint()
    {
        if (complaints.empty())
        {
            cout << "No complaints found to resolve.\n";
            return;
        }

        cout << "\nEnter the index of the complaint to resolve (1 to " << complaints.size() << "): ";
        int index;
        cin >> index;

        if (index < 1 || index > complaints.size())
        {
            cout << "Invalid complaint index.\n";
            return;
        }

        complaints[index - 1].status = "Resolved";
        cout << "Complaint resolved successfully!\n";

        ofstream outFile("C:\\Users\\Lenovo\\Desktop\\DAA PROJECT\\complaints.txt");
        if (outFile.is_open()) {
            for (const auto &complaint : complaints)
            {
                outFile << complaint.customerName << "," << complaint.complaintDetails << "," << complaint.status << "\n";
            }
            outFile.close();
        }
        else
        {
            cerr << "Error: Unable to update complaints file.\n";
        }
    }

    void manageComplaints()
    {
        while (true)
            {
            int choice;
            cout << "\n----------------\n";
            cout << "\n  Complaints Management:\n";
            cout << "\n----------------\n";
            cout << "1. View Complaints Summary\n";
            cout << "2. Resolve Complaint\n";
            cout << "3. Exit\n";
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice)
             {
                case 1:
                    ViewComplaintsSummary();
                    break;

                case 2:
                    resolveComplaint();
                    break;

                case 3:
                    cout << "Exiting Complaints Management Menu.\n";
                    return;

                default:
                    cout << "Invalid choice. Please try again.\n";
            }
        }
    }

    void addComplaint(const Complaint &complaint)
    {
        complaints.push_back(complaint);
        saveComplaintToFile(complaint);
        cout << "Complaint added successfully!\n";
    }
};

// Class to represent a waste item
class WasteItems
{
public:
    int id;
    string type;
    float weight;

    // Constructor to initialize a waste item
    WasteItems(int id, string type, float weight) : id(id), type(type), weight(weight) {}

    // Convert waste item to string for file storage
    string toString() const
    {
        return to_string(id) + "," + type + "," + to_string(weight);
    }

    // Create a waste item from a string (read from file)
    static WasteItems fromString(const string& data)
    {
        size_t firstComma = data.find(',');
        size_t secondComma = data.find(',', firstComma + 1);

        int id = stoi(data.substr(0, firstComma));
        string type = data.substr(firstComma + 1, secondComma - firstComma - 1);
        float weight = stof(data.substr(secondComma + 1));

        return WasteItems(id, type, weight);
    }
};

// Class to manage waste items
class WasteManagementSystems
{
public:
    vector<WasteItem> waste_items;
    const string file_name = "C:\\Users\\Lenovo\\Desktop\\DAA PROJECT\\waste_items.txt";

    // Constructor loads waste items from file
    WasteManagementSystems()
    {
        loadFromFile();
    }

    // Destructor saves waste items to file
    ~WasteManagementSystems()
    {
        saveToFile();
    }

    // Add a new waste item to the system and save to file
    void addWasteItems(int id, string type, float weight)
    {
        WasteItem item(id, type, weight);
        waste_items.push_back(item);
        saveToFile();
    }

    // Sort waste items by their weight and display sorted weights
    void sortWasteItems()
    {
        vector<float> weights;
        for (const auto& item : waste_items)
        {
            weights.push_back(item.weight);
        }

        sort(weights.begin(), weights.end());

        cout << "Sorted Weights: ";
        for (const auto& weight : weights)
        {
            cout << weight << " ";
        }
        cout << endl;
    }

    // Display all waste items
    void displayItems()
    {
        for (const auto& item : waste_items)
        {
            cout << "ID: " << item.id << ", Type: " << item.type << ", Weight: " << item.weight << endl;
        }
    }

    // Search for a waste item by ID
    void searchWasteItem(int id)
    {
        for (const auto& item : waste_items)
        {
            if (item.id == id)
            {
                cout << "Found Waste Item - ID: " << item.id << ", Type: " << item.type << ", Weight: " << item.weight << endl;
                return;
            }
        }
        cout << "No Waste Item found with ID: " << id << endl;
    }

    // Delete a waste item by ID
    void deleteWasteItem(int id)
    {
        auto it = remove_if(waste_items.begin(), waste_items.end(), [id](const WasteItem& item)
        {
            return item.id == id;
        });

        if (it != waste_items.end())
        {
            waste_items.erase(it, waste_items.end());
            cout << "Waste Item with ID: " << id << " has been deleted.\n";
            saveToFile();
        }
        else
        {
            cout << "No Waste Item found with ID: " << id << endl;
        }
    }

    // Display the total weight of all waste items
    void displayTotalWeight()
    {
        float totalWeight = 0;
        for (const auto& item : waste_items)
        {
            totalWeight += item.weight;
        }
        cout << "Total Weight of All Waste Items: " << totalWeight << " kg" << endl;
    }

private:
    // Save waste items to file
    void saveToFile()
    {
        ofstream file(file_name, ios::trunc);
        if (!file.is_open())
        {
            cerr << "Failed to open file for writing: " << file_name << endl;
            return;
        }
        for (const auto& item : waste_items)
        {
            file << item.toString() << endl;
        }
        file.close();
    }

    // Load waste items from file
    void loadFromFile()
    {
        ifstream file(file_name);
        if (!file.is_open())
        {
            cerr << "Failed to open file for reading: " << file_name << endl;
            return;
        }
        string line;
        while (getline(file, line))
        {
            WasteItem item = WasteItem::fromString(line);
            waste_items.push_back(item);
        }
        file.close();
    }
};

// Customer class derived from User
class Customer : public User
{
public:
    Customer(string uname, string pass) : User(uname, pass) {}

    void menu() override
    {
        SmartCityWasteManagement scm;
        WasteManagementSystem wms;
        int choice = 0;
        while (choice != 5)
            {
            cout << "\n-------------------------------\n";
            cout << "\n          Customer Menu        \n";
            cout << "\n-------------------------------\n";
            cout << "1. Check Waste Bin Status\n";
            cout << "2. Report Issue\n";
            cout << "3. Manage Waste Items\n";
            cout << "4. Exit\n";
            cout << "Enter choice: ";
            cin >> choice;

            switch (choice)
            {
                case 1:
                cout << "Check Waste Bin Status\n";
                    Bins();
                    break;

                case 2:
                cout << "Report Issue\n";
                    reportIssue(scm);
                    break;

                case 3:
                    manageWasteItems(wms);
                    break;

                case 4:
                    cout << "Exiting Customer Menu...\n";
                    break;

                default:
                    cout << "Invalid choice. Try again.\n";
            }
        }
    }

    void reportIssue(SmartCityWasteManagement &scm)
    {
        string complaintDetails;
        cout << "Enter complaint details: ";
        cin.ignore();
        getline(cin, complaintDetails);

        Complaint complaint = {username, complaintDetails, "Open"};
        scm.addComplaint(complaint);
    }

    void Bins()
    {
        vector<string> locationNames;
        ifstream inFile("C:\\Users\\Lenovo\\Desktop\\DAA PROJECT\\locations.txt");
        string location;

        if (inFile.is_open())
        {
            while (getline(inFile, location))
            {
                locationNames.push_back(location);
            }
            inFile.close();
        }
        else
        {
            cout << "Error: Unable to open locations file.\n";
            return;
        }

        while (true)
            {
            int choice;
            cout << "\n----------------\n";
            cout << "\n      Bins:    \n";
            cout << "\n----------------\n";
            cout << "1. View nearby bins\n";
            cout << "2. Exit\n";
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice)
             {
                case 1:
                    {
                    string userLocation;
                    cout << "Enter your location to check nearby bins: ";
                    cin.ignore();
                    getline(cin, userLocation);

                    cout << "\nNearby Bins for location: " << userLocation << "\n";
                    cout << "---------------------------\n";
                    bool found = false;

                    for (const auto& loc : locationNames) {
                        if (loc.find(userLocation) != string::npos) {
                            cout << "- " << loc << "\n";
                            found = true;
                        }
                    }

                    if (!found)
                    {
                        cout << "No bins found nearby for the entered location.\n";
                    }
                    break;
                }

                case 2:
                    cout << "Exiting Manage Bins Menu.\n";
                    return;

                default:
                    cout << "Invalid choice. Please try again.\n";
            }
        }
    }

    void manageWasteItems(WasteManagementSystem &wms)
    {
        while (true) {
            cout << "\n-----------------------------\n";
            cout << "\nWaste Management System Menu:\n";
            cout << "\n-----------------------------\n";
            cout << "1. Display Waste Items\n";
            cout << "2. Sort Waste Items by Weight\n";
            cout << "3. Display Total Weight of All Waste Items\n";
            cout << "4. Exit\n";
            cout << "Enter your choice: ";

            int choice;
            cin >> choice;

            switch (choice)
            {
                case 1:
                    cout << "Displaying Waste Items:\n";
                    wms.displayItems();
                    break;

                case 2:
                    cout << "Sorting Waste Items by Weight:\n";
                    wms.sortWasteItems();
                    break;

                case 3:
                    cout << "Calculating Total Weight of All Waste Items:\n";
                    wms.displayTotalWeight();
                    break;

                case 4:
                    cout << "Exiting Waste Management System Menu...\n";
                    return;

                default:
                    cout << "Invalid choice. Please try again.\n";
            }
        }
    }
};

struct Complaints
{
    string customerName;
    string complaintDetails;
    string status;
};

class SmartCityWasteManagementsystem
{
private:
    vector<Complaint> complaints;

    void saveComplaintToFile(const Complaint &complaint)
    {
        ofstream outFile("C:\\Users\\Lenovo\\Desktop\\DAA PROJECT\\complaints.txt", ios::app);
        if (outFile.is_open())
        {
            outFile << complaint.customerName << "," << complaint.complaintDetails << "," << complaint.status << "\n";
            outFile.close();
        }

        else
        {
            cerr << "Error: Unable to open file for saving complaints.\n";
        }
    }

    void loadComplaintsFromFile()
    {
        ifstream inFile("C:\\Users\\Lenovo\\Desktop\\DAA PROJECT\\complaints.txt");
        if (inFile.is_open())
            {
            string line;
            while (getline(inFile, line))
            {
                size_t pos1 = line.find(',');
                size_t pos2 = line.find(',', pos1 + 1);

                Complaint complaint;
                complaint.customerName = line.substr(0, pos1);
                complaint.complaintDetails = line.substr(pos1 + 1, pos2 - pos1 - 1);
                complaint.status = line.substr(pos2 + 1);

                complaints.push_back(complaint);
            }
            inFile.close();
        }

        else
        {
            cerr << "No past complaints found.\n";
        }
    }

public:
    SmartCityWasteManagementsystem()
    {
        loadComplaintsFromFile();
    }

    void ViewComplaintsSummary()
    {
        if (complaints.empty())
        {
            cout << "No complaints found.\n";
            return;
        }

        cout << "\nComplaints Summary:\n";
        cout << "-----------------------------------------\n";
        for (const auto &complaint : complaints)
        {
            cout << "Customer Name: " << complaint.customerName << "\n";
            cout << "Complaint Details: " << complaint.complaintDetails << "\n";
            cout << "Status: " << complaint.status << "\n";
            cout << "-----------------------------------------\n";
        }
    }

    void resolveComplaint()
    {
        if (complaints.empty())
        {
            cout << "No complaints found to resolve.\n";
            return;
        }

        cout << "\nEnter the index of the complaint to resolve (1 to " << complaints.size() << "): ";
        int index;
        cin >> index;

        if (index < 1 || index > complaints.size())
        {
            cout << "Invalid complaint index.\n";
            return;
        }

        complaints[index - 1].status = "Resolved";
        cout << "Complaint resolved successfully!\n";

        ofstream outFile("C:\\Users\\Lenovo\\Desktop\\DAA PROJECT\\complaints.txt");
        if (outFile.is_open())
        {
            for (const auto &complaint : complaints)
            {
                outFile << complaint.customerName << "," << complaint.complaintDetails << "," << complaint.status << "\n";
            }
            outFile.close();
        }
        else
        {
            cerr << "Error: Unable to update complaints file.\n";
        }
    }

    void manageComplaints()
    {
        while (true)
            {
            int choice;
            cout << "\n----------------\n";
            cout << "\n  Complaints Management:\n";
            cout << "\n----------------\n";
            cout << "1. View Complaints Summary\n";
            cout << "2. Resolve Complaint\n";
            cout << "3. Exit\n";
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice)
            {
                case 1:
                    cout << "View Complaints Summary\n";
                    ViewComplaintsSummary();
                    break;

                case 2:
                    cout << "Resolve Complaint\n";
                    resolveComplaint();
                    break;

                case 3:
                    cout << "Exiting Complaints Management Menu.\n";
                    return;

                default:
                    cout << "Invalid choice. Please try again.\n";
            }
        }
    }

    void addComplaint(const Complaint &complaint)
    {
        complaints.push_back(complaint);
        saveComplaintToFile(complaint);
        cout << "Complaint added successfully!\n";
    }
};

class Task
{
public:
    int id;
    string description;
    string status;

    Task(int id, string description, string status) : id(id), description(description), status(status) {}

    string toString() const
    {
        return to_string(id) + "," + description + "," + status;
    }

    static Task fromString(const string& data)
    {
        size_t firstComma = data.find(',');
        size_t secondComma = data.find(',', firstComma + 1);

        int id = stoi(data.substr(0, firstComma));
        string description = data.substr(firstComma + 1, secondComma - firstComma - 1);
        string status = data.substr(secondComma + 1);

        return Task(id, description, status);
    }
};


class Tasks
{
public:
    int id;
    string description;
    string status;

    Tasks(int id, string description, string status) : id(id), description(description), status(status) {}

    string toString() const
    {
        return to_string(id) + "," + description + "," + status;
    }

    static Task fromString(const string& str)
    {
        size_t pos1 = str.find(',');
        size_t pos2 = str.find(',', pos1 + 1);
        int id = stoi(str.substr(0, pos1));
        string description = str.substr(pos1 + 1, pos2 - pos1 - 1);
        string status = str.substr(pos2 + 1);
        return Task(id, description, status);
    }
};

class TaskManagementSystem
{
public:
    vector<Task> tasks;
    const string file_name;

    TaskManagementSystem() : file_name("C:\\Users\\Lenovo\\Desktop\\DAA PROJECT\\task.txt")
    {
        loadFromFile();
    }

    TaskManagementSystem(const string& file_name) : file_name(file_name)
    {
        loadFromFile();
    }

    void addTask(int id, string description, string status)
    {
        Task task(id, description, status);
        tasks.push_back(task);
        saveToFile();
    }

    void displayTasks()
    {
        if (tasks.empty())
        {
            cout << "No tasks found.\n";
            return;
        }

        cout << "\nTasks Summary:\n";
        cout << "-----------------------------------------\n";
        int totalTasks = tasks.size();
        int pendingTasks = count_if(tasks.begin(), tasks.end(), [](const Task& task) { return task.status == "Pending"; });
        int completedTasks = totalTasks - pendingTasks;

        cout << "Total tasks: " << totalTasks << "\n";
        cout << "Pending tasks: " << pendingTasks << "\n";
        cout << "Completed tasks: " << completedTasks << "\n";
        cout << "-----------------------------------------\n";

        cout << "Filter tasks by status (Pending/Completed/All): ";
        string filterStatus;
        cin >> filterStatus;

        for (const auto& task : tasks)
        {
            if (filterStatus == "All" || filterStatus == task.status)
            {
                cout << "ID: " << task.id << ", Description: " << task.description << ", Status: " << task.status << endl;
            }
        }
    }

    void searchTask(int id)
    {
        for (const auto& task : tasks)
        {
            if (task.id == id)
            {
                cout << "Found Task - ID: " << task.id << ", Description: " << task.description << ", Status: " << task.status << endl;
                return;
            }
        }
        cout << "No Task found with ID: " << id << endl;
    }

    void updateTaskStatus(int id, string newStatus)
    {
        for (auto& task : tasks)
        {
            if (task.id == id)
            {
                task.status = newStatus;
                saveToFile();
                cout << "Task status updated successfully!\n";
                return;
            }
        }
        cout << "No Task found with ID: " << id << endl;
    }

    void deleteTask(int id)
    {
        auto it = remove_if(tasks.begin(), tasks.end(), [id](const Task& task)
        {
            return task.id == id;
        });

        if (it != tasks.end())
        {
            tasks.erase(it, tasks.end());
            cout << "Task with ID: " << id << " has been deleted.\n";
            saveToFile();
        }
        else
        {
            cout << "No Task found with ID: " << id << endl;
        }
    }

private:
    void saveToFile()
    {
        ofstream file(file_name, ios::trunc);
        if (!file.is_open())
        {
            cerr << "Failed to open file for writing: " << file_name << endl;
            return;
        }
        for (const auto& task : tasks)
        {
            file << task.toString() << endl;
        }
        file.close();
    }

    void loadFromFile()
    {
        ifstream file(file_name);
        if (!file.is_open())
        {
            cerr << "Failed to open file for reading: " << file_name << endl;
            return;
        }
        string line;
        while (getline(file, line))
        {
            Task task = Task::fromString(line);
            tasks.push_back(task);
        }
        file.close();
    }
};

struct Edge
{
    string u, v;
    int weight;
};

class Graph
{
public:
    unordered_map<string, vector<pair<string, int>>> adjList;

    void addEdge(const string& u, const string& v, int weight)
    {
        adjList[u].emplace_back(v, weight);
        adjList[v].emplace_back(u, weight);
    }

    unordered_map<string, int> dijkstra(const string& src)
    {
        unordered_map<string, int> dist;
        for (const auto& pair : adjList)
        {
            dist[pair.first] = INT_MAX;
        }
        priority_queue<pair<int, string>, vector<pair<int, string>>, greater<pair<int, string>>> pq;

        dist[src] = 0;
        pq.emplace(0, src);

        while (!pq.empty())
        {
            string u = pq.top().second;
            pq.pop();

            for (const auto& neighbor : adjList[u])
            {
                string v = neighbor.first;
                int weight = neighbor.second;

                if (dist[u] + weight < dist[v])
                {
                    dist[v] = dist[u] + weight;
                    pq.emplace(dist[v], v);
                }
            }
        }

        return dist;
    }

    int findShortestPath(const string& src, const string& dest)
    {
        unordered_map<string, int> dist = dijkstra(src);
        return dist[dest];
    }
};


class Worker : public User
{

public:
    Worker(string uname, string pass) : User(uname, pass) {}

    void menu() override
    {
        TaskManagementSystem tms("C:\\Users\\Lenovo\\Desktop\\DAA PROJECT\\task.txt");
        // Pass the required argument to the constructor

        while (true)
        {
            cout << "\n-------------------------------\n";
            cout << "\n           Worker Menu         \n";
            cout << "\n-------------------------------\n";
            cout << "1. View Assigned Tasks\n";
            cout << "2. Find Shortest Path\n";
            cout << "3. Exit\n";
            cout << "Enter choice: ";
            int choice;
            cin >> choice;

            switch (choice)
            {
                case 1:
                    // Call to displayTasks method
                    cout << "View Assigned Tasks\n";
                    tms.displayTasks(); // Call to displayTasks method
                    break;

                case 2:
                    // Call the findShortestPath method
                    cout << "Find Shortest Path\n";
                    findShortestPath();
                    break;

                case 3:
                    // Exit the menu loop
                    cout << "Exiting Worker Menu...\n";
                    return;

                default:
                    cout << "Invalid choice. Try again.\n";
            }
        }
    }

    // to find the shorted path
    void findShortestPath()
    {
        string src, dest;
        cout << "Enter source location: ";
        cin >> src;
        cout << "Enter destination location: ";
        cin >> dest;

        // Check if the source and destination are the same
        if (src == dest)
        {
            cout << "The source and destination are the same. The shortest path is 0.\n";
            return;
        }

        ifstream inFile("C:\\Users\\Lenovo\\Desktop\\DAA PROJECT\\graph.txt");
        if (!inFile.is_open())
        {
            cerr << "Error: Unable to open graph file.\n";
            return;
        }

        Graph graph;
        string u, v;
        int weight;

        // Read graph data from the file
        while (inFile >> u >> v >> weight)
        {
            graph.addEdge(u, v, weight);
        }

        inFile.close();

        // Find the shortest path
        int shortestPath = graph.findShortestPath(src, dest);
        if (shortestPath == INT_MAX)

        {
            cout << "There is no path between the source and destination.\n";
        }

        else
        {
            cout << "The shortest path from " << src << " to " << dest << " is " << shortestPath << "\n";
        }
    }
};

// Struct to hold user credentials
struct UserCredentials
{
    string username;
    string password;
};

// Vectors to store credentials for different roles
vector<UserCredentials> adminCredentials;
vector<UserCredentials> customerCredentials;
vector<UserCredentials> workerCredentials;

// Function to load credentials from files
void loadCredentials()
{
    ifstream adminFile("C:\\Users\\Lenovo\\Desktop\\DAA PROJECT\\admin.txt");
    ifstream customerFile("C:\\Users\\Lenovo\\Desktop\\DAA PROJECT\\customer.txt");
    ifstream workerFile("C:\\Users\\Lenovo\\Desktop\\DAA PROJECT\\worker.txt");

    string username, password;

    while (adminFile >> username >> password)
    {
        adminCredentials.push_back({username, password});
    }

    while (customerFile >> username >> password)
    {
        customerCredentials.push_back({username, password});
    }

    while (workerFile >> username >> password)
    {
        workerCredentials.push_back({username, password});
    }
}

// Function to save credentials to files
void saveCredentials()
{
    ofstream adminFile("C:\\Users\\Lenovo\\Desktop\\DAA PROJECT\\admin.txt");
    for (const auto& admin : adminCredentials)
    {
        adminFile << admin.username << " " << admin.password << endl;
    }

    ofstream customerFile("C:\\Users\\Lenovo\\Desktop\\DAA PROJECT\\customer.txt");
    for (const auto& customer : customerCredentials)
    {
        customerFile << customer.username << " " << customer.password << endl;
    }

    ofstream workerFile("C:\\Users\\Lenovo\\Desktop\\DAA PROJECT\\worker.txt");
    for (const auto& worker : workerCredentials)
    {
        workerFile << worker.username << " " << worker.password << endl;
    }
}

// Function to register a new user
void registerUser()
{
    string role;
    cout << "Register as Admin, Customer, or Worker? (Enter 'Admin', 'Customer', or 'Worker'): ";
    cin >> role;

    string username, password;
    if (role == "Admin" || role == "admin")
        {
        cout << "Enter Admin Username: ";
        cin >> username;
        cout << "Enter Admin Password: ";
        cin >> password;

        for (const auto& admin : adminCredentials)
        {
            if (admin.username == username)
            {
                cout << "Admin Username already exists. Try a different one.\n";
                return;
            }
        }

        adminCredentials.push_back({username, password});
        saveCredentials();
        cout << "Admin registered successfully!\n";

    }

    else if (role == "Customer" || role == "customer")
        {
        cout << "Enter Customer Username: ";
        cin >> username;
        cout << "Enter Customer Password: ";
        cin >> password;

        for (const auto& customer : customerCredentials)
        {
            if (customer.username == username)
            {
                cout << "Customer Username already exists. Try a different one.\n";
                return;
            }
        }

        customerCredentials.push_back({username, password});
        saveCredentials();
        cout << "Customer registered successfully!\n";

    }

    else if (role == "Worker" || role == "worker")
        {
        cout << "Enter Worker Username: ";
        cin >> username;
        cout << "Enter Worker Password: ";
        cin >> password;

        for (const auto& worker : workerCredentials)
        {
            if (worker.username == username)
            {
                cout << "Worker Username already exists. Try a different one.\n";
                return;
            }
        }

        workerCredentials.push_back({username, password});
        saveCredentials();
        cout << "Worker registered successfully!\n";

    }

    else
    {
        cout << "Invalid role. Please try again.\n";
        registerUser();
    }
}

// Function to handle user login
void login()
{
    string role;
    cout << "Are you logging in as Admin, Customer, or Worker? (Enter 'Admin', 'Customer', or 'Worker'): ";
    cin >> role;

    string inputUsername, inputPassword;

    if (role == "Admin" || role == "admin")
        {
        cout << "Enter Admin Username: ";
        cin >> inputUsername;
        cout << "Enter Admin Password: ";
        cin >> inputPassword;

        for (const auto& admin : adminCredentials)
        {
            if (admin.username == inputUsername && admin.password == inputPassword)
            {
                cout << "Admin Login Successful!\n";
                Admin(inputUsername, inputPassword).menu();
                return;
            }
        }
        cout << "Invalid Admin Username or Password.\n";

    }

    else if (role == "Customer" || role == "customer")
        {
        cout << "Enter Customer Username: ";
        cin >> inputUsername;
        cout << "Enter Customer Password: ";
        cin >> inputPassword;

        for (const auto& customer : customerCredentials)
        {
            if (customer.username == inputUsername && customer.password == inputPassword)
            {
                cout << "Customer Login Successful!\n";
                Customer(inputUsername, inputPassword).menu();
                return;
            }
        }
        cout << "Invalid Customer Username or Password.\n";

    }

    else if (role == "Worker" || role == "worker")
        {
        cout << "Enter Worker Username: ";
        cin >> inputUsername;
        cout << "Enter Worker Password: ";
        cin >> inputPassword;

        for (const auto& worker : workerCredentials)
            {
            if (worker.username == inputUsername && worker.password == inputPassword)
            {
                cout << "Worker Login Successful!\n";
                Worker(inputUsername, inputPassword).menu();
                return;
            }
        }
        cout << "Invalid Worker Username or Password.\n";

    }

    else
    {
        cout << "Invalid role selected. Please try again.\n";
        login();
    }
}

// Simulate generating a password reset token
std::string generateResetToken()
{

    return "abc123xyz";
}

// Validate if the username exists
bool validateUsername(const std::string& username)
{

    // Check if the username exists in adminCredentials
    for (const auto &user : adminCredentials)
    {
        if (user.username == username)
        {
            return true;
        }
    }

    // Check if the username exists in customerCredentials
    for (const auto &user : customerCredentials)
    {
        if (user.username == username)
        {
            return true;
        }
    }

    // Check if the username exists in workerCredentials
    for (const auto &user : workerCredentials)
    {
        if (user.username == username)
        {
            return true;
        }
    }

    // Return false if username is not found
    return false;
}

// Function to validate the reset token provided by the user
bool validateResetToken(const std::string& token)
{

// Check if the token matches the predefined valid token
    return token == "abc123xyz";
}

// Function to reset a user's password
void resetPassword()
{
    std::string username, newPassword, token;

    // Prompt user for their username
    std::cout << "Enter your username to reset your password: ";
    std::cin >> username;

    // Validate the entered username
    if (!validateUsername(username))
    {
        std::cout << "Username not found!" << std::endl;
        return;
    }

    // Generate a reset token (simulated here for simplicity)
    std::string generatedToken = generateResetToken();
    std::cout << "Password reset token (simulated email): " << generatedToken << std::endl;

    // Prompt user to enter the received reset token
    std::cout << "Enter the reset token you received: ";
    std::cin >> token;

    // Validate the entered token
    if (!validateResetToken(token))
    {
        std::cout << "Invalid token!" << std::endl;
        return;
    }

    // Prompt user to enter a new password
    std::cout << "Enter your new password: ";
    std::cin >> newPassword;

    // Update the password in adminCredentials if the username matches
    for (auto &user : adminCredentials)
    {
        if (user.username == username)
        {
            user.password = newPassword;
            saveCredentials();
            std::cout << "Password reset successfully!" << std::endl;
            return;
        }
    }

    // Update the password in customerCredentials if the username matches
    for (auto &user : customerCredentials)
    {
        if (user.username == username)
        {
            user.password = newPassword;
            saveCredentials();
            std::cout << "Password reset successfully!" << std::endl;
            return;
        }
    }

    // Update the password in workerCredentials if the username matches
    for (auto &user : workerCredentials)
    {
        if (user.username == username)
        {
            user.password = newPassword;
            saveCredentials();
            std::cout << "Password reset successfully!" << std::endl;
            return;
        }
    }

    // If no matching username is found, display an error
    std::cout << "An error occurred. Please try again." << std::endl;
}

// Function to handle the waste management system menu
void wasteManagementSystem()
{
    WasteManagementSystem wms;

    while (true)
    {

        // Display menu options
        cout << "\n-----------------------------\n";
        cout << "\nWaste Management System Menu:\n";
        cout << "\n-----------------------------\n";
        cout << "1. Add Waste Item\n";
        cout << "2. Display Waste Items\n";
        cout << "3. Sort Waste Items by Weight\n";
        cout << "4. Search for a Waste Item by ID\n";
        cout << "5. Delete a Waste Item by ID\n";
        cout << "6. Display Total Weight of All Waste Items\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;

        switch (choice)
        {

            case 1:
            {
                // Add a new waste item
                int id;
                string type;
                float weight;
                cout << "Enter Waste Item ID: ";
                cin >> id;
                cin.ignore();
                cout << "Enter Waste Item Type: ";
                getline(cin, type);
                cout << "Enter Waste Item Weight: ";
                cin >> weight;
                wms.addWasteItem(id, type, weight);
                break;
            }

            case 2:
                // Display all waste items
                cout << "Waste Items:\n";
                wms.displayItems();
                break;

            case 3:
                // Sort waste items by weight
                cout << "Sorting Waste Items by Weight:\n";
                wms.sortWasteItems();
                break;

            case 4:
            {
                // Search for a waste item by ID
                int id;
                cout << "Enter Waste Item ID to Search: ";
                cin >> id;
                wms.searchWasteItem(id);
                break;
            }

            case 5:
            {
                // Delete a waste item by ID
                int id;
                cout << "Enter Waste Item ID to Delete: ";
                cin >> id;
                wms.deleteWasteItem(id);
                break;
            }

            case 6:
                // Display total weight of all waste items
                cout << "Calculating Total Weight of All Waste Items:\n";
                wms.displayTotalWeight();
                break;

            case 7:
                // Exit the system
                cout << "Exiting...\n";
                return;

            default:
                // Handle invalid input
                cout << "Invalid choice. Please try again.\n";
        }
    }
}

// Main function
int main()
{
    // Load credentials from storage
    loadCredentials();

    int choice;

    while (true)
    {
        // Display the main menu
        cout << "\n----------------------------------------------\n";
        cout << "\n      Smart City Waste Management System      \n";
        cout << "\n----------------------------------------------\n";
        cout << "1 - Register\n";
        cout << "2 - Login\n";
        cout << "3 - Reset Password\n";
        cout << "4 - Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
                // Register a new user
                registerUser();
                break;

            case 2:
                // Log in as an existing user
                login();
                break;

            case 3:
                // Reset password
                resetPassword();
                break;

            case 4:
                // Exit the system
                cout << "Exiting system. Goodbye!\n";
                return 0;

            default:
                // Handle invalid input
                cout << "Invalid choice. Try again.\n";
        }
    }

    return 0;
}
