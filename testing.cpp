#include <iostream>
#include <unordered_map>
#include <stdint.h>
#include <thread>
#include <chrono>
#include "src/include/mltable.h"
#include "testing_dataset.h"
#include <unistd.h>

//#include <container/flat_hash_map.h"

#define MEASUREMENT nanoseconds

using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::duration;
using std::chrono::MEASUREMENT;
using namespace std::chrono_literals;

struct NoHash {
  size_t operator()(const uint64_t &p) const  {
    return p;
  }
};

#define testing_unordered_set 1
#define testing_unordered_get 1
#define testing_mlht_set 1
#define testing_mlht_get 1
#define assertations 0

#define index_type random_keys[i]

int main() {
	printf("TABLE_SIZE: %lu %lu %lu\n", sizeof(struct table), sizeof(struct node), sysconf(_SC_PAGE_SIZE));
	std::chrono::steady_clock::time_point t1, t2;
	auto ms_int = duration_cast<MEASUREMENT>(t2 - t1);
	
	struct sc_alloc allocator = init_allocator();
	/*
	UNORDERD MAP!!!
	*/

//	absl::flat_hash_map<uint64_t, uint64_t, NoHash> x;
	std::unordered_map<uint64_t, uint64_t, NoHash> x;
	#if testing_unordered_set
	
	t1 = high_resolution_clock::now();
	for (int i = 0; i < sizeof(random_keys) / sizeof(random_keys[0]); i++)
		x[index_type] = i;
	t2 = high_resolution_clock::now();
	ms_int = duration_cast<MEASUREMENT>(t2 - t1);
	std::cout << "US:\t\t\t" << ms_int.count() << std::endl;
	#endif

	/*
	US
	*/
	struct mltable table = init_mltable(&allocator);
	#if testing_mlht_set
	
	t1 = high_resolution_clock::now();
	for (int i = 0; i < sizeof(random_keys) / sizeof(random_keys[0]); i++) {
		mltable_set(&table, index_type, i);

		#if assertations
			assert(mltable_get(table.root, index_type)->data.format.value.data == i);
		#endif
	}
		
	t2 = high_resolution_clock::now();
	ms_int = duration_cast<MEASUREMENT>(t2 - t1);
	std::cout << "MS:\t\t\t" << ms_int.count() << std::endl;
	#endif


	#if testing_unordered_get
	std::cout << std::endl << std::endl;
	/*
	UNORDERD MAP GET!!!
	*/
	t1 = high_resolution_clock::now();
	for (int i = 0; i < sizeof(random_keys) / sizeof(random_keys[0]); i++)
		x[index_type];
	t2 = high_resolution_clock::now();
	ms_int = duration_cast<MEASUREMENT>(t2 - t1);
	std::cout<< "UG:\t\t\t" << ms_int.count() << std::endl;
	#endif

	/*
	US
	*/
//	std::this_thread::sleep_for(2000ms);
	
	#if testing_mlht_get
	t1 = high_resolution_clock::now();
	for (int i = 0; i < sizeof(random_keys) / sizeof(random_keys[0]); i++) {
		mltable_get(table.root, index_type);

		#if assertations
			assert(mltable_get(table.root, index_type)->data.format.value.data == i);
		#endif
	}
		
	t2 = high_resolution_clock::now();
	ms_int = duration_cast<MEASUREMENT>(t2 - t1);
	std::cout << "MG:\t\t\t" << ms_int.count() << std::endl;
	#endif
	std::cout << std::endl << std::endl;


}
