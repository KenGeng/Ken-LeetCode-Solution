class Solution {
public:
    //dp
//     int numSquares(int n) {
//         // prepare square number array
//         int sq[n+1] ={0};
//         int sq_limit = sqrt(n)+1;
//         for(int i = 1; i < sq_limit; i++) sq[i] = i*i;
        
//         // initial dp array
//         vector<int> dp(n+1,INT_MAX);
        
//         dp[0] = 0;
//         for(int i = 1; i < n+1; i++){
//             for(int j = 1; j < sq_limit; j++){
//                 if(i<sq[j]) break;
//                 dp[i] = min(dp[i],dp[i-sq[j]]+1);
//             }
//         }
        

//         return dp[n];
//     }
    //bfs
//     int numSquares(int n) {
//         // prepare square number array
//         vector<int> sq(n+1);

//         int sq_limit = sqrt(n)+1;
//         for(int i = 1; i < sq_limit; i++) {
//             sq[i] = i*i;   
//         }
        
//         unordered_set<int> queue;
//         queue.insert(n);
//         int level = 0;
//         while(!queue.empty()){
//             level++;
//             unordered_set<int> next_queue;
//             for(auto& item : queue){
//                 for(auto i:sq){
//                     if(item == i) return level;
//                     else if( item < i) break;
//                     else next_queue.insert(item-i);
//                 }
//             }
//             queue = next_queue;
//         }

//         return level;
//     }
    // bfs from [Summary of 4 different solutions (BFS, DP, static DP and mathematics) - LeetCode Discuss](https://leetcode.com/problems/perfect-squares/discuss/71488/Summary-of-4-different-solutions-(BFS-DP-static-DP-and-mathematics)); much faster
    int numSquares(int n) 
    {
        if (n <= 0)
        {
            return 0;
        }
        
        // perfectSquares contain all perfect square numbers which 
        // are smaller than or equal to n.
        vector<int> perfectSquares;
        // cntPerfectSquares[i - 1] = the least number of perfect 
        // square numbers which sum to i.
        vector<int> cntPerfectSquares(n);
        
        // Get all the perfect square numbers which are smaller than 
        // or equal to n.
        for (int i = 1; i*i <= n; i++)
        {
            perfectSquares.push_back(i*i);
            cntPerfectSquares[i*i - 1] = 1;
        }
        
        // If n is a perfect square number, return 1 immediately.
        if (perfectSquares.back() == n)
        {
            return 1;
        }
        
        // Consider a graph which consists of number 0, 1,...,n as
        // its nodes. Node j is connected to node i via an edge if  
        // and only if either j = i + (a perfect square number) or 
        // i = j + (a perfect square number). Starting from node 0, 
        // do the breadth-first search. If we reach node n at step 
        // m, then the least number of perfect square numbers which 
        // sum to n is m. Here since we have already obtained the 
        // perfect square numbers, we have actually finished the 
        // search at step 1.
        queue<int> searchQ;
        for (auto& i : perfectSquares)
        {
            searchQ.push(i);
        }
        
        int currCntPerfectSquares = 1;
        while (!searchQ.empty())
        {
            currCntPerfectSquares++;
            
            int searchQSize = searchQ.size();
            for (int i = 0; i < searchQSize; i++)
            {
                int tmp = searchQ.front();
                // Check the neighbors of node tmp which are the sum 
                // of tmp and a perfect square number.
                for (auto& j : perfectSquares)
                {
                    if (tmp + j == n)
                    {
                        // We have reached node n.
                        return currCntPerfectSquares;
                    }
                    else if ((tmp + j < n) && (cntPerfectSquares[tmp + j - 1] == 0))
                    {
                        // If cntPerfectSquares[tmp + j - 1] > 0, this is not 
                        // the first time that we visit this node and we should 
                        // skip the node (tmp + j).
                        cntPerfectSquares[tmp + j - 1] = currCntPerfectSquares;
                        searchQ.push(tmp + j);
                    }
                    else if (tmp + j > n)
                    {
                        // We don't need to consider the nodes which are greater ]
                        // than n.
                        break;
                    }
                }
                
                searchQ.pop();
            }
        }
        
        return 0;
    }
};