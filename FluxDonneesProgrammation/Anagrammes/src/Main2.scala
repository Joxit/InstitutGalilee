import collection.immutable._

class MultSet[A] extends ListMap[A, Int] {

	override def +[B1 >: Int](kv: (A, B1)) = { super.+((kv._1, ((super.getOrElse(kv._1, 0) + 1)))) }

	override def -(k: A) = {
		var v = super.getOrElse(k, 0);
		if (v == 1)
			super.-(k)
		else
			super.+((k, ((v - 1))))
	}
}

object Main2 extends App {

	def lettres(mot: String): Map[Char, Int] = {
		return mot.filter { _ isLetter }.toLowerCase()
			.groupBy { c => c }.mapValues { _.length() }
	}

	lazy val lexique: Map[Map[Char, Int], List[String]] = {
		val source = scala.io.Source.fromFile("anagrammesutf.txt", "utf-8")
		val lignes = source.getLines().toList
		source.close()
		lignes.groupBy { (mot) => lettres(mot) }
	}

	def inferieur(m: Map[Char, Int], n: Map[Char, Int]): Boolean = {
		m.keys.forall { c =>
			(m(c), n.get(c)) match {
				case (x, Some(y)) => x <= y
				case (_, None) => false
			}
		}
	}

	def soustraire(m: Map[Char, Int], n: Map[Char, Int]): Map[Char, Int] = {
		m.map { case (k, v) => (k, v - n.getOrElse(k, 0)) }
	}

	def soluce2 = {
		val cible = lettres("vélo vélo")
		val lex = lexique.filterKeys(inferieur(_, cible))
		val solutions = for {
			bag1 <- lex.keys.toStream
			bag2 = soustraire(cible, bag1)
			if lex contains bag2
		} yield (bag1, bag2)
		println("affichage des phrases de deux mots")
		for {
			(bag1, bag2) <- solutions
			mot1 <- lex(bag1)
			mot2 <- lex(bag2)
		} println(mot1 + " " + mot2)
	}

	def soluce3 = {
		val cible = lettres("vélo vélo")
		val lex = lexique.filterKeys(inferieur(_, cible))
		val solutions = for {
			bag1 <- lex.keys.toStream
			cible2 = soustraire(cible, bag1)
			bag2 <- lex.filterKeys(inferieur(_, cible2)).keys.toStream
			bag3 = soustraire(cible2, bag2)
			if lex contains bag3
		} yield (bag1, bag2, bag3)
		println("affichage des phrases de trois mots")
		for {
			(bag1, bag2, bag3) <- solutions
			mot1 <- lex(bag1)
			mot2 <- lex(bag2)
			mot3 <- lex(bag3)
		} println(mot1 + " " + mot2 + " " + mot3)

	}
	soluce2
	soluce3

}
