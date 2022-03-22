#include <iostream>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <chrono>
#include <cmath>
#include <ctime>
#include <algorithm>
#include <map>

using namespace std;


void merge(vector<long long> &a, vector<long long> &b, vector<long long> &v) {
    vector<long long> c;
    long long i = 0, j = 0;
    while (i < a.size() && j < b.size()) {
        if (a[i] < b[j])
            c.push_back(a[i++]);
        else
            c.push_back(b[j++]);
    }
    while (i < a.size())
        c.push_back(a[i++]);
    while (j < b.size())
        c.push_back(b[j++]);
    swap(v, c);
}

void merge_sort(vector<long long> &v) {
    if (v.size() != 1) {
        long long mid = (long long) v.size() / 2;
        vector<long long> b(v.begin() + mid, v.end());
        v.resize(mid);
        merge_sort(v);
        merge_sort(b);
        merge(v, b, v);
    }
}

void insertion_sort(vector<long long> &v) {
    for (long long i = 1; i < v.size(); i++) {
        long long value = v[i];
        long long j = i - 1;
        while (j >= 0 && v[j] > value) {
            v[j + 1] = v[j];
            j--;
        }
        v[j + 1] = value;
    }
}

void shell_sort(vector<long long> &v) {
    for (long long gap = v.size() / 2; gap >= 1; gap /= 2) {
        for (long long i = gap; i < v.size(); i++) {
            long long value = v[i], j = i;
            while (j >= gap && value < v[j - gap]) {
                v[j] = v[j - gap];
                j -= gap;
            }
            v[j] = value;
        }
    }
}

void shell_sort_tokuda(vector<long long> &v) {
    vector<long long> sequence = {44782196, 19903198, 8845866, 3931496, 1747331, 776591, 345152, 153401,
                                  68178, 30301, 13467, 5985, 2660, 1182, 525, 233, 103, 46, 20, 9, 4, 1};
    for (auto gap: sequence) {
        for (long long i = gap; i < v.size(); i++) {
            long long value = v[i], j = i;
            while (j >= gap && value < v[j - gap]) {
                v[j] = v[j - gap];
                j -= gap;
            }
            v[j] = value;
        }
    }
}

void shell_sort_ciura(vector<long long> &v) {
    vector<long long> sequence = {66271020, 29453787, 13090572, 5818032, 2585792, 1149241, 510774, 227011,
                                  100894, 44842, 19930, 8858, 3937, 1750, 701, 301, 132, 57, 23, 10, 4, 1};
    for (auto gap: sequence) {
        for (long long i = gap; i < v.size(); i++) {
            long long value = v[i], j = i;
            while (j >= gap && value < v[j - gap]) {
                v[j] = v[j - gap];
                j -= gap;
            }
            v[j] = value;
        }
    }
}

void radix_sort(vector<long long> &v, int baza) {
    long long value = 1;
    long long max = v[0], i;
    for (auto it: v)
        if (it > max)
            max = it;
    while (max / value) {
        vector<long long> result(v.size());
        vector<long long> count(baza, 0);
        for (auto it: v)
            count[(it / value) % baza]++;
        for (i = 1; i < baza; i++)
            count[i] += count[i - 1];
        for (i = v.size() - 1; i >= 0; i--) {
            long long aux = (v[i] / value) % baza;
            result[count[aux] - 1] = v[i];
            count[aux]--;
        }
        for (i = 0; i < v.size(); i++)
            v[i] = result[i];
        value *= baza;
    }
}

void radix_sort_shift(vector<long long> &v, int putere) {
    long long value = 0;
    long long max = v[0], i;
    long long baza = 1 << putere;   // 2^putere
    for (auto it: v)
        if (it > max)
            max = it;
    while (max >> value) {
        vector<long long> result(v.size());
        vector<long long> count(baza, 0);
        for (auto it: v)
            count[(it >> value) & (baza - 1)]++;
        for (i = 1; i < baza; i++)
            count[i] += count[i - 1];
        for (i = v.size() - 1; i >= 0; i--) {
            long long aux = (v[i] >> value) & (baza - 1);
            result[count[aux] - 1] = v[i];
            count[aux]--;
        }
        for (i = 0; i < v.size(); i++)
            v[i] = result[i];
        value += putere;
    }
}

void counting_sort(vector<long long> &v) {
    map<long long, long long> freq;
    for (auto it: v)
        freq[it]++;
    vector<long long> v_sorted;
    for (auto it: freq)
        while (it.second) {
            v_sorted.push_back(it.first);
            it.second--;
        }
    swap(v_sorted, v);
}

