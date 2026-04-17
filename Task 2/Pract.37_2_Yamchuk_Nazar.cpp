
#include <iostream>
#include <vector>
#include <string>

using namespace std;

double calculateDotProduct(const double v1[], const double v2[], int size);
bool checkOrthogonality(const double v1[], const double v2[], int size);
void printVector(const string& name, const double v[], int size);

int main() {
    const int N = 5; 
    double a[N] = { 1, 0, 3, 2, -1 };
    double b[N] = { 2, 3, 0, 1, 4 };
    double c[N] = { -1, 2, 0, 0, 1 };

    cout << "- - Перевірка векторів на ортогональність - -" << endl;
    printVector("a", a, N);
    printVector("b", b, N);
    printVector("c", c, N);
    cout << "- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -" << endl;

    // Перевірка пар векторів
    struct Pair {
        string name1;
        string name2;
        double* vec1;
        double* vec2;
    };

    Pair pairs[] = {
        {"a", "b", a, b},
        {"a", "c", a, c},
        {"b", "c", b, c}
    };

    for (const auto& p : pairs) {
        double result = calculateDotProduct(p.vec1, p.vec2, N);
        cout << "Скалярний добуток (" << p.name1 << ", " << p.name2 << ") = " << result;

        if (checkOrthogonality(p.vec1, p.vec2, N)) {
            cout << " -> Вектори ОРТОГОНАЛЬНІ" << endl;
        }
        else {
            cout << " -> Вектори НЕ ортогональні" << endl;
        }
    }

    return 0;
}

double calculateDotProduct(const double v1[], const double v2[], int size) {
    double sum = 0;
    for (int i = 0; i < size; i++) {
        sum += v1[i] * v2[i];
    }
    return sum;
}

bool checkOrthogonality(const double v1[], const double v2[], int size) {
    return calculateDotProduct(v1, v2, size) == 0;
}

void printVector(const string& name, const double v[], int size) {
    cout << name << " = (";
    for (int i = 0; i < size; i++) {
        cout << v[i] << (i == size - 1 ? "" : "; ");
    }
    cout << ")" << endl;
}
