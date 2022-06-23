#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>
#include "clui.h"
using namespace std;

void gamestarter();
void starter();

struct player {
    string name;
    int score = 0;
};

struct save {
    int condition = 0, size, mine, level, flag;
    char game[20][20], page[20][20];
};

int size, mine, flag, iterator = 0, level, maxiterator = 0, check[20][20];
char game[20][20], page[20][20];
player person1, person2, person3, person4, person5, person6, person7, person8, person9, person10;
save slot1, slot2, slot3, slot4;
struct save slots[4] = {slot1, slot2, slot3, slot4};
struct player people[10] = {person1, person2, person3, person4, person5, person6, person7, person8, person9, person10};

void initializer() {
    for(int j = 0; j < 20; j++) {
        for(int i = 0; i < 20; i++) {
            game[i][j] = '*';
            page[i][j] = 'E';
            check[i][j] = 0;
        }
    }
    flag = 0;
}

void leaderboard() {
    player newperson1, newperson2, newperson3, newperson4, newperson5, newperson6, newperson7, newperson8, newperson9, newperson10 ;
    struct player newpeople[10] = {newperson1, newperson2, newperson3, newperson4, newperson5, newperson6, newperson7, newperson8, newperson9, newperson10};
    for(int i = 0; i < 10; i++)
        newpeople[i] = people[i];
    for(int i = 0; i < ::maxiterator; i++) {
        for(int j = 0; j < ::maxiterator - i; j++) {
            if(newpeople[j].score < newpeople[j + 1].score) {
                player temp = newpeople[j];
                newpeople[j] = newpeople[j + 1];
                newpeople[j + 1] = temp;
            }
        }
    }
    cout<<endl;
    for(int i = 0; i <= ::maxiterator && i < 5; i++) {
        cout<<newpeople[i].name<<" : "<<newpeople[i].score<<endl;
    }
}

void bombdistributer() {
    for(int i = 0; i < mine; i++) {
        int a = rand() % size, b = rand() % size;
        if(page[a][b] == 'B') {
            i--; continue;
        }
        else
            page[a][b] = 'B';
    }
}

void printer(char array[20][20]) {
    for(int j = 0; j < size; j++) {
        for(int i = 0; i < size; i++) {
            if(array[i][j] == 'B')
                change_color_rgb(250, 0, 0);
            else if(array[i][j] == 'F')
                change_color_rgb(30, 240, 20);
            if(array[i][j] == '0')
                array[i][j] = ' ';
            cout<<array[i][j]<<" ";
            reset_color();
        }
        cout<<endl;
    }
    cout<<endl;
}

void newgame() {
    clear_screen();
    cout<<"OK! first enter your difficulty:\n\n1. Easy\n2. Meduim\n3. Hard \n4. Costum \n\n";
    while(true) {
        level = getch();
        if(level == '1') {
            size = 5, mine = 4; break;
        }
        else if(level == '2') {
            size = 12, mine = 28; break;
        }
        else if(level == '3') {
            size = 20,  mine = 96; break;
        }
        else if(level == '4') {
            clear_screen();
            cout<<"Alright! Enter your preferred size: ";
            while(true) {
                cin>>size;
                if(size > 20 || size < 5) {
                    clear_screen();
                    change_color_rgb(250, 0, 0);
                    cout<<"This size is invalid! \a Enter a new one: ";
                    reset_color(); continue;
                }
                break;
            }
            cout<<"now Enter the quantity of the mines: ";
            while(true) {
                cin>>mine;
                if(mine > 96 || mine < 4 || mine > size * size - size) {
                    clear_screen();
                    change_color_rgb(250, 0, 0);
                    cout<<"This is invlid quantity of the mines \a Enter a new one: ";
                    reset_color(); continue;
                }
                break;
            }
            break;
        }
        else {
            change_color_rgb(250, 0, 0);
            cout<<"Invalid input! \aEnter again: \n";
            reset_color(); continue;
        }
    }
    clear_screen();
    bombdistributer();
    gamestarter();
}

bool conditionchecker(save x) {
    if(x.condition == 1) 
        return true;
    else
        cout<<"\nThis slot is empty!\n";
        return false;
}

void assigner(save n) {
    mine = n.mine, size = n.size, level = n.level, flag = n.flag;
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            game[j][i] = n.game[j][i];
            page[j][i] = n.page[j][i];
        }
    }
}

