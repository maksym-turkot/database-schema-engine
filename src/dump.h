/**
 * Pulls all data from the system and dumps it into a text file.
 * 
 * @author  Maksym Turkot
 * @version 11/05/2022
 */

#ifndef DUMP_H
#define DUMP_H

#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include "create_db.h"
#include "utils.h"

/**
 * Creates a file system_dump.txt in data folder and dumps 
 * system info into it.
 */
void system_dump();

/**
 * Prints information about a relation from a schema, along with the 
 * address of the relation.
 * 
 * @param FILE pointer fo the file.
 * @param void pointer to the database.
 */
void print_db(FILE*, void*);

/**
 * Prints records to a file from a table.
 * 
 * @param FILE pointer to a file.
 * @param void poiter to the table.
 * @param char string array of attribute names.
 */
void print_records(FILE*, void*, char**);

#endif //DUMP_H