#include<iostream>
using namespace std;
#define max_size 5
template <class type>
class A
{
	int top = -1;
	type stk[max_size];

public:
	void push()
	{
		if (top >= max_size - 1)
		{
			cout << "stack overflow" << endl;
			return;
		}
		top++;
		cout << "enter elements to push" << endl;
		cin >> stk[top];
	}
	void display_stack()
	{
		if (top <= -1)
		{
			cout << "stack is empty" << endl;
			return;
		}
		int i;
		for (i = 0; i <= top; i++)
			cout << stk[i] << " ";
		cout << endl;
	}
	void pop()
	{
		if (top < 0)
		{
			cout << "stack underflow" << endl;
			return;
		}
		cout << "deleted element" << stk[top] << endl;
		top--;
	}
};
int main()
{
	int op, op1, c = 0, op3, op4 = 0;
	A<int> *s1;
	A<char> *s2;
	A<float> *s3;
	A<double> *s4;
	A<string> *s5;
	while (1)
	{
	l1:
		cout << "enter a option" << endl;
		cout << "1)int 2)char 3)float 4)double 5)string 6)exit" << endl;
		cin >> op;
		switch (op)
		{
		case 1:
			cout << "integer data selected" << endl;
			if (op4 == op)
			{
				cout << "continue with 1)old stack 2)new stack\n";
				cin >> op3;
				if (op3 == 2)
				{
					delete s1;
					s1 = new A<int>();
				}
			}
			else
				s1 = new A<int>();
			while (1)
			{
				cout << "enter your option" << endl;
				cout << "1)push 2)pop 3)display 4)main_menu" << endl;
				cin >> op1;
				switch (op1)
				{
				case 1:
					s1->push();
					break;
				case 2:
					s1->pop();
					break;
				case 3:
					s1->display_stack();
					break;
				case 4:
					op4 = op;
					goto l1;
				}
			}
			break;
		case 2:
			cout << "char data selected" << endl;
			if (op4 == op)
			{
				cout << "continue with 1)old stack 2)new stack\n";
				cin >> op3;
				if (op3 == 2)
				{
					delete s2;
					s2 = new A<char>();
				}
			}
			else
				s2 = new A<char>();
			while (1)
			{
				cout << "enter your option" << endl;
				cout << "1)push 2)pop 3)display 4)main_menu" << endl;
				cin >> op1;
				switch (op1)
				{
				case 1:
					s2->push();
					break;
				case 2:
					s2->pop();
					break;
				case 3:
					s2->display_stack();
					break;
				case 4:
					op4 = op;
					goto l1;
				}
			}
			break;
		case 3:
			cout << "float data selected" << endl;
			if (op4 == op)
			{
				cout << "continue with 1)old stack 2)new stack\n";
				cin >> op3;
				if (op3 == 2)
				{
					delete s3;
					s3 = new A<float>();
				}
			}
			else
				s3 = new A<float>();
			while (1)
			{
				cout << "enter your option" << endl;
				cout << "1)push 2)pop 3)display 4)main_menu" << endl;
				cin >> op1;
				switch (op1)
				{
				case 1:
					s3->push();
					break;
				case 2:
					s3->pop();
					break;
				case 3:
					s3->display_stack();
					break;
				case 4:
					op4 = op;
					goto l1;
				}
			}
			break;
		case 4:
			cout << "double data selected" << endl;
			s4 = new A<double>();
			if (op4 == op)
			{
				cout << "continue with 1)old stack 2)new stack\n";
				cin >> op3;
				if (op3 == 2)
				{
					delete s4;
					s4 = new A<double>();
				}
			}
			else
				s4 = new A<double>();
			while (1)
			{
				cout << "enter your option" << endl;
				cout << "1)push 2)pop 3)display 4)main_menu" << endl;
				cin >> op1;
				switch (op1)
				{
				case 1:
					s4->push();
					break;
				case 2:
					s4->pop();
					break;
				case 3:
					s4->display_stack();
					break;
				case 4:
					op4 = op;
					goto l1;
				}
			}
			break;
		case 5:
			cout << "string  data selected" << endl;
			if (op4 == op)
			{
				cout << "continue with 1)old stack 2)new stack\n";
				cin >> op3;
				if (op3 == 2)
				{
					delete s5;
					s5 = new A<string>();
				}
			}
			else
				s5 = new A<string>();
			while (1)
			{
				cout << "enter your option" << endl;
				cout << "1)push 2)pop 3)display 4)main_menu" << endl;
				cin >> op1;
				switch (op1)
				{
				case 1:
					s5->push();
					break;
				case 2:
					s5->pop();
					break;
				case 3:
					s5->display_stack();
					break;
				case 4:
					op4 = op;
					goto l1;
				}
			}
			break;
		case 6:
			exit(0);
		default:
			c++;
			if (c == 1)
			{
				cout << "enter valid option\n";
			}
			else if (c == 2)
			{
				cout << "take care while entering the option\n";
			}
			else if (c == 3)
			{
				cout << "thanks for using our application\n";
				exit(0);
			}
		}
	}
}
