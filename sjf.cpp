#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
using namespace std;

struct Process {
    int id;
    int burstTime;
    int waitingTime;
    int turnaroundTime;
};

int main() {
    int processCount;
    cout << "=== SJF (Shortest Job First) Scheduling ===\n";
    cout << "Enter the number of processes: ";
    cin >> processCount;

    vector<Process> processes(processCount);

    // Step 1: Taking Input burst times
    cout << "\nEnter the Burst Time (BT) for each process:\n";
    for (int i = 0; i < processCount; i++) {
        processes[i].id = i + 1;
        cout << "Process " << i + 1 << " Burst Time: ";
        cin >> processes[i].burstTime;
    }

    // Step 2: Sorting processes by burst time (SJF)
    sort(processes.begin(), processes.end(), [](Process a, Process b) {
        return a.burstTime < b.burstTime;
    });

    // Step 3: Calculating waiting times
    processes[0].waitingTime = 0;
    for (int i = 1; i < processCount; i++) {
        processes[i].waitingTime = processes[i - 1].waitingTime + processes[i - 1].burstTime;
    }

    // Step 4: Calculating turnaround times
    for (int i = 0; i < processCount; i++) {
        processes[i].turnaroundTime = processes[i].waitingTime + processes[i].burstTime;
    }

    // Step 5: Displaying the process table
    cout << "\nProcess\tBurst Time\tWaiting Time\tTurnaround Time\n";
    cout << "------------------------------------------------------\n";
    for (int i = 0; i < processCount; i++) {
        cout << "P" << processes[i].id << "\t" 
             << processes[i].burstTime << "\t\t" 
             << processes[i].waitingTime << "\t\t" 
             << processes[i].turnaroundTime << "\n";
    }

    // Step 6: Calculating average WT and TAT
    double totalWT = 0, totalTAT = 0;
    for (int i = 0; i < processCount; i++) {
        totalWT += processes[i].waitingTime;
        totalTAT += processes[i].turnaroundTime;
    }
    cout << fixed << setprecision(2);
    cout << "\nAverage Waiting Time: " << (totalWT / processCount);
    cout << "\nAverage Turnaround Time: " << (totalTAT / processCount) << "\n";

    // Step 7: Displaying Gantt Chart
    cout << "\nGantt Chart:\n";
    cout << "------------------------------------------------\n";
    cout << "|";
    for (int i = 0; i < processCount; i++) {
        cout << "  P" << processes[i].id << "  |";
    }
    cout << "\n------------------------------------------------\n";

    cout << "0";
    for (int i = 0; i < processCount; i++) {
        cout << setw(6) << processes[i].waitingTime + processes[i].burstTime;
    }
    cout << "\n";

    cout << "\n=== SJF Scheduling Completed ===\n";

    return 0;
}
