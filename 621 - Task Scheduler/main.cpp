#include <vector>
#include <deque>
#include <iostream>
using namespace std;

class Solution {
public:
    int leastInterval(vector<char>& tasks, int n) {
        // there are 26 task types
        // each can have T_1 occurrences
        // as long as there are 2 or more task types, the 
        // cpu will not remain idle
        // the best way to schedule seems to be round robin
        // then, its the difference between the last 2 tasks * 3 + 
        // 2 * the overlap between the last 2 tasks
        // might be easier to just schedule
        
        // get the frequency of each 
        // I could code the cooldown as well
        vector<int> tasksLeft(26, 0);
        int numTasksLeft = 0;
        
        for (auto task : tasks) {
            tasksLeft[task - 'A']++;
            numTasksLeft++;
        }
    
        // iterate through
        int numCycles = 0;
        int currentTaskType = 0;
        
        deque<int> lastTwoTasks; // -1 corresponds to idle
        lastTwoTasks.push_back(-1);
        lastTwoTasks.push_back(-1);
        
        while (numTasksLeft) {
            currentTaskType = findNextTaskTypeToRun(currentTaskType, lastTwoTasks, tasksLeft);

            // I can keep track of the last 2 cycles, and if this task was in the last 2 cycles, skip it
            if (currentTaskType != -1) {
                tasksLeft[currentTaskType]--;
                numTasksLeft--;
                lastTwoTasks.push_back(currentTaskType);
            } else {
                // This is idling
                lastTwoTasks.push_back(-1);
            }

            numCycles++;
            lastTwoTasks.pop_front();
        }
        
        return numCycles;
    }
    
    int findNextTaskTypeToRun(const int currentTaskType, const deque<int>& previousTasks, const vector<int>& tasksLeft) {
        for (int i = 0; i < 26; i++) {
            int taskType = currentTaskType + i % 26;
            if (tasksLeft[taskType] && !taskTypeIsOnCooldown(taskType, previousTasks)) {
                return taskType;
            }
        }
        
        return -1;
    }
    
    bool taskTypeIsOnCooldown(int taskType, const deque<int>& previousTasks) {
        for (auto t : previousTasks) {
            if (t == taskType) {
                return true;
            }
        }
        return false;
    }
};

void test1() {
    vector<char> tasks = {'A','A','A','B','B','B'};
    const int n = 2;

    auto ans = Solution().leastInterval(tasks, n);
    assert(ans == 8);
}

int main() {
    test1();
}