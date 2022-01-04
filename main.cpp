#include <iostream>
#include <string>
#include <stack>
#include <cmath>

void ErrorExpr() {
    std::cout << "Error! Ex";
}

int PrioritypASS(char PMU) {
    if (PMU == '+') return 1;
    if (PMU == '*' || PMU == '/') return 2;
    if (PMU == '^') return 3;
    if (PMU == '-') return 4;
    if (PMU == 'c' || PMU == 's') return 5;
    return 0;
}

bool count(std::stack<double> &num, std::stack<char> &operations) {
    double first;
    double second;
    second = num.top();
    num.pop();
    switch (operations.top()) {
        case '+':
            if (!num.empty()) {
                first = num.top();
                num.pop();
            } else {
                first = 0;
            }
            num.push(first + second);
            break;
        case '*':
            first = num.top();
            num.pop();
            num.push(first * second);
            break;
        case '-':
            num.push(second * -1);
            break;
        case '/':
            first = num.top();
            if (first == 0) {
                std::cerr << "Error! Divide by 0";
                return false;
            }
            num.pop();
            num.push(first / second);
            break;
        case '^':
            first = num.top();
            if (first == 0 && second == 0) {
                std::cerr << "Error! Raise 0 to the power of 0";
                return false;
            }
            num.pop();
            num.push(pow(first, second));
            break;
        case 'c':
            num.push(cos(second));
            break;
        case 's':
            num.push(sin(second));
            break;
        case 't':
            if (cos(second) == 0) {
                std::cerr << "Error! In tg cos can't be = 0";
                return false;
            }
            num.push((sin(second) / cos(second)));
            break;
        case 'g':
            if (sin(second) == 0) {
                std::cerr << "Error! In ctg sin can't be = 0";
                return false;
            }
            num.push(cos(second) / sin(second));
            break;
        case 'e':
            num.push(exp(second));
            break;
        default:
            std::cerr << "Error! Operation";
            return false;
    }
    operations.pop();
    return true;
}


int main() {
    std::stack<char> operations;
    std::stack<double> nums;
    char current;
    double number;
    std::cout << "Enter example:" << std::endl;
    std::string main;
    getline(std::cin, main);
    double x;
    for (size_t i = 0; i < main.size(); i++) {
        if (main[i] == 'x' && main[i + 1] != 'p') {
            std::cout << "Enter x: ";
            std::cin >> x;
            break;
        }
    }
    while (!main.empty()) {
        current = main[0];
        if (main[0] == 'x' && main[1] != 'p') {
            nums.push({x});
            main.erase(main.begin());
            continue;
        } else if (current >= '0' && current <= '9') {
            number = stod(main);
            nums.push(number);
            while (main[0] >= '0' && main[0] <= '9' || main[0] == '.') {
                main.erase(main.begin());
            }
            continue;
        } else if (main.substr(0, 3) == "cos") {
            if (main[3] == '*' || main[3] == '^' || main[3] == '-' || main[3] == '+' || main[3] == '/') {
                ErrorExpr();
                return -1;
            }
            operations.push('c');
            main.erase(main.begin(), main.begin() + 3);
            continue;
        } else if (main.substr(0, 3) == "sin") {
            if (main[3] == '*' || main[3] == '^' || main[3] == '+' || main[3] == '/') {
                ErrorExpr();
                return -1;
            }
            operations.push('s');
            main.erase(main.begin(), main.begin() + 3);
            continue;
        } else if (main.substr(0, 2) == "tg") {
            if (main[2] == '*' || main[2] == '^' || main[2] == '-' || main[2] == '+' || main[2] == '/') {
                ErrorExpr();
                return -1;
            }
            operations.push('t');
            main.erase(main.begin(), main.begin() + 2);
            continue;
        } else if (main.substr(0, 3) == "ctg") {
            if (main[3] == '*' || main[3] == '^' || main[3] == '+' || main[3] == '/') {
                ErrorExpr();
                return -1;
            }
            operations.push('g');
            main.erase(main.begin(), main.begin() + 3);
            continue;
        } else if (main.substr(0, 3) == "exp") {
            if (main[3] == '*' || main[3] == '^' || main[3] == '-' || main[3] == '+' || main[3] == '/') {
                ErrorExpr();
                return -1;
            }
            operations.push('e');
            main.erase(main.begin(), main.begin() + 3);
            continue;
        } else if (current == '+' || current == '*' || current == '/' || current == '(' || current == '^') {
            if (current != '(' && main[1] == '*' || main[0] == '-' || main[1] == '^' || main[1] == '+' ||
                main[1] == '/') {
                ErrorExpr();
                return -1;
            }
            if (current == '(' && main[1] == ')' || main[1] == '*' || main[1] == '^' || main[1] == '+' ||
                main[1] == '/') {
                ErrorExpr();
                return -1;
            }
            while (!operations.empty() && PrioritypASS(current) <= PrioritypASS(operations.top()) &&
                   current != '(') {
                count(nums, operations);
            }
            operations.push(current);
            main.erase(main.begin());
            continue;
        } else if (current == '-') {
            if (main[1] == '*' || main[1] == '^' || main[1] == '-' || main[1] == '+' || main[1] == '/') {
                ErrorExpr();
                return -1;
            }
            while (!operations.empty() && operations.top() != '+' && operations.top() != '(')
                count(nums, operations);
            while (main[0] == '-' || main[0] == ' ') {
                main.erase(main.begin());
            }
            operations.push('+');
            operations.push('-');
            continue;
        } else if (current == ')') {
            while (operations.top() != '(') {
                if (count(nums, operations) == 0) return -1;
            }
            main.erase(main.begin());
            operations.pop();
        } else if (current == ' ') main.erase(main.begin());
        else {
            std::cerr << "Error expression...";
            return -3;
        }
    }
    while (!operations.empty()) {
        if (count(nums, operations) == 0) return -1;
    }
    std::cout << "Answer is: " << nums.top();
    return 0;
}