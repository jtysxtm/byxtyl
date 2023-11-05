#include<iostream>
#include<cstring>
#include<string>
#include<stack>
#include<vector>
#include<set>
#include<queue>
#define MAX 128
using namespace std;

typedef set<int> IntSet;
typedef set<char> CharSet;

//————————————表达式转NFA————————————//

struct NFA_State	//NFA状态
{
	int state_index;	//状态号
	char input;		//状态弧上的值
	int trans_state_index;		//状态弧转移到的状态号
	IntSet ep_trans;			//当前状态通过ε转移到的状态号集合
}NFA_States[MAX];

int nfa_state_num = 0;		//NFA状态总数

struct NFA
{
	NFA_State* head;		//头指针
	NFA_State* tail;		//尾指针
};


//n1--ch-->n2
void add(NFA_State* n1, NFA_State* n2, char ch)
{
	n1->input = ch;
	n1->trans_state_index = n2->state_index;
}

//n1--ε-->n2
void add(NFA_State* n1, NFA_State* n2)
{
	n1->ep_trans.insert(n2->state_index);
}

//新建一个NFA, 即从NFA状态数组中取出两个状态
NFA create_NFA(int sum)
{
	NFA nfa;
	nfa.head = &NFA_States[sum];
	nfa.tail = &NFA_States[sum + 1];
	return nfa;
}

//字符串s第n位后面插入ch
void insert(string& s, int n, char ch)
{
	s += '#';
	for (int i = s.size() - 1; i > n; i--)
	{
		s[i] = s[i - 1];
	}
	s[n] = ch;
}

//优先级比较，为操作符赋权重，比较权重大小以判断优先级
int priority(char ch)
{
	if (ch == '*')
	{
		return 3;
	}
	if (ch == '&')
	{
		return 2;
	}
	if (ch == '|')
	{
		return 1;
	}
	if (ch == '(')
	{
		return 0;
	}
}

//对字符串s进行预处理
//第一位是操作数、*或)、且第二位是操作数或(之间加入连接符&
void preprocess(string& s)
{
	int i = 0;
	int length = s.size();

	while (i < length)
	{
		if ((s[i] >= 'a' && s[i] <= 'z') || (s[i] == '*') || (s[i] == ')'))
		{
			if ((s[i + 1] >= 'a' && s[i + 1] <= 'z') || s[i + 1] == '(')
			{
				insert(s, i + 1, '&');
				length++;
			}
		}
		i++;
	}
}



//中缀转后缀
string infix_to_suffix(string infix_str)
{
	preprocess(infix_str);		

	string suffix_str;		//输出后缀表达式
	stack<char> operator_stack;	//运算符栈

	for (int i = 0; i < infix_str.size(); i++)
	{
		if (infix_str[i] >= 'a' && infix_str[i] <= 'z')	//操作数直接输出
		{
			suffix_str += infix_str[i];
		}
		else							//运算符
		{
			if (infix_str[i] == '(')			//左括号入栈
			{
				operator_stack.push(infix_str[i]);
			}
			else if (infix_str[i] == ')')	//右括号
			{
				char temp = operator_stack.top();
				while (temp != '(')		//栈中元素出栈，直到栈顶为左括号
				{
					suffix_str += temp;
					operator_stack.pop();
					temp = operator_stack.top();
				}
				operator_stack.pop();			//左括号出栈
			}
			else	//其他操作符
			{
				if (!operator_stack.empty())		//符号栈非空
				{
					char temp = operator_stack.top();
					while (priority(temp) >= priority(infix_str[i]))	//弹出栈中优先级大于等于当前运算符的
					{
						suffix_str += temp;
						operator_stack.pop();
						if (operator_stack.empty())		//运算符栈为空结束循环
						{
							break;
						}
						else temp = operator_stack.top();
					}
					operator_stack.push(infix_str[i]);		//当前运算符入栈
				}
				else		//符号栈为空，运算符入栈
				{
					operator_stack.push(infix_str[i]);
				}
			}
		}
	}

	//最后如果运算符栈不为空，出栈，输出
	while (!operator_stack.empty())
	{
		char temp = operator_stack.top();
		operator_stack.pop();
		suffix_str += temp;
	}

	cout << "—————————————————————————————————" << endl << endl;
	cout << "中缀表达式为：" << infix_str << endl << endl;
	cout << "后缀表达式为：" << suffix_str << endl << endl;

	return suffix_str;
}

