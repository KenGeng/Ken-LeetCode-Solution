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

### 9. [31. Next Permutation](https://leetcode.com/problems/next-permutation/)

```c++
//idea: 在当前序列中，从尾端往前寻找两个相邻元素，前一个记为first，后一个记为second，并且满足first 小于 second。然后再从尾端寻找另一个元素number，如果满足first 小于number，即将第first个元素与number元素对调，并将second元素之后（包括second）的所有元素颠倒排序，即求出下一个序列


class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        int len = nums.size();
        if (len <=1 ) return;
        int i = len - 2;
        while(i>=0&&nums[i+1]<=nums[i]) i--;
                
        if(i>=0){
            int j = len-1;
            while(j>=0&&nums[j]<=nums[i]) j--;
            int temp = nums[i];
            nums[i] = nums[j];
            nums[j] = temp;
        }
        
        //reverse
        for(int k = i+1 ; k < (len+i+1)/2; k++){
            
            int t = nums[k];
            nums[k] = nums[len-k+i];
            nums[len-k+i] = t;
            
        }
        
    }
};
```

### 10. [33. Search in Rotated Sorted Array](https://leetcode.com/problems/search-in-rotated-sorted-array/)
这个做了差不多两个小时 才想明白 我真的不适合学计算机
```c++
class Solution {
public:
    int search(vector<int>& nums, int target) {
        int len = nums.size();
        if(!len) return -1;
        
        int l = 0;
        int r = len-1;
        int cur = 0;
        while(l<=r){
            cur = (l+r)/2;
            if(nums[cur] == target) return cur;
            
            if(nums[cur] >= nums[l]){//the max element must be in the right part; so the left part is ascending; must be ">="  because as we use floor div in c++, so when length is even, cur is the rightest element in the left part. In this way we can update l and r correctly.
                if(target>=nums[l]&&target < nums[cur]){
                    r = cur-1;
                }else {
                    l = cur+1;
                }
            }else{
                if(target>nums[cur]&&target <= nums[r]){
                    l = cur+1;
                }else {
                    r = cur-1;
                }
            }
            
        }
        
        return -1;
    }
};
```

### 11.[34. Find First and Last Position of Element in Sorted Array](https://leetcode.com/problems/find-first-and-last-position-of-element-in-sorted-array/)

```c++
class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        int len = nums.size();
        int l=0 ,r = len-1;
        vector<int> res;
        int i0,i1;
        if(len==0) {
            res.push_back(-1);
            res.push_back(-1);
            return res;
        }
        while(l<r){// here is the key
            i0 = (l+r)/2;
            
            if(nums[i0]<target){
               l=i0+1; 
            }else r=i0;// here is the key; do not set r=i0-1; at last, if target exists in the array, l would be its leftest index.
        }
        if(nums[l]!=target){
            res.push_back(-1);
            res.push_back(-1);
            return res;
        }
        res.push_back(l);
        r = len-1;
        while(l<r){
            i1 = (l+r)/2+1;
           
            if(nums[i1]>target){
                r=i1-1;
            }else l=i1;
        }
        
 
        
        res.push_back(r);

        return res;
        
    }
};
```

### 12.[35. Search Insert Position](https://leetcode.com/problems/search-insert-position/)
```c++
class Solution {
public:
    int searchInsert(vector<int>& nums, int target) {
        int len  = nums.size();
        int l= 0,r=len-1;
        int mid = 0;
        while(l<r){
            mid = (l+r)/2;
            if(nums[mid] < target){
                l = mid+1;
            }else  r=mid;
        }
        if(nums[l]<target) return l+1;
        else return l;
    }
};
```
### 13.[39. Combination Sum](https://leetcode.com/problems/combination-sum/)

```c++
class Solution {
public:
    
    void util(vector<int>& candidates, int target,vector<int>& cur_res, vector<vector<int>>& results){
        if(target==0) results.push_back(cur_res);
        else if(target < 0) return;
        else{
            for(int i =0 ; i < candidates.size();i++){
                if(cur_res.size()==0||cur_res[cur_res.size()-1]<=candidates[i]){//shortcut calculation
                    cur_res.push_back(candidates[i]);
                    util(candidates,target-candidates[i],cur_res,results);
                    cur_res.pop_back();
                }
                
                
            }
        }
        
    }
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<vector<int>> results;
        vector<int> cur_res;
        util(candidates,target,cur_res,results);
        return results;
    }
};
```

