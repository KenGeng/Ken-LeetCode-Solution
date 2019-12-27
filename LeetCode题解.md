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

### 24. [63.Unique Paths II - LeetCode](https://leetcode.com/problems/unique-paths-ii/)

```c++
class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        
        int r = obstacleGrid.size();
        int c = obstacleGrid[0].size();
        // use long long for int overflow
        vector<vector<long long>> obstacleGrid_long(r,vector<long long>(c,0));
        for(int i =0;i<r;i++) for (int j=0;j<c;j++) obstacleGrid_long[i][j] = obstacleGrid[i][j];
        
        if(obstacleGrid_long[0][0]==1) return 0;
        else obstacleGrid_long[0][0]=1;
        //first col
        for (int i =1;i<r;i++) {
            if (obstacleGrid_long[i-1][0]==1&&obstacleGrid_long[i][0]!=1){
                obstacleGrid_long[i][0] = 1;
            }else obstacleGrid_long[i][0] = 0;
            
        }
        // first row
        for (int i =1;i<c;i++) {
            if (obstacleGrid_long[0][i-1]==1&&obstacleGrid_long[0][i]!=1){
                obstacleGrid_long[0][i] = 1;
            }else obstacleGrid_long[0][i] = 0;
            
        }
        
        for(int i =1;i<r;i++){
            for(int j = 1;j<c;j++){
                if(obstacleGrid_long[i][j]==1) {
                    obstacleGrid_long[i][j] = 0;
                    // continue;
                }       
                else {
                    obstacleGrid_long[i][j] = obstacleGrid_long[i-1][j] + obstacleGrid_long[i][j-1];
                }

            
            }
        }
        return obstacleGrid_long[r-1][c-1];
        
        //good solution from comments
        // int m = obstacleGrid.size() , n = obstacleGrid[0].size();
        // vector<vector<long long>> dp(m+1,vector<long long>(n+1,0));
        // dp[0][1] = 1;
        // for(int i = 1 ; i <= m ; ++i)
        //     for(int j = 1 ; j <= n ; ++j)
        //         if(!obstacleGrid[i-1][j-1])
        //             dp[i][j] = dp[i-1][j]+dp[i][j-1];
        // return dp[m][n];
    }
};
```

### 25.[66.Plus One - LeetCode](https://leetcode.com/problems/plus-one/)
```c++
class Solution {
public:
    vector<int> plusOne(vector<int>& digits) {
        int l = digits.size();
        for(int i = l-1;i>=0;i--) {
            digits[i]+=1;
            if(digits[i]==10) {
                digits[i]=0;
                if(i==0) digits.insert(digits.begin(), 1); 
                continue;
            }else break;
            
        
        }
        return digits;
    }
};
```
### [Reverse Integer - LeetCode](https://leetcode.com/problems/reverse-integer/)

没什么意思的题;刚开始很快用double存储做了出来,尝试只用INT 但判定overflow出了问题 没想到再加一层&&判断 whatever 控制时间 保持冷静 做好总结 不要自毁 不要浪费时间 一题20分钟以内 you can do it.
```c++
#include<cmath>
class Solution {
public:
    int reverse(int x) {
        int res=0;

        while(x!=0){
            
            if(res>INT_MAX/10||(res==INT_MAX&&x%10>7)) return 0;
            if(res<INT_MIN/10||(res==INT_MIN&&x%10<-8)) return 0;
            res=res*10+x%10;
            
            x/=10;
        }
        return res;
          
    }
};
```
## Top 100 Liked Question
### [Linked List Cycle - LeetCode](https://leetcode.com/problems/linked-list-cycle/solution/)
很有趣的一题, 用两个指针,以不同的速度后移,如果能追上说明有环, 就是题意理解不了…            只要二者速度差为1 肯定就能追上 为了变成方便让速度为2和1 
```c++
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    bool hasCycle(ListNode *head) {
        ListNode* slow;
        ListNode* fast;
        if(head==nullptr||head->next==nullptr) return false; 
        slow=head;
        fast=head->next;
        if(slow==fast) return true;
        while(slow!=fast&&slow->next!=nullptr&&fast->next!=nullptr&&fast->next->next!=nullptr){
            
            slow=slow->next;
            fast=fast->next->next;
            if(slow==fast) return true;
            
        }
        return false;
    }
};
```