//后缀表达式转nfa
NFA str_to_NFA(string suffix_str)
{

	stack<NFA> NFA_stack;		

	for (int i = 0; i < suffix_str.size(); i++)		
	{
		//操作数
		if (suffix_str[i] >= 'a' && suffix_str[i] <= 'z')		
		{
			NFA nfa = create_NFA(nfa_state_num);		
			nfa_state_num += 2;		//状态总数加2

			add(nfa.head, nfa.tail, suffix_str[i]);		//NFA的头指向尾，弧上的值为suffix_str[i]

			NFA_stack.push(nfa);		//NFA入栈
		}
		else if (suffix_str[i] == '*')		//闭包运算符
		{

			NFA nfa_1 = create_NFA(nfa_state_num);		//新建
			nfa_state_num += 2;					//状态总数加2
			NFA nfa_2 = NFA_stack.top();			//从栈中弹出一个NFA
			NFA_stack.pop();

			add(nfa_2.tail, nfa_1.head);			//2的尾--ε->1的头
			add(nfa_2.tail, nfa_1.tail);			//2的尾--ε->1的尾
			add(nfa_1.head, nfa_2.head);			//1的头--ε->2的头
			add(nfa_1.head, nfa_1.tail);			//1的头--ε->1的尾

			NFA_stack.push(nfa_1);			//新生成的NFA入栈*/
		}
		else if (suffix_str[i] == '|')		//或运算符
		{

			NFA nfa_1, nfa_2;			//从栈中弹出两个NFA
			nfa_2 = NFA_stack.top();		//栈顶
			NFA_stack.pop();		

			nfa_1 = NFA_stack.top();	//次栈顶
			NFA_stack.pop();

			NFA nfa = create_NFA(nfa_state_num);	
			nfa_state_num += 2;			//状态总数加2

			add(nfa.head, nfa_1.head);		//nfa的头--ε->1的头
			add(nfa.head, nfa_2.head);		//nfa的头--ε->2的头
			add(nfa_1.tail, nfa.tail);		//1的尾--ε->nfa的尾
			add(nfa_2.tail, nfa.tail);		//2的尾--ε->nfa的尾

			NFA_stack.push(nfa);		
		}
		else if (suffix_str[i] == '&')		//连接运算符
		{

			NFA nfa, nfa_1, nfa_2;		
			nfa_2 = NFA_stack.top();		
			NFA_stack.pop();
			nfa_1 = NFA_stack.top();
			NFA_stack.pop();

			add(nfa_1.tail, nfa_2.head);				//1的尾--ε->2的头

			nfa.head = nfa_1.head;					//nfa的头为1的头
			nfa.tail = nfa_2.tail;					//nfa的尾为2的尾

			NFA_stack.push(nfa);		
		}
	}

	return NFA_stack.top();	//最后的栈顶元素即为生成好的NFA
}

void print_NFA(NFA nfa)
{

	cout << "——————————     NFA     ——————————" << endl << endl;
	cout << "NFA总共有" << nfa_state_num << "个状态，" << endl;
	cout << "初态为：" << nfa.head->state_index << "，"<<endl;
	cout << "终态为：" << nfa.tail->state_index << "，" << endl;
	cout << "转移函数为：" << endl;

	for (int i = 0; i < nfa_state_num; i++)		
	{
		if (NFA_States[i].input != '#')		//弧上的值不是初始的‘#’
		{
			cout << NFA_States[i].state_index << "-->'" << NFA_States[i].input << "'-->" << NFA_States[i].trans_state_index << '\t';
		}

		IntSet::iterator it;		//经过ε到达的状态
		for (it = NFA_States[i].ep_trans.begin(); it != NFA_States[i].ep_trans.end(); it++)
		{
			cout << NFA_States[i].state_index << "-->'" << ' ' << "'-->" << *it << '\t';
		}

		cout << endl;
	}
}

//————————————NFA转DFA————————————

struct DFA_Edge			//转换弧
{
	char input;			
	int trans;			
};

struct DFA_State		//DFA状态
{

	bool is_end;	//是否为终态
	int index;		//状态号
	IntSet closure;		//ε-move()闭包

