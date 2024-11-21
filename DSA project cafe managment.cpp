#include<iostream>
#include <fstream>
#include <sstream> 
using namespace std;
class MenuItem {
public:
	int id;
	string name;
	float price;
	MenuItem* next;
public:
	MenuItem(int id, const string& name, float price) :id(id), name(name), price(price), next(nullptr) {

	}

};
class cafeManagment {
private:
	MenuItem* head;
	const string fileName = "menu.txt";
public:
	cafeManagment() :head(nullptr) {
		LoadFromFile();

	}
	~cafeManagment() {
		SaveToFile();
		clearMenu();
	}
	void AddMenu(int id, const string& name, float price) {
		MenuItem* newItem = new MenuItem(id, name, price);
		if (head == nullptr) {
			head = newItem;

		}
		else {
			MenuItem* temp = head;
			while (temp->next != nullptr) {
				temp = temp->next;
			}
			temp->next = newItem;
		}
		cout << " Item Added " << name << endl;
		SaveToFile();

	}
	void DisplayMenu() {
		if (head == nullptr) {
			cout << "Menu List Is Empty" << endl;
			return;
		}
		cout << "------salman's Cafe Menu------" << endl;
		MenuItem* temp = head;
		while (temp != nullptr) {
			cout << "ID: " << temp->id << endl << "NAME " << temp->name << endl << "PRICE: " << temp->price << endl;
			temp = temp->next;
		}
	}
	void PlaceOrder(int id) {
		if (head == nullptr) {
			cout << "Menu is Empty no item to order" << endl;
			return;
		}
		MenuItem* temp = head;
		while (temp != nullptr) {
			if (temp->id == id) {
				cout << "order placed for " << temp->name << " ($" << temp->price << ")" << endl;
				return;
			}
			temp = temp->next;
		}

		cout << "item with id" << id << "not found" << endl;

	}
	void updateMenu(int id, const string& newName, float newPrice) {
		if (head == nullptr) {
			cout << "menu is Empty" << endl;
			return;
		}
		MenuItem* temp = head;
		while (temp != nullptr) {
			if (temp->id == id) {
				temp->name = newName;
				temp->price = newPrice;
				cout << "item with" << id << "updated to" << newName << " | $" << newPrice << endl;
				return;
			}
			temp = temp->next;

		}
		cout << "item with id" << id << "not found" << endl;
		SaveToFile();
	}
	void clearMenu() {
		while (head != nullptr) {
			MenuItem* temp = head;
			head = head->next;
			delete temp;
		}
		cout << "Menu is cleared" << endl;
		SaveToFile();
	}
	void SaveToFile() {
		ofstream file(fileName);
		if (!file) {
			cout << "Error: Could not open file to save!" << endl;
			return;
		}
		MenuItem* temp = head;
		while (temp != nullptr) {
			file << temp->id << "," << temp->name << "," << temp->price << endl;
			temp = temp->next;
		}
		file.close();
	}

	void LoadFromFile() {
		ifstream file(fileName);
		if (!file) {
			cout << "No existing menu file found. Starting fresh." << endl;
			return;
		}
		string line;
		while (getline(file, line)) {
			stringstream ss(line);
			string idStr, name, priceStr;
			getline(ss, idStr, ',');
			getline(ss, name, ',');
			getline(ss, priceStr, ',');

			int id = stoi(idStr);
			float price = stof(priceStr);
			AddMenu(id, name, price);
		}
		file.close();
	}
};
int main() {
	cafeManagment c;
	int choice;
	int id;
	string name;
	float price;

	do {
		cout << "=============================================" << endl;
		cout << "         WELCOME TO SALMAN'S CAFE            " << endl;
		cout << "=============================================" << endl;
		cout << "|      Please<< select an option below:     |" << endl;
		cout << "|-------------------------------------------|" << endl;
		cout << "|  1. Add Items to the Menu                 |" << endl;
		cout << "|  2. Display Menu                          |" << endl;
		cout << "|  3. Place an Order                        |" << endl;
		cout << "|  4. Update Menu                           |" << endl;
		cout << "|  5. Clear Menu                            |" << endl;
		cout << "|  6.Exit salman's Cafe                     |" << endl;
		cout << "=============================================" << endl;
		cout << "Enter your choice: ";
		cin >> choice;

		switch (choice) {
		case 1:
			cout << "Enter item id" << endl;
			cin >> id;

			cout << "Enter item name" << endl;
			cin >> name;

			cout << "Enter item price" << endl;
			cin >> price;
			c.AddMenu(id, name, price);
			break;

		case 2:
			c.DisplayMenu();
			break;

		case 3:
			cout << "Enter item  id to place order" << endl;
			cin >> id;
			c.PlaceOrder(id);
			break;

		case 4:
			cout << "Enter id to update item" << endl;
			cin >> id;
			cout << "Enter new Name to update" << endl;
			cin >> name;
			cout << "Enter new Pricw to update" << endl;
			cin >> price;
			c.updateMenu(id, name, price);
			break;
		case 5:
			c.clearMenu();
			break;
		case 6:
			cout << "Exiting the salman's cafe.Thank You" << endl;
			break;

		default:

			cout << "Invalid chouce please try again" << endl;

		}
	}

	while (choice != 6);
	return 0;



}