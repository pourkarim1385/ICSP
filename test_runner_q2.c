#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_TESTS 30
#define MAX_INPUT_LEN 5000
#define MAX_OUTPUT_LEN 1000
#define MY_PROGRAM "sleep_analysis.exe"
#define SOLUTION_PROGRAM "sleep_analysis_solution.exe"
#define TEMP_INPUT "temp_input.txt"
#define TEMP_OUTPUT_MY "temp_output_my.txt"
#define TEMP_OUTPUT_SOL "temp_output_sol.txt"

typedef struct {
    char input[MAX_INPUT_LEN];
    char expected[MAX_OUTPUT_LEN];
    char my_output[MAX_OUTPUT_LEN];
    int passed;
} TestCase;

// تابع برای حذف فضاهای اضافی
void trim_string(char *str) {
    int i = 0, j = 0;
    int last_char = -1;
    
    while (str[i]) {
        if (!isspace(str[i])) {
            last_char = j;
            str[j++] = str[i];
        } else {
            if (last_char >= 0 && str[last_char] != ' ') {
                str[j++] = ' ';
            }
        }
        i++;
    }
    
    if (j > 0 && str[j-1] == ' ') j--;
    str[j] = '\0';
}

// اجرای یک برنامه با ورودی داده شده و ذخیره خروجی
int run_program(const char *program, const char *input, char *output) {
    // ایجاد فایل ورودی موقت
    FILE *f_temp = fopen(TEMP_INPUT, "w");
    if (!f_temp) return 0;
    fprintf(f_temp, "%s", input);
    fclose(f_temp);
    
    // اجرای برنامه
    char command[256];
    sprintf(command, "%s < %s > %s", program, TEMP_INPUT, 
            (strcmp(program, MY_PROGRAM) == 0) ? TEMP_OUTPUT_MY : TEMP_OUTPUT_SOL);
    
    int ret = system(command);
    if (ret != 0) {
        sprintf(output, "Program crashed (exit code: %d)", ret);
        return 0;
    }
    
    // خواندن خروجی
    const char *output_file = (strcmp(program, MY_PROGRAM) == 0) ? 
                              TEMP_OUTPUT_MY : TEMP_OUTPUT_SOL;
    FILE *f_out = fopen(output_file, "r");
    if (!f_out) {
        sprintf(output, "Could not read output file");
        return 0;
    }
    
    output[0] = '\0';
    char line[256];
    while (fgets(line, sizeof(line), f_out)) {
        strcat(output, line);
    }
    fclose(f_out);
    
    trim_string(output);
    return 1;
}

// آرایه تست‌ها (همان 25 تست قبلی)
TestCase tests[MAX_TESTS] = {
    // Test 1
    {"5\n2310-0710\n0100-0630\n0215-0545\n0030-1130\n2345-0615\n", "", "", 0},
    
    // Test 2
    {"3\n2200-0600\n2230-0630\n2300-0700\n", "", "", 0},
    
    // Test 3
    {"4\n0400-0930\n0330-0830\n0245-0745\n0100-0600\n", "", "", 0},
    
    // Test 4
    {"2\n0001-0959\n2359-0958\n", "", "", 0},
    
    // Test 5
    {"2\n0000-0600\n0100-0700\n", "", "", 0},
    
    // Test 6
    {"3\n0010-1005\n0045-1100\n2345-0900\n", "", "", 0},
    
    // Test 7
    {"1\n2000-0500\n", "", "", 0},
    
    // Test 8
    {"1\n2000-0459\n", "", "", 0},
    
    // Test 9
    {"1\n2000-1100\n", "", "", 0},
    
    // Test 10
    {"1\n2359-0500\n", "", "", 0},
    
    // Test 11
    {"2\n2359-0001\n0001-0500\n", "", "", 0},
    
    // Test 12
    {"2\n2359-0005\n2358-0004\n", "", "", 0},
    
    // Test 13 (15 nights)
    {"15\n2200-0600\n2215-0615\n2230-0630\n2245-0645\n2300-0700\n"
     "2315-0715\n2330-0730\n2345-0745\n0000-0800\n0015-0815\n"
     "0100-0900\n0200-1000\n0300-1100\n0400-1200\n2000-1959\n", "", "", 0},
    
    // Test 14
    {"1\n0000-1000\n", "", "", 0},
    
    // Test 15
    {"1\n2000-1959\n", "", "", 0},
    
    // Test 16
    {"1\n2000-0500\n", "", "", 0},
    
    // Test 17
    {"1\n0100-0900\n", "", "", 0},
    
    // Test 18
    {"1\n0459-1001\n", "", "", 0},
    
    // Test 19
    {"4\n2345-0715\n0020-0820\n0320-0920\n2200-0600\n", "", "", 0},
    
    // Test 20
    {"5\n2200-0600\n2200-0600\n2200-0600\n2200-0600\n2200-0600\n", "", "", 0},
    
    // Test 21 (50 nights - massive test)
    {"50\n"
     "2200-0600\n2200-0600\n2200-0600\n2200-0600\n2200-0600\n"
     "2200-0600\n2200-0600\n2200-0600\n2200-0600\n2200-0600\n"
     "2200-0600\n2200-0600\n2200-0600\n2200-0600\n2200-0600\n"
     "2200-0600\n2200-0600\n2200-0600\n2200-0600\n2200-0600\n"
     "2200-0600\n2200-0600\n2200-0600\n2200-0600\n2200-0600\n"
     "2200-0600\n2200-0600\n2200-0600\n2200-0600\n2200-0600\n"
     "2200-0600\n2200-0600\n2200-0600\n2200-0600\n2200-0600\n"
     "2200-0600\n2200-0600\n2200-0600\n2200-0600\n2200-0600\n"
     "2200-0600\n2200-0600\n2200-0600\n2200-0600\n2200-0600\n"
     "2200-0600\n2200-0600\n2200-0600\n2200-0600\n2200-0600\n", "", "", 0},
    
    // Test 22 (30 nights with pattern)
    {"30\n"
     "2000-0500\n2001-0501\n2002-0502\n2003-0503\n2004-0504\n"
     "2005-0505\n2006-0506\n2007-0507\n2008-0508\n2009-0509\n"
     "2010-0510\n2011-0511\n2012-0512\n2013-0513\n2014-0514\n"
     "2015-0515\n2016-0516\n2017-0517\n2018-0518\n2019-0519\n"
     "2020-0520\n2021-0521\n2022-0522\n2023-0523\n2024-0524\n"
     "2025-0525\n2026-0526\n2027-0527\n2028-0528\n2029-0529\n", "", "", 0},
    
    // Test 23 (all irregular)
    {"5\n2000-1001\n2100-1100\n2200-1200\n2300-1300\n0000-1400\n", "", "", 0},
    
    // Test 24 (exactly 6 hours)
    {"3\n0000-0600\n0100-0700\n0200-0800\n", "", "", 0},
    
    // Test 25 (varying sleep times)
    {"7\n2000-0600\n2100-0600\n2200-0600\n2300-0600\n"
     "0000-0600\n0100-0600\n0200-0600\n", "", "", 0},
    
    // Test 26 (1 night, minimum sleep)
    {"1\n0459-0500\n", "", "", 0},
    
    // Test 27 (1 night, maximum sleep in range)
    {"1\n2000-1959\n", "", "", 0},
    
    // Test 28 (sleep at 20:00, wake at 10:00 - irregular)
    {"1\n2000-1000\n", "", "", 0},
    
    // Test 29 (sleep at 00:00, wake at 05:00 - low sleep)
    {"1\n0000-0500\n", "", "", 0},
    
    // Test 30 (mixed with all conditions)
    {"6\n2000-0500\n2200-1000\n0000-0600\n"
     "0100-0900\n0200-0800\n0300-0700\n", "", "", 0}
};

