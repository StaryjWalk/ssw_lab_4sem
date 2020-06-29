#ifndef _CustomList;
#define _CustomList
	#include "customlist.h"
#endif

struct SlkCell {
	int value;
	SlkCell* next;
	SlkCell(int val) {
		value = val;
		next = nullptr;
	}
};
class Slk : public CustomList { //Singly linked list

private:
	SlkCell* m_Address;
	SlkCell* m_BeginAddress;
	SlkCell* m_EndAddress;
	unsigned int m_Count;
public:
	SlkCell* getBeginAddress() { return m_BeginAddress;}
	int* at(unsigned int index) override {
		if (index > m_Count - 1) return nullptr;
		SlkCell* tempCell = m_BeginAddress;
		for (int i = 0; i < index; i++) {
			tempCell = tempCell->next;
		}
		return &tempCell->value;
	}
	Slk() {
		m_Count = 0;
		m_Address = nullptr;
		m_BeginAddress = nullptr;
		m_EndAddress = nullptr;
	}
	~Slk() {
		m_Count = 0;
		m_Address = nullptr;
		m_BeginAddress = nullptr;
		m_EndAddress = nullptr;
	}
	void PushBegin(int value) { //cellTP = Cell To Push
		SlkCell* cellTP = new SlkCell(value);
		if (m_Count == 0) {
			m_Address = cellTP;
			m_BeginAddress = cellTP;
			m_EndAddress = cellTP;
		}
		else {
			cellTP->next = m_BeginAddress;
			m_BeginAddress = cellTP;
		}
		m_Count++;
	}
	void PushEnd(int value) {
		SlkCell* cellTP = new SlkCell(value);
		if (m_Count == 0) {
			m_Address = cellTP;
			m_BeginAddress = cellTP;
			m_EndAddress = cellTP;
		}
		else {
			SlkCell* tempCell = m_BeginAddress;
			for (int i = 0; i < m_Count - 1; i++) {
				tempCell = tempCell->next;
			}
			tempCell->next = cellTP;
			cellTP->next = nullptr;
			m_EndAddress = cellTP;
		}
		m_Count++;
	}
	int PopBegin() {
		int* tempValue;
		if (m_Count == 0) return 0;
		if (m_Count == 1) {
			tempValue = &m_Address->value;
			//free memory of first cell
			m_Address = nullptr;
			m_BeginAddress = nullptr;
			m_EndAddress = nullptr;
		}
		else {
			tempValue = &m_BeginAddress->value;
			//free memory of first cell
			m_BeginAddress = m_BeginAddress->next;
		}
		m_Count--;
		return *tempValue;
	}
	int PopEnd() {
		int* tempValue;
		if (m_Count == 0) return 0;
		if (m_Count == 1) {
			tempValue = &m_Address->value;
			//free memory of first cell
			m_Address = nullptr;
			m_BeginAddress = nullptr;
			m_EndAddress = nullptr;
		}
		else {
			SlkCell* tempCell = m_BeginAddress;
			for (int i = 0; i < m_Count - 2; i++) {
				tempCell = tempCell->next;
			}
			tempValue = &m_EndAddress->value;
			m_EndAddress = tempCell;
		}
		m_Count--;
		return *tempValue;
	}
	void Insert(int value, int index) {
		SlkCell* cellTP = new SlkCell(value);
		if (index > m_Count&& index < 0) return;
		if (index == 0) { // same as push begin
			cellTP->next = m_BeginAddress;
			m_BeginAddress = cellTP;
		}
		else if (index == m_Count) { // same as push end
			SlkCell* tempCell = m_BeginAddress;
			for (int i = 0; i < m_Count - 1; i++) {
				tempCell = tempCell->next;
			}
			tempCell->next = cellTP;
			cellTP->next = nullptr;
			m_EndAddress = cellTP;
		}
		else {
			SlkCell* tempCell = m_BeginAddress;
			for (int i = 0; i < index - 1; i++) {
				tempCell = tempCell->next;
			}
			cellTP->next = tempCell->next;
			tempCell->next = cellTP;
		}
		m_Count++;
	}
	void Erase(int index) {
		if (index > m_Count - 1 && index < 0) return;
		if (index == 0) {
			if (m_Count == 1) {
				//free memory of first cell
				m_Address = nullptr;
				m_BeginAddress = nullptr;
				m_EndAddress = nullptr;
			}
			else {
				m_BeginAddress = m_BeginAddress->next;
			}
		}
		else if (index == m_Count - 1) {
			SlkCell* tempCell = m_BeginAddress;
			for (int i = 0; i < m_Count - 2; i++) {
				tempCell = tempCell->next;
			}
			m_EndAddress = tempCell;
		}
		else {
			SlkCell* tempCell = m_BeginAddress;
			for (int i = 0; i < index - 1; i++) {
				tempCell = tempCell->next;
			}
			tempCell->next = tempCell->next->next;
		}
		m_Count--;
	}
	SlkCell* begin() {
		return m_BeginAddress;
	} // POD VOPROSOM
	SlkCell* end() {
		return m_EndAddress;
	} // POD VOPROSOM
	unsigned int count() override {
		return m_Count;
	}
	int* MinMaxList() {
		if (m_Count == 1) return new int[2]{ m_BeginAddress->value,m_BeginAddress->value };

		int* toReturn = new int[2]{ 0,0 };
		SlkCell* tempCell = m_BeginAddress;
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
};
bool operator > (Slk& slk1, Slk& slk2) {
	if (slk1.count() > slk2.count()) {
		return true;
	}
	else if (slk1.count() < slk2.count()) {
		return false;
	}
	else {
		SlkCell* cell1 = slk1.getBeginAddress();
		SlkCell* cell2 = slk2.getBeginAddress();
		for (int i = 0; i < slk1.count(); i++) {
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
bool operator == (Slk& slk1, Slk& slk2) {
	if (slk1.count() != slk2.count()) {
		return false;
	}
	SlkCell* cell1 = slk1.getBeginAddress();
	SlkCell* cell2 = slk2.getBeginAddress();
	for (int i = 0; i < slk1.count(); i++) {
		if (cell1->value != cell2->value) {
			return false;
		}
		cell1 = cell1->next;
		cell2 = cell2->next;
	}
	return true;
}
bool operator != (Slk& slk1, Slk& slk2) {
	return !(slk1 == slk2);
}
bool operator < (Slk& slk1, Slk& slk2) {
	return (!(slk1 > slk2)) && (slk1 != slk2);
}
bool operator <= (Slk& slk1, Slk& slk2) {
	return (slk1 < slk2) || (slk1 == slk2);
}
bool operator >= (Slk& slk1, Slk& slk2) {
	return (slk1 > slk2) || (slk1 == slk2);
}