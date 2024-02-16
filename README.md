# COP4520 Programming Assignment 2

### [Documentation](#Program-Documentation)

### [Compile Instructions](#Compile-Instructions)
Note: I recommend using Eustis3 for testing since they have up to 64 threads and it's the same environment I tested on.
- #### [Windows on Eustis3](#Compiling-for-Windows-on-Eustis3)
- #### [Mac/Linux on Eustis3](#Compiling-for-Linux-or-Mac-on-Eustis3)
- #### [Local Machine](#Compiling-for-Local-Machine)


## Program Documentation
### Problem 1
The solution to this problem is figuring out how to track if everyone has visited the labyrinth at least once.
There are two ways to do this. The first is by allowing everyone to eat the cake only once and having one person replace the cake each time.
The number of cake replacements indicates the number of people who have entered and eaten a cake.
The second method is having everyone replace the cake once and having one person eat all the cakes.
The number of cakes eaten indicates the number people that have entered and replaced a cake.

My program uses the former method to guarantee that everyone has entered the labyrinth at least once.
It works by designating a thread as the leader, which replaces cakes and tracks the number of replacements.
The goal of the other threads is to enter the labyrinth and eat the cake once if it exists.
When the lead thread counts n - 1 cake replacements, it knows n - 1 people have entered the maze and eaten a cake.
The lead thread then signals to the minotaur that everyone has entered at least once (since the lead thread is also guaranteed to enter once) and the game ends.
Since the goal is to ensure that every guest has entered the labyrinth at least once, the lead thread doesn't need to eat the cake after respawning it for the last time.
However, you could modify the code to allow the leader to eat the cake.

A unique_lock is used when entering the labyrinth to ensure mutual exclusion, so that multiple threads can't enter at the same time.
A shared_lock is used so that multiple threads can read if they were called to enter the labyrinth.
The average runtime for this program is O(n^2).
This is because it takes an average of O(n) time for a specific thread to eat a cake and then it also takes O(n) time to replace the cake.

I ran some empirical tests for 4/8 guests to track the number times the guests were called into the labyrinth before the program ended.
- 4 guests resulted in a range of 10 to 45 guest calls. (Expected is 16). However, a majority of the calls were +/- 4 away from 16.
- 8 guests resulted in a range of 49 to 133 guest calls. (Expected is 64). A majority of calls were +/- 15 away from 64.

There's some binomial distribution magic here, but I ran these tests quickly and with a low sample size so more testing is needed.
From the empirical testing, I believe the runtime is approximately O(n^2). O(n^3) would result in a much higher expected value, so I don't think it's that runtime.

Incrementing the number of guests is dependent on the number of available threads for a machine.
Having too many guests/threads than a machine can support will lead to a slow runtime.

### Problem 2
Strategy #1:
- The main benefit of this strategy is that it allows some guests to enter the showroom while also allowing them to roam around the castle.
Also, if guests aren't responsible for opening and closing the door, they don't need to worry about changing the availability of the room.
However, the main downside is that not every guest is guaranteed to enter when they want to.
The showroom's door could be closed every time a guest wants to enter the room, preventing that guest from ever entering.
It also could cause issues with multiple guests waiting/crowding around the door to try and get in as soon as someone leaves.

Strategy #2:
- This strategy is somewhat similar to strategy 1.
Checking if a sign is available/busy is the same process as checking if the door is opened/closed.
The main difference is that the guests are the ones setting the room's status.
An issue might arise when a guest forgets to change the sign's status when they leave/enter.
Another issue is that a guest isn't always guaranteed to enter, since the room might be busy every time they try to enter.

Strategy #3:
- This strategy utilizes a queue to guarantee that a guest can view the showroom.
This solves the issue with the previous two strategies -- as long as the guest queues, they can view the vase.
However, the biggest issue is that entering the showroom is dependent on receiving a signal.
The first guest in the queue will never receive a signal to enter, since no one has ever entered/exited the room at the start.
Another issue is when the queue size drops to 0 and a guest wants to re-queue.
After that guest enters the room, he would signal no one in the queue.
If the guest requeues to enter the room, he would wait for a signal to enter, but it would never come since no one is in the room.

