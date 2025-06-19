#ifndef INVENTORY_H
#define INVENTORY_H

#include <string>
#include <map>
#include <set>
#include <vector>

using namespace std;

class Item {
protected:
	string id;
	string name;
	double price;
public:
	Item(const string& id, const string& name, double price);
	virtual ~Item() = default;
	virtual string get_description() const;
	string get_id() const;
	double get_price() const;
	
	void set_price(double new_price);
};

class DigitalItem: public Item {
private:
	string license_key;

public:
	DigitalItem(const string& id, const string& name, double price, const string license);
	string get_description() const override;
};

class Inventory {
private:
	map<string, Item> items;
	set<string> categories;
	vector<string> inventory_log;  
public:
	~Inventory();
	
	void add_item(Item* item, const string& category);
	void remove_item(const string& id) const;
	Item* find_item(const string& id) const;
	void add_category(const string& category);
	const set<string>& get_categories() const;
	void log_action(const string& action);
	const vector<string>& get_log() const;
};

#endif
