/**
 * Савченко И.В.
 * М8О-208Б-19
 * https://github.com/ShyFly46/oop_exercise_07
 *
 * Вариант 1:
 * "Графический векторный редактор"
 * Треугольник, квадрат, прямоугольник
 **/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "point.h"
#include "figures.h"
#include "factory.h"

using namespace std;

struct FileWork {
	vector<Figure*> &vec;
	
	FileWork(vector<Figure*> &v)
		: vec(v)
	{}
	
	void Write(const string& fName){
		ofstream myFile(fName);
		for(Figure* i : vec){
			i->serialize(myFile);
		}
		myFile.close();
		cout
			<< "Saved as "
			<< fName
			<< '\n';
	}
	
	void Read(const string& fName){
		ifstream myFile(fName);
		if(!myFile.is_open()){
			cout << "File not found\n";
			return;
		}
		
		vec.clear();
		
		char figType;
		Point a, b, c;
		Factory fac;
		
		while(myFile.get(figType)){
			switch(figType){
				case 't':
					myFile >> a >> b >> c;
					vec.push_back(fac.createTri(a, b, c));
					break;
				case 'q':
					myFile >> a >> c;
					vec.push_back(fac.createSq(a, c));
					break;
				case 'r':
					myFile >> a >> b >> c;
					vec.push_back(fac.createRct(a, b, c));
					break;
				case ' ':
				case '\t':
				case '\n':
					break;
				default:
					cout << "File not supported\n";
					cout << "Read "
					     << vec.size()
						 << " figures so far\n";
						 myFile.close();
						 return;
			}
		}
		
		myFile.close();
		cout
			<< "Read successful ("
			<< vec.size()
			<< " figures)\n";
	}
};

struct LastOp{
	enum oper{NUL, ADD, DEL};
	oper op = NUL;
	Figure* ptr = nullptr;
	
	void Update(Figure* newPtr = nullptr){
		delete ptr;
		ptr = newPtr;
		if(!newPtr){
			op = ADD;
			return;
		}
		op = DEL;
	}
};

void help(){
	cout
		<< "    point is 2 numbers\n"
		<< "t         - triangle\n"
		<< "q         - square\n"
		<< "r         - rectangle\n"
		<< "l         - list figures\n"
		<< "d <index> - delete\n"
		<< "u         - undo last action\n"
		<< "s <name>  - save to file\n"
		<< "o <name>  - open from file\n"
		<< "x         - exit\n";
}

int main(){
	Factory myFac;
	vector<Figure*> figVec;
	FileWork fileW(figVec);
	Figure* fig;
	
	LastOp lOp;
	
	char cmd;
	
	help();
	
	cout << "> ";
	while(cin >> cmd){
		switch(cmd){
			case 'h':
				help();
				break;
			case 't':
				{
					cout << "Triangle\n";
					Point a, b, c;
					cout << "  a: ";
					cin >> a;
					cout << "  b: ";
					cin >> b;
					cout << "  c: ";
					cin >> c;
					
					fig = myFac.createTri(a, b, c);
					figVec.push_back(fig);
					
					lOp.Update(nullptr);
				}
				break;
			case 'q':
				{
					cout << "Square\n";
					Point a, c;
					cout << "  a: ";
					cin >> a;
					cout << "  c: ";
					cin >> c;
					
					fig = myFac.createSq(a, c);
					figVec.push_back(fig);
					
					lOp.Update();
				}
				break;
			case 'r':
				{
					cout << "Rect\n";
					Point a, b;
					cout << "  a: ";
					cin >> a;
					cout << "  b: ";
					cin >> b;
					cout << "  ratio: ";
					float r;
					cin >> r;
					
					fig = myFac.createRct(a, b, r);
					figVec.push_back(fig);
					
					lOp.Update();
				}
				break;
			case 'd':
				{
					unsigned int index;
					cin >> index;
					try{
						Figure *ptr = figVec.at(index);
						lOp.Update(ptr);
						figVec.erase(figVec.begin() + index);
					}
					catch(out_of_range& e){
						cout << "Out of range\n";
					}
				}
				break;
			case 'u':
				{
					if(lOp.op == LastOp::ADD){
						delete figVec.back();
						figVec.pop_back();
						cout << "Addition canceled\n";
					} else if(lOp.op == LastOp::DEL){
						figVec.push_back(lOp.ptr);
						cout << "Deletion canceled\n";
					} else {
						cout << "Nothing to undo\n";
					}
					lOp.op = LastOp::NUL;
					lOp.ptr = nullptr;
				}
				break;
			case 'l':
				{
					int ind = 0;
					for(Figure* i : figVec){
						cout << ind << '\t';
						i->print();
						++ind;
					}
				}
				break;
			case 's':
				{
					string name;
					cin >> name;
					fileW.Write(name);
				}
				break;
			case 'o':
				{
					string name;
					cin >> name;
					fileW.Read(name);
				}
				break;
			case 'x':
				cout << "exit\n";
				return 0;
			default:
				cout << "???\n";
				break;
		}
		cout << "\n> ";
	}
}