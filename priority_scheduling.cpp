#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
using namespace std;

struct Process
{
    int id;
    int burstTime;
    int priority;
    int waitingTime;
    int turnaroundTime;
};

int main()
{
    int processCount;
    cout << "=== Priority Scheduling (Non-Preemptive) ===\n";
    cout << "Enter the number of processes: ";
    cin >> processCount;

    vector<Process> processes(processCount);

    // Step 1: Taking input Burst Time and Priority
    cout << "\nEnter the Burst Time (BT) and Priority for each process:\n";
    for (int i = 0; i < processCount; i++)
    {
        processes[i].id = i + 1;
        cout << "Process " << i + 1 << " Burst Time: ";
        cin >> processes[i].burstTime;
        cout << "Process " << i + 1
             << " Priority (choose between 1 and " << processCount
             << ", smaller number = higher priority): ";
        cin >> processes[i].priority;
    }

    // Step 2: Sort processes by priority
    sort(processes.begin(), processes.end(), [](Process a, Process b)
         { return a.priority < b.priority; });

    // Step 3: Calculating waiting times
    processes[0].waitingTime = 0;
    for (int i = 1; i < processCount; i++)
    {
        processes[i].waitingTime = processes[i - 1].waitingTime + processes[i - 1].burstTime;
    }

    // Step 4: Calculating turnaround times
    for (int i = 0; i < processCount; i++)
    {
        processes[i].turnaroundTime = processes[i].waitingTime + processes[i].burstTime;
    }

    // Step 5: Display process table
    cout << "\nProcess\tBT\tPriority\tWT\tTAT\n";
    cout << "-----------------------------------------------\n";
    for (int i = 0; i < processCount; i++)
    {
        cout << "P" << processes[i].id << "\t"
             << processes[i].burstTime << "\t"
             << processes[i].priority << "\t\t"
             << processes[i].waitingTime << "\t"
             << processes[i].turnaroundTime << "\n";
    }

    // Step 6: Average WT and TAT
    double totalWT = 0, totalTAT = 0;
    for (int i = 0; i < processCount; i++)
    {
        totalWT += processes[i].waitingTime;
        totalTAT += processes[i].turnaroundTime;
    }
    cout << fixed << setprecision(2);
    cout << "\nAverage Waiting Time: " << (totalWT / processCount);
    cout << "\nAverage Turnaround Time: " << (totalTAT / processCount) << "\n";

    // Step 7: Gantt Chart
    cout << "\nGantt Chart:\n";
    cout << "------------------------------------------------\n";
    cout << "|";
    for (int i = 0; i < processCount; i++)
    {
        cout << "  P" << processes[i].id << "  |";
    }
    cout << "\n------------------------------------------------\n";

    cout << "0";
    for (int i = 0; i < processCount; i++)
    {
        cout << setw(6) << processes[i].waitingTime + processes[i].burstTime;
    }
    cout << "\n";

    cout << "\n=== Priority Scheduling Completed ===\n";
    return 0;
}
