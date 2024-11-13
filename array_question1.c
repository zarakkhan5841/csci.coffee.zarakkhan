#include <stdio.h>
#include <stdbool.h> 
#include <stdlib.h>   

// Define the size of the main array
#define SIZE 24

// Function prototypes
bool isValid(const int arr[], int length, int pos);
void remove_element(int arr[], int length, int pos);
void insert_element(int arr[], int length, int pos, int value); 
void reshape(const int arr[], int length, int nRows, int nCols, int arr2d[nRows][nCols]); // Reshapes a 1D array into a 2D array
void trans_matrix(int nRows, int nCols, const int mat[nRows][nCols], int mat_transp[nCols][nRows]); 
bool found_duplicate(int arr[], int length); 

int main() {
    // Initialize a 1D array with some values and set the rest to 0
    int arr[SIZE + 1] = {10, 20, 30, 40, 50};

    // Test if certain indices are valid in the array
    printf("Is index 2 valid? %s\n", isValid(arr, SIZE, 2) ? "Yes" : "No");
    printf("Is index 5 valid? %s\n", isValid(arr, SIZE, 5) ? "Yes" : "No");

    // Display array elements before removing an element
    printf("\nBefore removing element at index 2: ");
    for (int i = 0; i < SIZE; i++) {
        printf("%d ", arr[i]);
    }

    // Remove element at index 2 and then insert 10 
    remove_element(arr, SIZE, 2);
    insert_element(arr, SIZE - 1, 1, 10);

    // Display array elements after modifications
    printf("\nAfter removing element at index 2 : ");
    for (int i = 0; i < SIZE; i++) {
        printf("%d ", arr[i]);
    }

    // Test reshaping a 1D array into a 2D array
    printf("\n\nTesting reshape function:\n");
    int arr2d[2][3]; // 2D array with 2 rows and 3 columns
    int arr1d[6] = {1, 2, 3, 4, 5, 6}; // 1D array to be reshaped
    reshape(arr1d, 6, 2, 3, arr2d); // Call reshape function
    printf("2D array after reshape (column by column):\n");
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%d ", arr2d[i][j]);
        }
        printf("\n");
    }

    // Test transposing a matrix
    printf("\nTesting transpose of matrix:\n");
    int mat[2][3] = {{1, 2, 3}, {4, 5, 6}}; // Original matrix
    int mat_transp[3][2]; // Transposed matrix
    trans_matrix(2, 3, mat, mat_transp); // Call transpose function
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 2; j++) {
            printf("%d ", mat_transp[i][j]);
        }
        printf("\n");
    }

    // Test for duplicate elements in arrays
    printf("\nTesting found_duplicate function:\n");
    int arr_with_dup[5] = {1, 2, 3, 2, 4}; // Array with duplicates
    printf("Array has duplicate: %s\n", found_duplicate(arr_with_dup, 5) ? "Yes" : "No");

    int arr_no_dup[5] = {1, 2, 3, 4, 5}; // Array without duplicates
    printf("Array has duplicate: %s\n", found_duplicate(arr_no_dup, 5) ? "Yes" : "No");

    return 0;
}

// Checks if the given position is valid in the array
bool isValid(const int arr[], int length, int pos) {
    return pos >= 0 && pos < length;
}

// Removes an element from the array at the specified position
void remove_element(int arr[], int length, int pos) {
    if (!isValid(arr, length, pos)) {
        printf("Invalid index for removal: %d\n", pos);
        return;
    }
    for (int i = pos; i < length - 1; i++) {
        arr[i] = arr[i + 1];
    }
}

// Inserts an element at the specified position in the array
void insert_element(int arr[], int length, int pos, int value) {
    if (!isValid(arr, length + 1, pos)) {
        printf("Invalid index for insertion: %d\n", pos);
        return;
    }
    for (int i = length; i > pos; i--) {
        arr[i] = arr[i - 1];
    }
    arr[pos] = value;
}

// Reshapes a 1D array into a 2D array
void reshape(const int arr[], int length, int nRows, int nCols, int arr2d[nRows][nCols]) {
    if (length != nRows * nCols) {
        printf("Error: array size does not match nRows * nCols\n");
        return;
    }
    int index = 0;
    for (int col = 0; col < nCols; col++) {
        for (int row = 0; row < nRows; row++) {
            arr2d[row][col] = arr[index++];
        }
    }
}

// Transposes a matrix by swapping rows and columns
void trans_matrix(int nRows, int nCols, const int mat[nRows][nCols], int mat_transp[nCols][nRows]) {
    for (int i = 0; i < nRows; i++) {
        for (int j = 0; j < nCols; j++) {
            mat_transp[j][i] = mat[i][j];
        }
    }
}

// Checks if the array contains any duplicate elements
bool found_duplicate(int arr[], int length) {
    for (int i = 0; i < length; i++) {
        for (int j = i + 1; j < length; j++) {
            if (arr[i] == arr[j]) {
                return true;
            }
        }
    }
    return false;
}
