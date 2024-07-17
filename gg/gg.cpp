#include <iostream>
#include <stdexcept>
#include <cstring>
using namespace std;

template <typename T>
class Array {
private:
    T* data;
    int size;
    int capacity;
    int grow;

public:
    Array(int size = 0, int grow = 1)
        : size(size), capacity(size), grow(grow) {
        if (size < 0) {
            throw invalid_argument("Size cannot be negative");
        }
        data = size > 0 ? new T[size] : nullptr;
    }

    ~Array() {
        delete[] data;
    }

    int GetSize() const {
        return size;
    }

    void SetSize(int newSize, int grow = 1) {
        if (newSize < 0) {
            throw invalid_argument("Size cannot be negative");
        }
        this->grow = grow;
        if (newSize > capacity) {
            T* newData = new T[newSize];
            if (data != nullptr) {
                memcpy(newData, data, size * sizeof(T));
                delete[] data;
            }
            data = newData;
            capacity = newSize;
        }
        else if (newSize < size) {
            T* newData = new T[newSize];
            if (data != nullptr) {
                memcpy(newData, data, newSize * sizeof(T));
                delete[] data;
            }
            data = newData;
            capacity = newSize;
        }
        size = newSize;
    }

    int GetUpperBound() const {
        return size - 1;
    }

    bool IsEmpty() const {
        return size == 0;
    }

    void FreeExtra() {
        if (size < capacity) {
            T* newData = new T[size];
            if (data != nullptr) {
                memcpy(newData, data, size * sizeof(T));
                delete[] data;
            }
            data = newData;
            capacity = size;
        }
    }

    void RemoveAll() {
        delete[] data;
        data = nullptr;
        size = 0;
        capacity = 0;
    }

    T GetAt(int index) const {
        if (index < 0 || index >= size) {
            throw out_of_range("Index out of range");
        }
        return data[index];
    }

    void SetAt(int index, const T& value) {
        if (index < 0 || index >= size) {
            throw out_of_range("Index out of range");
        }
        data[index] = value;
    }

    T& operator[](int index) {
        if (index < 0 || index >= size) {
            throw out_of_range("Index out of range");
        }
        return data[index];
    }

    const T& operator[](int index) const {
        if (index < 0 || index >= size) {
            throw out_of_range("Index out of range");
        }
        return data[index];
    }

    void Add(const T& value) {
        if (size == capacity) {
            SetSize(size + grow);
        }
        data[size++] = value;
    }

    void Append(const Array& other) {
        int newSize = size + other.size;
        if (newSize > capacity) {
            SetSize(newSize);
        }
        for (int i = 0; i < other.size; ++i) {
            data[size++] = other.data[i];
        }
    }

    Array& operator=(const Array& other) {
        if (this != &other) {
            delete[] data;
            size = other.size;
            capacity = other.capacity;
            grow = other.grow;
            data = new T[capacity];
            memcpy(data, other.data, size * sizeof(T));
        }
        return *this;
    }

    T* GetData() {
        return data;
    }

    const T* GetData() const {
        return data;
    }

    void InsertAt(int index, const T& value) {
        if (index < 0 || index > size) {
            throw out_of_range("Index out of range");
        }
        if (size == capacity) {
            SetSize(size + grow);
        }
        for (int i = size; i > index; --i) {
            data[i] = data[i - 1];
        }
        data[index] = value;
        ++size;
    }

    void RemoveAt(int index) {
        if (index < 0 || index >= size) {
            throw out_of_range("Index out of range");
        }
        for (int i = index; i < size - 1; ++i) {
            data[i] = data[i + 1];
        }
        --size;
        if (size < capacity - grow) {
            FreeExtra();
        }
    }
};

int main() {
    try {
        Array<int> arr(5, 3);
        arr.SetAt(0, 1);
        arr.SetAt(1, 2);
        arr.SetAt(2, 3);
        arr.SetAt(3, 4);
        arr.SetAt(4, 5);

        cout << "Initial array: ";
        for (int i = 0; i < arr.GetSize(); ++i) {
            cout << arr[i] << " ";
        }
        cout << endl;

        arr.Add(6);
        cout << "After adding 6: ";
        for (int i = 0; i < arr.GetSize(); ++i) {
            cout << arr[i] << " ";
        }
        cout << endl;

        arr.InsertAt(2, 99);
        cout << "After inserting 99 at index 2: ";
        for (int i = 0; i < arr.GetSize(); ++i) {
            cout << arr[i] << " ";
        }
        cout << endl;

        arr.RemoveAt(3);
        cout << "After removing element at index 3: ";
        for (int i = 0; i < arr.GetSize(); ++i) {
            cout << arr[i] << " ";
        }
        cout << endl;

        Array<int> arr2(2);
        arr2.SetAt(0, 100);
        arr2.SetAt(1, 200);
        arr.Append(arr2);
        cout << "After appending another array: ";
        for (int i = 0; i < arr.GetSize(); ++i) {
            cout << arr[i] << " ";
        }
        cout << endl;

        cout << "Size of array: " << arr.GetSize() << endl;
        cout << "Upper bound of array: " << arr.GetUpperBound() << endl;
        cout << "Is array empty? " << (arr.IsEmpty() ? "Yes" : "No") << endl;

        arr.RemoveAll();
        cout << "After removing all elements, is array empty? " << (arr.IsEmpty() ? "Yes" : "No") << endl;
    }
    catch (const exception& e) {
        cout << "Exception: " << e.what() << endl;
    }

}