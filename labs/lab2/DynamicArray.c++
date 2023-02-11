// Aaron Bun, Aidan Kelly, Hannah Naphosaysavath, Olugbenga Olufasola

#include "DynamicArray.hpp"

#include <cstring>

DynamicArray::DynamicArray()
    : m_length(0), m_capacity(0), m_scaling_factor(2.0), m_data(nullptr) {
}

DynamicArray::DynamicArray(double scaling_factor, unsigned int capacity) {
    m_length = 0;
    m_capacity = capacity;
    m_scaling_factor = scaling_factor;
    m_data = new int[m_capacity];
}

DynamicArray::DynamicArray(double scaling_factor, unsigned int length, int default_value) {
    m_length = length;
    m_capacity = length;
    m_scaling_factor = scaling_factor;
    m_data = new int[m_capacity];

    for (int i = 0; i < m_capacity; i++) {
        m_data[i] = default_value;
    }
}

DynamicArray::DynamicArray(const DynamicArray &other) {
    // use the assignment operator
    (*this) = other;
}

DynamicArray::~DynamicArray() {
    delete[] m_data;
}

unsigned int DynamicArray::getLength() {
    return m_length;
}

unsigned int DynamicArray::getCapacity() {
    return m_capacity;
}

double DynamicArray::getScalingFactor() {
    return m_scaling_factor;
}

void DynamicArray::setScalingFactor(double value) {
    m_scaling_factor = value;
}

std::string DynamicArray::toString() {
    if (m_length == 0) return "{}";
    
    std::string str("{");

    for (int i = 0; i < m_length - 1; i++) {
        str += std::to_string(m_data[i]) + " ";
    }

    str += std::to_string(m_data[m_length - 1]) + "}";
    return str;
}

void DynamicArray::append(int value) {
    m_length++;

    if (m_length > m_capacity) {
        m_capacity *= m_scaling_factor;
        int *temp = new int[m_capacity];

        for (int i = 0; i < m_length; i++) {
            temp[i] = m_data[i];
        }

        delete[] m_data;
        m_data = temp;
    }

    m_data[m_length - 1] = value;
}

void DynamicArray::prepend(int value) {
    m_length++;

    if (m_length > m_capacity) {
        m_capacity *= m_scaling_factor;
    }

    int *temp = new int[m_capacity];

    for (int i = 0; i < m_length; i++) {
        temp[i + 1] = m_data[i];
    }

    delete[] m_data;
    m_data = temp;

    m_data[0] = value;
}

bool DynamicArray::findFirstOf(int value, unsigned int *index) {
    for (int i = 0; i < m_length; i++) {
        if (m_data[i] == value) {
            *index = i;
            return true;
        }
    }
    return false;
}

bool DynamicArray::findLastOf(int value, unsigned int *index) {
    for (int i = m_length - 1; i >= 0; i--) {
        if (m_data[i] == value) {
            *index = i;
            return true;
        }
    }
    return false;
}

void DynamicArray::removeLast() {
    m_length--;
    if (m_length < (m_capacity / 4)) {
        m_capacity /= 2;
        int *temp = new int[m_capacity];

        for (int i = 0; i < m_length + 1; i++) {
            temp[i] = m_data[i];
        }

        delete[] m_data;
        m_data = temp;
    }
}

void DynamicArray::removeFirst() {
    m_length--;

    if (m_length < (m_capacity / 4)) {
        m_capacity /= 2;
    }

    int *temp = new int[m_capacity];

    for (int i = 1; i < m_length + 1; i++) {
        temp[i - 1] = m_data[i];
    }

    delete[] m_data;
    m_data = temp;
}

void DynamicArray::clear() {
    m_length = 0;
    m_capacity = 0;
    delete[] m_data;
    m_data = nullptr;
}

int &DynamicArray::operator[](unsigned int index) {
    return m_data[index];
}

DynamicArray &DynamicArray::operator=(const DynamicArray &other) {
    m_length = other.m_length;
    m_capacity = other.m_capacity;
    m_scaling_factor = other.m_scaling_factor;
    m_data = new int[m_capacity];
    std::memcpy(m_data, other.m_data, sizeof(int) * m_length);
    // this allows statements such as (a = b = c) assuming a, b, and c are all the DynamicArray type
    return (*this);
}
