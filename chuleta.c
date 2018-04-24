#include <>

//------------------------------------------
//configurar signal

trat_sigusr1(int s) {}

sigset_t mask;
struct sigaction nom_signal;
sigemptyset(&mask); //posa tots els bits de la màscara a 0.
sigfillset(&mask); //posa a 1 tots els bits de la màscara.
sigaddset(sigset_t *mask, int signum); //afegeix el signal a la mask.
sigdelset(&mask, SINAL QUE VULGUIS); //elimina el signal de la mask.
sigismember(sigset_t *mask, int signum); //1 si el signal està a la màscara.
nom_signal.sa_handler = &trat_sigusr1;
nom_signal.sa_flags = 0; //es farà el tractament del handler.
nom_signal.sa_flags = SA_RESETHAND; //després de tractament del signal es torna al tractament per defecte.
nom_signal.sa_flags = SA_RESTART; //si un procés bloquejat rep el signal, es rienicia la crida que l'ha bloquejat.
sigaction(SIGNAL QUE VULGUIS, &nom_signal,0); //SIGNAL funcionarà com nom_signal.


//-------------------------------------------

execlp("executable","nom del que vols executar",argv[0]...argv[n],char*(null));

//-------------------------------------------

int p = fork();
p > 0; //al pare li torna al pid del fill
p = 0;//al fill
p < 0//si hi ha hagut error al crear nou procés

//-------------------------------------------

waitpid(pid,&status,maincra);
pid = 'pid'; //esperarà a que el fill amb pid = pid sigui zombie
pid = -1; //esperarà a que qualsevol procés fill sigui zombie
maincra = 0; //bloueja el pare si no hi ha processos fill no zombie
maincra = WNOHANG; //torna 0 si tens processos fills que no són zombie

//-------------------------------------------

punter = sbrk(num*sizeof(type)); //punter apunta a on comença l'espai reservat de la heap
if (sbrk(num*sizeof(type)) > 0); //reserva memòria
if (sbrk(num*sizeof(type)) < 0); //allibera memòria
ìf (sbrk(num*sizeof(type)) == 0); //el punter apuntarà a la memòria del heap actual

//-------------------------------------------