int main() {
    printf("Compiling programs...\n");
    
    // کامپایل برنامه شما
    if (system("gcc -o sleep_analysis sleep_analysis.c") != 0) {
        fprintf(stderr, "Failed to compile sleep_analysis.c\n");
        return 1;
    }
    
    // کامپایل برنامه جواب
    if (system("gcc -o sleep_analysis_solution sleep_analysis_solution.c") != 0) {
        fprintf(stderr, "Failed to compile sleep_analysis_solution.c\n");
        remove("sleep_analysis.exe");
        return 1;
    }
    
    printf("Compilation successful.\n\n");
    printf("Running %d tests...\n\n", MAX_TESTS);
    
    int passed = 0, failed = 0;
    int failed_ids[MAX_TESTS];
    
    // اجرای تست‌ها
    for (int i = 0; i < MAX_TESTS; i++) {
        // دریافت خروجی از برنامه جواب (expected)
        if (!run_program(SOLUTION_PROGRAM, tests[i].input, tests[i].expected)) {
            printf("F");
            failed_ids[failed++] = i + 1;
            continue;
        }
        
        // دریافت خروجی از برنامه شما (my_output)
        if (!run_program(MY_PROGRAM, tests[i].input, tests[i].my_output)) {
            printf("F");
            failed_ids[failed++] = i + 1;
            continue;
        }
        
        // مقایسه
        if (strcmp(tests[i].my_output, tests[i].expected) == 0) {
            printf(".");
            tests[i].passed = 1;
            passed++;
        } else {
            printf("F");
            tests[i].passed = 0;
            failed_ids[failed++] = i + 1;
        }
        
        fflush(stdout);
    }
    
    // چاپ کارنامه
    printf("\n\n");
    printf("========================================\n");
    printf("            TESTING COMPLETE           \n");
    printf("========================================\n");
    printf("Total Tests Run: %d\n", MAX_TESTS);
    printf("Tests Passed: %d\n", passed);
    printf("Tests Failed: %d\n", failed);
    printf("Success Rate: %.1f%%\n", (passed * 100.0) / MAX_TESTS);
    
    if (failed > 0) {
        printf("\nFailed Tests: ");
        for (int i = 0; i < failed; i++) {
            printf("%d", failed_ids[i]);
            if (i < failed - 1) printf(", ");
        }
        printf("\n");
        
        printf("\nDetails of Failed Tests:\n");
        printf("========================\n");
        
        for (int i = 0; i < failed; i++) {
            int test_id = failed_ids[i];
            TestCase *test = &tests[test_id - 1];
            
            printf("\n--- Test %d ---\n", test_id);
            printf("Input:\n%s", test->input);
            printf("\nExpected Output (from solution):\n%s\n", test->expected);
            printf("\nYour Output:\n%s\n", test->my_output);
            printf("----------------\n");
        }
    } else {
        printf("\n🎉 All tests passed successfully!\n");
    }
    
    printf("========================================\n");
    
    // پاکسازی
    remove(TEMP_INPUT);
    remove(TEMP_OUTPUT_MY);
    remove(TEMP_OUTPUT_SOL);
    remove(MY_PROGRAM);
    remove(SOLUTION_PROGRAM);
    
    return 0;
}