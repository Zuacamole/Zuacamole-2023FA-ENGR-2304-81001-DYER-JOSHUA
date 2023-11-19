/*

2023FA-ENGR-2304-81001-DYER-JOSHUA-P06

*/


#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    int year;
    int month;
    int day;
    double values[6]; // Considering columns L1 to L6
} DataRow;

// Function prototypes
void displayMenu();
void readDataFromFile(const char *filename, DataRow **data, int *size);
void performAnalysis(DataRow *data, int size);
void findBestAndWorstPlants(DataRow *data, int size);
void findBestSingleProductionDay(DataRow *data, int size);
void searchSinglePlantProduction(DataRow *data, int size);
void searchAllPlantProduction(DataRow *data, int size);
double calculateMean(const double *data, int size);
double calculateStdDev(const double *data, int size, double mean);
double calculateVariance(const double *data, int size, double mean);
double findMode(const double *data, int size);

int main() {
    const char filename[] = "/Users/joshuadyer/Documents/VirtualC/ENGR 2304 - Information Session P07 - Process Data Analysis.csv";

    DataRow *data;
    int size;

    readDataFromFile(filename, &data, &size);

    int choice;
    do {
        displayMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        // Clear the input buffer
        while (getchar() != '\n');

        switch (choice) {
            case 1:
                performAnalysis(data, size);
                break;
            case 2:
                findBestAndWorstPlants(data, size);
                break;
            case 3:
                findBestSingleProductionDay(data, size);
                break;
            case 4:
                searchSinglePlantProduction(data, size);
                break;
            case 5:
                searchAllPlantProduction(data, size);
                break;
            case 0:
                printf("Exiting the program.\n");
                break;
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }
    } while (choice != 0);

    free(data);

    return 0;
}

void displayMenu() {
    printf("\n===== Menu =====\n");
    printf("1. Display Statistical Analysis Report\n");
    printf("2. Find Best and Worst Performing Plants\n");
    printf("3. Find Best Single Production Day for a Single Plant\n");
    printf("4. Search Single Plant Production Data for a Single Date\n");
    printf("5. Search All Plant Production Data for a Single Date\n");
    printf("0. Exit\n");
}

void readDataFromFile(const char *filename, DataRow **data, int *size) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    // Assuming the maximum line length is 1024 characters
    int maxLineLength = 1024;
    char *line = (char *)malloc(maxLineLength * sizeof(char));
    if (line == NULL) {
        perror("Memory allocation error");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    // Read and discard the header
    fgets(line, maxLineLength, file);

    int maxRows = 1000;
    *data = (DataRow *)malloc(maxRows * sizeof(DataRow));
    if (*data == NULL) {
        perror("Memory allocation error");
        free(line);
        fclose(file);
        exit(EXIT_FAILURE);
    }

    *size = 0;
    while (fgets(line, maxLineLength, file) != NULL) {
        if (sscanf(line, "%d,%d,%d,%lf,%lf,%lf,%lf,%lf,%lf",
                   &(*data)[*size].year, &(*data)[*size].month, &(*data)[*size].day,
                   &(*data)[*size].values[0], &(*data)[*size].values[1], &(*data)[*size].values[2],
                   &(*data)[*size].values[3], &(*data)[*size].values[4], &(*data)[*size].values[5]) == 9) {
            (*size)++;

            if (*size == maxRows) {
                maxRows *= 2;
                *data = (DataRow *)realloc(*data, maxRows * sizeof(DataRow));
                if (*data == NULL) {
                    perror("Memory reallocation error");
                    free(line);
                    fclose(file);
                    exit(EXIT_FAILURE);
                }
            }
        } else {
            // Handle invalid line format
            printf("Invalid line format: %s", line);
        }
    }

    free(line);
    fclose(file);
}

void performAnalysis(DataRow *data, int size) {
    printf("\nStatistical Analysis of Plant Daily Unit Production:\n");

    for (int col = 0; col < 6; col++) { // Adjusted to consider columns L1 to L6
        double *columnData = (double *)malloc(size * sizeof(double));
        if (columnData == NULL) {
            perror("Memory allocation error");
            return;
        }

        for (int row = 0; row < size; row++) {
            columnData[row] = data[row].values[col];
        }

        double mean = calculateMean(columnData, size);
        double stdDev = calculateStdDev(columnData, size, mean);
        double variance = calculateVariance(columnData, size, mean);
        double mode = findMode(columnData, size);

        printf("Column L%d:\n", col + 1); // Adjusted to consider columns L1 to L6
        printf("  Mean: %.2lf\n", mean);
        printf("  Standard Deviation: %.2lf\n", stdDev);
        printf("  Variance: %.2lf\n", variance);
        printf("  Mode: %.2lf\n", mode);

        free(columnData);
    }
}

