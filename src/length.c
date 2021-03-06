/*
 *  Copyright (C) 2016 leminski <atleminski@gmail.com> https://github.com/leminski
 *
 *  This file is part of WPAdiz
 *
 *  WPAdiz is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *  WPAdiz is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with WPAdiz. If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include <string.h>
#include <locale.h>

#include <unistd.h>

#include "lib/essential.h"
#include "lib/outerr.h"
#include "lib/wpalength/outprint.h"

 #define MAX_LENGTH_WPA  64

 struct _file_information {
                            size_t size_file;              /* Byte size file */
                            char* name_file;               /* Name file */
                          };

uint8_t  sntnell_tab  = 0;
unsigned tab          = 0;
unsigned trash        = 0;
unsigned lengshort    = 0;
unsigned max_leng_wpa = 0;
unsigned long charmax = 0;

 /* Prototipi */

 void usage(const char*);
 void pars_leng_char_verb(FILE*, struct _file_information *, const uint8_t*, uint8_t*);
 void pars_leng_char(FILE*, struct _file_information *, const uint8_t*);
 void file_size(FILE*, struct _file_information *);
 int  check_length_save(struct _file_information *, const uint8_t*, uint8_t*, uint8_t*);
 void check_charset_space(wchar_t*);
 int  automatic_erase(struct _file_information *, const uint8_t*);

int main(int argc, char* argv[]) {

/* Varie informazioni del programma
  *      richiamabile attravarso la
   *         funzione author();
    */

_date     ="2016";
_version  ="v.1.2.04";
_programm ="WPAlength";
_author   ="(leminski) `https://github.com/leminski`";

   author();

   if(argc == 1) {
      printf("Nessuna opzione: digitare -h\n");
      return -1;
   }

   setlocale(LC_ALL, "en_US.UTF-8");   /* Codifica Unicode US UTF-8 */

   int ch;
   uint8_t leng = 0;
   uint8_t verbose = 0, whatsave = 1;
   char condition[0];

   struct _file_information __information_file;

    /* Initialize structure */

    __information_file.name_file     = NULL;
    __information_file.size_file     = 0;

   opterr=0;  /* Per non mostrare l'errore di default a schermo del parametro non valido */
   while( (ch = getopt(argc,argv,"f:l:hsev:S")) != -1 ) {

      switch(ch) {

         case 'h': /* help */

	          if(argc > 1) { usage(argv[0]); return -1; }

         case 'f': /* file input */

	          __information_file.name_file = optarg;

	          FILE *read;

	          read = fopen(__information_file.name_file, "r");

                  if(!read) { perror("Error: "); return -1; }

	          file_size(read, &__information_file);

                  fclose(read);

	          if( __information_file.size_file == 0x00 )  {

	             printf("\n File '%s' vuoto\n", __information_file.name_file);
	             return -1;
	          }

                  break;

         case 'l': /* lunghezza parola */

                   if( atoi(optarg) <= 0 || atoi(optarg) > MAX ) {

                      outerr_leng(INVALID_PARAM_L, optarg);
                      return -1;
                   }

                  leng = (uint8_t)atoi(optarg);

                  break;

         case 's': /* Salvataggio parole di lunghezza inferiore a '-l */

	          whatsave = 0;
                  break;

         case 'e': /* Elimina le parole inferiori al numero specificato con il parametro '-l' */

                  while(condition[0] != 's' && condition[0] != 'n') {

                     fflush(stdout);
                     fflush(stdin);

       	             printf("\n "YELLOW"[!] Stai per modificare il file '%s'. Vuoi procedere"CLOSECOLOR" s/n?: ",__information_file.name_file);
        	     condition[0] = getchar();

                     fflush(stdin);
                     fflush(stdout);
        	  }

        	  if(condition[0] == 's') {

	             automatic_erase(&__information_file, &leng);
	          }
	          else if(condition[0] == 'n') {

	              printf("\n Annullato.\n");
	              return -1;
	          }
	          return 0;

         case 'v':

                  if( atoi(optarg) >= 1 && atoi(optarg) <= 3 )
                     verbose = atoi(optarg);
                  else {
                      printf("ERROR\n"); return 0;
                  }
                break;

         case '?': default:

                  printf("wpalength: Unknow parameter '-%c' \nDigit: '-h'\n", optopt); return -1;
      }
   }

   for( ; optind < argc; optind++ ) {

     if( strcmp( argv[optind], "-" ) ) {
        printf("wpalength: Unknow parameter '%s' \nDigit: '-h'\n", argv[optind]);
        return -1;
     }
   }

   if(__information_file.name_file == NULL) {
      outerr_leng(ERROR_PARAM_F, 0);
      return -1;
   }

   if( leng == 0 ) {
      outerr_leng(ERROR_L, NULL);
      return -1;
   }

   check_length_save( &__information_file, &leng, &whatsave, &verbose );

  return 0;

} /* End main */

