#include <memory>
#include <vector>
//клас для опису вузла В+ -дерева ,зберігає список ключів і список дітей
template<typename DataType>
class BPlusNode {
    typedef std::shared_ptr<BPlusNode> Node_ptr;
public:
    bool leaf;
    unsigned size;
    std::vector<DataType> data;
    std::vector<Node_ptr> children;
    Node_ptr next_leaf;
    Node_ptr prev_leaf;
    Node_ptr parent;
    //конструктор
    BPlusNode();
};

//клас для опису самого В+ -дерева
template<typename DataType>
class BPlusTree {
    typedef std::shared_ptr<BPlusNode<DataType>> Node_ptr;
private:
    unsigned _minimum_degree;
    unsigned _min_node_fill;
    unsigned _max_node_fill;
    Node_ptr _root;

    template<typename OStream>
    void _printStep(OStream& output, std::shared_ptr<BPlusNode<DataType>> node, int level);//функція виводить деерево на консоль

    std::pair<Node_ptr,unsigned> _subtree_search(std::shared_ptr<BPlusNode<DataType>> subtree_root, const DataType& key);//пошук ключа у піддерві

    void _split_node(std::shared_ptr<BPlusNode<DataType>> node);//функція розєднує деерво на два піддерева

    std::pair<Node_ptr,unsigned> _subtree_insert(std::shared_ptr<BPlusNode<DataType>> subtree_root, const DataType& key);//вставка ключа у піддерево

    void _remove_from_node(Node_ptr node, unsigned index);//видалення ключа з піддерева

public:
    explicit BPlusTree(unsigned minimum_degree = 2);//конструктор

    template<typename OStream>
    void print(OStream& output);//функція виводить дерево на екран

    template<typename OStream>
    void printSorted(OStream& output);//функція виводить списки ключів у порядку зростання

    bool includes(const DataType& key);//функція перевіряє на входження ключа в деерво

    void insert(const DataType& key);//функція вставки 

    void remove(const DataType& key);//функція видалення 
};