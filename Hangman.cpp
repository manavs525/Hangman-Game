#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include<time.h>

using namespace std;

void printmessage(string message, bool printtop=true, bool printbottom=true){
    if(printtop){
        cout<<"+---------------------------------+"<<endl<<"|";
        
    }

    else{
        cout<<"|";
    }

    bool front=true;
    for(int i=message.length();i<33;i++){
        if(front==true){
            message=" "+message;
        }
        else{
            message=message + " ";
        }
        front=!front;
    }

    cout<<message.c_str();

    if(printbottom){
        cout<<"|"<<endl<<"+---------------------------------+"<<endl;
        
    }

    else{
        cout<<"|"<<endl;
    }

 

}

void DrawHangman(int guesscount=0){
    if(guesscount>=1)
        printmessage("|",false,false);
    else
        printmessage(" ",false,false);

    if(guesscount>=2)
        printmessage("|",false,false);
    else
        printmessage(" ",false,false);

    if(guesscount>=3)
        printmessage("O",false,false);
    else
        printmessage(" ",false,false);

    if(guesscount==4)
        printmessage("/",false,false);
    

    if(guesscount==5)
        printmessage("/|",false,false);
    
    if(guesscount>=6)
        printmessage("/|\\",false,false);
    else
        printmessage(" ",false,false);

    if(guesscount>=7)
        printmessage("|",false,false);
    else
        printmessage(" ",false,false);

    if(guesscount==8)
        printmessage("/",false,false);
    
    if(guesscount>=9)
        printmessage("/ \\",false,false);
    else
        printmessage(" ",false,false);
    
}

void PrintLetters(string input, char from, char to){
    string s;
    for(char i=from;i<=to;i++){
        if(input.find(i)==string::npos){
            s+=i;
            s+=" ";

        }
        else{
            s+=" ";
        }


    }

    printmessage(s,false, false);
}

void PrintAvailableLetters(string taken){
    printmessage("Available Letters");
    PrintLetters(taken,'a', 'm');
    PrintLetters(taken,'n','z');

}

bool PrintWordCheckWin(string word, string guessed){

        bool won=true;
        string s;
        for(int i=0;i<word.length();i++){
            if(guessed.find(word[i])==string::npos){
                    won =false;
                    s+="_";
            }

            else{
                s+= word[i];
                s+=" ";
            }
        }

        printmessage(s,false);
        return won;
}

string loadrandomword(string path){
    int linecount=0;
    string word;
    vector<string> v;
    ifstream reader (path);
    if(reader.is_open()){
        while(std::getline (reader,word))
            v.push_back(word);
        int randline=rand()%v.size();
        word=v.at(randline);
        reader.close();
    }

    return word;
}

int TriesLeft(string word, string guessed){
    int error=0;
    for(int i=0;i<guessed.length();i++){
        if(word.find(guessed[i])==string::npos)
            error++;

    }

    return error;
}

int main(){
   srand(time(0));
   string guesses, wordToGuess;
   wordToGuess=loadrandomword("words.txt");
   int tries=0;
   bool win =false;
   do{
       system("cls");
        printmessage("Hangman");
        DrawHangman(tries);
        PrintAvailableLetters(guesses);
        printmessage("Guess the word");
        win=PrintWordCheckWin(wordToGuess,guesses);

        if(win)
            break;
        
        char x;
        cout<<">";
        cin>>x;
        if(guesses.find(x)==string::npos){
            guesses+=x;

        }

        tries=TriesLeft(wordToGuess, guesses);
   }while(tries<10);

   if(win){
       printmessage("You Won!!");
   }

   else{
       printmessage("Game Over");
   }

   system("pause");
   getchar();
    return 0;
}
