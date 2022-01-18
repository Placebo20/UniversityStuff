#pragma once
#include "group.h"

struct UniversalHash {
    std::size_t operator ()(const std::string& string, int a, int b, int p, int m) const {
        return std::accumulate(
            string.cbegin(),
            string.cend(),
            0,
            [a, b, p](int sum, char ch) { return (a * (sum + ch) + b) % p; }
        ) % m;
    }
}; // struct UniversalHash<std::string>

class HashRow {
public:
    unsigned short a;
    unsigned short b;
    Group* groups;
    unsigned short size;
    HashRow() = default;
    int createHash(int id);
    friend std::ostream operator<<(std::ostream& os, HashRow  hashRow);
};

class Core {
    std::vector<Group*> groups;
    int size;
    const unsigned short p = 345;
public:
    void run();
    void printGroups();
    void createGroups();
    std::vector<std::string> getGroupsTitles(int count);
    void fillHashTable(HashRow* HashTable);
    int createHash(int id, int a, int b, int m);
    void printHashes(std::vector<std::vector<Group*>> hashesTable);
};

void Core::run() {
    std::cout << "Enter count of Groups yoy want to generate: ";
    int countOfGroups;
    std::cin >> countOfGroups;
    size = countOfGroups;
    HashRow* newHashTable = new HashRow[size];
    for (int i = 0; i < size; i++) {
        newHashTable[i].a = newHashTable[i].b = newHashTable[i].size = 0;
        newHashTable[i].groups = nullptr;
    }
    createGroups();
    fillHashTable(newHashTable);
    for (int i = 0; i < size; ++i) {
        if (newHashTable[i].groups != nullptr) {
            std::cout << "==================" << i << "===================" << std::endl;
            std::cout << newHashTable[i];
        }
        else {
            std::cout << "==================" << i << "===================" << std::endl;
            std::cout << "\t\tEmpty cell\n";
            std::cout << "===========================================" << std::endl;
        }
    }
}

void Core::printGroups() {
    for (int i = 0; i < groups.size(); ++i) {
        std::cout << groups[i];
    }
}

void Core::createGroups() {
    std::cout << "Type how much Groups you want to create: ";
    int countOfNewGroups;
    std::cin >> countOfNewGroups;
    for (int c = 0; c < countOfNewGroups; c++) {
        Group* newGroup = new Group();
        newGroup->addStudents();
    }
}

std::vector<std::string> Core::getGroupsTitles(int count) {
    std::ifstream fin("Groups.txt");
    std::vector<std::string> Groups;
    int i = 0;
    std::string groupName;
    while (i < count && !fin.eof()) {
        fin >> groupName;
        Groups.push_back(groupName);
        groupName = "\0";
    }
    fin.close();
    return Groups;
}

void Core::fillHashTable(HashRow* hashTable) {
    std::vector<std::vector<Group*>> hashesTable;
    hashesTable.resize(size);
    UniversalHash _hash;
    for (int i = 0; i < size; i++) {
        int newHash = _hash(groups[i]->getGroupTitle(), 6, 102, p, size);
        hashesTable[newHash].push_back(groups[i]);
    }

    for (int i = 0; i < hashesTable.size(); i++) {
        if (!hashesTable[i].empty()) {
            hashTable[i].groups = new Group[hashesTable.size() * hashesTable[i].size()];
            hashTable[i].size = hashesTable[i].size() * hashesTable[i].size();
        }
        if (hashesTable[i].size() == 1) {
            hashTable[i].groups[0] = *hashesTable[i][0];
            hashTable[i].a = hashTable[i].b = 0;
            continue;
        }
        bool flag = false, sameHash = false;
        std::vector<int> newHashes;
        hashTable[i].a = hashTable[i].b = 1;

        while (!flag) {
            for (int j = 0; j < hashesTable[i].size(); j++) {
                if (newHashes[j] == newHashes[j - 1])
                    sameHash = true;
            }
            if (sameHash) {
                sameHash = false;
                if (hashTable[i].a == p - 1) {
                    hashTable[i].a = 1;
                    hashTable[i].b++;
                }
                else { hashTable[i].a++; } continue;
            }
            else {
                flag = true;
                for (int j = 0; j < hashesTable[i].size(); j++) {
                    int newHash = _hash(hashesTable[i][j]->getGroupTitle(), hashTable[i].a, hashTable[i].b, p, hashTable[i].size);
                    hashTable[i].groups[newHash] = *hashesTable[i][j];
                }
            }
        }
    }
}

int Core::createHash(int id, int a, int b, int m) {
    int newHash;
    newHash = (((a * id + b) % p) % m);
    return newHash;
}

void Core::printHashes(std::vector<std::vector<Group*>> hashesTable) {
    for (int i; i < hashesTable.size(); i++) {
        std::cout << "Size: " << hashesTable[i].size() << std::endl;
        for (int j = 0; j < hashesTable[i].size(); j++) {
            std::cout << hashesTable[i][j];
        }
    }
}

std::ostream& operator<<(std::ostream& os, HashRow hashRow) {
    os << "a = " << hashRow.a << " b = " << hashRow.b << " size = " << hashRow.size << std::endl << "Groups: " << std::endl;
    for (int i = 0; i < hashRow.size; i++) {
        if (!hashRow.groups[i].getGroupTitle().empty()) os << hashRow.groups[i].getGroupTitle() << " | Count of Students: " << hashRow.groups[i].getGroupStudents().size() << std::endl;
    }
    os << "================================" << std::endl;
    return os;
}