void loader() {
    clear_screen();
    cout<<"In which slot you want to save (1, 2, 3, 4) ? (Press 0 for returning to the menu) : ";
    while(true) {
        char s = getch();
        if(s == '0') {
            starter(); break;
        }
        else if(s == '1') {
            if(conditionchecker(slots[0]))
                assigner(slots[0]);
            else
                continue;
        }
        else if(s == '2') {
            if(conditionchecker(slots[1]))
                assigner(slots[1]);
            else
                continue;
        }
        else if(s == '3') {
            if(conditionchecker(slots[2]))
                assigner(slots[2]);
            else
                continue;
        }
        else if(s == '4') {
            if(conditionchecker(slots[3]))
                assigner(slots[3]);
            else
                continue;
        }
        else {
            cout<<"\ninvalid number! \aPleasre enter again: "; continue;
        }
        break;
    }
    clear_screen();
    gamestarter();
}

void starter() {
    while(true) {
        clear_screen();
        cout<<"Hello "<<people[::iterator].name<<" !\n";
        change_color_rgb(48, 102, 201);
        cout<<"\n1. New Game \n2. Load Game \n3. Change name \n4. Leaderboard \n5. Quit\n";
        reset_color();
        int select = getch();
        if(select == '5')
            exit(0);
        else if(select == '4') {
            leaderboard(); 
            cout<<"\nPress any key to return to the main menu...\n";
            if(getch())
                continue;
        }
        else if(select == '3') {
            if(::maxiterator == 9) {
                change_color_rgb(250, 0, 0);
                cout<<"You can not have more than 10 players!\a\n";
                reset_color(); 
                cout<<"\nPress any key to return to the main menu...\n";
                if(getch())
                    continue;
            } 
            clear_screen();
            cout<<"Alright! Enter the new name: ";
            string tempname;
            getline(cin, tempname);
            int checker = 0;
            for(int i = 0; i <= ::maxiterator; i++) {
                if(tempname == people[i].name) {
                    checker = 1;
                    ::iterator = i; break;
                }
            }
            if(checker == 1) 
                continue;
            if(people[::iterator + 1].name[0] == '\0') {
                ::iterator++;
                ::maxiterator++;
            }
            else {
                for(int i = ::iterator; people[::iterator + 1].name[0] != '\0'; i++)
                    ::iterator = i;
            }
            people[::iterator].name = tempname;
            cout<<"Your name changed to: "<<people[::iterator].name<<"\n\n";
            cout<<"Press any key to return to the main menu...\n";
            if(getch())
                continue;
        }
        else if(select == '2') {
            loader(); break;
        }
        else if(select == '1') {
            newgame(); break;
        }
        else {
            change_color_rgb(250, 0, 0);
            cout<<"Invalid num!\a Please Enter again: ";
            reset_color();
            delay(2000); continue;
        }
    }
}

int bombcounter(char array[20][20], int i, int j) {
    int counter = 0;
    if(i > 0 && i < size - 1 && j > 0 && j < size - 1) {
        if(array[i + 1][j] == 'B')
            counter++;
        if(array[i - 1][j] == 'B')
            counter++;
        if(array[i][j + 1] == 'B')
            counter++;
        if(array[i][j - 1] == 'B')
            counter++;
        if(array[i + 1][j + 1] == 'B')
            counter++;
        if(array[i + 1][j - 1] == 'B')
            counter++;
        if(array[i - 1][j + 1] == 'B')
            counter++;
        if(array[i - 1][j - 1] == 'B')
            counter++;
    }
    else if(i == 0 && j == 0) {
        if(array[i + 1][j] == 'B')
            counter++;
        if(array[i + 1][j + 1] == 'B')
            counter++;
        if(array[i][j + 1] == 'B')
            counter++;
    }
    else if(i == 0 && j == size - 1) {
        if(array[i + 1][j] == 'B')
            counter++;
        if(array[i + 1][j - 1] == 'B')
            counter++;
        if(array[i][j - 1] == 'B')
            counter++;
    }
    else if(i == size - 1 && j == size - 1) {
        if(array[i - 1][j] == 'B')
            counter++;
        if(array[i - 1][j - 1] == 'B')
            counter++;
        if(array[i][j - 1] == 'B')
            counter++;
    }
    else if(i == size - 1 && j == 0) {
        if(array[i - 1][j] == 'B')
            counter++;
        if(array[i - 1][j + 1] == 'B')
            counter++;
        if(array[i][j + 1] == 'B')
            counter++;
    }
    else if(j == 0 && i > 0 && i < size - 1) {
        if(array[i + 1][j] == 'B')
            counter++;
        if(array[i - 1][j] == 'B')    
            counter++;
        if(array[i][j + 1] == 'B')
            counter++;
        if(array[i + 1][j + 1] == 'B')
            counter++;
        if(array[i - 1][j + 1] == 'B')
            counter++;
    }
    else if(j == size - 1 && i > 0 && i < size - 1) {
        if(array[i + 1][j] == 'B')
            counter++;
        if(array[i - 1][j] == 'B')    
            counter++;
        if(array[i][j - 1] == 'B')
            counter++;
        if(array[i + 1][j - 1] == 'B')
            counter++;
        if(array[i - 1][j - 1] == 'B')
            counter++;
    }
    else if(i == 0 && j < size - 1 && j > 0) {
        if(array[i][j + 1] == 'B')
            counter++;
        if(array[i][j - 1] == 'B')    
            counter++;
        if(array[i + 1][j] == 'B')
            counter++;
        if(array[i + 1][j + 1] == 'B')
            counter++;
        if(array[i + 1][j - 1] == 'B')
            counter++;
    }
    else if(i == size - 1 && j < size - 1 && j > 0) {
        if(array[i][j + 1] == 'B')
            counter++;
        if(array[i][j - 1] == 'B')    
            counter++;
        if(array[i - 1][j] == 'B')
            counter++;
        if(array[i - 1][j + 1] == 'B')
            counter++;
        if(array[i - 1][j - 1] == 'B')
            counter++;
    }
    return counter;
}

