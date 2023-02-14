/**
 * Creates an entry in the db_primary table with info about the 
 * new table. Allocates memory block for the new table.
 * 
 * @author  Maksym Turkot
 * @version 10/20/2022
 */

#ifndef CREATE_TABLE_H
#define CREATE_TABLE_H

#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include "create_db.h"

/**
 * Creates an entry in the db_primary table to store the table information.
 * 
 * @param char of the table to be created.
 * @param char of the ordering of the table to be created.
 * @param char name of the attribute to be primary key.
 * @param int number of additional function parameters.
 */
void create_table(const char*, const char*, const char*, int, ...);

#endif //CREATE_TABLE_H