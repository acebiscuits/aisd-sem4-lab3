#include<windows.h>
#include<stdio.h>
#include<iostream>
#include<conio.h>
#include<string>
#include<vector>
#include"graph.h"
#define ESC 27
#define UP 72
#define DOWN 80
#define ENTER 13
#define ACT_COL 11
#define DEF_COL 15
#define RED 12
#define GREEN 10
using namespace std;
HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

void ConsoleCursorVisible(bool show, short size)
{
	CONSOLE_CURSOR_INFO structCursorInfo;
	GetConsoleCursorInfo(hStdOut, &structCursorInfo);
	structCursorInfo.bVisible = show;
	structCursorInfo.dwSize = size;
	SetConsoleCursorInfo(hStdOut, &structCursorInfo);
}

int s_choice(int col = DEF_COL, const char* e = "nothing")
{
	string choice_menu[] = { "ввести опять","бэк (ESC)" };
	ConsoleCursorVisible(false, 100);
	int active_menu = 0;
	char ch;
	while (1)
	{
		system("cls");
		SetConsoleTextAttribute(hStdOut, col);
		cout << e << endl << endl;
		for (int i = 0; i < size(choice_menu); i++)
		{
			if (i == active_menu) SetConsoleTextAttribute(hStdOut, ACT_COL);
			else SetConsoleTextAttribute(hStdOut, DEF_COL);
			cout << choice_menu[i] << endl;
		}
		ch = _getch();
		if (ch == -32) ch = _getch();
		switch (ch)
		{
		case ESC:
			return 2;
		case UP:
			if (active_menu > 0) active_menu--;
			system("cls");
			break;
		case DOWN:
			if (active_menu < size(choice_menu) - 1) active_menu++;
			system("cls");
			break;
		case ENTER:
			switch (active_menu)
			{
			case 1:
				return 2;
			case 0:
				return 1;
			}
		default:
			break;
		}
	}
}

template<typename Vertex_t, typename Distance_t>
void add_v(Graph<Vertex_t, Distance_t>& gr)
{
	while (1)
	{
		Vertex_t new_v;
		while (1)
		{
			SetConsoleTextAttribute(hStdOut, DEF_COL);
			system("cls");
			cout << "enter value: ";
			ConsoleCursorVisible(true, 100);
			int choice = 0;
			while (!(cin >> new_v) || (cin.peek() != '\n'))
			{
				cin.clear();
				while (cin.get() != '\n');

				choice = s_choice(RED, "Text was entered");

				break;
			}
			if (choice == 1) continue;
			else if (choice == 2) return;
			else break;
		}
		try
		{
			gr.add_vertex(new_v);
		}
		catch (const char* e)
		{
			int choice = s_choice(RED, e);
			if (choice == 2) return;
			else continue;
		}
		return;
	}
}

template<typename Vertex_type, typename Distance_type>
void check_v(Graph<Vertex_type, Distance_type>& gr)
{
	while (1)
	{
		Vertex_type new_v;
		while (1)
		{
			SetConsoleTextAttribute(hStdOut, DEF_COL);
			system("cls");
			ConsoleCursorVisible(true, 100);
			cout << "enter value";
			int choice = 0;
			while (!(cin >> new_v) || (cin.peek() != '\n'))
			{
				cin.clear();
				while (cin.get() != '\n');

				choice = s_choice(RED, "Text vas entered");

				break;
			}
			if (choice == 1) continue;
			else if (choice == 2) return;
			else
			{
				cout << endl;
				break;
			}
		}
		try
		{
			int choice;
			if (gr.has_vertex(new_v)) choice = s_choice(GREEN, "This graph has this vertex");
			else choice = s_choice(RED, "This graph does not have this vertex");
			if (choice == 2)return;
			else continue;
		}
		catch (const char* e)
		{
			int choice = s_choice(RED, e);
			if (choice == 2) return;
			else continue;
		}
		return;
	}
}