	int edgeNum;		//射出弧数
	DFA_Edge Edges[10];		//射出弧
}DFA_states[MAX];	//DFA状态数组
int DFA_state_num = 0;		//状态总数

struct DFA		
{
	int startState;		//初态
	set<int> endStates;		//终态集
	set<char> terminator;		//终结符集
	int trans[MAX][26];		//转移矩阵
};


//判断是否为终态
bool IsEnd(NFA n, IntSet s)
{
	IntSet::iterator it;
	for (it = s.begin(); it != s.end(); it++)	//遍历nfa状态集
	{
		if (*it == n.tail->state_index)			//如果包含nfa的终态
		{
			return true;	//该状态为终态
		}
	}

	return false;		/*如果不包含，则不是终态，返回false*/
}

//求ε-cloure
IntSet ep_cloure(IntSet s)
{
	stack<int> ep_stack;		

	IntSet::iterator it;
	for (it = s.begin(); it != s.end(); it++)
	{
		ep_stack.push(*it);			//将状态集中的每一个元素都入栈
	}

	while (!ep_stack.empty())		
	{
		int temp = ep_stack.top();		//弹出一个元素
		ep_stack.pop();

		IntSet::iterator iter;
		for (iter = NFA_States[temp].ep_trans.begin(); iter != NFA_States[temp].ep_trans.end(); iter++) //遍历通过ε能转换到的状态集
		{
			if (!s.count(*iter))				//如果当前元素没有在集合中出现
			{								
				s.insert(*iter);		//加入集合中
				ep_stack.push(*iter);		//入栈
			}
		}
	}

	return s;		//返回ε-cloure
}

//求ε-cloure(move(ch))
IntSet moveEpCloure(IntSet s, char ch)
{
	IntSet temp;

	IntSet::iterator it;
	for (it = s.begin(); it != s.end(); it++)		
	{
		if (NFA_States[*it].input == ch)		//对应转换弧上的值为ch
		{
			temp.insert(NFA_States[*it].trans_state_index);		//把该弧通过ch转换到的状态加入集合
		}
	}

	temp = ep_cloure(temp);		//求temp的ε闭包
	return temp;
}


DFA NFA_To_DFA(NFA n, string str)	
{
	cout << "——————————     DFA     ——————————" << endl << endl;

	int i;
	DFA d;
	set<IntSet> states;		//判断求出一个状态集s的ε-cloure(move(ch))后是否出现新状态
	memset(d.trans, -1, sizeof(d.trans));	//初始化转移矩阵

	for (i = 0; i < str.size(); i++)			//遍历后缀表达式
	{
		if (str[i] >= 'a' && str[i] <= 'z')		//操作数，加入到终结符集中
		{
			d.terminator.insert(str[i]);
		}
	}

	d.startState = 0;		
	IntSet tempSet;
	tempSet.insert(n.head->state_index);		//初态加入集合

	DFA_states[0].closure = ep_cloure(tempSet);		//求dfa的初态
	DFA_states[0].is_end = IsEnd(n, DFA_states[0].closure);		//判断初态是否为终态

	DFA_state_num++;		

	queue<int> q;
	q.push(d.startState);		//dfa的初态存入队列

	while (!q.empty())	
	{
		int num = q.front();				//出队首元素
		q.pop();

		CharSet::iterator it;
		for (it = d.terminator.begin(); it != d.terminator.end(); it++)		//遍历终结符集
		{
			IntSet temp = moveEpCloure(DFA_states[num].closure, *it);		//计算每个终结符的ε-cloure(move(ch))
			if (!states.count(temp) && !temp.empty())	//状态集不为空且与之前求出来的状态集不同，新建DFA状态
			{
				states.insert(temp);				
				DFA_states[DFA_state_num].closure = temp;
				DFA_states[num].Edges[DFA_states[num].edgeNum].input = *it;				//状态弧的输入即为当前终结符
				DFA_states[num].Edges[DFA_states[num].edgeNum].trans = DFA_state_num;		//弧转移到的状态为最后一个DFA状态
				DFA_states[num].edgeNum++;	
				d.trans[num][*it - 'a'] = DFA_state_num;		//更新转移矩阵

				DFA_states[DFA_state_num].is_end = IsEnd(n, DFA_states[DFA_state_num].closure);	//是否为终态

				q.push(DFA_state_num);		//新状态号加入队列
				DFA_state_num++;		
			}
			else			//求出状态集在之前求出的某个状态集相同
			{
				for (i = 0; i < DFA_state_num; i++)		
				{
					if (temp == DFA_states[i].closure)		//找到与该集合相同的DFA状态
					{
						DFA_states[num].Edges[DFA_states[num].edgeNum].input = *it;		//状态弧的输入即为当前终结符
						DFA_states[num].Edges[DFA_states[num].edgeNum].trans = i;			//转移到的状态即为i
						DFA_states[num].edgeNum++;					
						d.trans[num][*it - 'a'] = i;		//更新转移矩阵
						break;
					}
				}
			}
		}
	}

	//计算终态集
	for (i = 0; i < DFA_state_num; i++)	//遍历dfa的所有状态
	{
		if (DFA_states[i].is_end == true)		//是终态
		{
			d.endStates.insert(i);		//将该状态号加入终态集
		}
	}

	return d;
}


