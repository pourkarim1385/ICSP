#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_TESTS 40
#define MAX_INPUT_SIZE 10000
#define INPUT_FILE "test_input.txt"
#define OUTPUT_FILE1 "output1.txt"
#define OUTPUT_FILE2 "output2.txt"
#define EXECUTABLE1 "program1.exe"
#define EXECUTABLE2 "program2.exe"

typedef struct {
    int id;
    char* input;
    char output1[500];
    char output2[500];
    int passed;
    int input_size;
} TestCase;

void create_input_file(const char* content) {
    FILE *f = fopen(INPUT_FILE, "w");
    if (!f) {
        perror("Failed to create input file");
        exit(1);
    }
    fprintf(f, "%s", content);
    fclose(f);
}

int run_program(const char* exe_name, const char* output_file) {
    char command[256];
    sprintf(command, "%s < %s > %s 2>nul", exe_name, INPUT_FILE, output_file);
    return system(command);
}

void read_output(const char* filename, char* buffer, int max_size) {
    FILE *f = fopen(filename, "r");
    if (!f) {
        strcpy(buffer, "[NO OUTPUT]");
        return;
    }
    
    buffer[0] = '\0';
    char line[256];
    int first_line = 1;
    
    while (fgets(line, sizeof(line), f)) {
        // Remove trailing newline and whitespace
        size_t len = strlen(line);
        while (len > 0 && (line[len-1] == '\n' || line[len-1] == '\r' || line[len-1] == ' ')) {
            line[--len] = '\0';
        }
        
        if (!first_line) {
            strcat(buffer, " | ");
        }
        strcat(buffer, line);
        first_line = 0;
    }
    
    fclose(f);
}

int compare_outputs(const char* output1, const char* output2) {
    // Normalize strings before comparison
    char norm1[500], norm2[500];
    strcpy(norm1, output1);
    strcpy(norm2, output2);
    
    // Remove extra spaces
    for (int i = 0; norm1[i]; i++) if (norm1[i] == '\t') norm1[i] = ' ';
    for (int i = 0; norm2[i]; i++) if (norm2[i] == '\t') norm2[i] = ' ';
    
    return strcmp(norm1, norm2) == 0;
}

