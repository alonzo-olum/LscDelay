#include <thread>
#include <chrono>
#include <iostream>

#include "processor.h"
#include "delay_op.h"

using namespace std;

void Processor::add_inventory(Inventory* inventory) {
	inventories.push_back(inventory);
	processing_logs["addition"].push_back("added inventory time: " + to_string(time(nullptr)));
}

void Processor::process_data_with_delay(int delay_ms) {
	DelayedExecutor executor;

	for (size_t i = 0; i < inventory.size(); ++i) {
		executor.add_task([this, i]() {
				cout << "processing inventory " << i << endl;
				// simulate processing, w/ exponential backoff
				this_thread::sleep_for(chrono::miliseconds(100));
				}, delay_ms * (i + 1));
	}
	thread executor_thread(&DelayedExecutor::execute_tasks, &executor);
	executor_thread.join();
}

void Processor::generate_report() const {
	cout << "==== data processing report ===\n";
	cout << "inventories: " << inventories.size() << endl;

	for (const auto& log : processing_logs) {
		cout << log.first << "operations: " << log.second.size() << endl;
	}
}
