/**
 * Contains the create_db function to create 
 * a schema table.
 * 
 * @author  Maksym Turkot
 * @version 11/01/2022
 */

#ifndef CREATE_DB_H
#define CREATE_DB_H

#include <stdlib.h>

// Global pointer to the db_primary block.
void *db;

/**
 * Allocates a memory block to store the schema data.
 * 
 * @return a void pointer to shcema data block.s
 */
void *create_db();

#endif //CREATE_DB_H