template<typename Vertex_type, typename Distance_type>
void del_v(Graph<Vertex_type, Distance_type>& gr)
{
	while (1)
	{
		Vertex_type new_v;
		while (1)
		{
			SetConsoleTextAttribute(hStdOut, DEF_COL);
			system("cls");
			cout << "enter value: ";
			ConsoleCursorVisible(true, 100);
			int choice = 0;
			while (!(cin >> new_v) || (cin.peek() != '\n'))
			{
				cin.clear();
				while (cin.get() != '\n');

				choice = s_choice(RED, "Text was entered");

				break;
			}
			if (choice == 1) continue;
			else if (choice == 2) return;
			else break;
		}
		try
		{
			gr.remove_vertex(new_v);
		}
		catch (const char* e)
		{
			int choice = s_choice(RED, e);
			if (choice == 2) return;
			else continue;
		}
		return;
	}
}

template<typename Vertex_type, typename Distance_type>
void add_e(Graph<Vertex_type, Distance_type>& gr)// Äîäåëàé êóðñîð è íîðìàëüíûé endl
{
	while (1)
	{
		Vertex_type from, to;
		Distance_type dis;
		while (1)
		{
			SetConsoleTextAttribute(hStdOut, DEF_COL);
			system("cls");
			ConsoleCursorVisible(true, 100);
			cout << "enter from: ";
			int choice = 0;
			while (!(cin >> from) || (cin.peek() != '\n'))
			{
				cin.clear();
				while (cin.get() != '\n');

				choice = s_choice(RED, "Text was entered");

				break;
			}
			//if (choice == 0)
			//{
			//	if (!gr.has_vertex(from)) choice = s_choice(RED, "No vertex");
			//}
			if (choice == 1) continue;
			else if (choice == 2) return;
			else
			{
				cout << endl;
				break;
			}
		}
		while (1)
		{
			SetConsoleTextAttribute(hStdOut, DEF_COL);
			system("cls");
			ConsoleCursorVisible(true, 100);
			cout << "enter to: ";
			int choice = 0;
			while (!(cin >> to) || (cin.peek() != '\n'))
			{
				cin.clear();
				while (cin.get() != '\n');

				choice = s_choice(RED, "Text was entered");

				break;
			}
			//if (choice == 0)
			//{
			//	if (!gr.has_vertex(to)) choice = s_choice(RED, "No vertex");
			//}
			if (choice == 1) continue;
			else if (choice == 2) return;
			else
			{
				cout << endl;
				break;
			}
		}
		while (1)
		{
			SetConsoleTextAttribute(hStdOut, DEF_COL);
			system("cls");
			ConsoleCursorVisible(true, 100);
			cout << "enter distance: ";
			int choice = 0;
			while (!(cin >> dis) || (cin.peek() != '\n'))
			{
				cin.clear();
				while (cin.get() != '\n');

				choice = s_choice(RED, "Text was entered");

				break;
			}
			if (choice == 1) continue;
			else if (choice == 2) return;
			else break;
		}
		try
		{
			gr.add_edge(from, to, dis);
		}
		catch (const char* e)
		{
			int choice = s_choice(RED, e);
			if (choice == 2) return;
			else continue;
		}
		return;
	}
}

