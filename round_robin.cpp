#include <iostream>
#include <vector>
#include <iomanip>
#include <queue>
using namespace std;

struct Process {
    int id;
    int burstTime;
    int remainingTime;
    int waitingTime;
    int turnaroundTime;
};

int main() {
    int processCount, timeQuantum;
    cout << "=== Round Robin (RR) Scheduling ===\n";
    cout << "Enter the number of processes: ";
    cin >> processCount;

    vector<Process> processes(processCount);

    // Step 1: Taking input
    cout << "\nEnter the Burst Time (BT) for each process:\n";
    for (int i = 0; i < processCount; i++) {
        processes[i].id = i + 1;
        cout << "Process " << i + 1 << " Burst Time: ";
        cin >> processes[i].burstTime;
        processes[i].remainingTime = processes[i].burstTime;
        processes[i].waitingTime = 0;
        processes[i].turnaroundTime = 0;
    }

    cout << "\nEnter Time Quantum: ";
    cin >> timeQuantum;

    // Step 2: Round Robin Scheduling Simulation
    queue<int> readyQueue;
    for (int i = 0; i < processCount; i++) {
        readyQueue.push(i);
    }

    int currentTime = 0;
    vector<pair<int,int>> gantt; // {processId, endTime}

    while (!readyQueue.empty()) {
        int idx = readyQueue.front();
        readyQueue.pop();

        if (processes[idx].remainingTime > 0) {
            int execTime = min(timeQuantum, processes[idx].remainingTime);
            currentTime += execTime;
            processes[idx].remainingTime -= execTime;

            gantt.push_back({processes[idx].id, currentTime});

            if (processes[idx].remainingTime > 0) {
                readyQueue.push(idx); // process goes back to queue
            } else {
                processes[idx].turnaroundTime = currentTime;
                processes[idx].waitingTime = processes[idx].turnaroundTime - processes[idx].burstTime;
            }
        }
    }

    // Step 3: Displaying the process table
    cout << "\nProcess\tBurst Time\tWaiting Time\tTurnaround Time\n";
    cout << "------------------------------------------------------\n";
    for (int i = 0; i < processCount; i++) {
        cout << "P" << processes[i].id << "\t" 
             << processes[i].burstTime << "\t\t" 
             << processes[i].waitingTime << "\t\t" 
             << processes[i].turnaroundTime << "\n";
    }

    // Step 4: Calculating averages
    double totalWT = 0, totalTAT = 0;
    for (int i = 0; i < processCount; i++) {
        totalWT += processes[i].waitingTime;
        totalTAT += processes[i].turnaroundTime;
    }
    cout << fixed << setprecision(2);
    cout << "\nAverage Waiting Time: " << (totalWT / processCount);
    cout << "\nAverage Turnaround Time: " << (totalTAT / processCount) << "\n";

    // Step 5: Gantt Chart
    cout << "\nGantt Chart:\n";
    cout << "------------------------------------------------\n";
    cout << "|";
    for (auto &p : gantt) {
        cout << "  P" << p.first << "  |";
    }
    cout << "\n------------------------------------------------\n";

    cout << "0";
    for (auto &p : gantt) {
        cout << setw(6) << p.second;
    }
    cout << "\n";

    cout << "\n=== Round Robin Scheduling Completed ===\n";

    return 0;
}
