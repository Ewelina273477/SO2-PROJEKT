#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <queue>
#include <chrono>

using namespace std;

queue<int> requestQueue;  // FIFO queue for philosophers waiting to eat

class DiningPhilosophers {
private:
    int numPhilosophers;
    vector<mutex> forks; // Mutexes representing forks
    mutex queueMutex; // Mutex for protecting request queue
    mutex printMutex; // Mutex for synchronized console output
    int eatingCount = 0; // Number of philosophers currently eating
    bool stopFlag = false; // Flag to stop execution
    mutex waiterMutex; // Waiter manages access to eating

public:
    DiningPhilosophers(int n) : numPhilosophers(n), forks(n) {}

    void philosopher(int id) {
        while (!stopFlag) {
            think(id);
            eat(id);
        }
    }

    void think(int id) {
        {
            lock_guard<mutex> lock(printMutex);
            cout << "Philosopher " << (id+1) << " is thinking..." << endl;
        }
        this_thread::sleep_for(chrono::milliseconds(1000));
    }

    void eat(int id) {
        int left = id;
        int right = (id + 1) % numPhilosophers;

        // Ensure that philosophers pick up forks in an alternating order to prevent deadlocks
        if (id % 2 == 0) swap(left, right);

        {
            lock_guard<mutex> lock(queueMutex);
            requestQueue.push(id);
        }

        // Waiter manages philosophers' access to eating
        while (true) {
            lock_guard<mutex> lock(waiterMutex);
            if (!requestQueue.empty() && requestQueue.front() == id && eatingCount < numPhilosophers - 1) {
                requestQueue.pop();
                eatingCount++;
                break;
            }
        }
        // Pick up forks
        forks[left].lock();
        forks[right].lock();

        {
            lock_guard<mutex> printLock(printMutex);
            cout << "Philosopher " << (id+1) << " is eating..." << endl;
        }
        this_thread::sleep_for(chrono::milliseconds(1000));

        {
            lock_guard<mutex> printLock(printMutex);
            cout << "Philosopher " << (id+1) << " puts down the fork..." << endl;
        }
        // Release forks
        forks[left].unlock();
        forks[right].unlock();

        {
            lock_guard<mutex> lock(waiterMutex);
            eatingCount--;
        }
    }

    void stop() {
        stopFlag = true;
    }
};

int main() {
    int numPhilosophers;
    cout << "Enter the number of philosophers ";
    cin >> numPhilosophers;

    if (numPhilosophers < 1) {
        cerr << "The number of philosophers must be greater than 0!" << endl;
        return 1;
    }

    DiningPhilosophers dp(numPhilosophers);
    vector<thread> philosophers;

    for (int i = 0; i < numPhilosophers; ++i) {
        philosophers.emplace_back(&DiningPhilosophers::philosopher, &dp, i);
    }

    cout << "Press Enter to stop..." << endl;
    cin.ignore();
    cin.get();

    dp.stop();

    for (auto& t : philosophers) {
        if (t.joinable()) t.join();
    }

    cout << "All philosophers have finished eating!" << endl;
    return 0;
}
