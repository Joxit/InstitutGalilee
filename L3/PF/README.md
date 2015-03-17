# Projet - L3 Programmation Fonctionnelle (PF) - 2012/2013

## Objectif
Implémentation du langage While étudié dans le cours de Calculabilité.

## Types de données pour la représentation des programmes While
### Les valeurs
Les valeurs du langage **While** sont des arbres binaires non-étiquetées construits à partir d’un constructeur `Vide` correspondant à l'arbre vide et d’un constructeur binaire `Comb` qui combine deux arbres. On donne à chaque fois en commentaire le morceau de la grammaire du langage While qui correspond (cf cours de Calculabilité).

### Les expressions
Pour la représentation des expressions de While on d ́finie un type `expr` avec un constructeur pour chaque opérateur de base existant sur les données de While. Le type `var` est le type de la représentation des variables dans les expressions et les programmes. Dans la version très simple de l'interpréte qu’on réalisera, les variables seront toutes directement représentées par leur noms, c’est-à-dire une chaî de caractères 

###Les commandes et les programmes
La seule commande simple de While est l'affectation de la valeur d'une expression à une variable. À partir de cette commande de base on construit des commandes complexes par composition séquentielle (on exécute deux commandes l'une après l'autre) et par itération en utilisant la boucle while. Le type OCaml `command` sera utilisé pour la représentation des commandes.
Un programme While est une commande plus le choix d'une variable d'entrée et d'une variable de
sortie (type `program`).

## Fonctions de base
Q 1. Ecrire les fonctions qui calculent respectivement la tête et la queue d'une valeur de type value. Si l'argument est Vide, les fonctions lèvent une exception `Empty_tree`.
```Ocaml
hd : value -> value
tl : value -> value
```

 
Q 2. Ecrire une fonction qui vérifie si deux arbres du type value sont  égaux.

```Ocaml
eqvalue : value -> value -> bool
```
En `While`, les entiers sont représenté comme de listes de valeurs Vide : l'entier n étant une liste de de longueur `Vide`. Par exemple :
`0  ~> Vide`    `1 ~> (Vide . Vide)` `2 ~> (Vide . (Vide . Vide))` ...
 
Q 3. Ecrire une fonction qui renvoie l'arbre binaire correspondant a un entier positif (si l'argument est n ́gatif, la fonction lève une exception `Invalid_argument` avec un message qui contient la valeur incorrecte).
```Ocaml
while_int : int -> value
```

##Affichage de programmes While
Q 4. Ecrire une fonction qui affiche une valeur du langage While.
```Ocaml
print_value : value -> unit
```


Q 5. Ecrire une fonction qui affiche une expression du langage While.
```Ocaml
print_expr : expr -> unit
```


Q 6. Ecrire une fonction qui affiche une commande du langage While.
```Ocaml
print_comm : command -> unit
```


Q 7. Ecrire une fonction qui affiche un programme du langage While.
```Ocaml
print_prog : program -> unit
```


##L'interprète While
Pour l'exécution d'un programme il faut donner une valeur pour l'initialisation de la variable d'entrée. Le résultat sera la valeur de la variable de sortie après l'évaluation du programme.

Pour évaluer une commande, il faut avoir d'abord une fonction pour l'évaluation des expressions. Comme montré dans le cours sur les arbres, et notamment sur l'évaluation d'expresions arithmetiques, pour l'évaluation d'une expression qui contient des variables il faut avoir un environnement qui associe une valeur aux variables qu'on a le droit d'utiliser dans l'expression. L'environnement sera une liste d'association de type :
```Ocaml
type environnement = (var * value) list
```
On rappelle qu'une variable doit être initialisée avant d'être utilisée dans une expression.

Q 8. Ecrire une fonction qui évalue une expression du langage While dans un environnement donné.
```Ocaml
eval_expr : environnement -> expr -> value
```

La fonction lève les exceptions :

* exception Empty_tree, si on essaye de prendre un sous-élément d'un arbre vide ;
* exception Undef_var of var, si l'expression contient une variable qui n'est pas définie dans l'environnement ;

Q 9. Ecrire une fonction qui évalue une commande du langage While dans un environnement donné. Le résultat sera un nouvel environnement qui contient les modifications apport ́es par la commande évaluée.
```Ocaml 
eval_comm : environnement -> command -> environnement
``` 
La fonction lève l'exception exception 
```Ocaml 
Undef_var_in_expr of var*expr
``` 
si l'évaluation de la commande demande d'évaluer une expression qui contient une variable pas encore initialisée dans l'environnement courant.

Q 10. Écrire une fonction qui évalue un programme du langage While. Le premier paramètre de la fonction est la valeur de la
variable d'entrée.
```Ocaml 
eval_prog : value -> program -> value
``` 




