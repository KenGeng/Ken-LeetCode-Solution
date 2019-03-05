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

### 4. [18. 4Sum](https://leetcode.com/problems/4sum/submissions/)

a. 在3sum基础上 再套一层循环

```c++
class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        vector<vector<int>> res;
        
        sort(nums.begin(), nums.end()); 
        int len = nums.size();
        for(int i = 0;i < len - 3 ; i++){
            
            if(i>0 && nums[i] == nums[i-1]) continue; //avoid the first two elements are same
            for(int j = i + 1 ; j < len - 2 ; j++ ){
                
                if(j>i+1 && nums[j] == nums[j-1]) continue; //avoid the second and third elements are same
                int l = j + 1;
                int r = len - 1;
                
                while(l < r){
                    int sum = nums[i] + nums[j] + nums[l] + nums[r];
                    
                    if(sum < target) l++;
                    else if (sum > target) r--;
                    else{

                        res.push_back({nums[i],nums[j],nums[l],nums[r]});
                        
                        while(l<r&&nums[l]==nums[l+1]) l++;
                        while(l<r&&nums[r]==nums[r-1]) r--;
                        
                        l++;
                        r--;
                    }
                }
            }
        } 
        return res;
    }
};
```
b. 递归版本
```c++

class Solution {
public:
    void nSum(vector<int> nums, int n, int target, vector<int>& cur_res, vector<vector<int>>& results){
        int len = nums.size();
        if(len < n || n < 2 || target < nums[0]*n ||target > nums[len-1]*n ) return ;
        
        if (n == 2 ){
            int l = 0;
            int r = len - 1;

            while(l < r){
                int sum = nums[l] + nums[r];

                if(sum < target) l++;
                else if (sum > target) r--;
                else{
                    cur_res.push_back(nums[l]);
                    cur_res.push_back(nums[r]);  
                    results.push_back(cur_res);
                    cur_res.pop_back();
                    cur_res.pop_back();
                    while(l<r&&nums[l]==nums[l+1]) l++;
                    while(l<r&&nums[r]==nums[r-1]) r--;

                    l++;
                    r--;
                }
                
            }
            
            return;
        }else{
            
            for (int i = 0; i < len - n + 1;i++){
                if(i>0 && nums[i] == nums[i-1]) continue; 
                vector<int> nums_new;
                nums_new.insert(nums_new.end(),nums.begin()+i+1,nums.end());
                
                cur_res.push_back(nums[i]);
                nSum(nums_new,n-1, target-nums[i],cur_res,results);
                cur_res.pop_back();
            }
        }
    }
    
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        vector<vector<int>> res;
        
        sort(nums.begin(), nums.end()); 
        int len = nums.size();
        vector<int> cur_res;
        nSum(nums, 4, target, cur_res, res);
        return res;
    }
};
```
### 5.[Median of Two Sorted Arrays](https://leetcode.com/problems/median-of-two-sorted-arrays/)

```c++
class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int m = nums1.size(),n = nums2.size();
        if(m==0) return n%2==0?(nums2[n/2-1]+nums2[n/2])/2.0:nums2[n/2];
        if(n==0) return m%2==0?(nums1[m/2-1]+nums1[m/2])/2.0:nums1[m/2];
        if (m > n) {//ensure m<=n

            nums1.swap(nums2);
            int temp2 = m;
            m = n;
            n = temp2;
        }
        int i_min =0,i_max=m;// i's range
        int half=(m+n+1)/2; // if m+n is even, as int division is down to floor, result is right; if m+n is odd,result is right,too
        while (i_min <= i_max){
            int i = (i_max+i_min)/2;//binary search
            int j = half - i;
            if (i < i_max && nums2[j-1] > nums1[i]) {
                i_min = i+1;// i is small
            }else if (i>i_min && nums1[i-1]>nums2[j]) {
                i_max = i-1;
            }else{// get the right i
                int max_left = 0;
                if (i==0) max_left=nums2[j-1];
                else if (j==0) max_left=nums1[i-1];
                else {
                    max_left = max(nums1[i-1],nums2[j-1]);
                }
                if ((m+n)%2 == 1) {// when it is odd
                    return max_left;
                }
                int min_right = 0;
                if (i==m) {
                    min_right=nums2[j];
                } else if (j==n) {
                    min_right= nums1[i];
                } else min_right=min(nums1[i],nums2[j]);

                return (max_left + min_right)/2.0;


            }

        }

    }
};
```

### 6. [1. Two Sum](https://leetcode.com/problems/two-sum/)
左右游标
```c++
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        vector<int> temp = nums;
        sort(nums.begin(),nums.end());
        int len = nums.size();
        
        vector<int> res;
        
        int l = 0;
        int r = len-1;
        
        while(l<r){
            int sum = nums[l]+nums[r];
            if(sum < target) l++;
            else if(sum > target) r--;
            else{
                res.push_back(nums[l]);
                res.push_back(nums[r]);
                // break;
                while(l<r&&nums[l]==nums[l+1]) l++;
                while(l<r&&nums[r]==nums[r-1]) r--;
                l++;
                r--;
            }
        }
        vector<int> res_trans;
        for(int i = 0;i < len; i++ ){
            if(res[0] == temp[i]) {
                res_trans.push_back(i);
                continue;
            }
            if(res[1] == temp[i]) res_trans.push_back(i);
        }
        
        return res_trans;
    }
};
```

### 7 [26. Remove Duplicates from Sorted Array](https://leetcode.com/problems/remove-duplicates-from-sorted-array/)

a. 我的
```c++
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int len = nums.size();
        if(len==0) return 0;
        int cnt = 1;
        for(int i = 0;i<len;){
            int l = i;
           
            while(l<len&&nums[i] == nums[l]) l++;
            if (l==len) break;
            else {
                cnt++;
                nums[cnt-1] = nums[l]; 
            }
            i = l;
            
        }
        return cnt;
    }
};
```

b. 我简化后的版本
```c++
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int len = nums.size();
        if(len==0) return 0;
        int cnt = 0;
        for(int i = 0;i<len;){
            nums[cnt++] = nums[i];
           
            while(i<len&&nums[cnt-1] == nums[i]) i++; //find next different element
                
        }
        return cnt;
    }
};
```

c. [讨论区的漂亮解法](https://leetcode.com/problems/remove-duplicates-from-sorted-array/discuss/11780/5-lines-C%2B%2BJava-nicer-loops)
```c++
int removeDuplicates(vector<int>& nums) {
    int i = !nums.empty();
    for (int n : nums)
        if (n > nums[i-1])
            nums[i++] = n;
    return i;
}
```
### 8. [27. Remove Element](https://leetcode.com/problems/remove-element/)

我的
```c++
class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
    
        if(nums.size()==0) return 0;
        int cnt = 0;
        for(int i = 0 ; i < nums.size();i++){
            if(nums[i]!=val) nums[cnt++]=nums[i];
        }
        
        return cnt;
    }
};
```