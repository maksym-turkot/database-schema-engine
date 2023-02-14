/**
 * Includes helper funcitons used by insert, update, and select, for finding 
 * the table schema, finding a pointer of the root record, and creating a 
 * reference of table attribute types for the insertion.
 * 
 * @author  Maksym Turkot
 * @version 11/01/2022
 */

#include "utils.h"

/**
 * Finds the pointer to the shcema entry for the desired table.
 * 
 * @param name of the table to find schema for.
 * @return pointer to the schema entry for the table.
 */
void *find_in_primary(const char *name) {
    void *ptr = db;
    
    // Check the first element.
    if (*(char*)ptr != '#') {
        // Check if first element name is equal.
        if (!strcmp((char*)ptr, name)) {
            return ptr;
        }
    }

    // Check all other elements.
    while (*(char*)ptr != '#') {
        // Check if reached end of record.
        if (*(char*)ptr++ == '$') {
            // Check if names are equal.
            if (!strcmp((char*)ptr, name)) {
                return ptr;
            }
        }
    }
    return NULL;
}

/**
 * Finds a pointer to the root table for a given schema.
 * Looks for the end of attribute list.
 * 
 * @param ptr to the shcema entry.
 * @return pointer to the root table.
 */
void *find_root_ptr(void *ptr) {
    // Find end of attribute list.
    while (*(char*)ptr++ != '&');
    return (void*) *(size_t*)ptr;
}

/**
 * Create an array of types of attributes in a table.
 * Types are in order of the attributes.
 * 
 * @param table pointer to the schema entry.
 * @return string array of attribute types.
 */
char **create_attr_typ_ref(void *table) {
    void *prep = table;
    int ctr = 0;

    // Find the beginning of attributes.
    while (ctr < 3) {
        table += strlen((char*)table) + 1;
        prep += strlen((char*)prep) + 1;
        ctr++;
    }

    ctr = 0;

    // Count number of attributes.
    while (*(char*)prep != '&') {
        // Skip attribute name.
        prep += strlen((char*)prep) + 1;
        prep += strlen((char*)prep) + 1;
        ctr++;
    }

    char **attr = malloc(sizeof(char*) * ctr);

    ctr = 0;

    // Record a type of each attribute.
    while (*(char*)table != '&') {
        // Skip attribute name.
        table += strlen((char*)table) + 1;

        char *str = malloc(sizeof(char*) * strlen((char*)table) + 1);
        strcpy(str, (char *)table);
        *(attr + ctr) = str;

        table += strlen((char*)table) + 1;

        ctr++;
    }
    return attr;
}
