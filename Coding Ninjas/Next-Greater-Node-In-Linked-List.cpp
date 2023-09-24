#include <bits/stdc++.h> 
/****************************************************************

    Following is the class structure of the Node class:

        class Node
        {
        public:
	        int data;
	        Node *next;
	        Node(int data)
	        {
		        this->data = data;
		        this->next = NULL;
	        }
        };

*****************************************************************/

vector<int> findNextGreaterNodeList(Node* head){
    
	stack<int> s;
	s.push(INT_MAX);
	vector<int> arr;
	Node* curr = head;
	while(curr){
		arr.push_back(curr->data);
		curr= curr->next;
	}
	vector<int> ans(arr.size());
	for(int i = arr.size()-1;i>-1;i--){

		while(s.top()<= arr[i]){
			s.pop();
		}

		if(s.top()==INT_MAX){
			ans[i]= 0;
		}else{
			ans[i]= s.top();
		}
		s.push(arr[i]);
	}
	return ans;
}