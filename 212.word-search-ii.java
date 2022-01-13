import java.awt.List;
import java.lang.Runtime.Version;
import java.util.ArrayList;
import java.util.HashSet;

/*
 * @lc app=leetcode id=212 lang=java
 *
 * [212] Word Search II
 * https://leetcode.com/problems/word-search-ii/description/
 *
 * algorithms
 * Hard (38.49%)
 * Likes:    5284
 * Dislikes: 182
 * Total Accepted:    392.5K
 * Total Submissions: 1M
 * Testcase Example:  '[["o","a","a","n"],["e","t","a","e"],["i","h","k","r"],["i","f","l","v"]]\n' +
  '["oath","pea","eat","rain"]'
 */

// @lc code=start
class Solution {

    public boolean check(char[][] board, int m, int n, String word, int index, int x, int y, int direction, int[] trace) {
        if (board[x][y] != word.charAt(index) ) {
            return false;
        }
        if (index == word.length() - 1) return true;
        trace[x*n+y] = 1;
        if (x>=1 && direction != 1 && trace[(x-1)*n+y] != 1) {
            if (check(board, m, n, word, index+1, x-1, y, 2, trace)) return true;
        }
        if (x< m-1 && direction != 2 && trace[(x+1)*n+y] != 1) {
            if (check(board, m, n, word, index+1, x+1, y, 1, trace)) return true;
        }
        if (y >= 1 && direction != 3 && trace[x*n+y-1] != 1) {
            if (check(board, m, n, word, index+1, x, y-1, 4, trace)) return true;
        }
        if (y < n-1 && direction != 4 && trace[x*n+y+1] != 1) {
            if (check(board, m, n, word, index+1, x, y+1, 3, trace)) return true;
        }
        trace[x*n+y] = 0;
        return false;

    }
    public List<String> findWords(char[][] board, String[] words) {
        int m = board.length;
        int n = board[0].length;
        List<String> res = new ArrayList<>();
        for (String word : words) {
            int f = 0;
            int[] trace = new int[m*n];
            for (int i = 0; i < m; i++) {
                for (int j = 0; j < n; j++) {
                    if (check(board, m, n, word, 0, i, j, 0, trace)) {
                        res.add(word);
                        f = 1;
                        break;
                    }
                }
                if (f==1) break;
            }
        }
        return res;
        
    }
}
// @lc code=end

