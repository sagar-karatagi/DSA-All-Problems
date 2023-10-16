class Solution {
public:
    string simplifyPath(string path) {
        stack<char> st;
        string ans;
        int count = 0;
        for(auto i:path){
            if(st.empty()){
                st.push(i);
            }else{
                if(i == '.'){
                    count++;
                }else if(i == '/'){
                    if(st.top() != '/'){
                        if(count >= 1){
                            while(count != 0){
                                st.push('.');
                                --count;
                            }
                    }count = 0;
                    st.push(i);
                    }else{
                        //Handling the dots
                        if(count == 2){
                            st.pop();
                            while(!st.empty() && st.top() !='/'){
                                st.pop();
                            }
                            if(st.empty()){
                                st.push('/');
                            }
                        }else if(count >= 3){
                            while(count != 0){
                                st.push('.');
                                --count;
                            }
                            st.push(i);
                        }
                        //Making count 0 again
                        count = 0;
                    }
                }else{
                    if(count >= 1){
                        while(count != 0){
                            st.push('.');
                            --count;
                        }
                    }count = 0;
                    st.push(i);
                }
            }
        }
        if(count == 2){
            if(st.top() == '/'){
                st.pop();
                while(!st.empty() && st.top()!='/'){
                    st.pop();
                }
                if(st.empty()){
                    st.push('/');
                }
            }else{
                while(count!=0){
                    st.push('.');
                    --count;
                }
            }
        }else if(count >= 3){
            while(count != 0){
                st.push('.');
                --count;
            }
        }
        if(st.top() == '/' && st.size()>1){
            st.pop();
        }
        while(!st.empty()){
            ans+=st.top();
            st.pop();
        }
        reverse(ans.begin(),ans.end());
        return ans;
    }
};        
