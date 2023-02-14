/**
 * Contains the main() function that starts the program execution.
 * It creates table schemas stored in the db_primary memory block.
 * It also inserts entries into the respective tables.
 * 
 * @author  Maksym Turkot
 * @version 11/06/2022
 */

#include "main.h"

/**
 * Creates table schemas and stores entries to the tables.
 * Calls create_table and insert functions to perform required actions.
 */
int main() {
    printf("Starting...\n");

    void *db_primary = create_db();
    
    create_table("test", "heap", "id", 4, "id",  "int", "moo", "int");
    create_table("app", "heap", "boo", 4, "foo", "int", "boo", "int");

    insert("test", 2, 11, 22);

    free(db_primary);

    printf("Exiting...\n");
    return 0;
}