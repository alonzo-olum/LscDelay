#ifndef DELAY_OP_H
#define DELAY_OP_H

#include <vector>
#include <functional>
#include <chrono>
#include <thread>
#include <mutex>
#include <condition_variable>

#include<cstddef>

using namespace std;

class DelayedExecutor {
private:
	mutex mtx;
	vector<thread> tasks;
	condition_variable cv;
	bool stop = false;
public:
	void add_task(const function<void()>& task, int delay_ms);
	void execute_tasks();
	void shutdown();
	size_t pending_tasks() const;
};

#endif
