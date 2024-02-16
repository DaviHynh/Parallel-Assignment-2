// David Huynh
// COP 4520 - Spring 2024

#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <shared_mutex>
#include <random>
#include <queue>

#define GUESTS 8

// I decided to implement a strategy using a queue and an availability status.

// Main class to simulate the showroom.
class ThreadQueue
{
    private:
    std::shared_mutex mtx;
    std::queue<int> q;

    // Variables for generating a random number.    
    std::random_device rd;
    std::mt19937 mt;
    std::uniform_int_distribution<int> dist;

    public:
    ThreadQueue() : mt(rd()), dist(0, 1)
    {
        
    }

    // When a guest enters the showroom, they leave the queue and the showroom becomes "busy".
    // When the function ends, the guest leaves and the showroom becomes "available".
    void enterShowroom(int guestNumber)
    {
        std::unique_lock lock(mtx);
        std::cout << "Guest " << guestNumber << " entered the showroom.\n";

        // Leave the queue.
        if (!q.empty())
        {
            q.pop();
        }
    }

    // One thread at a time can enqueue.
    void enqueue(int guestNumber)
    {
        std::unique_lock lock(mtx);
        q.push(guestNumber);

        // Uncomment the line below to view enqueue operations:
        // std::cout << "(ENQUEUE) " << guestNumber << "\n";
    }

    // Multiple threads can check if they're at the front.
    bool atFront(int guestNumber)
    {
        std::shared_lock lock(mtx);

        if(!q.empty() && guestNumber == q.front())
        {
            return true;
        }

        return false;
    }

    // Allows a thread to decide if it wants to requeue.
    bool requeue(int guestNumber)
    {
        std::unique_lock lock(mtx);
        int check = dist(mt);

        if (check == 0)
        {
            return false;
        }

        q.push(guestNumber);

        // Uncomment the line below to view requeue operations:
        // std::cout << "(REQUEUE) " << guestNumber << "\n";

        return true;
    }
};

// Thread function that places each thread in a queue.
void waitingRoom(ThreadQueue &tq, int myGuestNumber)
{
    // Each guest enqueues once to guarantee a visit to the room.
    tq.enqueue(myGuestNumber);

    while (true)
    {
        // Each guest continuously checks if they're at the front of the queue.
        if (tq.atFront(myGuestNumber) == true)
        {
            // If they're at the front, they can enter the showroom if it's available.
            // If it's busy, the current thread waits until it isn't.
            tq.enterShowroom(myGuestNumber);

            // After entering, the guest can decide if they want to enqueue again.
            if (tq.requeue(myGuestNumber) == false)
            {
                return;
            }
        }
    }
}

// Main function which spawns GUESTS amount of threads.
int main(void)
{
    std::vector<std::thread> pool(GUESTS);
    ThreadQueue tq;

    // Spawn the guests.
    for (int i = 0; i < GUESTS; i++)
    {
        pool[i] = std::thread(waitingRoom, std::ref(tq), i+1);
    }

    for (auto &t : pool)
    {
        t.join();
    }

    return 0;
}
