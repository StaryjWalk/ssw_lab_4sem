#ifndef _CustomList;
#define _CustomList
	#include "customlist.h"
#endif
struct RlkCell {
	int value;
	RlkCell* next;
	RlkCell(int val) {
		value = val;
		next = nullptr;
	}
};
class Rlk : public CustomList {
private:
	unsigned int m_Count;
	RlkCell* m_BeginAddress;
	RlkCell* m_EndAddress;
	unsigned int m_Size;
public:
	RlkCell* getBeginAddress() { return m_BeginAddress; }
	int* MinMaxList() {
		if (m_Count == 1) return new int[2]{ m_BeginAddress->value,m_BeginAddress->value };

		int* toReturn = new int[2]{ 0,0 };
		RlkCell* tempCell = m_BeginAddress;
		int* toReturnIndex = new int[2]{ 0,0 };
		toReturn[0] = tempCell->value;
		toReturn[1] = tempCell->value;
		for (int i = 0; i < m_Count; i++) {
			if (tempCell->value < toReturn[0]) {
				toReturn[0] = tempCell->value;
				toReturnIndex[0] = i;
			}
			if (tempCell->value > toReturn[1]) {
				toReturn[1] = tempCell->value;
				toReturnIndex[1] = i;
			}
			tempCell = tempCell->next;
		}
		if (toReturnIndex[0] > toReturnIndex[1]) {
			Erase(toReturnIndex[1]);
			Erase(toReturnIndex[0] - 1);
		}
		else {
			Erase(toReturnIndex[0]);
			Erase(toReturnIndex[1] - 1);
		}

		return toReturn;
	}
	int* at(unsigned int index) override {
		if (index > m_Count - 1) return nullptr;
		RlkCell* tempCell = m_BeginAddress;
		for (int i = 0; i < index; i++) {
			tempCell = tempCell->next;
		}
		return &tempCell->value;
	}
	Rlk(unsigned int size) {
		m_Size = size;
		m_Count = 0;
		m_EndAddress = nullptr;
		m_BeginAddress = nullptr;
	}
	~Rlk() {
		m_Size = 0;
		m_EndAddress = nullptr;
		m_BeginAddress = nullptr;
		m_Count = 0;
	}
	void Push(int value) {
		if (m_Count >= m_Size) return;
		RlkCell* cellTP = new RlkCell(value);
		if (m_Count == 0) {
			m_BeginAddress = cellTP;
			m_EndAddress = cellTP;
			m_EndAddress->next = m_BeginAddress;
		}
		else {
			m_EndAddress->next = cellTP;
			m_EndAddress = cellTP;
			m_EndAddress->next = m_BeginAddress;
		}
		m_Count++;
	}
	int Pop() {
		int* tempValue;
		if (m_Count > m_Size&& m_Count > 0) return 0;
		if (m_Count == 1) {
			tempValue = &m_EndAddress->value;
			m_BeginAddress = nullptr;
			m_EndAddress = nullptr;
		}
		else {
			RlkCell* tempCell = m_BeginAddress;
			for (int i = 0; i < m_Count - 2; i++) {
				tempCell = tempCell->next;
			}
			tempValue = &m_EndAddress->value;
			m_EndAddress = tempCell;
			tempCell->next = m_BeginAddress;
		}
		m_Count--;
		return *tempValue;
	}
	void Insert(int value, int index) {
		if (m_Count >= m_Size) return;
		RlkCell* cellTP = new RlkCell(value);
		if (index == 0) {
			if (m_Count == 0) {
				m_BeginAddress = cellTP;
				m_EndAddress = cellTP;
				m_EndAddress->next = m_BeginAddress;
			}
			else {
				cellTP->next = m_BeginAddress;
				m_BeginAddress = cellTP;
				m_EndAddress->next = m_BeginAddress;
			}
		}
		else if (index == m_Count) {
			m_EndAddress->next = cellTP;
			m_EndAddress = cellTP;
			m_EndAddress->next = m_BeginAddress;
		}
		else {
			RlkCell* tempCell = m_BeginAddress;
			for (int i = 0; i < index - 1; i++) {
				tempCell = tempCell->next;
			}
			cellTP->next = tempCell->next;
			tempCell->next = cellTP;
		}
		m_Count++;
	}
	void Erase(int index) {
		if (index >= m_Count && index < 0) return;
		if (index == 0) {
			if (m_Count == 0) {
				m_BeginAddress = nullptr;
				m_EndAddress = nullptr;
			}
			else {
				m_EndAddress->next = m_BeginAddress->next;
				m_BeginAddress = m_BeginAddress->next;
			}
		}
		else if (index == m_Count - 1) {
			RlkCell* tempCell = m_BeginAddress;
			for (int i = 0; i < m_Count - 2; i++) {
				tempCell = tempCell->next;
			}
			m_EndAddress = tempCell;
			m_EndAddress->next = m_BeginAddress;
		}
		else {
			RlkCell* tempCell = m_BeginAddress;
			for (int i = 0; i < index - 1; i++) {
				tempCell = tempCell->next;
			}
			tempCell->next = tempCell->next->next;
		}
		m_Count--;
	}
	RlkCell* begin() {
		return m_BeginAddress;
	}
	RlkCell* end() {
		return m_EndAddress;
	}
	unsigned int count() override {
		return m_Count;
	}
};
bool operator > (Rlk& rlk1, Rlk& rlk2) {
	if (rlk1.count() > rlk2.count()) {
		return true;
	}
	else if (rlk1.count() < rlk2.count()) {
		return false;
	}
	else {
		RlkCell* cell1 = rlk1.getBeginAddress();
		RlkCell* cell2 = rlk2.getBeginAddress();
		for (int i = 0; i < rlk1.count(); i++) {
			if (cell1->value != cell2->value) {
				if (cell1->value > cell2->value) {
					return true;
				}
				else {
					return false;
				}
			}
			cell1 = cell1->next;
			cell2 = cell2->next;
		}
		return false;
	}
}
bool operator == (Rlk& rlk1, Rlk& rlk2) {
	if (rlk1.count() != rlk2.count()) {
		return false;
	}
	RlkCell* cell1 = rlk1.getBeginAddress();
	RlkCell* cell2 = rlk2.getBeginAddress();
	for (int i = 0; i < rlk1.count(); i++) {
		if (cell1->value != cell2->value) {
			return false;
		}
		cell1 = cell1->next;
		cell2 = cell2->next;
	}
	return true;
}
bool operator != (Rlk& rlk1, Rlk& rlk2) {
	return !(rlk1 == rlk2);
}
bool operator < (Rlk& rlk1, Rlk& rlk2) {
	return (!(rlk1 > rlk2)) && (rlk1 != rlk2);
}
bool operator <= (Rlk& rlk1, Rlk& rlk2) {
	return (rlk1 < rlk2) || (rlk1 == rlk2);
}
bool operator >= (Rlk& rlk1, Rlk& rlk2) {
	return (rlk1 > rlk2) || (rlk1 == rlk2);
}