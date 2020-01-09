#include<iostream>
#include<conio.h>
#include<string>
#include<Windows.h>
#include<time.h>
using namespace std;


class Snake
{
private:
	int source = 0;
	string Bady[40][40] = { " " };
	struct bady
	{
		int x;
		int y;
		bady*next;
	};
	bady*head;
	bady*pStart = new bady;
	bady*pEnd = pStart;
	bady*last = pStart;
	struct Food
	{
		int x;
		int y;
	};
	Food*food = new Food;

public:
	void SnakeBady()
	{
		head = NULL;
		for (int i = 2; i < 8; i++)//��ʼ���ߵ��������Ϸ���
		{
			pStart->y = i;
			pStart->x = 4;
			if (head == NULL)
				head = pStart;
			else
				pEnd->next = pStart;
			last = pEnd;
			pEnd = pStart;
			if (i == 7)
				pEnd->next = NULL;
			pStart = new bady;
		}
		bady *p = head;
		for (int i = 0; i < 30; i++)//����
			for (int j = 0; j < 30; j++)
			{
				if (i == 0 || i == 29 || j == 0 || j == 29)
					Bady[i][j] = { "o" };
				else
					Bady[i][j] = { " " };
			}
		while (p)//����
		{
			Bady[p->x][p->y] = { "a" };
			p = p->next;
		}
		DrawBady();
	}
	void DrawBady()//���ƴ���
	{
		cout << "\n\n\n\n\n\n\t\t\t\t\tSource:" << source << endl;
		for (int i = 0; i < 30; i++)
		{
			cout << "\t\t";
			for (int j = 0; j < 30; j++)
				//cout << Bady[i][j];
				printf("%s", Bady[i][j].c_str());//��˵printf��ӡ�ַ�Ч�ʸ���
			cout << endl;
		}
		cout << endl << "\t\tW��S��A��D���Ʒ���\n\t\t�����������ͣ\n\t\t����Q�˳���Ϸ" << endl;
	}
	void Delete(int x,int& time)//����ͷβ//ɾ�����//�ж��Ƿ�Ե�ʳ��//�ж��Ƿ���Լ�
	{
		bady*ps = head;
		if (pEnd->x == food->x&&pEnd->y == food->y)
		{
			cout << "\a";//ring
			/*
			*����Ե�������ɾ����β
			*/
			randfood();//ˢ������
			gotoxy(6, 50);
			cout<<"\b\b\b"<<++source;//���ӵ÷�
			switch (source)
			{
			case 10:time = time * 2 / 3; break;
			case 20:time = time * 4 / 5; break;
			case 30:time = time * 5 / 6; break;
			case 40:time = time * 5 / 6; break;
			default:break;
			}
		}
		else
		{
			Bady[pEnd->x][pEnd->y] = { "a" };
			gotoxy(pEnd->x+7, pEnd->y+17);
			cout << "\b" << Bady[pEnd->x][pEnd->y];
			Bady[head->x][head->y] = { " " };
			gotoxy(head->x+7, head->y+17);
			cout << "\b" << Bady[head->x][head->y];
			head = head->next;
			delete ps;//ɾ��β��
		}
		bady*temp = new bady;//��ͷ������µĽ��
		temp->x = pEnd->x;
		temp->y = pEnd->y;
		temp->next = NULL;
		switch (x)
		{
		case 1:pEnd->x++; break;
		case 2:pEnd->x--; break;
		case 3:pEnd->y++; break;
		case 4:pEnd->y--; break;
		default:cout << "����" << endl; break;
		}
		last = pEnd;
		pEnd->next = temp;
		pEnd = temp;
	}
	int judge(char cho,int& time)//�жϼ�ֵ
	{
		switch (cho)
		{
		case'r':
		case'R':
			return 5;
		case'q':
		case'Q':
			return 0;
		case'w':
		case'W':
			//�ж��Ƿ��뵱ǰǰ�������෴
			if (--pEnd->x == last->x)
			{
				against(cho, time);
				return 1;
			}
			else if ( pEnd->x == 0 ||pEnd->x==29 || Bady[pEnd->x][pEnd->y] == "a")
				return 0;
			Delete(1,time);
			Sleep(time);
			//DrawBady();
			return 1;
		case'a':
		case'A':
			if(--pEnd->y == last->y)
			{
				against(cho, time);
				return 1;
			}
			if ( pEnd->y == 0 || pEnd->y == 29 || Bady[pEnd->x][pEnd->y] == "a")
				return 0;
			Delete(3,time);
			Sleep(time);
			//DrawBady();
			return 1;
		case's':
		case'S':
			if(++pEnd->x == last->x)
			{
				against(cho, time);
				return 1;
			}
			if ( pEnd->x == 0 || pEnd->x == 29 || Bady[pEnd->x][pEnd->y] == "a")
				return 0;
			Delete(2,time);
			Sleep(time);
			//DrawBady();
			return 1;
		case'd':
		case'D':
			if(++pEnd->y == last->y)
			{
				against(cho, time);
				return 1;
			}
			if ( pEnd->y == 0 || pEnd->y == 29 || Bady[pEnd->x][pEnd->y] == "a")
				return 0;
			Delete(4,time);
			Sleep(time);
			//DrawBady();
			return 1;
		default:
			return 1;
		}
	}
	void against(char cho, int time)
	{
		switch (cho)
		{
		case'w':
		case'W':
			judge('s', time);
			break;
		case'a':
		case'A':
			judge('d', time);
			break;
		case's':
		case'S':
			judge('w', time);
			break;
		case'd':
		case'D':
			judge('a', time);
			break;
		default:
			break;
		}
	}
	Food randfood()
	{
		//time_t t;
		//tm tim;
		//time(&t);
		//localtime_s(&tim,&t);
		//srand(unsigned(time(0)));//��ͼ��ϵͳʱ����ˢ������//��û����//����һ�ξ����˶�ε���û��Ҫ��֮ǰû����������
		food->x = (rand() % 27) + 1;
		food->y = (rand() % 27) + 1;
		bady*temp = new bady;
		temp = head;
		while (temp)
		{
			if (food->x == temp->x || food->y == temp->y)//�ж��Ƿ���ߵ������غ�
				randfood();
			else
				temp = temp->next;
		}
		Bady[food->x][food->y] = { "o" };
		gotoxy(food->x+7, food->y+17);
		cout << "\b" << Bady[food->x][food->y];
		return *food;
	}
	void gotoxy(int x, int y)//�ƶ����api
	{
		HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);//д��ȫ�֣��������и���һ��
		COORD c = { (short)y, (short)x };
		SetConsoleCursorPosition(hOut, c);
	}

};