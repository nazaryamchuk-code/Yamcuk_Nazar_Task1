#include <iostream>
#include <ctime>
#include <iomanip>

using namespace std;

int** createMatrix(int n) {
    int** matrix = new int* [n];
    for (int i = 0; i < n; ++i) {
        matrix[i] = new int[n];
    }
    return matrix;
}

void deleteMatrix(int** matrix, int n) {
    for (int i = 0; i < n; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

void printMatrix(int** matrix, int n) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << setw(5) << matrix[i][j];
        }
        cout << endl;
    }
}

void processSector3(int** matrix, int n, int k) {
    cout << "\n- - Task 1 (Sector 3\\) - -" << endl;
    int count = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (j >= i && i + j >= n - 1) {
                if (matrix[i][j] < k) {
                    count++;
                }
            }
        }
    }
    cout << "Number of elements in Sector 3\\ smaller than " << k << ": " << count << endl;
}

void processSector9(int** matrix, int n) {
    cout << "\n- - Task 2 (Sector 9) - -" << endl;

    int minDiag = matrix[0][0];
    for (int i = 1; i < n; ++i) {
        if (matrix[i][i] < minDiag) {
            minDiag = matrix[i][i];
        }
    }
    cout << "Min element on main diagonal: " << minDiag << endl;

    int count = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i >= n / 2) {
                count++;
                matrix[i][j] = minDiag;
            }
        }
    }
    cout << "Number of elements in Sector 9 replaced: " << count << endl;
}

int main() {
    srand(static_cast<unsigned int>(time(0)));
    int n, variant, k;

    cout << "Enter matrix size (n): ";
    cin >> n;
    cout << "Enter your variant (V): ";
    cin >> variant;
    cout << "Enter number k to compare: ";
    cin >> k;

    int** matrix = createMatrix(n);

    int minVal = -10 - variant;
    int maxVal = 10 + variant;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            matrix[i][j] = minVal + rand() % (maxVal - minVal + 1);
        }
    }

    cout << "\nInitial Matrix:" << endl;
    printMatrix(matrix, n);

    processSector3(matrix, n, k);
    processSector9(matrix, n);

    cout << "\nMatrix after Sector 9 replacement:" << endl;
    printMatrix(matrix, n);

    deleteMatrix(matrix, n);

    return 0;
}