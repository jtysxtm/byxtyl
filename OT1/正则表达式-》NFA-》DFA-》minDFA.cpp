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

//���������������������������ʽתNFA������������������������//

struct NFA_State	//NFA״̬
{
	int state_index;	//״̬��
	char input;		//״̬���ϵ�ֵ
	int trans_state_index;		//״̬��ת�Ƶ���״̬��
	IntSet ep_trans;			//��ǰ״̬ͨ����ת�Ƶ���״̬�ż���
}NFA_States[MAX];

int nfa_state_num = 0;		//NFA״̬����

struct NFA
{
	NFA_State* head;		//ͷָ��
	NFA_State* tail;		//βָ��
};


//n1--ch-->n2
void add(NFA_State* n1, NFA_State* n2, char ch)
{
	n1->input = ch;
	n1->trans_state_index = n2->state_index;
}

//n1--��-->n2
void add(NFA_State* n1, NFA_State* n2)
{
	n1->ep_trans.insert(n2->state_index);
}

//�½�һ��NFA, ����NFA״̬������ȡ������״̬
NFA create_NFA(int sum)
{
	NFA nfa;
	nfa.head = &NFA_States[sum];
	nfa.tail = &NFA_States[sum + 1];
	return nfa;
}

//�ַ���s��nλ�������ch
void insert(string& s, int n, char ch)
{
	s += '#';
	for (int i = s.size() - 1; i > n; i--)
	{
		s[i] = s[i - 1];
	}
	s[n] = ch;
}

//���ȼ��Ƚϣ�Ϊ��������Ȩ�أ��Ƚ�Ȩ�ش�С���ж����ȼ�
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

//���ַ���s����Ԥ����
//��һλ�ǲ�������*��)���ҵڶ�λ�ǲ�������(֮��������ӷ�&
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



//��׺ת��׺
string infix_to_suffix(string infix_str)
{
	preprocess(infix_str);		

	string suffix_str;		//�����׺���ʽ
	stack<char> operator_stack;	//�����ջ

	for (int i = 0; i < infix_str.size(); i++)
	{
		if (infix_str[i] >= 'a' && infix_str[i] <= 'z')	//������ֱ�����
		{
			suffix_str += infix_str[i];
		}
		else							//�����
		{
			if (infix_str[i] == '(')			//��������ջ
			{
				operator_stack.push(infix_str[i]);
			}
			else if (infix_str[i] == ')')	//������
			{
				char temp = operator_stack.top();
				while (temp != '(')		//ջ��Ԫ�س�ջ��ֱ��ջ��Ϊ������
				{
					suffix_str += temp;
					operator_stack.pop();
					temp = operator_stack.top();
				}
				operator_stack.pop();			//�����ų�ջ
			}
			else	//����������
			{
				if (!operator_stack.empty())		//����ջ�ǿ�
				{
					char temp = operator_stack.top();
					while (priority(temp) >= priority(infix_str[i]))	//����ջ�����ȼ����ڵ��ڵ�ǰ�������
					{
						suffix_str += temp;
						operator_stack.pop();
						if (operator_stack.empty())		//�����ջΪ�ս���ѭ��
						{
							break;
						}
						else temp = operator_stack.top();
					}
					operator_stack.push(infix_str[i]);		//��ǰ�������ջ
				}
				else		//����ջΪ�գ��������ջ
				{
					operator_stack.push(infix_str[i]);
				}
			}
		}
	}

	//�����������ջ��Ϊ�գ���ջ�����
	while (!operator_stack.empty())
	{
		char temp = operator_stack.top();
		operator_stack.pop();
		suffix_str += temp;
	}

	cout << "������������������������������������������������������������������" << endl << endl;
	cout << "��׺���ʽΪ��" << infix_str << endl << endl;
	cout << "��׺���ʽΪ��" << suffix_str << endl << endl;

	return suffix_str;
}

