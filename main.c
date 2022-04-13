#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define CANALE 100
#define USER 50

#define BLUE 9
#define GREEN 10
#define RED 4
#define YELLOW 6
#define PURPLE 5
#define WHITE 15
#define GRAY 8

void set_color(int color_code)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color_code);
}

int numar_canale;

struct canal{
    char id_canal[CANALE][CANALE];
    char nume_canal[CANALE][CANALE];
    double rating_canale[CANALE];
    int numar_rating[CANALE];
}c;

struct persoana{
    char nume[USER];
    char prenume[USER];
    char email[USER];
    char parola[USER];
    char data_nasterii[USER];
    char gen[USER];
}p;

void inregistrare()
{
    printf("-----");
    set_color(YELLOW);
    printf(" Inregistrare ");
    set_color(WHITE);
    printf("----- \n\n");

    FILE *fp = fopen("date-utilizatori.txt", "a+");

    int i;

    set_color(GRAY);
    printf("NUME: ");
    set_color(WHITE);
    scanf("%s", p.nume);

    set_color(GRAY);
    printf("PRENUME: ");
    set_color(WHITE);
    scanf("%s", p.prenume);

    char line[USER*6];
    int ok = 0;
    while (ok == 0){
        int aux = 1;

        set_color(GRAY);
        printf("ADRESA DE EMAIL: ");
        set_color(WHITE);
        scanf("%s", p.email);

        while (eof() != 1 && fgets(line, USER*6, fp)!= NULL){
            char *eml = strtok(line, " ");
            char *oth = strtok(NULL, "\n");

            if (strcmp(p.email, eml) == 0)
                aux = 0;
        }
        if (aux == 0){
            set_color(RED);
            printf("Adresa de email introdusa exista deja!\n");
            set_color(WHITE);
        }
        else
            ok = 1;
    }

    while (strlen(p.parola)<8){
        set_color(GRAY);
        printf("PAROLA");
        set_color(WHITE);
        printf(" (cel putin 8 caractere)");
        set_color(GRAY);
        printf(": "); scanf("%s", p.parola);
        set_color(WHITE);
    }

    set_color(GRAY);
    printf("DATA NASTERII");
    set_color(WHITE);
    printf(" (zz/ll/aaaa)");
    set_color(GRAY);
    printf(": "); scanf("%s", p.data_nasterii);
    set_color(WHITE);

    set_color(GRAY);
    printf("GEN");
    set_color(WHITE);
    printf(" (feminin/masculin)");
    set_color(GRAY);
    printf(": "); scanf("%s", p.gen);
    set_color(WHITE);

    fprintf(fp, "%s %s %s;%s;%s;%s;\n", p.email,
                                        p.parola,
                                        p.nume,
                                        p.prenume,
                                        p.data_nasterii,
                                        p.gen);

    fclose(fp);

    FILE *fp2 = fopen("abonat-canale.txt", "a");
    fprintf(fp2, "%s ;\n", p.email);

    fclose(fp2);
}


int logat = 0;

char date[6*USER];
void logare()
{
    FILE *fp = fopen("date-utilizatori.txt", "r");
    char line[USER*6];

    printf("-----");
    set_color(YELLOW);
    printf(" Logare ");
    set_color(WHITE);
    printf("----- \n\n");

    set_color(GRAY);
    printf("ADRESA DE EMAIL: ");
    set_color(WHITE);
    scanf("%s", p.email);

    set_color(GRAY);
    printf("PAROLA: ");
    set_color(WHITE);
    scanf("%s", p.parola);

    int oke = 0, okp = 0;
    while (logat == 0 && eof() != 1 && fgets(line, USER*6, fp)!= NULL){
        char *em = strtok(line, " ");
        char *pass = strtok(NULL, " ");
        strcpy(date, strtok(NULL, "\n"));

        if(strcmp(p.email, em) == 0 && strcmp(p.parola, pass) == 0)
            logat = 1;
    }
    if (logat == 0){
        set_color(RED);
        printf("\nAdresa de email sau parola invalida(e)!");
        set_color(WHITE);
        sleep(2);
    }
    else{
        set_color(GREEN);
        printf("\nTe-ai logat cu succes!");
        set_color(WHITE);
        sleep(2);
    }
    system("cls");
}


