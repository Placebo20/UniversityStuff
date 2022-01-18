#include "bPlusTree.h"
#include <algorithm>
#include <iostream>

template<typename DataType>
BPlusNode<DataType>::BPlusNode() :
    leaf{ false },
    size{ 0 },
    data(),
    children(),
    next_leaf{ nullptr },
    prev_leaf{ nullptr },
    parent{ nullptr } {}

template<typename DataType>
BPlusTree<DataType>::BPlusTree(unsigned minimum_degree) :
    _minimum_degree{ minimum_degree < 2 ? 2 : minimum_degree },
    _min_node_fill{ minimum_degree < 2 ? 1 : minimum_degree - 1 },
    _max_node_fill{ minimum_degree < 2 ? 3 : 2 * minimum_degree - 1 },
    _root{ (std::make_shared<BPlusNode<DataType>>()) } {
    _root->leaf = true;
}

template<typename DataType>
template<typename OStream>
void BPlusTree<DataType>::_printStep(OStream& output, std::shared_ptr<BPlusNode<DataType>> node, int level) {
    output << '|';
    for (int i = 0; i < level; i++) {
        output << '\t' << '|';
    }

    if (!node.get()) {
        output << "*\n";
    }
    else {
        output << "Data: (" << node->size << ")\n";

        for (auto& item : node->data) {
            output << '|';
            for (int i = 0; i < level; i++) {
                output << '\t' << '|';
            }
            output << item << "\n";
        }

        if (!node->leaf) {
            output << '|';
            for (int i = 0; i < level; i++) {
                output << '\t' << '|';
            }
            output << "Children:\n";
            for (auto& item : node->children) {
                _printStep(output, item, level + 1);
            }
        }
    }
    output << '|';
    for (int i = 0; i < level; i++) {
        output << '\t' << '|';
    }
    output << "=====\n";
}

template<typename DataType>
template<typename OStream>
void BPlusTree<DataType>::print(OStream& output) {
    _printStep(output, _root, 0);
}

template<typename DataType>
template<typename OStream>
void BPlusTree<DataType>::printSorted(OStream& output) {
    Node_ptr ptr = _root;
    while (!ptr->leaf) {
        ptr = ptr->children[0];
    }

    int i = 0;
    while (ptr.get()) {
        for (auto& item : ptr->data) {
            output << ++i << ") " << item << "\n";
        }
        ptr = ptr->next_leaf;
    }
}

template<typename DataType>
std::pair<std::shared_ptr<BPlusNode<DataType>>, unsigned>
BPlusTree<DataType>::_subtree_search(std::shared_ptr<BPlusNode<DataType>> subtree_root, const DataType& key) {
    if (subtree_root->leaf) {
        auto it = std::find(subtree_root->data.begin(), subtree_root->data.end(), key);
        if (it != subtree_root->data.end()) {
            return { subtree_root, std::distance(subtree_root->data.begin(), it) };
        }
        else {
            return { nullptr, 0 };
        }
    }
    else {
        unsigned index = 0;
        while (index < subtree_root->size && key >= subtree_root->data[index]) {
            index++;
        }
        return _subtree_search(subtree_root->children[index], key);
    }
}

template<typename DataType>
bool BPlusTree<DataType>::includes(const DataType& key) {
    return _subtree_search(_root, key).first.get();
}

template<typename DataType>
void BPlusTree<DataType>::_split_node(std::shared_ptr<BPlusNode<DataType>> node) {
    unsigned split_index = (node->size / 2);
    std::vector<DataType> data_first_part(node->data.begin(), node->data.begin() + split_index);
    std::vector<DataType> data_second_part(node->data.begin() + split_index, node->data.end());

    std::vector<Node_ptr> children_first_part(node->children.begin(), node->children.begin() + split_index + 1);
    std::vector<Node_ptr> children_second_part(node->children.begin() + split_index + 1, node->children.end());
    children_second_part.insert(children_second_part.begin(), nullptr);

    node->data = data_first_part;
    node->size = data_first_part.size();
    node->children = children_first_part;

    Node_ptr new_node = std::make_shared<BPlusNode<DataType>>();
    new_node->leaf = node->leaf;
    new_node->data = data_second_part;
    new_node->size = data_second_part.size();
    new_node->children = children_second_part;
    for (auto& item : new_node->children) {
        if (item.get()) {
            item->parent = new_node;
        }
    }

    if (!node->parent.get()) {
        Node_ptr new_parent = std::make_shared<BPlusNode<DataType>>();
        new_parent->leaf = false;
        new_parent->size = 1;
        new_parent->data = { data_second_part.front() };
        new_parent->children = { node, new_node };

        node->parent = new_parent;
        new_node->parent = new_parent;

        _root = new_parent;
    }
    else {
        Node_ptr parent = node->parent;
        new_node->parent = node->parent;
        unsigned index = 0; //max index of element, smaller than element to insert
        while (index < parent->size && data_second_part.front() > parent->data[index]) {
            index++;
        }

        parent->data.insert(parent->data.begin() + index, data_second_part.front());
        parent->size++;
        parent->children.insert(parent->children.begin() + index + 1, new_node);

        if (parent->size > _max_node_fill) {
            _split_node(parent);
        }
    }


    if (node->next_leaf.get()) {
        new_node->next_leaf = node->next_leaf;
        node->next_leaf->prev_leaf = new_node;
    }
    node->next_leaf = new_node;
    new_node->prev_leaf = node;
}

