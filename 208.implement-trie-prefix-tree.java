import javax.sound.sampled.BooleanControl;

/*
 * @lc app=leetcode id=208 lang=java
 *
 * [208] Implement Trie (Prefix Tree)
 * https://leetcode.com/problems/implement-trie-prefix-tree/description/
 *
 * algorithms
 * Medium (56.57%)
 * Likes:    6165
 * Dislikes: 84
 * Total Accepted:    520.1K
 * Total Submissions: 918.8K
 * Testcase Example:  '["Trie","insert","search","search","startsWith","insert","search"]\n' +
  '[[],["apple"],["apple"],["app"],["app"],["app"],["app"]]'
 */

// @lc code=start

class TrieNode {
    TrieNode[] children;
    boolean isLeaf;
    public TrieNode() {
        children = new TrieNode[26];
        isLeaf = false;
    }
    
    public boolean containsKey(char ch) {
        return children[ch - 'a']  != null;
    }

    public TrieNode get (char ch) {
        return children[ch - 'a'];
    }

    public void put(char ch, TrieNode node) {
        children[ch - 'a'] = node;
    }
    
    public boolean isLeaf() {
        return isLeaf;
    }

    public void setLeaf(boolean val){
        isLeaf = val;
    }
}
class Trie {
    TrieNode root;
    public Trie () {
        root = new TrieNode();
    }
    public void insert(String word) {
        TrieNode cur = root;
        for (char ch : word.toCharArray()) {
            if (!cur.containsKey(ch)) {
                cur.put(ch, new TrieNode());
            }
            cur = cur.get(ch);
        }
        cur.setLeaf(true);
    }
    public TrieNode _search(String prefix) {
        TrieNode cur = root;
        for (char ch : prefix.toCharArray()) {
            if (cur.containsKey(ch)) {
                cur = cur.get(ch);
            } else {
                return null;
            }
        }
        return cur;
    }
    public boolean search(String word) {
        TrieNode res = _search(word);
        return res != null && res.isLeaf();

    }
    
    public boolean startsWith(String prefix) {
        TrieNode res = _search(prefix);
        return res != null;
        
    }
}

/**
 * Your Trie object will be instantiated and called as such:
 * Trie obj = new Trie();
 * obj.insert(word);
 * boolean param_2 = obj.search(word);
 * boolean param_3 = obj.startsWith(prefix);
 */
// @lc code=end