double top_rating[CANALE];

char top_canale[CANALE][CANALE];

void citire_canale()
{
    FILE *fp = fopen("canale.txt", "r");

    fscanf(fp, "%d", &numar_canale);

    int i;
    char rat_can[CANALE];
    for (i=0; i<numar_canale; i++){
        fscanf(fp, "%s%s%lf%d", c.id_canal[i],
                                c.nume_canal[i],
                                &c.rating_canale[i],
                                &c.numar_rating[i]);
    }
    fclose(fp);
}

char alegere_canal[CANALE];

char abonat_canale[CANALE][CANALE*CANALE];
char email_abonat[USER][USER];

char w[CANALE][CANALE];
void abonare()
{
    FILE *fp = fopen("abonat-canale.txt", "r");
    char line[USER*6];
    int n=0;
    while (eof() != 1 && fgets(line, USER*6, fp)!= NULL){
        strcpy(email_abonat[n], strtok(line, " "));
        strcpy(abonat_canale[n], strtok(NULL, "\n"));
        n++;
    }
    fclose(fp);

    int i=0;
    int ok = 0;
    while(i<n && ok == 0){
        if (strcmp(email_abonat[i], p.email) == 0)
            ok = 1;
        i++;
    }

    int y = 0;
    int ok2=1;

    if (strcmp(abonat_canale[i-1], ";")==0){
        strcpy(abonat_canale[i-1], "");
    }
    else{
        char vector[CANALE*CANALE];
        strcpy(vector, abonat_canale[i-1]);
        strcat(vector, " ");
        while (strcmp(vector, " ")==1){
            char *can = strtok(vector, ";");
            char *oth = strtok(NULL, "\n");

            strcat(w[y], can);
            y++;
            strcpy(vector, oth);
        }

        for (int j=0; j<y; j++)
            if (strcmp(alegere_canal, w[j])==0)
                ok2 = 0;
    }

    if (ok2==1){
            strcat(abonat_canale[i-1], alegere_canal);
            strcat(abonat_canale[i-1], ";");
            set_color(GREEN);
            printf("Te-ai abonat la canalul %s!", alegere_canal);
            set_color(WHITE);
        }
        else{
            set_color(RED);
            printf("Esti deja abonat(a) la acest canal!");
            set_color(WHITE);
        }

    fp = fopen("abonat-canale.txt", "w");

    for (i=0; i<n; i++)
        fprintf(fp, "%s %s\n", email_abonat[i],
                               abonat_canale[i]);
    fclose(fp);
}

void dezabonare()
{
    FILE *fp = fopen("abonat-canale.txt", "r");
    char line[USER*6];
    int n=0;
    while (eof() != 1 && fgets(line, USER*6, fp)!= NULL){
        strcpy(email_abonat[n], strtok(line, " "));
        strcpy(abonat_canale[n], strtok(NULL, "\n"));
        n++;
    }
    fclose(fp);

    int i=0;
    int ok = 0;
    while(i<n && ok == 0){
        if (strcmp(email_abonat[i], p.email) == 0)
            ok = 1;
        i++;
    }

    int y = 0;
    int j;

    if (strcmp(abonat_canale[i-1], ";")==0){
        strcpy(abonat_canale[i-1], "");
    }
    else{
        char vector[CANALE*CANALE];
        strcpy(vector, abonat_canale[i-1]);
        strcat(vector, " ");
        while (strcmp(vector, " ")==1){
            char *can = strtok(vector, ";");
            char *oth = strtok(NULL, "\n");

            strcat(w[y], can);
            y++;
            strcpy(vector, oth);
        }
        ok=-1;
        for (j=0; j<y; j++)
            if (strcmp(alegere_canal, w[j])==0)
                ok = j;
    }

    strcpy(abonat_canale[i-1], "");

    if (ok!=-1){
        for (j=ok; j<y; j++)
            strcpy(w[j], w[j+1]);
        y--;
    }

    for (j=0; j<y; j++){
        strcat(abonat_canale[i-1], w[j]);
        strcat(abonat_canale[i-1], ";");
    }

    if(ok==-1){
        set_color(RED);
        printf("Nu esti abonat(a) la acest canal!");
        set_color(WHITE);
    }
    else{
        set_color(GREEN);
        printf("Te-ai dezabonat de la canalul %s!", alegere_canal);
        set_color(WHITE);
    }

    if (y==0)
        strcpy(abonat_canale[i-1], ";");

    fp = fopen("abonat-canale.txt", "w");

    for (i=0; i<n; i++)
        fprintf(fp, "%s %s\n", email_abonat[i],
                               abonat_canale[i]);
    fclose(fp);
}

