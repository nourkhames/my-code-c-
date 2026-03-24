#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <vector>

using namespace std;

struct SubjectStats {
    double totalScore = 0;
    int count = 0;
    int maxScore = -1;
    string topStudents;
};

int main() {
    ifstream myfile("data.csv");
    if (!myfile.is_open()) {
        cerr << "Error: Could not open file!" << endl;
        return 1;
    }

    string line;
    getline(myfile, line); // Skip header

    map<string, SubjectStats> subjects;

    while (getline(myfile, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        string name, subject, tempScore;

        getline(ss, name, ',');
        getline(ss, subject, ',');
        getline(ss, tempScore);

        try {
            double score = stod(tempScore);
            auto& stats = subjects[subject]; // سيسجل المادة تلقائياً إذا لم تكن موجودة

            stats.totalScore += score;
            stats.count++;

            if (score > stats.maxScore) {
                stats.maxScore = score;
                stats.topStudents = name;
            } else if (score == stats.maxScore) {
                stats.topStudents += " And " + name;
            }
        } catch (...) { continue; } // تجاوز الأخطاء في البيانات
    }

    string hardestSubject;
    double minAvg = 1e9;

    for (auto const& [name, stats] : subjects) {
        if (stats.count == 0) continue;

        double avg = stats.totalScore / stats.count;
        cout << name << " Avg: " << avg << " | Top: " << stats.topStudents << " (" << stats.maxScore << ")" << endl;

        if (avg < minAvg) {
            minAvg = avg;
            hardestSubject = name;
        }
    }

    cout << "\n-------------------------------------\n";
    cout << "The Hardest Subject: " << hardestSubject << " with Avg: " << minAvg << endl;

    return 0;
}