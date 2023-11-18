/*

2023FA-ENGR-2304-81001-DYER-JOSHUA-P02

*/

#include <stdio.h>
#include <string.h>
#include <math.h>

// Function to convert a decimal number to binary in two's complement
void decimalToBinary(int decimalNumber, int numBits) {
    if (decimalNumber < -127 || decimalNumber > 127) {
        printf("Number out of range.\n");
        return;
    }

    int binaryNumber[64]; // Assuming a 64-bit binary representation
    int index = numBits - 1; // Start from the most significant bit

    // Handle negative numbers within the specified range
    if (decimalNumber < 0) {
        decimalNumber += (1 << numBits); // Convert to equivalent positive number
    }

    while (index >= 0) {
        binaryNumber[index] = decimalNumber % 2;
        decimalNumber /= 2;
        index--;
    }

    printf("Binary: ");
    for (int i = 0; i < numBits; i++) {
        printf("%d", binaryNumber[i]);
    }
    printf("\n");
}

// Function to convert a binary string to decimal using two's complement
int binaryToDecimal(const char *binaryString, int numBits) {
    int len = strlen(binaryString);

    if (len > numBits) {
        printf("Binary number exceeds %d bits.\n", numBits);
        return 0;
    }

    int decimalNumber = 0;
    int signBit = (binaryString[0] == '1') ? 1 : 0;

    // Handle negative numbers within the specified range
    if (signBit == 1) {
        int carry = 1;
        for (int i = len - 1; i >= 0; i--) {
            if (binaryString[i] == '0') {
                if (carry == 1) {
                    decimalNumber += (1 << (len - 1 - i));
                }
            } else {
                if (carry == 0) {
                    decimalNumber += (1 << (len - 1 - i));
                }
            }
        }
        decimalNumber = -(decimalNumber + 1); // Apply two's complement for negative value
    } else {
        for (int i = len - 1; i > 0; i--) {
            if (binaryString[i] == '1') {
                decimalNumber += (1 << (len - 1 - i));
            }
        }
    }

    // Check if the result is within the specified range
    if (decimalNumber < -127 || decimalNumber > 127) {
        printf("Number out of range.\n");
        return 0;
    }

    return decimalNumber;
}

// Function to convert a binary string to hexadecimal with up to 64 bits
void binaryToHex(const char *binaryString) {
    int len = strlen(binaryString);
    int padding = 64 - len;

    printf("Hexadecimal: ");
    for (int i = 0; i < padding; i++) {
        printf("0"); // Pad with leading zeros
    }

    for (int i = 0; i < len; i += 4) {
        char binary[5];
        strncpy(binary, binaryString + i, 4);
        binary[4] = '\0';

        char hexDigit = '0';
        int value = 0;

        for (int j = 0; j < 4; j++) {
            value = value * 2 + (binary[j] - '0');
        }

        if (value >= 10) {
            hexDigit = 'A' + (value - 10);
        } else {
            hexDigit = '0' + value;
        }

        printf("%c", hexDigit);
    }
    printf("\n");
}

// Function to convert a hexadecimal string to binary with up to 64 bits
void hexToBinaryString(const char *hexString) {
    int len = strlen(hexString);
    int startIndex = 0;

    // Skip the "0x" prefix if present
    if (len >= 2 && hexString[0] == '0' && (hexString[1] == 'x' || hexString[1] == 'X')) {
        startIndex = 2;
    }

    printf("Binary: ");
    for (int i = startIndex; i < len; i++) {
        char hexDigit = hexString[i];
        int value;

        if (hexDigit >= '0' && hexDigit <= '9') {
            value = hexDigit - '0';
        } else if (hexDigit >= 'A' && hexDigit <= 'F') {
            value = hexDigit - 'A' + 10;
        } else if (hexDigit >= 'a' && hexDigit <= 'f') {
            value = hexDigit - 'a' + 10;
        } else {
            printf("Invalid hexadecimal digit '%c'\n", hexDigit);
            return;
        }

        for (int j = 3; j >= 0; j--) {
            if (value & (1 << j)) {
                printf("1");
            } else {
                printf("0");
            }
        }
    }
    printf("\n");
}

int main() {
    int choice;
    int numBits = 8; // Change this to the number of bits you want in the binary representation

    while (1) {
        printf("1. Decimal to Binary\n");
        printf("2. Binary to Decimal (Up to 8 bits)\n");
        printf("3. Binary to Hexadecimal\n");
        printf("4. Hexadecimal to Binary\n");
        printf("5. Quit\n");
        printf("Enter your choice (1/2/3/4/5): ");
        scanf("%d", &choice);

        if (choice == 1) {
            int decimalNumber;
            printf("Enter a decimal number between -127 and 127: ");
            scanf("%d", &decimalNumber);
            decimalToBinary(decimalNumber, numBits);
        } else if (choice == 2) {
            char binaryString[9]; // Up to 8 bits
            printf("Enter a binary number (up to 8 bits): ");
            scanf("%8s", binaryString);
            if (strcmp(binaryString, "00000000") == 0) {
                printf("Decimal: 0\n");
            } else {
                int decimalNumber = binaryToDecimal(binaryString, numBits);
                if (decimalNumber != 0) {
                    printf("Decimal: %d\n", decimalNumber);
                }
            }
        } else if (choice == 3) {
            char binaryString[64];
            printf("Enter a binary number (up to 64 bits): ");
            scanf("%s", binaryString);
            binaryToHex(binaryString);
        } else if (choice == 4) {
            char hexString[32];
            printf("Enter a hexadecimal number: ");
            scanf("%s", hexString);
            hexToBinaryString(hexString);
        } else if (choice == 5) {
            printf("Exiting the program.\n");
            break; // Exit the loop and end the program
        } else {
            printf("Invalid choice. Please enter 1, 2, 3, 4, or 5.\n");
        }
    }

    return 0;
}







