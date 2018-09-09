#pragma once

#include <string>


class Expression
{
public:
	//virtual ~Expression();
	virtual double interpret() = 0;
};

class NumberExpression : public Expression
{
	double number;
public:
	NumberExpression(double _number)
	{
		number = _number;
	}
	double interpret()
	{
		return number;
	}
};

class PlusExpression : public Expression
{
	Expression *left;
	Expression *right;
public:
	PlusExpression(Expression *_left, Expression *_right)
	{
		left = _left;
		right = _right;
	}
	double interpret()
	{
		return left->interpret() + right->interpret();
	}
};

class MinusExpression : public Expression
{
	Expression *left;
	Expression *right;
public:
	MinusExpression(Expression *_left, Expression *_right)
	{
		left = _left;
		right = _right;
	}
	double interpret()
	{
		return left->interpret() - right->interpret();
	}
};

class MultExpression : public Expression
{
	Expression *left;
	Expression *right;
public:
	MultExpression(Expression *_left, Expression *_right)
	{
		left = _left;
		right = _right;
	}
	double interpret()
	{
		return left->interpret() * right->interpret();
	}
};

class DivExpression : public Expression
{
	Expression *left;
	Expression *right;
public:
	DivExpression(Expression *_left, Expression *_right)
	{
		left = _left;
		right = _right;
	}
	double interpret()
	{
		return left->interpret() / right->interpret();
	}
};

class Context
{
public:
	Expression * evaluate(std::string s)
	{
		//убираю все пробелы и все запятые меняю на точки
		std::string tmp;
		for (size_t i = 0; i < s.length(); ++i)
		{
			if (s[i] != ' ')
			{
				if (s[i] == ',')
					tmp += '.';
				else
					tmp += s[i];
			}
		}
		s.swap(tmp);

		//сначала считаем то что в скобках
		size_t ind = s.find('(');
		if (ind != std::string::npos)
		{
			int k = 1;
			size_t i = ind + 1;
			while (i < s.length())
			{
				if (s[i] == '(')
				{
					if (k == 0)
						ind = i;
					++k;
				}
				else
				{
					if (s[i] == ')')
					{
						if (k == 1)
						{
							//нашли конец закрывающей скобки
							s = s.substr(0, ind) + std::to_string(evaluate(s.substr(ind + 1, i - 1 - ind))->interpret()) + s.substr(i + 1);
							//если скобок больше нету то выходим из цикла
							if ((ind = s.find('(')) == std::string::npos)
							{
								break;
							}
							else
							{
								i = ind + 1;
								++k;
							}
						}
						--k;
					}
				}
				++i;
			}
		}

		//char priorityOperator = '/';
		//пока есть операторы крутим цикл
		while (s.find_first_of("*/") != std::string::npos)
		{
			//беру приоритетный оператор
			if ((ind = s.find('/')) == std::string::npos)
			{
				//priorityOperator = '*';
				//если не нашли деление ищу умножение
				if ((ind = s.find('*')) == std::string::npos)
				{
					//если не нашел умножения, то все операции можно делать подряд
					break;
				}
			}
			size_t pos = ind - 1;
			while (pos > 0)
			{
				if (isdigit(s[pos]) || s[pos] == '.')
				{
					--pos;
				}
				else
				{
					break;
				}
			}

			size_t pos1 = ind + 1;
			while (pos1 < s.length())
			{
				if (isdigit(s[pos1]) || s[pos1] == '.')
				{
					++pos1;
				}
				else
				{
					break;
				}
			}

			s = s.substr(0, pos + 1) + std::to_string(oper(s.substr(pos + 1, pos1 - pos))->interpret()) + s.substr(pos1);
		}
		return oper(s);
	}
	Expression *oper(std::string s)
	{
		int pos = s.length() - 1;
		std::string tmp;
		while (pos > 0)
		{
			if (isdigit(s[pos]) || s[pos] == '.')
			{
				--pos;
			}
			else
			{
				Expression *right = new NumberExpression(std::stod(s.substr(pos + 1, s.length())));
				Expression *left = evaluate(s.substr(0, pos));
				char oper = s[pos];
				switch (oper)
				{
				case '+': return new PlusExpression(left, right);
					break;
				case '-': return new MinusExpression(left, right);
					break;
				case '*': return new MultExpression(left, right);
					break;
				case '/': return new DivExpression(left, right);
					break;
				}
			}
		}
		double result = std::stod(s);
		return new NumberExpression(result);
	}
};

