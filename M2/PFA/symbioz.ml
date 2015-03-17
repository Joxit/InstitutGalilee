(*******************************************************************************
 *                                                                             *
 * Devoir de Programmation Fonctionnelle Avancée                               *
 *         Projet : Symbioz                                                    *
 * Auteur Jones Magloire (11000369)                                            *
 *                                                                             *
 *******************************************************************************)

(*******************************************************************************
 *    5  Fonctions globales                                                    *
 *******************************************************************************)

(*************************** 5.1 Aléatoire, options ****************************)

(* Initialisation du générateur aléatoire *)
let _ = Random.self_init ();;


(********************************* 5.2 Listes **********************************)

(* 1/ Insert un élément à une position. Si la position est trop grande on 
 * l'insert a la fin de la liste. On commence à la position 0. *)
let rec insert_at_pos elt list pos = match list with
  | [] -> [elt]
  | hd::tl when pos = 0 -> elt::hd::tl
  | hd::tl -> hd::insert_at_pos elt tl (pos-1);;

(* 2/ Insert un élément à une position aléatoire. *)
let insert_at_random elt list = 
  insert_at_pos elt list (Random.int (List.length list));;

(* 3/ Melange une liste. *)
let rec shuffle list = match list with
  | hd::[] -> [hd]
  | hd::tl -> insert_at_random hd (shuffle tl)
  (* On le met en derniere position car on ne peut pas melanger une liste vide *)
  | [] -> [];;

(* 4/ Renvoie un élément aleatoire de la liste typé en 'a option *)
let random_get list = match list with
  | [] -> None
  | _ -> Some (List.nth list (Random.int (List.length list)));;

(* 5/ Renvoie la liste des éléments qui ne sont pas None *)
let rec clean_list list = match list with
  | [] -> []
  | None::tl -> clean_list tl
  | (Some hd)::tl -> hd::clean_list tl;;

(* Fonction annexe pour afficher une position *)
let print_pos x y = Printf.printf "(%d, %d)" x y;;

(* Fonction annexe pour recuperer la valeur d'une option *)
let option_get x = match x with
  | Some a -> a
  | None -> failwith "No value";;

(****************************** 5.3 Âge et sexe  *******************************)

(* 6/ Les types enumérés *)
type sexe = Masculin | Feminin;;

type age = Bebe | Enfant | Adulte;;

(* 7/ Renvoier une valeur au hasard pour le sexe et l'age *)
let random_sexe () = match (Random.int 2) with
  | 0 -> Masculin
  | _ -> Feminin;;

let random_age () = match (Random.int 3) with
  | 0 -> Bebe
  | 1 -> Enfant
  | _ -> Adulte;;

(* 8/ Transforme les valeurs en chaine de caractères *)
let string_sexe sexe = match sexe with
  | Masculin -> "Masculin"
  | Feminin -> "Feminin";;

let string_age age = match age with
  | Bebe -> "Bebe"
  | Enfant -> "Enfant"
  | Adulte -> "Adulte";;

(*******************************************************************************
 *    6  La planète Symbioz                                                    *
 *******************************************************************************)

(******************************** 6.1 Signature ********************************)

(* 9/ Signature de module PLANETE *)
module type PLANETE =
sig
  type pos
  val ouest : pos -> pos
  val est : pos -> pos
  val nord : pos -> pos
  val sud : pos -> pos
  val random_pos : unit -> pos
  val at_pos : ('a -> pos) -> pos -> 'a list -> 'a list
  val sort_by_pos : ('a -> pos) -> 'a list -> 'a list list
  val display : (int -> int -> unit) -> pos -> unit
  val clear : unit -> unit
end;;

(********************************** 6.2 Module *********************************)

(* 10/ Implementation du module Symbioz *)
let size_x = 3;;
let size_y = 3;;

module Symbioz:PLANETE =
struct
  type pos = int * int
  let ouest (x, y) = ((size_x + (x - 1)) mod size_x, y)
  let est (x, y) = ((x + 1) mod size_x, y)
  let nord (x, y) = (x, (y + 1) mod size_y)
  let sud (x, y) = (x, (size_y + (y - 1)) mod size_y)
  let random_pos () = (Random.int size_x, Random.int size_y)
  let rec at_pos get_pos pos list =
    List.filter (function elt -> (get_pos elt) = pos) list  

  let sort_by_pos get_pos list =
    let rec sort_x x =
      if x = size_x then
	[]
      else 
	let rec sort_y y =
	  if y = size_y  then
            []
	  else
            (at_pos get_pos (x, y) list)::sort_y (y + 1)
	in (sort_y 0)@(sort_x (x + 1))
    in sort_x 0

  let display f (x,y) = f x y
  let clear () = ()
end;;

(*******************************************************************************
 *    7  Génétique élémentaire                                                 *
 *******************************************************************************)

(********************************* 7.1 Signature *******************************)

(* 11/ Signature INDIVIDU *)
module type INDIVIDU =
sig
  type pos
  type individu
  type t = individu
  val last_id : int ref
  val equals : individu -> individu -> bool
  val create : unit -> individu
  val get_pos : individu -> pos
  val get_sexe : individu -> sexe
  val get_age : individu -> age
  (* On renvoie None quand on meurt ou quand on a pas faim *)
  val manger : int -> individu -> individu option
  val bouger : (pos -> int) -> individu -> individu
  val reproduire : int -> individu -> individu -> individu list
  val vieillir : individu -> individu option
  val afficher : individu -> unit
end;;

(* 12/ Signature MAKE_INDIVIDU *)
module type MAKE_INDIVIDU =
  functor (P:PLANETE) -> 
    INDIVIDU with type pos = P.pos;;

(********************************** 7.2 Zherbs *********************************)

(* 13/ Mudule Make_Zherb *)
module Make_Zherb:MAKE_INDIVIDU = 
  functor (P:PLANETE) ->
struct
  type pos = P.pos
  type individu = {id:int; age:age; pos:pos}
  type t = individu
  let last_id = ref 0
  let equals individu1 individu2 = individu1.id = individu2.id
  let create () =
    last_id := !last_id + 1 ;
    {id = !last_id; age = random_age (); pos = P.random_pos ()}

  let get_pos individu = individu.pos
  let get_sexe individu = failwith "Il n'a pas de sexe"
  let get_age individu = individu.age
  let manger i individu = Some individu
  let bouger f individu = individu
  let reproduire nb_zherbs mere pere =
    let rec create_children n = match n with
      | 0 -> []
      | x ->
	let rnd_case = Random.int 100
	in let child = create ()
	   in let new_pos =
		if rnd_case < 60 then
		  mere.pos
		else if rnd_case < 70 then
		  P.ouest mere.pos
		else if rnd_case < 80 then
		  P.est mere.pos
		else if rnd_case < 90 then
		  P.nord mere.pos
		else
		  P.sud mere.pos
              in {child with
		age = Bebe;
		pos = new_pos}::create_children (x - 1)
    in if mere.age = Adulte && nb_zherbs > 0 then
	create_children (Random.int nb_zherbs)
      else 
	[]

  let vieillir individu = 
    if get_age individu = Bebe then
      Some {individu with age = Enfant}
    else if get_age individu = Enfant then
      Some {individu with age = Adulte}
    else
      None

  let afficher individu = 
    Printf.printf "[id=%d age=%s pos="
      individu.id (string_age individu.age) ; 
    P.display 
      (print_pos) individu.pos;
    print_string "]"
end;;

(********************************** 7.3 Krapits ********************************)

(* 14/ Mudule Make_Krapit *)
let krapit_pv_max = 6;;
let krapit_pv_consum = 1;;
let krapit_seuil_faim = 3;;
module Make_Krapit:MAKE_INDIVIDU = 
  functor (P:PLANETE) ->
struct
  type pos = P.pos
  type individu = {id:int; sexe:sexe; age:(age * int); pos:pos; pv:int}
  type t = individu
  let last_id = ref 0
  let equals individu1 individu2 = individu1.id = individu2.id
  let create () =  last_id := !last_id + 1 ;
    let rnd_age = random_age ()
    in let age = 
     if rnd_age = Adulte then
       (rnd_age, (Random.int 4) + 1)  (* 1 a 4 tours adulte *)
     else
       (rnd_age, 1)
       in  {id = !last_id;
        sexe = random_sexe ();
            (* Comme l'age est aléatoire, on ne sait pas si il sera 
               adulte ou non, on initialise donc aussi le second champs *)
        age = age;
        pos = P.random_pos ();
        pv = krapit_pv_max}

  let get_pos individu = individu.pos
  let get_sexe individu = individu.sexe
  let get_age individu = fst individu.age
  let manger qte individu = 
    if qte > 0 then 
      if individu.pv <= krapit_pv_consum then 
	Some {individu with pv = krapit_pv_max}
      else
	None (* On renvoie None quand on a rien mangé *)
    else if  individu.pv > krapit_pv_consum then 
      (* Si on a plus de pv que ce qu'on va perdre il survit *)
      Some {individu with  pv = individu.pv - krapit_pv_consum}
    else 
      (* Sinon il meurt *)
      None

  let bouger f individu = 
    if individu.pv > krapit_seuil_faim then
      individu
    else
      let new_pos = 
	option_get (random_get [P.ouest individu.pos;
				P.est individu.pos;
				P.nord individu.pos;
				P.sud individu.pos])
      in {individu with pos = new_pos}
      
  let reproduire dummy mere pere =
    let rec create_children n = 
      match n with
      | 0 -> []
      | x -> let child = create ()
             in let new_pos =
		  match Random.int 100 with 
		  | x when x < 20 -> mere.pos
		  | x when x < 40 -> P.ouest mere.pos
		  | x when x < 60 -> P.est mere.pos
		  | x when x < 80 -> P.nord mere.pos
		  | _ -> P.sud mere.pos
		in {child with 
		  age = (Bebe, 1);
		  pos = new_pos}::create_children (x - 1)
    in if get_age mere = Adulte && get_age pere = Adulte then
	create_children ((Random.int 5) + 1)
      else
	[]

  let vieillir individu = 
    if snd individu.age > 1 then 
      (* on reduit l'esperance de vie dans tous les cas *)
      Some {individu with age = (get_age individu, snd individu.age - 1)}
    else if get_age individu = Bebe then 
      (* Sinon on change d'age *)
      Some {individu with age = (Enfant, 1)}
    else if get_age individu = Enfant then
      Some {individu with age = (Adulte, (Random.int 4) + 1)} (* entre 1 et 4 *)
    else
      None  
  let afficher individu = 
    Printf.printf "[id=%d sexe=%s age=(%s, %d) pv=%d pos="
      individu.id (string_sexe individu.sexe) (string_age (get_age individu))
      (snd individu.age) (individu.pv); 
    P.display 
      (print_pos) individu.pos;
    print_string "]"
end;;

(********************************** 7.4 Kroguls ********************************)

(* 15/ Mudule Make_Kroguls *)
let krogul_pv_max = 10;;
let krogul_pv_consum = 2;;
let krogul_seuil_faim = 6;;
let krogul_gain_faim = 5;;
let krogul_affame = 4;;
module Make_Krogul:MAKE_INDIVIDU = 
  functor (P:PLANETE) ->
struct
  type pos = P.pos
  type individu = {id:int; sexe:sexe; age:(age * int); pos:pos; pv:int}
  type t = individu

  let last_id = ref 0
  let equals individu1 individu2 = individu1.id = individu2.id
  let create () =  
    last_id := !last_id + 1 ; 
    let rnd_age = random_age ()
    in let age = 
     if rnd_age = Adulte then
       (rnd_age, (Random.int 4) + 2)  (* 2 a 5 tours adulte *)
     else
       (rnd_age, 2)
       in {id = !last_id;
       sexe = random_sexe ();
       age = age;
       pos = P.random_pos ();
       pv = krogul_pv_max}

  let get_pos individu = individu.pos
  let get_sexe individu = individu.sexe
  let get_age individu = fst individu.age
  let manger qte individu = 
    if qte > 0  then 
      if individu.pv <= krogul_seuil_faim then
	let pv =
	  if individu.pv + (krogul_gain_faim * qte) > krogul_pv_max then
            krogul_pv_max
	  else
            individu.pv + (krogul_gain_faim * qte)
	in Some {individu with pv = pv} (* le nombre de krapits manges *)
      else
	None (* On renvoie none quand on a rien mangé *)
    else if individu.pv > krogul_pv_consum then 
      (* Si on a plus de pv que ce qu'on va perdre il survit *)
      Some {individu with  pv = individu.pv - krogul_pv_consum}
    else 
      (* Sinon il meurt *)
      None

  let bouger f individu =
    if individu.pv > krogul_affame then
      individu
    else
      (* On met uniquement 3 points cardinaux, le dernier sera notre base du fold *)
      let lesPos = [(f (P.est individu.pos), P.est individu.pos);
		    (f (P.nord individu.pos), P.nord individu.pos);
		    (f (P.sud individu.pos), P.sud individu.pos)]
      in let (_, new_pos) = List.fold_right 
	   (function (nour, pos) -> 
             function (res_nour, res_pos) ->
               if res_nour < nour then
		 (* On cherche la zone avec le plus de nouriture *)
		 (nour, pos)
               else if res_nour = nour then
		 (* En car d'egalité on prend l'un ou l'autre au hasard *)
		 if Random.int 100 < 50 then 
		   (nour, pos)
		 else 
		   (res_nour, res_pos)
               else (res_nour, res_pos)
	   ) lesPos (f (P.ouest individu.pos), P.ouest individu.pos) 
	 in {individu with pos = new_pos}
	 
  let reproduire dummy mere pere =
    let rec create_children n = match n with
      | 0 -> []
      | x ->
    let rnd_case = Random.int 100
    in let child = create ()
       in let new_pos = 
        if rnd_case < 80 then
          mere.pos
        else if rnd_case < 85 then
          P.ouest mere.pos
        else if rnd_case < 90 then
          P.est mere.pos
        else if rnd_case < 95 then
          P.nord mere.pos
        else
          P.sud mere.pos
          in {child with age = (Bebe, 2);
            pos = new_pos}::create_children (x - 1)
    in if get_age mere == Adulte && get_age pere == Adulte then
	create_children (Random.int 3)
      else []

  let vieillir individu = 
    if snd individu.age > 1 then 
      (* on reduit l'esperance de vie dans tous les cas *)
      Some {individu with age = (get_age individu, snd individu.age - 1)}
    else if get_age individu = Bebe then 
      (* Sinon on change d'age *)
      Some {individu with age = (Enfant, 2)}
    else if get_age individu = Enfant then
      Some {individu with age = (Adulte, (Random.int 4) + 2)} (* 2 a 5 tours *)
    else (* Quand tout est faux il meurt *)
      None
  let afficher individu =
    Printf.printf "[id=%d sexe=%s age=(%s, %d) pv=%d pos="
      individu.id (string_sexe individu.sexe) (string_age (get_age individu)) 
      (snd individu.age) (individu.pv); 
    P.display 
      (print_pos) individu.pos;
    print_string "]"
end;;  

(*******************************************************************************
 *    8  Population                                                            *
 *******************************************************************************)

(******************************** 8.1 Signatures ******************************)

(* 16/ Signature POPULATION *)
module type POPULATION =
sig
  type pos
  type population
  type individu
  type nourriture
  type elt = individu
  type t = population
  val create : int -> population
  val random_ind : population ->  individu option
  val sous_pop : pos -> population -> population
  val tuer_ind : individu -> population -> population
  val map : ('a -> 'b) -> 'a list -> 'b list
  val iter : ('a -> unit) -> 'a list -> unit
  val reduce : (individu -> 'a -> 'a) -> population -> 'a -> 'a
  val vieillissement : population -> population
  val reproduction : population -> population
  val mouvement : nourriture -> population -> population
  val nourriture : nourriture -> population -> (population * nourriture)
  val affichage : population -> unit
end;;


(* 17/ Signature MAKE_PLANTES *)
module type MAKE_PLANTES = 
  functor (P:PLANETE) -> 
    functor (MI:MAKE_INDIVIDU) -> 
      POPULATION with type pos = P.pos
         and type nourriture = unit
         and type individu = MI(P).individu;;

(* 18/ Signature MAKE_ANIMAUX *)
module type MAKE_ANIMAUX = 
  functor (P:PLANETE) ->
    functor (PROIES:POPULATION with type pos = P.pos) -> 
      functor (MI:MAKE_INDIVIDU) -> 
    POPULATION with type pos = P.pos
           and type nourriture = PROIES.population
           and type individu = MI(P).individu;; 

(******************************** 8.2 Plantes *********************************)

(* 19/ Module Make_Zherbs *)
module Make_Zherbs:MAKE_PLANTES = 
  functor (P:PLANETE) ->
    functor (MI:MAKE_INDIVIDU) ->
struct 
  module Plante = MI(P)
  type pos = P.pos
  type individu = Plante.individu
  type population = individu list
  type nourriture = unit
  type elt = Plante.individu
  type t = population

  let map = List.map
  let iter = List.iter 
  let reduce = List.fold_right
  let rec create n = match n with
    | 0 -> []
    | x -> Plante.create ()::create (x-1)

  let random_ind = random_get
  let sous_pop = P.at_pos Plante.get_pos

  let tuer_ind individu population = 
    let is_alive ind  = (Plante.equals individu ind) = false
    in List.filter is_alive population 

  let vieillissement population = clean_list (map Plante.vieillir population)
  let reproduction population = 
    reduce (function ind -> function res -> 
      let adultes = (* on filtre les adultes de la position *)
        List.filter 
          (function ind2 -> Plante.get_age ind2 = Adulte) 
          (sous_pop (Plante.get_pos ind) population)
      in res@(Plante.reproduire ((List.length adultes) - 1) ind ind)
    ) population population 

  let mouvement nourriture population = population (* Ils ne bougent pas *)
  let nourriture nourriture population = (population, nourriture) (* Ils ne mangent pas *)
  let affichage population = 
    iter (function ind -> Plante.afficher ind) population
end;;

(* 20/ Module Zherbs *)
module Zherbs = Make_Zherbs (Symbioz) (Make_Zherb);;

(********************************* 8.3 Animaux ********************************)

(* 21/ Module Make_Bestioles *)
module Make_Bestioles:MAKE_ANIMAUX =
  functor (P:PLANETE) ->
    functor (PROIES:POPULATION with type pos = P.pos) ->
      functor (MI:MAKE_INDIVIDU) ->
struct 
  module Bestiole = MI(P)
  type pos = P.pos
  type individu = Bestiole.individu
  type population = individu list
  type nourriture = PROIES.population
  type elt = individu
  type t = population

  let map = List.map
  let iter = List.iter
  let reduce = List.fold_right
  let rec create n = match n with
    | 0 -> []
    | x -> Bestiole.create ():: create (x-1)
  let random_ind = random_get
  let sous_pop = P.at_pos Bestiole.get_pos 

  let tuer_ind individu population =
    let is_alive ind = (Bestiole.equals individu ind) = false 
    in List.filter is_alive population 

  let vieillissement population = clean_list (map Bestiole.vieillir population)

  let reproduction population =
    let adultes = 
      List.filter (function ind -> Bestiole.get_age ind = Adulte) population
    in let l_sorted = P.sort_by_pos Bestiole.get_pos adultes
       in let split = List.partition 
	    (function ind -> Bestiole.get_sexe ind = Masculin)  
	  in let l_splited = map split l_sorted
             in let l_shuffled =
		  map (function (m, f) -> 
		    (shuffle m, shuffle f)) l_splited
		in let rec reprod list = 
		     match list with 
		     | ([], _) -> []
		     | (_, []) -> []
		     | (m::tlm, f::tlf) -> 
		       (Bestiole.reproduire 0 f m)@(reprod (tlm, tlf))
		   in population@(List.flatten (map reprod l_shuffled))

  let mouvement nourriture population = 
    map 
      (Bestiole.bouger
	 (function pos -> PROIES.reduce (function ind -> function x -> x + 1) 
	   (PROIES.sous_pop pos nourriture) 0))
      population

  let nourriture nourriture population =
    let manger ind (p, n) =
      let proie = 
	PROIES.random_ind 
	  (PROIES.sous_pop (Bestiole.get_pos ind) n)
      in if proie = None then
	  ((Bestiole.manger 0 ind)::p, n)
	else
	  let bestiole = Bestiole.manger 1 ind 
	  in if bestiole = None then
              (* Si on a None ici, c'est que notre bestiole n'a pas mange *)
              (Some ind::p, n)
            else
              (bestiole::p, 
               (PROIES.tuer_ind (option_get proie) n))
    in let (pop, nour) = reduce manger population ([], nourriture)
       in (clean_list pop, nour)

  let affichage population = 
    iter (function ind -> Bestiole.afficher ind) population
end;;


(* 22/ Module Krapits et Kroguls *)
module Krapits = Make_Bestioles (Symbioz) (Zherbs) (Make_Krapit);;
module Kroguls = Make_Bestioles (Symbioz) (Krapits) (Make_Krogul);;

(*******************************************************************************
 *    9  Jeu Complet                                                           *
 *******************************************************************************)

(* 23/ Module Make_Game *)
module Make_Game =
  functor (P:PLANETE) ->
    functor (Plantes:POPULATION 
             with type pos = P.pos
             and type nourriture = unit) ->
      functor (Herbivores:POPULATION 
               with type pos = P.pos
               and type nourriture = Plantes.population) ->
	functor (Carnivores:POPULATION 
		 with type pos = P.pos
		 and type nourriture = Herbivores.population) ->
struct
  type env = 
    {p:Plantes.population; h:Herbivores.population; c:Carnivores.population}
      
  let create env = { p = Plantes.create 50; 
		     h = Herbivores.create 20; 
		     c = Carnivores.create 25 }

  let tour env = 
    print_string "\nPlantes\n";
    Plantes.affichage env.p;
    let (p, _) = Plantes.nourriture () env.p in 
    let p = Plantes.reproduction p in 
    let p = Plantes.mouvement () p in
    
    print_string "\nHerbivores\n";
    Herbivores.affichage env.h;
    let (h, p) = Herbivores.nourriture p env.h in
    let h = Herbivores.reproduction h in
    let h = Herbivores.mouvement p h; in
    
    print_string "\nCarnivores\n";
    Carnivores.affichage env.c;
    let (c, h) = Carnivores.nourriture h env.c in
    let c = Carnivores.reproduction c in
    let c = Carnivores.mouvement h c; in 
    
    let p = Plantes.vieillissement p in 
    let h = Herbivores.vieillissement h in 
    let c = Carnivores.vieillissement c in 
    {p = p; h = h; c = c}	
end;;

module Game = Make_Game (Symbioz) (Zherbs) (Krapits) (Kroguls);;

let env = Game.create ();;

let env = Game.tour env;;
let env = Game.tour env;;
let env = Game.tour env;;
let env = Game.tour env;;
let env = Game.tour env;;

