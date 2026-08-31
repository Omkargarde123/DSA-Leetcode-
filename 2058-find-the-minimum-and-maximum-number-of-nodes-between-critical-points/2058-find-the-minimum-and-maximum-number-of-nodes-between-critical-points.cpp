/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    vector<int> nodesBetweenCriticalPoints(ListNode* head) {
        // Less than 3 nodes cannot have any critical points
        if (!head || !head->next || !head->next->next) {
            return {-1, -1};
        }

        int firstCritical = -1;
        int prevCritical = -1;
        int minDistance = INT_MAX;
        
        ListNode* prev = head;
        ListNode* curr = head->next;
        int index = 1; // 0-indexed position of curr

        while (curr->next != nullptr) {
            ListNode* next = curr->next;

            // Check if curr is a local maxima or local minima
            bool isMaxima = (curr->val > prev->val) && (curr->val > next->val);
            bool isMinima = (curr->val < prev->val) && (curr->val < next->val);

            if (isMaxima || isMinima) {
                if (firstCritical == -1) {
                    firstCritical = index;
                } else {
                    minDistance = min(minDistance, index - prevCritical);
                }
                prevCritical = index;
            }

            prev = curr;
            curr = next;
            index++;
        }

        // If fewer than 2 critical points were found
        if (minDistance == INT_MAX) {
            return {-1, -1};
        }

        int maxDistance = prevCritical - firstCritical;
        return {minDistance, maxDistance};
    }
};