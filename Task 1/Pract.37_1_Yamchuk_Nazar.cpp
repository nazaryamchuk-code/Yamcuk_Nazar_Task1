#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <iomanip>
#include <random>
#include <future>
#include <string>

using namespace std;
using namespace std::chrono;

void printArray(const vector<int>& arr, int n, const string& label) {
    cout << label << " (перші 20 елементів): ";
    int limit = (n > 20) ? 20 : n;
    for (int i = 0; i < limit; i++) {
        cout << arr[i] << " ";
    }
    if (n > 20) cout << "...";
    cout << endl;
}

void selectionSort(vector<int> arr) { 
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++)
            if (arr[j] < arr[min_idx])
                min_idx = j;
        swap(arr[min_idx], arr[i]);
    }
}

void quickSortInternal(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pivot = arr[high];
        int i = (low - 1);
        for (int j = low; j <= high - 1; j++) {
            if (arr[j] < pivot) {
                i++;
                swap(arr[i], arr[j]);
            }
        }
        swap(arr[i + 1], arr[high]);
        int pi = i + 1;
        quickSortInternal(arr, low, pi - 1);
        quickSortInternal(arr, pi + 1, high);
    }
}

void quickSort(vector<int> arr) {
    if (!arr.empty()) quickSortInternal(arr, 0, arr.size() - 1);
}

void countingSort(vector<int> arr) {
    if (arr.empty()) return;
    auto min_max = minmax_element(arr.begin(), arr.end());
    int min = *min_max.first;
    int max = *min_max.second;
    int range = max - min + 1;
    vector<int> count(range, 0);
    vector<int> output(arr.size());
    for (int x : arr) count[x - min]++;
    for (int i = 1; i < range; i++) count[i] += count[i - 1];
    for (int i = arr.size() - 1; i >= 0; i--) {
        output[count[arr[i] - min] - 1] = arr[i];
        count[arr[i] - min]--;
    }
}

int binarySearch(const vector<int>& arr, int target) {
    int left = 0, right = arr.size() - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == target) return mid;
        if (arr[mid] < target) left = mid + 1;
        else right = mid - 1;
    }
    return -1;
}

int main() {
    vector<int> sizes = { 18, 160, 1024, 4096, 32600, 128000 };

    cout << "- - Аналіз часу сортування (ms) - -" << endl;
    cout << left << setw(10) << "n"
        << setw(15) << "Selection"
        << setw(15) << "Quick"
        << setw(15) << "Counting" << endl;
    cout << string(55, '- -') << endl;

    vector<int> last_sorted_arr; 

    for (int n : sizes) {
        vector<int> base_arr(n);
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(1, 100000);
        for (int i = 0; i < n; i++) base_arr[i] = dis(gen);

        auto start = high_resolution_clock::now();

        auto f_select = async(launch::async, [base_arr]() {
            auto s = high_resolution_clock::now();
            selectionSort(base_arr);
            return duration<double, milli>(high_resolution_clock::now() - s).count();
            });

        auto f_quick = async(launch::async, [base_arr]() {
            auto s = high_resolution_clock::now();
            quickSort(base_arr);
            return duration<double, milli>(high_resolution_clock::now() - s).count();
            });

        auto f_count = async(launch::async, [base_arr]() {
            auto s = high_resolution_clock::now();
            countingSort(base_arr);
            return duration<double, milli>(high_resolution_clock::now() - s).count();
            });

        cout << left << setw(10) << n
            << setw(15) << fixed << setprecision(3) << f_select.get()
            << setw(15) << f_quick.get()
            << setw(15) << f_count.get() << endl;

        if (n == sizes[0]) {
            last_sorted_arr = base_arr;
            sort(last_sorted_arr.begin(), last_sorted_arr.end());
        }
    }

    cout << "\n- - Бінарний пошук - -" << endl;
    printArray(last_sorted_arr, last_sorted_arr.size(), "Відсортований масив (n=18)");

    int target;
    cout << "Введіть елемент для пошуку: ";
    cin >> target;

    int result = binarySearch(last_sorted_arr, target);
    if (result != -1)
        cout << "Елемент знайдено на позиції: " << result << endl;
    else
        cout << "Елемент не знайдено." << endl;

    return 0;
}