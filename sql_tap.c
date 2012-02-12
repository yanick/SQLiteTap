#include "sqlite3ext.h"
SQLITE_EXTENSION_INIT1;

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int test_counter = 0;

static void sql_tap_plan( 
    sqlite3_context *ctx,
    int num_values,
    sqlite3_value **values 
) {
    int nbr_tests = sqlite3_value_int( values[0] );

    char *plan;

    plan = sqlite3_mprintf( "1..%d", nbr_tests );
    
    sqlite3_result_text( ctx, plan, strlen(plan), NULL );
}

void sql_tap_ok(
    sqlite3_context *ctx,
    int result,
    char *comment
) {
    char *verdict = result ? "ok" : "not ok";
    char *output;

    int *test_counter = (int *)sqlite3_user_data(ctx);
    (*test_counter)++;

    if ( comment ) {
        comment = sqlite3_mprintf( " - %s", comment );
    }

    output = sqlite3_mprintf( "%s %d%s", verdict, *test_counter, comment );

    sqlite3_result_text( ctx, output, strlen(output), NULL );
}

static void sql_tap_ok_with_desc(
    sqlite3_context *ctx,
    int num_values,
    sqlite3_value **values 
) {
    sql_tap_ok( 
        ctx, 
        sqlite3_value_int(values[0]), 
        sqlite3_value_text( values[1] ) 
    );
}

static void sql_tap_ok_without_desc(
    sqlite3_context *ctx,
    int num_values,
    sqlite3_value **values 
) {
    sql_tap_ok( 
        ctx, 
        sqlite3_value_int(values[0]), 
        NULL 
    );
}

int sqlite3_extension_init( sqlite3 *db, char **error, const sqlite3_api_routines *api ) {
    SQLITE_EXTENSION_INIT2(api);

    int test_counter = 0;  /* bound to change into a struct */

    sqlite3_create_function( db, "plan", 1, SQLITE_UTF8, NULL, sql_tap_plan, NULL, NULL );
    sqlite3_create_function( db, "ok", 2, SQLITE_UTF8, &test_counter, sql_tap_ok_with_desc, NULL, NULL );
    sqlite3_create_function( db, "ok", 1, SQLITE_UTF8, &test_counter, sql_tap_ok_without_desc, NULL, NULL );

    return SQLITE_OK;
}


