class Solution {
public:
    int strStr(string haystack, string needle) {
      int nSize = needle.size();
      int hSize = haystack.size();
      if(hSize<nSize) return -1;
      for(int i =0;i<hSize;i++){
          if(haystack[i] == needle[0]){
              int temp = i;
              int j = 0;
              while(temp <hSize && haystack[temp] == needle[j]){
                  temp++;
                  j++;
              }
              if(j == nSize){
                  return i;
              }
          }
      }
      return -1;  
    }
};