void print_DFA(DFA d)
{
	cout << "DFA总共有" << DFA_state_num << "个状态，" << endl;
	cout << "初态为" << d.startState << endl << endl;
	cout << "有穷字母表为｛ ";
	set<char>::iterator it;
	for (it = d.terminator.begin(); it != d.terminator.end(); it++)
	{
		cout << *it << ' ';
	}
	cout << '}' << endl << endl;
	cout << "终态集为｛ ";
	IntSet::iterator iter;
	for (iter = d.endStates.begin(); iter != d.endStates.end(); iter++)
	{
		cout << *iter << ' ';
	}
	cout << '}' << endl << endl;
	cout << "转移函数为：" << endl;
	int i, j;
	for (i = 0; i < DFA_state_num; i++)
	{
		for (j = 0; j < DFA_states[i].edgeNum; j++)
		{

			if (DFA_states[DFA_states[i].Edges[j].trans].is_end == true)
			{
				cout << DFA_states[i].index << "-->'" << DFA_states[i].Edges[j].input;
				cout << "'--><" << DFA_states[i].Edges[j].trans << ">\t";
			}
			else
			{
				cout << DFA_states[i].index << "-->'" << DFA_states[i].Edges[j].input;
				cout << "'-->" << DFA_states[i].Edges[j].trans << '\t';
			}
		}
		cout << endl;
	}
	cout << endl << "转移矩阵为：" << endl << "     ";
	CharSet::iterator t;
	for (t = d.terminator.begin(); t != d.terminator.end(); t++)
	{
		cout << *t << "   ";
	}
	cout << endl;

	for (i = 0; i < DFA_state_num; i++)
	{

		if (d.endStates.count(i))
		{
			cout << '<' << i << ">  ";
		}
		else
		{
			cout << ' ' << i << "   ";
		}

		for (j = 0; j < 26; j++)
		{
			if (d.terminator.count(j + 'a'))
			{
				if (d.trans[i][j] != -1)
				{
					cout << d.trans[i][j] << "   ";
				}
				else
				{
					cout << "    ";
				}
			}
		}

		cout << endl;
	}
}

//————————————DFA的最小化————————————
IntSet s[MAX];					
DFA_State min_DFA_states[MAX];		
int min_DFA_state_num = 0;			//minDfa的状态总数/划分出的集合数

struct stateSet			//划分状态集
{
	int index;			//能转换到的状态集标号
	IntSet s;		//dfa状态号
};

//当前划分总数为count，返回状态n所属的状态集标号
int find_set_num(int count, int n)
{
	for (int i = 0; i < count; i++)
	{
		if (s[i].count(n))
		{
			return i;
		}
	}
}

