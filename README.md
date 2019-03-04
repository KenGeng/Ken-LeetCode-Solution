# LeetCode-Solution-C
LeetCode Solution in C++

# LeetCode题解

## Array

### 1. [Container With Most Water](https://leetcode.com/problems/container-with-most-water/)

Answer:

a. 暴搜

```c++
class Solution {
public:
    int maxArea(vector<int>& height) {
        int res=-1;
        for (int i = 0; i < height.size(); i++){
            for (int j =i+1 ; j< height.size(); j++){
                int h = height[i]>height[j]?height[j]:height[i];
                int temp = (j-i)*h;
                if (temp>res) res=temp;
            }
                
        
        }
        return res;
        
    }
};
```

b. 左右横跳

```c++
class Solution {
public:
    int maxArea(vector<int>& height) {
        int res = -1;
        int l=0,r=height.size()-1;
        while(l<r){
            if(height[l]<height[r]){
                int temp = (r-l)*height[l];
                if (temp>res) res = temp;
                l++;
            }else{
                int temp = (r-l)*height[r];
                if (temp>res) res = temp;
                r--;
                
            }
            
        }
        
        return res;
        
    }
};
```

### 2. [15. 3Sum](https://leetcode.com/problems/3sum/)

   a. 暴力+用二分查找找第三个数+规避特殊的全是0的case

```c++
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> res;
        int len = nums.size();
        sort(nums.begin(), nums.end()); 
        int fuck=0;
        for (int i=0;i<len;i++) {
            if (nums[i]!=0) {
                fuck=1;
                break;
            }
        }
        if (!fuck&&len>2) {
            vector<int> temp;
            temp.push_back(0);
            temp.push_back(0);
            temp.push_back(0);
            res.push_back(temp);
            return res;
        }
        
        for (int i=0;i<len-2;i++){
            for (int j=i+1;j<len-1;j++){
                
                    
                    vector<int> temp;
                    int num_to_find=-nums[i]-nums[j];
                if (binary_search(nums.begin()+j+1,nums.end(),num_to_find)){
                    vector<int>::iterator iter=std::lower_bound(nums.begin()+j+1,nums.end(),num_to_find);
                if(iter!=nums.end()){
                        temp.push_back(nums[i]);
                        temp.push_back(nums[j]);
                        temp.push_back(-nums[i]-nums[j]);
                        sort(temp.begin(), temp.end());
                        int is_exist=0;
                        // for(int m=0;m<res.size();m++){
                        //     if(temp==res[m]) is_exist=1;
                        // }
                        if(is_exist==0) res.push_back(temp);
                }
                }
                        
            
            
            
        }
    }
     sort(res.begin(), res.end());   
     vector<vector<int>>::iterator iter = unique(res.begin(),res.end());
     res.erase(iter,res.end());
     return res;                                           
    }
};
                                            	
```

   b. 网上的漂亮解法 左右游标 N*N
```c++
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> res;
        
        sort(nums.begin(), nums.end()); 
        int len = nums.size();
        for(int i = 0;i<len-2;i++){
            int l =i+1;
            int r =len-1;
            
            if (nums[i]>0) break;
            if (i>0&& nums[i]==nums[i-1]) continue;//special case; remember to avoid all numberes are zeros.
            while(l<r){
                
                if (nums[i]+nums[l]+nums[r] < 0){
                    l++;
                }else if (nums[i]+nums[l]+nums[r] > 0){
                    r--;
                }else{
                    vector<int> temp;
                    temp.push_back(nums[i]);
                    temp.push_back(nums[l]);
                    temp.push_back(nums[r]);
                    res.push_back(temp);
                    
                    while(l<r&&nums[l]==nums[l+1]) l++;
                    while(l<r&&nums[r]==nums[r-1]) r--;
                    
                    l++;
                    r--;
                }
                
                
            }
        }
        
        return res;
    }
};
```

### 3. [16. 3Sum Closest](https://leetcode.com/problems/3sum-closest/)
```c++
class Solution {
public:
    int threeSumClosest(vector<int>& nums, int target) {
        int res;
        
        sort(nums.begin(), nums.end()); 
        int min = 1000000000;
        int len = nums.size();
        for(int i = 0;i<len-2;i++){
            int l =i+1;
            int r =len-1;

            while(l<r){
                int sum = nums[i]+nums[l]+nums[r];
                int dif = target-sum;
                if (abs(dif) > min ){
                    if(dif>0) l++;
                    else r--;
                }else{
                    min=abs(dif);
                    res=sum;
                    if(dif>0) l++;
                    else if(dif<0) r--;
                    else return target;
                }
                
                
            }
        }
        
        return res;
    }
};
```
