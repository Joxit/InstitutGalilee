object sheet {
  println("Welcome to the Scala worksheet")       //> Welcome to the Scala worksheet
  3+4                                             //> res0: Int(7) = 7
  println("lol")                                  //> lol
	val x = {println("effet de bord") ; 2}    //> effet de bord
                                                  //| x  : Int = 2
   x                                              //> res1: Int = 2
	/* x = 3 imppossible car immutable */
 	var y = {println("effet de bord") ; 2}    //> effet de bord
                                                  //| y  : Int = 2
 	y = 3
 	y                                         //> res2: Int = 3
 	def z = {println("effet de bord") ; 2}    //> z: => Int
 	/* z = 3 impossible car immutable */
	// a chaque fois qu'on va demander z, on va executer le code entier comme une fonction
 	z                                         //> effet de bord
                                                  //| res3: Int = 2
                                                  
  {x
  y}                                              //> res4: Int = 3
  
  {x;
  y}                                              //> res5: Int = 3
  // c'est identique que le precedent
  {x
  +y
  }                                               //> res6: Int = 3
  
  // on fait l'addition ici
 (x+
  y)                                              //> res7: Int = 5
  
  if ({println("ha ha"); true; false}) {
  "toto"
  } else{
  "tata"
  }                                               //> ha ha
                                                  //| res8: String = tata
 if ({println("ha ha"); true; false}) {
  "toto"
  } else{
  3
  };                                              //> ha ha
                                                  //| res9: Any = 3
 	{
 		def f (x:Int, y:Int):Int = 3
 		var a =f(2, 3)
 	}
 	def f (g:(Int, Int) => Int, x: Int) = g(x, 2)
                                                  //> f: (g: (Int, Int) => Int, x: Int)Int
	// on juxtapose les arguments avec les ()
	def currification(g:Int=> Int)(x:Int)= g(x)
                                                  //> currification: (g: Int => Int)(x: Int)Int
	
	((x:Int) => x + 3)                        //> res10: Int => Int = <function1>

	def p:Int = p;                            //> p: => Int
	
	def somme (f:Int=>Int)(a:Int, b:Int):Int = (if(a < b) f(a) + somme(f)(a+1,b) else 0)
                                                  //> somme: (f: Int => Int)(a: Int, b: Int)Int
	somme((x:Int) => x * x)(1, 5)             //> res11: Int = 30
	
	def somme2 (f:Int=>Int, a:Int, b:Int):Int = Range(a,b)
							.map(f).fold(0)((x:Int, y:Int) => x +y)
                                                  //> somme2: (f: Int => Int, a: Int, b: Int)Int
 	somme2((x:Int) => x * x,1, 5)             //> res12: Int = 30
 	
 	var string = "lol"                        //> string  : String = lol
 	val list = scala.collection.mutable.MutableList[String]()
                                                  //> list  : scala.collection.mutable.MutableList[String] = MutableList()
 	var imlist = scala.collection.immutable.List[String]()
                                                  //> imlist  : List[String] = List()
	list += string                            //> res13: sheet.list.type = MutableList(lol)
	imlist = string::imlist
	imlist                                    //> res14: List[String] = List(lol)
	string = "xD"
	list                                      //> res15: scala.collection.mutable.MutableList[String] = MutableList(lol)
	imlist                                    //> res16: List[String] = List(lol)
	list += string                            //> res17: sheet.list.type = MutableList(lol, xD)
	imlist = string::imlist
	imlist                                    //> res18: List[String] = List(xD, lol)
	
	val xs = List (10,20,30,40,50,60)         //> xs  : List[Int] = List(10, 20, 30, 40, 50, 60)
	xs.take(4)                                //> res19: List[Int] = List(10, 20, 30, 40)
	
	val ys = Stream.from(2).map(n => {println("coucou " + n); 10 * n})
                                                  //> coucou 2
                                                  //| ys  : scala.collection.immutable.Stream[Int] = Stream(20, ?)
                                                  
	ys.take(5).toList                         //> coucou 3
                                                  //| coucou 4
                                                  //| coucou 5
                                                  //| coucou 6
                                                  //| res20: List[Int] = List(20, 30, 40, 50, 60)
	ys.take(2).toList                         //> res21: List[Int] = List(20, 30)

}