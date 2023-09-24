class Solution {
public:
    int garbageCollection(vector<string>& garbage, vector<int>& travel) {
        
        
        int Ptime =0;
        int Gtime =0;
        int Mtime =0;
        int LPtime = 0;
        int LGtime = 0;
        int LMtime = 0;

        travel.push_back(0);
        for(int i =0;i<garbage.size();i++){
                bool Mgarbage = 0;
                bool Ggarbage = 0;
                bool Pgarbage = 0;

                    for(auto j:garbage[i]){
                        if(j == 'G'){
                            Gtime++;LGtime++;
                            Ggarbage =1;
                        }else if(j == 'P'){
                            Ptime++;
                            Pgarbage = 1;
                            LPtime++;
                        }else{
                            Mtime++;LMtime++;
                            Mgarbage =1;
                        }
                    }
            if(Pgarbage) LPtime = Ptime;
            if(Mgarbage) LMtime = Mtime;
            if(Ggarbage) LGtime = Gtime;
                
            Mtime+= travel[i];
            Gtime+=travel[i];
            Ptime+= travel[i];
        }
        return LMtime+LPtime+LGtime;
    }
};