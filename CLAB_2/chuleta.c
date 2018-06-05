    /*********************
         RANDOM STUFF
    *********************/

    void error(char *msg) {
        perror(msg);
        exit(1);
    }

    void Usage() {
        char buff[85];
        sprintf(buff,"USAGE: [insert message]");
        printf(1,buff,strlen(buff));
    }

    /*********************
        PIPE CON NOBMRE
    *********************/

    //Cualsevol amb permisos hi pot accedir.
    open(nom,R);
    open(nom,W);
    //no es poden obrir a la vegada, sino GG

    /*********************
        PIPE SIN NOBMRE
    *********************/

    /*
    * es crea vector de mida 2:
    *    · v[0] <- canal entrada (escriptura)
    *    · v[1] <- canal sortida (lectura)
    */

    int fd_v[2];
    int ret = pipe(fd_v);

    /*********************
           SOCKETS
    *********************/

    /**???????????????????/

    /*********************
          DUP - DUP2
    *********************/

    new_channel = dup(channel);
    //fa copia del canal que passes per paràmetre

    new_channel = dup2(channel,new_channel);
    //borra new_channel i duplica channel

    /*********************
            READ
    *********************/

    int ret =  read(int f, void *buffer, sizeof(variable));
    if (ret == 0) //res a llegir
    if (ret >  0) //segueix llegint
    if (ret <  0) error("read");

    /*
    * ret = num_bytes_llegits;
    * f es el canal
    */

    /*********************
            WRITE
    *********************/

    int ret =  write(int f, const void *buffer, sizeof(variable));
    if (ret == 0) //res a llegir
    if (ret >  0) //segueix llegint
    if (ret <  0) error("read");
    ret = num_bytes_escrits;

    /*********************
            OPEN
    *********************/

    int file = open("path_to_file", acces_mode, permisos);
    //file <- nou canal
    write(file,"string random\n", 14); //escrius al file
    close(file); //tancar el canal

    /*********************
            LSEEK
    *********************/
    int fd      = fitxer_desti;
    int despl   = desplaçament;
    int pos = lseek(fd,despl,rel);

    /*
    rel = SEEK_SET -> posicio_l/e = desplaçament
    rel = SEEK_CUR -> posicio_l/e = posicio_l/e + desplaçament
    rel = SEEK_END -> posicio_l/e = file_size + desplaçament
    */
