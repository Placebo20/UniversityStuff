#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <cstdint>
#include <string>
using namespace std;

struct Monster {
    int ID;
    string name;
    int health_point;
    int damage_point;
    int chanse_of_specattack;
    int type_of_specattack;
    int year;
    int month;
    int day;
    int hour;
};

void read_from_txt() {
    string line;
    ifstream outputmonster;
    outputmonster.open("MonsterTXT.txt");
    if (outputmonster.is_open()) {
        cout << "File is open!" << endl;
        while (getline(outputmonster, line)) {
            cout << line << endl;
        }
    }
    else {
        cout << "File isn't open!" << endl;
    }
    outputmonster.close();
}

/*void read_from_bin(){
    ifstream readbin("MonsterBIN.txt", ios::binary|ios::in);
    readbin.read();
}*/

void FindMonsterViaName(vector<Monster> MonsterVector) {
    string check;
    cout << "Enter check: ";
    cin >> check;
    for (int i = 0; i < MonsterVector.size(); i++) {
        Monster tmp = MonsterVector[i];
        if (check == tmp.name.substr(0, check.length())) {
            cout << "ID: " << tmp.ID << endl;
            cout << "Name: " << tmp.name << endl;
        }
    }
}

void FindMonstersViaSpecAttackAndDamage(vector<Monster> MonsterVector) {
    int FindSpecAttack, MinimumDamage, MaximumDamage = 0;
    cout << "What type of attack you want to find?\n"
        "1)Double Damage\n"
        "2)Paralyze enemy\n"
        "3)Cure yourself\n"
        "4)Double attack" << endl;
    cin >> FindSpecAttack;
    while (FindSpecAttack < 1 || FindSpecAttack > 4 || cin.fail()) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Incorrect number, or it's not a number, try again: ";
        cin >> FindSpecAttack;
    }
    cout << "Now enter the minimum damage: ";
    cin >> MinimumDamage;
    cout << "Now enter the maximum damage: ";
    cin >> MaximumDamage;
    cout << "====================" << endl;
    for (int i = 0; i < MonsterVector.size(); i++) {
        Monster tmp = MonsterVector[i];
        if (tmp.chanse_of_specattack == 1) {
            if (FindSpecAttack == tmp.type_of_specattack && tmp.damage_point >= MinimumDamage && tmp.damage_point <= MaximumDamage) {
                cout << "ID: " << tmp.ID << endl;
                cout << "Name: " << tmp.name << endl;
            }
            else {
                cout << "There are no monsters matching your criteria." << endl;
            }
        }
    }
    cout << "====================" << endl;
}

void FindMonstersViaTime(vector<Monster> MonsterVector) {
    int findyear, findmonth, findday, findhour = 0;
    cout << "Enter the date" << endl;
    cout << "Year(2010 to 2019): ";
    cin >> findyear;
    cout << "Month(1 to 12): ";
    cin >> findmonth;
    cout << "Day(1 to 31): ";
    cin >> findday;
    cout << "Hour(0 to 23): ";
    cin >> findhour;
    for (int i = 0; i < MonsterVector.size(); i++) {
        Monster tmp = MonsterVector[i];
        if (findyear <= tmp.year && findmonth <= tmp.month && findday <= tmp.day && findhour < tmp.hour) {
            cout << "ID: " << tmp.ID << endl;
            cout << "Name: " << tmp.name << endl;
        }
        else {
            cout << "There are no monsters matching your criteria." << endl;
        }
    }
}

void BufferMenu(vector<Monster> MonsterVector) {
    int bufferint;
    cout << "What you want to do?:\n"
        "1)Find some monsters\n"
        "2)Read data from txt file\n"
        "3)Read data from bin file\n"
        "4)Exit" << endl;
    cin >> bufferint;
    while (bufferint < 1 || bufferint > 3 || cin.fail()) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Incorrect number, or it is not a number, try again: ";
        cin >> bufferint;
    }
    if (bufferint == 4) {
        exit(0);
    }
    else if (bufferint == 2) {
        system("cls");
        read_from_txt();
    }
    else if (bufferint == 1) {
        system("cls");
        int tmp = 0;
        cout << "How do you want to find monsters?\n"
            "1)Monsters with a name beginning with a given snippet\n"
            "2)monsters with a given special attack type and number of units attacks in a given range\n"
            "3)the monsters that appeared in the game after the specified time." << endl;
        cin >> tmp;
        while (tmp < 1 || tmp > 3 || cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Incorrect number, or it's not a number, try again: ";
            cin >> tmp;
        }
        if (tmp == 1) {
            FindMonsterViaName(MonsterVector);
        }
        else if (tmp == 2) {
            FindMonstersViaSpecAttackAndDamage(MonsterVector);
        }
        else if (tmp == 3) {
            FindMonstersViaTime(MonsterVector);
        }
    }

    /*else if(bufferint == 3){
        system("cls");
        read_from_bin();
    }*/

}

