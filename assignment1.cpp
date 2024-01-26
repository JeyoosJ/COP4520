#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <mutex>
#include <thread>
#include <chrono>
#include <cmath>
#include <algorithm>

using namespace std;

priority_queue<int> primes;
mutex primesMutex;
int numThreads = 8;
long long sum = 2; // not counting 2 in the findPrimes function

bool isPrime(int n) {
    if (n < 2)
        return false;
    if (n == 2)
        return true;
    if (n % 2 == 0)
        return false;

    for (int i = 3; i * i <= n; i+=2) {
        if (n % i == 0)
            return false;
    }

    return true;
}

void findPrimes(int start) {
    vector<int> tempPrimes;
    for (int i = start; i <= 1e8; i+=(numThreads*2)) {
        if (isPrime(i)) {
            lock_guard<mutex> lock(primesMutex);
            primes.push(i);
            sum += i;
        }
    }
}

int main() {
    vector<thread> threads;

    auto startTime = chrono::high_resolution_clock::now();
    
    for (int i = 0; i < numThreads; i++) {
        // All even numbers are non-prime except for 2. Assigning start values as odd numbers from 1-16
        int start = (i*2)+1;
        threads.emplace_back(findPrimes, start);
    }
    // we skipped over the only even prime number, 2, in the above loop
    primes.push(2);

    for (auto& thread: threads) {
        thread.join();
    }

    auto endTime = chrono::high_resolution_clock::now();
    auto executionTime = chrono::duration_cast<chrono::seconds>(endTime - startTime);
    cout << "Time elapsed: " << executionTime.count() << " seconds" << endl;

    ofstream outputFile("primes.txt");
    if (outputFile.is_open()) {
        outputFile << executionTime.count() << " " << primes.size() << " " << sum << endl;
        vector<int> top10Primes;

        for (int i = 0; i < 10; i++) {
            int prime = primes.top();
            top10Primes.insert(top10Primes.begin()+0, prime);
            primes.pop();
        }

        for (int prime : top10Primes) {
            outputFile << prime << " ";
        }

        outputFile << endl;
        outputFile.close();
    } else {
        cerr << " Unable to open output file" << endl;
        return 1;
    }

    return 0;
}