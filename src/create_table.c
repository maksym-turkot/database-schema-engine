/**
 * Creates an entry in the db_primary table with info about the 
 * new table. Allocates memory block for the new table.
 * 
 * @author  Maksym Turkot
 * @version 10/20/2022
 */

#include "create_table.h"

/**
 * Creates an entry in the db_primary table to store the table information.
 * Stores passed attributes to the db_primary along with the pointer to the 
 * root table.
 * 
 * @param name of the table to be created.
 * @param type of the ordering of the table to be created.
 * @param primary_key name of the attribute to be primary key.
 * @param length number of additional function parameters.
 */
void create_table(const char *name, const char *type, const char *primary_key, 
        int length, ...) {
    va_list arg_list;
    va_start(arg_list, length);

    void *ptr = db;

    // Find the end of last record.
    while (*(char *)ptr++ != '#');
    ptr--;

    // Store name.
    strcpy((char *) ptr, name);
    ptr += strlen(name) + 1;

    // Store type.
    strcpy((char *) ptr, type);
    ptr += strlen(type) + 1;

    // Store primary key.
    strcpy((char *) ptr, primary_key);
    ptr += strlen(primary_key) + 1;

    // Store attribute names and types.
    for (int cntr = 0; cntr < length; cntr++) {
        char *str = va_arg(arg_list, char*);

        strcpy((char *)ptr, str);
        ptr += strlen(str) + 1;
    }

    // Terminate attr/type list.
    *(char *)ptr = '&';
    ptr++;

    // Allocate mem for root table.
    void *root = malloc(256);

    // Set up root table.
    *(char*)root = '#';

    // Store root table address as an unsigned long.
    *(size_t*) ptr = (size_t) root;
    ptr += sizeof((size_t) root);

    // Terminate record.
    *(char *)ptr = '$';
    ptr++;

    // Terminate file.
    *(char *)ptr = '#';
    ptr++;

    va_end(arg_list);
}