//��׺���ʽתnfa
NFA str_to_NFA(string suffix_str)
{

	stack<NFA> NFA_stack;		

	for (int i = 0; i < suffix_str.size(); i++)		
	{
		//������
		if (suffix_str[i] >= 'a' && suffix_str[i] <= 'z')		
		{
			NFA nfa = create_NFA(nfa_state_num);		
			nfa_state_num += 2;		//״̬������2

			add(nfa.head, nfa.tail, suffix_str[i]);		//NFA��ͷָ��β�����ϵ�ֵΪsuffix_str[i]

			NFA_stack.push(nfa);		//NFA��ջ
		}
		else if (suffix_str[i] == '*')		//�հ������
		{

			NFA nfa_1 = create_NFA(nfa_state_num);		//�½�
			nfa_state_num += 2;					//״̬������2
			NFA nfa_2 = NFA_stack.top();			//��ջ�е���һ��NFA
			NFA_stack.pop();

			add(nfa_2.tail, nfa_1.head);			//2��β--��->1��ͷ
			add(nfa_2.tail, nfa_1.tail);			//2��β--��->1��β
			add(nfa_1.head, nfa_2.head);			//1��ͷ--��->2��ͷ
			add(nfa_1.head, nfa_1.tail);			//1��ͷ--��->1��β

			NFA_stack.push(nfa_1);			//�����ɵ�NFA��ջ*/
		}
		else if (suffix_str[i] == '|')		//�������
		{

			NFA nfa_1, nfa_2;			//��ջ�е�������NFA
			nfa_2 = NFA_stack.top();		//ջ��
			NFA_stack.pop();		

			nfa_1 = NFA_stack.top();	//��ջ��
			NFA_stack.pop();

			NFA nfa = create_NFA(nfa_state_num);	
			nfa_state_num += 2;			//״̬������2

			add(nfa.head, nfa_1.head);		//nfa��ͷ--��->1��ͷ
			add(nfa.head, nfa_2.head);		//nfa��ͷ--��->2��ͷ
			add(nfa_1.tail, nfa.tail);		//1��β--��->nfa��β
			add(nfa_2.tail, nfa.tail);		//2��β--��->nfa��β

			NFA_stack.push(nfa);		
		}
		else if (suffix_str[i] == '&')		//���������
		{

			NFA nfa, nfa_1, nfa_2;		
			nfa_2 = NFA_stack.top();		
			NFA_stack.pop();
			nfa_1 = NFA_stack.top();
			NFA_stack.pop();

			add(nfa_1.tail, nfa_2.head);				//1��β--��->2��ͷ

			nfa.head = nfa_1.head;					//nfa��ͷΪ1��ͷ
			nfa.tail = nfa_2.tail;					//nfa��βΪ2��β

			NFA_stack.push(nfa);		
		}
	}

	return NFA_stack.top();	//����ջ��Ԫ�ؼ�Ϊ���ɺõ�NFA
}

void print_NFA(NFA nfa)
{

	cout << "��������������������     NFA     ��������������������" << endl << endl;
	cout << "NFA�ܹ���" << nfa_state_num << "��״̬��" << endl;
	cout << "��̬Ϊ��" << nfa.head->state_index << "��"<<endl;
	cout << "��̬Ϊ��" << nfa.tail->state_index << "��" << endl;
	cout << "ת�ƺ���Ϊ��" << endl;

	for (int i = 0; i < nfa_state_num; i++)		
	{
		if (NFA_States[i].input != '#')		//���ϵ�ֵ���ǳ�ʼ�ġ�#��
		{
			cout << NFA_States[i].state_index << "-->'" << NFA_States[i].input << "'-->" << NFA_States[i].trans_state_index << '\t';
		}

		IntSet::iterator it;		//�����ŵ����״̬
		for (it = NFA_States[i].ep_trans.begin(); it != NFA_States[i].ep_trans.end(); it++)
		{
			cout << NFA_States[i].state_index << "-->'" << ' ' << "'-->" << *it << '\t';
		}

		cout << endl;
	}
}

//������������������������NFAתDFA������������������������

struct DFA_Edge			//ת����
{
	char input;			
	int trans;			
};

struct DFA_State		//DFA״̬
{

	bool is_end;	//�Ƿ�Ϊ��̬
	int index;		//״̬��
	IntSet closure;		//��-move()�հ�

	int edgeNum;		//�������
	DFA_Edge Edges[10];		//�����
}DFA_states[MAX];	//DFA״̬����
int DFA_state_num = 0;		//״̬����

struct DFA		
{
	int startState;		//��̬
	set<int> endStates;		//��̬��
	set<char> terminator;		//�ս����
	int trans[MAX][26];		//ת�ƾ���
};


//�ж��Ƿ�Ϊ��̬
bool IsEnd(NFA n, IntSet s)
{
	IntSet::iterator it;
	for (it = s.begin(); it != s.end(); it++)	//����nfa״̬��
	{
		if (*it == n.tail->state_index)			//�������nfa����̬
		{
			return true;	//��״̬Ϊ��̬
		}
	}

	return false;		/*�����������������̬������false*/
}