void generate_smart_test(char** input_ptr, int test_id) {
    char* input = malloc(MAX_INPUT_SIZE);
    if (!input) {
        *input_ptr = NULL;
        return;
    }
    
    input[0] = '\0';
    
    switch(test_id) {
        case 1: // Example from problem
            strcpy(input, "4\n6 5 30\n5 6 32\n6 7 33\n7 8 35\n");
            break;
            
        case 2: // Single session
            strcpy(input, "1\n5 10 30\n");
            break;
            
        case 3: // Two improving
            strcpy(input, "2\n3 8 25\n4 9 26\n");
            break;
            
        case 4: // Two declining
            strcpy(input, "2\n8 12 40\n7 11 39\n");
            break;
            
        case 5: // All same values (avg=5)
            strcpy(input, "5\n5 10 30\n5 10 30\n5 10 30\n5 10 30\n5 10 30\n");
            break;
            
        case 6: // All same values (avg=6)
            strcpy(input, "5\n6 10 30\n6 10 30\n6 10 30\n6 10 30\n6 10 30\n");
            break;
            
        case 7: // Strictly improving
            strcpy(input, "5\n1 5 20\n2 6 21\n3 7 22\n4 8 23\n5 9 24\n");
            break;
            
        case 8: // Strictly declining
            strcpy(input, "5\n10 20 50\n9 19 48\n8 18 46\n7 17 44\n6 16 42\n");
            break;
            
        case 9: // Stable - mixed
            strcpy(input, "5\n5 10 30\n6 9 31\n5 11 29\n6 8 32\n5 12 28\n");
            break;
            
        case 10: // Time constant, success increasing
            strcpy(input, "5\n5 5 30\n5 6 30\n5 7 30\n5 8 30\n5 9 30\n");
            break;
            
        case 11: // Success constant, time decreasing
            strcpy(input, "5\n6 10 40\n6 10 39\n6 10 38\n6 10 37\n6 10 36\n");
            break;
            
        case 12: // Edge: difficulty = 1 always
            strcpy(input, "5\n1 15 25\n1 16 26\n1 17 27\n1 18 28\n1 19 29\n");
            break;
            
        case 13: // Edge: difficulty = 10 always
            strcpy(input, "5\n10 15 25\n10 16 26\n10 17 27\n10 18 28\n10 19 29\n");
            break;
            
        case 14: // Average exactly 5.0
            strcpy(input, "3\n4 10 30\n5 11 31\n6 12 32\n");
            break;
            
        case 15: // Zero or one record edge cases
            strcpy(input, "0\n");
            break;
            
        case 16: // Large test 20 records - improving
            sprintf(input, "20\n");
            for (int i = 0; i < 20; i++) {
                char line[50];
                sprintf(line, "%d %d %d\n", 
                        (i % 5) + 1, 
                        10 + i, 
                        20 + i);
                strcat(input, line);
            }
            break;
            
        case 17: // Large test 20 records - declining
            sprintf(input, "20\n");
            for (int i = 0; i < 20; i++) {
                char line[50];
                sprintf(line, "%d %d %d\n", 
                        10 - (i % 5), 
                        50 - i, 
                        60 - i);
                strcat(input, line);
            }
            break;
            
        case 18: // Test with max values
            sprintf(input, "10\n");
            for (int i = 0; i < 10; i++) {
                strcat(input, "10 100 1000\n");
            }
            break;
            
        case 19: // Test with min values
            sprintf(input, "10\n");
            for (int i = 0; i < 10; i++) {
                strcat(input, "1 1 1\n");
            }
            break;
            
        case 20: // Random small test
            srand(12345);
            sprintf(input, "8\n");
            for (int i = 0; i < 8; i++) {
                char line[50];
                sprintf(line, "%d %d %d\n", 
                        rand() % 10 + 1,
                        rand() % 50 + 1,
                        rand() % 100 + 20);
                strcat(input, line);
            }
            break;
            
        case 21: // Pattern: up then down
            sprintf(input, "6\n");
            strcat(input, "5 10 30\n");
            strcat(input, "6 11 31\n");
            strcat(input, "7 12 32\n");
            strcat(input, "6 11 31\n");
            strcat(input, "5 10 30\n");
            strcat(input, "4 9 29\n");
            break;
            
        case 22: // Only difficulty changes
            sprintf(input, "7\n");
            for (int i = 0; i < 7; i++) {
                char line[50];
                sprintf(line, "%d 25 35\n", (i % 10) + 1);
                strcat(input, line);
            }
            break;
            
        case 23: // Only success changes
            sprintf(input, "7\n");
            for (int i = 0; i < 7; i++) {
                char line[50];
                sprintf(line, "5 %d 35\n", 20 + ((i % 2) ? i : -i));
                strcat(input, line);
            }
            break;
            
        case 24: // Only time changes
            sprintf(input, "7\n");
            for (int i = 0; i < 7; i++) {
                char line[50];
                sprintf(line, "5 25 %d\n", 30 + ((i % 3) ? i : -i));
                strcat(input, line);
            }
            break;
            
        case 25: // Medium test 30 records
            sprintf(input, "30\n");
            for (int i = 0; i < 30; i++) {
                char line[50];
                int pattern = i % 4;
                int diff, succ, time;
                
                switch(pattern) {
                    case 0: diff = 3; succ = 15 + i; time = 25 + i; break;
                    case 1: diff = 7; succ = 45 - i; time = 55 - i; break;
                    case 2: diff = 5; succ = 25; time = 35 + (i % 3); break;
                    default: diff = (i % 10) + 1; succ = 20 + (i % 5); time = 30 + (i % 7);
                }
                
                sprintf(line, "%d %d %d\n", diff, succ, time);
                strcat(input, line);
            }
            break;
            
        case 26: // Boundary: time equal, success equal
            sprintf(input, "5\n");
            for (int i = 0; i < 5; i++) {
                strcat(input, "5 20 30\n");
            }
            break;
            
        case 27: // Test with negative patterns? No, all positive
            sprintf(input, "6\n");
            strcat(input, "8 15 40\n");
            strcat(input, "7 14 41\n"); // time up but diff down
            strcat(input, "9 13 39\n"); // time down
            strcat(input, "6 16 42\n"); // success up
            strcat(input, "10 12 38\n");
            strcat(input, "5 17 43\n");
            break;
            
        case 28: // All values decreasing but diff <= 5
            sprintf(input, "5\n");
            for (int i = 0; i < 5; i++) {
                char line[50];
                sprintf(line, "%d %d %d\n", 
                        5 - (i % 3),
                        30 - i * 2,
                        40 - i * 2);
                strcat(input, line);
            }
            break;
            
        case 29: // All values increasing but diff > 5
            sprintf(input, "5\n");
            for (int i = 0; i < 5; i++) {
                char line[50];
                sprintf(line, "%d %d %d\n", 
                        6 + (i % 3),
                        10 + i * 2,
                        20 + i * 2);
                strcat(input, line);
            }
            break;
            
        case 30: // Large test 50 records - stable pattern
            sprintf(input, "50\n");
            for (int i = 0; i < 50; i++) {
                char line[50];
                int diff = (i * 7) % 10 + 1;
                int succ = 25 + ((i % 3) ? 1 : -1) * (i % 7);
                int time = 35 + ((i % 2) ? 1 : -1) * (i % 5);
                sprintf(line, "%d %d %d\n", diff, succ, time);
                strcat(input, line);
            }
            break;
            
        case 31: // Test with exactly 2 records edge cases
            sprintf(input, "2\n");
            strcat(input, "5 10 30\n");
            strcat(input, "5 10 30\n");
            break;
            
        case 32: // Test with exactly 3 records
            sprintf(input, "3\n");
            strcat(input, "3 5 20\n");
            strcat(input, "4 6 21\n");
            strcat(input, "5 7 22\n");
            break;
            
        case 33: // Complex: periodic pattern
            sprintf(input, "12\n");
            for (int i = 0; i < 12; i++) {
                char line[50];
                int phase = i % 3;
                int diff = phase == 0 ? 4 : (phase == 1 ? 7 : 5);
                int succ = 20 + phase * 3;
                int time = 30 + (i % 4);
                sprintf(line, "%d %d %d\n", diff, succ, time);
                strcat(input, line);
            }
            break;
            
        case 34: // Test with whitespace variations
            sprintf(input, "3\n");
            strcat(input, "6   5     30\n");
            strcat(input, "5 6 32\n");
            strcat(input, "6 7 33\n");
            break;
            
        case 35: // Test with \r\n line endings
            sprintf(input, "3\r\n");
            strcat(input, "5 10 30\r\n");
            strcat(input, "6 11 31\r\n");
            strcat(input, "7 12 32\r\n");
            break;
            
        case 36: // Stress test 100 records but simple pattern
            sprintf(input, "100\n");
            for (int i = 0; i < 100; i++) {
                char line[50];
                sprintf(line, "5 %d %d\n", 20 + (i % 10), 30 + (i % 15));
                strcat(input, line);
            }
            break;
            
        case 37: // Test with decreasing then constant
            sprintf(input, "6\n");
            strcat(input, "8 20 50\n");
            strcat(input, "7 19 48\n");
            strcat(input, "6 18 46\n");
            strcat(input, "6 18 46\n");
            strcat(input, "6 18 46\n");
            strcat(input, "6 18 46\n");
            break;
            
        case 38: // Test with increasing then constant
            sprintf(input, "6\n");
            strcat(input, "3 10 20\n");
            strcat(input, "4 12 22\n");
            strcat(input, "5 14 24\n");
            strcat(input, "5 14 24\n");
            strcat(input, "5 14 24\n");
            strcat(input, "5 14 24\n");
            break;
            
        case 39: // Real-world simulation
            sprintf(input, "15\n");
            // Simulate an athlete having good and bad days
            int diff_pattern[] = {3, 7, 4, 8, 5, 6, 4, 7, 5, 6, 3, 8, 4, 7, 5};
            int succ_pattern[] = {15, 12, 18, 10, 20, 14, 19, 11, 21, 13, 17, 9, 22, 12, 20};
            int time_pattern[] = {28, 32, 26, 34, 25, 30, 27, 33, 24, 31, 29, 35, 23, 32, 26};
            
            for (int i = 0; i < 15; i++) {
                char line[50];
                sprintf(line, "%d %d %d\n", diff_pattern[i], succ_pattern[i], time_pattern[i]);
                strcat(input, line);
            }
            break;
            
        case 40: // Final comprehensive test
            sprintf(input, "25\n");
            for (int i = 0; i < 25; i++) {
                char line[50];
                // Create a pattern that tests all conditions
                int diff, succ, time;
                
                if (i < 5) {
                    // First 5: improving pattern
                    diff = (i % 4) + 2;
                    succ = 10 + i * 2;
                    time = 20 + i;
                } else if (i < 10) {
                    // Next 5: declining pattern
                    diff = 10 - (i % 4);
                    succ = 40 - (i-5) * 2;
                    time = 50 - (i-5);
                } else if (i < 15) {
                    // Next 5: stable mixed
                    diff = (i % 10) + 1;
                    succ = 25 + ((i % 2) ? 3 : -3);
                    time = 35 + ((i % 3) ? 2 : -2);
                } else if (i < 20) {
                    // Next 5: all same
                    diff = 5;
                    succ = 20;
                    time = 30;
                } else {
                    // Last 5: random
                    diff = ((i * 13) % 10) + 1;
                    succ = ((i * 17) % 30) + 10;
                    time = ((i * 19) % 40) + 20;
                }
                
                sprintf(line, "%d %d %d\n", diff, succ, time);
                strcat(input, line);
            }
            break;
            
        default:
            // Fallback: simple test
            strcpy(input, "3\n5 10 30\n5 10 30\n5 10 30\n");
    }
    
    *input_ptr = input;
}

