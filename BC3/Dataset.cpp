#include "Dataset.h"
#include <vector>

Dataset::Dataset(const Dataset & other)
{
	*this = other;
}

Dataset::~Dataset()
{
	if (numberOfObjects > 0) {
		while (all.size() > 0) {
			Object* last = all.back();
			delete last;
			all.pop_back();
		}
	}
}

Dataset & Dataset::operator=(const Dataset & other)
{
	numberOfObjects = other.numberOfObjects;
	all.clear();
	for (Object* cur : other.all) {
		all.push_back(new Object(*cur));
	}
	return *this;
}

void Dataset::add(Object* object)
{
	all.push_back(object);
	numberOfObjects++;
}

int Dataset::getSize() const
{
	return numberOfObjects;
}

const Object Dataset::operator[](const int index) const
{
	Object* object = all[index];
	return *object;
}

double Dataset::getMinCoordinate(int which) const
{
	double min = LONG_MAX;
	for (int i = 0; i < numberOfObjects; i++) {
		Object current = *(all[i]);
		double value = current.getValue(which);
		if (value < min) {
			min = value;
		}
	}
	return min - 0.01;
}

double Dataset::getMaxCoordinate(int which) const
{
	double max = LONG_MIN;
	for (int i = 0; i < numberOfObjects; i++) {
		Object current = *(all[i]);
		double value = current.getValue(which);
		if (value > max) {
			max = value;
		}
	}
	return max + 0.01;
}

Object& Dataset::operator[](const int index)
{
	Object* object = all[index];
	return *object;
}

/*int Dataset::whichNumberOfObject(const Object& object) const
{
	int which = 0;
	for (Object *actual : all) {
		if (actual == &object) {
			return which;
		}
		which++;
	}
	return which;
}*/