void flaghandler(int x, int y) {
    if(game[x][y] == 'F') {
        game[x][y] = '*';
        flag--;
        printer(game);
    }
    else if(game[x][y] == '*'){
        flag++;
        game[x][y] = 'F';
        printer(game);
    }
}

bool winchecker() {
    int counter  = 0;
    for(int j = 0; j < size; j++) {
        for(int i = 0; i < size; i++) {
            if(game[i][j] == '*' || game[i][j] == 'F')
                counter++;
        }
    }
    if(counter == mine) {
        for(int i = 0; i < size; i++) {
            for(int j = 0; j < size; j++) {
                if(page[i][j] == 'B')
                    game[i][j] = page[i][j];
            }
        }
        if(level <= 3)
            people[::iterator].score += level;
        else
            people[::iterator].score += 1;
        return true;
    }
    return false;
}

void neighbor(int i, int j) {
    game[i][j] = ' ';
    check[i][j] = 1;
    if(i + 1 < size) {
        if(bombcounter(page, i + 1, j) != 0) 
            game[i + 1][j] = bombcounter(page, i + 1, j) + 48;
        else if(check[i + 1][j] != 1) 
            neighbor(i + 1, j);
    }
    if(i - 1 >= 0) {
        if(bombcounter(page, i - 1, j) != 0) 
            game[i - 1][j] = bombcounter(page, i - 1, j) + 48;
        else if(check[i - 1][j] != 1) 
            neighbor(i - 1, j);
    }
    if(j + 1 < size) {
        if(bombcounter(page, i, j + 1) != 0) 
            game[i][j + 1] = bombcounter(page, i, j + 1) + 48;
        else if(check[i][j + 1] != 1)
            neighbor(i, j + 1);
    }
    if(j - 1 >= 0) {
        if(bombcounter(page, i, j - 1) != 0) 
            game[i][j - 1] = bombcounter(page, i, j - 1) + 48;
        else if(check[i][j - 1] != 1)
            neighbor(i, j - 1);
    }
    if(i + 1 < size && j + 1 < size) {
        if(bombcounter(page, i + 1, j + 1) != 0)
            game[i + 1][j + 1] = bombcounter(page, i + 1, j + 1) + 48;
        else if(check[i + 1][j + 1] != 1)
            neighbor(i + 1, j + 1); 
    }
    if(i + 1 < size && j - 1 >= 0) {
        if(bombcounter(page, i + 1, j - 1) != 0)
            game[i + 1][j - 1] = bombcounter(page, i + 1, j - 1) + 48;
        else if(check[i + 1][j - 1] != 1)
            neighbor(i + 1, j - 1);
    }
    if(i - 1 >= 0 && j - 1 >= 0) {
        if(bombcounter(page, i - 1, j - 1) != 0)
            game[i - 1][j - 1] = bombcounter(page, i - 1, j - 1) + 48;
        else if(check[i - 1][j - 1] != 1)
            neighbor(i - 1, j - 1);
    }
    if(i - 1 >= 0 && j + 1 < size) {
        if(bombcounter(page, i - 1, j + 1) != 0)
            game[i - 1][j + 1] = bombcounter(page, i - 1, j + 1) + 48;
        else if(check[i - 1][j + 1] != 1)
            neighbor(i - 1, j + 1);
    }
}

