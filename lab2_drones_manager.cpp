#include "lab2_drones_manager.hpp"
#include <iomanip>
#include <iostream>

using namespace std;

// TODO: Implement all of the listed functions below

//PURPOSE: Creates a new empty DronesManager
DronesManager::DronesManager() {
	first = last = NULL;
	size = 0;	
}

//PURPOSE: Destroys this instance and frees up all dynamically allocated memory
DronesManager::~DronesManager() {
	DroneRecord* curr = first;
	while(curr) {
		curr = curr -> next;
		delete first;
		first = curr;
	}
	size = 0;
	first = last = NULL;
	
}

// IMPLEMENT AS FRIEND FUNCTION
bool operator==(const DronesManager::DroneRecord& lhs, 
const DronesManager::DroneRecord& rhs) {
	return lhs.droneID == rhs.droneID && lhs.range == rhs.range && 
	lhs.yearBought == rhs.yearBought && lhs.droneType == rhs.droneType && 
	lhs.manufacturer == rhs.manufacturer && lhs.description == rhs.description && 
	lhs.batteryType == rhs.batteryType;
}

unsigned int DronesManager::get_size() const {
	return size;
}

bool DronesManager::empty() const {
	return size == 0 && !first;
}

DronesManager::DroneRecord DronesManager::select(unsigned int index) const {
	if(size == 0)
		return DroneRecord(0);
	else if(index == 0)
		return *first;
	else if(index >= size - 1)
		return *last;
	else {
		DroneRecord* curr = first;
		for(int i = 0; i < index; i++)
			curr = curr -> next;
		return *curr;
	}
}

unsigned int DronesManager::search(DroneRecord value) const {
	if(size == 0 && !first)
		return 0;
	DroneRecord* curr = first;
	for(int i = 0; i < size; i++) {
		if(*curr == value)
			return i;
		curr = curr -> next;
	}
	return size;
}

void DronesManager::print() const {
	DroneRecord* curr = first;
	cout << setw(15) << "DroneID" << endl;
	for(int i = 0; i < size; i++) {
		cout << setw(4) << i << setw(8) << curr -> droneID << endl;
		curr = curr -> next;
	}
}

bool DronesManager::insert(DroneRecord value, unsigned int index) {
	DroneRecord* newVal = new DroneRecord(value);
	if(index > size || !newVal)
		return false;
	else if(index == 0 && size == 0)
		first = last = newVal;
	else {
		DroneRecord* curr = first;
		for(int i = 0; i < size; i++) {
			if(curr -> droneID == newVal -> droneID)
				return false;
			curr = curr -> next;
		}
		if(index == 0) {
			first -> prev = newVal;
			newVal -> next = first;
			first = newVal;
		}
		else if(index == size) {
			last -> next = newVal;
			newVal -> prev = last;
			last = newVal;
		}
		else{
			curr = first;
			for(int i = 0; i < index; i++)
				curr = curr -> next;
			curr -> prev -> next = newVal;
			newVal -> prev = curr -> prev;
			curr -> prev = newVal;
			newVal -> next = curr; 
		}
	}
	++size;
	return true;
}

bool DronesManager::insert_front(DroneRecord value) {
	DroneRecord* newVal = new DroneRecord(value);
	if(!newVal)
		return false;
	else if(!first) {
		first = last = newVal;
	}
	else {
		DroneRecord* curr = first;
		for(int i = 0; i < size; i++) {
			if(curr -> droneID == newVal -> droneID)
				return false;
			curr = curr -> next;
		}
		first -> prev = newVal;
		newVal -> next = first;
		first = newVal;
	}
	++size;
	return true;
}

bool DronesManager::insert_back(DroneRecord value) {
	DroneRecord* newVal = new DroneRecord(value);
	if(!newVal)
		return false;
	else if(!first)
		first = last = newVal;
	else {
		DroneRecord* curr = first;
		for(int i = 0; i < size; i++) {
			if(curr -> droneID == newVal -> droneID)
				return false;
			curr = curr -> next;
		}
		last -> next = newVal;
		newVal -> prev = last;
		last = newVal;
	}
	++size;
    return true;
}

bool DronesManager::remove(unsigned int index) {
	if(!first || index > size - 1)
		return false;
	else if(index == 0 && size == 1) {
		delete last;
		first = last = NULL;
	}
	else if(index == 0) {
		DroneRecord* temp = first;
		first = first -> next;
		delete temp;
		temp = NULL;
	}
	else if(index == size - 1) {
		DroneRecord* temp = last;
		last = last -> prev;
		delete temp;
		temp = NULL;
	}
	else {
		DroneRecord* curr = first;
		for(int i = 0; i < index && curr; i++)
			curr = curr -> next;
		curr -> next -> prev = curr -> prev;
		curr -> prev -> next = curr -> next;
		delete curr;
		curr = NULL;
	}
	--size;
	return true;
}

bool DronesManager::remove_front() {
	if(!first)
		return false;
	else if(size == 1) {
		delete first;
		first = last = NULL;
	}
	else {
		DroneRecord* temp = first;
		first = first -> next;
		delete temp;
		temp = NULL;
	}
	--size;
	return true;
}

bool DronesManager::remove_back() {
	if(!first)
		return false;
	else if(size == 1) {
		delete last;
		first = last = NULL;
	}
	else {
		DroneRecord* temp = last;
		last = last -> prev;
		delete temp;
		temp = NULL;
	}
	--size;
	return true;
}

bool DronesManager::replace(unsigned int index, DroneRecord value) {
	DroneRecord* newVal = new DroneRecord(value);
	if(!first || !newVal || index > size-1)
		return false;		
	else if(index == 0 && size == 1) {
		delete first;
		first = last = newVal;
	}
	else {
		DroneRecord* curr = first;
		for(int i = 0; i < size; i++) {
			if(curr -> droneID == newVal -> droneID)
				return false;
			curr = curr -> next;
		}
		if(index == 0) {
			first -> next -> prev = newVal;
			newVal -> next = first -> next;
			delete first;
			first = newVal;
		}
		else if(index == size-1) {
			last -> prev -> next = newVal;
			newVal -> prev = last -> prev; 
			delete last;
			last = newVal;
		}
		else {
			curr = first;
			for(int i = 0; i < index; i++)
				curr = curr->next;
			curr -> next -> prev = newVal;
			curr -> prev -> next = newVal;
			newVal -> next = curr -> next;
			newVal -> prev = curr -> prev;
			delete curr;
		}
	}
	return true;
}

bool DronesManager::reverse_list() {
	if(!first || size == 1)
		return false;
	DroneRecord* curr = first;
	DroneRecord* temp = first -> next;
	first -> prev = temp;
	first -> next = NULL;
	while(temp) {
		temp -> prev = temp -> next;
		temp -> next = curr;
		temp = temp -> prev;
		curr = curr -> prev;
	}
	last = first;
	first = curr;
	return true;
}

