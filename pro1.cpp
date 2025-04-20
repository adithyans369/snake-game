#include <iostream>
#include <chrono>
#include <thread>
#include <cstdlib>
#include <ctime>

using namespace std;
using namespace std::chrono;

int main() {
    cout << "=== Reaction Time Tester ===" << endl;
    cout << "Press Enter to start the test..." << endl;
    cin.ignore();

    // Random delay between 2 and 5 seconds
    srand(time(0));
    int delay = 2000 + rand() % 3000;
    cout << "Get ready..." << endl;

    // Wait for the random delay
    this_thread::sleep_for(chrono::milliseconds(delay));

    cout << "GO! Press Enter now!" << endl;

    // Start time
    auto start = high_resolution_clock::now();

    cin.ignore(); // Wait for Enter

    // End time
    auto end = high_resolution_clock::now();

    auto duration = duration_cast<milliseconds>(end - start);
    cout << "Your reaction time: " << duration.count() << " ms" << endl;

    return 0;
}
cd ~/Desktop/projects
git init
git add .
git commit -m "Initial commit - Reaction Time Tester in C++"
git branch -M main
git remote add origin https://github.com/your-username/reaction-time-tester.git
git push -u origin main
