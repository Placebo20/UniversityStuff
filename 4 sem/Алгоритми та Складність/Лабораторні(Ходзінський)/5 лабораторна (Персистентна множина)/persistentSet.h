#pragma once
#include <iostream>
#include <vector>
template <typename T>
class PersistentSet {//���� ��� ����� ������������ �������

private:
    class Node {//�����  ��� ����� ����� �������-������� ������

    public:
        T value;
        Node* parent;
        Node* left;
        Node* right;
        bool isBlack{};

        Node() {//����������� ������-�������� ������
            left = right = parent = nullptr;
            isBlack = true;
        }

        explicit Node(T& value) {
            this->value = value;
            this->left = nullptr;
            this->right = nullptr;
            this->parent = nullptr;
            this->isBlack = false;
        }

        explicit Node(Node* toCopy) {
            if (toCopy == nullptr)
                return;

            this->value = toCopy->value;
            this->left = toCopy->left;
            this->right = toCopy->right;
            this->parent = toCopy->parent;
            this->isBlack = toCopy->isBlack;


            if (left != nullptr)
                left->parent = this;
            if (right != nullptr)
                right->parent = this;

            if (parent != nullptr) {
                if (parent->left != nullptr) {
                    if (parent->left->value == value) {
                        parent->left = this;
                    }
                    else
                        parent->right = this;
                }
                else {
                    parent->right = this;
                }
            }
        }

        ~Node() = default;
    };

