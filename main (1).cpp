#include <fstream>
#include <iostream>
#include <stack>

using namespace std;

class Money{
protected:
    int value;

public:
    Money(int value) {
        this->value = value;
    }
    virtual void print() = 0;
};

class Bill : public Money{
private:
    string denomination;

public:
    Bill(int value, string denomination) : Money(value) {
        this->denomination = denomination;
    }
    void print() {
        cout << denomination << ": $" << value << endl;
    }
};

int main() {
    stack<Bill> bills;

    ifstream inputFile("bills.txt");
    if (!inputFile.is_open()) {
        cout << "Error opening input file!" << endl;
        return 1;
    }

    int value;
    string denomination;
    while (inputFile >> value >> denomination) {
        Bill b(value, denomination);
        bills.push(b);
    }

    inputFile.close();

    ofstream outputFile("sorted_bills.txt");
    if (!outputFile.is_open()) {
        cout << "Error opening output file!" << endl;
        return 1;
    }

    stack<Bill> sortedBills;
    while (!bills.empty()) {
        Bill b = bills.top();
        bills.pop();

        while (!sortedBills.empty() && sortedBills.top().value > b.value) {
            bills.push(sortedBills.top());
            sortedBills.pop();
        }

        sortedBills.push(b);
    }

    while (!sortedBills.empty()) {
        Bill b = sortedBills.top();
        sortedBills.pop();
        outputFile << b.value << " " << b.denomination << endl;
    }

    outputFile.close();

    cout << "Sorted bills:" << endl;
    ifstream sortedFile("sorted_bills.txt");
    int total = 0;
    while (sortedFile >> value >> denomination) {
        Bill b(value, denomination);
        b.print();
        total += value;
    }

    cout << "Total: $" << total << endl;

    return 0;
}