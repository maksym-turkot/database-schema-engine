/**
 * Runs the tests. IDE may indicate errors, please ignore them.
 * Software is compiled using CMake and runs correctly in the Terminal.
 * 
 * @author  Maksym Turkot
 * @version 11/06/2022
 */


#include "gtest/gtest.h"

extern "C" {
    #include "create_db.h"
    #include "create_table.h"
    #include "insert.h"
    #include "utils.h"
    #include "dump.h"
}

/**
 * Tests the create_table function of the create_table file.
 * Creates tables and checks that selected characters are present
 * in correct memory locations.
 */
TEST(create_table_test, create_table) {
    create_db();
    create_table("test", "heap", "id", 4, "id",  "integer", "moo", "integer");
    create_table("app", "heap", "boo", 4, "foo", "integer", "boo", "integer");

    EXPECT_EQ (*((char*) db + 0),  't');
    EXPECT_EQ (*((char*) db + 1),  'e');
    EXPECT_EQ (*((char*) db + 20), 'g');
    EXPECT_EQ (*((char*) db + 36), '&');
    EXPECT_EQ (*((char*) db + 45), '$');
    EXPECT_EQ (*((char*) db + 51), 'e');
    EXPECT_EQ (*((char*) db + 93), '#');
}

/**
 * Tests the find_in_primary function of the utils file.
 * Creates tables in db_primary and checks if pointers to the 
 * schema entries for a given table name are returned.
 */
TEST(utils_test, find_in_primary) {
    create_db();
    create_table("test", "heap", "id", 4, "id",  "integer", "moo", "short");
    create_table("app", "heap", "boo", 4, "foo", "integer", "boo", "integer");

    void *ptr = find_in_primary("test");
    EXPECT_EQ (*((char*)ptr + 0), 't');
    EXPECT_EQ (*((char*)ptr + 1), 'e');
    EXPECT_EQ (*((char*)ptr + 2), 's');
    EXPECT_EQ (*((char*)ptr + 4), '\0');


    ptr = find_in_primary("app");
    EXPECT_EQ (*((char*)ptr + 0), 'a');
    EXPECT_EQ (*((char*)ptr + 1), 'p');
    EXPECT_EQ (*((char*)ptr + 2), 'p');
    EXPECT_EQ (*((char*)ptr + 4), 'h');

    // Edge case of the table name not being present.
    ptr = find_in_primary("home");
    void *null = NULL;
    EXPECT_EQ (ptr, null);
}

/**
 * Tests the create_attr_typ_ref function of the utils file.
 * Creates tables in db_primary and checks if attribute reference
 * array is created with correct datatype names.
 */
TEST(utils_test, create_attr_typ_ref) {
    create_db();
    create_table("test", "heap", "id", 4, "id",  "integer", "moo", "short");
    create_table("app", "heap", "boo", 4, "foo", "integer", "boo", "integer");

    void *table = find_in_primary("test");
    void *root = find_root_ptr(table);
    char **attr_ref = create_attr_typ_ref(table);

    EXPECT_EQ (strcmp(*(attr_ref + 0), "integer"), 0);
    EXPECT_EQ (strcmp(*(attr_ref + 1), "short"), 0);   
}

/**
 * Tests the insert function of the insert file.
 * Creates tables in db_primary, inserts an entry into the correct table and 
 * checks if its values are present in that memory block.
 */
TEST(insert_test, insert) {
    create_db();
    create_table("test", "heap", "id", 8, "id",  "integer", "moo", "char*", "goo", "smallint", "voo", "real");
    create_table("app", "heap", "boo", 4, "foo", "integer", "boo", "integer");

    insert("test", 4, 11, "rambo", 3, 4.1);

    EXPECT_EQ (*((int*)((void*)*(size_t*)((char*)db + 57)) + 0), 11);
    EXPECT_EQ (*(char*)((char*)((void*)*(size_t*)((char*)db + 57)) + 4),  'r');
    EXPECT_EQ (*(short*)((char*)((void*)*(size_t*)((char*)db + 57)) + 10),  3);
    EXPECT_GT (*(float*)((char*)((void*)*(size_t*)((char*)db + 57)) + 12),  4.099);
    EXPECT_LT (*(float*)((char*)((void*)*(size_t*)((char*)db + 57)) + 12),  4.101);
    EXPECT_EQ (*(char*)((char*)((void*)*(size_t*)((char*)db + 57)) + 17), '#');
}

/**
 * Dumps the system contents to a file.
 * Creates tables in db_primary, inserts an entry into the tables and
 * dumps the system to a file.
 */
TEST(utils_test, system_dump) {
    create_db();
    create_table("movies", "heap", "id", 10, "id",  "integer", "name", "char*", "age_restriction", "smallint", "length", "integer", "rating", "real");
    create_table("star", "heap", "id", 8, "id", "integer", "name", "char*", "age", "smallint", "last_film", "char*");

    insert("movies", 5, 1, "Bad Times at the El Royale", 17, 141, 7.1);
    insert("movies", 5, 2, "WALL-E",                      0, 97,  8.4);
    insert("movies", 5, 3, "Bullet Train",               17, 97,  7.3);

    insert("star", 4, 1, "Chris Hamsworth",   39, "Furiosa");
    insert("star", 4, 2, "John Ratzenberger", 75, "Luck");
    insert("star", 4, 3, "Brad Pitt",         58, "Babylon");

    system_dump();
}