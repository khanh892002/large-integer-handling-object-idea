#include "../largeInt.h"
#include <iostream>
#include <chrono>
#include <string>
#include <vector>
using namespace std;

// Function to measure execution time
template<typename Func>
double measureTime(Func func) {
    auto start = chrono::high_resolution_clock::now();
    func();
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> duration = end - start;
    return duration.count();
}

int main() {
    cout << "Large Integer Multiplication Efficiency Test\n"
        << "============================================\n\n";
    
    // Test with different sized numbers
    vector<pair<string, string>> testCases = {
        {"123", "456"},                    // Small numbers (3 digits each)
        {"12345", "67890"},                // Medium numbers (5 digits each)
        {"123456789", "987654321"},        // Larger numbers (9 digits each)
        {"123456789012345", "987654321098765"} // Very large numbers (15 digits each)
    };

    largeInt a, b;

    for (const auto& testCase : testCases) {
        a.setNumWithStrNum(testCase.first);
        b.setNumWithStrNum(testCase.second);
        
        cout << "Testing: " << testCase.first << " * " << testCase.second << "\n"
               << "Number of digits: " << testCase.first.length() << " and " << testCase.second.length() << "\n";
        
        // Measure Karatsuba multiplication time
        largeInt result;
        double time = measureTime([&]() {result = a * b;});
        
        cout << "Karatsuba multiplication time: " << time << " ms\n"
            << "Result: ";
        
        // Display result (simplified - just show first few digits)
        cout << "[" << result.getNum()->size() << " bytes]\n"
            << "----------------------------------------\n\n";
    }
    // Demonstrate the crossover point
    cout << "Crossover Point Analysis:\n"
        << "========================\n";
    
    // Test with progressively larger numbers
    for (int digits = 1; digits <= 20; digits += 2) {
        string num1(digits, '9');
        string num2(digits, '9');
        
        largeInt a = createLargeNumber(num1);
        largeInt b = createLargeNumber(num2);
        
        double time = measureTime([&]() {largeInt result = a * b;});
        
        cout << digits << " digits each: " << time << " ms\n";
        
        if (time > 100) break; // Stop if it takes too long
    }
    return 0;
}