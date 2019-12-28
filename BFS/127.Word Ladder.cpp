class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        unordered_set<string> dict(wordList.begin(),wordList.end());
        if (dict.find(endWord) == dict.end()) {
            return 0;
        }
        queue<string> todo;
        todo.push(beginWord);
        
        int ladder = 1;
        while(!todo.empty()){
            int n = todo.size();
            for(int i = 0; i< n; i++){
                string word = todo.front();
                todo.pop();
                if(word==endWord){
                    return ladder;
                }
                dict.erase(word);
                for(int j = 0 ; j<word.size();j++){
                    char c = word[j];
                    for(int k = 0; k<26;k++){
                        word[j]='a'+k;
                        if(dict.find(word)!=dict.end()){
                            todo.push(word);
                            dict.erase(word);
                        }
                    }
                    word[j] = c;
                }
            }
            ladder++;
        }
        return 0;
        
    }
};
// class Solution {
// public:
//     int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
//         unordered_set<string> wordDict(wordList.begin(), wordList.end());
//         //wordDict.insert(endWord);
//         queue<string> toVisit;
//         // addNextWords(beginWord, wordDict, toVisit);
//         toVisit.push(beginWord);
//         int dist = 1;
//         while (!toVisit.empty()) {
//             int num = toVisit.size();
//             for (int i = 0; i < num; i++) {
//                 string word = toVisit.front();
//                 toVisit.pop();
//                 if (word == endWord) return dist;
//                 addNextWords(word, wordDict, toVisit);
//             }
//             dist++;
//         }
//         return 0;
//     }
// private:
//     void addNextWords(string word, unordered_set<string>& wordDict, queue<string>& toVisit) {
//         wordDict.erase(word);
//         for (int p = 0; p < (int)word.length(); p++) {
//             char letter = word[p];
//             for (int k = 0; k < 26; k++) { 
//                 word[p] = 'a' + k;
//                 if (wordDict.find(word) != wordDict.end()) {
//                     toVisit.push(word);
//                     wordDict.erase(word);
//                 }
//             }
//             word[p] = letter;
//         } 
//     } 
// };