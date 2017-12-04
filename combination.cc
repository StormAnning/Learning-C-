#include <iostream>
using namespace std;

//abc
///a
///ab
///abc
////*

//bc
///b
///bc
////*

//c
///c

//comb(0,{abc}, {})
//{
	//output = {a}
	//PRINT a
		//combination(1, {b,c}, {a})
		//{
			//output = {a,b}
			//PRINT ab
				//combination(2, {c}, {a,b})
			//REMOVE LAST - output = {a}

			//output = {a,c}
			//PRINT ac
				//End recursion
			//REMOVE LAST - output = {a}
		//}
	//REMOVE LAST - output = {}

	//output = {b}
	//PRINT b
		//combination(2, {c}, {b})
	//REMOVE LAST - output = {}

	//output = {c}
	//PRINT c 
		// END recursion
	//REMOVE LAST - output = {}
//}

//a.   .b.   .c.
//a     b     c           
//ab    bc                           
//abc
//ac              

void indent(int n){
	for (int i=0; i<n;i++){
		cout << "  ";
	}
}

void combination(int startPos, string str, string output){
	for(int i=startPos; i < str.length(); i++){
		output += str[i];
		indent(startPos);
		cout << output << endl;
		if(i < str.length()){
			combination(i + 1, str, output);
		}
		output = string(output).erase(output.length()-1,1);
	}
}

//w,wx,wxy,wxyz, wy,wyz, wz
//x,xy,xyz,xz -no w
//y,yz - no x
//z - no z

int main(int argc, char const *argv[])
{
	combination(0,"abc", "");
	return 0;
}