//最小化DFA
DFA min_DFA(DFA d)
{

	int i, j;
	cout << endl << "——————————     minDFA     ——————————" << endl << endl;

	DFA minDfa;
	minDfa.terminator = d.terminator;		//终结符集赋给minDfa
	memset(minDfa.trans, -1, sizeof(minDfa.trans));		//初始化minDfa转移矩阵

	//第一次划分，终态与非终态分开
	bool endFlag = true;					//判断所有状态是否全为终态
	bool cutFlag = true;		//上一次是否产生新的划分的标志
	for (i = 0; i < DFA_state_num; i++)	
	{
		if (DFA_states[i].is_end == false)		//不是终态
		{
			endFlag = false;						
			min_DFA_state_num = 2;					
			s[1].insert(DFA_states[i].index);		//该状态的状态号加入s[1]
		}
		else						//是终态
		{
			s[0].insert(DFA_states[i].index);		//该状态的状态号加入s[0]
		}
	}

	if (endFlag)			//所有dfa状态都是终态
	{
		min_DFA_state_num = 1;			//只有一个集合
	}

	while (cutFlag)		//上一次产生新划分
	{
		int cutCount = 0;			//需要产生新的划分的数量
		for (i = 0; i < min_DFA_state_num; i++)			//遍历每个划分集合
		{
			CharSet::iterator it;
			for (it = d.terminator.begin(); it != d.terminator.end(); it++)		//遍历dfa的终结符集
			{
				int setNum = 0;				//当前缓冲区中的状态集个数
				stateSet temp[20];			//划分状态集“缓冲区”

				IntSet::iterator iter;
				for (iter = s[i].begin(); iter != s[i].end(); iter++)		//遍历每个状态号
				{
					bool epFlag = true;			//该集合中是否存在没有该终结符对应的转换弧的状态
					for (j = 0; j < DFA_states[*iter].edgeNum; j++)		//遍历该状态的所有边
					{
						if (DFA_states[*iter].Edges[j].input == *it)		//输入为该终结符
						{
							epFlag = false;			

							//计算该状态转换到的状态集的标号
							int transNum = find_set_num(min_DFA_state_num, DFA_states[*iter].Edges[j].trans);

							int curSetNum = 0;			//遍历缓冲区，寻找是否存在到达这个标号的状态集
							while ((temp[curSetNum].index != transNum) && (curSetNum < setNum))
							{
								curSetNum++;
							}

							if (curSetNum == setNum)		//缓冲区中不存在到达这个标号的状态集
							{
								//缓冲区中新建状态集
								temp[setNum].index = transNum;		//能转换到的状态集
								temp[setNum].s.insert(*iter);		

								setNum++;		//缓冲区中的状态集个数加一
							}
							else			//缓冲区中存在到达这个标号的状态集
							{
								temp[curSetNum].s.insert(*iter);	//加入到该状态集中
							}
						}
					}

					if (epFlag)		//该状态不存在与该终结符对应的转换弧
					{
						int curSetNum = 0;
						while ((temp[curSetNum].index != -1) && (curSetNum < setNum))
						{
							curSetNum++;
						}

						if (curSetNum == setNum)	//不存在这样的状态集
						{
							//缓冲区中新建状态集
							temp[setNum].index = -1;			//转移到的状态集标号为-1
							temp[setNum].s.insert(*iter);		
							setNum++;		
						}
						else			//缓冲区中存在到达这个标号的状态集
						{
							temp[curSetNum].s.insert(*iter);	
						}
					}
				}
				if (setNum > 1)	//缓冲区中的状态集个数大于1，表示同一个状态集中的元素能转换到不同的状态集，需要划分
				{
					cutCount++;		
					//每组划分创建新的dfa
					for (j = 1; j < setNum; j++)
					{
						IntSet::iterator t;
						for (t = temp[j].s.begin(); t != temp[j].s.end(); t++)
						{
							s[i].erase(*t);				//原状态集删除该状态
							s[min_DFA_state_num].insert(*t);		//新的状态集加入该状态
						}
						min_DFA_state_num++;		
					}
				}
			}
		}
		if (cutCount == 0)		//本次不需要进行划分
		{
			cutFlag = false;
		}
	}

	//遍历每个划分好的状态集
	for (i = 0; i < min_DFA_state_num; i++)
	{
		IntSet::iterator y;
		for (y = s[i].begin(); y != s[i].end(); y++)	
		{
			if (*y == d.startState)		//最小化DFA状态为初态
			{
				minDfa.startState = i;
			}
			if (d.endStates.count(*y))		//最小化DFA状态也为终态
			{
				min_DFA_states[i].is_end = true;
				minDfa.endStates.insert(i);		//最小化DFA状态加入终态集
			}

			for (j = 0; j < DFA_states[*y].edgeNum; j++)		//遍历该DFA状态的每条弧，为最小化DFA创建弧
			{
				for (int t = 0; t < min_DFA_state_num; t++)
				{
					if (s[t].count(DFA_states[*y].Edges[j].trans))
					{
						bool haveEdge = false;		//判断该弧是否已经创建的标志
						for (int l = 0; l < min_DFA_states[i].edgeNum; l++)	
						{		
							if ((min_DFA_states[i].Edges[l].input == DFA_states[*y].Edges[j].input) && (min_DFA_states[i].Edges[l].trans == t))
							{
								haveEdge = true;	
							}
						}
						if (!haveEdge)		//创建一条新的弧
						{
							min_DFA_states[i].Edges[min_DFA_states[i].edgeNum].input = DFA_states[*y].Edges[j].input;	
							min_DFA_states[i].Edges[min_DFA_states[i].edgeNum].trans = t;	
							minDfa.trans[i][DFA_states[*y].Edges[j].input - 'a'] = t;	//更新转移矩阵
							min_DFA_states[i].edgeNum++;	
						}
						break;
					}
				}
			}
		}
	}
	return minDfa;
}

