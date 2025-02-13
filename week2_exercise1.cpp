//STARTER 
//THIS EXERCISE IS TO BE DONE IN A GENERIC C++ COMPILER
//https://www.programiz.com/cpp-programming/online-compiler/
//IF YOU HAVE ISSUES WITH THE COMPILER, CONTACT EMBEDDED LEAD
const int BUFFER_SIZE = 26;
const int offset = 1;
#include <iostream>

static char inputString[] = "ydrsxdladccdclzqhmzqzrztbd"; //this test string should output zestyembeddedmarinarasauce

//puts a character into the output buffer
//remember that nothing will show until you print a newline.
void putc(char c){
    printf("%c", c);
}

//returns a number for a corresponding letter 
//a is 0, b is 1, all the way to z is 25
int letterToNumber(char c){ 
    return c - 'a';
}

//returns a letter to the corresponding number
//a is 0, b is 1, all the way to z is 25
char numberToLetter(char i){ 
    return i + 'a';
}

int main(void)
{
    for(int i = 0; inputString[i] != '\0'; i++){
        char shifted_char = numberToLetter((letterToNumber(inputString[i]) + offset) % BUFFER_SIZE);
        putc(shifted_char);
    }
    putc('\n');
    return 0;
}
