/**
 * Inserts a new entry to the table. Includes a helper funciton for finding an 
 * insertion location for the heap organisaton.
 * 
 * @author  Maksym Turkot
 * @version 11/01/2022
 */

#include "insert.h"

/**
 * Inserts a record into the table. This method controls the insertion process 
 * by finding the table schema in db_primary, locating the root pointer in the
 * schema, compiling an array with types of attributes to be inserted, finding 
 * a location for insertino within the root, and inserting passed values into 
 * the table.
 * 
 * @param name of the table to insert in.
 * @param length number of additional function parameters.
 */
void insert(const char *name, int length, ...) {
    va_list arg_list;
    va_start(arg_list, length);

    // Find table schema.
    void *table = find_in_primary(name);

    // Check if table schema was found.
    if (table == NULL) {
        printf("No table with name \"%s\"", name);
        return;
    }
    
    // Find the root pointer.
    void *root = find_root_ptr(table);

    // Create a reference of attribute types from schema.
    char **attr_typ_ref = create_attr_typ_ref(table);

    // Find where to insert record.
    void *record = find_insert_heap(root);

    // Store attributes to the table.
    for (int cntr = 0; cntr < length; cntr++) {
        // Check what type is the attribute.
        if (!strcmp(*(attr_typ_ref + cntr), "integer")) {
            *(int*)record = va_arg(arg_list, int);
            record += sizeof(int);
        } else if (!strcmp(*(attr_typ_ref + cntr), "char*")) {
            char *str = va_arg(arg_list, char*);
            strcpy((char *)record, str);
            record += strlen(str) + 1;
        } else if (!strcmp(*(attr_typ_ref + cntr), "smallint")) {
            *(short*)record = (short) va_arg(arg_list, int);
            record += sizeof(short);
        } else if (!strcmp(*(attr_typ_ref + cntr), "real")) {
            *(float*)record = (float) va_arg(arg_list, double);
            record += sizeof(float);
        }
    }

    // Terminate the record.
    *(char *)record = '$';
    record++;

    // Terminate the file.
    *(char *)record = '#';
    record++;

    va_end(arg_list);
}

/**
 * Finds the location to insert a record in a heap structure.
 * Looks for the end of the file.
 * 
 * @param ptr to the root table.
 * @return pointer to the insert location on the heap.
 */
void *find_insert_heap(void *ptr) {
    // Find the end of the table.
    while (*(char*)ptr++ != '#');
    return --ptr;
}