template<typename DataType>
std::pair<std::shared_ptr<BPlusNode<DataType>>, unsigned>
BPlusTree<DataType>::_subtree_insert(std::shared_ptr<BPlusNode<DataType>> subtree_root, const DataType& key) {
    if (subtree_root->leaf) {
        unsigned index = 0; //max index of element, smaller than key
        while (index < subtree_root->size && key > subtree_root->data[index]) {
            index++;
        }
        if (subtree_root->data.empty()) {
            subtree_root->data.push_back(key);
            subtree_root->children.push_back(Node_ptr(nullptr));
            subtree_root->children.push_back(Node_ptr(nullptr));
        }
        else {
            subtree_root->data.insert(subtree_root->data.begin() + index, key);
            subtree_root->children.push_back(Node_ptr(nullptr));
        }
        subtree_root->size++;

        if (subtree_root->size > _max_node_fill) {
            _split_node(subtree_root);
        }

        return { subtree_root, index };

    }
    else {
        unsigned index = 0; //index of child where key should be insert
        while (index < subtree_root->size && key >= subtree_root->data[index]) {
            index++;
        }

        _subtree_insert(subtree_root->children[index], key);
    }

    return std::pair<Node_ptr, unsigned int>();
}

template<typename DataType>
void BPlusTree<DataType>::insert(const DataType& key) {
    if (!_root.get()) {
        _root = std::make_shared<BPlusNode<DataType>>();
        _root->leaf = true;
    }
    _subtree_insert(_root, key);
}

template<typename DataType>
void BPlusTree<DataType>::_remove_from_node(BPlusTree::Node_ptr node, unsigned index) {
    auto key = node->data[index];
    node->data.erase(node->data.begin() + index);
    node->children.erase(node->children.begin() + index + 1);
    node->size--;

    if (node == _root && node->size == 0) {
        _root = node->children[0];
        return;
    }
    if (node == _root) return;


    auto parent = node->parent;
    unsigned child_index = std::distance(parent->data.begin(),
        std::find_if(parent->data.begin(), parent->data.end(),
            [&key](const DataType& item) { return item > key; }));

    if (child_index > 0) parent->data[child_index - 1] = node->data[0];

    if (node->size >= _min_node_fill) return;

    auto left_sib = (child_index != 0) ? parent->children[child_index - 1] : nullptr;
    auto right_sib = (child_index < parent->size) ? parent->children[child_index + 1] : nullptr;

    if (left_sib.get() && left_sib->size - 1 >= _min_node_fill) {
        //take max element from left_sib;
        node->data.insert(node->data.begin(), left_sib->data.back());
        left_sib->data.pop_back();

        node->children.insert(node->children.begin() + 1, left_sib->children.back());
        left_sib->children.pop_back();

        node->size++;
        left_sib->size--;

        parent->data[child_index - 1] = node->data[0];
        return;
    }

    if (right_sib.get() && right_sib->size - 1 >= _min_node_fill) {
        //take min element from right_sib;
        node->data.push_back(right_sib->data[0]);
        right_sib->data.erase(right_sib->data.begin());

        node->children.push_back(right_sib->children[1]);
        right_sib->children.erase(right_sib->children.begin() + 1);

        node->size++;
        right_sib->size--;

        parent->data[child_index] = right_sib->data[0];
        return;
    }

    if (left_sib.get()) {
        //merge node with left_sib; recursively delete corresponding constraint element from parent;
        unsigned new_size = node->size + left_sib->size;

        std::vector<DataType> new_data;
        new_data.reserve(new_size);
        new_data.insert(new_data.end(), left_sib->data.begin(), left_sib->data.end());
        new_data.insert(new_data.end(), node->data.begin(), node->data.end());

        std::vector<Node_ptr> new_children;
        new_children.reserve(new_size + 1);
        new_children.insert(new_children.end(), left_sib->children.begin(), left_sib->children.end());
        new_children.insert(new_children.end(), node->children.begin() + 1, node->children.end());

        for (auto& item : new_children) {
            if (item.get())item->parent = left_sib;
        }

        left_sib->size = new_size;
        left_sib->data = new_data;
        left_sib->children = new_children;

        if (node->next_leaf.get()) {
            node->next_leaf->prev_leaf = left_sib;
            left_sib->next_leaf = node->next_leaf;
        }

        _remove_from_node(node->parent, child_index - 1);

        return;
    }

    if (right_sib.get()) {
        //merge node with right_sib; recursively delete corresponding constraint element from parent;
        unsigned new_size = node->size + right_sib->size;

        std::vector<DataType> new_data;
        new_data.reserve(new_size);
        new_data.insert(new_data.end(), node->data.begin(), node->data.end());
        new_data.insert(new_data.end(), right_sib->data.begin(), right_sib->data.end());

        std::vector<Node_ptr> new_children;
        new_children.reserve(new_size + 1);
        new_children.insert(new_children.end(), node->children.begin(), node->children.end());
        new_children.insert(new_children.end(), right_sib->children.begin() + 1, right_sib->children.end());

        for (auto& item : new_children) {
            if (item.get()) item->parent = node;
        }

        node->size = new_size;
        node->data = new_data;
        node->children = new_children;

        if (right_sib->next_leaf.get()) {
            right_sib->next_leaf->prev_leaf = node;
            node->next_leaf = right_sib->next_leaf;
        }

        _remove_from_node(node->parent, child_index);
        return;
    }
}


template<typename DataType>
void BPlusTree<DataType>::remove(const DataType& key) {
    auto node = _subtree_search(_root, key).first;
    auto index = _subtree_search(_root, key).second;
    if (!node) return;

    _remove_from_node(node, index);
}