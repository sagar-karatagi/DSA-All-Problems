class MinStack {
    stack<int> Element;
    stack<int> MinElement;
public:
    MinStack() {
        
    }
    void push(int val) {
        if(Element.empty()){
            MinElement.push(val);
        }else if(!MinElement.empty() && val <= MinElement.top()){
            MinElement.push(val);
        }
        Element.push(val);
    }
    void pop() {
        if(!MinElement.empty() && MinElement.top() == Element.top()){
            MinElement.pop();
        }
        Element.pop();
    }
    
    int top() {
        return Element.top();
    }
    
    int getMin() {
        return MinElement.top();
    }
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(val);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */
