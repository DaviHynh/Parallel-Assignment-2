# COP4520 Programming Assignment 2

### [Documentation](#Program-Documentation)

### [Compile Instructions](#Compile-Instructions)
Note: I recommend using Eustis3 for testing since they have up to 64 threads and it's the same environment I tested on.
- #### [Windows on Eustis3](#Compiling-for-Windows-on-Eustis3)
- #### [Mac/Linux on Eustis3](#Compiling-for-Linux-or-Mac-on-Eustis3)
- #### [Local Machine](#Compiling-for-Local-Machine)


## Program Documentation
### Problem 1

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
