/*
 * Copyright 2020-2021 the Pacemaker project contributors
 *
 * The version control history for this file may have further details.
 *
 * This source code is licensed under the GNU Lesser General Public License
 * version 2.1 or later (LGPLv2.1+) WITHOUT ANY WARRANTY.
 */

#include <crm_internal.h>

#include <stdio.h>
#include <stdbool.h>
#include <glib.h>

static void
uppercase_str_passes(void)
{
    g_assert_true(pcmk_str_is_minus_infinity("-INFINITY"));
}

static void
mixed_case_str_fails(void)
{
    g_assert_false(pcmk_str_is_minus_infinity("-infinity"));
    g_assert_false(pcmk_str_is_minus_infinity("-Infinity"));
}

static void
added_whitespace_fails(void)
{
    g_assert_false(pcmk_str_is_minus_infinity(" -INFINITY"));
    g_assert_false(pcmk_str_is_minus_infinity("-INFINITY "));
    g_assert_false(pcmk_str_is_minus_infinity(" -INFINITY "));
    g_assert_false(pcmk_str_is_minus_infinity("- INFINITY"));
}

static void
empty_str_fails(void)
{
    g_assert_false(pcmk_str_is_minus_infinity(NULL));
    g_assert_false(pcmk_str_is_minus_infinity(""));
}

static void
infinity_fails(void)
{
    g_assert_false(pcmk_str_is_minus_infinity("INFINITY"));
}

int main(int argc, char **argv)
{
    g_test_init(&argc, &argv, NULL);

    g_test_add_func("/common/utils/minus_infinity/uppercase", uppercase_str_passes);
    g_test_add_func("/common/utils/minus_infinity/mixed_case", mixed_case_str_fails);
    g_test_add_func("/common/utils/minus_infinity/whitespace", added_whitespace_fails);
    g_test_add_func("/common/utils/minus_infinity/empty", empty_str_fails);
    g_test_add_func("/common/utils/minus_infinity/infinity", infinity_fails);

    return g_test_run();
}
