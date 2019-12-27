/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    //method1
    // bool checkCurLevel(deque<TreeNode*> q){
    //     int n = q.size();
    //     if(n < 2) return true;
    //     if(n%2!=0) return false;
    //     while(!q.empty()){
    //         TreeNode* f = q.front();
    //         TreeNode* b = q.back();
    //         if(f&&!b) return false;
    //         else if(!f&&b) return false;
    //         else if(!f&&!b) ;
    //         else{
    //             if(f->val!=b->val) return false;
    //         }
    //         q.pop_front();
    //         q.pop_back();
            
    //     }
    //     return true;
    // }
    // bool isSymmetric(TreeNode* root) {
        
    //     deque<TreeNode*> q;
    //     q.push_back(root);
    //     while(!q.empty()){
    //         if(!checkCurLevel(q)) return false;
    //         deque<TreeNode*> new_q;
    //         while(!q.empty()){
    //             TreeNode* tmp = q.front();
    //             q.pop_front();
    //             if(tmp){
    //                 new_q.push_back(tmp->left);
    //                 new_q.push_back(tmp->right);
    //             }
    //         }
    //         q = new_q;
            
    //     }
    //     return true;
    // }
    //method2
    bool isSymmetric(TreeNode* root) {
        
        queue<TreeNode*> q;
        q.push(root);
        q.push(root);
        while(!q.empty()){
            TreeNode* t1 = q.front();
            q.pop();
            TreeNode* t2 = q.front();
            q.pop();
            if(!t1&&!t2) continue;
            if(!t1 || !t2) return false;
            if(t1->val!=t2->val) return false;
            q.push(t1->left);
            q.push(t2->right);
            q.push(t1->right);
            q.push(t2->left);
        }
        return true;
    }
};