/*
2023FA-ENGR-2304-81001-DYER-JOSHUA-P03
*/
#include <stdio.h>
#include <math.h> 

// Function to calculate the determinant of a 2x2 matrix
double determinant(double a, double b, double c, double d) {
    return (a * d - b * c);
}

// Function to calculate the determinant of a 3x3 matrix
double determinant3x3(double a, double b, double c, double d, double e, double f, double g, double h, double i) {
    return (a * e * i + b * f * g + c * d * h - c * e * g - b * d * i - a * f * h);
}

int main(void) { 
    int choice;
    do {
        printf("Choose an option:\n");
        printf("1. Solve a system of two equations (2 variables)\n");
        printf("2. Solve a system of three equations (3 variables)\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                double a1, b1, c1, a2, b2, c2;

                // Input coefficients of the linear equations
                printf("Enter the coefficients of the first equation (a1 b1 c1): ");
                scanf("%lf %lf %lf", &a1, &b1, &c1);

                printf("Enter the coefficients of the second equation (a2 b2 c2): ");
                scanf("%lf %lf %lf", &a2, &b2, &c2);

                // Calculate the determinants
                double determinant_main = determinant(a1, b1, a2, b2);
                double determinant_x = determinant(c1, b1, c2, b2);
                double determinant_y = determinant(a1, c1, a2, c2);

                // Define a tolerance for comparing floating-point numbers
                double tolerance = 1e-10;

                // Check if the system has a unique solution (non-zero determinant_main)
                if (fabs(determinant_main) > tolerance) {
                    // Calculate the values of x and y using Cramer's Rule
                    double x = determinant_x / determinant_main;
                    double y = determinant_y / determinant_main;

                    // Output the solution
                    printf("Solution: x = %.2f, y = %.2f\n", x, y);
                } else {
                    // If determinant_main is zero, the system may have no solution or infinite solutions
                    if (fabs(determinant_x) <= tolerance && fabs(determinant_y) <= tolerance) {
                        printf("Infinite solutions\n");
                    } else {
                        printf("No solution\n");
                    }
                }
                break;
            }
            case 2: {
                double a1, b1, c1, d1, a2, b2, c2, d2, a3, b3, c3, d3;

                // Input coefficients of the linear equations
                printf("Enter the coefficients of the first equation (a1 b1 c1 d1): ");
                scanf("%lf %lf %lf %lf", &a1, &b1, &c1, &d1);

                printf("Enter the coefficients of the second equation (a2 b2 c2 d2): ");
                scanf("%lf %lf %lf %lf", &a2, &b2, &c2, &d2);

                printf("Enter the coefficients of the third equation (a3 b3 c3 d3): ");
                scanf("%lf %lf %lf %lf", &a3, &b3, &c3, &d3);

                // Calculate the determinants
                double determinant_main = determinant3x3(a1, b1, c1, a2, b2, c2, a3, b3, c3);
                double determinant_x = determinant3x3(d1, b1, c1, d2, b2, c2, d3, b3, c3);
                double determinant_y = determinant3x3(a1, d1, c1, a2, d2, c2, a3, d3, c3);
                double determinant_z = determinant3x3(a1, b1, d1, a2, b2, d2, a3, b3, d3);

                // Define a tolerance for comparing floating-point numbers
                double tolerance = 1e-10;

                // Check if the system has a unique solution (non-zero determinant_main)
                if (fabs(determinant_main) > tolerance) {
                    // Calculate the values of x, y, and z using Cramer's Rule
                    double x = determinant_x / determinant_main;
                    double y = determinant_y / determinant_main;
                    double z = determinant_z / determinant_main;

                    // Output the solution
                    printf("Solution: x = %.2f, y = %.2f, z = %.2f\n", x, y, z);
                } else {
                    // If determinant_main is zero, the system may have no solution or infinite solutions
                    if (fabs(determinant_x) <= tolerance && fabs(determinant_y) <= tolerance && fabs(determinant_z) <= tolerance) {
                        printf("Infinite solutions\n");
                    } else {
                        printf("No solution\n");
                    }
                }
                break;
            }
            case 3:
                printf("Exiting the program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 3);

    return 0;
}
