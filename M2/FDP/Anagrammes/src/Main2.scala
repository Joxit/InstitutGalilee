import collection.immutable._
import scala.annotation.{ tailrec, bridge }

class MultiSet[A] extends ListMap[A, Int] {

	def updated[B2 >: Int](key: A, value: Int): MultiSet[A] =
		new Node(key, value)

	override def size: Int = 0

	/**
	 * on ajouter le couple a celui qui existait
	 */
	def +(kv: (A, Int)): MultiSet[A] = { updated(kv._1, (super.getOrElse(kv._1, 0) + kv._2)) }

	/**
	 * on peut ajouter un element k
	 */
	def +(k: A): MultiSet[A] = { this.+((k, 1)) }

	/**
	 * par defaut on renvoie 0
	 */
	override def get(key: A): Option[Int] = Some(0)

	/**
	 * un simple - enleve un element k
	 */
	override def -(k: A) = {
		this.-(k, 1)
	}

	/**
	 * on enleve v elements k
	 */
	def -(k: A, v: Int) = {
		val newV = super.getOrElse(k, 0) - v
		if (newV == 1)
			super.-(k)
		else
			super.+((k, newV))
	}

	/**
	 * On regarde si notre ensemble est inferieur ou egale
	 */
	def <=(m: MultiSet[A]): Boolean = {
		this.keys.forall { c =>
			(get(c), m.get(c)) match {
				case (Some(x), Some(y)) => x <= y
				case (x, y) => false
			}
		}
	}

	/**
	 * On regarde si notre ensemble est inferieur strictement
	 */
	def <(m: MultiSet[A]): Boolean = {
		this.keys.forall { c =>
			(get(c), m.get(c)) match {
				case (Some(x), Some(y)) => x < y
				case (x, y) => false
			}
		}
	}

	/**
	 * supprimer plusieurs couples (pas obligé d'avoir un MultiSet ici)
	 */
	def --(m: Map[A, Int]): MultiSet[A] = { foldLeft(new MultiSet[A]()) { case (res, (k, v)) => res + ((k, v - m.getOrElse(k, 0))) } }

	override protected def key: A = throw new NoSuchElementException("empty map")
	override protected def value: Int = throw new NoSuchElementException("empty map")
	protected def next: MultiSet[A] = throw new NoSuchElementException("empty map")

	protected class Node[B1 >: Int](override protected val key: A,
			override protected val value: Int) extends MultiSet[A] {

		/**
		 * Is this an empty map?
		 *
		 *  @return true, iff the map is empty.
		 */
		override def isEmpty: Boolean = false

		/**
		 * size fait une somme sur les valeurs et pas sur le nombre d'elements
		 */
		override def size: Int = size0(this, 0)

		@tailrec private def size0(cur: MultiSet[A], acc: Int): Int = if (cur.isEmpty) acc else size0(cur.next, acc + cur.value)

		override def updated[B2 >: Int](k: A, v: Int): MultiSet[A] = {
			val m = this - k
			new m.Node(k, v)
		}

		/**
		 * Cette opération enleve simplement un élement k
		 */
		override def -(k: A): MultiSet[A] = {
			val newVal = getOrElse(k, 0) - 1
			if (newVal < 0)
				remove0(k, this, Nil)
			else
				updated(k, newVal)
		}

		/**
		 * on supprime v elements k
		 */
		override def -(k: A, v: Int): MultiSet[A] = {
			val newVal = getOrElse(k, 0) - v
			if (newVal < 0)
				remove0(k, this, Nil)
			else
				updated(k, newVal)
		}

		@tailrec private def remove0(k: A, cur: MultiSet[A], acc: List[MultiSet[A]]): MultiSet[A] =
			if (cur.isEmpty)
				acc.last
			else if (k == cur.key)
				(cur.next /: acc) {
					case (t, h) => val tt = t; new tt.Node(h.key, h.value) // SI-7459
				}
			else
				remove0(k, cur.next, cur :: acc)

		override def get(k: A): Option[Int] = get0(this, k)

		@tailrec private def get0(cur: MultiSet[A], k: A): Option[Int] =
			if (k == cur.key) Some(cur.value)
			else if (cur.next.nonEmpty) get0(cur.next, k) else Some(0)

		override protected def next: MultiSet[A] = MultiSet.this
	}
}

object Main2 extends App {
	def toMultiSet(map: Map[Char, Int]): MultiSet[Char] = {
		map.foldLeft(new MultiSet[Char]()) { case (res, (k, v)) => res.+((k, v)) }
	}

	def lettres(mot: String): MultiSet[Char] = {
		return toMultiSet(mot.filter { _ isLetter }.toLowerCase()
			.groupBy { c => c }.mapValues { _.length() })
	}

	val m1 = new MultiSet[Char]() + (('c', 3)) + (('a', 2)) + (('b', 1))
	val m2 = new MultiSet[Char]() + (('c', 1)) + (('a', 2)) + (('b', 1))

	lazy val lexique: Map[MultiSet[Char], List[String]] = {
		val source = scala.io.Source.fromFile("anagrammesutf.txt", "utf-8")
		val lignes = source.getLines().toList
		source.close()
		lignes.groupBy { (mot) => toMultiSet(lettres(mot)) }
	}

	def soluce2 = {
		val cible = lettres("vélo vélo")
		val lex = lexique.filterKeys(_ <= cible)
		val solutions = for {
			bag1 <- lex.keys.toStream
			bag2 = cible -- bag1
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
		val lex = lexique.filterKeys(_ <= cible)
		val solutions = for {
			bag1 <- lex.keys.toStream
			cible2 = cible -- bag1
			bag2 <- lex.filterKeys(_ <= cible2).keys.toStream
			bag3 = cible2 -- bag2
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
	/**
	 * On va stocker toutes les solutions ici
	 */
	var solutions = List[List[String]]()
	/**
	 * @param hm le multi ensemble contenant la phrase a regarder
	 * @param len initialement la taille de la phrase. On va limiter la longueur des mots
	 */
	def foundAllWord(hm: MultiSet[Char], len: Int): Unit = {
		if (hm.size == 0)
			return ;
		/* on ajoute la condition (ms.size <= len) pour forcer des réponses décroissantes ce qui limite les repetitions dans des ordres differents
		 * on aura toujours la repetition des melanges des mots de meme taille */
		val lex = lexique.filterKeys(ms => (ms <= hm) && (ms.size <= len))
		lex.keys.foreach(bag1 =>
			{
				if (!(bag1 <= hm))
					return ;
				val cible2 = hm -- bag1;
				if (cible2.size <= 0) {
					solutions = lex(bag1) :: solutions;
						def printAll(l: List[List[String]], acc: String): Unit = {
							l match {
								case Nil => println(acc)
								case hd :: tl =>
									hd.foreach { s => printAll(tl, acc + " " + s) }
							}
						}
					printAll(solutions, "")
					solutions = solutions.tail
				}
				solutions = lex(bag1) :: solutions;
				foundAllWord(cible2, bag1.size);
				solutions = solutions.tail

			})
	}

	println("la phrase a chercher est : j'aime scala et le vélo")
	val phrase = lettres("j'aime scala et le vélo")
	foundAllWord(phrase, phrase.size)
	//soluce2
	//soluce3

}