优化一下的代码:

```c++
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    bool hasCycle(ListNode *head) {
        ListNode* slow;
        ListNode* fast;
        if(head==nullptr||head->next==nullptr) return false; 
        slow=head;
        fast=head->next;
        
        while(slow!=fast){
            if(fast==nullptr||fast->next==nullptr) {
                return false;
            }
            slow=slow->next;
            fast=fast->next->next;
        }
        return true;
    }
};
```

### [Minimum Path Sum - LeetCode](https://leetcode.com/problems/minimum-path-sum/)
standard DP. 
```c++
class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();

        if(m==n&&m==1) return grid[0][0];
        for(int i =1;i<n;i++) grid[0][i]+=grid[0][i-1];//initial first row
        for(int i =1;i<m;i++) grid[i][0]+=grid[i-1][0];//initial first col
        for(int i=1;i<m;i++){
            for(int j =1;j<n;j++){
                grid[i][j]+=grid[i-1][j]<grid[i][j-1]?grid[i-1][j]:grid[i][j-1];
            }
        }
        
        return grid[m-1][n-1];
    }
};
```

### [Basic Calculator - LeetCode](https://leetcode.com/problems/basic-calculator/)
没做出来 卡了好久 非常自闭 和以前写过的中缀计算器记混了 哎
```c++
class Solution {
public:
    int calculate(string s) {
        stack <int> nums, ops;
        int num = 0;
        int rst = 0;
        int sign = 1;
        for (char c : s) { 
            if (isdigit(c)) {
                num = num * 10 + (c - '0');//获得operand
            }
            else {
                rst += sign * num;//全是加法 减法=加负数；最开始有个0+
                num = 0;
                if (c == '+') sign = 1;
                if (c == '-') sign = -1;
                if (c == '(') {
                    nums.push(rst);//当前结果入栈
                    ops.push(sign);//括号前的操作符入栈
                    rst = 0;
                    sign = 1;
                }
                if (c == ')' ) {
                    rst = ops.top() * rst + nums.top();//括号内结果+当前结果
                    ops.pop(); nums.pop();
                }
            }
        }
        rst += sign * num;
        return rst;
    }
};
```
### [Word Break - LeetCode](https://leetcode.com/problems/word-break/)
```c++
class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        if(wordDict.size()==0) return false;

        vector<bool> dp(s.size()+1,false);
        dp[0] = true;
        
        for(int i =1;i<=s.size();i++){
            for(int j = i-1;j>=0;j--){
                if(dp[j]){
                   string word = s.substr(j,i-j);
                    if(std::find(wordDict.begin(),wordDict.end(),word)!=wordDict.end()){                 
                                dp[i] = true;
                                break;
                        } 
                    }
                
            }
        }
        return dp[s.size()];
        
    }
};
```
DP, 找前缀的匹配, 然后应该必须O(n^2)?
two cases:
s = "catsdog", wordDict = ["cats", "dog", "cat"]
s = "catsister", wordDict = ["cats","sister", "cat"]
If there is an O(n) solution, then we can only traverse the s for a one time. If we traverse from front to end, we can not decide which word to match(cat or cats).
If we traverse from end to front, similar cases can be built.

### [Can Make Palindrome from Substring - LeetCode](https://leetcode.com/problems/can-make-palindrome-from-substring/)
需要统计出一个子串有多少个字母落单，这个不做优化的话，统计就是 O(m)的复杂度。
再加上 n 个子串询问，综合复杂度就是 O(n*m)了。