a prune version
```c++
class Solution {
public:
    
    void util(vector<int>& candidates, int target,vector<int>& cur_res, vector<vector<int>>& results){
        if(target==0) results.push_back(cur_res);
        else if(target < 0) return;
        else{
            for(int i =0 ; i < candidates.size()&& target >= candidates[i];i++){//prune
                if(cur_res.size()==0||cur_res[cur_res.size()-1]<=candidates[i]){//shortcut calculation
                    cur_res.push_back(candidates[i]);
                    util(candidates,target-candidates[i],cur_res,results);
                    cur_res.pop_back();
                }
                
                
            }
        }
        
    }
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        sort(candidates.begin(),candidates.end());//sort for pruning
        vector<vector<int>> results;
        vector<int> cur_res;
        util(candidates,target,cur_res,results);
        return results;
    }
};
```

### 14.[40. Combination Sum II](https://leetcode.com/problems/combination-sum-ii/)

```c++
class Solution {
public:
        void util(vector<int>& candidates,int begin, int target,vector<int>& cur_res, vector<vector<int>>& results){
        if(target==0) results.push_back(cur_res);
        else if(target < 0) return;
        else{
            for(int i = begin ; i < candidates.size();i++){
                if(cur_res.size()==0||cur_res[cur_res.size()-1]<=candidates[i]){
                    cur_res.push_back(candidates[i]);
               
                    util(candidates,i+1,target-candidates[i],cur_res,results);
                    cur_res.pop_back();
            
                
                    while(i<candidates.size()-1&&candidates[i]==candidates[i+1]) i++;//skip the same element
                    
                }   
            }
        }
        
    }
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        vector<vector<int>> results;
        vector<int> cur_res;
        int begin =0;
        sort(candidates.begin(),candidates.end());
        util(candidates,0,target,cur_res,results);
        return results;
    }
};
```

### 15. [41. First Missing Positive](https://leetcode.com/problems/first-missing-positive/)

我的解法:
```c++
class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        vector<int> bucket;
        sort(nums.begin(),nums.end());
        for(int i =0;i<nums.size();i++){
            if(nums[i]>0) {
                if(bucket.size()>0) {
                    if(nums[i]>bucket[bucket.size()-1]) bucket.push_back(nums[i]);
                }else bucket.push_back(nums[i]);
            }
        }

        int len=bucket.size();
        if(len==0) return 1;
        int res = 1;
        for(int i =0;i<len;i++){
            if(bucket[i]<=res) res++;
            if(i<len-1&&bucket[i]<bucket[i+1]-1) {
                return res<bucket[i]+1?res:bucket[i]+1;
            }
        }

        return res;
    }
};
```

评论区的漂亮解法:
```c++
class Solution
{
public:
    int firstMissingPositive(int A[], int n)
    {
        for(int i = 0; i < n; ++ i)
            while(A[i] > 0 && A[i] <= n && A[A[i] - 1] != A[i])
                swap(A[i], A[A[i] - 1]);
        
        for(int i = 0; i < n; ++ i)
            if(A[i] != i + 1)
                return i + 1;
        
        return n + 1;
    }
};
```

###  16. [42. Trapping Rain Water](https://leetcode.com/problems/trapping-rain-water/)
我的暴力解法(一行一行地数格子):
```c++
class Solution {
public:
    int trap(vector<int>& height) {
        int max= 0;
        int len = height.size();
        for(int i=0;i<len;i++){
            if(height[i]>max) max=height[i];
        }
        int res=0;
        for(int i=1;i<=max;i++){
            int l=len-1,r=0;
            for(int j=0;j<len;j++){
                if(height[j]>=i) {
                    l=j;
                    break;
                }
            }
            for(int j=len-1;j>=0;j--){
                if(height[j]>=i) {
                    r=j;
                    break;
                }
            }
            for(int j=l;j<=r;j++){
                if(height[j]<i) res++;
            }
        }
        return res;
    }
};
```
评论区的漂亮解法
左右摇摆数格子 一列一列的数
```c++
class Solution {
public:
    int trap(int A[], int n) {
        int left=0; int right=n-1;
        int res=0;
        int maxleft=0, maxright=0;
        while(left<=right){
            if(A[left]<=A[right]){
                if(A[left]>=maxleft) maxleft=A[left];
                else res+=maxleft-A[left];
                left++;
            }
            else{
                if(A[right]>=maxright) maxright= A[right];
                else res+=maxright-A[right];
                right--;
            }
        }
        return res;
    }
};
```

