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

(* 7/ Renvoyer une valeur au hasard pour le sexe et l'age *)
let random_sexe () = match (Random.int 2) with
  | 0 -> Masculin
  | _ -> Feminin;;

let random_age () = match (Random.int 3) with
  | 0 -> Bebe
  | 1 -> Enfant
  | _ -> Adulte;;

(* 8/ Transformer les valeurs en chaine de caractères *)
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
          if y = size_y  then []
          else (at_pos get_pos (x, y) list)::sort_y (y + 1)
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
  (* Quand on utilise la fonction en argument, on prend la valeur max en 
   * fonction de la position qu'on lui donne *)
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
  let equals ind1 ind2 = ind1.id = ind2.id
  let create () =
    last_id := !last_id + 1 ;
    {id = !last_id; age = random_age (); pos = P.random_pos ()}

  let get_pos ind = ind.pos
  let get_sexe ind = failwith "Il n'a pas de sexe"
  let get_age ind = ind.age
  let manger i ind = Some ind
  let bouger f ind = ind
  let reproduire nb_zherbs mere pere =
    let rec create_children n = match n with
      | 0 -> []
      | x ->
         let child = create ()
         and new_pos = match Random.int 100 with
           | x when x < 60 -> mere.pos
           | x when x < 70 -> P.ouest mere.pos
           | x when x < 80 -> P.est mere.pos
           | x when x < 90 -> P.nord mere.pos
           | _ ->  P.sud mere.pos
         in { child with
              age = Bebe;
              pos = new_pos}::create_children (x - 1)
    in if mere.age = Adulte && nb_zherbs > 0 then
         create_children (Random.int nb_zherbs)
       else 
         []

  let vieillir ind = match get_age ind with
    | Bebe -> Some {ind with age = Enfant}
    | Enfant -> Some {ind with age = Adulte}
    | Adulte -> None

  let afficher ind = 
    Printf.printf "[id=%d age=%s pos=" ind.id (string_age ind.age); 
    P.display (print_pos) ind.pos; print_string "]"
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
  let equals ind1 ind2 = ind1.id = ind2.id
  let create () =
    last_id := !last_id + 1;
    let rnd_age = random_age () in
    let age = 
      if rnd_age = Adulte then
        (rnd_age, (Random.int 4) + 1)  (* 1 a 4 tours adulte *)
      else
        (rnd_age, 1)
    in { id = !last_id ;
         sexe = random_sexe () ;
         age = age ;
         pos = P.random_pos () ;
         pv = krapit_pv_max }

  let get_pos ind = ind.pos
  let get_sexe ind = ind.sexe
  let get_age ind = fst ind.age
  let manger qte ind = 
    if qte > 0 then 
      if ind.pv <= krapit_pv_consum then 
        Some {ind with pv = krapit_pv_max}
      else  None (* On renvoie None quand on a rien mangé *)
    else if  ind.pv > krapit_pv_consum then 
      (* Si on a plus de pv que ce qu'on va perdre il survit *)
      Some {ind with  pv = ind.pv - krapit_pv_consum}
    else  None (* Sinon il meurt *)

  let bouger f ind = 
    if ind.pv > krapit_seuil_faim then
      ind (* Il n'a pas faim *)
    else
      let new_pos = 
        option_get (random_get [ P.ouest ind.pos;
                                 P.est ind.pos;
                                 P.nord ind.pos;
                                 P.sud ind.pos])
      in {ind with pos = new_pos}
           
  let reproduire dummy mere pere =
    let rec create_children n = 
      match n with
      | 0 -> []
      | x -> let child = create ()
             and new_pos =
               match Random.int 100 with 
               | x when x < 20 -> mere.pos
               | x when x < 40 -> P.ouest mere.pos
               | x when x < 60 -> P.est mere.pos
               | x when x < 80 -> P.nord mere.pos
               | _ -> P.sud mere.pos
             in { child with 
                  age = (Bebe, 1);
                  pos = new_pos}::create_children (x - 1)
    in if get_age mere = Adulte && get_age pere = Adulte then
         create_children ((Random.int 5) + 1)
       else
         []

  let vieillir ind = 
    if snd ind.age > 1 then 
      (* on reduit l'esperance de vie dans tous les cas *)
      Some {ind with age = (get_age ind, snd ind.age - 1)}
    else match get_age ind with
         | Bebe ->  Some {ind with age = (Enfant, 1)}
         | Enfant -> Some {ind with age = (Adulte, (Random.int 4) + 1)}
         | Adulte -> None

  let afficher ind = 
    Printf.printf "[id=%d sexe=%s age=(%s, %d) pv=%d pos="
                  ind.id (string_sexe ind.sexe)
                  (string_age (get_age ind)) (snd ind.age)
                  (ind.pv); 
    P.display (print_pos) ind.pos; print_string "]"
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
    last_id := !last_id + 1; 
    let rnd_age = random_age ()
    in let age = 
         if rnd_age = Adulte then
           (rnd_age, (Random.int 4) + 2)  (* 2 a 5 tours adulte *)
         else
           (rnd_age, 2)
       in { id = !last_id;
            sexe = random_sexe ();
            age = age;
            pos = P.random_pos ();
            pv = krogul_pv_max}

  let get_pos ind = ind.pos
  let get_sexe ind = ind.sexe
  let get_age ind = fst ind.age
  let manger qte ind = 
    if qte > 0  then
      begin
        if ind.pv <= krogul_seuil_faim then
          let pv =
            if ind.pv + (krogul_gain_faim * qte) > krogul_pv_max then
              krogul_pv_max
            else
              ind.pv + (krogul_gain_faim * qte)
          in Some {ind with pv = pv} (* le nombre de krapits manges *)
        else
          None (* On renvoie none quand on a rien mangé *)
      end
    else if ind.pv > krogul_pv_consum then 
      (* Si on a plus de pv que ce qu'on va perdre il survit *)
      Some {ind with  pv = ind.pv - krogul_pv_consum}
    else 
      (* Sinon il meurt *)
      None

  let bouger f ind =
    if ind.pv > krogul_affame then
      ind
    else
      (* On met uniquement 3 points cardinaux, le dernier sera notre base du fold *)
      let les_pos = [(f (P.ouest ind.pos), P.ouest ind.pos); 
                     (f (P.est ind.pos), P.est ind.pos);
                     (f (P.nord ind.pos), P.nord ind.pos);
                     (f (P.sud ind.pos), P.sud ind.pos)]
      and get_max (nour1, pos1) (nour2, pos2) = match nour2 with
        (* On cherche la zone avec le plus de nouriture *)
        | x when x < nour1 -> (nour1, pos1)
        (* En car d'egalité on prend l'un ou l'autre au hasard *)
        | x when x = nour1 && Random.int 100 < 50 -> (nour1, pos1)
        | _ -> (nour2, pos2)
      in let (_, new_pos) = List.fold_right get_max
           (List.tl les_pos) (List.hd les_pos)  
         in {ind with pos = new_pos}
         
  let reproduire dummy mere pere =
    let rec create_children n = match n with
      | 0 -> []
      | x ->
         let child = create () in
         let new_pos = match Random.int 100 with
           | x when x < 80 -> mere.pos
           | x when x < 85 -> P.ouest mere.pos
           | x when x < 90 -> P.est mere.pos
           | x when x < 95 -> P.nord mere.pos
           | _ -> P.sud mere.pos
         in {child with age = (Bebe, 2);
                        pos = new_pos}::create_children (x - 1)
    in if get_age mere == Adulte && get_age pere == Adulte then
         create_children (Random.int 3)
       else []

  let vieillir ind = 
    if snd ind.age > 1 then 
      (* on reduit l'esperance de vie dans tous les cas *)
      Some {ind with age = (get_age ind, snd ind.age - 1)}
    else match get_age ind with
         (* Sinon on change d'age *)
         | Bebe -> Some {ind with age = (Enfant, 2)}
         | Enfant -> Some {ind with age = (Adulte, (Random.int 4) + 2)}
         | Adulte -> None
                       
  let afficher ind =
    Printf.printf "[id=%d sexe=%s age=(%s, %d) pv=%d pos="
                  ind.id (string_sexe ind.sexe)
                  (string_age (get_age ind)) (snd ind.age)
                  (ind.pv) ; 
    P.display (print_pos) ind.pos ; print_string "]"
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

  let tuer_ind individu pop = 
    let is_alive ind = (Plante.equals individu ind) = false in
    List.filter is_alive pop 

  let vieillissement pop = clean_list (map Plante.vieillir pop)
  let reproduction pop =
    let adultes = (* on filtre les adultes *)
      List.filter (fun ind -> Plante.get_age ind = Adulte) pop in
    let get_enfants ind acc =
      let nb_zherb = ((List.length (sous_pop (Plante.get_pos ind) adultes)) - 1) 
      in acc@(Plante.reproduire nb_zherb ind ind)
    in reduce get_enfants adultes pop 

  let mouvement proies pop = pop (* Ils ne bougent pas *)
  let nourriture proies pop = (pop, proies) (* Ils ne mangent pas *)
  let affichage pop = iter (function ind -> Plante.afficher ind) pop
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

  let tuer_ind individu pop =
    let is_alive ind = (Bestiole.equals individu ind) = false in
    List.filter is_alive pop 

  let vieillissement pop = clean_list (map Bestiole.vieillir pop)

  let reproduction pop =
    let adultes = List.filter (fun ind -> Bestiole.get_age ind = Adulte) pop in
    let l_sorted = P.sort_by_pos Bestiole.get_pos adultes in
    let split = List.partition (fun ind -> Bestiole.get_sexe ind = Masculin) in
    let l_splited = map split l_sorted in
    let l_shuffled =  map (fun (m, f) -> (shuffle m, shuffle f)) l_splited in
    let rec reprod list = match list with 
      | ([], _) -> []
      | (_, []) -> []
      | (m::tlm, f::tlf) -> (Bestiole.reproduire 0 f m)@(reprod (tlm, tlf))
    in pop@(List.flatten (map reprod l_shuffled))

  let mouvement proies pop =
    let nb_proies pos =
      PROIES.reduce (fun ind -> fun x -> x + 1) (PROIES.sous_pop pos proies) 0
    in map (Bestiole.bouger (fun pos -> nb_proies pos)) pop

  let nourriture nourriture population =
    let manger ind (p, n) =
      let proie = 
        PROIES.random_ind (PROIES.sous_pop (Bestiole.get_pos ind) n) in
      if proie = None then
        ((Bestiole.manger 0 ind)::p, n)
      else
        begin 
          let bestiole = Bestiole.manger 1 ind in
          if bestiole = None then
            (* Si on a None ici, c'est que notre bestiole n'a pas mange *)
            (Some ind::p, n)
          else
            (bestiole::p, (PROIES.tuer_ind (option_get proie) n))
        end
    in let (pop, nour) = reduce manger population ([], nourriture) in
       (clean_list pop, nour)

  let affichage pop = iter (fun ind -> Bestiole.afficher ind) pop
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

