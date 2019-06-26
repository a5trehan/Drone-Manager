#ifndef DRONES_MANAGER_TEST
#define DRONES_MANAGER_TEST

#include "lab2_drones_manager.hpp"

#define ASSERT_TRUE(T); if (!(T)) return false;
#define ASSERT_FALSE(T); if ((T)) return false;

using namespace std;

class DronesManagerTest {
public:
	// PURPOSE: New empty list is valid
	bool test1() {
		DronesManager manager1; 
		ASSERT_TRUE(manager1.first == manager1.last && manager1.first == NULL) // tests first and last are NULL when instantiated
		ASSERT_TRUE(manager1.empty() && manager1.size == 0) 
		return true;
	}
	
	// PURPOSE: insert_front() and insert_back() on zero-element list
	bool test2() {
		DronesManager manager1, manager2;
		
		manager1.insert_front(DronesManager::DroneRecord(120));
		manager2.insert_back(DronesManager::DroneRecord(100));
		ASSERT_FALSE(manager1.empty() && manager2.empty()) // tests size != 0	
		ASSERT_TRUE(manager1.first->prev == NULL && manager1.last->next == NULL) 
		ASSERT_TRUE(manager2.first->prev == NULL && manager2.last->next == NULL)
		
		ASSERT_TRUE(*(manager1.first) == DronesManager::DroneRecord(120) && manager1.first == manager1.last) // tests correct insertion of elements 
		ASSERT_TRUE(*(manager2.first) == DronesManager::DroneRecord(100) && manager2.first == manager2.last)
			
	    return true;
	}
	
	// TODO: Implement all of the test cases below
	
	// PURPOSE: select() and search() work properly
	bool test3() {
	    DronesManager manager;
		
		ASSERT_TRUE(manager.select(1) == DronesManager::DroneRecord(0) && manager.empty()) // tests selection of empty list
		ASSERT_TRUE(manager.search(DronesManager::DroneRecord(100)) == 0 && manager.empty())
		
		manager.insert_front(DronesManager::DroneRecord(100));
		ASSERT_TRUE(manager.select(0) == *(manager.first)) // tests correct selection of index = 0
		ASSERT_TRUE(manager.search(DronesManager::DroneRecord(100)) == 0 && !manager.empty())
		
		manager.insert_front(DronesManager::DroneRecord(200));
		ASSERT_TRUE(manager.select(4) == *(manager.last)) // tests selection of index > size - 1
		ASSERT_TRUE(manager.search(DronesManager::DroneRecord(300)) == manager.size) // tests search of false element 
		
		manager.insert_front(DronesManager::DroneRecord(250)); 
		ASSERT_TRUE(manager.select(1) == DronesManager::DroneRecord(200)) // tests correct selection of second element 
				
	    return true;
	}
	
	// PURPOSE: remove_front() and remove_back() on one-element list
	bool test4() {
		DronesManager manager1, manager2;
	    
		manager1.insert_front(DronesManager::DroneRecord(100));
		manager2.insert_front(DronesManager::DroneRecord(100));
		ASSERT_TRUE(manager1.remove_front()) // tests front and back removal
		ASSERT_TRUE(manager2.remove_back())		

		ASSERT_TRUE(manager1.size == 0 && manager2.size == 0) // tests size != 0
		ASSERT_TRUE(manager1.first == NULL && manager1.last == NULL) 
		ASSERT_TRUE(manager2.first == NULL && manager2.last == NULL)
		
		return true;
	}
	
	// PURPOSE: replace() and reverse_list() work properly
	bool test5() {
		DronesManager manager;
		ASSERT_FALSE(manager.replace(0, DronesManager::DroneRecord(127))) // replace when size = 0 and index = 0 
		ASSERT_FALSE(manager.reverse_list()) // reverse empty list 
		
		manager.insert_front(DronesManager::DroneRecord(100));
		ASSERT_TRUE(manager.replace(0, DronesManager::DroneRecord(666))) // replace when size = 1 and index = 0 
		ASSERT_FALSE(manager.reverse_list()) // reverse single element list
		manager.insert_front(DronesManager::DroneRecord(100));
		ASSERT_TRUE(manager.replace(0, DronesManager::DroneRecord(420))) // tests index = 0 condition 
		ASSERT_TRUE(manager.replace(1, DronesManager::DroneRecord(100))) // tests index = size - 1
		ASSERT_FALSE(manager.replace(0, DronesManager::DroneRecord(100))) // replace with duplicate element
		
		manager.reverse_list();
		ASSERT_TRUE(manager.select(0) == DronesManager::DroneRecord(100) && manager.select(1) == DronesManager::DroneRecord(420))

		manager.insert_front(DronesManager::DroneRecord(747));
		ASSERT_TRUE(manager.replace(1, DronesManager::DroneRecord(333))) // replace middle index 
		ASSERT_TRUE(manager.reverse_list());
		ASSERT_TRUE(manager.size == 3)
		ASSERT_TRUE(manager.select(0) == DronesManager::DroneRecord(420) && manager.select(1) == DronesManager::DroneRecord(333)
		&& manager.select(2) == DronesManager::DroneRecord(747))
		
		return true;
	}
	