所以这里需要对统计进行优化，比如预先统计好所有前缀子串。
当需要查询某个子串时，两个前缀子串的统计结果相减，就得到当前子串的统计。
(学到了)
```c++
class Solution {
    vector<map<char, int>> base;
    void born(string&s){
        map<char,int> m;
        base.push_back(m);
        for(auto c: s){
            m[c]++;
            base.push_back(m);
        }
    }
    
    int getRange(int l, int r){
        int ans = 0;
        map<char, int> tmp = base[r+1];
        for(auto&p : base[l]){
            tmp[p.first] -= p.second;
        }
        for(auto&p: tmp){
            if(p.second %2 == 1)ans++;
        }
        return ans;
    }
public:
    vector<bool> canMakePaliQueries(string& s, vector<vector<int>>& queries) {
        born(s);
        vector<bool>ans;
        
        for(auto& q: queries){
            int num = getRange(q[0], q[1]);
            if(num/2 <= q[2]){
                ans.push_back(true);
            }else{
                ans.push_back(false);
            }
        }
        
        return ans;
    }
};
```

### [Prime Arrangements - LeetCode](https://leetcode.com/problems/prime-arrangements)
整除的不变性?
```c++
class Solution {
public:
    bool isPrime(int n){
        if (n==1) return false;
        if (n==2) return true;
        for(int i =2;i<=sqrt(n);i++){
            if(n%i==0) return false;
        }
        return true;
    }
    int numPrimeArrangements(int n) {
        int count = 0;
        for(int i = 1;i <= n; i++){
            if(isPrime(i)) count++;
        }
        long long int res = 1;
        for(int i = 1; i <= count; i++){
            res *= i;
            res=res%(1000000000 + 7);
        }
        for(int i = 1; i <= n-count; i++){
            res *= i;
            res=res%(1000000000 + 7);
            
        }
        return res;
        
    }
};
```
### [Diet Plan Performance - LeetCode](https://leetcode.com/problems/diet-plan-performance/)
```c++
class Solution {
public:
    int dietPlanPerformance(vector<int>& calories, int k, int lower, int upper) {
        int res = 0;
        int count = 0;
        int sum = 0;
        for(int i = 0; i<= calories.size()-k;i++){
            if(i>0){
                sum-=calories[i-1];
                sum+=calories[i+k-1];
            }
            else{
                for(int j = i;j<i+k; j++){
                sum += calories[j];
                }
            }
            
            if(sum>upper) res+=1;
            else if(sum<lower) res-=1;
    
            
        }
        return res;
    }
};

```

### [N-ary Tree Level Order Traversal - LeetCode](https://leetcode.com/problems/n-ary-tree-level-order-traversal/submissions/)

```c++
/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> children;

    Node() {}

    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};
*/
class Solution {
public:
    vector<vector<int>> levelOrder(Node* root) {
        std::queue<Node*> myqueue;
        vector<vector<int>> res;
        if (!root) return res;
        myqueue.push(root);
        while(!myqueue.empty()){
            int size = myqueue.size();
            vector<int> cur_level;
            for(int i =0;i<size;i++){
                Node* cur = myqueue.front();
                myqueue.pop();
                cur_level.push_back(cur->val);
                for(auto item : cur->children){
                    myqueue.push(item);
                }
            }
            res.push_back(cur_level);
        }
        return res;
        
    }
};
```

