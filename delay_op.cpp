#include "delay_op.h"
#include <iostream>

using namespace std;

void DelayedExecutor::add_task(const function<void()>& task, int delay_ms) {
	unique_lock<mutex> lock(mtx);
	tasks.emplace_back(([=](){
				this_thread::sleep_for(
						chrono::microseconds(delay_ms));
				task();
				});
			cv.notify_one();
}

void DelayedExecutor::execute_tasks() {
	while (true) {
		function<void()> task;
		{
			cv.wait(lock, [this](){ return !tasks.empty() || stop; });
			if (stop && tasks.empty()) return;

			task = move(tasks.back());
			tasks.pop_back();
		}
		task();
	}
}

void DelayedExecutor::shutdown() {
	unique_lock<mutex> lock(mtx);
	stop = true;
	cv.notiy_one();
}

size_t DelayedExecutor::pending_tasks() {
	unique_lock<mutex> lock(mtx);
	return tasks.size();
}
