#ifndef GENERATOR_H
#define GENERATOR_H

#include "ensitlm.h"
#include "bus.h"

using namespace std;
using namespace sc_core;

struct generator : sc_core::sc_module {
	ensitlm::initiator_socket<generator> socket;
    sc_core::sc_in<bool> irq;

	void thread(void);

	SC_CTOR(generator);
};

#endif