### [Evaluate Division - LeetCode](https://leetcode.com/problems/evaluate-division/submissions/)
学一波BFS的写法
```c++
class Solution {
    unordered_map<string , unordered_map<string, double>> adj_list;
    void construct_adj_list(vector<vector<string>>& equations, vector<double>& values){
        
        for(int i =0;i<equations.size();i++){
            string op1 = equations[i][0];
            string op2 = equations[i][1];
            double val = values[i];
            adj_list[op1][op2] = val;
            adj_list[op2][op1] = 1/val;
        }
    }
    double BFS(string start, string end){
        queue<pair<string, double>> q;
        unordered_set<string> visited;
        q.push(make_pair(start,1));
        visited.insert(start);
    
        while(!q.empty()){
            auto p = q.front();
            q.pop();
            string node = p.first;
            double dist = p.second;
            if(adj_list.find(node)==adj_list.end()) return -1;
            if(node == end){
                // adj_list[start][end] = dist;
                // adj_list[end][start] = 1/dist;
                return dist;
            }
            for(auto i = adj_list[node].begin();i!=adj_list[node].end();i++){
                string next = i->first;
                double weight = i->second;
                if(visited.find(next)==visited.end()){
                    visited.insert(next);
                    q.push(make_pair(next, dist*weight));
                }
            }
        }
        return -1;
    }
public:
    vector<double> calcEquation(vector<vector<string>>& equations, vector<double>& values, vector<vector<string>>& queries) {
        vector<double> res;
       construct_adj_list(equations,values);
        for(auto i : queries){
            string op1 = i[0];
            string op2 = i[1];
            res.push_back({BFS(op1,op2)});
        }
        return res;
        
    }
};
```

### [Longest Palindromic Substring - LeetCode](https://leetcode.com/problems/longest-palindromic-substring/submissions/)
我爱DP
```c++
class Solution {
public:
    string longestPalindrome(string s) {
        int len = s.size();
        if(len<=1) return s;
        int left=0,right=0;
        vector<vector<int>> dp(len, vector<int>(len,0));
        for(int i=0;i<len;i++){
            dp[i][i]=1;
            if(i<len-1&&s[i]==s[i+1]){
                    dp[i][i+1]= 1;
                    left=i;
                    right=i+1;
            }
                
        }
        for(int i=len-3;i>=0;i--){
            for(int j =i+2;j<len;j++){
                if(dp[i+1][j-1]&&s[i]==s[j]){
                    dp[i][j]= 1;
                    if(j-i>right-left) {
                        left = i;
                        right = j;
                    }
                }
            }
        }
        return s.substr(left,right-left+1);
    }
};
```
### [Maximum Distance in Arrays - LeetCode](https://leetcode.com/problems/maximum-distance-in-arrays/submissions/)
```c++
class Solution {
public:
    int maxDistance(vector<vector<int>>& arrays) {
        int len = arrays.size();
        int res = INT_MIN;
        int min_val = arrays[0][0];
        int max_val = arrays[0][arrays[0].size()-1];
        for(int i=1;i<len;i++){
            
            int temp0=abs(max_val-arrays[i][0]);
            int temp1=abs(arrays[i][arrays[i].size()-1]-min_val);
            res = max(res,max(temp0,temp1));
            min_val = min(min_val,arrays[i][0]);
            max_val = max(max_val, arrays[i][arrays[i].size()-1]);
            
        }
        return res;
    }
};	
```

## Google 

### [Longest Absolute File Path - LeetCode](https://leetcode.com/problems/longest-absolute-file-path/)

```c++
class Solution {
public:

    int lengthLongestPath(string input) {
        input+='\n';
        unordered_map<int,int> levels;
        levels[-1] = 0;
        int cur_level =0 , cur_length = 0, max_length = 0, is_file = 0;
        
        for(int i =0;i<input.size(); i++){
            switch(input[i]){
                case '\n': 
                    if (is_file) {
                        max_length = max(max_length,cur_length+levels[cur_level-1]);
                        
                    }
                    else{
                        levels[cur_level] = cur_length+levels[cur_level-1]+1; // +1 for slash /
                        
                    }
                    cur_level = 0;
                    cur_length = 0;
                    is_file = 0;
                    break;
                case '\t':
                    
                    cur_level++;
                    break;
                case '.':
                    is_file = 1;
                    cur_length++;
                    cout<<max_length<<endl;
                    break;
                default:
                    cur_length++;
            }
        }
        
        
        return max_length;
    }
};
```