char ca[CANALE][CANALE];
void abonat()
{
    FILE *fp = fopen("abonat-canale.txt", "r");
    char line[USER*6];
    int n=0;
    while (eof() != 1 && fgets(line, USER*6, fp)!= NULL){
        strcpy(email_abonat[n], strtok(line, " "));
        strcpy(abonat_canale[n], strtok(NULL, "\n"));
        n++;
    }
    fclose(fp);

    int y=0;;

    int i=0;
    int ok = 0;
    while(i<n && ok == 0){
        if (strcmp(email_abonat[i], p.email) == 0){
            ok=1;
            if (strcmp(abonat_canale[i], ";")==0){
                set_color(RED);
                printf("Nu esti abonat(a) la niciun canal!");
                set_color(WHITE);
                sleep(2);
            }
            else{
                char vector[CANALE*CANALE];
                strcpy(vector, abonat_canale[i]);
                strcat(vector, " ");
                while (strcmp(vector, " ")==1){
                    strcpy(ca[y], "");
                    char *can = strtok(vector, ";");
                    char *oth = strtok(NULL, "\n");

                    strcat(ca[y], can);
                    y++;
                    strcpy(vector, oth);
                }
            }

        }
        else
            i++;
    }

    if (strcmp(abonat_canale[i], ";")==1){
        for (int j=0; j<y; j++){
            set_color(PURPLE);
            printf("%s\n", ca[j]);
            set_color(WHITE);
        }
        sleep(2);
    }
}

void rating_can()
{
    FILE *fp = fopen("canale.txt", "w");

    double rating = 0;
    while(rating<1 || rating>5){
        printf("Introduceti un numar (1-5): ");
        scanf("%lf", &rating);
    }

    int i;
    for (i=0; i<numar_canale; i++)
        if (strcmp(alegere_canal, c.nume_canal[i])==0){
        c.rating_canale[i] = (double)((c.rating_canale[i]*c.numar_rating[i] + rating)/(c.numar_rating[i]+1));
        c.numar_rating[i]++;

        set_color(GREEN);
        printf("\nAi oferit %.2lf rating canalului %s!!", rating, alegere_canal);
        set_color(WHITE);
        sleep(2);
    }

    fprintf(fp,"%d\n", numar_canale);

    for (i=0; i<numar_canale; i++)
        fprintf(fp, "%s %s %.2lf %d\n", c.id_canal[i],
                                        c.nume_canal[i],
                                        c.rating_canale[i],
                                        c.numar_rating[i]);

    fclose(fp);
}

void sortare(char tc[CANALE][CANALE], double tr[CANALE], double rc[CANALE])
{
    int i, j;
    for (i=0; i<numar_canale; i++){
        tr[i] = rc[i];
    }

    double aux;
    char can[CANALE];
    for (i=1; i<numar_canale; i++){
        aux = tr[i];
        strcpy(can, tc[i]);
        j=i-1;
        while (j>=0 && aux>tr[j]){
            tr[j+1] = tr[j];
            strcpy(tc[j+1], tc[j]);
            j--;
        }
        tr[j+1] = aux;
        strcpy(tc[j+1], can);
    }
}

