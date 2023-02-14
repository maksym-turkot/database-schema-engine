/**
 * Pulls all data from the system and dumps it into a text file.
 * 
 * @author  Maksym Turkot
 * @version 11/05/2022
 */

#include "dump.h"

/**
 * Creates a file system_dump.txt in data folder and dumps 
 * system info into it.
 */
void system_dump() {
    FILE *fp = fopen("data/system_dump.txt", "w");
    void *ptr = db;

    print_db(fp, ptr);
    
    int fclose( FILE *fp );
}

/**
 * Prints information about a relation from a schema, along with the 
 * address of the relation.
 * 
 * @param fp pointer fo the file.
 * @param ptr pointer to the database.
 */
void print_db(FILE *fp, void *ptr) {
    char **attrs = create_attr_typ_ref(ptr);

    fprintf(fp, "%p: ", ptr);

    // Iterate through the memory block.
    while (1) {
        // Check if the end of attributes was reached.
        if (*(char*)ptr == '&') {
            ptr++;
            void *root = (void*) *(size_t*)ptr;
            fprintf(fp, "%p\n", root);
            ptr += sizeof((size_t) ptr) + 1;

            fprintf(fp, "                data:\n");
            print_records(fp, root, attrs);
            fprintf(fp, "\n");

            // Check if the end of database was reached.
            if(*(char*)ptr == '#') {
                break;
            }

            fprintf(fp, "%p: ", ptr);

            attrs = create_attr_typ_ref(ptr);
        } else {
            char* str = malloc(sizeof(char*) * strlen((char*)ptr) + 1);
            strcpy(str, (char *)ptr);
            ptr += strlen((char*)ptr) + 1;
            fprintf(fp, "%s|", str);
        }
    }
}

/**
 * Prints records to a file from a table.
 * 
 * @param fp pointer to a file.
 * @param root poiter to the table.
 * @param attrs string array of attribute names.
 */
void print_records(FILE* fp, void *root, char **attrs) {
    int ctr = 0;

    fprintf(fp, "%p: ", root);

    // Iterate through the memory block.
    while (1) {
        // Check if the end of a record. Otherwise, check the data type.
        if (*(char*)root == '$') {
            fprintf(fp, "\n");
            root++;

            // Check if the end of database was reached.
            if(*(char*)root == '#') {
                break;
            }

            fprintf(fp, "%p: ", root);
            ctr = 0;
        } else if (!strcmp(*(attrs + ctr), "integer")) {
            fprintf(fp, "%d|", *(int*)root);
            root += sizeof(int);
            ctr++;
        } else if (!strcmp(*(attrs + ctr), "char*")) {
            fprintf(fp, "%s|", (char*)root);
            root += strlen((char*)root) + 1;
            ctr++;
        } else if (!strcmp(*(attrs + ctr), "smallint")) {
            fprintf(fp, "%hi|", *(short*)root);
            root += sizeof(short);
            ctr++;
        } else if (!strcmp(*(attrs + ctr), "real")) {
            fprintf(fp, "%f|", *(float*)root);
            root += sizeof(float);
            ctr++;
        } 
    }
    fprintf(fp, "\n");
}

