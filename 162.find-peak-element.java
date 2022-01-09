/*
 * @lc app=leetcode id=162 lang=java
 *
 * [162] Find Peak Element
 */

// @lc code=start
class Solution {
    public int findPeakElement(int[] nums) {
        int low = 0, hi = nums.length - 1;
        while (low < hi) {
            int mid = low + (hi - low) / 2;
            if( nums[mid] < nums[mid+1]) {
                low = mid + 1;
            } else {
                hi = mid;
            }
        }
        return low;
    }
}
// @lc code=end

