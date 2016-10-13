Download digit on terminal:

 - git clone https://github.com/leminski/WPAdiz.git

Read file INSTALL for more information.

 # Author: leminski                    #
 # City:   Italy, (Campania)           #
 # email:  atleminski@gmail.com        #
 # Site:   https://github.com/leminski #

[Italiano]:

 Premessa:

Questo software non è un passpartou che consente di violare qualsiasi rete di
tipo wireless, o che il risultato sia sempre quello desiderato. Tuttavia puo
aumentare la percentuale di successo e la velocità con cui creare un dizionario
di questo tipo.

L'approccio a questo programma è nato dal fatto che non trovando qualche utility
che permettesse di generare un tipo di dizionario con delle paroli comuni usate
quotidianamente, mi ha spinto a creare un software che mi permettesse di
generare un dizionario che avesse una maggiore probabilità di successo,
(dato che la maggior parte delle persone usa come password nomi comuni, date, nomi del proprio
figlio, madre ecc.), e cioè che  generasse a partire da un file con dei nomi
(o piu di un file), tutte le combinazioni con dei numeri, lettere, 
parole, date, oppure con combinazioni di maiuscolo e minuscolo ecc, senza dover 
andare manualmente a scrivere parola per parola. Cosa piu importante(forse), è
la possibilità di poter controllare poi che le parole non siano piu piccole di
8 caratteri, perchè sappiamo che la lunghezza minima di una password del wifi
(che sia decente o meno) è DI 8 CARATTERI. Quindi immaginate di scaricare 
un dizionario di 10 GB con piu 1000000000 di parole e darlo in pasto a qualche
programma di "craccaggio"... e che magari in quel file, il 50% 
delle parole non possono andar bene in quanto sono meno di 8 caratteri..
quindi si passerà (magari) quel giorno in piu ad aspettare davanti al PC 
sperando(invano) che la password possa essere presente in quel 50%, quando
potrebbe durare poche ore o pochi minuti(Dipende anche dalla potenza del PC).
Quindi è buona norma controllare prima il tutto, per poi dare in pasto al famoso
aircrack-ng ;).

Sono disponibili 3 software:

* Uno per le date (wpadate)

 - permette di generare delle date con vari formati e divisioni dei singoli numeri
   (es.)
        - 1/1/2016
        - 01-02-2016
        - 1 1 2015    (anche con dei spazi tra loro)

   Lo slash magari lo si puo cambiare con un altro carattere o addirittura con 
   una parola. Per sapere nello specifico le possibili opzioni, usate l'help
   del software.

* Uno per la lunghezza delle parole(wpalength)

 - come detto prima, permette di vedere se nel file sono presenti delle parole
   con meno del numero di caratteri specificato con il parametro -l.
   Inoltre, se sono presenti, sarà possbile con un parametro, eliminare automaticamente
   nel file tutte le parole che risultano "non valide :)" per i nostri gusti.
   Vedere nell'help del programma

* Uno per la generazione di parole(wpahashword)

 - Permette di generare a partire da un file di nomi(o massimo uno in piu),
   delle combinazioni con dei cognomi, oppure con delle date o dei numeri
   oppure creare dei nomi insieme a dei cognomi o delle date...
   quindi c'è una vasta scelta e il tutto dipende dalla fantasia di chi sta
   dietro.

Inoltre nella cartella file, sono presenti gia dei dizionari con dei nomi,
cognomi, e delle marche dei router piu famosi da ampliare ancora. Quindi invito
chiunque ad arricchire ulteriormente quei file, magari con dei nuovi nomi
o altro, per avere una maggiore percentuale di successo.

Inoltre è ancora in fase di "ampliamento"... ma questa versione per il momento
puo andare piu che bene( nella maggior parte di voi ;) ).

Per qualsiasi tipo di segnalazione contattatemi a: atleminski@gmail.com