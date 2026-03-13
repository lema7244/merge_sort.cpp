#include <iostream>
#include <vector>
#include <chrono>
#include <random>

using namespace std;

// Global counters
long long comparisons = 0;
long long swaps = 0;

// Merge function
void merge(vector<int>& arr, int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<int> L(n1);
    vector<int> R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];

    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0;
    int j = 0;
    int k = left;

    while (i < n1 && j < n2)
    {
        comparisons++;

        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }

        swaps++;
        k++;
    }

    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
        swaps++;
    }

    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
        swaps++;
    }
}

// Merge Sort function
void mergeSort(vector<int>& arr, int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
}

// Function to generate random list
vector<int> generateRandomList(int size)
{
    vector<int> arr(size);

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, size * 10);

    for (int i = 0; i < size; i++)
        arr[i] = dis(gen);

    return arr;
}

// Run experiment for different list sizes
void runExperiment(int size)
{
    comparisons = 0;
    swaps = 0;

    vector<int> arr = generateRandomList(size);

    auto start = chrono::high_resolution_clock::now();

    mergeSort(arr, 0, arr.size() - 1);

    auto end = chrono::high_resolution_clock::now();

    chrono::duration<double> duration = end - start;

    cout << "List Size: " << size << endl;
    cout << "Comparisons: " << comparisons << endl;
    cout << "Swaps/Moves: " << swaps << endl;
    cout << "Time Taken: " << duration.count() << " seconds" << endl;
    cout << "-------------------------------------" << endl;
}

int main()
{
    // Small example demonstration
    vector<int> example = {8, 3, 5, 2, 9};

    cout << "Original List: ";
    for (int x : example)
        cout << x << " ";
    cout << endl;

    mergeSort(example, 0, example.size() - 1);

    cout << "Sorted List: ";
    for (int x : example)
        cout << x << " ";
    cout << endl;

    cout << "Comparisons: " << comparisons << endl;
    cout << "Swaps/Moves: " << swaps << endl;

    cout << "\nRunning Experiments...\n";
    cout << "=============================\n";

    vector<int> sizes = {
        1, 2, 3, 4, 5, 10,
        250, 999, 9999,
        89786,
        789300,
        1780000
    };

    for (int size : sizes)
        runExperiment(size);

    return 0;
}