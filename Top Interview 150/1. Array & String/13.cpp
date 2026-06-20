#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    bool canJump(vector<int>& nums) {

        // max_index = farthest position we can reach so far.
        // Initially we are standing at index 0, so the farthest reachable index is 0.
        //
        // Why needed?
        // We must continuously track the best reachable position.
        //
        // If removed:
        // We lose information about how far we can currently travel.
        //
        // Example:
        // nums = [2,3,1,1,4]
        // Initially:
        // max_index = 0
        int max_index = 0;

        // Traverse every index of the array.
        //
        // Why needed?
        // We must check whether each position is reachable and update
        // the farthest reachable position.
        //
        // If removed:
        // No indices are processed, so we cannot determine reachability.
        //
        // Dry Run:
        // nums = [2,3,1,1,4]
        //
        // i=0
        // i=1
        // i=2
        // i=3
        // i=4
        for (int i = 0; i < nums.size(); i++) {

            // Check whether current index is reachable.
            //
            // Logic:
            // If current index is greater than max_index,
            // then we cannot even stand on this index.
            //
            // Why needed?
            // Once an index becomes unreachable, moving further
            // is impossible.
            //
            // If removed:
            // The algorithm may incorrectly assume unreachable
            // positions can still be used to jump further.
            //
            // Example:
            // nums = [3,2,1,0,4]
            //
            // i=0 -> max_index=3
            // i=1 -> reachable
            // i=2 -> reachable
            // i=3 -> reachable
            // i=4 -> NOT reachable because 4 > 3
            //
            // Therefore answer = false.
            if (i > max_index) {
                return false;
            }

            // Update the farthest reachable index.
            //
            // Current reach:
            // i + nums[i]
            //
            // We compare it with previously known best reach
            // and keep the maximum.
            //
            // Why needed?
            // A later index may allow us to jump farther.
            //
            // If removed:
            // max_index never expands and the algorithm fails.
            //
            // Dry Run:
            // nums = [2,3,1,1,4]
            //
            // i=0:
            // reach = 0+2 = 2
            // max_index = max(0,2)=2
            //
            // i=1:
            // reach = 1+3 = 4
            // max_index = max(2,4)=4
            //
            // i=2:
            // reach = 2+1 = 3
            // max_index remains 4
            //
            // i=3:
            // reach = 3+1 = 4
            // max_index remains 4
            //
            // i=4:
            // reach = 4+4 = 8
            // max_index becomes 8
            //
            // Since last index is reachable,
            // answer = true.
            max_index = max(max_index, i + nums[i]);
        }

        // If loop finishes successfully,
        // every visited index was reachable.
        //
        // Why needed?
        // Reaching this point means we never got stuck.
        //
        // If removed:
        // Function would not return a value.
        //
        // Edge Case:
        // nums = [0]
        //
        // Loop executes once:
        // i=0 reachable
        // return true
        //
        // Correct because we already start at the last index.
        return true;
    }
};

int main() {

    return 0;
}