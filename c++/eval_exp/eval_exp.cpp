#include <iostream>
#include <string>
#include <ctype.h>
#include <stack>
#include <vector>

bool isDigit(char c) {
	return isdigit(c) || c == '.';
}

bool isOperator(char c) {
	return c=='(' || c=='+' || c=='-' || c=='/' || c=='*' || c==')';
}

int precedence(char c) {
	switch (c) {
	case '+':
	case '-':
		return 0;
	case '*':
	case '/':
		return 1;
	case '(':
		return -1;
	}
	std::cout << "Unsupported operation (precedence): " << c << "\n";
	return -1;
}
double eval(double v1, double v2, char op) {
	switch (op) {
	case '+':
		return v2 + v1;
	case '-':
		return v2 - v1;
	case '*':
		return v2 * v1;
	case '/':
		return v2 / v1;
	}
	std::cout << "Unsupported operation (eval): " << op << "\n";
	return -1;
}

void adjust(std::stack<char> &opstack, std::stack<double> &vstack) {
	char op = opstack.top();
	opstack.pop();
	double v1 = vstack.top();
	vstack.pop();
	double v2 = vstack.top();
	vstack.pop();
	vstack.push(eval(v1, v2, op));
}

int main()
{
	//std::string expr = "1.03+1.12/(4.01-3/2)-1.5*(0.01+2/100.0+4)-5";
	//std::string expr = "1+2+3";
	//std::string expr = "1+2*3+4-5/6";
	std::vector<std::string> exprs = {"1+2+(3/4)", "1.03+1.12/(4.01-3/2)-1.5*(0.01+2/100.0+4)-5", "1+2+3", "1+2*3+4-5/6"};
	std::string tmp;
	std::stack<char> opstack;
	std::stack<double> vstack;
	for (auto expr: exprs) {
		for (char c : expr) {
			if (isDigit(c)) {
				tmp.push_back(c);
			}
			else if (isOperator(c)) {
				if (!tmp.empty()) {
					vstack.push(std::stod(tmp));
					tmp.clear();
				}
				if (c == '(') {
					opstack.push(c);
				}
				else if (c == ')') {
					while (opstack.top() != '(') {
						adjust(opstack, vstack);
					}
					opstack.pop();
				}
				else if (!opstack.empty()) {
					if (precedence(c) < precedence(opstack.top())) {
						adjust(opstack, vstack);
					}
					opstack.push(c);
				}
				else {
					opstack.push(c);
				}
			}
		}
		if (!tmp.empty()) {
			vstack.push(std::stod(tmp));
		}
		while (!opstack.empty()) {
			adjust(opstack, vstack);
		}

		while (!vstack.empty()) {
			std::cout << expr << " = " << vstack.top() << "\n";
			vstack.pop();
		}
		while (!opstack.empty()) {
			opstack.pop();
		}
		tmp.clear();
	}
	return 0;
}
