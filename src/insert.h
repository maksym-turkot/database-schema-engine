/**
 * Inserts a new entry to the table. Includes helper funciton for finding an 
 * insertion location for the heap organisaton.
 * 
 * @author  Maksym Turkot
 * @version 11/01/2022
 */

#ifndef INSERT_H
#define INSERT_H

#include <stdarg.h>
#include <string.h>
#include "create_db.h"
#include "utils.h"

/**
 * Inserts a record into the table. 
 * 
 * @param name of the table to insert in.
 * @param length number of additional function parameters.
 * @param *values to be inserted into the table, in the order of attributes.
 */
void insert(const char*, int, ...);

/**
 * Finds the location to insert a record in a heap structure.
 * 
 * @param void to the root table.
 * @return pointer to the root table.
 */
void *find_insert_heap(void*);

#endif //INSERT_H