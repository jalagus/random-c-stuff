#include <stdio.h>

void printSudoku(char sudoku[]) {
    int i, k;
    
    for (i = 0; i < 9; i++) {
        if (i % 3 == 0 && i > 0) {
            printf("\n");
        }
        
        for (k = 0; k < 9; k++) {
            if (k % 3 == 0 && k > 0) {
                printf(" ");
            }       
            
            if (sudoku[(i * 9) + k] > 0) {
                printf(" %d ", sudoku[(i * 9) + k]);
            }
            else {
                printf(" _ ");
            }
        }
        
        printf("\n");
    }
}

int checkRows(char sudoku[]) {
    int i, k;
    int used[10];
    int currentVal = 0;
    
    for (i = 0; i < 9; i++) {
        
        for (k = 0; k < 10; k++) {
            used[k] = 0;
        }
        
        for (k = 0; k < 9; k++) {
            currentVal = sudoku[(i * 9) + k];
            
            if (used[currentVal] > 0 && currentVal != 0) {
                return 0;
            }
            
            used[currentVal]++;
        }
    }
    
    return 1;
}

int checkColumns(char sudoku[]) {
    int i, k;
    int used[10];
    int currentVal = 0;
    
    for (i = 0; i < 9; i++) {
        
        for (k = 0; k < 10; k++) {
            used[k] = 0;
        }
        
        for (k = 0; k < 9; k++) {
            currentVal = sudoku[i + (k * 9)];
            
            if (used[currentVal] > 0 && currentVal != 0) {
                return 0;
            }
            
            used[currentVal]++;
        }
    }
    
    return 1;
}

int checkBox(int pos, char sudoku[]) {
    int used[10] = {0};
    int i = 0;
    int relPos[9] = {0,1,2, 9,10,11, 18,19,20};
    int currentVal = 0;
    
    for (i = 0; i < 9; i++) {
        currentVal = sudoku[pos + relPos[i]];
        
        if (used[currentVal] > 0 && currentVal != 0) {
            return 0;
        }
        used[currentVal]++;
    }
    
    return 1;
}

int checkBoxes(char sudoku[]) {
    int i;
    
    int relPos[9] =  {0,3,6, 27,30,33, 54,57,60};
    
    for (i = 0; i < 9; i++) {
        if (!checkBox(relPos[i], sudoku)) {
            return 0;
        }
    }
    
    return 1;
}


int recurSudoku(char sudoku[], int pos) {
    int k;

    if (sudoku[pos] != 0) {
        if (recurSudoku(sudoku, pos + 1)) {
            return 1;
        }
    }

    if (pos > 81) {
        printSudoku(sudoku);
        return 1;
    }

    for (k = 1; k < 10; k++) {
        if (sudoku[pos] == 0) {
            sudoku[pos] = k;       
            
            if (checkRows(sudoku) && checkColumns(sudoku) && checkBoxes(sudoku)) {
                if (recurSudoku(sudoku, pos + 1)) {
                    return 1;
                }
            }

            sudoku[pos] = 0;
        }
    }
    
    return 0;
}

int main() {
    // World's (mathematically) hardest sudoku!
    char sudoku[9 * 9] = {
        0,0,5, 3,0,0, 0,0,0,
        8,0,0, 0,0,0, 0,2,0,
        0,7,0, 0,1,0, 5,0,0,
        
        4,0,0, 0,0,5, 3,0,0,
        0,1,0, 0,7,0, 0,0,6,
        0,0,3, 2,0,0, 0,8,0,
        
        0,6,0, 5,0,0, 0,0,9,
        0,0,4, 0,0,0, 0,3,0,
        0,0,0, 0,0,9, 7,0,0
    };
    
    printf("Original:\n");
    printSudoku(sudoku);
    
    printf("\n\nSolving...\n");
    
    if (!recurSudoku(sudoku, 0)) {
        printf("No solution!");
    }
    
    return 0;
}
