#include <iostream>
#include <stdlib.h>


std::string reverseWordsGeneral(std::string string){
	const char *str = string.c_str();
	int n = string.length();
	//allocate a buffer
	char buffer[n+1];
	int readPosition = n-1;
	int writePosition = 0;
	int endOfLastWordPos;
	int startOfWordReadPos;
	while(readPosition >= 0){
		if(str[readPosition] == ' '){
			buffer[writePosition++] = str[readPosition--];
		}else{ // non character word

			/* Store position of end of the word we've found*/
			endOfLastWordPos = readPosition;

			/* Scan to next non-word character - to identify start of this word */
			while(str[readPosition] != ' ' && readPosition >= 0){
				readPosition--;
			}

			/* tokenReadPos went past the start of the word */ 
			startOfWordReadPos = readPosition + 1;

			/* Copy the characters of the word */
			while(startOfWordReadPos <= endOfLastWordPos){
				buffer[writePosition++] = str[startOfWordReadPos++];
			}
		}
	}
	string = buffer;
	return string;
}

void reverseWord(char word[],int start, int end){
	char temp;
	while(start <end){
		 temp = word[start];
		 word[start] = word[end];
		 word[end] = temp;
		 start++;
		 end--;
	}
}

std::string reverseWords(std::string string){
	const char *strC = string.c_str();
	int n = string.length();

	char str[n+1];
	for(int i =0; i < n; i++){
		str[i] = strC[(n-1) - i];
	}
	//allocate a buffer
	int start = 0, end = 0;
	while(end < n){
		if(str[end] != ' '){
			start = end;
			while(end < n && str[end] != ' '){
				end++;
			}
			end --; 
			reverseWord(str,start,end);
		}
		end ++;
	}
	string = str;
	return string;
}



int main(int argc, char const *argv[])
{
	/* code */
	std::string newString = reverseWords("the words in this string should be printed in reverse");

	std::cout << newString << "\n";
	return 0;
}

