/*
  MIT License

  Copyright (c) 2026 Noa Adhum

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.
*/

#ifndef CEST_H_
#define CEST_H_

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
     size_t assertions;
     size_t assertions_failed;
} Cest;

static Cest cest = {0};

#define CEST_Cstr_Pass                                                     "PASS"
#define CEST_Cstr_Failed                                                   "FAILED"
#define CEST_Cstr_Left                                                     "left"
#define CEST_Cstr_Right                                                    "right"

#define CEST_Msg_Fmt                                                       "%s:%zu: %s"
#define CEST_End_Fmt                                                       "test result: %s; total %zu; passed %zu; failed %zu"

#define CEST_Eq_Fmt                                                        "%s == %s"

// Test macros
#define TEST_BEGIN()                                                       cest_test_begin()
#define TEST_END()                                                         cest_test_end()

// Test assertions
#define ASSERT_TRUE(expr)                                                  cest_assert_true(__FILE__, __LINE__, __func__, #expr, expr)
#define ASSERT_FALSE(expr)                                                 cest_assert_false(__FILE__, __LINE__, __func__, #expr, expr)
#define ASSERT_EQ(type, left, right)                                       cest_assert_eq_##type(__FILE__, __LINE__, __func__, #left, left, #right, right)

#define EXPECT_TRUE(expr)                                                  cest_expect_true(__FILE__, __LINE__, __func__, #expr, expr)
#define EXPECT_FALSE(expr)                                                 cest_expect_false(__FILE__, __LINE__, __func__, #expr, expr)
#define EXPECT_EQ(type, left, right)                                       cest_expect_eq_##type(__FILE__, __LINE__, __func__, #left, left, #right, right)

// Prettier print function implementation
#define cest_print_expr(failed, expr_cstr)                                 cest__print_expr(file, line, func, failed, expr_cstr)
#define cest_print_binary(failed, binary_fmt, left_cstr, right_cstr)       cest__print_binary(file, line, func, failed, binary_fmt, left_cstr, right_cstr)

static void cest__print_expr(const char *file, size_t line, const char *func,
                             bool failed, const char *expr_cstr)
{
     FILE *stream = (failed) ? stderr : stdout;
     const char *result = (failed) ? CEST_Cstr_Failed : CEST_Cstr_Pass;

     fprintf(stream, "\n%s "CEST_Msg_Fmt": %s\n", result, file, line, func, expr_cstr);
}

static void cest__print_binary(const char *file, size_t line, const char *func,
                               bool failed, const char *binary_fmt,
                               const char *left_cstr, const char *right_cstr)
{
     FILE *stream = (failed) ? stderr : stdout;
     const char *result = (failed) ? CEST_Cstr_Failed : CEST_Cstr_Pass;

     fprintf(stream, "\n%s "CEST_Msg_Fmt": ", result, file, line, func);
     fprintf(stream, binary_fmt, left_cstr, right_cstr);
     fputc('\n', stream);
}

static void cest_print_test_result(void)
{
     const char *cstr_result = (cest.assertions_failed == 0) ? CEST_Cstr_Pass : CEST_Cstr_Failed;
     size_t assertions_passed = cest.assertions - cest.assertions_failed;

     fputc('\n', stdout);
     fprintf(stdout, CEST_End_Fmt, cstr_result, cest.assertions, assertions_passed, cest.assertions_failed);
}

// Test function implementation
static void cest_test_begin(void)
{
     cest.assertions = 0;
     cest.assertions_failed = 0;
}

static int cest_test_end(void)
{
     cest_print_test_result();
     return (cest.assertions_failed == 0) ? 0 : 1;
}

// Assertion function implementation

// Asserts
static void cest_assert_true(const char *file, size_t line, const char *func,
                             const char *expr_cstr, bool expr)
{
     cest.assertions++;
     if (!expr) {
          cest_print_expr(true, expr_cstr);
          cest.assertions_failed++;

          cest_print_test_result();
          exit(1);
     } else {
          cest_print_expr(false, expr_cstr);
     }
}

static void cest_assert_false(const char *file, size_t line, const char *func,
                             const char *expr_cstr, bool expr)
{
     cest.assertions++;
     if (expr) {
          cest_print_expr(true, expr_cstr);
          cest.assertions_failed++;

          cest_print_test_result();
          exit(1);
     } else {
          cest_print_expr(false, expr_cstr);
     }
}

// Assert equal
static void cest_assert_eq_char(const char *file, size_t line, const char *func,
                               const char *left_cstr, char left,
                               const char *right_cstr, char right)
{
     cest.assertions++;
     if (left != right) {
          cest_print_binary(true, CEST_Eq_Fmt, left_cstr, right_cstr);
          fprintf(stderr, "    "CEST_Cstr_Left":  %c\n", left);
          fprintf(stderr, "    "CEST_Cstr_Right": %c\n", right);
          cest.assertions_failed++;

          cest_print_test_result();
          exit(1);
     } else {
          cest_print_binary(false, CEST_Eq_Fmt, left_cstr, right_cstr);
     }
}

