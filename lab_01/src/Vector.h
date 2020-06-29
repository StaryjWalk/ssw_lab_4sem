template <typename T>
class Vector {
private:
	T* m_Array{nullptr};
	int m_Size{0};
public:
	Vector() {};
	Vector(int nSize) : m_Array(new T[nSize]), m_Size(nSize) {
	}
	~Vector() {
		delete[] m_Array;
		m_Array = nullptr;
		m_Size = 0;
	}
	void push(T value)
	{
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
	void pop()
	{
		T* buffer = new T[m_Size - 1];
		for (int i = 0; i < m_Size - 1; i++) {
			buffer[i] = m_Array[i];
		}

		delete[] m_Array;
		m_Array = buffer;

		m_Size--;
		return;
	}

	T peek()
	{
		return m_Array[m_Size - 1];
	}

	int count()
	{
		return m_Size;
	}

	T* at(int index)
	{
		if (index < 0 || index >= m_Size) {
			return nullptr;
		}
		return &m_Array[index];
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
int operator + (const Vector<T>& left, const Vector<T>& right) {
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
bool operator == (Vector<T>& vec1, Vector<T>& vec2) {

	int size1 = vec1.count();
	int size2 = vec2.count();

	int size;

	if (size1 < size2) size = size1;
	else size = size2;

	for (int i = 0; i < size; i++) {
		T* num1 = vec1.at(i);
		T* num2 = vec2.at(i);
		if (*num1 != *num2) {
			return false;
		}
		else {
			continue;
		}
	}

	if (vec1.count() == vec2.count()) return true;
	return false;
};
template <typename T>
bool operator != (Vector<T>& vec1, Vector<T>& vec2) {
	if (vec1 == vec2) return false;
	return true;
}
template <typename T>
bool operator > (Vector<T>& vec1, Vector<T>& vec2) {

	int size1 = vec1.count();
	int size2 = vec2.count();

	int size;

	if (size1 < size2) size = size1;
	else size = size2;

	for (int i = 0; i < size; i++) {
		T* num1 = vec1.at(i);
		T* num2 = vec2.at(i);
		if (*num1 != *num2) {
			if (*num1 < *num2) {
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

	if (vec1.count() <= vec2.count()) return false;
	return true;
};
template <typename T>
bool operator < (Vector<T>& vec1, Vector<T>& vec2) {
	int size1 = vec1.count();
	int size2 = vec2.count();

	int size;

	if (size1 < size2) size = size1;
	else size = size2;

	for (int i = 0; i < size; i++) {
		T* num1 = vec1.at(i);
		T* num2 = vec2.at(i);
		if (*num1 != *num2) {
			if (*num1 < *num2) {
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

	if (vec1.count() < vec2.count()) return true;
	return false;
};
template <typename T>
bool operator >= (Vector<T>& vec1, Vector<T>& vec2) {
	if ((vec1 > vec2) || (vec1 == vec2)) return true;
	return false;
}
template <typename T>
bool operator <= (Vector<T>& vec1, Vector<T>& vec2) {
	if ((vec1 < vec2) || (vec1 == vec2)) return true;
	return false;
}