	// PURPOSE: insert_front() keeps moving elements forward
	bool test6() {
	    DronesManager manager;
		
		manager.insert_front(DronesManager::DroneRecord(100));
		ASSERT_TRUE(manager.size == 1)
		ASSERT_TRUE(manager.first == manager.last && *(manager.first) == DronesManager::DroneRecord(100)) // tests correction insertion of element
		ASSERT_TRUE(manager.first->prev == NULL && manager.last->next == NULL)
		
		manager.insert_front(DronesManager::DroneRecord(200));
		ASSERT_TRUE(manager.size == 2)
		ASSERT_TRUE(*(manager.first) == DronesManager::DroneRecord(200) && *(manager.last) == DronesManager::DroneRecord(100))
		ASSERT_TRUE(manager.first->prev == NULL && manager.last->next == NULL)
		ASSERT_TRUE(*(manager.first->next) == DronesManager::DroneRecord(100) && *(manager.last->prev) == DronesManager::DroneRecord(200))

	    return true;
	}
	
	// PURPOSE: inserting at different positions in the list
	bool test7() {
		DronesManager manager;
		ASSERT_FALSE(manager.insert(DronesManager::DroneRecord(256), 1)) // insert when size = 0 and index != 0
		ASSERT_TRUE(manager.insert_front(DronesManager::DroneRecord(416)))
		ASSERT_TRUE(manager.insert_back(DronesManager::DroneRecord(111)))
		ASSERT_TRUE(manager.insert(DronesManager::DroneRecord(212), 1))
		ASSERT_TRUE(manager.insert(DronesManager::DroneRecord(527), 2))
		ASSERT_FALSE(manager.insert(DronesManager::DroneRecord(987), 6)) // insert when size != 0 and index > size
		ASSERT_TRUE(manager.insert_front(DronesManager::DroneRecord(838)))
		ASSERT_TRUE(manager.insert_back(DronesManager::DroneRecord(903)))
		ASSERT_FALSE(manager.insert(DronesManager::DroneRecord(903), 1)) // tests duplicate insert
		ASSERT_TRUE(manager.insert(DronesManager::DroneRecord(456), 1))
	    return true;
	}

	
	// PURPOSE: try to remove too many elements, then add a few elements
	bool test8() {
		DronesManager manager;
		
		manager.insert_front(DronesManager::DroneRecord(100));
		ASSERT_TRUE(manager.remove_front()) // tests removing single element
		ASSERT_FALSE(manager.remove(2)) // tests removal of too many elements and at index > size - 1
		
		ASSERT_TRUE(manager.first == manager.last && manager.first == NULL)
		
		manager.insert_front(DronesManager::DroneRecord(400));
		manager.insert_back(DronesManager::DroneRecord(300));
		
		ASSERT_TRUE(manager.get_size() == 2)
		ASSERT_TRUE(*(manager.first) == DronesManager::DroneRecord(400) && *(manager.last) == DronesManager::DroneRecord(300))
		ASSERT_TRUE(manager.first->prev == NULL && manager.last->next == NULL)
		ASSERT_TRUE(*(manager.first->next) == DronesManager::DroneRecord(300) && *(manager.last->prev) == DronesManager::DroneRecord(400))
		
	    return true;
	}
	
	// PURPOSE: lots of inserts and deletes, some of them invalid
	bool test9() {
		DronesManager manager;
		ASSERT_TRUE(manager.insert_front(DronesManager::DroneRecord(150)))
		ASSERT_TRUE(manager.remove_front())
		ASSERT_FALSE(manager.remove_back()) // remove from empty list 
		ASSERT_FALSE(manager.remove(3)) // remove index > size - 1
		
		ASSERT_FALSE(manager.insert(DronesManager::DroneRecord(381), 2)) // insert at index != 0 when size = 0
		ASSERT_TRUE(manager.insert_front(DronesManager::DroneRecord(144)))
		ASSERT_TRUE(manager.insert_back(DronesManager::DroneRecord(729)))
		ASSERT_TRUE(manager.remove_back())
		ASSERT_FALSE(manager.remove(2)) // remove index > size - 1
		ASSERT_TRUE(manager.insert_back(DronesManager::DroneRecord(900)))
		ASSERT_TRUE(manager.insert(DronesManager::DroneRecord(233), 1))
		ASSERT_FALSE(manager.insert(DronesManager::DroneRecord(121), 5)) // insert at index > size 
		ASSERT_TRUE(manager.remove_front())
		
		return true;
	}    
 
	    	
	// PURPOSE: lots of inserts, reverse the list, and then lots of removes until empty
	bool test10() {
		DronesManager manager1;
		for(int i = 0; i < 10; i++) {
			manager1.insert_back(DronesManager::DroneRecord(i + 100));
			ASSERT_TRUE(manager1.select(i).droneID == i + 100) // tests correct insertion ID
		}

		ASSERT_TRUE(manager1.size == 10)
		ASSERT_TRUE(manager1.first != NULL &&  manager1.last !=NULL)
		ASSERT_FALSE(manager1.empty())	
		
		manager1.reverse_list();
		for(int i = 9; i >= 0; i--) {
			ASSERT_TRUE(manager1.select(9-i).droneID == i + 100) // tests reversal of the list
		}

		for(int i = 0; i < 10; i++)
			manager1.remove_front();
			
		ASSERT_TRUE(manager1.size == 0)
		ASSERT_TRUE(manager1.first == manager1.last && manager1.first == NULL)
		ASSERT_TRUE(manager1.empty())	

		return true;
	} 
};

#endif