//���-cloure
IntSet ep_cloure(IntSet s)
{
	stack<int> ep_stack;		

	IntSet::iterator it;
	for (it = s.begin(); it != s.end(); it++)
	{
		ep_stack.push(*it);			//��״̬���е�ÿһ��Ԫ�ض���ջ
	}

	while (!ep_stack.empty())		
	{
		int temp = ep_stack.top();		//����һ��Ԫ��
		ep_stack.pop();

		IntSet::iterator iter;
		for (iter = NFA_States[temp].ep_trans.begin(); iter != NFA_States[temp].ep_trans.end(); iter++) //����ͨ������ת������״̬��
		{
			if (!s.count(*iter))				//�����ǰԪ��û���ڼ����г���
			{								
				s.insert(*iter);		//���뼯����
				ep_stack.push(*iter);		//��ջ
			}
		}
	}

	return s;		//���ئ�-cloure
}

//���-cloure(move(ch))
IntSet moveEpCloure(IntSet s, char ch)
{
	IntSet temp;

	IntSet::iterator it;
	for (it = s.begin(); it != s.end(); it++)		
	{
		if (NFA_States[*it].input == ch)		//��Ӧת�����ϵ�ֵΪch
		{
			temp.insert(NFA_States[*it].trans_state_index);		//�Ѹû�ͨ��chת������״̬���뼯��
		}
	}

	temp = ep_cloure(temp);		//��temp�Ħűհ�
	return temp;
}


DFA NFA_To_DFA(NFA n, string str)	
{
	cout << "��������������������     DFA     ��������������������" << endl << endl;

	int i;
	DFA d;
	set<IntSet> states;		//�ж����һ��״̬��s�Ħ�-cloure(move(ch))���Ƿ������״̬
	memset(d.trans, -1, sizeof(d.trans));	//��ʼ��ת�ƾ���

	for (i = 0; i < str.size(); i++)			//������׺���ʽ
	{
		if (str[i] >= 'a' && str[i] <= 'z')		//�����������뵽�ս������
		{
			d.terminator.insert(str[i]);
		}
	}

	d.startState = 0;		
	IntSet tempSet;
	tempSet.insert(n.head->state_index);		//��̬���뼯��

	DFA_states[0].closure = ep_cloure(tempSet);		//��dfa�ĳ�̬
	DFA_states[0].is_end = IsEnd(n, DFA_states[0].closure);		//�жϳ�̬�Ƿ�Ϊ��̬

	DFA_state_num++;		

	queue<int> q;
	q.push(d.startState);		//dfa�ĳ�̬�������

	while (!q.empty())	
	{
		int num = q.front();				//������Ԫ��
		q.pop();

		CharSet::iterator it;
		for (it = d.terminator.begin(); it != d.terminator.end(); it++)		//�����ս����
		{
			IntSet temp = moveEpCloure(DFA_states[num].closure, *it);		//����ÿ���ս���Ħ�-cloure(move(ch))
			if (!states.count(temp) && !temp.empty())	//״̬����Ϊ������֮ǰ�������״̬����ͬ���½�DFA״̬
			{
				states.insert(temp);				
				DFA_states[DFA_state_num].closure = temp;
				DFA_states[num].Edges[DFA_states[num].edgeNum].input = *it;				//״̬�������뼴Ϊ��ǰ�ս��
				DFA_states[num].Edges[DFA_states[num].edgeNum].trans = DFA_state_num;		//��ת�Ƶ���״̬Ϊ���һ��DFA״̬
				DFA_states[num].edgeNum++;	
				d.trans[num][*it - 'a'] = DFA_state_num;		//����ת�ƾ���

				DFA_states[DFA_state_num].is_end = IsEnd(n, DFA_states[DFA_state_num].closure);	//�Ƿ�Ϊ��̬

				q.push(DFA_state_num);		//��״̬�ż������
				DFA_state_num++;		
			}
			else			//���״̬����֮ǰ�����ĳ��״̬����ͬ
			{
				for (i = 0; i < DFA_state_num; i++)		
				{
					if (temp == DFA_states[i].closure)		//�ҵ���ü�����ͬ��DFA״̬
					{
						DFA_states[num].Edges[DFA_states[num].edgeNum].input = *it;		//״̬�������뼴Ϊ��ǰ�ս��
						DFA_states[num].Edges[DFA_states[num].edgeNum].trans = i;			//ת�Ƶ���״̬��Ϊi
						DFA_states[num].edgeNum++;					
						d.trans[num][*it - 'a'] = i;		//����ת�ƾ���
						break;
					}
				}
			}
		}
	}

	//������̬��
	for (i = 0; i < DFA_state_num; i++)	//����dfa������״̬
	{
		if (DFA_states[i].is_end == true)		//����̬
		{
			d.endStates.insert(i);		//����״̬�ż�����̬��
		}
	}

	return d;
}