template<typename Vertex_type, typename Distance_type>
void check_e(Graph<Vertex_type, Distance_type>& gr, bool dist)
{
	while (1)
	{
		Vertex_type from, to;
		Distance_type dis;
		while (1)
		{
			SetConsoleTextAttribute(hStdOut, DEF_COL);
			system("cls");
			ConsoleCursorVisible(true, 100);
			cout << "enter from: ";
			int choice = 0;
			while (!(cin >> from) || (cin.peek() != '\n'))
			{
				cin.clear();
				while (cin.get() != '\n');

				choice = s_choice(RED, "Text was entered");

				break;
			}
			if (choice == 0)
			{
				if (!gr.has_vertex(from)) choice = s_choice(RED, "No vertex");
			}
			if (choice == 1) continue;
			else if (choice == 2) return;
			else
			{
				cout << endl;
				break;
			}
		}
		while (1)
		{
			SetConsoleTextAttribute(hStdOut, DEF_COL);
			system("cls");
			ConsoleCursorVisible(true, 100);
			cout << "enter to: ";
			int choice = 0;
			while (!(cin >> to) || (cin.peek() != '\n'))
			{
				cin.clear();
				while (cin.get() != '\n');

				choice = s_choice(RED, "Text was entered");

				break;
			}
			if (choice == 0)
			{
				if (!gr.has_vertex(to)) choice = s_choice(RED, "No vertex");
			}
			if (choice == 1) continue;
			else if (choice == 2) return;
			else
			{
				cout << endl;
				break;
			}
		}
		if (dist)
		{
			while (1)
			{
				SetConsoleTextAttribute(hStdOut, DEF_COL);
				system("cls");
				ConsoleCursorVisible(true, 100);
				cout << "enter distance: ";
				int choice = 0;
				while (!(cin >> dis) || (cin.peek() != '\n'))
				{
					cin.clear();
					while (cin.get() != '\n');

					choice = s_choice(RED, "Text was entered");

					break;
				}
				if (choice == 1) continue;
				else if (choice == 2) return;
				else break;
			}
		}
		try
		{
			int choice;
			if (!dist)
			{
				if (gr.has_edge(from, to)) choice = s_choice(GREEN, "This graph has this vertex");
				else choice = s_choice(RED, "This graph does not have this vertex");
				if (choice == 2)return;
				else continue;
			}
			else
			{
				if (gr.has_edge(from, to, dis)) choice = s_choice(GREEN, "This graph has this vertex");
				else choice = s_choice(RED, "This graph does not have this vertex");
				if (choice == 2)return;
				else continue;
			}
		}
		catch (const char* e)
		{
			int choice = s_choice(RED, e);
			if (choice == 2) return;
			else continue;
		}
		return;
	}
}

template<typename Vertex_type, typename Distance_type>
void del_e(Graph<Vertex_type, Distance_type>& gr, bool dist)
{
	while (1)
	{
		Vertex_type from, to;
		Distance_type dis;
		while (1)
		{
			SetConsoleTextAttribute(hStdOut, DEF_COL);
			system("cls");
			ConsoleCursorVisible(true, 100);
			cout << "enter from: ";
			int choice = 0;
			while (!(cin >> from) || (cin.peek() != '\n'))
			{
				cin.clear();
				while (cin.get() != '\n');

				choice = s_choice(RED, "Text was entered");

				break;
			}
			if (choice == 0)
			{
				if (!gr.has_vertex(from)) choice = s_choice(RED, "No vertex");
			}
			if (choice == 1) continue;
			else if (choice == 2) return;
			else
			{
				cout << endl;
				break;
			}
		}
		while (1)
		{
			SetConsoleTextAttribute(hStdOut, DEF_COL);
			system("cls");
			ConsoleCursorVisible(true, 100);
			cout << "enter to: ";
			int choice = 0;
			while (!(cin >> to) || (cin.peek() != '\n'))
			{
				cin.clear();
				while (cin.get() != '\n');

				choice = s_choice(RED, "Text was entered");

				break;
			}
			if (choice == 0)
			{
				if (!gr.has_vertex(to)) choice = s_choice(RED, "No vertex");
			}
			if (choice == 1) continue;
			else if (choice == 2) return;
			else
			{
				cout << endl;
				break;
			}
		}
		if (dist)
		{
			while (1)
			{
				SetConsoleTextAttribute(hStdOut, DEF_COL);
				system("cls");
				ConsoleCursorVisible(true, 100);
				cout << "enter distance: ";
				int choice = 0;
				while (!(cin >> dis) || (cin.peek() != '\n'))
				{
					cin.clear();
					while (cin.get() != '\n');

					choice = s_choice(RED, "Text was entered");

					break;
				}
				if (choice == 1) continue;
				else if (choice == 2) return;
				else break;
			}
		}
		try
		{
			if (!dist)
			{
				gr.remove_edge(from, to);
			}
			else
			{
				gr.remove_edge(from, to, dis);
			}
		}
		catch (const char* e)
		{
			int choice = s_choice(RED, e);
			if (choice == 2) return;
			else continue;
		}
		return;
	}
}

