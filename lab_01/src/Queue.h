template<typename T>
class Queue {
private:
	T* m_Array{nullptr};
	int m_Size{0};
public:
	Queue() {};
	Queue(int nSize) : m_Size(nSize), m_Array(new T[nSize]) {};
	~Queue() {
		delete[] m_Array;
		m_Array = nullptr;
		m_Size = 0;
	};
	void push(T value) {
		T* buffer = new T[m_Size + 1];
		for (int i = 0; i < m_Size; i++) {
			buffer[i] = m_Array[i];
		}

		buffer[m_Size] = value;

		delete[] m_Array;
		m_Array = buffer;

		m_Size++;
		return;
	}
	void pop() {
		T* buffer = new T[m_Size - 1];
		for (int i = 1; i < m_Size; i++) {
			buffer[i - 1] = m_Array[i];
		}

		delete[] m_Array;
		m_Array = buffer;

		m_Size--;
	}

	T peek() {
		return m_Array[0];
	}

	int count() {
		return m_Size;
	}

	int concat() {
		int result = 0;

		for (int i = 0; i < m_Size; i++) {
			int num1 = m_Array[i];
			int times = 0;
			int multiplyFactor = 10;
			while (num1 >= 10) {
				num1 /= 10;
				times++;
			}
			for (int i = 0; i < times; i++) {
				multiplyFactor *= 10;
			}
			result *= multiplyFactor;
			result += m_Array[i];
		}

		return result;
	}
};
template <typename T>
int operator + (const Queue<T>& left, const Queue<T>& right) {
	int num1 = left.concat();
	int concat1 = num1;
	int concat2 = right.concat();

	int times = 0;
	int multiplyFactor = 10;
	while (num1 >= 10) {
		num1 /= 10;
		times++;
	}
	for (int i = 0; i < times; i++) {
		multiplyFactor *= 10;
	}
	concat1 *= multiplyFactor;
	concat1 += concat2;

	return concat1;
}
template <typename T>
bool operator == (Queue<T>& queue1, Queue<T>& queue2) {
	int size1 = queue1.count();
	int size2 = queue2.count();

	int size;

	if (size1 < size2) size = size1;
	else size = size2;

	for (int i = 0; i < size; i++) {
		T num1 = queue1.m_Array[i];
		T num2 = queue2.m_Array[i];
		if (num1 != num2) {
			return false;
		}
		else {
			continue;
		}
	}

	if (queue1.count() == queue2.count()) return true;
	return false;
}
template <typename T>
bool operator != (Queue<T>& queue1, Queue<T>& queue2) {
	if (queue1 == queue2) return false;
	return true;
}
template <typename T>
bool operator > (Queue<T>& queue1, Queue<T>& queue2) {
	int size1 = queue1.count();
	int size2 = queue2.count();

	int size;

	if (size1 < size2) size = size1;
	else size = size2;

	for (int i = 0; i < size; i++) {
		T num1 = queue1.m_Array[i];
		T num2 = queue2.m_Array[i];
		if (num1 != num2) {
			if (num1 < num2) {
				return false;
			}
			else {
				return true;
			}
		}
		else {
			continue;
		}
	}

	if (queue1.count() <= queue2.count()) return false;
	return true;
}
template <typename T>
bool operator < (Queue<T>& queue1, Queue<T>& queue2) {
	int size1 = queue1.count();
	int size2 = queue2.count();

	int size;

	if (size1 < size2) size = size1;
	else size = size2;

	for (int i = 0; i < size; i++) {
		T num1 = queue1.m_Array[i];
		T num2 = queue2.m_Array[i];
		if (num1 != num2) {
			if (num1 < num2) {
				return true;
			}
			else {
				return false;
			}
		}
		else {
			continue;
		}
	}

	if (queue1.count() < queue2.count()) return true;
	return false;
}
template <typename T>
bool operator >= (Queue<T>& queue1, Queue<T>& queue2) {
	if ((queue1 > queue2) || (queue1 == queue2)) return true;
	return false;
}
template <typename T>
bool operator <= (Queue<T>& queue1, Queue<T>& queue2) {
	if ((queue1 < queue2) || (queue1 == queue2)) return true;
	return false;
}
