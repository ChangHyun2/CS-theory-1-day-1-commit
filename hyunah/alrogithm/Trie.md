# [Algorithm] 트라이(Trie)

## 개념

### 트라이(Trie)

-   트라이란 문자열을 저장하고 효율적으로 탐색하기 위한 트리 형태의 자료구조이다.
-   아래와 같이 트리의 루트에서부터 자식들을 따라가면 문자열이 생성되는데 해당 문자열은 트라이에 저장되어있다고 한다. 저장된 단어는 끝을 표시하는 변수를 추가해서 저장된 단어의 끝을 구분할 수 있다.
-   문자열 탐색을 할때 빠르게 할 수 있고 효율적이다.
-   각 노드에서 자식들에 대한 포인터들을 배열로 저장하고 있어서 저장 공간의 크기가 크다는 단점이 있따.
-   검색어 자동완성, 사전에서 찾기 그리고 문자열 검사 같은 부분에서 사용할 수 있다.

## 시간 복잡도

-   제일 긴 문자열의 길이를 L, 총 문자열들의 수를 M이라고 하자.
-   트라이 생성: O(M*L). 문자열 개수 * 제일 긴 문자열의 길이만큼 시간이 걸린다.
-   트라이 탐색: O(L). 최대 L만큼 탐색하기 때문에 O(L)이다.

## 구현

-   struct로 트라이를 선언해준다.
-   is_terminal : 단어의 끝임을 표시하는 변수
-   void insert(const char\* key) : 새로운 문자열을 트라이에 추가하는 함수
-   Trie* find(const char* key) : key에 해당하는 문자열을 접두어로 가지고 있는지 확인하고 가지고 있다면 해당 접두어가 끝나는 부분의 위치를 반환
-   bool string_exist(const char\* key) : key에 해당하는 문자열이 포함되어 있는지 확인하는 함수. 해당 key의 문자열이 있다면 true를 반환하고 없으면 false를 반환.

<pre><code>
struct Trie {
	//to check finish point
	bool is_terminal;
    //for alphabet a~z
    Trie* children[26];
    //constructor, initialize
    Trie() : is_terminal(false){
    	memset(children, 0, sizeof(children));
    }
    //destuctor, delete
    ~Trie(){
    	for(int i=0;i < 26; i++){
        	if(children[i]) delete children[i];
        }
    
    void insert(const char* key){
    	//check end of string
    	if(*key == '\0') is_terminal = true;
        else{
        	int curr = *key - 'A';
            //if there's no string, add
            if(children[curr] == NULL) children[curr] = new Trie();
            //insert next string
            children[curr]->insert(key + 1);
        }
    }
    
    Trie* find(const char* key){
    	//return end of string
    	if(*key == '\0') return this;
        int curr = *key - 'A';
        //no string exists
        if(children[curr] == NULL) return NULL;
        //search next string
        return children[curr]->find(key + 1);
    }
    
    bool string_exist(const char* key){
    	//string exists so return true
    	if(*key == 0 && is_terminal) return true;
        int curr = *key - 'A';
        //no string return false
        if(children[curr] == 0) return false;
        return children[curr]->string_exist(key + 1);
    }
};
</code></pre>
