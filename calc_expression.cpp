#include <iostream>
#include <string>
#include <cstdlib>
#include "Stack"


//函数功能：实现表达式求值
//函数参数：
//exp 待求值的表达式（整数的四则混合运算表达式，可能含有小括号）
//返回值：表达式的值

/*
bool isHigh(char top, char exp)
{
	if((top == '+' || top == '-') && (exp == '*' || exp == '/'))
		return false;
	return true;
}
*/

int calc(std::string exp)
{
	//你需要完成的代码
	
	std::string exp2; //后缀表达式
	Stack<char> ops;  //运算符栈

	int i;
	for(i = 0; i < exp.size(); ++i)
	{
		switch(exp[i])
		{
			case '+':
			case '-':
			{
				exp2 += ' ';

				if(ops.empty())
				{
					ops.push(exp[i]);
					break;
				}

				char op;

				try
				{
					while((op = ops.top()) != '(')
					{
						ops.pop();
						exp2 += op;
					}
				}
				catch(int)
				{
				}
				
				ops.push(exp[i]);						
			}
			break;

			case '*':
			case '/':
			{
				exp2 += ' ';

				if(ops.empty())
				{
					ops.push(exp[i]);
					break;
				}

				char op = ops.top();

				if(op == '+' || op == '-')
				{
					ops.push(exp[i]);
				}
				else
				{
					char c;
					
					while(1)	
					{
						try
						{
							c = ops.top();

							if(c == '*' || c == '/')
							{
								ops.pop();
								exp2 += c;
							}
							else
							{
								ops.push(exp[i]);
								break;
							}
						}
						catch(int)
						{
						}
					}			
				}
			}
			break;

			case '(':
			{
				ops.push('(');
			}
			break;
		
			case ')':
			{
				char op;

				while((op = ops.top()) != '(')
				{
					ops.pop();
					exp2 += op;
				}

				ops.pop();
			}
			break;
			
			default:
			{
				exp2 += exp[i];
			}
		}
	}

	char op;

	try
	{
		while(op = ops.top())
		{
			ops.pop();	
			exp2 += op;
		}
	}
	catch(int)
	{
	}

	//std::cout << exp2 << std::endl;

	Stack<int> vals;
	int n;

	for(i = 0; i < exp2.size();)
	{
		if(exp2[i] >= '0' && exp2[i] <= '9')
		{
			n = atoi(exp2.c_str() + i);
			vals.push(n);

			while(exp2[i] >= '0' && exp2[i] <= '9') ++i;
		}
		else if(exp2[i] == ' ')
		{
			++i;
		}
		else
		{
			int n1, n2, r = 0;

			n1 = vals.top();
			vals.pop();
			n2 = vals.top();
			vals.pop();

			switch(exp2[i])
			{
				case '+':
				{
					r = n1 + n2;
				}
				break;

				case '-':
				{
					r = n2 - n1;
				}
				break;

				case '*':
				{
					r = n1 * n2;
				}
				break;

				case '/':
				{
					if(n1 == 0)
					{
						//std::cout << "除数不能为零！" << std::endl;
						throw 1;
					}

					r = n2 / n1;
				}
				break;
			}

			vals.push(r);
			
			++i;
		}
	}

	return vals.top();
}


int main()
{
	std::string exp;

	while(1)
	{
		std::cout << "\n>>> ";
		std::cin >> exp;

		try
		{
			std::cout << calc(exp) << std::endl;
		}
		catch(int e)
		{
			if(e == 1)
			{
				std::cout << "除数不能为零！" << std::endl;
			}
		}
	}
}


