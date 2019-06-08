#include "lab2_drones_manager.hpp"
#include <iomanip>

// TODO: Implement all of the listed functions below

//PURPOSE: Creates a new empty DronesManager
DronesManager::DronesManager() {
	first = NULL;
	last = NULL;
	size = 0;	
}

//PURPOSE: Destroys this instance and frees up all dynamically allocated memory
DronesManager::~DronesManager() {
	while(first) {
		DroneRecord* curr = first;
		first = first -> next;
		delete curr;
		curr = NULL;
	}
}

// IMPLEMENT AS FRIEND FUNCTION
friend bool operator==(const DronesManager::DroneRecord& lhs, 
const DronesManager::DroneRecord& rhs) {
	return lhs.droneID == rhs.droneID && lhs.range == rhs.range && 
	lhs.yearBought == rhs.yearBought && lhs.droneType == rhs.droneType && 
	lhs.manufacturer == rhs.manufacturer && lhs.description == rhs.description && 
	lhs.batteryType == rhs.batteryType;
}

friend class DronesManagerTest;

unsigned int DronesManager::get_size() const {
	return size;
}

bool DronesManager::empty() const {
	return size == 0;
}

DronesManager::DroneRecord DronesManager::select(unsigned int index) const {
	if(*this.empty())
		return DroneRecord(0);
	else if(index > size - 1)
		return *last;
	else {
		DroneRecord* curr = first;
		for(int i = 0; i < index; i++)
			curr = curr -> next;
		return *curr;
	}
}

unsigned int DronesManager::search(DroneRecord value) const {
	if(*this.empty())
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
	cout << setw(15) << "Drone ID" << endl;
	for(int i = 0; i < size; i++)
	{
		cout << setw(4) << i << setw(10) << *curr.droneID << endl;
		curr = curr -> next;
	}
}

bool DronesManager::insert(DroneRecord value, unsigned int index) {
	return false;
}

bool DronesManager::insert_front(DroneRecord value) {
	first = &value;
	return false;
}

bool DronesManager::insert_back(DroneRecord value) {
	if(!first)
		first = new DroneRecord(value);
	else {
		DroneRecord* curr = first;
		while (curr -> next)
			curr = curr -> next;
		curr -> next = new DroneRecord(value);
	}
    	++size;
    	return true;
}

bool DronesManager::remove(unsigned int index) {
	return false;
}

bool DronesManager::remove_front() {
	return false;
}

bool DronesManager::remove_back() {
	return false;
}

bool DronesManager::replace(unsigned int index, DroneRecord value) {
	return false;
}

bool DronesManager::reverse_list() {
	return false;
}

