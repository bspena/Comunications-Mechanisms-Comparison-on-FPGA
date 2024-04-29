# Architecture Diagram

## Convenzioni Interfacce
* to_sink (to_slave): sta per master to slave, il modulo corrente è il master quindi l'interfaccia è di uscita
* to_source: sta per slave to master, il modulo corrente è lo slave quindi l'interfaccia è d'ingresso
* Identificare master/source/host e slave/sink/agent:
  *  Il master ha sempre read, write, writedata e address come output per dire allo slave cosa fare, cosa scrivere ed a che indirizzo.
  * Lo slave ha come output sempre waitrequest, readdatavalid, readdata, writeresponsevalid per le risposte ai segnali di cui sopra.
* In OFS e ASP, esiste una variante con "split read and write channel". Potresti trovare gli stessi segnali di un bus Avalon MM normale, ma replicati per due canali. Un canale di sola lettura (rd) e l'altro di sola scrittura (wr). Ovviamente il canale "rd" non avrà segnali per le scritture, e.g. write, writedata e writeresponsevalid, dato che non potrà usarli. Lo stesso vale per il canale "wr", che non avrà i segnali relativi alle scritture.

## Diagram Legend
* `Orange box`: Module
* `Thick black arrow`: Signal
* `Blue arrow`: Interface
* `Dashed violet box`:
* `Green box`: Module added with the #ifdef verification
* `Green arrow`: Signal added with the #ifdef verification
* `Thick green arrow`: Interface added with the #ifdef verification
* `Dashed green box`:

# ifdef Compilation Directive
* INCLUDE_UDP_OFFLOAD_ENGINE
* USE_MPF_VTP
* INCLUDE_USM_SUPPORT
* PAC_BSP_ENABLE_DDR4_BANKi
* USE_KERNEL_IRQ


## Dubbi diagramma
* Senza direttive di compilazione
  * bsp_logic 
      * modulo baord
* Con direttive di compilazione
  * bsp_logic
      * riga 281 - 301  
      * riga 377
      * riga 382
  * kernel_wrapper
      * riga 23 (inserita nel diagramma)
      * riga 170-180
  * udp_offload_engine
      * riga 47 --> va bene in input al tx ?
      * riga 59 --> va bene in input all'rx ?
