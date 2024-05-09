#include <iostream>
#include <deque>

struct Task {
    std::string name;

    Task(const std::string &name) : name{name} {};

    ~Task() = default;

    bool operator==(const Task &rhs) const {
        return this->name == rhs.name;
    }
};

struct TaskQueue {
private:
    int queue_size;
    int queue_max_size;
    std::deque<Task> task_queue;
public:
    TaskQueue() = default;

    TaskQueue(int max_size = 5, const std::deque<Task> &queue = {}) : queue_size{0}, queue_max_size{max_size},
                                                                      task_queue{queue} {};

    ~TaskQueue() = default;

    [[nodiscard]] std::deque<Task> return_queue() const {
        return task_queue;
    }

    void push_front(const Task &task) {
        for (auto it = task_queue.begin(); it != task_queue.end(); it++) {
            if (*it == task) {
                task_queue.erase(it);
                queue_size--;
                break;
            }
        }
        if (queue_size < queue_max_size) {
            task_queue.push_front(task);
            queue_size++;
        } else if (queue_size >= queue_max_size) {
            pop_back();
            push_front(task);
        }
    }

    void pop_back() {
        task_queue.pop_back();
        queue_size--;
    }
};

int main() {
    TaskQueue taskQueue{4};
    auto show = [&taskQueue] {
        std::cout << "Queue:" << std::endl;
        for (auto &t: taskQueue.return_queue()) { std::cout << t.name << std::endl; }
    };
    taskQueue.push_front({"new1"});
    show();
    taskQueue.push_front({"new2"});
    show();
    taskQueue.push_front({"new3"});
    show();
    taskQueue.push_front({"new2"});
    show();
    taskQueue.push_front({"new1"});
    show();
    taskQueue.push_front({"new4"});
    show();
    taskQueue.push_front({"new3"});
    show();
    taskQueue.push_front({"new5"});
    show();
}