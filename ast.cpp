#include <iostream>
#include <cctype>

#define NUMBER "NUMBER"
#define ADDITION "ADDITION"
#define DIVISION  "DIVISION"
#define MULTIPLICATION "MULTIPLICATION"
#define SUBSTRACTION "SUBSCTRACTION"
#define MODULUS "MODULUS"

using namespace std;

class String {
	public:
	string value;
	int len;
	
	String(){
		this->value = "";
		this->len = 0;
	}
	
	String(string value){
		this->value = value;
		this->len = value.length();
	}
	
	string sub_string(int start , int end){
		string sub = "";
		for(int i = start ; i < end ; i++){
			sub  = sub + value[i];
		}
		
		return sub;
	}
	
	char at(int i){
		return value[i];
	}
};


template <typename T>
class LinkedList {
	T *head;
	public: 
	LinkedList(){
		this->head = NULL;
	}
	
	
	bool is_empty() {
		return head == NULL;
	}
	
	void add_node(T *newNode){
		if(is_empty()){
			head = newNode;
		} else{
			T *tail = head;
			while(tail->next){
				tail = tail->next;
			}
			tail->next = newNode;
			newNode->last = tail;
		}
	}
	
	void print_nodes(){
		cout <<  endl;
		if(is_empty()) { 
			cout << "Linked list is empty" << endl;
			return;
		}
		
		T *temp = this->head;
		while(temp != NULL){
			temp->print();
			temp = temp->next;
		}
	}
	
};


class Token{
	public:
	Token *last;
	Token *next;
	char lexeme;
	float value;
	string token;
	
	Token(char lexeme, int value, string token){
		this->last = NULL;
		this->next = NULL;
		this->lexeme =lexeme;
		this->value = value;
		this->token = token;
	}
	
	void delete_from_list(){
		Token *temp = this;
		if(temp->next == NULL){
			free(this);
			return;
		}
		temp->last->next = temp->next;
		temp->next->last = temp->last;
		free(temp);
	}
	
	void print(){
		cout <<"Lexeme: " << this->lexeme << "\tValue: " << this->value << "\tToken: " << this->token << endl;
	}
};	

namespace logger {
	void error(string message, int pos){
		cout << "Error on line 1 character " << pos << " :: "  << "\"" << message << "\"" << endl; 
	}
	
	void error(string message) {
		cout << "Error " << "\"" << message << "\"" << endl; 
	}
}


class Scanner{
	public:
	int start = 0;
	int current = 0;
	int end;
	LinkedList<Token> *tokens = new LinkedList<Token>();
	String source;
	
	Scanner(string source){
		cout << "New scanner: " <<  source << endl;
		this->source = String(source);
		this->end  = this->source.len;
	}
	
	// returns current character and increases the current;
	char advance(){
		current ++;
		cout << current << ":" << source.at(current -1) << "\t";
		return source.at(current -1);
	}
	
	// returns current character;
	char peek(){
		if(current == end)  return '\0';
		return source.at(current);
	}
	
	char peek_next(){
		if(current+1 == end) return '\0';
		return source.at(current +1);
	}
	
	void add_token(string type){
		tokens->add_node(new Token(source.at(current-1), 0, type)); 
	}
	
	void add_token(string type, int value){
		Token *token = new Token(source.at(current-1),value, type);
		tokens->add_node(token);
	}
	
	
	void number(){
		// checks if the 1st character is not the end of source  and is also a digit
		while(current != end && isdigit(peek())) advance();
		
		// verifies if the next character is . and is also followed by a digit to make a valid floating number
		if(peek() == '.' && isdigit(peek_next())) advance();
		// keep moving the current ( pointer) unti we reach the end of the number
		while(isdigit(peek())) advance();
		add_token(NUMBER, stoi(String(source).sub_string(start, current)));
		
	}
	
	void scan_tokens(){
			while(current != end){
			start = current;
			char c = advance();
			
			switch(c){
				case ' ': 
					break;
				case '-':
					this->add_token(SUBSTRACTION);
					break;
				case '/':
					this->add_token(DIVISION);
					break;
				case '+':
					this->add_token(ADDITION);
					break;
				case '*': 
					this->add_token(MULTIPLICATION);
					break;
				case '%':
					this->add_token(MODULUS);
					break;
				default:
					if(isdigit(c)){
						this->number();
					} else{
						logger::error("Unexpected character ", current);
					}
		
			}
		}
//		Token *token = new Token('\o',0, EOF);
//		tokens->add_node(token)	;
	}
};


//class BinaryTree {
//	public:
//		
//	BinaryTree()
//};


//float walk_the_tree
// calculate the value of 1+2*3+4;
int main(){
	Scanner *scanner = new Scanner("22.4+ 2*3-5");
	scanner->scan_tokens();
	scanner->tokens->print_nodes();
}