void savertoslot(save &m) {
    m.condition = 1, m.size = size, m.mine = mine, m.level = level, m.flag = flag;
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            m.game[i][j] = game[i][j];
            m.page[i][j] = page[i][j];
        }
    }
}

void saver() {
    clear_screen();
    cout<<"In which slot you want to save? : ";
    while(true) {
        int slot = getch();
        if(slot == '1')
            savertoslot(slots[0]);
        else if(slot == '2') 
            savertoslot(slots[1]);
        else if(slot == '3')
            savertoslot(slots[2]);
        else if(slot == '4')
            savertoslot(slots[3]);
        else {
            cout<<"invalid number! \aPleasre enter again: "; continue;
        }
        break;
    }
}

void gamestarter() {
    printer(game);
    cursor_to_pos(1, 1);
    int x = 0, y = 0;
    bool quit = false, saving = false, wining = false, losing = false;
    while(true) {
        if(winchecker()) {
            wining = true;
            clear_screen();
            change_color_rgb(150, 40, 210);
            cout<<"Congragratulations!\a\n"<<endl;
            reset_color();
            printer(game);
            cout<<"Press any key to return to the main menu...\n";
            initializer();
            if(getch())     
                break;
        }
        char input = getch();
        if(input == 'w' && y >= 1) {
            cursor_up(1);
            y--;
        }
        else if(input == 's' && (y < size - 1)) {
            cursor_down(1);
            y++;
        }
        else if(input == 'a' && x >= 1) {
            cursor_backward(2);
            x--;
        }
        else if(input == 'd' && (x < size - 1)) {
            cursor_forward(2);
            x++;
        }
        else if(input == 'h') {
            cursor_to_pos(size + 1, 1);
            printer(page);
            x= 0, y = 0;
            cursor_to_pos(1, 1);
        }
        else if(input == 'f') {
            if(flag == mine && game[x][y] != 'F') {
                cursor_to_pos(size + 1, 1);
                cout<<"You can not have more flags!"<<endl;
                x = 0, y = 0;
                cursor_to_pos(1, 1);
                continue;
            }
            else if(!(game[x][y] >= '0' && game[x][y] <= '9' || game[x][y] == ' ')) {
                clear_screen();
                flaghandler(x, y);
                x = 0, y = 0;
                cursor_to_pos(1, 1);
            }
        }
        else if(input == 'q') {
            initializer();
            quit = true; break;
        }
        else if(input == 'o') {
            saver();
            saving = true; break;
        }
        else if(input == ' ') {
            if(game[x][y] == 'F') {
                clear_screen();
                printer(game);
                cout<<"First you have to unflag this position!\a\n";
                x = 0, y = 0;
                cursor_to_pos(1, 1); continue;
            }
            else if(page[x][y] == 'B') {
                losing = true;
                clear_screen();
                change_color_rgb(250, 0, 0);
                cout<<"You Lost!\a\n\n";
                reset_color();
                printer(page);
                initializer();
                cout<<"Press any key to return to the main menu...\n";
                if(getch())
                    break;
            }
            else {
                if(bombcounter(page, x, y) == 0) {
                    game[x][y] = bombcounter(page, x, y) + 48;
                    neighbor(x, y);
                    clear_screen();
                    printer(game);
                    x = 0, y = 0;
                    cursor_to_pos(1, 1); continue;
                }
                else {
                    game[x][y] = bombcounter(page, x, y) + 48;
                    clear_screen();
                    printer(game);
                    x = 0, y = 0;
                    cursor_to_pos(1, 1); continue;
                }
            }
        }
        else
            continue;
    }
    if(quit || saving || wining || losing)
        starter();
}

int main() {
    init_clui();
    srand(time(NULL));
    change_color_rgb(250, 250, 0);
    cout<<endl<<"Welcome to MineSweeper game! \nPlease Enter your name: ";
    reset_color();
    getline(cin, people[::iterator].name);
    initializer();
    starter();
}
