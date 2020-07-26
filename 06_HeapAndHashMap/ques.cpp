#include <iostream>
#include <list>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

// Leetcode 215. Kth Largest Element in an Array==================
int findKthLargest(vector<int>& nums, int k) {
    priority_queue<int, vector<int>, greater<int>> pq;

    for (int i = 0; i < k; i++) pq.push(nums[i]);

    for (int i = k; i < nums.size(); i++)
        if (nums[i] > pq.top()) {
            pq.pop();
            pq.push(nums[i]);
        }

    return pq.top();
}

// Leetcode 703. Kth Largest Element in a Stream==================
class KthLargest {
    priority_queue<int, vector<int>, greater<int>> pq;
    int size = -1;

   public:
    KthLargest(int k, vector<int>& nums) {
        size = k;
        for (int ele : nums) {
            pq.push(ele);
            if (pq.size() > k) pq.pop();
        }
    }

    int add(int val) {
        pq.push(val);
        if (pq.size() > size) pq.pop();

        return pq.top();
    }
};

// Leetcode 378. Kth Smallest Element in a Sorted Matrix==========
// same question in java file having different approach
int kthSmallest(vector<vector<int>>& matrix, int k) {
    priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> pq;

    // in vector==========
    // 0th index is val
    // 1st index is row
    // 2nd index is col
    for (int i = 0; i < matrix.size(); i++) {
        vector<int> arr{matrix[i][0], i, 0};
        pq.push(arr);
    }

    for (int i = 0; i < k - 1; i++) {
        vector<int> rem = pq.top();
        pq.pop();

        int r = rem[1];
        int c = rem[2];

        if (c < matrix[0].size() - 1)
            pq.push(vector<int>{matrix[r][c + 1], r, c + 1});
    }
    return pq.top()[0];
}

// Leetcode 786. K-th Smallest Prime Fraction====================
// Approach 1 - solve with double
// it gives TLE on Leetcode
vector<int> kthSmallestPrimeFraction(vector<int>& arr, int K) {
    // We implement max priority queue, but insert number in negative form
    // to prevent from long and weird syntax of min PQ
    priority_queue<pair<double, pair<int, int>>> pq;

    int n = arr.size();
    for (int i = 1; i < n; i++)
        pq.push({-(arr[0] * 1.0) / arr[i], {0, i}});

    for (int i = 1; i < K; i++) {
        int r = pq.top().second.first;
        int c = pq.top().second.second;

        pq.pop();

        if (r + 1 < c) {
            pq.push({-(arr[r + 1] * 1.0) / arr[c], {r + 1, c}});
        }
    }

    return vector<int>{arr[pq.top().second.first], arr[pq.top().second.second]};
}

// Leetcode 349. Intersection of Two Arrays=======================
vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
    vector<int> result;
    if (nums1.size() == 0 || nums2.size() == 0)
        return result;

    unordered_map<int, int> map;
    for (int val : nums1)
        map[val]++;

    for (int val : nums2)
        if (map.count(val) != 0) {
            result.push_back(val);
            map.erase(val);
        }

    return result;
}

// Leetcode 350. Intersection of Two Arrays II====================
vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
    vector<int> result;
    if (nums1.size() == 0 || nums2.size() == 0)
        return result;

    unordered_map<int, int> map;
    for (int val : nums1)
        map[val]++;

    for (int val : nums2)
        if (map.count(val) != 0) {
            result.push_back(val);
            map[val]--;
            if (map[val] == 0)
                map.erase(val);
        }

    return result;
}

// Leetcode 128. Longest Consecutive Sequence=====================
int longestConsecutive(vector<int>& nums) {
    unordered_map<int, int> map;

    for (int ele : nums)
        map[ele]++;

    int len = 0;
    for (int ele : nums) {
        if (map.find(ele) == map.end())
            continue;

        map.erase(ele);
        // make potential previous and next
        int prevEle = ele - 1;
        int nextEle = ele + 1;

        while (map.find(prevEle) != map.end())
            map.erase(prevEle--);
        while (map.find(nextEle) != map.end())
            map.erase(nextEle++);

        len = max(len, nextEle - prevEle - 1);
    }

    return len;
}

