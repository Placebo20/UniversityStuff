#include <iostream>
#include <cmath>
#include <ctime>
#include <fstream>
#include <random>

const int FILES = 5; // > 3
const int N = 4000000;
const int MEMORY_SIZE = 100;
const char SRC_NAME[] = "src.bin";

// === Quick sort ===
void swap(int* a, int* b) { // Swap elements
    int t = *a;
    *a = *b;
    *b = t;
}

int partition(int* arr, int low, int high) { // Partition of the array elements
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quick_sort(int* arr, int low, int high) { // Quick sort of the array or linked list
    if (low < high) {
        int p = partition(arr, low, high);

        quick_sort(arr, low, p - 1);
        quick_sort(arr, p + 1, high);
    }
}

int rand_int(int min, int max) { // create random values
    static std::random_device rd;
    static std::seed_seq seed{ rd(), static_cast<unsigned int>(time(nullptr)) };
    static std::mt19937_64 gen(seed);
    std::uniform_int_distribution<int> dist(min, max);

    return dist(gen);
}

void create_source(int size) { // create the data for two matrixes
    std::ofstream file(SRC_NAME, std::ios_base::out | std::ios_base::binary);
    int num;
    for (int i = 0; i < size; i++) {
        num = rand_int(0, 100);
        file.write(reinterpret_cast<const char*>(&num), sizeof(int));
    }
    file.close();
}

int array_sum(const int* array) { //  The sum of the array elements
    int res = 0;
    for (int i = 0; i < FILES; i++)
        res += array[i];
    return res;
}

int max_index(const int* array) { // The index of the maximal value
    int res = 0;
    for (int i = 1; i < FILES; i++) {
        if (array[i] > array[res]) res = i;
    }
    return res;
}

int min_index(const int* array) { // The index of the minimal value
    int res = 0;
    for (int i = 1; i < FILES; i++) {
        if (array[i] < array[res]) res = i;
    }
    return res;
}

int min_positive_index(const int* array) { //returns index of min except of 0 in array;
    int res = (array[0] != 0) ? 0 : 1;
    for (int i = 1; i < FILES; i++) {
        if ((array[i] < array[res]) && (array[i] != 0)) res = i;
    }
    return res;
}

bool all_int_max(const int* array) { //checks whether all elements of array are INT_MAX;
    bool res = true;
    for (int i = 0; i < FILES; i++) {
        if (array[i] != INT_MAX) res = false;
    }
    return res;

}

struct Node { // A Node of the linked list
    int data[FILES];
    Node* prev = nullptr;

    explicit Node(Node* Prev = nullptr) {
        for (auto& e : data) e = 0;
        prev = Prev;
    }
};

void polyphase_sort() { // The polyphase sort in the files with data
    std::fstream srcFile(SRC_NAME, std::ios_base::in | std::ios_base::binary);

    //determination of input file size;
    srcFile.seekg(0, std::ios_base::end);
    int size = srcFile.tellg() / sizeof(int);
    srcFile.seekg(0, std::ios_base::beg);

    //determination of chunks number in sorting files and merge phases number;
    Node* chunks_number = new Node;
    chunks_number->data[0] = 1;

    int max, i_max; //max value and index of max in chunks_number[];
    int merge_steps = 0;
    int output_file = 0;
    Node* tmp;
    while (array_sum(chunks_number->data) < ceil((double)size / (double)MEMORY_SIZE)) {
        merge_steps++;

        output_file = i_max = max_index(chunks_number->data);
        max = chunks_number->data[i_max];

        tmp = new Node(chunks_number);
        for (int i = 0; i < FILES; i++) {
            tmp->data[i] = chunks_number->data[i] + max;
        }
        tmp->data[i_max] = 0;
        chunks_number = tmp;
    }

    //initial filling of sorting files;
    int total_chunks = array_sum(chunks_number->data);
    int chunk_size = floor((double)size / (double)total_chunks);
    int remainder = size - chunk_size * total_chunks;
    int tmp_array[MEMORY_SIZE];
    const int X = -1;
    std::fstream files[FILES];
    char tmp_name[] = "A.bin";

    for (int i = 0; i < FILES; i++) {
        files[i].open(tmp_name, std::ios_base::out | std::ios_base::binary);

        for (int j = 0; j < chunks_number->data[i]; j++) {
            for (int k = 0; k < chunk_size; k++)
                srcFile.read(reinterpret_cast<char*>(&tmp_array[k]), sizeof(int));

            if (remainder) {
                remainder--;
                srcFile.read(reinterpret_cast<char*>(&tmp_array[chunk_size]), sizeof(int));
                quick_sort(tmp_array, 0, chunk_size);
                for (int k = 0; k < chunk_size + 1; k++) {
                    files[i].write(reinterpret_cast<const char*>(&tmp_array[k]), sizeof(int));
                }
            }
            else {
                quick_sort(tmp_array, 0, chunk_size - 1);
                for (int k = 0; k < chunk_size; k++) {
                    files[i].write(reinterpret_cast<const char*>(&tmp_array[k]), sizeof(int));
                }
            }

            files[i].write(reinterpret_cast<const char*>(&X), sizeof(int));
        }

        files[i].close();
        if (i != output_file)
            files[i].open(tmp_name, std::ios_base::in | std::ios_base::binary);
        else
            files[i].open(tmp_name, std::ios_base::out | std::ios_base::binary);

        tmp_name[0]++;
    }

    //merging files
    int nums[FILES];
    int i_min;
    int i_merge_substeps;
    for (int i = 0; i < merge_steps; i++) {
        i_merge_substeps = min_positive_index(chunks_number->data);

        for (int j = 0; j <
                        chunks_number->data[i_merge_substeps]; j++) {
            tmp_name[0] = 'A';
            for (int k = 0; k < FILES; k++) {
                if (k != output_file) {
                    files[k].read(reinterpret_cast<char*>(&nums[k]), sizeof(int));
                }
                else {
                    nums[k] = INT_MAX;
                }
                tmp_name[0]++;
            }

            while (!all_int_max(nums)) {
                i_min = min_index(nums);

                files[output_file].write(reinterpret_cast<const char*>(&nums[i_min]), sizeof(int));
                files[i_min].read(reinterpret_cast<char*>(&nums[i_min]), sizeof(int));

                if (nums[i_min] == X) nums[i_min] = INT_MAX;
            }
            files[output_file].write(reinterpret_cast<const char*>(&X), sizeof(int));
        }

        files[i_merge_substeps].close();
        tmp_name[0] = 'A' + i_merge_substeps;
        files[i_merge_substeps].open(tmp_name, std::ios_base::out | std::ios_base::binary);

        files[output_file].close();
        tmp_name[0] = 'A' + output_file;
        files[output_file].open(tmp_name, std::ios_base::in | std::ios_base::binary);

        output_file = i_merge_substeps;
        tmp = chunks_number->prev;
        delete chunks_number;
        chunks_number = tmp;
    }
}

int main() {
    create_source(N);
    polyphase_sort();
    return 0;
}


