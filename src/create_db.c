/**
 * Contains the create_db function to create 
 * a schema table.
 * 
 * @author  Maksym Turkot
 * @version 11/01/2022
 */

#include "create_db.h"

// Global pointer to the db_primary block.
void *db;

/**
 * Allocates a memory block to store the schema data and 
 * returns a void pointer to that block.
 * 
 * @return a void pointer to shcema data block.s
 */
void *create_db() {
    db = malloc(256);
    *(char *) db = '#';

    return db;
}