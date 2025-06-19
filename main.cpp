#include <iostream>
#include <memory>
#include <vector>

#include "inventory.h"
#include "processor.h"
#include "delay_op.h"

using namespace std;

void demo_delay_op() {
	DelayedExecutor executor;

	for (int i = 0; i < 5; ++i) {
		executor.add_task([]() {
				cout << "delay task " << i << endl;
				}, 1000 * (i + 1));
	}

	thread executor_thread(&DelayedExecutor::execute_tasks, &executor);
	executor_thread.join();
}

void demo_inventory() {
	Inventory inventory;
	inventory.add_item(new Item("001", "laptop", 99.99), "Electronics");
	inventory.add_item(new DigitalItem("002", "license", 59.99, "ADS-123"), "software");

	auto item = inventory.find_item("001");
	if (item) {
		cout << "found item: " << item->get_description() << endl;
	}
}

void demo_processor() {
	Processor processor;
	Inventory inv_one, inv_two;

	inv_one.add_item(new Item("101", "monitor", 199.99), "Electronics");
	inv_two.add_item(new Item("201", "keyboard", 49.99), "Electronics");

	processor.add_inventory(&inv_one);
	processor.add_inventory(&inv_two);

	processor.process_data_with_delay(500);
	processor.generate_report();
}

int main() {
	cout << "=== Delayed Ops ====" << endl;
	demo_delay_op();
	cout << "=== Inventory demo ===" << endl;
	demo_inventory();
	cout << "=== Processor demo ===" << endl;
	demo_processor();
	return 0;
}
