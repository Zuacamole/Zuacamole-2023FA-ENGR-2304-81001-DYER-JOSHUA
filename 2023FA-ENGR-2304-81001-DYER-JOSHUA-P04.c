/*

2023FA-ENGR-2304-81001-DYER-JOSHUA-P04
modified for github sample

*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int main() {
    // Initialize the random number generator with the current time
    srand(time(NULL));

    int option;

    do {
        // Generate random values for Vs, R1, R2, and R3
        double Vs = (rand() % 1000) / 100.0; // Random Vs value between 0 and 9.99
        double R1 = (rand() % 2000) / 100.0; // Random R1 value between 0 and 19.99
        double R2 = (rand() % 2000) / 100.0; // Random R2 value between 0 and 19.99
        double R3 = (rand() % 2000) / 100.0; // Random R3 value between 0 and 19.99

        // Calculate the total resistance (Rtotal) in the circuit
        double Rtotal = R1 + ((R2 * R3) / (R2 + R3));

        // Calculate I1 using Ohm's law
        double I1 = Vs / Rtotal;

        // Calculate V1 using Ohm's law
        double V1 = I1 * R1;

        // Calculate V2 (which is also equal to V3)
        double V2 = Vs - V1;

        // Calculate I2 using Ohm's law
        double I2 = V2 / R2;

        // Calculate I3 using Ohm's law
        double I3 = V2 / R3;

        // Truncate the calculated values to two decimal places
        I1 = floor(I1 * 100) / 100;
        V2 = floor(V2 * 100) / 100;
        I2 = floor(I2 * 100) / 100;
        I3 = floor(I3 * 100) / 100;

        // Present the random values to the user and query for answers
        printf("Random Values:\n");
        printf("Vs: %.2lf\n", Vs);
        printf("R1: %.2lf\n", R1);
        printf("R2: %.2lf\n", R2);
        printf("R3: %.2lf\n", R3);

        double user_I1, user_V3, user_I2, user_I3;

        printf("Enter your answers for I1, V3 (or V2), I2, and I3 (space-separated): ");
        scanf("%lf %lf %lf %lf", &user_I1, &user_V3, &user_I2, &user_I3);

        // Compare the user input values to the calculated ones
        int success = 1;

        if (fabs(I1 - user_I1) >= 1e-3) {
            printf("Failure. Your answer for I1 is incorrect.\n");
            success = 0;
        }
        if (fabs(V2 - user_V3) >= 1e-3) {
            printf("Failure. Your answer for V3 (or V2) is incorrect.\n");
            success = 0;
        }
        if (fabs(I2 - user_I2) >= 1e-3) {
            printf("Failure. Your answer for I2 is incorrect.\n");
            success = 0;
        }
        if (fabs(I3 - user_I3) >= 1e-3) {
            printf("Failure. Your answer for I3 is incorrect.\n");
            success = 0;
        }

        if (success) {
            printf("Success! Your answers are correct.\n");
        } else {
            // Provide correct answers to the user
            printf("Correct Answers:\n");
            printf("I1: %.2lf\n", I1);
            printf("V3 (or V2): %.2lf\n", V2);
            printf("I2: %.2lf\n", I2);
            printf("I3: %.2lf\n", I3);
        }

        // Ask the user if they want to restart or exit
        printf("Do you want to restart (1) or exit (2)? ");
        scanf("%d", &option);
    } while (option == 1);

    return 0;
}


