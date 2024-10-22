#include<iostream>
#include<string>
#include<cmath>
using namespace std;
int precedence(char a);
void postfix_exp(const string exp, string& postfix, string checker);
void prefix_exp(const string exp, string& prefix);
void rev_invert(string exp, string& rev_exp);
void reverse(string rev, string& result);
template<class type>
class Stack
{
private:
    int top;
    type array[100];
public:
    Stack() { top = -1; }
    ~Stack() {};
    bool isEmpty() {
        if (top < 0) {
            // cout << "Stack is Empty Nothing to POP" << endl;
            return true;
        }
        else return false;
    }
    bool isFull() {
        if (top >= 99) {
            cout << "Stack is FUll can't Push" << endl;
            return true;
        }
        else return false;
    }
    void Push(type item) {
        if (isFull() == false) {
            top++;
            array[top] = item;
        }
    }
    char pop() {
        if (isEmpty() == false) {
            char character = array[top];
            top--;
            return character;

        }
    }
};

int main()
{
    string postfix, pre_exp, post_exp, pre_eva, post_eva, prefix;
    int choice = 0, result;
    char option;
    do {
        cout << "1.convert to postfix.\n2.convert to prefix." << endl;
        cout << "Enter Your Choice = ";
        cin >> choice;
        if (choice == 1)
        {
            cout << "Enter Expression = ";
            cin.ignore();
            getline(cin, post_exp);
            postfix_exp(post_exp, postfix, "post");
            for (int i = 0; i < postfix.length(); i++)
            {
                cout << postfix[i];
            }
            cout << endl;
        }
        else if (choice == 2)
        {
            cout << "Enter Expression = ";
            cin.ignore();
            getline(cin, pre_exp);
            prefix_exp(pre_exp, prefix);
            for (int i = 0; i < prefix.length(); i++)
            {
                cout << prefix[i];
            }
        }
        else
        {
            cout << "Invalid input! " << endl;
        }
        cout << "\nDo you want to use it again = ";
        cin >> option;
    } while (option == 'Y' || option == 'y');
    return 0;
}
void postfix_exp(const string exp, string& postfix, string checker) {
    Stack<char>stack;
    for (int i = 0; i < exp.length(); i++)
    {
        if (exp[i] == '+' || exp[i] == '-' || exp[i] == '*' || exp[i] == '/' || exp[i] == '^')
        {
            char preCheck = NULL;
            while (preCheck != '(')
            {
                if (stack.isEmpty() == true)
                {
                    stack.Push(exp[i]);
                    break;
                }
                preCheck = stack.pop();
                /* if (stack.isEmpty() == true && preCheck !='(')
                 {
                     stack.Push(preCheck);
                     break;
                 }*/
                if (preCheck == exp[i])
                {
                    stack.Push(preCheck);
                    break;
                }
                if (checker == "post")
                {
                    if ((precedence(preCheck) >= precedence(exp[i])) && exp[i] != '(')
                    {
                        postfix += preCheck;
                        stack.Push(exp[i]);
                    }
                    else {
                        stack.Push(preCheck);
                        stack.Push(exp[i]);
                    }
                }
                else if (checker == "pre")
                {
                    if ((precedence(preCheck) > precedence(exp[i])) && exp[i] != '(')
                    {
                        postfix += preCheck;
                        stack.Push(exp[i]);
                    }
                    else {
                        stack.Push(preCheck);
                        stack.Push(exp[i]);
                    }
                }
                else cout << "Give valid parameters";
            }
        }
        else if (exp[i] == '(' || exp[i] == ')')
        {
            if (exp[i] == ')')
            {
                char postfixChar = NULL;
                while (postfixChar != '(')
                {
                    postfixChar = stack.pop();
                    if (postfixChar == '(')
                        continue;
                    postfix += postfixChar;
                }
            }
            else
            {
                stack.Push(exp[i]);
            }
        }
        else if (exp[i] == ' ')
        {
            continue;
        }
        else
        {
            postfix += exp[i];
        }
    }
    while (stack.isEmpty() == false)
    {
        postfix += stack.pop();
    }
    stack.~Stack();
}
void prefix_exp(const string exp, string& prefix)
{
    string reverse_exp, prefix_rev;
    rev_invert(exp, reverse_exp);
    postfix_exp(reverse_exp, prefix_rev, "pre");
    reverse(prefix_rev, prefix);
}
void reverse(string rev, string& result)
{
    Stack<char>stack;
    for (int i = 0; i < rev.length(); i++)
    {
        stack.Push(rev[i]);
    }
    for (int i = 0; i < rev.length(); i++)
    {
        result += stack.pop();
    }
}
void rev_invert(string exp, string& rev_exp)
{
    Stack<char>stack;
    int count = 0;
    for (int i = 0; i < exp.length(); i++)
    {
        if (exp[i] == ' ')
            continue;
        stack.Push(exp[i]);
        count++;
    }
    for (int i = 0; i < count; i++)
    {
        char stackpop = NULL;
        stackpop = stack.pop();
        if (stackpop == '(')
        {
            rev_exp += ')';
        }
        else if (stackpop == ')')
        {
            rev_exp += '(';
        }
        else
        {
            rev_exp += stackpop;
        }
    }
}
int precedence(char a)
{
    if (a == '^')
    {
        return 3;
    }
    else if (a == '/' || a == '*')
    {
        return 2;
    }
    else if (a == '+' || a == '-')
    {
        return 1;
    }
    else
    {
        return 0;
    }
}