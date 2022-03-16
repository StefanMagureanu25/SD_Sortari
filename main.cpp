#include <iostream>
#include <vector>
#include <chrono>
#include <cmath>
#include <algorithm>

using namespace std;


void merge(vector<long long> &v, int left, int mid, int right) {
    vector<long long> temp;
    int j = left, i = mid + 1;
    while (j <= mid && i <= right) {
        if (v[j] <= v[i])
            temp.push_back(v[j++]);
        else
            temp.push_back(v[i++]);
    }
    while (j <= mid)
        temp.push_back(v[j++]);
    while (i <= right)
        temp.push_back(v[i++]);
    for (int i = left; i <= right; i++)
        v[i] = temp[i - left];
}

void merge_sort(vector<long long> &v, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        merge_sort(v, left, mid);
        merge_sort(v, mid + 1, right);
        merge(v, left, mid, right);
    }
}

void insertion_sort(vector<long long> &v) {
    for (int i = 1; i < v.size(); i++) {
        long long value = v[i];
        int j = i - 1;
        while (j >= 0 && v[j] > value) {
            swap(v[j], v[j + 1]);
            j--;
        }
    }
}

void shell_sort(vector<long long> &v) {
    for (long long gap = v.size() / 2; gap >= 1; gap /= 2) {
        for (long long i = gap; i < v.size(); i++) {
            long long value = v[i], j = i;
            while (j >= gap && value < v[j - gap]) {
                swap(v[j], v[j - gap]);
                j -= gap;
            }
        }
    }
}

void shell_sort_tokuda(vector<long long> &v, long long max) {
    vector<long long> sequence = {1};
    while (sequence.back() <= floor(max / ceil((9 * (pow(2.25, sequence.size())) - 4) / 5)))
        sequence.push_back(ceil((9 * (pow(2.25, sequence.size())) - 4) / 5));
    reverse(sequence.begin(), sequence.end());
    for (auto gap: sequence) {
        for (long long i = gap; i < v.size(); i++) {
            long long value = v[i], j = i;
            while (j >= gap && value < v[j - gap]) {
                swap(v[j], v[j - gap]);
                j -= gap;
            }
        }
    }
}

void shell_sort_ciura(vector<long long> &v, long long max) {
    vector<long long> sequence = {1, 4, 10, 23, 57, 132, 301, 701, 1750};
    while (sequence.back() <= floor(max / 2.25))
        sequence.push_back(floor(sequence.back() * 2.25));
    reverse(sequence.begin(), sequence.end());
    for (auto gap: sequence) {
        for (long long i = gap; i < v.size(); i++) {
            long long value = v[i], j = i;
            while (j >= gap && value < v[j - gap]) {
                swap(v[j], v[j - gap]);
                j -= gap;
            }
        }
    }
}


bool check_sort(vector<long long> &v) {
    for (int i = 0; i < v.size() - 1; i++)
        if (v[i] > v[i + 1])
            return false;
    return true;
}

void print_vector(vector<long long> &v) {
    for (auto it: v)
        cout << it << " ";
    cout << "\n";
}

int main() {
    vector<long long> v;
    int n;
    long long x;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> x;
        v.push_back(x);
    }

}