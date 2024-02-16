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
There are two ways to do this. The first is by allowing everyone to eat the cake once and having one person replace the cake each time.
The number of cake replacements indicates the number of people who have entered and eaten a cake.
The second method is having everyone replace the cake once and having one person eat all the cakes.
The number of cakes eaten indicates the number people that have entered and replaced a cake.

My program uses the former method to guarantee that everyone has entered the labyrinth at least once.
It works by designating a thread as the leader, which replaces cakes and tracks the number of replacements.
The goal of the other threads is to enter the labyrinth and eat the cake once if it exists.
When the lead thread counts n - 1 cake replacements, it knows n - 1 people have entered the maze and eaten a cake.
The lead thread then signals to the minotaur that everyone has entered at least once and the game ends.

A unique_lock is used when entering the labyrinth to ensure mutual exclusion, so that multiple threads can't enter at the same time.
A shared_lock is used so that multiple threads can read if they were called to enter the labyrinth.
The average runtime for this program is O(n^2).
This is because it takes an average of O(n) time for a specific thread to eat a cake and then it also takes O(n) time to replace the cake.

I ran some empirical tests for 4/8 guests to track the number times the guests were called into the labyrinth before the program ended.
- 4 guests resulted in a range of 10 to 45 guest calls. (Expected is 16). However, a majority of the calls were +/- 4 away from 16.
- 8 guests resulted in a range of 49 to 133 guest calls. (Expected is 64). A majority of calls were +/- 15 away from 64.

There's some binomial distribution magic here, but I ran these tests quickly so this is as good as it's gonna get.
From the empirical testing, I believe the runtime is approximately O(n^2).

Incrementing the number of guests is dependent on the number of available threads for a machine.
Having too many guests/threads than a machine can support will lead to a slow runtime.


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