static void cest_assert_eq_cstr(const char *file, size_t line, const char *func,
                               const char *left_cstr, const char *left,
                                const char *right_cstr, const char *right)
{
     cest.assertions++;
     if (strcmp(left, right) != 0) {
          cest_print_binary(true, CEST_Eq_Fmt, left_cstr, right_cstr);
          fprintf(stderr, "    "CEST_Cstr_Left":  %s\n", left);
          fprintf(stderr, "    "CEST_Cstr_Right": %s\n", right);
          cest.assertions_failed++;

          cest_print_test_result();
          exit(1);
     } else {
          cest_print_binary(false, CEST_Eq_Fmt, left_cstr, right_cstr);
     }
}

static void cest_assert_eq_int(const char *file, size_t line, const char *func,
                               const char *left_cstr, int left,
                               const char *right_cstr, int right)
{
     cest.assertions++;
     if (left != right) {
          cest_print_binary(true, CEST_Eq_Fmt, left_cstr, right_cstr);
          fprintf(stderr, "    "CEST_Cstr_Left":  %d\n", left);
          fprintf(stderr, "    "CEST_Cstr_Right": %d\n", right);
          cest.assertions_failed++;

          cest_print_test_result();
          exit(1);
     } else {
          cest_print_binary(false, CEST_Eq_Fmt, left_cstr, right_cstr);
     }
}

static void cest_assert_eq_size_t(const char *file, size_t line, const char *func,
                                  const char *left_cstr, size_t left,
                                  const char *right_cstr, size_t right)
{
     cest.assertions++;
     if (left != right) {
          cest_print_binary(true, CEST_Eq_Fmt, left_cstr, right_cstr);
          fprintf(stderr, "    "CEST_Cstr_Left":  %zu\n", left);
          fprintf(stderr, "    "CEST_Cstr_Right": %zu\n", right);
          cest.assertions_failed++;

          cest_print_test_result();
          exit(1);
     } else {
          cest_print_binary(false, CEST_Eq_Fmt, left_cstr, right_cstr);
     }
}

// Expects
static void cest_expect_true(const char *file, size_t line, const char *func,
                             const char *expr_cstr, bool expr)
{
     cest.assertions++;
     if (!expr) {
          cest_print_expr(true, expr_cstr);
          cest.assertions_failed++;
     } else {
          cest_print_expr(false, expr_cstr);
     }
}

static void cest_expect_false(const char *file, size_t line, const char *func,
                              const char *expr_cstr, bool expr)
{
     cest.assertions++;
     if (expr) {
          cest_print_expr(true, expr_cstr);
          cest.assertions_failed++;
     } else {
          cest_print_expr(false, expr_cstr);
     }
}

// Expect equal
static void cest_expect_eq_char(const char *file, size_t line, const char *func,
                                const char *left_cstr, char left,
                                const char *right_cstr, char right)
{
     cest.assertions++;
     if (left != right) {
          cest_print_binary(true, CEST_Eq_Fmt, left_cstr, right_cstr);
          fprintf(stderr, "    "CEST_Cstr_Left":  %c\n", left);
          fprintf(stderr, "    "CEST_Cstr_Right": %c\n", right);
          cest.assertions_failed++;
     } else {
          cest_print_binary(false, CEST_Eq_Fmt, left_cstr, right_cstr);
     }
}

static void cest_expect_eq_cstr(const char *file, size_t line, const char *func,
                                const char *left_cstr, const char *left,
                                const char *right_cstr,const char *right)
{
     cest.assertions++;
     if (strcmp(left, right) != 0) {
          cest_print_binary(true, CEST_Eq_Fmt, left_cstr, right_cstr);
          fprintf(stderr, "    "CEST_Cstr_Left":  %s\n", left);
          fprintf(stderr, "    "CEST_Cstr_Right": %s\n", right);
          cest.assertions_failed++;
     } else {
          cest_print_binary(false, CEST_Eq_Fmt, left_cstr, right_cstr);
     }
}

static void cest_expect_eq_int(const char *file, size_t line, const char *func,
                               const char *left_cstr, int left,
                               const char *right_cstr, int right)
{
     cest.assertions++;
     if (left != right) {
          cest_print_binary(true, CEST_Eq_Fmt, left_cstr, right_cstr);
          fprintf(stderr, "    "CEST_Cstr_Left":  %d\n", left);
          fprintf(stderr, "    "CEST_Cstr_Right": %d\n", right);
          cest.assertions_failed++;
     } else {
          cest_print_binary(false, CEST_Eq_Fmt, left_cstr, right_cstr);
     }
}

static void cest_expect_eq_size_t(const char *file, size_t line, const char *func,
                                  const char *left_cstr, size_t left,
                                  const char *right_cstr, size_t right)
{
     cest.assertions++;
     if (left != right) {
          cest_print_binary(true, CEST_Eq_Fmt, left_cstr, right_cstr);
          fprintf(stderr, "    "CEST_Cstr_Left":  %zu\n", left);
          fprintf(stderr, "    "CEST_Cstr_Right": %zu\n", right);
          cest.assertions_failed++;
     } else {
          cest_print_binary(false, CEST_Eq_Fmt, left_cstr, right_cstr);
     }
}

#endif // CEST_H_
