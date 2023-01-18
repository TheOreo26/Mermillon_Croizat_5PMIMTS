/********************************************************************
 * Copyright (C) 2009 by Ensimag and Verimag                        *
 * Initial author: Matthieu Moy                                     *
 ********************************************************************/

#include "generator.h"

using namespace std;

void generator::thread(void) {
	ensitlm::data_t val = 1;
	ensitlm::addr_t addr = 0x10000000;

	for (int i = 0 ; i < 5 ; i++, addr += 4) {
		cout << "Entrer un nombre" << endl;
		cin >> val;
		cout << "je vais envoyer : " << std::dec << val << endl;
		socket.write(addr, val);
	}

    for (int i = 0 ; i < 5 ; i++) {
        cout << "Entrer l'addresse à laquelle vous voulez lire " << endl;
        cin >> addr;
        cout << "je vais lire à l'adresse " << std::dec << addr << endl;
        socket.read(0x10000000 + addr, val);
    }
}

generator::generator(sc_core::sc_module_name name) : sc_core::sc_module(name) {
	SC_THREAD(thread);
}