My Strategy:
- My program uses a mix of concepts from the previous three strategies.
Multiple threads are able to enter a queue -- one at a time.
Each thread in the queue constantly checks if it's at the front.
If a thread is at the front, it waits until the showroom is "available" before entering it.
Upon entering the showroom, the thread leaves the queue, and the showroom becomes "busy".
Upon exiting, the showroom becomes available for the next thread in the queue, and the current thread can decide if it wants to requeue with a 50% chance.
This guarantees that everyone is able to enter the showroom, since every thread is forced to enqueue once.
It also prevents the threads from waiting infinitely, since they can always see if the room is available or not.

My program should always allow the guests to visit the room at least once.
However, the threads are not guaranteed to enter the room in sequential order.
Some threads might enqueue and requeue at different times, but they always access the showroom in FIFO order.

My program is also thread safe, since it uses a unique_lock on a single mutex for multiple methods.
This prevents data races for operations like enqueue and requeue (coarse-grained locking).
Another unique_lock is used upon entering the showroom, to prevent multiple threads from entering at the same time.
A shared_lock allows multiple threads to read the front of the queue, while also disabling write access.

When testing my program, I tracked the output to view which threads were able to enter the showroom.
Every time I checked the output, each thread visited the showroom at least once.
Approximately half of the threads visited the showroom more than once, which is equivalent to my requeue chance.
My program outputs the order of people entering the showroom.

## Compile Instructions
These instructions assume you have a UCF account. To compile without one, check out the third section.

1. If you're not on the campus WiFi, set up the UCF VPN.
2. Download and install Cisco AnyConnect from https://secure.vpn.ucf.edu/.
3. Open Cisco AnyConnect and type in `https://secure.vpn.ucf.edu`.
4. Login to establish a VPN connection.


## Compiling for Windows on Eustis3

0. (If necessary) Set up the UCF VPN.
1. Download and open MobaXterm from https://mobaxterm.mobatek.net/.
2. Establish a new SSH session by clicking `Session --> SSH`.
3. For remote host, input `eustis3.eecs.ucf.edu`.
4. Click `Specify Username` and input your NID (2 letters + numbers).
5. Leave port as 22 and click OK.
6. Double Click `eustis3.eecs.ucf.edu` in the side bar, and login using your password.
7. Download problem1.cpp/problem2.cpp from this repository and drag it into the sidebar.
8. Run `g++ problem1.cpp` and then run `./a.out` on the command line.
9. Run `g++ problem2.cpp` and then run `./a.out` on the command line.



## Compiling for Linux or Mac on Eustis3

0. (If necessary) Set up the UCF VPN.
1. Open a terminal window and type `YOURNID@eustis3.eecs.ucf.edu` to connect to eustis3. Use your actual NID instead of YOURNID.
2. Enter your password when prompted for one.
3. Download problem1.cpp and problem2.cpp from this repository.
4. Open a NEW terminal, and `cd` into the directory with problem1.cpp/problem2.cpp.
5. Transfer that file to eustis3 by doing `scp problem1.cpp YOUR_NID@eustis3.eecs.ucf.edu:~/`. Do the same for problem2.cpp. Retype password when prompted.
6. On the terminal connected to eustis3, `cd` into the directory with problem1.cpp/problem2.cpp.
7. Run `g++ problem1.cpp` and then run `./a.out` on the command line.
8. Run `g++ problem2.cpp` and then run `./a.out` on the command line.


## Compiling for Local Machine
This section assumes you don't have a UCF account, and want to compile/run the program.

**Windows/Mac/Linux**
1. Install a g++ compiler to compile C++ files.
2. Download problem1.cpp and problem2.cpp from this repository.
3. Use `g++ problem1.cpp` to compile the program and `./a.out` to run it.
4. Use `g++ problem2.cpp` to compile the program and `./a.out` to run it.

**Quick guide for installing g++:**

Windows --> Enable WSL, setup Ubuntu, run: `sudo apt-get install g++` on its command line.

Linux --> Run `sudo apt-get install g++` on the command line.

MacOS --> Google: `how to install g++ on mac` and follow those steps.


**Other OS**
1. Figure out a way to install the g++ compiler on your OS.
2. Compile the .cpp files and run them.
