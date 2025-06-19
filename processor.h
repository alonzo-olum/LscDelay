#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <vector>
#include <map>

#include "inventory.h"

using namespace std;

class Processor {
private:
	vector<Inventory*> inventories;
	map<string, vector<string>> processing_logs;
public:
	void add_inventory(Inventory* inventory);
	void process_data_with_delay(int delay_ms);
	void generate_report() const;
};

#endif