### [Missing Ranges - LeetCode](https://leetcode.com/problems/missing-ranges/)
```c++
class Solution {
public:
    vector<string> findMissingRanges(vector<int>& nums, int lower, int upper) {
        vector<long int> long_nums;
        long int long_lower = lower, long_upper = upper;
        for(auto i : nums) long_nums.push_back(i);
        vector<vector<int>> res;
        vector<string> final_res;
        
        if (nums.size()==0) {
            if(long_upper == long_lower) {
                cout<<long_upper<<endl;
                return {to_string(long_upper)};
            }
            else return {to_string(long_lower)+"->"+to_string(long_upper)};
        }

        
        long_nums.push_back(long_lower-1);
        long_nums.push_back(long_upper+1);

        sort(long_nums.begin(),long_nums.end());
        
        for(int i=0;i < long_nums.size()-1;i++){
            if(long_nums[i+1]-long_nums[i]<=1) continue;
            else {
                string temp;
                long int begin = long_nums[i]+1;
                long int end = long_nums[i+1]-1;
                if(begin==end){
                    temp = to_string(end);

                }else{
                    temp = to_string(begin)+"->"+to_string(end);
                }
                final_res.push_back(temp);
            }
        }

        return final_res;
    }
};
```

### [K Empty Slots - LeetCode](https://leetcode.com/problems/k-empty-slots/submissions/)
```c++
#include<cmath>
class Solution {
public:
//     exceed time limits
//     int kEmptySlots(vector<int>& bulbs, int K) {
//         vector<int> days(bulbs.size(),0);
        
//         for(int i =0; i<days.size();i++){
//             days[bulbs[i]-1]=1;
//             int count=0;
//             int begin = 0;
//             int end = 0;
//             for(int j = 0; j < days.size();){
//                 if(days[j]==1 ) {
//                     int k;
//                     for(k =j+1; k<days.size();k++){
//                         if(days[k]==1) {
//                             count = k-j-1;
//                             if(count == K) return i+1;
                            
//                             break;
//                         }
//                     }
//                     j = k;
                    
//                 }
//                 else j++;
                
                
//             }
            
//         }
//         return -1;
//     }
    
     int kEmptySlots(vector<int>& bulbs, int K) {
         vector<int> days(bulbs.size(),0);
         for(int i =0;i<bulbs.size();i++){
            days[bulbs[i]-1] = i + 1; // bulbs[i]-1 will turn on at day i+1;
         }
         int res = INT_MAX;
         int left=0,right=K+1;
         for(int i = left+1; right<days.size(); i++){
             if(days[i]==days[right]){//find such day
                 res = min(res,max(days[left],days[right]));
                 left = i ;
                 right = left+K+1;
            
             }else if(days[i]<days[left] || days[i]<days[right]){//not what we want
                 left = i;
                 right = left+K+1; 
             }
         }
        
         return res < INT_MAX?res:-1;
    }
};
```


### [Minimum Domino Rotations For Equal Row - LeetCode](https://leetcode.com/problems/minimum-domino-rotations-for-equal-row/submissions/)
```c++
class Solution {
public:
    int check(int val,vector<int> A, vector<int> B){
        int cnt_a = 0;
        int cnt_b = 0;
        for(int i=0; i < A.size(); i++){
           if(A[i]!=val && B[i]!= val) return -1;
            else  if(A[i]!=val) cnt_a ++;
            else if(B[i]!=val) cnt_b++;
            else continue;
        }
        
        return min(cnt_a,cnt_b);
    }
    int minDominoRotations(vector<int>& A, vector<int>& B) {
        if(A.size() == 1 ) return 0;
        
        int temp1 = check(A[0],A,B);
        if(temp1 != -1 || A[0]==B[0]) return temp1;
        else return check(B[0],A,B);// if both A[0] and B[0] fulfill the requirement, then according to the symmetry, check(B[0],A,B) equals to check(A[0],A,B)
        // int temp2 = check(B[0],A,B);
        // if(temp1==-1 && temp2==-1) return -1;
        // if(temp1==-1) return temp2;
        // if(temp2==-1) return temp1;
        // return min(temp1,temp2);
    }
};
```


## Amazon

