#include <iostream>

template <typename T>
class VectorLite {
private:
	uint8_t capacity_;     // 1byte
	uint8_t currentSize_;  // 1byte
	T* arr_;               // 8byte

public:
	VectorLite() {
		arr_ = nullptr;
		capacity_ = 0;
		currentSize_ = 0;
	}

	void push(T data) {
		if (capacity_ == 0) {
			resize(1);
		} else if (currentSize_ == capacity_) {
			T* temp = new T[2 * capacity_];
			for (uint8_t i = 0; i < capacity_; i++) {
				temp[i] = arr_[i];
			}
			if (arr_ != nullptr) {
				delete[] arr_;
			}
			capacity_ *= 2;
			arr_ = temp;
		}
		arr_[currentSize_] = data;
		currentSize_++;
	}

	void push(T data, uint8_t index) {
		if (index == capacity_)
			push(data);
		else
			arr_[index] = data;
	}

	T& at(uint8_t index) {
		return arr_[index];
	}

	uint8_t size() {
		return currentSize_;
	}

	uint8_t capacity() {
		return capacity_;
	}

	void print() {
		for (uint8_t i = 0; i < currentSize_; i++) {
			std::cout << arr_[i] << " ";
		}
		std::cout << std::endl;
	}

	void resize(uint8_t new_size) {
		T* temp = new T[new_size];
		for (uint8_t i = 0; i < currentSize_; i++) {
			temp[i] = arr_[i];
		}
		if (arr_ != nullptr) {
			delete[] arr_;
		}

		arr_ = temp;
		capacity_ = new_size;
	}

	T& operator[](uint8_t index) {
		return arr_[index];
	}

	T* begin() {
		if (currentSize_ == 0) {
			return nullptr;
		}
		return &arr_[0];
	}

	T* end() {
		return &arr_[currentSize_ - 1];
	}
};
