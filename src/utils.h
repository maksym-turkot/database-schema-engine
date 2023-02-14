/**
 * Includes helper funcitons used by insert, update, and select, for finding 
 * the table schema, finding a pointer of the root record, and creating a 
 * reference of table attribute types for the insertion.
 * 
 * @author  Maksym Turkot
 * @version 11/01/2022
 */

#ifndef UTILS_H
#define UTILS_H

#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include "create_db.h"

/**
 * Finds the pointer to the shcema entry for the desired table.
 * 
 * @param name of the table to find schema for.
 * @return pointer to the schema entry for the table.
 */
void *find_in_primary(const char*);

/**
 * Finds a pointer to the root table for a given schema.
 * 
 * @param void to the shcema entry.
 * @return pointer to the root table.
 */
void *find_root_ptr(void*);

/**
 * Create an array of types of attributes in a table.
 * Types are in order of the attributes.
 * 
 * @param void pointer to the schema entry.
 * @return string array of attribute types.
 */
char **create_attr_typ_ref(void*);

void system_dump();

void print_db(FILE*, void*);

void print_records(FILE*, void*, char**);

#endif //UTILS_H