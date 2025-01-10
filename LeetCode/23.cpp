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
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        ios_base::sync_with_stdio(false);
        cin.tie(nullptr);
        cout.tie(nullptr);
        if(!lists.size()) return nullptr;

        vector<int> v;
        for(int i =0;i<lists.size();i++){
            ListNode* temp = lists[i];
            while(temp){
                v.push_back(temp->val);
                temp = temp->next;
            }
        }
        sort(v.begin(),v.end());
        ListNode* head = NULL;
        ListNode* curr = NULL;
        for(auto i: v){
            if(!head){
                head = new ListNode(i);
                curr = head;
            }else{
                curr->next = new ListNode(i);
                curr = curr->next;
            }
        }
        return head;
    }
};