void save_to_txt(vector<Monster> MonsterVector) {
    ofstream txtsave;
    txtsave.open("MonsterTXT.txt");
    if (!txtsave.is_open())
        cout << "Problem with File" << endl;
    else {
        cout << "File is open!" << endl;
        for (int i = 0; i < MonsterVector.size(); i++) {
            Monster tmp = MonsterVector[i];
            txtsave << "ID: " << tmp.ID << endl;
            txtsave << i + 1 << " Monster" << endl;
            txtsave << tmp.name << endl;
            txtsave << "Health point: " << tmp.health_point << endl;
            txtsave << "Damage point: " << tmp.damage_point << endl;
            txtsave << "Special attack?: ";
            if (tmp.chanse_of_specattack == 1)
                txtsave << "Yes" << endl;
            else
                txtsave << "No" << endl;
            if (tmp.chanse_of_specattack == 1) {
                txtsave << "Type of specattack is: ";
                if (tmp.type_of_specattack == 1)
                {
                    txtsave << "DOUBLE DAMAGE" << endl;
                }
                else if (tmp.type_of_specattack == 2)
                {
                    txtsave << "PARALYZYS" << endl;
                }
                else if (tmp.type_of_specattack == 3)
                {
                    txtsave << "CURING" << endl;
                }
                else
                {
                    txtsave << "DOUBLE ATTACK" << endl;
                }
            }
            txtsave << "Created at: " << tmp.day << "/" << tmp.month << "/" << tmp.year << " " << tmp.hour << ":00" << endl;
            txtsave << "===========================================" << endl;
        }
    }
    txtsave.close();
    BufferMenu(MonsterVector);
}

void save_to_bin(vector<Monster> MonsterVector) {
    ofstream savebin("MonsterBIN.txt", ios::binary | ios::out);
    for (int i = 0; i < MonsterVector.size(); i++) {
        Monster tmp = MonsterVector[i];

        uint16_t namelen = tmp.name.length();
        savebin.write((char*)&namelen, sizeof(namelen));
        savebin.write(tmp.name.data(), namelen);

        savebin.write((char*)&tmp.ID, sizeof(tmp.ID));
        savebin.write((char*)&tmp.health_point, sizeof(tmp.health_point));
        savebin.write((char*)&tmp.damage_point, sizeof(tmp.damage_point));

        savebin.write((char*)&tmp.chanse_of_specattack, sizeof(tmp.chanse_of_specattack));
        if (tmp.chanse_of_specattack == 1) {
            savebin.write((char*)&tmp.type_of_specattack, sizeof(tmp.type_of_specattack));
        }

        savebin.write((char*)&tmp.year, sizeof(tmp.year));
        savebin.write((char*)&tmp.month, sizeof(tmp.month));
        savebin.write((char*)&tmp.day, sizeof(tmp.day));
    }
    savebin.close();
    BufferMenu(MonsterVector);
}

void Menu(int& Mode, int& Storage) {
    cout << "Hello, please, choose the mode:\n"
        "1)Interactive\n"
        "2)Demonstration\n"
        "3)Benchmark" << endl;
    cin >> Mode;
    while (Mode < 1 || Mode > 3 || cin.fail()) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Incorrect number, or it's not a number, please, try again: ";
        cin >> Mode;
    }
    cout << "Hello, please, choose the storage:\n"
        "1)Vector contaier\n"
        "2).txt file\n"
        "3).bin file" << endl;
    cin >> Storage;
    while (Storage < 1 || Storage > 3 || cin.fail()) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Incorrect number, or it's not a number, please, try again: ";
        cin >> Storage;
    }
}

