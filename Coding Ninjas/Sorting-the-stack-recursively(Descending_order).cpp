void insertAtPosition(stack<int>& s,int element){
	if(s.empty()||s.top() <=element ){
		s.push(element);
		return;
	}
	int top = s.top();
	s.pop();
	insertAtPosition(s,element);
	s.push(top);
}
void solve(stack<int>& s,stack<int>& source){
	if(source.empty()) return;

	if(s.empty()||source.top() >= s.top()){
		s.push(source.top());
	}else{
		insertAtPosition(s,source.top());
	}
	source.pop();
	solve(s, source);
}
stack<int> sortStack(stack<int> &s){
	stack<int> ans;
	solve(ans,s);
	return ans;
}