### 17. [45. Jump Game II](https://leetcode.com/problems/jump-game-ii/)

我的超时的递归解法
```c++
class Solution {
public:
    int jump(vector<int>& nums) {
        vector<int> res;
        int cur=0,cnt=0;
        if(nums.size()==1) return 0;
        util( nums,res,cur,cnt);
        int min = 1000000;
        for(int i=0;i<res.size();i++ ){
      
            if(min>res[i]) min=res[i];
        }
        return min;
    }
         
    void util(vector<int>& nums, vector<int>& res,int cur,int cnt){
        if(cur+nums[cur]>=nums.size()-1) res.push_back(cnt+1);
        else if(cur!=nums.size()-1&&nums[cur]==0||(res.size()>0&&cnt>=res[res.size()-1])) return;
        else{
            for(int i = nums[cur];i>=1;i--){
                cnt++;
                cur+=i;
                util( nums,res,cur,cnt);
                cur-=i;
                cnt--;
            }
        }
    }
    
};
```

[科学的用BFS思想的解法-可达节点放在一层](https://leetcode.com/problems/jump-game-ii/discuss/18207/Sharing-my-straightforward-C%2B%2B-solution)

```c++
class Solution {
public:
    int jump(vector<int>& nums) {
        int len = nums.size();
        int cur=0,cnt=0;
        if(nums.size()<2) return 0;
        
        int level=0,currentMax=0,i=0,nextMax=0;

         while(currentMax-i+1>0){		//nodes count of current level>0
             level++;
             for(;i<=currentMax;i++){	//traverse current level , and update the max reach of next level
                nextMax=nextMax>nums[i]+i?nextMax:nums[i]+i;
                if(nextMax>=len-1) return level;   // if last element is in level+1,  then the min jump=level 
             }
             currentMax=nextMax;
         }
        return 0;
    }
         

};
```

### 18.[48. Rotate Image](https://leetcode.com/problems/rotate-image/)
```c++
class Solution {
public:
    // void rotate(vector<vector<int>>& matrix) {
    //      reverse(matrix.begin(), matrix.end());
    // for (int i = 0; i < matrix.size(); ++i) {
    //     for (int j = i + 1; j < matrix[i].size(); ++j)
    //         swap(matrix[i][j], matrix[j][i]);
    // }
    // }
     
//      void rotate(vector<vector<int>>& m) {
//         int n = m.size();
        
//         for(int i=0; i<n; i++)
//             for(int j=0; j<i; j++)
//                 swap(m[i][j], m[j][i]);
        
//         for(int i=0; i<n; i++)
//             reverse(m[i].begin(), m[i].end());
//     }
    void rotate(vector<vector<int>>& matrix) {
        int n =  matrix.size();
         for (int i=0; i<n/2; ++i)
    {
        for (int j=i; j<n-1-i; ++j)
        {
            int z = matrix[i][j];
            matrix[i][j] = matrix[n-j-1][i];
            matrix[n-j-1][i] = matrix[n-i-1][n-j-1];
            matrix[n-i-1][n-j-1] = matrix[j][n-i-1];
            matrix[j][n-i-1] = z;
        }
    }
    }
};
```

评论区大佬:
here give a common method to solve the image rotation problems.
```c++
/*
 * clockwise rotate
 * first reverse up to down, then swap the symmetry 
 * 1 2 3     7 8 9     7 4 1
 * 4 5 6  => 4 5 6  => 8 5 2
 * 7 8 9     1 2 3     9 6 3
*/
void rotate(vector<vector<int> > &matrix) {
    reverse(matrix.begin(), matrix.end());
    for (int i = 0; i < matrix.size(); ++i) {
        for (int j = i + 1; j < matrix[i].size(); ++j)
            swap(matrix[i][j], matrix[j][i]);
    }
}

/*
 * anticlockwise rotate
 * first reverse left to right, then swap the symmetry
 * 1 2 3     3 2 1     3 6 9
 * 4 5 6  => 6 5 4  => 2 5 8
 * 7 8 9     9 8 7     1 4 7
*/
void anti_rotate(vector<vector<int> > &matrix) {
    for (auto vi : matrix) reverse(vi.begin(), vi.end());
    for (int i = 0; i < matrix.size(); ++i) {
        for (int j = i + 1; j < matrix[i].size(); ++j)
            swap(matrix[i][j], matrix[j][i]);
    }
}
```

### 19.[53. Maximum Subarray](https://leetcode.com/problems/maximum-subarray/)
#### 一个简洁的online:
```c++
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int res=nums[0];
        int sum =0;
        for(int i = 0;i<nums.size();i++){
            sum += nums[i];
            res = max(res,sum);
            sum = max(sum,0);
            
        }
        return res;
    }
};
```
#### 一个分治算法(待补充)


### 20.[54. Spiral Matrix](https://leetcode.com/problems/spiral-matrix/)
#### 绕圈遍历
做了好久没做出来 对顺时针理解得不到位....
```c++
class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        vector<int> res;
        int m = matrix.size();
        if(m==0) return res;
        int n = matrix[0].size();
        
        int l = 0, r = n-1;//left right
        int t = 0, b = m-1;//top bottom
        while(l<=r&&t<=b){
            for(int i = l; i<=r;i++) res.push_back(matrix[t][i]);
            
            for(int i = t+1;i<=b;i++) res.push_back(matrix[i][r]);
            if(l<r&&t<b){
                for(int i = r-1;i>l;i--) res.push_back(matrix[b][i]);
                for(int i = b; i> t;i--) res.push_back(matrix[i][l]);
            }
            l++;
            r--;
            t++;
            b--;
        }
     
        return res;
    }
};
```
#### 评论区里一个很好看的解法
```c++
class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        if (matrix.empty()) return {};
        int m = matrix.size(), n = matrix[0].size();
        vector<int> spiral(m * n);
        int u = 0, d = m - 1, l = 0, r = n - 1, k = 0;
        while (true) {
            // up
            for (int col = l; col <= r; col++) spiral[k++] = matrix[u][col];
            if (++u > d) break;
            // right
            for (int row = u; row <= d; row++) spiral[k++] = matrix[row][r];
            if (--r < l) break;
            // down
            for (int col = r; col >= l; col--) spiral[k++] = matrix[d][col];
            if (--d < u) break;
            // left
            for (int row = d; row >= u; row--) spiral[k++] = matrix[row][l];
            if (++l > r) break;
        }
        return spiral;
    }
};
```

###21. [55.Jump Game - LeetCode](https://leetcode.com/problems/jump-game/)
我的解法(DP by myself)
```c++
class Solution {
public:
    bool canJump(vector<int>& nums) {

        int len = nums.size();
        if(!len) return false;
        
        vector<int> judge(len,0);
        judge[len-1]=1;
        
        for(int i = len-1;i>=0;i--){
            for(int j=i;j<=i+nums[i]&&j<len;j++){
            
                if(judge[j]==1) {
                    judge[i]=1;
                    break;
                }
            
            }
        }
        return judge[0]==1; 

           
    }
};
```
elegant greedy code from comments:
```c++
bool canJump(int A[], int n) {
    int i = 0;
    for (int reach = 0; i < n && i <= reach; ++i)
        reach = max(i + A[i], reach);
    return i == n;
}
```

### 21. [56.Merge Intervals - LeetCode](https://leetcode.com/problems/merge-intervals/)

```c++
/**
 * Definition for an interval.
 * struct Interval {
 *     int start;
 *     int end;
 *     Interval() : start(0), end(0) {}
 *     Interval(int s, int e) : start(s), end(e) {}
 * };
 */
class Solution {
public:
    
    static bool compare(const Interval &odd1,const Interval &odd2)
    {
        return odd1.start<odd2.start;
    }
    vector<Interval> merge(vector<Interval>& intervals) {
        int len = intervals.size();
        vector<Interval> res;
        if(len == 1 || len ==0 ) return intervals;
        //sort according to the 'start' , so we only need to consider 3 situations: 
        //a. [1,2],[2,3] 
        //b. [1,3],[2,3]
        //c. [1,2],[4,5]
        sort(intervals.begin(),intervals.end(),compare);
        Interval temp = intervals[0];
        for(int i = 1 ; i < len; i++){
            
            if(temp.end >= intervals[i].start && temp.end < intervals[i].end){//situation a 
                temp = Interval(temp.start, intervals[i].end);
            }else if(temp.end >= intervals[i].end ){//situation b
                temp = Interval(temp.start, temp.end);
            }else{//situation c
                res.push_back(temp);
                temp = intervals[i];
            }
        }
        //add the last one
        res.push_back(temp);
        return res;
    }
};
```

评论区利用 按start已经排序好的性质 提出的O(N)解法:
```c++
class Solution {
public:
    vector<Interval> insert(vector<Interval>& intervals, Interval newInterval) {
        vector<Interval> res;
        int index = 0;
        while(index < intervals.size() && intervals[index].end < newInterval.start){
            res.push_back(intervals[index++]);
        }
        while(index < intervals.size() && intervals[index].start <= newInterval.end){
            newInterval.start = min(newInterval.start, intervals[index].start);
            newInterval.end = max(newInterval.end, intervals[index].end);
            index++;
        }
        res.push_back(newInterval);
        while(index < intervals.size()){
            res.push_back(intervals[index++]);
        }
        return res;
    }
};
```

### 22. [59.Spiral Matrix II - LeetCode](https://leetcode.com/problems/spiral-matrix-ii/)

c++绕圈圈
```c++
class Solution {
public:
    vector<vector<int>> generateMatrix(int n) {
        vector<vector<int>> res(n, vector<int>(n,0));
        
        if(!n) return res;
        
        int r0=0,r1=n-1;
        int c0=0,c1=n-1;
        int num=1;
        while(r0<=r1 && c0<=c1 ){
            
            if(r0==r1) {
                res[r0][c0]=num;
                break;
            }
            for(int i = c0;i < c1;i++){
                res[r0][i] = num++;
            }
            // r0++;
            for(int i = r0; i< r1;i++){
                res[i][c1] = num++;
            }
            
            for(int i = c1; i> c0; i--){
                res[r1][i] = num++;
            }
            
            for(int i = r1; i > r0; i--){
                res[i][c0] = num++;
            }
            c0++;
            c1--;
            r0++;
            r1--;
        }
        
        return res;
    }
};
```

评论区的更漂亮一点的解法:
```c++
public class Solution {
    public int[][] generateMatrix(int n) {
        // Declaration
        int[][] matrix = new int[n][n];
        
        // Edge Case
        if (n == 0) {
            return matrix;
        }
        
        // Normal Case
        int rowStart = 0;
        int rowEnd = n-1;
        int colStart = 0;
        int colEnd = n-1;
        int num = 1; //change
        
        while (rowStart <= rowEnd && colStart <= colEnd) {
            for (int i = colStart; i <= colEnd; i ++) {
                matrix[rowStart][i] = num ++; //change
            }
            rowStart ++;
            
            for (int i = rowStart; i <= rowEnd; i ++) {
                matrix[i][colEnd] = num ++; //change
            }
            colEnd --;
            
            for (int i = colEnd; i >= colStart; i --) {
                if (rowStart <= rowEnd)
                    matrix[rowEnd][i] = num ++; //change
            }
            rowEnd --;
            
            for (int i = rowEnd; i >= rowStart; i --) {
                if (colStart <= colEnd)
                    matrix[i][colStart] = num ++; //change
            }
            colStart ++;
        }
        
        return matrix;
    }
}
```

### 23. [62.Unique Paths - LeetCode](https://leetcode.com/problems/unique-paths/)

```c++
class Solution {
public:
    int uniquePaths(int m, int n) {
        //C(m+1,n)
        double num,deno;
        num=1;
        deno=1;
        n--;
        m--;
        double temp = max(m,n);
        
        for(int i = m+n;i>temp;i--) num*=i;
        if(temp == m) for(int i = 1;i<=n; i++) deno*=i;
        else for(int i = 1;i<=m; i++) deno*=i;
        return num/deno;
    }
};
```
评论区的漂亮DP:
```c++
class Solution {
public:
    int uniquePaths(int m, int n) {
        vector<vector<int>> dp(m, vector<int>(n, 1));
        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {
                dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
            }
        }
        return dp[m - 1][n - 1];
    }
};
```
