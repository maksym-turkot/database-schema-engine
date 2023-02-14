/**
 * Contains the main() function that starts the program execution.
 * It creates table schemas stored in the db_primary memory block.
 * It also inserts entries into the respective tables.
 * 
 * @author  Maksym Turkot
 * @version 11/06/2022
 */

#ifndef MAIN_H

#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include "create_db.h"
#include "create_table.h"
#include "insert.h"

/**
 * Creates table schemas and stores entries to the tables.
 */
int main();

#endif //MAIN_H