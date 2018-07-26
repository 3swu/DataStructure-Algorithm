/*
 * author: wulei
 *
 * this is a program to evalute a math expression,include:
 * -->parse a expression to a infix
 * -->convert the infix to a suffix
 * -->evalute a infix
 * -->evalute a suffix
 *
 */
#include <iostream>
#include <vector>
#include <stack>
#include <string>
#include <cstring>
#include <sstream>

using namespace std;

vector<string> parseInfix(char* str){
    vector<string> tokens;
    int len = strlen(str);
    char* p = (char*)malloc((len + 1) * sizeof(char));
    for(int i = 0, j = 0; i < len;){
        if(str[i] == ' '){
            i++;
            continue;
        }
        p[j++] = str[i++];
        p[j + 1] = '\0';
    }

    for(int i = 0; i < strlen(p); i++){
        char temp[2];
        string token;

        switch(p[i]){
            case '+':
            case '*':
            case '/':
            case '(':
            case ')':
                temp[0] = p[i];
                temp[1] = '\0';
                token = temp;
                tokens.push_back(token);
                break;
            case '-':
                if(p[i - 1] == ')' || isdigit(p[i - 1])){
                    temp[0] = p[i];
                    temp[1] = '\0';
                    token = temp;
                    tokens.push_back(token);
                }
                else{
                    int j = i + 1;
                    for(; isdigit(p[j]); j++);
                    char* t = (char*) malloc ((j - i + 1) * sizeof(char));
                    for(int k = i; k != j; k++){
                        t[k-i] = p[k];
                    }
                    t[j - i] = '\0';
                    token = t;
                    free(t);
                    tokens.push_back(token);
                    i = j - 1;
                }
                break;
            default:
                int j = i + 1;
                for(; isdigit(p[j]); j++);
                char* t = (char*) malloc ((j - i + 1) * sizeof(char));
                for(int k = i; k != j; k++){
                    t[k-i] = p[k];
                }
                t[j - i] = '\0';
                token = t;
                free(t);
                tokens.push_back(token);
                i = j - 1;
        }
    }
    return tokens;
}

void calculate(stack<string> &opStack, stack<int> &numStack){
    int a, b;
    b = numStack.top();
    numStack.pop();
    a = numStack.top();
    numStack.pop();
    string op;
    op = opStack.top();
    opStack.pop();
    if(op == "+")
        numStack.push(a + b);
    else if(op == "-")
        numStack.push(a - b);
    else if(op == "*")
        numStack.push(a * b);
    else if(op == "/")
        numStack.push(a / b);
}

int evalInfix(vector<string> tokens){
    stack<string> opStack;
    opStack.push("#");
    stack<int> numStack;
    for(int i = 0; i < tokens.size(); i++){
        string token = tokens.at(i);
        if(isdigit(token[0]) || (token[0] == '-' && isdigit(token[1]))){
            istringstream is(token);
            int a;
            is >> a;
            numStack.push(a);
        }
        else if(token == "(")
            opStack.push(token);
        else if(token == "+" || token == "-"){
            if(opStack.top() == "#" || opStack.top() == "(")
                opStack.push(token);
            else{
                while(opStack.top() == "+" || opStack.top() == "-" || opStack.top() == "*" || opStack.top() == "/"){
                    calculate(opStack, numStack);
                }
                opStack.push(token);
            }
        }
        else if(token == "*" || token == "/"){
            if(opStack.top() == "(" || opStack.top() == "#")
                opStack.push(token);
            else if(opStack.top() == "+" || opStack.top() == "-")
                opStack.push(token);
            else if(opStack.top() == "*" || opStack.top() == "/"){
                while(opStack.top() == "*" || opStack.top() == "/"){
                    calculate(opStack, numStack);
                }
                opStack.push(token);
            }
        }
        else if(token == ")"){
            while(opStack.top() != "("){
                calculate(opStack, numStack);
            }
            opStack.pop();
        }
    }
    while(opStack.top() != "#")
        calculate(opStack, numStack);
    if(numStack.size() == 1)
        return numStack.top();
}

vector<string> parseSuffix(vector<string> infix){
    stack<string> opStack;
    vector<string> suffix;
    opStack.push("#");
    for(int i = 0; i < infix.size(); i++){
        string token = infix.at(i);
        if(isdigit(token[0]) || (token[0] == '-' && isdigit(token[1]))){
            suffix.push_back(token);
        }
        else if(token == "(")
            opStack.push(token);
        else if(token == "+" || token == "-" || token == "*" || token == "/"){
            if(opStack.top() == "#")
                opStack.push(token);
            else if((token == "*" || token == "/") && (opStack.top() == "+" || opStack.top() == "-"))
                opStack.push(token);
            else{
                if(opStack.top() != "(" && opStack.top() != "#"){
                    suffix.push_back(opStack.top());
                    opStack.pop();
                }
                opStack.push(token);
            }
        }
        else if(token == ")"){
            while(opStack.top() != "("){
                suffix.push_back(opStack.top());
                opStack.pop();
            }
            opStack.pop();
        }
    }
    while(opStack.top() != "#"){
        suffix.push_back(opStack.top());
        opStack.pop();
    }
    return suffix;
}

int evalSuffix(vector<string> suffix){
    stack<int> numStack;
    for(int i = 0; i < suffix.size(); i++){
        string token = suffix.at(i);
        if(isdigit(token[0]) || (token[0] == '-' && isdigit(token[1]))){
            istringstream is(token);
            int a;
            is >> a;
            numStack.push(a);
        }
        else{
            int a, b;
            b = numStack.top();
            numStack.pop();
            a = numStack.top();
            numStack.pop();
            if(token == "+")
                numStack.push(a + b);
            else if(token == "-")
                numStack.push(a - b);
            else if(token == "*")
                numStack.push(a * b);
            else if(token == "/")
                numStack.push(a / b);
        }
    }
    if(numStack.size() == 1){
        return numStack.top();
    }
}


int main(){
    //test infix parse and suffix parse
    char* test = "(-8)+56/(28)+(-6-1)";
    vector<string> infix = parseInfix(test);
    vector<string> suffix = parseSuffix(infix);
    for(int i = 0; i < infix.size(); i++)
        cout << infix.at(i) << " ";
    cout << endl;
    for(int i = 0; i < suffix.size(); i++)
        cout << suffix.at(i) << " ";
    //test infix evalute and suffix evalute
    cout << endl << evalInfix(infix);
    cout << endl << evalSuffix(suffix);
}