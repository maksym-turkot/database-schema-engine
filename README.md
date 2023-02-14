
# Database Engine with Internal Schema Focus

This project implements a simple database engine that focuses on low-level data storage. Specifically, it follows the internal schema architecture of a typical database by creating, indexing, and modifying memory blocks on the disk. The system maintains a primary data block that resembles the conceptual schema of the database: it holds attribute names and data types, as well as pointers to memory blocks (tables) with the data. The program also generates a system-dump, showing the conceptual schema, data tables, as well as memory locations of the data and table pointers.

## User Manual

### Building the program

The program was implemented using C programming language and is built using CMake. To build the program, the user should enter the `build` folder and type:

`cmake -DCMAKE_BUILD_TYPE=Debug ..`

### Running the program

After the program is build, the user may use the makefile in the root folder with the following commands:

`make all`: compiles the program

`make run`: runs the main program, provides no output.

`make test`: runs the testing suite as well as performs a system dump to the file located in the data folder.

`make debug`: runs the lldb debugger, was used during development.

`make debug-tst`: runs the debugger on google tests.

`make clean`: removes executable files.


### Reference

For more information, please see the `schema-database-doc.pdf` in the `doc` folder.