void
  usage(const char* ptr)

  {
        fprintf(stderr, " Usage: %s -f <fileinput> -l <maxlengthchar> -[OPTIONAL_PARAMETER..]\n\n"
                        " Parameters:\n\n"
                        " -f :   File da analizzare\n"
                        " -l :   Lunghezza minima di ogni singola parola\n\n"
                        " Optional Parameters:\n\n"
                        " -v :   Modalità verbose. Visualizza ogni singola parola con vari dettagli.\n"
                        "        Puo assumere il valore:\n"
                        "           1 : visualizza tutto\n"
                        "           2 : visualizza solo le parole che NON SONO inferiori\n"
                        "               a quelle indicate con -l\n"
                        "           3 : visualizza solo le parole che SONO inferiori\n"
                        "               a quelle indicate con -l e quelle superiori a 64.\n"
                        " -s :   Salva le parole, inferiori al numero indicato con -l, in un file\n"
                        "        denominato con \"_save.txt\"\n"
                        " -e :   Elimina nel file originale le parole inferiori indicate dal parametro '-l'\n"
                        "        e tabulazioni inutili se sono presenti\n\n", ptr);
        exit(0);
  }

void
  file_size(FILE* read, struct _file_information* _info)      /* Calcolo Grandezza file */

  {
       rewind(read);                                          /* Porta il cursore all inizio del file */
       fseek(read, 0, SEEK_END);

       _info->size_file = ftell(read);
  }

int
  check_length_save(struct _file_information *__info, const uint8_t* leng, uint8_t* boolean/* 1 - stdin. 0 - save of file*/, uint8_t* verbose) {

   FILE *read, *write;

   read = fopen(__info->name_file, "r");

   switch( *boolean ) {                                       /* # Output sullo stdin(schermo) # */

      case 1:

              if( *verbose == 0 ) {                           /* Modalità non verbose */

                 printf(" [-] Reading file...\n");

                 pars_leng_char(read, __info, *&leng);
                 fclose(read);
              }
              else if( *verbose >= 1 && *verbose <= 3 ) {     /* Modalità verbose */

                 sleep(1);                                    /* Blocca per 1 secondo */

                 pars_leng_char_verb(read, __info, *&leng, *&verbose);
                 fclose(read);
              }

              file_print_size(__info->size_file);             /* Stampa la grandezza del file */
              out_print_read_file(__info->name_file, &charmax, *leng, &lengshort, max_leng_wpa);

              break;

      case 0:                                                 /* Salva le parole con meno di '-l' caratteri in un file */
              write = fopen(strcat(__info->name_file, "_save.txt"), "w");

              wchar_t buffer[9000];

              if(!write) { perror(""); return -1; }

              while( fgetws(buffer, sizeof(buffer), read) ) {

                 charmax++;
                 check_charset_space(buffer);

                 if( (wcslen(buffer) - trash) < *leng || (wcslen(buffer) - trash) > MAX_LENGTH_WPA ) {

                    fwprintf(write, L"-°%lu (%u/%u) %ls", charmax, (unsigned)( wcslen(buffer) - trash), *leng, buffer);
                 }
              } /* End while */

              printf(" Successfully saved file in '%s'\n", __info->name_file);
              fclose(read); fclose(write);

              break;

   } /* End switch() */

   if( sntnell_tab == 1 ) {

      printf("\n"YELLOW"[ ! ]"CLOSECOLOR""BLUE"[ Sono presenti dei caratteri di tabulazione inutili. ]"CLOSECOLOR"\n"
             YELLOW"[ ! ]"CLOSECOLOR""BLUE"[ Si consiglia di pulire il file \"%s\" con \"-e\"         ]"CLOSECOLOR"\n\n", __info->name_file);
   }

   return 0;
 }