// Leetcode 347. Top K Frequent Elements==========================
// using class in java file
vector<int> topKFrequent(vector<int>& nums, int k) {
    unordered_map<int, int> map;

    for (int ele : nums)
        map[ele]++;

    // Min Priority Queue
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    for (pair<int, int> p : map) {
        pq.push({p.second, p.first});

        if (pq.size() > k) {
            pq.pop();
        }
    }

    vector<int> res;
    while (pq.size() != 0) {
        pair<int, int> p = pq.top();
        pq.pop();

        res.push_back(p.second);
    }
    return res;
}

// Leetcode 49. Group Anagrams====================================
vector<vector<string>> groupAnagrams(vector<string>& strs) {
    unordered_map<string, vector<string>> map;
    for (string& str : strs) {
        int freq[26] = {0};
        for (int i = 0; i < str.size(); i++)
            freq[str[i] - 'a']++;

        string code = "";
        for (int i = 0; i < 26; i++)
            if (freq[i] > 0)
                code += string(1, (char)(i + 'a')) + "" + to_string(freq[i]);

        map[code].push_back(str);
    }

    vector<vector<string>> ans;
    for (auto keys : map) {
        ans.push_back(keys.second);
    }
    return ans;
}

// Leetcode 380. Insert Delete GetRandom O(1)=====================
class RandomizedSet {
   private:
    unordered_map<int, int> map;
    vector<int> arr;

   public:
    /** Initialize your data structure here. */
    RandomizedSet() {
    }

    /** Inserts a value to the set. Returns true if the set did not already contain the specified element. */
    bool insert(int val) {
        if (map.count(val) != 0)
            return false;

        arr.push_back(val);
        map[val] = arr.size() - 1;
        return true;
    }

    /** Removes a value from the set. Returns true if the set contained the specified element. */
    bool remove(int val) {
        if (map.count(val) == 0)
            return false;

        // get index of removal value
        int indx = map[val];

        // swap the value from last
        swap(arr[indx], arr[arr.size() - 1]);
        // set the change value in hashmap too
        map[arr[indx]] = indx;

        // remove from vector and hashmap
        map.erase(val);
        arr.pop_back();

        return true;
    }

    /** Get a random element from the set. */
    int getRandom() {
        int loc = rand() % arr.size();
        return arr[loc];
    }
};

// Leetcode 295. Find Median from Data Stream=====================
class MedianFinder {
   private:
    priority_queue<int, vector<int>, greater<int>> minPQ;  // right region
    priority_queue<int> maxPQ;                             // left region

    void balance() {
        if (maxPQ.size() > minPQ.size() + 1) {
            minPQ.push(maxPQ.top());
            maxPQ.pop();
        } else if (minPQ.size() > maxPQ.size()) {
            maxPQ.push(minPQ.top());
            minPQ.pop();
        }
    }

   public:
    /** initialize your data structure here. */
    MedianFinder() {
    }

    void addNum(int num) {
        if (maxPQ.size() == 0 || maxPQ.top() > num)
            maxPQ.push(num);
        else
            minPQ.push(num);

        balance();
    }

    double findMedian() {
        if (minPQ.size() == maxPQ.size()) {
            return (minPQ.top() + maxPQ.top()) * 1.0 / 2;
        } else {
            return maxPQ.top() * 1.0;
        }
    }
};

