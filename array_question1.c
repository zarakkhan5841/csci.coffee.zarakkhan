
#include <stdio.h>
#include <stdbool.h> 
#include <stdlib.h>   

// Defining the main arrays size
#define SIZE 24

// Function prototypes
bool isValid(const int arr[], int length, int pos);
void remove_element(int arr[], int length, int pos);
void insert_element(int arr[], int length, int pos, int value); 
void reshape(const int arr[], int length, int nRows, int nCols, int arr2d[nRows][nCols]); // Reshapes a 1D array into a 2D array
void trans_matrix(int nRows, int nCols, const int mat[nRows][nCols], int mat_transp[nCols][nRows]); 
bool found_duplicate(int arr[], int length); 

int main() {
    // putting some values to the first 1d array 
    int arr[SIZE + 1] = {10, 20, 30, 40, 50};

    // Testing if some index are valid or invalid 
    printf("is the index 3 valid? %s\n", isValid(arr, SIZE, 3) ? "Yes" : "No");
    printf("is the  index 4 valid? %s\n", isValid(arr, SIZE, 4) ? "Yes" : "No");

    // Displaying the original array before removing the index 2 
    printf("\nbefore we remove the the index 2 , the array is : ");
    for (int i = 0; i < SIZE; i++) {
        printf("%d ", arr[i]);
    }

    // removing the element at 2nd index 
    remove_element(arr, SIZE, 2);
    insert_element(arr, SIZE - 1, 1, 10);

    // Displaying the array after the value is removed 
    printf("\nAfter we remove element  : ");
    for (int i = 0; i < SIZE; i++) {
        printf("%d ", arr[i]);
    }

    //  reshaping the  1d  array to  2d
    printf("\n\n reshaping function:\n");
    int arr2d[2][3]; // 2d array containing 2R and 3C
    int arr1d[6] = {1, 2, 3, 4, 5, 6}; // original array that is to be reshaped 
    reshape(arr1d, 6, 2, 3, arr2d); // Calling the  reshape function
    printf("2D array after we  reshape it :\n");
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%d ", arr2d[i][j]);
        }
        printf("\n");
    }

    // transpose  matrix
    printf("\n transpose of matrix:\n");
    int mat[2][3] = {{1, 2, 3}, {4, 5, 6}}; // initial matrix 
    int mat_transp[3][2]; // matrix after getting transposed 
    trans_matrix(2, 3, mat, mat_transp); // Calling the function 
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 2; j++) {
            printf("%d ", mat_transp[i][j]);
        }
        printf("\n");
    }

    // testing if there is a duplicate in the array 
    printf("\n the duplicate function:\n");
    int array_containing_duplicate[5] = {1, 2, 3, 2, 4}; // an array that contains duplicates 
    printf("Array has duplicate: %s\n", found_duplicate(array_containing_duplicate, 5) ? "Yes" : "No");

    int array_without_duplicate[5] = {1, 2, 3, 4, 5}; // an array without any duplicates 
    printf("Array has duplicate: %s\n", found_duplicate(array_without_duplicate, 5) ? "Yes" : "No");

    return 0;
}

// Checking if the element position is valid 
bool isValid(const int arr[], int length, int pos) {
    return pos >= 0 && pos < length;
}

// this function removes the element from a specific index 
void remove_element(int arr[], int length, int pos) {
    if (!isValid(arr, length, pos)) {
        printf(" index not valid for  removal: %d\n", pos);
        return;
    }
    for (int i = pos; i < length - 1; i++) {
        arr[i] = arr[i + 1];
    }
}

// this function inserts an element 
void insert_element(int arr[], int length, int pos, int value) {
    if (!isValid(arr, length + 1, pos)) {
        printf(" index not valid for insertion: %d\n", pos);
        return;
    }
    for (int i = length; i > pos; i--) {
        arr[i] = arr[i - 1];
    }
    arr[pos] = value;
}

// this function makes 1d array into a 2d array 
void reshape(const int arr[], int length, int nRows, int nCols, int arr2d[nRows][nCols]) {
    if (length != nRows * nCols) {
        printf("Error: array is invalid \n");
        return;
    }
    int index = 0;
    for (int col = 0; col < nCols; col++) {
        for (int row = 0; row < nRows; row++) {
            arr2d[row][col] = arr[index++];
        }
    }
}

// this function prints the transpose 
void trans_matrix(int nRows, int nCols, const int mat[nRows][nCols], int mat_transp[nCols][nRows]) {
    for (int i = 0; i < nRows; i++) {
        for (int j = 0; j < nCols; j++) {
            mat_transp[j][i] = mat[i][j];
        }
    }
}

// this function looks for any duplicatee value 
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
