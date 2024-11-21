#ifndef OBJECT_H
#define OBJECT_H

class Object
{
private:
	static unsigned int id; // Inline keyword is used to be able to initialise the static id inside the class definition: C++17

public:
	Object() { ++id;  }
	~Object() {}
};

#endif // OBJECT_H
