#include <stdio.h>
#include <stdlib.h>
#include "headers.h"
#include <string.h>

int count_char(FILE *f)
{
	int nombres_char = 0;
	while (fgetc(f)!= EOF)
	{
		nombres_char++;
	}
	return nombres_char;
}

void option_bytes(char *argv[],FILE *f)
{
	int c;
	int i = 0;
	int nombres = count_char(f) - atoi(argv[2]);
	rewind(f);
	while(1)
	{
		
		c = fgetc(f);
		if (i >= nombres)
		{
			printf("%c",c);
		}
		if(c == EOF)
			break;
		i++;
	}
}

void afficher_ligne(int ligneSauter,FILE *f)
{	
	char mot[552];
	int i = 0;
	while (fgets(mot, 500, f) != NULL)
	{
		i++;
	}
	rewind(f);
	int j = 0;
	while (fgets(mot, 500, f) != 0)
	{
		if (j > i - ligneSauter)
		{
			printf("%s", mot);
		}
		j++;
	}
}

void option_help(){
    printf("Utilisation : tail [OPTION]... [FICHIER]...\n");
    printf("Afficher les 10 dernieres lignes de chaque FICHIER sur la sortie standard.\n");
    printf("Avec plusieurs FICHIERs, ecrire un en-tête donnant le nom avant chaque fichier.\n");
    printf("Sans FICHIER ou quand FICHIER est -, afficher une demande.\n\n");
    printf("Les arguments disponible :\n");
    printf("-c, --bytes=[+]N ,-b        afficher les N derniers octets ; -c +N peut aussi\n");
    printf("                            être utilise pour afficher les octets a partir du\n");
    printf("                            Nieme de chaque fichier\n");
    printf(" -f, --follow[={name|descriptor}]\n");
    printf("                         afficher les donnees ajoutees au fur et a mesure\n");
    printf("                             que le fichier grandit ; sans argument, c’est\n");
    printf("                             equivalent a 'descriptor'\n");
    printf(" -F                       identique a --follow=name --retry\n");
    printf(" -n, --lines=[+]N         afficher les N dernieres lignes, au lieu des 10\n");

    printf("                             dernieres, -n +N pour afficher a partir de la Nieme\n");
    printf("-q, --quiet, --silent    ne jamais afficher l'en-tête donnant les noms\n");
    printf("                             de fichiers\n");
    printf(" -v, --verbose            afficher toujours les en-têtes des noms de fichier\n");
    printf("                             du saut de ligne\n");
    printf("     --help     afficher l'aide et quitter\n");
    printf("--version  afficher des informations de version et quitter\n\n");
    printf("Aide en ligne de GNU coreutils : <https://www.gnu.org/software/coreutils/>\n");
    printf("Signalez les problemes de traduction de « tail » a : <traduc@traduc.org>\n");
    printf("Documentation complete a : <https://www.gnu.org/software/coreutils/tail>\n");
    printf("ou disponible localement via: info '(coreutils) tail invocation'\n");
}

void test_error(FILE *f, char *argv)
{
	if (f == NULL)
	{
		printf("Erreur d'ouverture de fichier \n");
		printf("tail: impossible d'ouvrir %s en lecture: Aucun fichier ou dossier de ce type\n",argv);
		exit (-1);
	}
}

void option_follow(FILE *f)
{
	char phrase[555];
	rewind(f);
	afficher_ligne(11,f);

	while(1)
	{
		fgets(phrase, 555, f);
		fscanf(f,"%[^EOF]",phrase);
	}
}
void option_version()
{
	printf("tail (GNU coreutils) 8.32\n");
	printf("Copyright © 2024, Inc.\n");
	printf("License GPLv3+ : GNU GPL version 3 ou ultérieure <https://gnu.org/licenses/gpl.html>\n");
	printf("Ceci est un logiciel libre. Vous êtes libre de le modifier et de le redistribuer.\n");
	printf("Ce logiciel n'est accompagné d'ABSOLUMENT AUCUNE GARANTIE, dans les limites permises par la loi.\n");
	printf("\n");
	printf("Écrit par RAZAFITRIMO Tsifeherana Miranto, L1 MIT\n");
}
void options(char *argv[], int argc)
{
	FILE *f = NULL;
	f = fopen(argv[argc-1], "r+");
	test_error(f,argv[1]);
	//option --help
	if (strcmp(argv[1],"--help") == 0)
	{
		option_help();
		exit(1);
	}
	//option par défaut (sans paramètre)
	if (argc == 2)
	{
		afficher_ligne(11,f);
		exit(1);
	}
	
    int ligne_à_sauter = atoi(argv[2])+1;
	if (argc > 2)
	{
		//option -n
		if (strcmp(argv[1],"-n") == 0)
		{
			afficher_ligne(ligne_à_sauter,f);
		}
		//option -v (verbose)
		else if (strcmp(argv[1],"-v") == 0)
		{
			printf("==> %s <== \n", argv[argc-1]);
			afficher_ligne(11,f);
		}
		//option -f (follow)
		else if (strcmp(argv[1],"-f") == 0)
		{
			option_follow(f);
		}

		//option --bytes ou -f
		else if (strcmp(argv[1],"-c") == 0 || strcmp(argv[1],"--bytes") == 0)
		{	
			option_bytes(argv,f);
		}
		//option --version
		else if (argc == 2 && (strcmp(argv[1], "--version") == 0)) 
		{
			option_version();
		exit(0); // Exit proprement après avoir affiché la version
		}
		else 
		{
			printf("Veuillez consulter la page manuel de la commande tail avec l'option --help .\n");	
		}
	}
	else if (argc == 1)
	{
		printf("Veuillez consulter la page manuel de la commande tail avec l'option --help .\n");
	}
	
}
