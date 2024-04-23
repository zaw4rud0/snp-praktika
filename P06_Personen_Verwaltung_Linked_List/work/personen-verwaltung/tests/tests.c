/* ----------------------------------------------------------------------------
 * --  _____       ______  _____                                              -
 * -- |_   _|     |  ____|/ ____|                                             -
 * --   | |  _ __ | |__  | (___    Institute of Embedded Systems              -
 * --   | | | '_ \|  __|  \___ \   Zuercher Hochschule Winterthur             -
 * --  _| |_| | | | |____ ____) |  (University of Applied Sciences)           -
 * -- |_____|_| |_|______|_____/   8401 Winterthur, Switzerland               -
 * ----------------------------------------------------------------------------
 */
/**
 * @file
 * @brief Test suite for the given package.
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <time.h>
#include <assert.h>
#include <CUnit/Basic.h>
#include "../../../../testlib/include/test_utils.h"
#include "../src/list.h"

#ifndef TARGET // must be given by the make file --> see test target
#error missing TARGET define
#endif

/// @brief alias for EXIT_SUCCESS
#define OK   EXIT_SUCCESS
/// @brief alias for EXIT_FAILURE
#define FAIL EXIT_FAILURE

/// @brief The name of the STDOUT text file.
#define OUTFILE "stdout.txt"
/// @brief The name of the STDERR text file.
#define ERRFILE "stderr.txt"

#define TRACE_INDENT "\n                " ///< allow for better stdout formatting in case of error

// setup & cleanup
static int setup(void)
{
    remove_file_if_exists(OUTFILE);
    remove_file_if_exists(ERRFILE);
    return 0; // success
}

static int teardown(void)
{
    // Do nothing.
    // Especially: do not remove result files - they are removed in int setup(void) *before* running a test.
    return 0; // success
}

// tests
static void test_person_compare(void)
{
    person_t person1 = {"Able", "Alice", 20};
    person_t person2 = {"Bach", "Bob", 40};

    // act
    int test_one = person_compare(&person1, &person2);
    int test_two = person_compare(&person2, &person1);
    int test_three = person_compare(&person1,&person1);

    // assert
    CU_ASSERT(test_one < 0);
    CU_ASSERT(test_two > 0);
    CU_ASSERT(test_three == 0);
}

static void test_list_insert(void)
{
    node_t *root = list_init();

    person_t person_test_one = {"Able", "Alice", 20};
    person_t person_test_two = {"Bach", "Bob", 40};
    person_t person_test_three = {"Roger", "Gold", 60};
    person_t person_test_four = {"Sokolovskiy", "Gleb", 28};
    person_t person_test_five = {"Sokolovskiy", "Gleb", 25};

    // act
    list_insert(&root, person_test_one);
    list_insert(&root, person_test_two);
    list_insert(&root, person_test_three);
    list_insert(&root, person_test_four);
    list_insert(&root, person_test_five);

    // assert
    node_t *current = root->next;
    CU_ASSERT_PTR_NOT_NULL(current);
    CU_ASSERT_STRING_EQUAL(current->content.name, "Able");
    CU_ASSERT_STRING_EQUAL(current->content.first_name, "Alice");
    CU_ASSERT_EQUAL(current->content.age, 20);

    current = current->next;
    CU_ASSERT_PTR_NOT_NULL(current);
    CU_ASSERT_STRING_EQUAL(current->content.name, "Bach");
    CU_ASSERT_STRING_EQUAL(current->content.first_name, "Bob");
    CU_ASSERT_EQUAL(current->content.age, 40);

    current = current->next;
    CU_ASSERT_PTR_NOT_NULL(current);
    CU_ASSERT_STRING_EQUAL(current->content.name, "Roger");
    CU_ASSERT_STRING_EQUAL(current->content.first_name, "Gold");
    CU_ASSERT_EQUAL(current->content.age, 60);

    current = current->next;
    CU_ASSERT_PTR_NOT_NULL(current);
    CU_ASSERT_STRING_EQUAL(current->content.name, "Sokolovskiy");
    CU_ASSERT_STRING_EQUAL(current->content.first_name, "Gleb");
    CU_ASSERT_EQUAL(current->content.age, 25);

    current = current->next;
    CU_ASSERT_PTR_NOT_NULL(current);
    CU_ASSERT_STRING_EQUAL(current->content.name, "Sokolovskiy");
    CU_ASSERT_STRING_EQUAL(current->content.first_name, "Gleb");
    CU_ASSERT_EQUAL(current->content.age, 28);
}

static void test_list_remove(void)
{
    // arrange
    node_t *root = list_init();

    person_t person_test_one = {"Able", "Alice", 20};
    person_t person_test_two = {"Bach", "Bob", 40};
    person_t person_test_three = {"Roger", "Gold", 60};
    person_t person_test_four = {"Sokolovskiy", "Gleb", 28};

    list_insert(&root, person_test_one);
    list_insert(&root, person_test_two);
    list_insert(&root, person_test_three);
    list_insert(&root, person_test_four);

    // act
    list_remove(&root, person_test_two);

    // assert
    node_t *current = root->next;
    CU_ASSERT_PTR_NOT_NULL(current);
    CU_ASSERT_STRING_EQUAL(current->content.name, "Able");
    CU_ASSERT_STRING_EQUAL(current->content.first_name, "Alice");
    CU_ASSERT_EQUAL(current->content.age, 20);

    current = current->next;
    CU_ASSERT_PTR_NOT_NULL(current);
    CU_ASSERT_STRING_EQUAL(current->content.name, "Roger");
    CU_ASSERT_STRING_EQUAL(current->content.first_name, "Gold");
    CU_ASSERT_EQUAL(current->content.age, 60);

    current = current->next;
    CU_ASSERT_PTR_NOT_NULL(current);
    CU_ASSERT_STRING_EQUAL(current->content.name, "Sokolovskiy");
    CU_ASSERT_STRING_EQUAL(current->content.first_name, "Gleb");
    CU_ASSERT_EQUAL(current->content.age, 28);
}

static void test_list_clear(void)
{
    // arrange
    node_t *root = list_init();

    person_t person_test_one = {"Able", "Alice", 20};
    person_t person_test_two = {"Bach", "Bob", 40};
    person_t person_test_three = {"Roger", "Gold", 60};
    person_t person_test_four = {"Sokolovskiy", "Gleb", 28};

    list_insert(&root, person_test_one);
    list_insert(&root,person_test_two);
    list_insert(&root, person_test_three);
    list_insert(&root, person_test_four);

    // act
    list_clear(&root);

    // assert
    CU_ASSERT_EQUAL(root->next, root);
}

/**
 * @brief Registers and runs the tests.
 * @returns success (0) or one of the CU_ErrorCode (>0)
 */
int main(void)
{
    // setup, run, teardown
    TestMainBasic("lab test", setup, teardown
                  , test_person_compare
                  , test_list_insert
                  , test_list_remove
                  , test_list_clear
                  );
}
