#include <iostream>

#include "slk.h";
#include "dlk.h";
#include "rlk.h";

bool CheckEnter(CustomList& b, CustomList& s) {
	if (b.count() < s.count()) {
		return false;
	}
	unsigned int count = b.count();
	unsigned int smallSize = s.count();
	for (int i = 0; i < count; i++) {
		if (*b.at(i) == *s.at(0)) {
			if (i + smallSize > count) return false;
			for (int j = 0; j < smallSize; j++) {
				if (*b.at(i + j) == *s.at(j)) {
					if (j == smallSize - 1) return true;
					continue;
				}
				else {
					break;
				};
			}
		}
	}
	return false;
}

int main()
{
	// Dlk dlk1 = Dlk(); structure create
}
