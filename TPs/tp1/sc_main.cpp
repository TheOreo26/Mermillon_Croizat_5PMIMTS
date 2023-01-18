/********************************************************************
 * Copyright (C) 2009 by Ensimag and Verimag			    *
 * Initial author: Matthieu Moy					    *
 ********************************************************************/

#include "generator.h"
#include "memory.h"
#include "bus.h"
#include "LCDC.h"

int sc_main(int argc, char **argv) {
	(void)argc;
	(void)argv;
	/*
	  +---------+	 +-------------+    +--------+
	  |	   +++	+-+	      +++  +++	     |
	  | Generator1  | +--+ |  Bus   | +--+ | Memory  |
	  |	   +++	+-+	      +++  +++	     |
	  +---------+	 +-------------+    +--------+
	*/
    sc_signal<bool, SC_MANY_WRITERS> irq_signal("IRQ");

	generator gen("Generator1");
	Bus router("Bus");

    uint32_t taille_memoire = 64;
    memory mem("Memory", taille_memoire);

    LCDC ecran("Ecran", sc_time(1.0 / 25, SC_SEC));

    /*Memory is mapped at address 0x10000000 of Bus*/
    router.map(mem.socket, 0x10000000, taille_memoire);
        
    /*LCD is mapped at address 0x00000000*/    
    router.map(ecran.target_socket, 0x00000000, 0x08);


	/* connect components to the bus */
	gen.socket.bind(router.target);
    
    //Interrupts
    ecran.display_intr(irq_signal);
    gen.irq(irq_signal);
    
    router.initiator.bind(mem.socket);
    router.initiator.bind(ecran.target_socket);
    ecran.initiator_socket.bind(router.target);


    

	/* and start simulation */
	sc_core::sc_start();
	return 0;
}
