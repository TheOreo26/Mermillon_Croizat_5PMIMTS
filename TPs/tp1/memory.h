#ifndef MEMORY_H
#define MEMORY_H

#include "ensitlm.h"
#include "bus.h"

#define TESTS_MEMOIRE 0

using namespace std;
using namespace sc_core;

struct memory : sc_core::sc_module {
	ensitlm::target_socket<memory> socket;
    ensitlm::data_t * storage;
    uint32_t size;

    tlm::tlm_response_status write(const ensitlm::addr_t &a,
	                               const ensitlm::data_t &d);

	tlm::tlm_response_status read(const ensitlm::addr_t &a,
	                              /* */ ensitlm::data_t &d);

	memory(sc_core::sc_module_name name, uint32_t taille_memoire);

    ~memory();
};


#endif