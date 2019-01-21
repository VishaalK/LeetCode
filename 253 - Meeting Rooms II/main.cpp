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
    vector<vector<Interval>*> rooms;

public:
    int minMeetingRooms(vector<Interval>& intervals) {
        sort(intervals.begin(), intervals.end(), [](const Interval& l, const Interval& r) {
            return l.start < r.start;
        });

        // union find -> number of distinct components
        // assign to rooms, and if a room can't take it, add a new one
        for (auto interval : intervals) {
            // for each room, chekc if it abuts with all the intervals already in that room
            // if there is one where it doesn't abut, push the interval into that room
            placeRooms(rooms, interval);
        }
        
        // cout << intervals.size() << endl;

        // print rooms
        // for (auto room : rooms) {
        //     for (auto interval : room) {
        //         // cout << "(" << interval.start << "," << interval.end << ") - ";
        //     }
        //     // cout << endl;
        // }

        return rooms.size();
    }

    void printState(vector<vector<Interval>>& rooms) {
        for (auto room : rooms) {
            for (auto interval : room) {
                cout << "(" << interval.start << "," << interval.end << ") - ";
            }
            cout << endl;
        }
    }

    void printState(const vector<vector<Interval>*>& rooms) {
        // cout << "pointer rooms size: " << rooms.size() << endl;
        // for (auto room : rooms) {
        //     cout << "numIntervals in room: " << room->size() << endl;
        //     for (auto interval : *room) {
        //         cout << "(" << interval.start << "," << interval.end << ") - ";
        //     }
        //     cout << endl;
        // }
    }

    void placeRooms(vector<vector<Interval>*>& rooms, const Interval& interval) {
        // for each room, figure out the minimum meeting time that this interval does not abut with
        vector<vector<Interval>*> availableRooms;
        for (auto roomPtr : rooms) {
            auto available = none_of(roomPtr->begin(), roomPtr->end(), [this, interval](const Interval& i) {
                return this->overlaps(interval, i);
            });

            if (available) {
                // cout << "Found an available room: " << endl;
                // for (const Interval i : *roomPtr) {
                    // cout << "(" << i.start << "," << i.end << ") - ";
                // }
                // cout << endl;

                availableRooms.push_back(roomPtr);
            }
        }

        // cout << "available rooms: " << endl;
        printState(availableRooms);

        // room to insert into
        sort(begin(availableRooms), end(availableRooms), [](const vector<Interval>* l, const vector<Interval>* r) {
            return l->back().end < r->back().end;
        });

        if (availableRooms.empty()) {
            // cout << "No rooms, so creating a new one" << endl;
            rooms.push_back(new vector<Interval>{interval});
            return;
        } else {
            // cout << "Pushing into an existing room" << endl;
            availableRooms.front()->push_back(interval);
        }

        printState(availableRooms);

        // auto ;

        // for (auto& room: rooms) {
        //     auto abutsWithAnyExistingRooms = any_of(room.begin(), room.end(), [this, interval](const Interval& i) {
        //         return this->overlaps(interval, i);
        //     });

        //     if (!abutsWithAnyExistingRooms) {
        //         // for (auto l : room) {
        //         //     // cout << "(" << l.start << "," << l.end << ") - ";
        //         // }
        //         // cout << endl;
        //         room.push_back(interval);
        //         // for (auto l : room) {
        //         //     // cout << "(" << l.start << "," << l.end << ") - ";
        //         // }
        //         // cout << endl;
        //         // cout << "placed1:" << endl;
        //         // cout << "afterwards1" << endl;
        //         printState(rooms);
        //         return;
        //     }
        // }

        // cout << "placed2:" << endl;
        // rooms.push_back(vector<Interval>{interval});

        // cout << "afterwards2" << endl;
        // printState(rooms);
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

    auto ans = Solution().minMeetingRooms(A);
    // cout << ans << endl;
    assert(ans == 2);
}

