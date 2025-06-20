#include <sstream>
#include <iostream>

#include "inventory.h"

using namespace std;

Item::Item(const string& id, const string& name, double price)
	: id(id), name(name), price(price) {}

string Item::get_description() const {
	ostringstream oss;
	oss << "ID: " << id << endl;
	return oss.str();
}

DigitalItem::DigitalItem(const string& id, const string& name, double price, const string& license):
	Item(id, name, price), license_key(license) {}

string DigitalItem::get_description() const {
	ostringstream oss;
	oss << Item::get_description() << ", License: " << license_key;
	return oss.str();
}

Inventory::~Inventory() {
	for (auto& pair : items) {
		delete pair;
	}
}

void Inventory::add_item(Item* item, const string& category) {
	items[item->get_id()] = item;
	categories.insert(category);
	log_action("Added Item: " + item->get_id());
}

void Inventory::remove_item(const string& id) {
	auto item = items.find(id);
	if (item != items.end()) {
		delete item->second;
		items.erase(item);
		log_action("Removed Item: " + id);
	}
}

Item* Inventory::find_item(const string& id) const {
	auto item = items.find(id);
	return item != items.end() ? item : nullptr;
}

void Inventory::add_category(const string& category) {
	categories.insert(category);
}

void Inventory::log_action(const string& action) {
	inventory_log.push_back(action);
}

