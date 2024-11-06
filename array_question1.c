#include <stdio.h>
#include <stdbool.h> 
#include <stdlib.h>   

#define SIZE 5


bool isValid(const int arr[], int length, int pos);
void remove_element(int arr[], int length, int pos);
void insert_element(int arr[], int length, int pos, int value);
void reshape(const int arr[], int length, int nRows, int nCols, int arr2d[nRows][nCols]);
void trans_matrix(int nRows, int nCols, const int mat[nRows][nCols], int mat_transp[nCols][nRows]);
bool found_duplicate(int arr[], int length);

int main() {
    
    int arr[SIZE] = {10, 20, 30, 40, 50};
    
  
    printf("Is index 2 valid? %s\n", isValid(arr, SIZE, 2) ? "Yes" : "No");
    printf("Is index 5 valid? %s\n", isValid(arr, SIZE, 5) ? "Yes" : "No");

   
    printf("\nBefore removing element at index 2: ");
    for (int i = 0; i < SIZE; i++) {
        printf("%d ", arr[i]);
    }
    remove_element(arr, SIZE, 2);
    printf("\nAfter removing element at index 2: ");
    for (int i = 0; i < SIZE - 1; i++) {
        printf("%d ", arr[i]);
    }

    
    printf("\n\nBefore inserting 80 at index 2: ");
    for (int i = 0; i < SIZE - 1; i++) {
        printf("%d ", arr[i]);
    }
    insert_element(arr, SIZE - 1, 2, 80);
    printf("\nAfter inserting 80 at index 2: ");
    for (int i = 0; i < SIZE; i++) {
        printf("%d ", arr[i]);
    }

    
    printf("\n\nTesting reshape function:\n");
    int arr2d[2][3];  
    int arr1d[6] = {1, 2, 3, 4, 5, 6};
    reshape(arr1d, 6, 2, 3, arr2d);
    printf("2D array after reshape (column by column):\n");
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%d ", arr2d[i][j]);
        }
        printf("\n");
    }

    
    printf("\nTesting transpose of matrix:\n");
    int mat[2][3] = {{1, 2, 3}, {4, 5, 6}};
    int mat_transp[3][2];
    trans_matrix(2, 3, mat, mat_transp);
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 2; j++) {
            printf("%d ", mat_transp[i][j]);
        }
        printf("\n");
    }

    
    printf("\nTesting found_duplicate function:\n");
    int arr_with_dup[5] = {1, 2, 3, 2, 4};
    printf("Array has duplicate: %s\n", found_duplicate(arr_with_dup, 5) ? "Yes" : "No");

    int arr_no_dup[5] = {1, 2, 3, 4, 5};
    printf("Array has duplicate: %s\n", found_duplicate(arr_no_dup, 5) ? "Yes" : "No");

    return 0;
}



bool isValid(const int arr[], int length, int pos) {
    return pos >= 0 && pos < length;
}

void remove_element(int arr[], int length, int pos) {
    if (!isValid(arr, length, pos)) {
        printf("Invalid index for removal: %d\n", pos);
        return;
    }

    
    for (int i = pos; i < length - 1; i++) {
        arr[i] = arr[i + 1];
    }
}

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

void trans_matrix(int nRows, int nCols, const int mat[nRows][nCols], int mat_transp[nCols][nRows]) {
    for (int i = 0; i < nRows; i++) {
        for (int j = 0; j < nCols; j++) {
            mat_transp[j][i] = mat[i][j];
        }
    }
}

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
