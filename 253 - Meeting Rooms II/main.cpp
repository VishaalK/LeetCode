#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

/**
 * Definition for an interval. */
struct Interval {
    int start;
    int end;
    Interval() : start(0), end(0) {}
    Interval(int s, int e) : start(s), end(e) {}
};

class Solution {
    vector<vector<Interval>> rooms;

public:
    int minMeetingRooms(vector<Interval>& intervals) {
        // union find -> number of distinct components
        // assign to rooms, and if a room can't take it, add a new one
        for (auto interval : intervals) {
            // for each room, chekc if it abuts with all the intervals already in that room
            // if there is one where it doesn't abut, push the interval into that room
            placeRooms(rooms, interval);
        }
        
        // cout << intervals.size() << endl;

        // print rooms
        for (auto room : rooms) {
            for (auto interval : room) {
                cout << "(" << interval.start << "," << interval.end << ") - ";
            }
            cout << endl;
        }

        return rooms.size();
    }

    void placeRooms(vector<vector<Interval>>& rooms, const Interval& interval) {
        for (auto room: rooms) {
            auto abutsWithAnyExistingRooms = any_of(room.begin(), room.end(), [this, interval](const Interval& i) {
                return this->overlaps(interval, i);
            });

            if (!abutsWithAnyExistingRooms) {
                room.push_back(interval);
                cout << "placed1:" << endl;
                return;
            }
        }

        cout << "placed2:" << endl;
        rooms.push_back(vector<Interval>{interval});
    }
    
    bool overlaps(const Interval& l, const Interval& r) {
        auto first = l.start < r.start ? l : r;
        auto second = l.start < r.start ? r : l;
        
        return second.start < first.end;
    }
};

void test_overlaps() { 
    assert(Solution().overlaps(Interval(8, 9), Interval(8, 9)));
    assert(Solution().overlaps(Interval(5,10), Interval(9, 14)));
    assert(!Solution().overlaps(Interval(5, 10), Interval(10, 15)));
    assert(!Solution().overlaps(Interval(5, 10), Interval(20, 25)));
}

void test1() {
    vector<Interval> A{
        {Interval(0, 30)},
        {Interval(5, 10)},
        {Interval(15, 20)}
    };

    assert(Solution().minMeetingRooms(A) == 2);
}

void test2() {
    vector<Interval> A{
        {Interval(7, 10)},
        {Interval(2, 4)}
    };

    assert(Solution().minMeetingRooms(A) == 1);
}

void test3() {
    vector<Interval> A{
        {Interval(13,15)},
        {Interval(1,13)}
    };

    assert(Solution().minMeetingRooms(A) == 1);
}

void test4() {
    vector<Interval> A{
        {Interval(1,5)},
        {Interval(8,9)},
        {Interval(8,9)}
    };

    assert(Solution().minMeetingRooms(A) == 2);
}
int main() {
    test_overlaps();
    // test1();
    // test2();
    // test3();
    test4();
}