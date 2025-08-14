#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

int main() {
    int processCount;

    cout << "=== FCFS (First Come First Serve) Scheduling ===\n";
    cout << "Enter the number of processes: ";
    cin >> processCount;

    vector<int> burstTime(processCount), waitingTime(processCount), turnaroundTime(processCount);

    // Step 1: Input burst times
    cout << "\nEnter the Burst Time (BT) for each process:\n";
    for (int i = 0; i < processCount; i++) {
        cout << "Process " << i + 1 << " Burst Time: ";
        cin >> burstTime[i];
    }

    // Step 2: Calculate waiting times
    waitingTime[0] = 0;
    for (int i = 1; i < processCount; i++) {
        waitingTime[i] = waitingTime[i - 1] + burstTime[i - 1];
    }

    // Step 3: Calculate turnaround times
    for (int i = 0; i < processCount; i++) {
        turnaroundTime[i] = waitingTime[i] + burstTime[i];
    }

    // Step 4: Display the process table
    cout << "\nProcess\tBurst Time\tWaiting Time\tTurnaround Time\n";
    cout << "------------------------------------------------------\n";
    for (int i = 0; i < processCount; i++) {
        cout << i + 1 << "\t" 
             << burstTime[i] << "\t\t" 
             << waitingTime[i] << "\t\t" 
             << turnaroundTime[i] << "\n";
    }

    // Step 5: Calculate average WT and TAT
    double totalWT = 0, totalTAT = 0;
    for (int i = 0; i < processCount; i++) {
        totalWT += waitingTime[i];
        totalTAT += turnaroundTime[i];
    }
    cout << fixed << setprecision(2);
    cout << "\nAverage Waiting Time: " << (totalWT / processCount);
    cout << "\nAverage Turnaround Time: " << (totalTAT / processCount) << "\n";

    // Step 6: Display Gantt Chart
    cout << "\nGantt Chart:\n";
    cout << "------------------------------------------------\n";
    cout << "|";
    for (int i = 0; i < processCount; i++) {
        cout << "  P" << i + 1 << "  |";
    }
    cout << "\n------------------------------------------------\n";

    cout << "0";
    for (int i = 0; i < processCount; i++) {
        cout << setw(6) << waitingTime[i] + burstTime[i];
    }
    cout << "\n";

    cout << "\n=== FCFS Scheduling Completed ===\n";

    return 0;
}
