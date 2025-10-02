class Solution:
    def maxBottlesDrunk(self, numBottles: int, exchange: int) -> int:

        empty = numBottles
        ans = numBottles
        numBottles = 0

        while(empty >= exchange):
            ans+=1
            empty-= exchange - 1         
            exchange+=1

        return ans


        
