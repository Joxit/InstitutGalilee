import collection.mutable.HashMap, scala.collection.mutable.MutableList
/**
 * Je vais travailler sur des HashMap pour representer des anagrammes.
 * Le mot ou la phrase dont je vais vouloir un anagramme aura un HashMap[Char, Int]
 * ou le char est une lettre du mot/phrase et l'int son nombre d'occurrence dans celui ci
 *
 * @author Jones Magloire (11000369)
 */
object Main extends App {
	/* Activer la recher de tous les anagrammes (prend du temps) */
	val activerFoundAllWords = false

	/**
	 * On regarde si hm1 est inclu dans hm2, donc tous les élements de hm1 sont dans hm2 et en plus petit nombre
	 * en maths : hm1 C hm2
	 */
	def isIncluded(hm1: HashMap[Char, Int], hm2: HashMap[Char, Int]): Boolean = {
		return hm1.foldLeft(true) { case (res, (k, v)) => res && (v <= hm2.getOrElse(k, 0)) };
	}

	/**
	 * On supprime tous les elements qui sont dans hm2 de hm1
	 * en maths : hm1 \ hm2
	 */
	def divide(hm1: HashMap[Char, Int], hm2: HashMap[Char, Int]): HashMap[Char, Int] = {
		val res = HashMap[Char, Int]();
		hm1.foreach { entry => res += ((entry._1, (entry._2.-(hm2.getOrElse(entry._1, 0))))) }
		return res.filter { case (k, v) => v != 0 };
	}

	/**
	 * Renvoie le HashMap correspondant au mot.
	 * Pour chaque lettre du mot on lui associe son nombre d'occurrences dans ce mot
	 */
	def getHashMap(mot: String): HashMap[Char, Int] = {
		val res = HashMap[Char, Int]()
		mot.foreach { c => if (c isLetter) res += ((c, res.getOrElse(c, 0) + 1)) }
		return res;
	}

	/**
	 * Fait une somme sur les valeurs
	 */
	def getNbChar(hm: HashMap[Char, Int]): Int = {
		return hm.foldLeft(0) { case (res, (k, v)) => res + v }
	}

	// On initialise la liste qui aura les mots pour nos anagrammes.
	// La liste aura un couple (mot, HasMap du mot)
	var dummy = MutableList[(String, HashMap[Char, Int])]()
	// on ouvre le fichier ou il y a les mots
	val file = scala.io.Source.fromFile("anagrammes.txt")
	file.getLines().foreach { line =>
		dummy += ((line, getHashMap(line)));
	}
	file.close()

	/**
	 * Liste des anagrammes trie des plus longs mots aux plus courts. On prend les grands mots pour utiliser le plus de caracteres dès le début.
	 * Ceci augmente la rapidité de l'algorithme est simule une séparation en deux des ensembles. Cette valeure est utilise dans les algorithmes
	 */
	val lesAnagrammes = dummy.sortWith((_._1.length() > _._1.length()));

	/**
	 * Phrase ou l'on veut avoir un anagramme
	 */
	val phrase = "j'aime scala et le velo";
	val map = getHashMap(phrase)

	/**
	 * Etant donne un HashMap, on cherche un ensemble de mots qui pourrait faire un anagramme.
	 * On met en argument la phrase de base à chaque fois pour ne pas mettre de mot qui y sont deja, ce qui pimente un peu l'exercice
	 * On pourrait egalement ajouter un random quand on trouve un mot acceptable pour avoir des solutions différentes.
	 */
	def foundAWord(phrase: String, hm: HashMap[Char, Int]): String = {
		if (getNbChar(hm) == 0)
			return null;
		lesAnagrammes.foreach { entry =>
			val word = entry._1
			val wordHm = entry._2
			// On verifie que la phrase qu'on veut en anagramme ne contient pas deja le mot qu'on veut tester
			// Ensuite on verifie que le mot qu'on veut tester a bien toutes ses lettres dans notre HashMap actuelle
			if (!phrase.contains(word) && isIncluded(wordHm, hm)) {
				// On soustrait les lettres du mot qu'on vient de tester à notre HashMap
				val nextHm = divide(hm, wordHm)
				// Si le nombre de char est egale à 0, on a fini sinon on cherche un autre mot
				if (getNbChar(nextHm) <= 0) {
					return word
				} else {
					val res = foundAWord(phrase, nextHm)
					// Si on res == null c'est qu'on a pas trouvé de mot a cette étape, donc on teste avec le mot suivant de la liste
					if (res != null) {
						return word + " " + res
					}
				}
			}
		}
		return null;
	}

	var res = foundAWord(phrase, map)
	if (getHashMap(res).equals(map))
		println("Un resultat pour un anagramme de '" + phrase + "' est : '" + res + "'")
	else
		println("Une erreur s'est produite car " + res + " n'est pas un anagramme de " + phrase)

	/**
	 * Etant donne un HashMap, on cherche tous les ensembles de mots qui pourrait faire un anagramme.
	 * On met en argument la phrase de base à chaque fois pour ne pas mettre de mot qui y sont deja, ce qui pimente un peu l'exercice
	 * On met également la phrase finale pour l'afficher des qu'on trouve un anagramme
	 */
	def foundAllWords(phrase: String, hm: HashMap[Char, Int], phraseFinale: String) {
		if (getNbChar(hm) == 0)
			return ;
		lesAnagrammes.foreach { entry =>
			val word = entry._1
			val wordHm = entry._2
			// On verifie que la phrase qu'on veut en anagramme ne contient pas deja le mot qu'on veut tester
			// Ensuite on verifie que le mot qu'on veut tester a bien toutes ses lettres dans notre HashMap actuelle
			if (!phrase.contains(word) && isIncluded(wordHm, hm)) {
				// On soustrait les lettres du mot qu'on vient de tester à notre HashMap
				val nextHm = divide(hm, wordHm)
				// Si le nombre de char est egale à 0, on affiche sinon on cherche un autre mot pour completer
				if (getNbChar(nextHm) <= 0) {
					println(phraseFinale + " " + word)
				} else {
					foundAllWords(phrase, nextHm, phraseFinale + " " + word)
				}
			}
		}
	}

	/* Ce calcul met beaucoup de temps et affiche tous les anagrammes meme ceux avec les mots a des endroits différents */
	if (activerFoundAllWords)
		foundAllWords(phrase, map, "")
	else
		println("Pour activer la recherche de tous les anagrammes, mettez la valeur activerFoundAllWords a true")

}
