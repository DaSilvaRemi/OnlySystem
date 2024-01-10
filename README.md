# Only System - Simulated Linux-Like File System

**Description:**
Only System is a school project aimed at creating a command-line program in C to simulate a Linux-like file system. This program allows users to perform various operations on the simulated file system, mimicking real-world file system functionality. The supported operations include:

- `ls`: Display all the contents of the current directory.
- `cd`: Change the current directory to another one (only works with one degree of directory, e.g., `cd test` or `cd ..`).
- `put`: Read a file from the current directory of the C executable, put it into the virtual file system, and copy the file to the physical representation in the partition directory.
- `get`: Retrieve a file from the file system and write it to the dump directory.
- `rmdir`: Remove a directory.
- `mkdir`: Create a directory.
- `cat`: Display the content of a file.
- `touch`: Create a file.
- `exit`: Exit and save the file system into a binary dump file.

**Implementation:**
The project is implemented in C, leveraging system operations. The file system is structured using a simple Tree data structure, with all the necessary operations handled within.

**How to Run:**
Before running the program, ensure you have the following prerequisites:

- `gcc`
- `Make`
- Linux or WSL

To run the program:

1. Clone the repository and navigate to the `src` directory.
2. Execute the following commands:
   ```bash
   make
   ```
3. Run the executable named "run" to test the program.

**How to Use:**
After running the program, you will be prompted to choose between two options:

1. Read a binary save of the file system.
2. Create a new "partition" (simulating a directory as the file system).

Choose the second option and specify the size of your partition. This will create two directories: "dump" and "partition." You can then explore and test all the supported commands.