// Leetcode 407. Trapping Rain Water II===========================
int trapRainWater(vector<vector<int>>& map) {
    int r = map.size();
    int c = map[0].size();

    vector<vector<bool>> vis(r, vector<bool>(c, false));

    // use typedef to prevent from type again and again
    typedef pair<int, pair<int, int>> cell;  // (height, i * m + j)

    priority_queue<cell, vector<cell>, greater<cell>> pq;

    // all all the boaundaries in priority Queue

    // first column and last column add in PQ
    for (int i = 0; i < r; i++) {
        pq.push({map[i][0], {i, 0}});
        pq.push({map[i][c - 1], {i, c - 1}});
        // marking in visited
        vis[i][0] = true;
        vis[i][c - 1] = true;
    }

    // first row and last row add in PQ
    for (int j = 1; j < c - 1; j++) {
        pq.push({map[0][j], {0, j}});
        pq.push({map[r - 1][j], {r - 1, j}});
        // marking in visited
        vis[0][j] = true;
        vis[r - 1][j] = true;
    }

    // now move on priority queue
    int water = 0;
    int maxTillNow = 0;

    while (pq.size() > 0) {
        cell rem = pq.top();
        pq.pop();

        if (maxTillNow < rem.first) {
            maxTillNow = rem.first;
        }

        int x = rem.second.first;
        int y = rem.second.second;
        // left
        if (y - 1 >= 0 && vis[x][y - 1] == false) {
            if (map[x][y - 1] < maxTillNow) {
                water += (maxTillNow - map[x][y - 1]);
                pq.push({maxTillNow, {x, y - 1}});
            } else
                pq.push({map[x][y - 1], {x, y - 1}});
        }
        // top
        if (x - 1 >= 0 && vis[x - 1][y] == false) {
            if (map[x - 1][y] < maxTillNow) {
                water += (maxTillNow - map[x - 1][y]);
                pq.push({maxTillNow, {x - 1, y}});
            } else
                pq.push({map[x - 1][y], {x - 1, y}});
        }
        //right
        if (y + 1 < c && vis[x][y + 1] == false) {
            if (map[x][y + 1] < maxTillNow) {
                water += (maxTillNow - map[x][y + 1]);
                pq.push({maxTillNow, {x, y - 1}});
            } else
                pq.push({map[x][y + 1], {x, y + 1}});
        }
        // down
        if (x + 1 < r && vis[x + 1][y] == false) {
            if (map[x + 1][y] < maxTillNow) {
                water += (maxTillNow - map[x + 1][y]);
                pq.push({maxTillNow, {x + 1, y}});
            } else
                pq.push({map[x + 1][y], {x + 1, y}});
        }
    }

    return water;
}

// Leetcode 138. Copy List with Random Pointer==========================
class Node {
   public:
    int val;
    Node* next;
    Node* random;

    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};
class Solution {
    Node* copyRandomList(Node* head) {
    }
};

// Leetcode 778. Swim in Rising Water
int swimInWater(vector<vector<int>>& grid) {
    int r = grid.size();
    int c = grid[0].size();

    vector<vector<bool>> vis(r, vector<bool>(c, false));
    typedef pair<int, int> cell;  // {Height, i * c + j}
    priority_queue<cell, vector<cell>, greater<cell>> pq;

    pq.push({grid[0][0], 0});
    vis[0][0] = true;

    int maxWait = 0;

    vector<vector<int>> dir = {{0, -1}, {-1, 0}, {0, 1}, {1, 0}};

    while (pq.size() > 0) {
        cell rem = pq.top();
        pq.pop();

        int height = rem.first;
        int x = rem.second / c;
        int y = rem.second % c;

        maxWait = max(maxWait, height);

        if (x == r - 1 && y == c - 1)
            break;

        for (int i = 0; i < 4; i++) {
            int ii = x + dir[i][0];
            int jj = y + dir[i][1];

            if (ii >= 0 && ii < r &&
                jj >= 0 && jj < c && vis[ii][jj] == false) {
                pq.push({grid[ii][jj], (ii * c + jj)});
                vis[ii][jj] = true;
            }
        }
    }
    return maxWait;
}

// Leetcode 146. LRU Cache
// just for submission - using STL
class LRUCache {
    unordered_map<int, int> map;  // {key, value}
    list<int> ll;
    int size = 0;

   public:
    LRUCache(int capacity) {
        this->size = capacity;
    }

    int get(int key) {
        if (map.find(key) == map.end())
            return -1;
        else {
            // erase from that position in linkedlist
            ll.remove(key);  // O(n)

            // add add it in front
            ll.push_back(key);  // O(1)

            return map[key];
        }
    }

    void put(int key, int value) {
        if (map.find(key) != map.end()) {
            ll.remove(key);     // O(n)
            ll.push_back(key);  // O(1)
            map[key] = value;   // O(1)
        } else {
            map[key] = value;
            // check for size
            if (ll.size() == size) {
                map.erase(ll.front());
                ll.pop_front();
            }

            ll.push_back(key);
        }
    }
};

int main(int argc, char** argv) {
}