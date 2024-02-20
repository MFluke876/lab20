#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstdlib>

using namespace std;

char score2grade(int score){
    if(score >= 80) return 'A';
    if(score >= 70) return 'B';
    if(score >= 60) return 'C';
    if(score >= 50) return 'D';
    else return 'F';
}

string toUpperStr(string x){
    string y = x;
    for(unsigned i = 0; i < x.size();i++) y[i] = toupper(x[i]);
    return y;
}

void importDataFromFile(string filename, vector<string> &a, vector<int> &b, vector<char> &c){
    ifstream file(filename);
    string data;
    char format[] = "%[^:]: %d %d %d";
    char names[100];
    int score1, score2, score3, total;
    

    while (getline(file, data)){
        const char * cdata = data.c_str();
        sscanf(cdata, format, names, &score1, &score2, &score3);
        total = score1 + score2 + score3;
        a.push_back(names);
        b.push_back(total);
        c.push_back(score2grade(total));
    }
    file.close();
}

void getCommand(string &command, string &key){
    string input;
    cout << "Please input your command: ";
    getline(cin, input);
    size_t spacePos = input.find(' ');
    command = input.substr(0, spacePos);
    key = input.substr(spacePos + 1);
}

void searchName(vector<string> &names, vector<int> &scores, vector<char> &grades, string key){
    for (unsigned int i = 0; i < names.size(); i++){
        if (toUpperStr(names[i]) == key){
            cout << "---------------------------------\n";
            cout << names[i] << "\'s" << " score = " << scores[i] << '\n';
            cout << names[i] << "\'s" << " grade = " << grades[i] << '\n';
            cout << "---------------------------------\n";
            return;
        }
    }    
    cout << "---------------------------------\n";
    cout << "Cannot found." << '\n';
    cout << "---------------------------------\n";
}

void searchGrade(vector<string> names, vector<int> scores, vector<char> grades, string key){
    bool check = false;
    cout << "---------------------------------\n";
    for (unsigned int i = 0; i < names.size(); i++){
        if (grades[i] == key[0]){
            cout << names[i] << " " << "(" << scores[i] << ")" << '\n';
            check = true;
        }
    }    
    if (check == false){
        cout << "Cannot found." << '\n';
    }
    cout << "---------------------------------\n";
}


int main(){
    string filename = "name_score.txt";
    vector<string> names;
    vector<int> scores;
    vector<char> grades; 
    importDataFromFile(filename, names, scores, grades);
    
    do{
        string command, key;
        getCommand(command,key);
        command = toUpperStr(command);
        key = toUpperStr(key);
        if(command == "EXIT") break;
        else if(command == "GRADE") searchGrade(names, scores, grades, key);
        else if(command == "NAME") searchName(names, scores, grades, key);
        else{
            cout << "---------------------------------\n";
            cout << "Invalid command.\n";
            cout << "---------------------------------\n";
        }
    }while(true);
    
    return 0;
}