### [LRU Cache - LeetCode](https://leetcode.com/problems/lru-cache)
use only one map
```c++
class LRUCache {
public:
    list<int> lru; //MRU is at the front; LRU is at the back
    unordered_map<int,int> cache;
    int _capacity;
    LRUCache(int capacity) {
        _capacity = capacity;
    }
    
    int get(int key) {
        if(cache.count(key)) {
            update_lru(key);
            return cache[key];
        }else return -1;
    }
    
    void put(int key, int value) {
        if(cache.size()==_capacity && cache.count(key)==0){// cache is full and miss
            cache.erase(lru.back());
            lru.pop_back();
        }
        cache[key] = value;
        update_lru(key);
        
    }
    void update_lru(int key){
        auto it = find (lru.begin(), lru.end(), key);
        if(it!=lru.end()){
            lru.erase(it);
        }
        lru.push_front(key);
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
```

use only 2 maps for O(1)
```c++
class LRUCache {
public:
    list<int> lru; //MRU is at the front; LRU is at the back
    unordered_map<int,int> cache;
    unordered_map<int,list<int>::iterator> key_iter;
    int _capacity;
    LRUCache(int capacity) {
        _capacity = capacity;
    }
    
    int get(int key) {
        if(cache.count(key)) {
            update_lru(key);
            return cache[key];
        }else return -1;
    }
    
    void put(int key, int value) {
        if(cache.size()==_capacity && cache.count(key)==0){// cache is full and miss
            cache.erase(lru.back());
            
            // for O(1)
            key_iter.erase(lru.back());
            
            lru.pop_back();
        }
        
        update_lru(key);
        cache[key] = value;
        
    }
    void update_lru(int key){
        // auto it = find (lru.begin(), lru.end(), key);
        // if(it!=lru.end()){
        //     lru.erase(it);
        // }
        // lru.push_front(key);
        if(key_iter.count(key)) lru.erase(key_iter[key]);
        lru.push_front(key);
        key_iter[key] = lru.begin();
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
```

### [Best Time to Buy and Sell Stock - LeetCode](https://leetcode.com/problems/best-time-to-buy-and-sell-stock/)
```c++
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int res =  -1;
        int n = prices.size();
        if(n==0||n==1) return 0;
        vector<int> max_price(n,-1);
        max_price[n-1] = prices[n-1];
        for(int i = n-2;i>=0;i--){
            max_price[i] = max(max_price[i+1], prices[i]);
        }
        for(int i =0 ;i< prices.size(); i++){
            res = max(res,max_price[i]-prices[i]);
        }
    
        return res;
    }
    
};
```
a better one:
```c++
int maxProfit(vector<int>& prices) {
        int res =  0;
        int min_price = INT_MAX;
        for(int i =0 ;i< prices.size(); i++){
            if(prices[i]<min_price) min_price = prices[i];
            else if(prices[i]-min_price > res) res = prices[i]-min_price;
        }
    
        return res;
    }
```

## Random
### [Divide Two Integers - LeetCode](https://leetcode.com/problems/divide-two-integers/)
```c++
class Solution {
public:
    int divide(int dividend, int divisor) {
        if(dividend == INT_MIN && divisor == -1) return INT_MAX;
        if(dividend == INT_MIN && divisor == 1) return INT_MIN;
        if(dividend == divisor) return 1;
        int sign = (dividend>>31)^(divisor>>31)?-1:1 ;
        if(dividend>0) dividend=-dividend;
        if(divisor>0) divisor=-divisor;
        if(divisor<dividend) return 0;
        int cnt=0;
        while(dividend-divisor<=0){
            int temp = divisor;
            int temp_cnt = 1;
            int condition = (int)((temp&0xffffffff)<<1); 
            while(condition>dividend && condition<0){
                temp = condition;
                temp_cnt<<=1;
                condition = (int)((condition&0xffffffff)<<1);
            }
            
            dividend -= temp;
            cnt += temp_cnt;
            
        }
        return sign*cnt;
         
    }
};
```






