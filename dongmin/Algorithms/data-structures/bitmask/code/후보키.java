import java.util.*;

class Solution {
    String[][] relation;
    int R,C;
    
    int[] possible = new int[1024];
    
    int answer;
    int[] record;
    int record2Key(int level) { 
        int key = 0;
        for(int i = 0 ; i <level; i++) {
            key |= ( 1 << record[i]);
        }
        return key;
    }
    boolean isMinimum(int level, int key) {
        for(int i = 0; i < this.answer; i++) {
            if((possible[i] & key) != possible[i]) continue;
            return false;
        }
        return true;
    }
    
    boolean valid(int level) {
        HashMap<String, Boolean> hash = new HashMap();
        for(int i = 0; i < R; i++) {
            String key = "/";
            for(int j = 0 ; j <level; j++) {
                key += relation[i][record[j]] +"/";
            }
            if(hash.containsKey(key)) {
                return false;
            }
            hash.put(key, true);
        }
        return true;
    }
    void recursive(int level, int lastIdx, int goal) {
        if(level == goal) {
            int key = record2Key(level);
            if(!isMinimum(level, key)) return;
            if(!valid(level)) return;
            possible[this.answer] = key;
            this.answer ++;
            return;
        }
        for(int i = lastIdx; i < C; i++) {
            record[level] = i;
            recursive(level + 1, i + 1, goal);
            record[level] = 0;
        }
    }
    void init(String[][] relation){
        this.R = relation.length;
        this.C = relation[0].length;
        
        this.relation = new String[R][C];
        for(int i = 0; i < R; i++){
            for(int j = 0; j < C; j++) {
                this.relation[i][j] = relation[i][j];
            }
        }
        this.record = new int[C];
        for(int i = 0; i < C; i++) {
            this.record[i] = 0;
        }
    }
    public int solution(String[][] relation) {
        this.answer = 0;
        init(relation);
        for(int i = 1; i <= C; i++) {
            recursive(0, 0, i);
        }
        return this.answer;
    }
}