void print_DFA(DFA d)
{
	cout << "DFA�ܹ���" << DFA_state_num << "��״̬��" << endl;
	cout << "��̬Ϊ" << d.startState << endl << endl;
	cout << "������ĸ��Ϊ�� ";
	set<char>::iterator it;
	for (it = d.terminator.begin(); it != d.terminator.end(); it++)
	{
		cout << *it << ' ';
	}
	cout << '}' << endl << endl;
	cout << "��̬��Ϊ�� ";
	IntSet::iterator iter;
	for (iter = d.endStates.begin(); iter != d.endStates.end(); iter++)
	{
		cout << *iter << ' ';
	}
	cout << '}' << endl << endl;
	cout << "ת�ƺ���Ϊ��" << endl;
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
	cout << endl << "ת�ƾ���Ϊ��" << endl << "     ";
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

//������������������������DFA����С��������������������������
IntSet s[MAX];					
DFA_State min_DFA_states[MAX];		
int min_DFA_state_num = 0;			//minDfa��״̬����/���ֳ��ļ�����

struct stateSet			//����״̬��
{
	int index;			//��ת������״̬�����
	IntSet s;		//dfa״̬��
};

//��ǰ��������Ϊcount������״̬n������״̬�����
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

//��С��DFA
DFA min_DFA(DFA d)
{

	int i, j;
	cout << endl << "��������������������     minDFA     ��������������������" << endl << endl;

	DFA minDfa;
	minDfa.terminator = d.terminator;		//�ս��������minDfa
	memset(minDfa.trans, -1, sizeof(minDfa.trans));		//��ʼ��minDfaת�ƾ���

	//��һ�λ��֣���̬�����̬�ֿ�
	bool endFlag = true;					//�ж�����״̬�Ƿ�ȫΪ��̬
	bool cutFlag = true;		//��һ���Ƿ�����µĻ��ֵı�־
	for (i = 0; i < DFA_state_num; i++)	
	{
		if (DFA_states[i].is_end == false)		//������̬
		{
			endFlag = false;						
			min_DFA_state_num = 2;					
			s[1].insert(DFA_states[i].index);		//��״̬��״̬�ż���s[1]
		}
		else						//����̬
		{
			s[0].insert(DFA_states[i].index);		//��״̬��״̬�ż���s[0]
		}
	}

	if (endFlag)			//����dfa״̬������̬
	{
		min_DFA_state_num = 1;			//ֻ��һ������
	}

	while (cutFlag)		//��һ�β����»���
	{
		int cutCount = 0;			//��Ҫ�����µĻ��ֵ�����
		for (i = 0; i < min_DFA_state_num; i++)			//����ÿ�����ּ���
		{
			CharSet::iterator it;
			for (it = d.terminator.begin(); it != d.terminator.end(); it++)		//����dfa���ս����
			{
				int setNum = 0;				//��ǰ�������е�״̬������
				stateSet temp[20];			//����״̬������������

				IntSet::iterator iter;
				for (iter = s[i].begin(); iter != s[i].end(); iter++)		//����ÿ��״̬��
				{
					bool epFlag = true;			//�ü������Ƿ����û�и��ս����Ӧ��ת������״̬
					for (j = 0; j < DFA_states[*iter].edgeNum; j++)		//������״̬�����б�
					{
						if (DFA_states[*iter].Edges[j].input == *it)		//����Ϊ���ս��
						{
							epFlag = false;			

							//�����״̬ת������״̬���ı��
							int transNum = find_set_num(min_DFA_state_num, DFA_states[*iter].Edges[j].trans);

							int curSetNum = 0;			//������������Ѱ���Ƿ���ڵ��������ŵ�״̬��
							while ((temp[curSetNum].index != transNum) && (curSetNum < setNum))
							{
								curSetNum++;
							}

							if (curSetNum == setNum)		//�������в����ڵ��������ŵ�״̬��
							{
								//���������½�״̬��
								temp[setNum].index = transNum;		//��ת������״̬��
								temp[setNum].s.insert(*iter);		

								setNum++;		//�������е�״̬��������һ
							}
							else			//�������д��ڵ��������ŵ�״̬��
							{
								temp[curSetNum].s.insert(*iter);	//���뵽��״̬����
							}
						}
					}

					if (epFlag)		//��״̬����������ս����Ӧ��ת����
					{
						int curSetNum = 0;
						while ((temp[curSetNum].index != -1) && (curSetNum < setNum))
						{
							curSetNum++;
						}

						if (curSetNum == setNum)	//������������״̬��
						{
							//���������½�״̬��
							temp[setNum].index = -1;			//ת�Ƶ���״̬�����Ϊ-1
							temp[setNum].s.insert(*iter);		
							setNum++;		
						}
						else			//�������д��ڵ��������ŵ�״̬��
						{
							temp[curSetNum].s.insert(*iter);	
						}
					}
				}
				if (setNum > 1)	//�������е�״̬����������1����ʾͬһ��״̬���е�Ԫ����ת������ͬ��״̬������Ҫ����
				{
					cutCount++;		
					//ÿ�黮�ִ����µ�dfa
					for (j = 1; j < setNum; j++)
					{
						IntSet::iterator t;
						for (t = temp[j].s.begin(); t != temp[j].s.end(); t++)
						{
							s[i].erase(*t);				//ԭ״̬��ɾ����״̬
							s[min_DFA_state_num].insert(*t);		//�µ�״̬�������״̬
						}
						min_DFA_state_num++;		
					}
				}
			}
		}
		if (cutCount == 0)		//���β���Ҫ���л���
		{
			cutFlag = false;
		}
	}

	//����ÿ�����ֺõ�״̬��
	for (i = 0; i < min_DFA_state_num; i++)
	{
		IntSet::iterator y;
		for (y = s[i].begin(); y != s[i].end(); y++)	
		{
			if (*y == d.startState)		//��С��DFA״̬Ϊ��̬
			{
				minDfa.startState = i;
			}
			if (d.endStates.count(*y))		//��С��DFA״̬ҲΪ��̬
			{
				min_DFA_states[i].is_end = true;
				minDfa.endStates.insert(i);		//��С��DFA״̬������̬��
			}

			for (j = 0; j < DFA_states[*y].edgeNum; j++)		//������DFA״̬��ÿ������Ϊ��С��DFA������
			{
				for (int t = 0; t < min_DFA_state_num; t++)
				{
					if (s[t].count(DFA_states[*y].Edges[j].trans))
					{
						bool haveEdge = false;		//�жϸû��Ƿ��Ѿ������ı�־
						for (int l = 0; l < min_DFA_states[i].edgeNum; l++)	
						{		
							if ((min_DFA_states[i].Edges[l].input == DFA_states[*y].Edges[j].input) && (min_DFA_states[i].Edges[l].trans == t))
							{
								haveEdge = true;	
							}
						}
						if (!haveEdge)		//����һ���µĻ�
						{
							min_DFA_states[i].Edges[min_DFA_states[i].edgeNum].input = DFA_states[*y].Edges[j].input;	
							min_DFA_states[i].Edges[min_DFA_states[i].edgeNum].trans = t;	
							minDfa.trans[i][DFA_states[*y].Edges[j].input - 'a'] = t;	//����ת�ƾ���
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
	cout << "minDFA�ܹ���" << min_DFA_state_num << "��״̬��" << endl;
	cout << "��̬Ϊ" << d.startState << endl << endl;

	cout << "������ĸ��Ϊ�� ";
	set<char>::iterator it;
	for (it = d.terminator.begin(); it != d.terminator.end(); it++)
	{
		cout << *it << ' ';
	}
	cout << '}' << endl << endl;

	cout << "��̬��Ϊ�� ";
	IntSet::iterator iter;
	for (iter = d.endStates.begin(); iter != d.endStates.end(); iter++)
	{
		cout << *iter << ' ';
	}
	cout << '}' << endl << endl;

	cout << "ת�ƺ���Ϊ��" << endl;
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

	cout << endl << "ת�ƾ���Ϊ��" << endl << "     ";
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
	cout << endl << "������������������������������������������������������������������";
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

