#include <>


void error_y_exit(char *s, int error) {
	perror(s);
	exit(error);
}

//------------------------------------------
//configurar signal

trat_sigusr1(int s) {}

sigset_t mask;
struct sigaction nom_signal;

//tractament de màscares
sigemptyset(&mask); //posa tots els bits de la màscara a 0.
sigfillset(&mask); //posa a 1 tots els bits de la màscara.
sigaddset(sigset_t *mask, int signum); //afegeix el signal a la mask.
sigdelset(&mask, SINAL QUE VULGUIS); //elimina el signal de la mask.
sigismember(sigset_t *mask, int signum); //1 si el signal està a la màscara.

//capturar signals
sigaction(SIGNAL QUE VULGUIS, &nom_signal, NULL); //Quan arribi SIGNAL QUE VULGUIS efectuarà el tractament "nom_signal"

//bloquejar i desbloquejar processos
sigprocmask(SIG_BLOCK, mask, old_mask); //afegir signals mask a la mask bloquejada pel procés
sigprocmask(SIG_UNBLOCK, mask, old_mask); //treure el signals indicats per la mask a la mask bloqu...
sigprocmask(SIG_SETMASK, mask, old_mask); //mask signals block passi a ser el paràmetre mask

//esperar evento
sigsuspend(&mask); //bloqueja procés fins que arriba un SIGIGN(ore)

kill(pid, SIGNAL QUE VULGUIS); //enviar signal al pid del procés

//tractament del handler
nom_signal.sa_handler = &trat_sigusr1;
nom_signal.sa_flags = 0; //es farà el tractament del handler.
nom_signal.sa_flags = SA_RESETHAND; //després de tractament del signal es torna al tractament per defecte.
nom_signal.sa_flags = SA_RESTART; //si un procés bloquejat rep el signal, es rienicia la crida que l'ha bloquejat.

//-------------------------------------------
//programar un signal pa que funcione: per exemple SIGALARM

sigaction(SIGNAL QUE VULGUIS, &nom_signal,0); //SIGNAL funcionarà com nom_signal.

//tractament error
if (sigaction(SIGNAL QUE VULGUIS, &nom_signal, NULL) < 0) error_y_exit("asdfg",1);

//-------------------------------------------

execlp("executable","nom del que vols executar",argv[0]...argv[n],char*(null));
error_y_exit("ha fallado la mutacion",1);

//-------------------------------------------

int p = fork();
if (p == -1) {
	sprintf(buffer,"error...");
	error_y_exit(buffer,1);
}
p > 0; //al pare li torna al pid del fill
p = 0;//al fill

//-------------------------------------------

waitpid(pid,&status,maincra);
if (pid == 'pid'); //esperarà a que el fill amb pid = pid sigui zombie
if (pid == -1); //esperarà a que qualsevol procés fill sigui zombie
maincra = 0; //bloueja el pare si no hi ha processos fill no zombie
maincra = WNOHANG; //torna 0 si tens processos fills que no són zombie

//-------------------------------------------

punter = sbrk(num*sizeof(type)); //punter apunta a on comença l'espai reservat de la heap
if (sbrk(num*sizeof(type)) > 0); //reserva memòria
if (sbrk(num*sizeof(type)) < 0); //allibera memòria
if (sbrk(num*sizeof(type)) == 0); //el punter apuntarà a la memòria del heap actual

//-------------------------------------------

