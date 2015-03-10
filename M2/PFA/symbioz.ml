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
  (* On le met en derniere position car on ne peut pas melanger *)
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


let print_pos x y = Printf.printf "(%d, %d)" x y;;

let option_get x = match x with
  | Some a -> a
  | None -> failwith "No value";;

(****************************** 5.3 Âge et sexe  *******************************)

(* 6/ Les types enumérés *)
type sexe =
    Masculin
  | Feminin;;

type age =
    Bebe
  | Enfant
  | Adulte;;

(* 7/ Renvoie une valeur au hasard *)
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
let size_x = 10;;
let size_y = 10;;
  
module Symbioz:PLANETE =
struct
  type pos = int * int
  let ouest (x, y) =
    let x2 =
      if x = 0 then
	(size_x - 1)
      else
	(x - 1)
    in (x2, y)
  let est (x, y) =
    let x2 =
      if (x + 1) = size_x then
	0
      else
	(x + 1)
    in (x2, y)
  let nord (x, y) =
    let y2 = 
      if y = 0 then
	(size_x - 1)
      else (y - 1)
    in (x, y2)
  let sud (x, y) =
    let y2 = 
      if (y + 1) = size_y then
	0
      else
	(y + 1)
    in (x, y2)
  let random_pos () = (Random.int size_x, Random.int size_y)
  let rec at_pos get_a_pos pos list = 
    begin 
      match list with
      | [] -> []
      | hd::tl -> let hd_pos = get_a_pos hd in
		  if (fst hd_pos) = (fst pos) && (snd hd_pos) = (snd pos)
		  then
		    hd::(at_pos get_a_pos pos tl)
		  else
		    at_pos get_a_pos pos tl
    end
  let sort_by_pos get_a_pos list =
    let rec sort_x x =
      if x = size_x then
	[]
      else 
	let rec sort_y y =
	  if y = size_y  then
	    []
	  else
	    (at_pos get_a_pos (x, y) list)::sort_y (y + 1)
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
  val manger : int -> individu -> individu option
  val bouger : (pos -> int) -> individu -> individu
  val reproduire : int -> individu -> individu -> individu list
  val vieillir : individu -> individu option
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
	   (rnd_age, 0)
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
      let rnd = Random.int 4
      in let new_pos =
	   if rnd = 0 then
	     P.ouest individu.pos
	   else if rnd = 1 then
	     P.est individu.pos
	   else if rnd = 2 then
	     P.nord individu.pos
	   else
	     P.sud individu.pos
	 in {individu with pos = new_pos}
  let reproduire dummy mere pere =
    let rec create_children n = 
      begin
      match n with
      | 0 -> []
      | x ->
	let rnd_case = Random.int 100
	in let child = create ()
	   in let new_pos =
		if rnd_case < 20 then
		  mere.pos
		else if rnd_case < 40 then
		  P.ouest mere.pos
		else if rnd_case < 60 then
		  P.est mere.pos
		else if rnd_case < 80 then
		  P.nord mere.pos
		else
		  P.sud mere.pos
	      in {child with 
		age = (Bebe, 0);
		pos = new_pos}::create_children (x - 1)
      end
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
      Some {individu with age = (Enfant, 0)}
    else if get_age individu = Enfant then
      Some {individu with age = (Adulte, (Random.int 4) + 1)} (* entre 1 et 4 *)
    else
      None
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
      if  individu.pv <= krogul_seuil_faim then
	let pv =
	  if individu.pv + (krogul_gain_faim * qte) > krogul_pv_max then
	    krogul_pv_max
	  else
	    individu.pv + (krogul_gain_faim * qte)
	in Some {individu with pv = pv} (* le nombre de krapits manges *)
      else
	None (* On renvoie none quand on a rien mangé *)
    else if  individu.pv > krogul_pv_consum then 
      (* Si on a plus de pv que ce qu'on va perdre il survit *)
      Some {individu with  pv = individu.pv - krogul_pv_consum}
    else 
      (* Sinon il meurt *)
      None
  let bouger f individu = 
    if individu.pv > krogul_affame then
      individu
    else
      let rnd = f individu.pos
      in let new_pos =
	   if rnd = 0 then
	     P.ouest individu.pos
	   else if rnd = 1 then
	     P.est individu.pos
	   else if rnd = 2 then
	     P.nord individu.pos
	   else
	     P.sud individu.pos
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
	      in {child with 
		age = (Bebe, 2);
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
end;;  

(*******************************************************************************
 *    8  Population                                                            *
 *******************************************************************************)

(********************************* 8.1 Signatures *******************************)

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
    functor (MI:INDIVIDU with type pos = P.pos) -> 
      POPULATION with type pos = P.pos
		 and type nourriture = unit;;

(* 18/ Signature MAKE_ANIMAUX *)
module type MAKE_ANIMAUX = 
  functor (P:PLANETE) ->
    functor (PROIES:POPULATION with type pos = P.pos) -> 
      functor (MI:INDIVIDU with type pos = P.pos) -> 
	POPULATION with type pos = P.pos
		   and type nourriture = PROIES.population;; 

(********************************* 8.2 Zherbs *********************************)

(* 19/ Module Make_Zherbs *)
module Make_Zherbs:MAKE_PLANTES = 
  functor (P:PLANETE) ->
    functor (MI:INDIVIDU with type pos = P.pos) ->
struct 
  type pos = P.pos
  type individu = MI.individu
  type population = individu list
  type nourriture = unit
  type elt = individu
  type t = population
  let map f list = List.map f list
  let iter f population = List.iter f population
  let reduce f population a = List.fold_right f population a
  let create n = map MI.create (Array.to_list (Array.make n ()))
  let random_ind  population = random_get population
  let sous_pop pos population = P.at_pos MI.get_pos pos population
  let tuer_ind individu population = 
    List.filter (function ind -> 
      ((MI.equals individu ind) = false)) population 
  let vieillissement population = clean_list (map MI.vieillir population)
  let reproduction population = 
    let rec reprod pop = 
      begin 
	match pop with
	| [] -> population
	| hd::tl -> 
	  let pop_pos = (* on filtre les adultes de la position *)
	    List.filter 
	      (function ind -> MI.get_age ind = Adulte) 
	      (sous_pop (MI.get_pos hd) population) 
	  in let enfants = 
	       (MI.reproduire ((List.length pop_pos) - 1) hd hd)
	     in enfants@(reprod tl)
      end
    in (reprod population)
  let mouvement nourriture population = population (* Ils ne bougent pas *)
  let nourriture nourriture population = (population, nourriture) (* Ils ne mangent pas *)
  let affichage population = 
    iter (function ind -> Printf.printf "[%s " (string_age (MI.get_age ind)) ;
      P.display 
	(function x -> function y -> Printf.printf "(%d, %d)" x y) 
	(MI.get_pos ind); 
      print_string "]") 
      population
end;;

(* 20/ Module Zherbs *)
module Zherbs = Make_Zherbs (Symbioz) (Make_Zherb (Symbioz));;

(********************************* 8.3 Animaux ********************************)


(* 21/ Module Make_Bestioles *)
module Make_Bestioles:MAKE_ANIMAUX =
  functor (P:PLANETE) ->
    functor (PROIES:POPULATION with type pos = P.pos) ->
      functor (MI:INDIVIDU with type pos = P.pos) ->
struct 
  type pos = P.pos
  type individu = MI.individu
  type population = individu list
  type nourriture = PROIES.population
  type elt = individu
  type t = population
  let map f list = List.map f list
  let iter f population = List.iter f population
  let reduce f population a = List.fold_right f population a
  let create n = map MI.create (Array.to_list (Array.make n ()))
  let random_ind population = random_get population
  let sous_pop pos population = P.at_pos MI.get_pos pos population
  let tuer_ind individu population = 
    List.filter (function ind -> ((MI.equals individu ind) = false)) population 
  let vieillissement population = clean_list (map MI.vieillir population)
  let reproduction population =
    let adultes = 
      List.filter (function ind -> MI.get_age ind = Adulte) population
    in let sorted = P.sort_by_pos MI.get_pos adultes
       in let rec split list = 
	    begin 
	      match list with 
	      | [] -> ([], [])
	      | hd::tl when MI.get_sexe hd = Masculin -> 
		let (m, f) = split tl 
		in (hd::m, f)
	      | hd::tl -> 
		let (m, f) = split tl 
		in (m, hd::f)
	    end
	  in let splited = map split sorted
	     in let shuffled = map (function (m, f) -> 
	       (shuffle m, shuffle f)) splited
		in let rec reprod list = 
		     begin 
		       match list with 
		       | ([], _) -> []
		       | (_, []) -> []
		       | (m::tlm, f::tlf) -> 
			 (MI.reproduire 0 f m)@(reprod (tlm, tlf))
		     end
		   in let enfants = map reprod shuffled
		      in let rec flatten list = 
			   begin 
			     match list with 
			     | [] -> []
			     | hd::tl -> hd@(flatten tl)
			   end
			 in population@(flatten enfants)
  let mouvement nourriture population = 
    map (MI.bouger (function pos -> 1)) population
  let nourriture nourriture  population = 
    let (pop, nour) = reduce 
      (function ind -> function (p, n) -> 
	let proie = 
	  PROIES.random_ind 
	    (PROIES.sous_pop (MI.get_pos ind) n)
	in if proie = None then
	    ((MI.manger 0 ind)::p, n)
	  else 
	    let bestiole = MI.manger 1 ind 
	    in if bestiole = None then 
		(Some ind::p, n)
	      else
		(bestiole::p, 
		 (PROIES.tuer_ind (option_get proie) n))
      ) 
      population ([], nourriture)
    in (clean_list pop, nour)
  let affichage population = 
    iter (function ind -> 
      Printf.printf "[%s %s " 
	(string_sexe (MI.get_sexe ind)) 
	(string_age (MI.get_age ind)) ; 
      P.display 
	(function x -> function y -> Printf.printf "(%d, %d)" x y) 
	(MI.get_pos ind);
      print_string "]") 
      population
end;;


(* 22/ Module Krapits et Kroguls *)
module Krapits = Make_Bestioles (Symbioz) (Zherbs) (Make_Krapit (Symbioz));;
module Kroguls = Make_Bestioles (Symbioz) (Krapits) (Make_Krogul (Symbioz));;

(*******************************************************************************
 *    9  Jeu Complet                                                           *
 *******************************************************************************)

(* 23/ Module Make_Game *)
module Make_Game =
  functor (P:PLANETE) ->
    functor (Plantes:POPULATION with type pos = P.pos
				and type nourriture = unit) ->
      functor (Herbivores:POPULATION with type pos = P.pos
				     and type nourriture = Plantes.population) ->
	functor (Carnivores:POPULATION with type pos = P.pos
				       and type nourriture = Herbivores.population) ->
struct
  let plantes = ref (Plantes.create 200)
  let herbivores = ref (Herbivores.create 100)
  let carnivores = ref (Carnivores.create 100)
  let tour () = 
    print_string "\nPlantes\n";
    Plantes.affichage !plantes;
    let (p, _) = Plantes.nourriture () !plantes 
    in plantes := p;
    plantes := Plantes.reproduction !plantes;
    plantes := Plantes.mouvement () !plantes;

    print_string "\nHerbivores\n";
    Herbivores.affichage !herbivores;
    let (p, n) = Herbivores.nourriture !plantes !herbivores 
    in herbivores := p;
    plantes := n;
    herbivores := Herbivores.reproduction !herbivores;
    herbivores := Herbivores.mouvement !plantes !herbivores;

    print_string "\nCarnivores\n";
    Carnivores.affichage !carnivores;
    let (p, n) = Carnivores.nourriture !herbivores !carnivores 
    in carnivores := p;
    herbivores := n;
    carnivores := Carnivores.reproduction !carnivores;
     carnivores := Carnivores.mouvement !herbivores !carnivores;

    plantes := Plantes.vieillissement !plantes;
    herbivores := Herbivores.vieillissement !herbivores;
    carnivores := Carnivores.vieillissement !carnivores

end;;
module Game = Make_Game (Symbioz) (Zherbs) (Krapits) (Kroguls);;



Game.tour ();;
Game.tour ();;
Game.tour ();;
Game.tour ();;
Game.tour ();;