void print_min_DFA(DFA d)
{
	cout << "minDFA总共有" << min_DFA_state_num << "个状态，" << endl;
	cout << "初态为" << d.startState << endl << endl;

	cout << "有穷字母表为｛ ";
	set<char>::iterator it;
	for (it = d.terminator.begin(); it != d.terminator.end(); it++)
	{
		cout << *it << ' ';
	}
	cout << '}' << endl << endl;

	cout << "终态集为｛ ";
	IntSet::iterator iter;
	for (iter = d.endStates.begin(); iter != d.endStates.end(); iter++)
	{
		cout << *iter << ' ';
	}
	cout << '}' << endl << endl;

	cout << "转移函数为：" << endl;
	int i, j;
	for (i = 0; i < min_DFA_state_num; i++)
	{
		for (j = 0; j < min_DFA_states[i].edgeNum; j++)
		{

			if (min_DFA_states[min_DFA_states[i].Edges[j].trans].is_end == true)
			{
				cout << min_DFA_states[i].index << "-->'" << min_DFA_states[i].Edges[j].input;
				cout << "'--><" << min_DFA_states[i].Edges[j].trans << ">\t";
			}
			else
			{
				cout << min_DFA_states[i].index << "-->'" << min_DFA_states[i].Edges[j].input;
				cout << "'-->" << min_DFA_states[i].Edges[j].trans << '\t';
			}
		}
		cout << endl;
	}

	cout << endl << "转移矩阵为：" << endl << "     ";
	CharSet::iterator t;
	for (t = d.terminator.begin(); t != d.terminator.end(); t++)
	{
		cout << *t << "   ";
	}
	cout << endl;

	for (i = 0; i < min_DFA_state_num; i++)
	{

		if (d.endStates.count(i))
		{
			cout << '<' << i << ">  ";
		}
		else
		{
			cout << ' ' << i << "   ";
		}

		for (j = 0; j < 26; j++)
		{
			if (d.terminator.count(j + 'a'))
			{
				if (d.trans[i][j] != -1)
				{
					cout << d.trans[i][j] << "   ";
				}
				else
				{
					cout << "    ";
				}
			}
		}

		cout << endl;
	}
	cout << endl << "—————————————————————————————————";
}


int main()
{
	string str = "(a|b*)c*acb";

	str = infix_to_suffix(str);		

	int i, j;
	for (i = 0; i < MAX; i++)
	{
		NFA_States[i].state_index = i;
		NFA_States[i].input = '#';
		NFA_States[i].trans_state_index = -1;
	}

	for (i = 0; i < MAX; i++)
	{

		DFA_states[i].index = i;
		DFA_states[i].is_end = false;

		for (j = 0; j < 10; j++)
		{

			DFA_states[i].Edges[j].input = '#';
			DFA_states[i].Edges[j].trans = -1;
		}
	}

	for (i = 0; i < MAX; i++)
	{

		min_DFA_states[i].index = i;
		min_DFA_states[i].is_end = false;

		for (int j = 0; j < 10; j++)
		{

			min_DFA_states[i].Edges[j].input = '#';
			min_DFA_states[i].Edges[j].trans = -1;
		}
	}

	NFA n = str_to_NFA(str);
	print_NFA(n);

	DFA d = NFA_To_DFA(n, str);
	print_DFA(d);

	DFA minDfa = min_DFA(d);
	print_min_DFA(minDfa);

	return 0;
}