void check_sort(vector<long long> &v) {
    bool sortat = true;
    for (int i = 0; i < v.size() - 1; i++)
        if (v[i] > v[i + 1]) {
            sortat = false;
            break;
        }
    if (sortat)
        cout << "Sortat cu succes";
    else
        cout << "Nesortat";
}

int main() {
    ifstream fin("D:\\SD_Sortari\\input.in");
    //ofstream fout("D:\\SD_Sortari\\output.txt");
    long long T, N, Max;
    fin >> T;   //numarul de teste
    for (long long i = 0; i < T; i++) {
        srand(unsigned(time(nullptr)));
        fin >> N >> Max;
        vector<long long> v(N);
        generate(v.begin(), v.end(), rand);
        for (auto &it: v)
            it = (long long) (pow(it, 2)) % Max;
        cout << "N=" << N;
        cout << "\nMax=" << Max << "\n";
        vector<long long> a = v;

        auto begin = chrono::high_resolution_clock::now();
        sort(a.begin(), a.end());
        auto end = chrono::high_resolution_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
        cout << "C++ sort: " << double(double(elapsed.count()) / 1000000) << "s ";
        check_sort(a);
        cout << "\n";

        a = v;
        begin = chrono::high_resolution_clock::now();
        merge_sort(a);
        end = chrono::high_resolution_clock::now();
        elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
        cout << "Merge sort: " << double(double(elapsed.count()) / 1000000) << "s ";
        check_sort(a);
        cout << "\n";

        a = v;
        begin = chrono::high_resolution_clock::now();
        radix_sort(a, 10);
        end = chrono::high_resolution_clock::now();
        elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
        cout << "Radix sort baza 10: " << double(double(elapsed.count()) / 1000000) << "s ";
        check_sort(a);
        cout << "\n";

        a = v;
        begin = chrono::high_resolution_clock::now();
        radix_sort(a, 16);
        end = chrono::high_resolution_clock::now();
        elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
        cout << "Radix sort baza 16: " << double(double(elapsed.count()) / 1000000) << "s ";
        check_sort(a);
        cout << "\n";

        a = v;
        begin = chrono::high_resolution_clock::now();
        radix_sort(a, 8);
        end = chrono::high_resolution_clock::now();
        elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
        cout << "Radix sort baza 8: " << double(double(elapsed.count()) / 1000000) << "s ";
        check_sort(a);
        cout << "\n";

        a = v;
        begin = chrono::high_resolution_clock::now();
        radix_sort(a, 65536);
        end = chrono::high_resolution_clock::now();
        elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
        cout << "Radix sort baza 2^16: " << double(double(elapsed.count()) / 1000000) << "s ";
        check_sort(a);
        cout << "\n";

        a = v;
        begin = chrono::high_resolution_clock::now();
        radix_sort_shift(a, 16);
        end = chrono::high_resolution_clock::now();
        elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
        cout << "Radix sort baza 2^16 shift: " << double(double(elapsed.count()) / 1000000) << "s ";
        check_sort(a);
        cout << "\n";

        a = v;
        begin = chrono::high_resolution_clock::now();
        shell_sort(a);
        end = chrono::high_resolution_clock::now();
        elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
        cout << "Shell sort: " << double(double(elapsed.count()) / 1000000) << "s ";
        check_sort(a);
        cout << "\n";


        a = v;
        begin = chrono::high_resolution_clock::now();
        shell_sort_tokuda(a);
        end = chrono::high_resolution_clock::now();
        elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
        cout << "Shell sort tokuda: " << double(double(elapsed.count()) / 1000000) << "s ";
        check_sort(a);
        cout << "\n";

        a = v;
        begin = chrono::high_resolution_clock::now();
        shell_sort_ciura(a);
        end = chrono::high_resolution_clock::now();
        elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
        cout << "Shell sort ciura: " << double(double(elapsed.count()) / 1000000) << "s ";
        check_sort(a);
        cout << "\n";

        a = v;
        begin = chrono::high_resolution_clock::now();
        counting_sort(a);
        end = chrono::high_resolution_clock::now();
        elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
        cout << "Counting sort: " << double(double(elapsed.count()) / 1000000) << "s ";
        check_sort(a);
        cout << "\n";

//        a = v;
//        begin = chrono::high_resolution_clock::now();
//        insertion_sort(a);
//        end = chrono::high_resolution_clock::now();
//        elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
//        cout << "Insertion sort: " << double(double(elapsed.count()) / 1000000) << "s ";
//        check_sort(a);
//        cout << "\n";
    }
    return 0;
}