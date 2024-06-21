#include <iostream>
using namespace std;

enum TokenType {
	NUMBER,
	ADDITION, 
	SUBSTRACTION,
	DIVISION, 
	MULTIPLICATION
};


class Token{
	public:
	string lexeme;
	int value;
	TokenType token;
	
	Token(string lexeme, int value, TokenType token){
		this->lexeme =lexeme;
		this->value = value;
		this->token = token;
	}
};	

namespace logger {
	void error(string message, int char){
		cout << "Error on line 1: " << char << "\"" << message << "\"" << endl; 
	}
	
	void error(string message) {
		cout << "Error" << "\"" << message << "\"" << endl; 
	}
}

// calculate the value of 1+2*3+4;
class Scanner(){
	public:
	int start = 0;
	int current = 0;
	int end;
	string source;
	Scanner(string source){
		this->source = source;
		this->end  = sizeof(source) / sizeof(sizeof[0]);
	}
	
	char peek(){
		current ++;
		return source[current -1];
	}
	
	Token[] scan_tokens(){
		while(current != end){
			cout << peek() << "\t";
		}	
	}
	
}

int main(){
	Scanner scanner = new Scanner("1+2*3-5");
	scanner->sca
}