template<typename Vertex_t, typename Distance_t>
void shortest_path(Graph<Vertex_t, Distance_t>& gr)
{
	while (1)
	{
		Vertex_t from, to;
		pair<pair<Distance_t, int>, vector<Vertex_t>> vec;
		//pair<pair<Distance_t, int>, vector<Vertex_t>> vec_with_cyrc;
		while (1)
		{
			SetConsoleTextAttribute(hStdOut, DEF_COL);
			system("cls");
			ConsoleCursorVisible(true, 100);
			cout << "enter from: ";
			int choice = 0;
			while (!(cin >> from) || (cin.peek() != '\n'))
			{
				cin.clear();
				while (cin.get() != '\n');

				choice = s_choice(RED, "Text was entered");

				break;
			}
			if (choice == 0)
			{
				if (!gr.has_vertex(from)) choice = s_choice(RED, "No vertex");
			}
			if (choice == 1) continue;
			else if (choice == 2) return;
			else
			{
				cout << endl;
				break;
			}
		}
		while (1)
		{
			SetConsoleTextAttribute(hStdOut, DEF_COL);
			system("cls");
			ConsoleCursorVisible(true, 100);
			cout << "enter to: ";
			int choice = 0;
			while (!(cin >> to) || (cin.peek() != '\n'))
			{
				cin.clear();
				while (cin.get() != '\n');

				choice = s_choice(RED, "Text was entered");

				break;
			}
			if (choice == 0)
			{
				if (!gr.has_vertex(to)) choice = s_choice(RED, "No vertex");
			}
			if (choice == 1) continue;
			else if (choice == 2) return;
			else
			{
				cout << endl;
				break;
			}
		}
		try
		{
			vec = gr.shortest_path(from, to, false);
			//vec_with_cyrc = gr.shortest_path(from, to, true);
			system("cls");
			SetConsoleTextAttribute(hStdOut, DEF_COL);
			if (vec.first.second == 0)
			{
				cout << "path: ";
				for (auto i = vec.second.begin(); i != vec.second.end(); i++)
				{
					cout << *(i);
					if (i + 1 != vec.second.end()) cout << "-";
				}
				cout << endl << "distance: " << vec.first.first;
			}
			else if(vec.first.second == 1)
			{
				cout << "вершина недостижима";

			}
			else
			{
				cout << "на пути есть минусовой цикл";
			}
			char ch = _getch();
		}
		catch (const char* e)
		{
			int choice = s_choice(RED, e);
			if (choice == 2) return;
			else continue;
		}
		return;
	}


}