void Interactive(int Storage) {
    int num_of_monsters;
    cout << "How much monsters you want to create?: ";
    cin >> num_of_monsters;
    while (cin.fail()) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Incorrect input, try again: ";
        cin >> num_of_monsters;
    }
    char Check;
    if (num_of_monsters > 5) {
        cout << "Are you sure you want to create so much monsters? (Yes(y), No(n): ";
        cin >> Check;
        if (Check == 'y') {
            cout << "OKAY!" << endl;
        }
        else if (Check == 'n') {
            cout << "Okay, try again: ";
            cin >> num_of_monsters;
        }
    }
    vector<Monster> MonsterVector;
    for (int i = 0; i < num_of_monsters; i++) {
        Monster tmp;
        tmp.ID = i + 1;
        cout << "ID: " << tmp.ID << endl;
        cout << "Enter the name of monster: ";
        cin >> tmp.name;
        cout << "Enter how much points of health you want to give for " << tmp.name << "(between 1 and 50000): ";
        cin >> tmp.health_point;
        while (tmp.health_point < 1 || tmp.health_point > 50000 || cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Incorrect number, or it's not a number, try again: ";
            cin >> tmp.health_point;
        }
        cout << "Enter how much points of damage you want to give for " << tmp.name << "(between 1 and 1000): ";
        cin >> tmp.damage_point;
        while (tmp.damage_point < 1 || tmp.damage_point > 1000 || cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Incorrect number, or it's not a number, try again: ";
            cin >> tmp.damage_point;
        }
        cout << "Do you want a special attack for " << tmp.name << "?(Yes(1), No(0)): ";
        cin >> tmp.chanse_of_specattack;
        while (tmp.chanse_of_specattack < 0 || tmp.chanse_of_specattack > 1 || cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Incorrect number, or it's not a number, try again: ";
            cin >> tmp.chanse_of_specattack;
        }
        if (tmp.chanse_of_specattack == 1) {
            cout << "What type of attack you want?\n"
                "1)Double Damage\n"
                "2)Paralyze enemy\n"
                "3)Cure yourself\n"
                "4)Double attack" << endl;
            cin >> tmp.type_of_specattack;
            while (tmp.type_of_specattack < 1 || tmp.type_of_specattack > 4 || cin.fail()) {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Incorrect number, or it's not a number, try again: ";
                cin >> tmp.type_of_specattack;
            }
        }
        cout << "Please enter the year of creation(between 2010 and 2019): ";
        cin >> tmp.year;
        while (tmp.year < 2010 || tmp.year > 2019 || cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Incorrect number, or it's not a number, try again: ";
            cin >> tmp.year;
        }
        cout << "Please enter the month of creation(between 1 and 12): ";
        cin >> tmp.month;
        while (tmp.month < 1 || tmp.month > 12 || cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Incorrect number, or it's not a number, try again: ";
            cin >> tmp.month;
        }
        cout << "Please enter the day of creation(between 1 and 31): ";
        cin >> tmp.day;
        while (tmp.day < 1 || tmp.day > 31 || cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Incorrect number, or it's not a number, try again: ";
            cin >> tmp.day;
        }
        cout << "Please enter the hour of creation(between 0 and 23): ";
        cin >> tmp.hour;
        while (tmp.hour < 0 || tmp.hour > 23 || cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Incorrect number, or it's not a number, try again: ";
            cin >> tmp.hour;
        }
        MonsterVector.push_back(tmp);
        system("cls");
    }
    system("cls");
    int check = 0;
    cout << "Do you want to output your data?(Yes(1), No(0)): ";
    cin >> check;
    cout << "===========================================" << endl;
    while (check < 0 || check > 1 || cin.fail()) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Incorrect, try again: ";
        cin >> check;
    }
    if (check == 1) {
        for (int i = 0; i < num_of_monsters; i++) {
            Monster tmp = MonsterVector[i];
            cout << i + 1 << " Monster" << endl;
            cout << "ID: " << tmp.ID << endl;
            cout << tmp.name << endl;
            cout << "Health point: " << tmp.health_point << endl;
            cout << "Damage point: " << tmp.damage_point << endl;
            cout << "Special attack?: ";
            if (tmp.chanse_of_specattack == 1)
                cout << "Yes" << endl;
            else
                cout << "No" << endl;
            if (tmp.chanse_of_specattack == 1) {
                cout << "Type of specattack is: ";
                if (tmp.type_of_specattack == 1)
                {
                    cout << "DOUBLE DAMAGE" << endl;
                }
                else if (tmp.type_of_specattack == 2)
                {
                    cout << "PARALYZYS" << endl;
                }
                else if (tmp.type_of_specattack == 3)
                {
                    cout << "CURING" << endl;
                }
                else
                {
                    cout << "DOUBLE ATTACK" << endl;
                }
            }
            cout << "Created at: " << tmp.day << "/" << tmp.month << "/" << tmp.year << " " << tmp.hour << ":00" << endl;
            cout << "===========================================" << endl;
        }
    }
    if (Storage == 1)
        return;
    else if (Storage == 2)
        save_to_txt(MonsterVector);
    else
        save_to_bin(MonsterVector);
}

int getMax(Monster& strct, int n)
{
    int mx = strct[0];
    for (int i = 1; i < n; i++)
        if (strct[i] > mx)
            mx = strct[i];
    return mx;
}

void countSort(Monster& strct, int n, int exp)
{
    int output[n]; 
    int i, count[10] = { 0 };

    
    for (i = 0; i < n; i++)
        count[(arr[i] / exp) % 10]++;

    
    for (i = 1; i < 10; i++)
        count[i] += count[i - 1];

     
    for (i = n - 1; i >= 0; i--)
    {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }

     
    for (i = 0; i < n; i++)
        arr[i] = output[i];
}

void radixsort(Monster& strct, int n)
{
    
    int m = getMax(arr, n);
    for (int exp = 1; m / exp > 0; exp *= 10)
        countSort(arr, n, exp);
}

int main() {
    int Mode, Storage = 0;
    Menu(Mode, Storage);
    if (Mode == 1)
        Interactive(Storage);
    /*else if (Mode == 2)
        Demonstration();
    else
        Benchmark()*/
}