void
  pars_leng_char_verb(FILE* read, struct _file_information *_info, const uint8_t* leng, uint8_t* type_verb)

  {
      wchar_t buffer[9000];

      while(fgetws(buffer, sizeof(buffer), read) ) {

         charmax++;
         check_charset_space(buffer);

         if( *type_verb == 1 ) {

           if( ( wcslen(buffer) - trash ) >= *leng && ( wcslen(buffer) - trash ) <= MAX_LENGTH_WPA ) {
               out_add_print(buffer, (wcslen(buffer) - trash), tab);
            }

            if( ( wcslen(buffer) - trash ) < *leng ) {
               lengshort++;
               out_err_print(buffer, (wcslen(buffer) - trash), tab);
            }

            if( ( wcslen(buffer) - trash ) > MAX_LENGTH_WPA ) {
               max_leng_wpa++;
               out_err_print(buffer, (wcslen(buffer) - trash), tab);
            }
         }
         else if( *type_verb == 2 ) {

            if( ( wcslen(buffer) - trash ) >= *leng && ( wcslen(buffer) - trash ) <= MAX_LENGTH_WPA )
               out_add_print(buffer, (wcslen(buffer) - trash), tab);
         }
         else if( *type_verb == 3 ) {

            if( ( wcslen(buffer) - trash ) < *leng) {
               lengshort++;
               out_err_print(buffer, (wcslen(buffer) - trash), tab);
            }

            if( ( wcslen(buffer) - trash ) > MAX_LENGTH_WPA ) {
               max_leng_wpa++;
               out_err_print(buffer, (wcslen(buffer) - trash), tab);
            }
         }
      }
  }

void
  pars_leng_char(FILE* read, struct _file_information *_info, const uint8_t* leng)

  {
      trash = 0;
      wchar_t buffer[9000];

      while(fgetws(buffer, sizeof(buffer), read) ) {

         charmax++;
         check_charset_space(buffer);

         if( ( ( wcslen(buffer) - trash ) ) < *leng)
            lengshort++;

         if( ( wcslen(buffer) - trash ) > MAX_LENGTH_WPA)
            max_leng_wpa++;
      }
  }

void
  check_charset_space(wchar_t* word)

  {
       tab        = 0;
       trash      = 0;

       for(register unsigned i; i <= wcslen(word); i++) {

          if( ( word[i] >= 0x00 && word[i] <= 0x08 ) || ( word[i] >= 0xB && word[i] <= 0x1F ) ) {
             trash++;
          }

          if( word[i] == 0x09 ) {
             tab++;
             trash++;
          }
      }

      if( tab > 0 )
         sntnell_tab = 1;
  }

int
  automatic_erase(struct _file_information *__info, const uint8_t* length)

  {
      wchar_t buffer[9000];

      FILE *read, *write, *read2, *write2;

      read  = fopen(__info->name_file,"r");

      printf("\n  [+] Check del file '%s'\n", __info->name_file);

      pars_leng_char(read, __info, *&length);                    /* Controlla le parole inferiori al numero indicato con il parametro -l */

      if(lengshort == 0 && sntnell_tab == 0) {

         printf("\n Non sono presenti parole inferiori a quelle indicate.\n");

         return 0;
      }

      rewind(read);

      /* In caso che le parole siano inferiori..*/

      write = fopen(".tmpfile","w");

      if(!write) { perror(" "); return -1; }

      printf("  [-] Modifica file '%s' in corso..\n", __info->name_file);

      /* Rilegge il file originale */

      while( fgetws(buffer, sizeof(buffer), read) ) {

         check_charset_space(buffer);

         if( ( wcslen(buffer) - trash ) >= *length && ( wcslen(buffer) - trash ) <= MAX_LENGTH_WPA )
            fwprintf(write, L"%ls", buffer);                           /* Scrive nel file temporaneo */
      }

      fclose(read); fclose(write);

      memset(buffer, 0x00, sizeof(buffer));

      read2  = fopen(".tmpfile", "r");
      write2 = fopen(__info->name_file, "w");

      /* Legge il file temporaneo */
      while( fgetws(buffer, sizeof(buffer), read2) ) {

         if( sntnell_tab == 1 ) {

            for(unsigned int i = 0; i <= wcslen(buffer); i++) {

               if( buffer[i] == '\t' || buffer[i] == '\0' )            /* Omette le tabulazioni e il terminatore stringa*/
                  ;
               else
                  fwprintf(write2, L"%lc", buffer[i]);                 /* Scrive il contenuto nel file Originale */
            }
         }
         else
            fwprintf(write2, L"%ls", buffer);
      }

      fclose(read2); fclose(write2);

      out_print_cancell(&lengshort, &charmax);

      if( sntnell_tab == 1 ) { printf(" Completato: Eliminate tabulazioni non necessarie.\n\n"); }

      remove(".tmpfile");   /* Elimina il file temporaneo creato in precedenza */

      return 0;
  }
