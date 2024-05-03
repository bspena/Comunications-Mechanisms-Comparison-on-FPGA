# Architecture Diagram

## Convenzioni Interfacce
* to_sink (to_slave): sta per master to slave, il modulo corrente è il master quindi l'interfaccia è di uscita
* to_source (to_master): sta per slave to master, il modulo corrente è lo slave quindi l'interfaccia è d'ingresso
* Identificare master/source/host e slave/sink/agent:
  * Il master ha sempre read, write, writedata e address come output per dire allo slave cosa fare, cosa scrivere ed a che indirizzo.
  * Lo slave ha come output sempre waitrequest, readdatavalid, readdata, writeresponsevalid per le risposte ai segnali di cui sopra.
* In OFS e ASP, esiste una variante con "split read and write channel". Potresti trovare gli stessi segnali di un bus Avalon MM normale, ma replicati per due canali. Un canale di sola lettura (rd) e l'altro di sola scrittura (wr). Ovviamente il canale "rd" non avrà segnali per le scritture, e.g. write, writedata e writeresponsevalid, dato che non potrà usarli. Lo stesso vale per il canale "wr", che non avrà i segnali relativi alle scritture.
* I prefissi s0 e m0 stanno esattamente per slave e master

## Diagram Legend
* `Box`: Module
* `Arrow`: Signal
* `Thick arrow`: Interface
* `Green box`: Module added with INCLUDE_UDP_OFFLOAD_ENGINE and INCLUDE_USM_SUPPORT macros
* `Green arrow`: Signal added with INCLUDE_UDP_OFFLOAD_ENGINE and INCLUDE_USM_SUPPORT macros
* `Thick green arrow`: Interface added with INCLUDE_UDP_OFFLOAD_ENGINE and INCLUDE_USM_SUPPORT macros


## Info Moduli
mem_if_vpt si occupa di tradurre gli indirizzi da virtuali a fisico (Virtual to Physical Translation - VTP)
dma_top è un DMA, nulla di strano 
board wrappa tutte le interfacce che non vedi nei sorgenti, in particolare i banchi di DDR on-board
bsp_host_mem_if_mux inietta sul bus AVMM delle transazioni speciali che quando kernel_irq è alto. Queste transazioni vengono interpretate dall'host (Linux drivers) come un evento di interrupt vero e proprio
avmm_wr_ack_gen ti ho già spiegato cosa fa
il sincronizzatore non ha una funzione logica, serve solo a stabilizzare il segnale sul nuovo clock
kernel_system è il l'hardware generato dalla descrizione in SYCL. Lo puoi vedere come un device con 4 interfacce
una linea di interrupt (kernel_irq) in uscita
un interfaccia AVMM slave CSR dove scrivere comandi e parametri (e.g. start, busy, pending interrupt, etc)
un'interfaccia AVMM master di lettura/scrittura verso ogni banco DDR
un'interfaccia AVMM master di lettura/scrittura verso la memoria host (Shared/Unified Virtual Memroy SVM/USM)
questa non è abilitata nel design che stai analizzando tu