#include <iostream>
#include <string>
#include <map>

using namespace std;

class Drink {
private:
	string name;
	float price;
	size_t _count;
public:
	Drink() {
		name = "";
		price = 0;
		_count = 0;
	}
	Drink(const string& Name, const float& Price, const size_t& Count) {
		name = Name;
		price = Price;
		_count = Count;
	}
	string GetName() const {
		return name;
	}
	float GetPrice() const {
		return price;
	}
	size_t GetCount() const {
		return _count;
	}
};

class Visitor {
private:
	int ID;
	string name;
	string email;
public:
	Visitor() {
		ID = 0;
		name = "";
		email = "";
	}
	Visitor(const int& id, const string& Name, const string& Email) {
		ID = id;
		name = Name;
		email = Email;
	}
	int GetID() const {
		return ID;
	}
	string GetName() const {
		return name;
	}
	string GetEmail() const {
		return email;
	}
};

class Bar {
private:
	map<Visitor, Drink> Order;
public:
	void order(const Visitor& v, const Drink& d) {
		Order[v] = d;
	}
};

int main() {
	return 0;
}