void findBestAndWorstPlants(DataRow *data, int size) {
    double totalProduction[6] = {0.0};
    
    for (int row = 0; row < size; row++) {
        for (int col = 0; col < 6; col++) { // Adjusted to consider columns L1 to L6
            totalProduction[col] += data[row].values[col];
        }
    }

    int bestPlant = 1;
    int worstPlant = 1;
    double bestProduction = totalProduction[0];
    double worstProduction = totalProduction[0];

    for (int col = 1; col < 6; col++) { // Start from index 1
        if (totalProduction[col] > bestProduction) {
            bestProduction = totalProduction[col];
            bestPlant = col + 1; // Adjusted to consider columns L1 to L6
        }

        if (totalProduction[col] < worstProduction) {
            worstProduction = totalProduction[col];
            worstPlant = col + 1; // Adjusted to consider columns L1 to L6
        }
    }

    printf("\nBest Performing Plant: L%d\n", bestPlant);
    printf("Worst Performing Plant: L%d\n", worstPlant);
}

void findBestSingleProductionDay(DataRow *data, int size) {
    double bestSingleProduction = data[0].values[0];
    int bestSingleProductionPlant = 1;
    int bestSingleProductionDay = data[0].day;
    int bestSingleProductionMonth = data[0].month;
    int bestSingleProductionYear = data[0].year;

    for (int row = 0; row < size; row++) {
        for (int col = 0; col < 6; col++) { // Adjusted to consider columns L1 to L6
            if (data[row].values[col] > bestSingleProduction) {
                bestSingleProduction = data[row].values[col];
                bestSingleProductionPlant = col + 1; // Adjusted to consider columns L1 to L6
                bestSingleProductionDay = data[row].day;
                bestSingleProductionMonth = data[row].month;
                bestSingleProductionYear = data[row].year;
            }
        }
    }

    printf("\nBest Single Production Day:\n");
    printf("Plant: L%d\n", bestSingleProductionPlant);
    printf("Production: %.2lf\n", bestSingleProduction);
    printf("Date: %d/%d/%d\n", bestSingleProductionMonth, bestSingleProductionDay, bestSingleProductionYear);
}

double calculateMean(const double *data, int size) {
    double sum = 0.0;
    for (int i = 0; i < size; i++) {
        sum += data[i];
    }
    return sum / size;
}

double calculateStdDev(const double *data, int size, double mean) {
    double sumSquaredDiff = 0.0;
    for (int i = 0; i < size; i++) {
        double diff = data[i] - mean;
        sumSquaredDiff += diff * diff;
    }
    return sqrt(sumSquaredDiff / size);
}

double calculateVariance(const double *data, int size, double mean) {
    double sumSquaredDiff = 0.0;
    for (int i = 0; i < size; i++) {
        double diff = data[i] - mean;
        sumSquaredDiff += diff * diff;
    }
    return sumSquaredDiff / size;
}

double findMode(const double *data, int size) {
    double mode = 0.0;
    int maxCount = 0;

    for (int i = 0; i < size; i++) {
        int count = 0;

        for (int j = 0; j < size; j++) {
            if (data[j] == data[i])
                count++;
        }

        if (count > maxCount) {
            maxCount = count;
            mode = data[i];
        }
    }

    return mode;
}

void searchSinglePlantProduction(DataRow *data, int size) {
    int plant;
    int day;
    int month;
    int year;

    printf("Enter plant number: ");
    scanf("%d", &plant);
    printf("Enter production date (day month year): ");
    scanf("%d %d %d", &day, &month, &year);

    int found = 0;

    for (int i = 0; i < size; i++) {
        if (data[i].day == day && data[i].month == month && data[i].year == year) {
            printf("Plant L%d Production Data for %d/%d/%d:\n", plant, month, day, year);
            printf("Production: %.2lf\n", data[i].values[plant - 1]);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("No data found for the specified date.\n");
    }
}

void searchAllPlantProduction(DataRow *data, int size) {
    int day;
    int month;
    int year;

    printf("Enter production date (day month year): ");
    scanf("%d %d %d", &day, &month, &year);

    int found = 0;

    printf("All Plant Production Data for %d/%d/%d:\n", month, day, year);
    for (int i = 0; i < size; i++) {
        if (data[i].day == day && data[i].month == month && data[i].year == year) {
            printf("Plant L1: %.2lf\n", data[i].values[0]);
            printf("Plant L2: %.2lf\n", data[i].values[1]);
            printf("Plant L3: %.2lf\n", data[i].values[2]);
            printf("Plant L4: %.2lf\n", data[i].values[3]);
            printf("Plant L5: %.2lf\n", data[i].values[4]);
            printf("Plant L6: %.2lf\n", data[i].values[5]);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("No data found for the specified date.\n");
    }
}




























