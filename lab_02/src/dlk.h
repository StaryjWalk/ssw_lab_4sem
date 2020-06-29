#ifndef _CustomList;
#define _CustomList
	#include "customlist.h"
#endif
struct DlkCell
{
	int value;
	DlkCell* next;
	DlkCell* prev;
	DlkCell(int val) {
		value = val;
		next = nullptr;
		prev = nullptr;
	}
};
class Dlk : public CustomList {

private:
	unsigned int m_Count;
	DlkCell* m_Address;
	DlkCell* m_BeginAddress;
	DlkCell* m_EndAddress;
public:
	DlkCell* getBeginAddress() { return m_BeginAddress; }
	int* MinMaxList() {
		if (m_Count == 1) return new int[2]{ m_BeginAddress->value,m_BeginAddress->value };

		int* toReturn = new int[2]{ 0,0 };
		DlkCell* tempCell = m_BeginAddress;
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
		DlkCell* tempCell = m_BeginAddress;
		for (int i = 0; i < index; i++) {
			tempCell = tempCell->next;
		}
		return &tempCell->value;
	}
	Dlk() {
		m_Count = 0;
		m_BeginAddress = nullptr;
		m_EndAddress = nullptr;
		m_Address = nullptr;
	}
	~Dlk() {
		m_Count = 0;
		m_BeginAddress = nullptr;
		m_EndAddress = nullptr;
		m_Address = nullptr;
	}
	void PushBegin(int value) {
		DlkCell* cellTP = new DlkCell(value);
		if (m_Count == 0) {
			m_BeginAddress = cellTP;
			m_EndAddress = cellTP;
			m_Address = cellTP;
		}
		else {
			m_BeginAddress->prev = cellTP;
			cellTP->next = m_BeginAddress;
			m_BeginAddress = cellTP;
		}
		m_Count++;
	}
	void PushEnd(int value) {
		DlkCell* cellTP = new DlkCell(value);
		if (m_Count == 0) {
			m_BeginAddress = cellTP;
			m_EndAddress = cellTP;
			m_Address = cellTP;
		}
		else {
			m_EndAddress->next = cellTP;
			cellTP->prev = m_EndAddress;
			m_EndAddress = cellTP;
		}
		m_Count++;
	}
	int PopBegin() {
		int* tempValue;
		if (m_Count == 0) return 0;
		if (m_Count == 1) {
			m_BeginAddress = nullptr;
			m_EndAddress = nullptr;
			m_Address = nullptr;
		}
		else {
			m_BeginAddress = m_BeginAddress->next;
			m_BeginAddress->prev = nullptr;
		}
		m_Count--;
	}
	int PopEnd() {
		int* tempValue;
		if (m_Count == 0) return 0;
		if (m_Count == 1) {
			m_BeginAddress = nullptr;
			m_EndAddress = nullptr;
			m_Address = nullptr;
		}
		else {
			m_EndAddress = m_EndAddress->prev;
			m_EndAddress->next = nullptr;
		}
		m_Count--;
	}
	void Insert(int value, int index) {
		DlkCell* cellTP = new DlkCell(value);
		if (index > m_Count&& index < 0) return;
		if (index == 0) {
			cellTP->next = m_BeginAddress;
			m_BeginAddress->prev = cellTP;
			m_BeginAddress = cellTP;
		}
		else if (index == m_Count) {
			cellTP->prev = m_EndAddress;
			m_EndAddress->next = cellTP;
			m_EndAddress = cellTP;
		}
		else {
			DlkCell* tempCell = m_BeginAddress;
			for (int i = 0; i < index - 1; i++) {
				tempCell = tempCell->next;
			}
			cellTP->next = tempCell->next;
			cellTP->prev = tempCell;
			tempCell->next->prev = cellTP;
			tempCell->next = cellTP;
		}
		m_Count++;
	}
	void Erase(int index) {
		if (index > m_Count&& index < 0) return;
		if (index == 0) {
			if (m_Count == 1) {
				m_Address = nullptr;
				m_Count = 0;
				m_BeginAddress = nullptr;
				m_EndAddress = nullptr;
			}
			else {
				m_BeginAddress = m_BeginAddress->next;
				m_BeginAddress->prev = nullptr;
			}
		}
		else if (index == m_Count - 1) {
			m_EndAddress = m_EndAddress->prev;
			m_EndAddress->next = nullptr;
		}
		else {
			DlkCell* tempCell = m_BeginAddress;
			for (int i = 0; i < index - 1; i++) {
				tempCell = tempCell->next;
			}
			tempCell->next = tempCell->next->next;
			tempCell->next->prev = tempCell;
		}
		m_Count--;
	}
	DlkCell* begin() {
		return m_BeginAddress;
	}
	DlkCell* end() {
		return m_EndAddress;
	}
	unsigned int count() override {
		return m_Count;
	}
};
bool operator > (Dlk& dlk1, Dlk& dlk2) {
	if (dlk1.count() > dlk2.count()) {
		return true;
	}
	else if (dlk1.count() < dlk2.count()) {
		return false;
	}
	else {
		DlkCell* cell1 = dlk1.getBeginAddress();
		DlkCell* cell2 = dlk2.getBeginAddress();
		for (int i = 0; i < dlk1.count(); i++) {
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
bool operator == (Dlk& dlk1, Dlk& dlk2) {
	if (dlk1.count() != dlk2.count()) {
		return false;
	}
	DlkCell* cell1 = dlk1.getBeginAddress();
	DlkCell* cell2 = dlk2.getBeginAddress();
	for (int i = 0; i < dlk1.count(); i++) {
		if (cell1->value != cell2->value) {
			return false;
		}
		cell1 = cell1->next;
		cell2 = cell2->next;
	}
	return true;
}
bool operator != (Dlk& dlk1, Dlk& dlk2) {
	return !(dlk1 == dlk2);
}
bool operator < (Dlk& dlk1, Dlk& dlk2) {
	return (!(dlk1 > dlk2)) && (dlk1 != dlk2);
}
bool operator <= (Dlk& dlk1, Dlk& dlk2) {
	return (dlk1 < dlk2) || (dlk1 == dlk2);
}
bool operator >= (Dlk& dlk1, Dlk& dlk2) {
	return (dlk1 > dlk2) || (dlk1 == dlk2);
}