int main()
{
    citire_canale();

    int i;
    for (i=0; i<numar_canale; i++){
        strcpy(top_canale[i], c.nume_canal[i]);
        top_rating[i] = c.rating_canale[i];
    }


    int end_program=1;

    while (end_program){
        int alegere_meniu_principal = 0;

        printf("-----");
        set_color(BLUE);
        printf(" MENIU PRINCIPAL ");
        set_color(WHITE);
        printf("----- \n\n");

        printf("1. ");
        set_color(YELLOW);
        printf("Inregistrare");
        set_color(WHITE);

        printf("\n2. ");
        set_color(YELLOW);
        printf("Logare");
        set_color(WHITE);

        printf("\n3. ");
        set_color(YELLOW);
        printf("Top canale");
        set_color(WHITE);

        printf("\n4. ");
        set_color(RED);
        printf("Iesire\n\n");
        set_color(WHITE);

        while (alegere_meniu_principal < 1 || alegere_meniu_principal > 4){
            printf("Selectati optiunea dorita: ");
            scanf("%d", &alegere_meniu_principal);
        }

        system("cls");

        if (alegere_meniu_principal == 1){  //----------------------------------------------- INREGISTRARE --------------------------------------
            inregistrare();
        }
        if (alegere_meniu_principal == 2){  //----------------------------------------------- LOGARE --------------------------------------------
            logare();


            while (logat){
                int alegere_logare = 0;

                printf("-----");
                set_color(BLUE);
                printf(" OPTIUNI ");
                set_color(WHITE);
                printf("----- \n\n");

                printf("1. ");
                set_color(YELLOW);
                printf("Date utilizator");
                set_color(WHITE);

                printf("\n2. ");
                set_color(YELLOW);
                printf("Canale");
                set_color(WHITE);

                printf("\n3. ");
                set_color(RED);
                printf("Delogare\n\n");
                set_color(WHITE);

                while (alegere_logare < 1 || alegere_logare > 3){
                    printf("Selectati optiunea dorita: ");
                    scanf("%d", &alegere_logare);
                }

                system("cls");

                if (alegere_logare == 1){               //----------------------------------- DATE UTILIZATOR ------------------------------------
                    char *nume;
                    char *prenume;
                    char *data_nasterii;
                    char *gen;

                    nume =  strtok(date, ";");
                    prenume = strtok(NULL, ";");
                    data_nasterii = strtok(NULL, ";");
                    gen = strtok(NULL, ";");

                    printf("-----");
                    set_color(BLUE);
                    printf(" DATE UTILIZATOR ");
                    set_color(WHITE);
                    printf("----- \n\n");

                    set_color(GRAY);
                    printf("Nume: ");
                    set_color(WHITE);
                    printf("%s\n", nume);

                    set_color(GRAY);
                    printf("Prenume: ");
                    set_color(WHITE);
                    printf("%s\n", prenume);

                    set_color(GRAY);
                    printf("Adresa de email: ");
                    set_color(WHITE);
                    printf("%s\n", p.email);

                    set_color(GRAY);
                    printf("Data nasterii: ");
                    set_color(WHITE);
                    printf("%s\n", data_nasterii);

                    set_color(GRAY);
                    printf("Gen: ");
                    set_color(WHITE);
                    printf("%s\n", gen);

                    printf("\n");
                    system("pause");
                }

                if (alegere_logare == 2){               //----------------------------------- MENIUL CANALELOR -----------------------------------

                    int canale = 1;
                    while(canale){
                        printf("-----");
                        set_color(BLUE);
                        printf(" CANALE ");
                        set_color(WHITE);
                        printf("----- \n\n");

                        int alegere_meniu_canale = 0;

                        printf("1. ");
                        set_color(YELLOW);
                        printf("Canale disponibile");
                        set_color(WHITE);

                        printf("\n2. ");
                        set_color(YELLOW);
                        printf("Canale la care esti abonat");
                        set_color(WHITE);

                        printf("\n3. ");
                        set_color(YELLOW);
                        printf("Cautare");
                        set_color(WHITE);

                        printf("\n4. ");
                        set_color(YELLOW);
                        printf("Top canale");
                        set_color(WHITE);

                        printf("\n5. ");
                        set_color(RED);
                        printf("Iesire\n\n");
                        set_color(WHITE);

                        while (alegere_meniu_canale < 1 || alegere_meniu_canale > 5){
                            printf("Selectati optiunea dorita: ");
                            scanf("%d", &alegere_meniu_canale);
                        }

                        system("cls");

                        if (alegere_meniu_canale == 1){     //-------------------------- CANALE DISPONIBILE -------------------------------------
                            printf("-----");
                            set_color(BLUE);
                            printf(" CANALE DISPONIBILE ");
                            set_color(WHITE);
                            printf("----- \n\n");

                            int i;
                            for (i=0; i<numar_canale; ++i){
                                printf("id:");
                                set_color(GRAY);
                                printf("%s", c.id_canal[i]);
                                set_color(WHITE);
                                printf(" - ");
                                set_color(PURPLE);
                                printf("%s \n", c.nume_canal[i]);
                                set_color(WHITE);
                            }

                            printf("\nDoriti sa accesati un canal? (");
                            set_color(GREEN);
                            printf("da=1");
                            set_color(WHITE);
                            printf("/");
                            set_color(RED);
                            printf(" nu=0");
                            set_color(WHITE);
                            printf("): ");

                            int raspuns;
                            scanf("%d", &raspuns);

                            if (raspuns == 1){
                                printf("\nIntroduceti numele canalului: ");
                                set_color(PURPLE);
                                scanf("%s", &alegere_canal);
                                set_color(WHITE);

                                int i=0, ok=0;
                                while (i<numar_canale && ok == 0){
                                    if(strcmp(alegere_canal, c.nume_canal[i]) == 0){
                                        ok = 1;
                                    }
                                    i++;
                                }

                                system("cls");

                                if (ok == 1){
                                    int abonare_rating = 1;
                                    while(abonare_rating){
                                        int alegere_optiune = 0;

                                        printf("1. ");
                                        set_color(YELLOW);
                                        printf("Abonare");
                                        set_color(WHITE);

                                        printf("\n2. ");
                                        set_color(YELLOW);
                                        printf("Dezabonare");
                                        set_color(WHITE);

                                        printf("\n3. ");
                                        set_color(YELLOW);
                                        printf("Rating");
                                        set_color(WHITE);

                                        printf("\n4. ");
                                        set_color(RED);
                                        printf("Iesire\n");
                                        set_color(WHITE);

                                        while (alegere_optiune < 1 || alegere_optiune > 4){
                                            printf("\nSelectati optiunea dorita: ");
                                            scanf("%d", &alegere_optiune);
                                        }

                                        system("cls");

                                        if (alegere_optiune == 1){  //--------------------------- ABONARE --------------------------------------------
                                            abonare();
                                            sleep(2);
                                        }

                                        if(alegere_optiune == 2){   //--------------------------- DEZABONARE ------------------------------------------
                                            dezabonare();
                                            sleep(2);
                                        }

                                        if(alegere_optiune == 3){   //--------------------------- RATING ---------------------------------------------
                                            rating_can();
                                        }

                                        if (alegere_optiune == 4)
                                            abonare_rating = 0;
                                        system("cls");
                                    }
                                }
                                else{
                                    set_color(RED);
                                    printf("Acest canal nu exista!");
                                    set_color(WHITE);
                                    sleep(2);
                                }

                                system("cls");
                            }
                        }

                        if (alegere_meniu_canale == 2){     //-------------------------- CANALE LA CARE ESTI ABONAT -----------------------------
                            printf("----- ");
                            set_color(BLUE);
                            printf("CANALE LA CARE ESTI ABONAT");
                            set_color(WHITE);
                            printf(" -----\n\n");
                            abonat();
                        }

                        if (alegere_meniu_canale == 3){     //-------------------------- CAUTARE ------------------------------------------------
                            printf("Introduceti numele canalului: ");
                            set_color(PURPLE);
                            scanf("%s", &alegere_canal);
                            set_color(WHITE);

                            int i=0, ok=0;
                            while (i<numar_canale && ok == 0){
                                if(strcmp(alegere_canal, c.nume_canal[i]) == 0){
                                    ok = 1;
                                }
                                i++;
                            }

                            system("cls");

                            if (ok == 1){
                                int abonare_rating = 1;
                                while(abonare_rating){
                                    int alegere_optiune = 0;

                                    printf("1. ");
                                    set_color(YELLOW);
                                    printf("Abonare");
                                    set_color(WHITE);

                                    printf("\n2. ");
                                    set_color(YELLOW);
                                    printf("Dezabonare");
                                    set_color(WHITE);

                                    printf("\n3. ");
                                    set_color(YELLOW);
                                    printf("Rating");
                                    set_color(WHITE);

                                    printf("\n4. ");
                                    set_color(RED);
                                    printf("Iesire\n");
                                    set_color(WHITE);


                                    while (alegere_optiune < 1 || alegere_optiune > 4){
                                        printf("\nSelectati optiunea dorita: ");
                                        scanf("%d", &alegere_optiune);
                                    }

                                    system("cls");

                                    if (alegere_optiune == 1){  //--------------------------- ABONARE --------------------------------------------
                                        abonare();
                                        sleep(2);
                                    }

                                    if(alegere_optiune == 2){   //--------------------------- DEZABONARE ------------------------------------------
                                        dezabonare();
                                        sleep(2);
                                    }

                                    if(alegere_optiune == 3){   //--------------------------- RATING ---------------------------------------------
                                        rating_can();
                                    }

                                    if (alegere_optiune == 4)
                                        abonare_rating = 0;
                                    system("cls");
                                }
                            }

                            else{
                                set_color(RED);
                                printf("Acest canal nu exista!\n");
                                set_color(WHITE);
                                sleep(2);
                            }
                        }

                        if (alegere_meniu_canale == 4){ //------------------------------ TOP CANALE -------------------------------------------
                            sortare(top_canale, top_rating, c.rating_canale);

                            printf("-----");
                            set_color(BLUE);
                            printf(" TOP CANALE ");
                            set_color(WHITE);
                            printf("----- \n\n");

                            int i=0;
                            for (i=0; i<25; i++){
                                set_color(PURPLE);
                                printf("%s", top_canale[i]);
                                set_color(WHITE);
                                printf(" - ");
                                set_color(GRAY);
                                printf("%.2lf\n", top_rating[i]);
                                set_color(WHITE);
                            }

                            printf("\n");
                            system("pause");
                        }


                        if (alegere_meniu_canale == 5){
                            canale = 0;
                        }
                        system("cls");
                    }
                }
                if (alegere_logare == 3){
                    logat = 0;
                }
                system("cls");
            }
        }

        if (alegere_meniu_principal == 3){  //----------------------------------------------- TOP CANALE --------------------------------------
            sortare(top_canale, top_rating, c.rating_canale);

            printf("-----");
            set_color(BLUE);
            printf(" TOP CANALE ");
            set_color(WHITE);
            printf("----- \n\n");

            int i=0;
            for (i=0; i<25; i++){
                set_color(PURPLE);
                printf("%s", top_canale[i]);
                set_color(WHITE);
                printf(" - ");
                set_color(GRAY);
                printf("%.2lf\n", top_rating[i]);
                set_color(WHITE);
            }

            printf("\n");
            system("pause");
        }

        system("cls");

        if(alegere_meniu_principal == 4){   //----------------------------------------------- IESIRE --------------------------------------------
            set_color(BLUE);
            printf("La revedere!!!\n");
            set_color(WHITE);
            end_program = 0;
        }
    }
}
