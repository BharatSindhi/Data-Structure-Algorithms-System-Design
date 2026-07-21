#include <iostream>
using namespace std;
class Solution {
public:
    bool hasCycle(ListNode* head) {
        ListNode* slow = head;
        ListNode* fast = head;

        while (fast != NULL && fast->next != NULL) {
            slow = slow->next;          // Move 1 step
            fast = fast->next->next;    // Move 2 steps

            if (slow == fast) {
                return true;
            }
        }

        return false;
    }
};

int main() {
    
    return 0;
}