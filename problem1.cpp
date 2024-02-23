// David Huynh
// COP 4520 - Spring 2024

#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <shared_mutex>
#include <random>

#define GUESTS 8

// Notes:
// Thread #1 is the designated leader thread. It could also be randomized, but for simplicity I chose 1.
// I set the number of threads to 8. You can use more threads if your machine can handle it.
// Eustis3 supports up to 64 threads, so this program should work on there.

// The output for this program is in the minotaur's perspective (assuming he has cameras everywhere and can see what happens).

class Labyrinth
{
    private:
    std::shared_mutex mtx;
    bool cake;
    bool gameStatus;
    int calledThreadNumber;

    // Variables for generating a random number.
    std::random_device rd;
    std::mt19937 mt;
    std::uniform_int_distribution<int> dist;

    public:
    // Default constructor.
    Labyrinth() : cake(true), gameStatus(true), mt(rd()), dist(1, GUESTS), calledThreadNumber(-1)
    {

    }

    // Allows one thread to enter a labyrinth at a time.
    // The leader thread is the only one allowed to replace cakes.
    // The other threads may eat a cake only ONCE if it exists.
    bool enterLabyrinth(bool isLeader, bool canEatCake, int threadNumber)
    {
        std::unique_lock lock(mtx);

        if (isLeader == true)
        {
            // If the cake doesn't exist, the leader replaces it.
            if (cake == false)
            {
                std::cout << "Person #" << threadNumber << " entered and replaced the cake!\n";
                cake = true;
                return true;
            }
        }
        else
        {
            // A person may eat a cake once if it exists.
            if (cake == true && canEatCake == true)
            {
                std::cout << "Person #" << threadNumber << " entered and ate a cake!\n";
                cake = false;
                return false;
            }
            return canEatCake;
        }

        return false;
    }

    // Allows the leader to tell the minotaur that everyone has entered the labyrinth.
    void signalMinotaur()
    {
        std::unique_lock lock(mtx);
        gameStatus = false;
    }

    // Every other thread continues running until the game is ended by the leader/minotaur.
    bool checkGameStatus()
    {
        std::shared_lock lock(mtx);
        return gameStatus;
    }

    // Allows the minotaur to call another random thread to enter.
    void minotaurCallsNext()
    {
        std::unique_lock lock(mtx);
        calledThreadNumber = dist(mt);
        std::cout << "Minotaur called person #" << calledThreadNumber << " to enter!\n";
    }
    
    // Each thread can check if it was called by the minotaur to enter.
    int checkCalledGuestNumber()
    {
        // Shared lock allows multiple threads to read, but not write.
        // Reference: https://en.cppreference.com/w/cpp/thread/shared_mutex
        std::shared_lock lock(mtx);
        return calledThreadNumber;
    }
};


// The leader thread will track the number of cake replacements.
// The number of cake replacements is the number of people who have entered + eaten a cake.
void leaderThread(Labyrinth &lab, int myGuestNumber)
{
    bool isLeader = true;
    bool canEatCake = true;
    int counter = 0;

    while (true)
    {
        // Check if the leader is called to enter.
        if (myGuestNumber == lab.checkCalledGuestNumber())
        {
            // If leader replaces a cake, increment the counter.
            if (lab.enterLabyrinth(isLeader, canEatCake, myGuestNumber) == true)
            {
                counter++;
            }

            // Exit the game when everyone else has entered the maze.
            if (counter == GUESTS - 1)
            {
                std::cout << "Person #" << myGuestNumber << " has replaced the cake " << counter << " times!\n";
                std::cout << "Person #" << myGuestNumber << " has signaled that everyone has entered the labyrinth!\n";
                lab.signalMinotaur();
                return;
            }

            lab.minotaurCallsNext();
        }
    }
}

// The goal of the other threads is to eat a cake only once.
void otherThread(Labyrinth &lab, int myGuestNumber)
{
    bool isLeader = false;
    bool canEatCake = true;

    while (true)
    {
        // Loop until leader signals the game is over.
        if (lab.checkGameStatus() == false)
        {
            return;
        }

        // Check if you were the called thread.
        if (myGuestNumber == lab.checkCalledGuestNumber())
        {
            // Enter the labyrinth and eat the cake if you haven't already.
            canEatCake = lab.enterLabyrinth(isLeader, canEatCake, myGuestNumber);
            lab.minotaurCallsNext();
        }
    }
}

int main(void)
{
    std::vector<std::thread> pool(GUESTS);
    Labyrinth myLab;

    // Spawns the leader thread.
    pool[0] = std::thread(leaderThread, std::ref(myLab), 1);

    // Spawns the other threads.
    for (int i = 1; i < pool.size(); i++)
    {
        pool[i] = std::thread(otherThread, std::ref(myLab), i+1);
    }

    // Minotaur calls the first person to enter.
    myLab.minotaurCallsNext();

    // Join the threads at the end.
    for (auto &t : pool)
    {
        t.join();
    }

    return 0;
}
