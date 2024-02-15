// David Huynh
// COP 4520 - Spring, 2024

#include <iostream>
#include <atomic>
#include <chrono>
#include <fstream>
#include <thread>
#include <vector>
#include <mutex>
#include <shared_mutex>

class Labyrinth
{
    private:


    public:
    // Default constructor for this class.
    Labyrinth ()
    {

    }

    // Sends one person into the labyrinth.
    void enterLabyrinth(void)
    {




    }
};




int main(void)
{
    // Number of threads (people) to spawn.
    int n = 8;

    Labyrinth myLab;


    








    return 0;
}




// --> every thread keeps track of how many people have entered the labyrinth?
// when someone is called twice? they should leave the cake there?
// or have everyone track the # of times another person has entered the maze.
// 