int main() {
    printf("=========================================\n");
    printf("OPTIMIZED TEST RUNNER - ATHLETE ANALYSIS\n");
    printf("=========================================\n\n");
    
    // Check if source files exist
    FILE *f1 = fopen("program1.c", "r");
    FILE *f2 = fopen("program2.c", "r");
    
    if (!f1 || !f2) {
        printf("ERROR: Missing source files!\n");
        printf("Please ensure both program1.c and program2.c exist.\n");
        if (f1) fclose(f1);
        if (f2) fclose(f2);
        return 1;
    }
    fclose(f1);
    fclose(f2);
    
    printf("Compiling programs...\n");
    
    // Compile with simple commands
    int compile1 = system("gcc -o program1 program1.c 2>nul");
    int compile2 = system("gcc -o program2 program2.c 2>nul");
    
    if (compile1 != 0 || compile2 != 0) {
        printf("Compilation failed!\n");
        if (compile1 != 0) printf("  program1.c failed to compile\n");
        if (compile2 != 0) printf("  program2.c failed to compile\n");
        return 1;
    }
    
    printf("Compilation successful.\n\n");
    printf("Generating test cases...\n");
    
    // Allocate and generate test cases
    TestCase tests[MAX_TESTS];
    for (int i = 0; i < MAX_TESTS; i++) {
        tests[i].id = i + 1;
        tests[i].input = NULL;
        tests[i].passed = 0;
        generate_smart_test(&tests[i].input, i + 1);
        
        if (!tests[i].input) {
            printf("Warning: Failed to generate test case %d\n", i + 1);
            // Create a simple fallback test
            tests[i].input = malloc(100);
            if (tests[i].input) {
                strcpy(tests[i].input, "2\n5 10 30\n5 10 30\n");
            }
        }
    }
    
    printf("Running %d test cases...\n\n", MAX_TESTS);
    
    int passed = 0;
    clock_t start_time = clock();
    
    for (int i = 0; i < MAX_TESTS; i++) {
        printf("Test %2d/%2d: ", i + 1, MAX_TESTS);
        fflush(stdout);
        
        if (!tests[i].input) {
            printf("SKIP (no input)\n");
            continue;
        }
        
        // Create input file
        create_input_file(tests[i].input);
        
        // Run programs
        int ret1 = run_program(EXECUTABLE1, OUTPUT_FILE1);
        int ret2 = run_program(EXECUTABLE2, OUTPUT_FILE2);
        
        if (ret1 != 0 || ret2 != 0) {
            printf("ERROR (program crashed)\n");
            strcpy(tests[i].output1, "[CRASHED]");
            strcpy(tests[i].output2, "[CRASHED]");
            continue;
        }
        
        // Read outputs
        read_output(OUTPUT_FILE1, tests[i].output1, sizeof(tests[i].output1));
        read_output(OUTPUT_FILE2, tests[i].output2, sizeof(tests[i].output2));
        
        // Compare
        tests[i].passed = compare_outputs(tests[i].output1, tests[i].output2);
        
        if (tests[i].passed) {
            printf("PASS ✓\n");
            passed++;
        } else {
            printf("FAIL ✗\n");
        }
    }
    
    clock_t end_time = clock();
    double elapsed = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    
    printf("\n=========================================\n");
    printf("RESULTS SUMMARY\n");
    printf("=========================================\n");
    printf("Total Tests:    %d\n", MAX_TESTS);
    printf("Tests Passed:   %d\n", passed);
    printf("Tests Failed:   %d\n", MAX_TESTS - passed);
    printf("Success Rate:   %.1f%%\n", (passed * 100.0) / MAX_TESTS);
    printf("Time Elapsed:   %.2f seconds\n", elapsed);
    
    // Show failed tests
    if (passed < MAX_TESTS) {
        printf("\nFailed Tests:\n");
        printf("-------------\n");
        
        for (int i = 0; i < MAX_TESTS; i++) {
            if (!tests[i].passed) {
                printf("\nTest #%d:\n", tests[i].id);
                
                // Show first few lines of input
                char first_lines[200];
                strncpy(first_lines, tests[i].input, 150);
                first_lines[150] = '\0';
                
                // Count lines
                int lines = 0;
                for (int j = 0; tests[i].input[j] && lines < 3; j++) {
                    if (tests[i].input[j] == '\n') lines++;
                }
                
                printf("Input (first %d lines):\n%s...\n", 
                       lines < 3 ? lines : 3, first_lines);
                
                printf("Output 1: %s\n", tests[i].output1);
                printf("Output 2: %s\n", tests[i].output2);
            }
        }
    } else {
        printf("\n🎉 EXCELLENT! All tests passed!\n");
    }
    
    // Cleanup
    printf("\nCleaning up...\n");
    
    // Free allocated memory
    for (int i = 0; i < MAX_TESTS; i++) {
        if (tests[i].input) {
            free(tests[i].input);
        }
    }
    
    // Remove temporary files
    remove(INPUT_FILE);
    remove(OUTPUT_FILE1);
    remove(OUTPUT_FILE2);
    remove(EXECUTABLE1);
    remove(EXECUTABLE2);
    
    printf("Done.\n");
    printf("=========================================\n");
    
    return 0;
}