void test5() {
    vector<Interval> A{Interval(64738,614406),Interval(211748,780229),Interval(208641,307338),Interval(499908,869489),Interval(218907,889449),Interval(177201,481150),Interval(123679,384415),Interval(120440,404695),Interval(191810,491295),Interval(800783,826206),Interval(165175,221995),Interval(420412,799259),Interval(484168,617671),Interval(746410,886281),Interval(765198,792311),Interval(493853,971285),Interval(194579,313372),Interval(119757,766274),Interval(101315,917883),Interval(557309,599256),Interval(167729,723580),Interval(731216,988021),Interval(225883,752657),Interval(588461,854166),Interval(231328,285640),Interval(772811,869625),Interval(892212,973218),Interval(143535,306402),Interval(336799,998119),Interval(65892,767719),Interval(380440,518918),Interval(321447,558462),Interval(54489,234291),Interval(43934,44986),Interval(11260,968186),Interval(248987,707178),Interval(355162,798511),Interval(661962,781083),Interval(149228,412762),Interval(71084,953153),Interval(44890,655659),Interval(708781,956341),Interval(251847,707658),Interval(650743,932826),Interval(561965,814428),Interval(697026,932724),Interval(583473,919161),Interval(463638,951519),Interval(769086,785893),Interval(17912,923570),Interval(423089,653531),Interval(317269,395886),Interval(412117,701471),Interval(465312,520002),Interval(168739,770178),Interval(624091,814316),Interval(143729,249836),Interval(699196,879379),Interval(585322,989087),Interval(501009,949840),Interval(424092,80498),Interval(282845,345477),Interval(453883,926476),Interval(392148,878695),Interval(471772,771547),Interval(339375,590100),Interval(110499,619323),Interval(8713,291093),Interval(268241,283247),Interval(160815,621452),Interval(168922,810532),Interval(355051,377247),Interval(10461,488835),Interval(220598,261326),Interval(403537,438947),Interval(221492,640708),Interval(114702,926457),Interval(166567,477230),Interval(856127,882961),Interval(218411,256327),Interval(184364,909088),Interval(130802,828793),Interval(312028,811716),Interval(294638,839683),Interval(269329,343517),Interval(167968,391811),Interval(25351,369583),Interval(210660,454598),Interval(166834,576380),Interval(296440,873280),Interval(660142,822072),Interval(33441,778393),Interval(456500,955635),Interval(59220,954158),Interval(306295,429913),Interval(110402,448322),Interval(44523,88192),Interval(231386,353197),Interval(120940,902781),Interval(348758,597599),Interval(329467,664450),Interval(208411,890114),Interval(230238,516885),Interval(434113,602358),Interval(349759,419831),Interval(10689,308144),Interval(94526,180723),Interval(435280,986655),Interval(611999,690154),Interval(75208,395348),Interval(403243,489260),Interval(498884,611075),Interval(487209,863242),Interval(13900,873774),Interval(656706,782943),Interval(53478,586952),Interval(226216,723114),Interval(554799,922759),Interval(467777,689913),Interval(80630,147482),Interval(277803,506346),Interval(532240,976029),Interval(206622,761192),Interval(148277,985819),Interval(10879,807349),Interval(952227,971268),Interval(172074,919866),Interval(239230,384499),Interval(607687,984661),Interval(4405,264532),Interval(41071,437502),Interval(432603,661142),Interval(144398,907360),Interval(139605,360037),Interval(943191,997317),Interval(12894,171584),Interval(382477,800157),Interval(452077,518175),Interval(208007,398880),Interval(375250,489928),Interval(384503,726837),Interval(278181,628759),Interval(114470,635575),Interval(382297,733713),Interval(156559,874172),Interval(507016,815520),Interval(164461,532215),Interval(17332,536971),Interval(418721,911117),Interval(11497,14032)};


    auto ans = Solution().minMeetingRooms(A);
    cout << ans << endl;
    assert(ans == 77);
}

int main() {
    // test_overlaps();
    test1();
    test2();
    test3();
    test4();
    // test5();
}