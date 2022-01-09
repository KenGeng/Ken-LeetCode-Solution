import java.util.HashMap;
import java.util.Map;

/*
 * @lc app=leetcode id=128 lang=java
 *
 * [128] Longest Consecutive Sequence
 */

// @lc code=start
// [4,0,-4,-2,2,5,-8,-1,7,6,-3]

class Solution {
    public int longestConsecutive(int[] nums) {
        Map<Integer, Integer> map = new HashMap<>();
        int res = 0;
        for (int i : nums) {
            if (map.containsKey(i) ) continue;
            // the newly addded num only interact with its 2 neighbors
            int tmp = map.getOrDefault(i-1, 0) + map.getOrDefault(i+1, 0) + 1;
            res = tmp > res ? tmp : res;
            // always make the two end have correct length
            map.put(i, tmp);
            map.put(i - map.getOrDefault(i-1, 0), tmp);
            map.put(i + map.getOrDefault(i+1, 0), tmp);
            
        }
        return res;
    }
}


// class Solution {
//     public int longestConsecutive(int[] nums) {
//         int res = 0;
//         Set<Integer> set = new HashSet<>();
//         for (int i : nums) {
//             set.add(i);
//         }
//         for (int i : set) {
//             if (set.contains(i-1)) continue;
//             int cur = i;
//             int tmp = 1;
//             while (set.contains(++cur)) {
//                 tmp += 1;
//             }
//             res = res < tmp ? tmp : res;
            
//         }
//         return res;
//     }
// }
// @lc code=end

