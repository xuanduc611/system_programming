#include "my_lib.h"

static int print_numbers(const char *input);

/**
 * @param input: The number string passed to the program. The format of string would be: "1234 425 -239"
 * @return The total count of numbers printed.
*/
static int print_numbers(const char *input)
{
    int cnt = 0;
    int i, space_cnt;
    int int_to_console;
    char *temp_str;

    printf("Input: [%s]\r\n", input);

    if (input == NULL) {
        return cnt;
    }

    // Count space char in input string:
    space_cnt = ml_char_cnt(input, ' ');

    printf("space_cnt = %d\r\n", space_cnt);
    if (space_cnt == 0) {
        space_cnt++;
        cnt = space_cnt;
    }

    printf("[debug]%s, line(%d)\r\n", __FUNCTION__, __LINE__);

    for (i = 0; i <= space_cnt; i++) {
        printf("******loop[%d]******\r\n", i);
        if (i == 0) {
            int_to_console = atoi(input);
            printf("Res: %d\r\n", int_to_console);
            
            // Get the next string after space char:
            temp_str = strchr(input, SPACE_CHAR);
        } else {
            printf("Check temp_str before atoi(): [%s]\r\n", temp_str);
            int_to_console = atoi(temp_str);
            printf("Res: %d\r\n", int_to_console);
            
            if (i == space_cnt) {
                break;
            }

            // Get the next string after space char:
            // The first char of string after execution of strchr(str, c) is 'c'
            temp_str = strchr(temp_str + 1, SPACE_CHAR);
        }
    }

    return cnt;
}

int main(int argc, char** argv)
{
    char input_str[100];

    while(1) {
        printf("Enter string: ");

        if (fgets(input_str, sizeof(input_str), stdin) == NULL) {
            printf("Invalid string\r\n");
            return(-1);
        }
        
        // Replace newline character with null character:
        if ((input_str[strlen(input_str) - 1] == '\r') || (input_str[strlen(input_str) - 1] == '\n')) {
            input_str[strlen(input_str) - 1] = '\0';
        }

        print_numbers(input_str);
    }

    return(0);
}