template<typename Vertex_t, typename Distance_t>
void walk(Graph<Vertex_t, Distance_t>& gr)
{
	while (1)
	{
		Vertex_t vertex_start;
		vector<Vertex_t> vec;
		//pair<pair<Distance_t, int>, vector<Vertex_t>> vec_with_cyrc;
		while (1)
		{
			SetConsoleTextAttribute(hStdOut, DEF_COL);
			system("cls");
			ConsoleCursorVisible(true, 100);
			cout << "enter vertex: ";
			int choice = 0;
			while (!(cin >> vertex_start) || (cin.peek() != '\n'))
			{
				cin.clear();
				while (cin.get() != '\n');

				choice = s_choice(RED, "Text was entered");

				break;
			}
			if (choice == 0)
			{
				if (!gr.has_vertex(vertex_start)) choice = s_choice(RED, "No vertex");
			}
			if (choice == 1) continue;
			else if (choice == 2) return;
			else
			{
				cout << endl;
				break;
			}
		}
		
		try
		{
			vec = gr.walk(vertex_start);
			//vec_with_cyrc = gr.shortest_path(from, to, true);
			system("cls");
			SetConsoleTextAttribute(hStdOut, DEF_COL);

				cout << "path: ";
				for (auto i = vec.begin(); i != vec.end(); i++)
				{
					cout << *(i);
					if (i + 1 != vec.end()) cout << "-";
				}
				
			
			char ch = _getch();
		}
		catch (const char* e)
		{
			int choice = s_choice(RED, e);
			if (choice == 2) return;
			else continue;
		}
		return;
	}


}

template<typename Vertex_t, typename Distance_t>
void lasttask(Graph<Vertex_t, Distance_t>& gr)
{
	while (1)
	{
		pair<Vertex_t, Distance_t> point;

			SetConsoleTextAttribute(hStdOut, DEF_COL);
			system("cls");
			ConsoleCursorVisible(true, 100);



		try
		{
			point = gr.task();
			//vec_with_cyrc = gr.shortest_path(from, to, true);
			system("cls");
			SetConsoleTextAttribute(hStdOut, DEF_COL);

			cout << "point: ";
				cout << point.first<<endl;
				cout << "avg dist: ";
				cout << point.second << endl;

			


			char ch = _getch();
		}
		catch (const char* e)
		{
			int choice = s_choice(RED, e);
			if (choice == 2) return;
			else continue;
		}
		return;
	}
}

int main()
{
	setlocale(0, "rus");
	string main_menu[] = { "Добавить вершину","проверка вершины","удалить вершину","добавить ребро","проверить ребро с расстоянием","проверить ребро без расстояния",
		"удалить ребро с расстоянием","удалить ребро без расстояния","кратчайший путь","обход","задание","Выход (ESC)"};
	int active_menu = 0;
	char ch;
	Graph<int> gr;
	while (1)
	{
		system("cls");
		ConsoleCursorVisible(false, 100);
		if (!gr._empty())
		{
			cout << "граф:" << endl;
			gr.print();
			cout << endl;
		}
		else
		{
			cout << "Граф пустой" << endl << endl;
		}


		for (int i = 0; i < size(main_menu); i++)
		{
			if (i == active_menu) SetConsoleTextAttribute(hStdOut, ACT_COL);
			else SetConsoleTextAttribute(hStdOut, DEF_COL);
			cout << main_menu[i] << endl;
		}

		ch = _getch();
		if (ch == -32) ch = _getch();

		switch (ch)
		{
		case ESC:
			SetConsoleTextAttribute(hStdOut, DEF_COL);
			return 0;
		case UP:
			if (active_menu > 0) active_menu--;
			system("cls");
			break;
		case DOWN:
			if (active_menu < size(main_menu) - 1) active_menu++;
			system("cls");
			break;
		case ENTER:
			switch (active_menu)
			{
			case 0:
				add_v(gr);
				break;
			case 1:
				check_v(gr);
				break;
			case 2:
				del_v(gr);
				break;
			case 3:
				add_e(gr);
				break;
			case 4:
				check_e(gr, true);
				break;
			case 5:
				check_e(gr, false);
				break;
			case 6:
				del_e(gr, true);
				break;
			case 7:
				del_e(gr, false);
				break;
			case 8:
				shortest_path(gr);
				break;
			case 9:
				walk(gr);
				break;
			case 10:
				lasttask(gr);
				break;
			case size(main_menu) - 1:
				SetConsoleTextAttribute(hStdOut, DEF_COL);
				return 0;
			}
		default:
			break;
		}
	}
}