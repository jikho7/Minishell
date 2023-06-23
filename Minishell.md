# -   [**C**: _Tutorial - Write a Shell in C_](https://brennan.io/2015/01/16/write-a-shell-in-c/)
## Basic lifetime of a shell
- **Initialize ** : Lit et execute ses fichiers de configuration. Change le comportement du shell.
- **Interpret** : Ensuite, shell lit les commandes depuis stdin (qui peut aussi etre un fichier) puis les execute.
- **Terminate** : Apres l'execution des commandes, le shell execute les commandes d'arrets, freent la memoire et termine.

int main ()
{
	//initialize : load config files.
	// run command loop -> lsh_loop(); (loop n interpret commands)
	// shutdown n cleanup, free.
	return( EXIT_SUCCESS);
}

## La boucle shell
Pendant la boucle lsh_loop, le shell:
1.  lit les commandes depuis l entree standard. // lsh_read_line
2. analyse (parsing) : separe la chaine de commande en unb programme et des arguments. // lsh_split_line(line)
3. execution : lances les commandes analysees. // lsh_execute(args)
Le code de cette boucle imprime un prompt (>), appel une fonction qui lit la ligne entree dans le prompt, appel une autre fonction qui split cette ligne (pour recup les args) et une derniere qui execute ces args. 
Elle free la ligne et les args cree en amont. Une variable "statut" est utilisee pour savoir quand sortir de la boucle. Ca valeur est initilisee au debut de la boucle pour modifiee dans la dernier fonction appelee (celle qui exectute).

##### 1. Lire la ligne
La strat: Allouer un espace memoire, si cet espace est insuffisant pour recup la ligne entree par l user, realloquer.
``
```
char *buffer = malloc(sizeof(char) * bufsize); //allocation
...
    if (position >= bufsize) {  //ligne trop longue
      bufsize += LSH_RL_BUFSIZE;
      buffer = realloc(buffer, bufsize); // reallocation
```
Ne pas oublier de controler si l'allocation s est faite.
Une boucle "infinie" est utilisee. 'c' est un INT et non CHAR pour pouvoir etre comparer avec le EOF, INT.  buffer est une str \*char.
Si 'c' == '\\0' ou '\\n', on termine la string buffer avec un '\\0' et on le retourne. SInon, on ajoute le nouveau 'c' a la string buffer. 
Si la ligne entree dans stdin est plus longue que le buffer, on realloque.
check **getline(), stdio.h (fait bien ce taff). Mais tenter de faire sans.**

Si l'utilisateur tape ctrl + D, cela equivaut a un EOF.
La fonction lsh_read_line exit(EXIT_SUCCESS) si EOF atteint (soit le EOF d'un fichier, soit le CTRL + D de l'utilisateur). Exit(EXIT_FAILURE) si une erreur apparait, on echoue apres avoir imprimer l'erreur (perror).

##### 2. Parsing, analyse de la ligne
A cet instant, nous avons la ligne entree dans stdin. Il faut maintenant l'analysee (parsing) en liste d'arguments (' ', " ", <, >, | , / etc.).  Il faut tokeniser les arguements a l aides des differents separeteurs, comme des espaces. 
Une fonction lsh_split_line est cree. On lit la ligne, tokenize chaque mot separer par les delimiteurs et cree le double tableau (commandes + args), teminer ce double tableau par le '\\0. Ne pas oublier de realloquer le buffer si la ligne est trop longue (puis d'ajuste la taille du double tableau).
La technique du buffer pouvant s'etendre est appliquee autant pour le parsing que pour la lecture de la ligne (1ere etape).
strtok() est equivalant a un split, il renvoit un ptr et termine les tokens par '\\0' . Ces ptr sont sotckes dans un double tableau.  Ce tableau est realloque si necessaire. Quand strtok ne retourne plus de tokens, la liste de tokens est termine par '\\0' (derniere case du tableau).

##### 3.  Execution
La fontion principale d'un shell est d'executer des process. 2 types (init, le process du kernel) et les process fait avec fork(). 
-> voir **exec()** et ses variantes: remplace le programme en cours par un nouveau programme. Quand **exec** est appele, le système d’exploitation arrête le processus, charge le nouveau programme, et commence celui-ci à sa place. Un processus existant se divise en deux processus distincts. Ensuite, l’enfant utilise exec() pour se remplacer par un nouveau programme. Le processus parent peut continuer à faire d’autres choses, et il peut même garder un œil sur ses enfants, en utilisant le système call wait(). Utiliser perror avec exec() puis exit.
L'execution se composent de plusieurs fonctions. 
- Une pour le fork prenant en parametre la liste des args precedemment cree. Les enfants lancent les commandes donnee par l'utilisateur.  (lsh_launch)
- les builtins
- La fonction qui execute (lsh_execute).

###### Shell Builtins
Programmes constuits a l interieur meme du shell et pas propre aux process. 
Si on veut changer de répertoire, il faut utiliser la fonction chdir(). Le répertoire courant est une propriété d’un processus. Si on écrit un programme appelé cd qui change de répertoire, il change juste  son propre répertoire courant, puis se termine. Le répertoire actuel de son processus parent reste inchangé. Au lieu de cela, le processus shell lui-même doit exécuter chdir(), afin que son propre répertoire courant soit mis à jour. Les processus enfants  lances par la suite hériteront aussi de ce répertoire.
ex: exit, cd, help.

###### Assembler process et builtin
- Creer une fonction qui lancer un process ou un builtin. Controle si la commande est une builtin, si oui, elle l'excecute, sinon, elle appelle une autre fonction qui lance un process (lsh_launch, fork, et exec par un child).
- Attention si argv[0] == NULL (utilisateur entre un str vide ou juste des espaces) -> doit retourner 1.

## Notes : Library
-   `#include <sys/wait.h>`
    -   `waitpid()` and associated macros
-   `#include <unistd.h>`
    -   `chdir()`
    -   `fork()`
    -   `exec()`
    -   `pid_t`
-   `#include <stdlib.h>`
    -   `malloc()`
    -   `realloc()`
    -   `free()`
    -   `exit()`
    -   `execvp()`
    -   `EXIT_SUCCESS`, `EXIT_FAILURE`
-   `#include <stdio.h>`
    -   `fprintf()`
    -   `printf()`
    -   `stderr`
    -   `getchar()`
    -   `perror()`
-   `#include <string.h>`
    -   `strcmp()`
    -   `strtok()`

-> Check **man 3p** pour des infos sur les appels systeme.
-> Points manquant de ce resume :
-   Only whitespace separating arguments, no quoting or backslash escaping.
-   No piping or redirection.
-   Few standard builtins.
-   No globbing.

###### Autres details concerant de possibles erreurs futures:
- La page de manuel de getline() spécifie que le premier argument devrait être libre, donc la ligne devrait être initialisée à NULL dans mon implémentation lsh_read_line() qui utilise getline().

--------------------
# -   [**C**: _Let's build a shell!_](https://github.com/kamalmarhubi/shell-workshop)

### Appel systeme
Pour executer une commande rentree par un utilisateur, le noyau peut aider. Il est en charge de la plupart des choses liées aux processus, entre autres.

Les programmes parlent au noyau par le biais des appels système.
Exemples:
- ouverture de fichiers (open)
- lire et écrire pour eux (read, write)
- envoyer et recevoir des données sur le réseau. (sendto, recvfrom)
- programmes de démarrage (execve), execp est une fonction wrappe de execve.




















