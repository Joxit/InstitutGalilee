(* http://lipn.univ-paris13.fr/~guerrini/cours/PF/2012-13/ *)
type value =
  | Vide
  | Comb of value * value;;

(* Q1 *)
let rec write_value = function
  | Vide -> Printf.printf "nil"
  | Comb (x,y) -> Printf.printf "("; write_value x ; Printf.printf " . " ; write_value y ; Printf.printf ")";;


write_value (Comb ((Comb (Vide, (Comb (Vide, Vide)))),(Comb ((Comb (Vide, Vide)), (Comb ((Comb (Vide, Vide)), Vide))))));;

(* Q2 *)
let rec eq_value v w = match (v, w) with
  | (Vide, Vide) -> true
  | (Comb (x1, y1), Comb (x2, y2)) -> if(eq_value x1 x2) then (eq_value y1 y2) else false
  | x -> false;;

 (* true *)
eq_value (Comb ((Comb (Vide, (Comb (Vide, Vide)))),(Comb ((Comb (Vide, Vide)), (Comb ((Comb (Vide, Vide)), Vide)))))) (Comb ((Comb (Vide, (Comb (Vide, Vide)))),(Comb ((Comb (Vide, Vide)), (Comb ((Comb (Vide, Vide)), Vide))))));;


 (* false *)
eq_value (Comb ((Comb (Vide, (Comb (Vide, Vide)))),(Comb ((Comb (Vide, Vide)), (Comb ((Comb (Vide, Vide)), Vide)))))) (Comb ((Comb (Vide, (Comb (Vide, Vide)))),(Comb ((Comb (Vide, Vide)), (Comb ((Comb (Vide, Vide)), Comb (Vide, Vide)))))));;

(* Q3 *)
let rec length = function
  | Vide -> 0
  | Comb (x, y) -> length y + 1;;

let rec depth = function
  | Vide -> 0
  | Comb (g, d) -> let lg = depth g and ld = depth d in if(lg > ld) then lg +1 else ld +1;;

depth (Comb (Comb (Vide, Vide), Comb (Vide, Comb (Comb( Comb (Vide, Vide), Vide), Comb (Vide, Vide)))));;

length (Comb (Comb (Vide, Vide), Comb (Vide, Comb (Comb( Comb (Vide, Vide), Vide), Comb (Vide, Vide)))));;

(* Q4 *)
exception Invalide_value of string;;

let hd = function
Vide -> raise (Invalide_value "hd a recu une valeur vide innattendue")
  | Comb (h,t) -> h;;

let tl = function
Vide -> raise (Invalide_value "tl a recu une valeur vide innattendue")
  | Comb (h,t) -> t;;


(* Q5 *)
let concat v1 v2 =
  let rec concat_rec = function
    | Vide -> v2
    | Comb (x, y) -> Comb (x, concat_rec y) in
  concat_rec v1;;

concat (Comb (Vide, Comb(Vide, Comb(Vide, Vide)))) (Comb (Vide, Comb(Vide, Comb(Vide, Comb(Vide, Vide)))));;

(* Q6 a tester *)
let rec flat = function
  | Vide -> Vide
  | Comb (Vide, y) -> Comb(Vide, flat y)
  | Comb (x, y) -> concat (flat x) (flat y);;

(* Q7 *)
exception Negative_int;;

let rec value_of_int x = if (x < 0) then raise (Negative_int) else if(x=0) then Vide else Comb(Vide, value_of_int (x-1));;

value_of_int (-1);;

(* Q8 *)
let mult x y =
  let rec mult_rec = function
    | Vide -> Vide
    | Comb (Vide, y2) -> concat x (mult_rec y2)
    | v -> failwith "la deuxieme entree n'etait pas un nombre"
  in mult_rec y;;

mult (value_of_int 5) (value_of_int 7);;

(* Q9 *)
let rec int_of_value = function
Vide -> 0
  | Comb(h, t) -> 1 + int_of_value t;;

int_of_value (mult (value_of_int 5) (value_of_int 7));;

(* 10 *)
let rec canon = function
Vide -> Vide
  | Comb (h, t) -> Comb (Vide, concat (canon t) (canon h));;

canon (Comb (Comb (Vide, Vide), Comb (Vide, Comb (Vide, Vide))));;

(* 11 faux *)
let mult x y = let x1 = canon x in
               let rec mult_rec = function
               Vide -> Vide
                 | Comb(h, t) -> concat x1 (mult_rec t) in
               mult_rec (canon y);;


(* ******************** PARTIE 2 ******************** *)
type var = string;;
type expr =
    Var of var           (* X *)
  | Data of value        (* d *)
  | Cons of expr * expr  (* cons E F *)
  | Head of expr         (* hd E *)
  | Tail of expr         (* tl E *)
  | Test of expr * expr;;(* =? E F *)
type command =
    Assign of var * expr (* X := E *)
  | Seq of command * command (* C ; D *)
  | While of expr * command  (* while E do {C} *);;
type program =
  { input : var; (* read X; *)
    body : command ; (* C; *)
    output : var };; (* write Y *)
type environnement = (var * value) list;;

exception Undef_var of var;;
let env_get (env:environnement) var =
  let rec env_rec = function
  [] -> raise (Undef_var var)
	| (x, y)::t -> if(x = var) then y else env_rec t in
  env_rec env;;

let env_set (env:environnement) var value =
  let rec env_rec = function
  [] -> ([(var, value)]:environnement)
    | (x, y)::t -> if(x = var) then (var, value)::t else env_rec env in
  env_rec env;;

let rec print_expr = function
Var x -> print_string x
  | Data d -> write_value d
  | Cons (e,f) ->  Printf.printf "cons ("; print_expr e; Printf.printf " "; print_expr f; Printf.printf ") "
  | Head e -> Printf.printf "hd "; print_expr e
  | Tail e -> Printf.printf "tl "; print_expr e
  | Test (e,f) ->  Printf.printf "=? ("; print_expr e; Printf.printf " "; print_expr f ; Printf.printf ") ";;

let rec print_comm = function
Assign (x, e) -> print_string x; Printf.printf " := "; print_expr e
  | Seq (c, d) -> print_comm c; Printf.printf " ; "; print_comm c
  | While (e, c) -> Printf.printf "while "; print_expr e; Printf.printf "{";print_comm c; Printf.printf "}";;

let rec print_prog = function
{input = i; body = b; output = o} -> print_string i; print_comm b; print_string o;;

(* Q4 *)
exception Empty_tree;;
let rec eval_expr env = function
Var x -> env_get env x
  | Data d -> d
  | Cons (e,f) -> Comb (eval_expr env e, eval_expr env f)
  | Head Data Vide -> raise Empty_tree
  | Head e -> hd (eval_expr env e)
  | Tail Data Vide -> raise Empty_tree
  | Tail e -> tl (eval_expr env e)
  | Test (e, f) -> if (eq_value (eval_expr env e) (eval_expr env f)) then Comb ( Vide, Vide) else Vide ;;

(* Q5 *)
exception Undef_var_in_expr of var * expr;;

let rec eval_com (env:environnement)  = function
Assign (var, expr) ->  env_set env var (eval_expr env expr)
  | Seq (c, d) -> eval_com (eval_com env c) d (* C ; D *)
  | While (expr, c) -> if(eval_expr env expr = Vide) then env else eval_com (eval_com env c) (While (expr, c));;  (* while E do {C} *)

let eval_prog value p = env_get (eval_com [(p.input, value)] p.body) p.output ;;
