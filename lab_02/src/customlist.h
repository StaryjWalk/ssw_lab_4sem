class CustomList {
public:
	virtual unsigned int count() { return 0; }
	virtual int* at(unsigned int index) { return nullptr; }
};