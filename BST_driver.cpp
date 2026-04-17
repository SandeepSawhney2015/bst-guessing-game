#include "BST.hpp"
#include <iostream>
#include <fstream>
#include <map>
#include <cctype>

using namespace std;

class EndGame {
    public:
        void getMessage(){
            cout << message << endl;
        }
    private:
        string message = "Automatically ended game due to caught exception.";
};

class UnopenableFile {
    public:
        UnopenableFile(string filename) : file_in(filename) {} 
        void getMessage(){
            cout << "Unable to open db file: " << file_in << endl; 
        }
    private:
        string file_in;
};

pair<map<int, int>, int> gather_data(string filename){
    map<int, int> freq;
    ifstream file(filename);
    if(!file){
        throw UnopenableFile(filename);
    }
    int number, count;
    int total = 0;
    while(file >> number >> count){
        freq[number] = count;
        total += count;
    }
    return {freq, total};
}

int create_root(const map<int, int>& freq, const double& total){
    int number;
    int where_we_at = 0;
    int boundary = total/2;
    for(auto i : freq){
        where_we_at = i.second + where_we_at;
        if(where_we_at >= boundary){
            number = i.first;
            break;
        }
    }
    return number;
}

void add_to_db(map<int, int>& freq, int user){
    freq[user] += 1;
}

void play_game(map<int, int>& freq, BST<int>& tree){
    int user_guess;
    cout << "What is your guess (a number between 1 and 100 inclusive)? ";
    cin >> user_guess;
    cout << endl;
    add_to_db(freq, user_guess);
    int current_guess = tree.get_current();
    string answer = "n";
    string movement;
    while(answer != "y"){
        cout << "Is your answer " << current_guess << "? (y/n) ";
        cin >> answer;
        cout << endl;
        if(answer == "n"){
            try{
                tree.check_user(user_guess, answer);
            } catch (UserTryingBSGame& e){
                cout << e.getMessage() << endl;
                throw EndGame();
            }
            cout << "Was your answer less or greater? (l/g) ";
            cin >> movement;
            cout << endl;
            if(movement == "l"){
                tree.go_left();
            } else {
                tree.go_right();
            }
            current_guess = tree.get_current();
        } 
    }
    cout << "Your number was " << current_guess;
    cout << endl;
}

void rebuild_db(const map<int, int>& freq){
    ofstream file("data.txt");

    for(const auto& data : freq){
        file << data.first << " " << data.second << endl;
    }
}

int main(){
    try {
        auto read = gather_data("data.txt");
        BST<int> tree(create_root(read.first, read.second));
        tree.build_around_root(1,100);
        play_game(read.first, tree);
        rebuild_db(read.first);
    } catch (EndGame& e){
        cout << "automatically ended game due to exception :(" << endl;
    } catch (UnopenableFile& e){
        e.getMessage();
    }
}