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
    int getDecimalValue(ListNode* head) {
        
        ListNode* curr = head;
        int num = 0;
        int i = 30;
        int size = 0;
        while(curr){
            if(curr->val==1){
                num+=1<<i;
            }
            --i;
            size++;
            curr=curr->next;
        }
        num = num >> (31-size);
        return num;
    }
};
