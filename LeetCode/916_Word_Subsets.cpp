class Solution {
public:
    vector<string> wordSubsets(vector<string>& words1, vector<string>& words2) {
        unordered_map<char,int> masterMap;
        for(const string& word : words2){
            unordered_map<char,int> temp;
            for(const char& c:word){
                temp[c]++;
            }
            for(auto it :temp){
                masterMap[it.first] = max(masterMap[it.first],it.second);
            }

        }
        vector<string> result;
        for (const string& word : words1) {
            unordered_map<char, int> wordFreq;
            for (char c : word) {
                wordFreq[c]++;
            }
            bool isValid = true;
            for (auto& it : masterMap) {
                if (wordFreq[it.first] < it.second) {
                    isValid = false;
                    break;
                }
            }
            if (isValid) {
                result.push_back(word);
            }
        }
        return result;
    }
};
