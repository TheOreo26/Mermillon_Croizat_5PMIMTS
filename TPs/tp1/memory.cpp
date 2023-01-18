#include "memory.h"

using namespace std;

tlm::tlm_response_status memory::write(const ensitlm::addr_t &a,
                                       const ensitlm::data_t &d) {
	cout << "j'ecris : " << d << ", dans la mémoire à l'addresse : " << a << endl;

    storage[a/sizeof(size)] = d;

	return tlm::TLM_OK_RESPONSE;
}

tlm::tlm_response_status memory::read(const ensitlm::addr_t &a,
                                      /* */ ensitlm::data_t &d) {

    /*test pour verifier qu'on lit bien à des adresses valides*/
    #if TESTS_MEMOIRE
        if (a > size) {
            cout << "Addresse en dehors des limites" << endl;
            return tlm::TLM_ADDRESS_ERROR_RESPONSE;
        }
    #endif
    
    d = storage[a/sizeof(size)];
	cout << "je lis  : " << d  << " de la mémoire à l'addresse " << a << endl;

	return tlm::TLM_OK_RESPONSE;
}

memory::memory(sc_core::sc_module_name name, uint32_t taille_memoire) : sc_core::sc_module(name) {
    
    storage = new ensitlm::data_t[taille_memoire / sizeof(taille_memoire)];
    size = taille_memoire / sizeof(taille_memoire);
}

memory::~memory() {

    delete(storage);
}
