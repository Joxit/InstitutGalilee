/**
 * Rempli par Magloire Jones
 */
object clavier extends App {
	/* dans les deux listes suivantes, chaque triplet représente
- le nom d'une touche clavier
- le caractère obtenu sur la touche à vide
- le caractère obtenu sur la touche lorsque Shift est enfoncé
 on ne représente pas l'action des autres modificateurs */

	/* cette liste représente le clavier français pc fr-latin1, fr-latin9 */
	// ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┲━━━━━━━━━┓
	// │ ³ ¸ │ 1 ̨  │ 2 É │ 3 ˘ │ 4 — │ 5 – │ 6 ‑ │ 7 È │ 8 ™ │ 9 Ç │ 0 À │ ° ≠ │ + ± ┃ ⌫ Retour┃
	// │ ² ¹ │ & ˇ │ é ~ │ " # │ ' { │ ( [ │ - | │ è ` │ _ \ │ ç ^ │ à @ │ ) ] │ = } ┃  arrière┃
	// ┢━━━━━┷━┱───┴─┬───┴─┬───┴─┬───┴─┬───┴─┬───┴─┬───┴─┬───┴─┬───┴─┬───┴─┬───┴─┬───┺━┳━━━━━━━┫
	// ┃       ┃ A Æ │ Z Â │ E ¢ │ R Ê │ T Þ │ Y Ÿ │ U Û │ I Î │ O Œ │ P Ô │ ¨ ˚ │ £ Ø ┃Entrée ┃
	// ┃Tab ↹  ┃ a æ │ z â │ e € │ r ê │ t þ │ y ÿ │ u û │ i î │ o œ │ p ô │ ^ ~ │ $ ø ┃   ⏎   ┃
	// ┣━━━━━━━┻┱────┴┬────┴┬────┴┬────┴┬────┴┬────┴┬────┴┬────┴┬────┴┬────┴┬────┴┬────┺┓      ┃
	// ┃        ┃ Q Ä │ S „ │ D Ë │ F ‚ │ G ¥ │ H Ð │ J Ü │ K Ï │ L Ŀ │ M Ö │ % Ù │ µ ̄  ┃      ┃
	// ┃Maj ⇬   ┃ q ä │ s ß │ d ë │ f ‘ │ g ’ │ h ð │ j ü │ k ï │ l ŀ │ m ö │ ù ' │ * ` ┃      ┃
	// ┣━━━━━━━┳┹────┬┴────┬┴────┬┴────┬┴────┬┴────┬┴────┬┴────┬┴────┬┴────┬┴────┲┷━━━━━┻━━━━━━┫
	// ┃       ┃ > ≥ │ W “ │ X ” │ C ® │ V ← │ B ↑ │ N → │ ? … │ . . │ / ∕ │ § − ┃             ┃
	// ┃Shift ⇧┃ < ≤ │ w « │ x » │ c © │ v ⍽ │ b ↓ │ n ¬ │ , ¿ │ ; × │ : ÷ │ ! ¡ ┃Shift ⇧      ┃
	// ┣━━━━━━━╋━━━━━┷━┳━━━┷━━━┱─┴─────┴─────┴─────┴─────┴─────┴───┲━┷━━━━━╈━━━━━┻━┳━━━━━━━┳━━━┛
	// ┃       ┃       ┃       ┃ ␣         Espace fine insécable ⍽ ┃       ┃       ┃       ┃
	// ┃Ctrl   ┃Meta   ┃Alt    ┃ ␣ Espace       Espace insécable ⍽ ┃AltGr ⇮┃Menu   ┃Ctrl   ┃
	// ┗━━━━━━━┻━━━━━━━┻━━━━━━━┹───────────────────────────────────┺━━━━━━━┻━━━━━━━┻━━━━━━━┛
	val fr_layout = List(
		("AE01", "&", "1"), // & 1 ˇ ̨
		("AE02", "é", "2"), // é 2
		("AE03", "\"", "3"), // " 3 # ˘
		("AE04", "\'", "4"), // ' 4 { — (tiret cadratin)
		("AE05", ")", "5"), // ( 5 [ – (tiret demi-cadratin)
		("AE06", "-", "6"), // - 6 | ‑ (tiret insécable)
		("AE07", "è", "7"), // è 7 ` È
		("AE08", "_", "8"), // _ 8 \ ™
		("AE09", "ç", "9"), // ç 9 ^ Ç
		("AE10", "à", "0"), // à 0 @ À
		("AE11", ")", "°"), // ) ° ] ≠
		("AE12", "=", "+"), // = + } ±

		// Second row
		("AD01", "a", "A"), // a A æ Æ
		("AD02", "z", "Z"), // z Z â Â
		("AD03", "e", "E"), // e E € ¢
		("AD04", "r", "R"), // r R ê Ê
		("AD05", "t", "T"), // t T þ Þ
		("AD06", "y", "Y"), // y Y ÿ Ÿ
		("AD07", "u", "U"), // u U û Û
		("AD08", "i", "I"), // i I î Î
		("AD09", "o", "O"), // o O œ Œ
		("AD10", "p", "P"), // p P ô Ô
		("AD11", "^", "¨"), // ^ ̈ ̃ ˚
		("AD12", "$", "£"), // $ £ ø Ø

		// Third row
		("AC01", "q", "Q"), // q Q ä Ä
		("AC02", "s", "S"), // s S ß „
		("AC03", "d", "D"), // d D ë Ë
		("AC04", "f", "F"), // f F ‘ ‚
		("AC05", "g", "G"), // g G ’ ¥
		("AC06", "h", "H"), // h H ð Ð
		("AC07", "j", "J"), // j J ü Ü
		("AC08", "k", "K"), // k K ï Ï
		("AC09", "l", "L"), // l L ŀ Ŀ
		("AC10", "m", "M"), // m M ö Ö
		("AC11", "ù", "%"), // ù % ' Ù
		("BKSL", "*", "µ"), // * µ ` ̄

		// Fourth row
		("LSGT", "<", ">"), // < > ≤ ≥
		("AB01", "w", "W"), // w W « “
		("AB02", "x", "X"), // x X » ”
		("AB03", "c", "C"), // c C © ®
		("AB04", "v", "V"), // v V ⍽ ← (espace fine insécable)
		("AB05", "b", "B"), // b B ↓ ↑
		("AB06", "n", "N"), // n N ¬ →
		("AB07", ",", "?"), // , ? ¿ …
		("AB08", ";", "."), // ; . × ⋅
		("AB09", ":", "/"), // : / ÷ ∕
		("AB10", "!", "§"), // ! § ¡ −
		// SPCE
		("SPCE", " ", " "))

	// Bépo layout (1.0rc2 version) for a pc105 keyboard (french) :
	// ┌────┐
	// │ S A│   S = Shift,  A = AltGr + Shift
	// │ s a│   s = normal, a = AltGr
	// └────┘
	//
	// ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┲━━━━━━━━━┓
	// │ # ¶ │ 1 „ │ 2 “ │ 3 ” │ 4 ≤ │ 5 ≥ │ 6   │ 7 ¬ │ 8 ¼ │ 9 ½ │ 0 ¾ │ ° ′ │ ` ″ ┃ ⌫ Retour┃
	// │ $ – │ " — │ « < │ » > │ ( [ │ ) ] │ @ ^ │ + ± │ - − │ / ÷ │ * × │ = ≠ │ % ‰ ┃  arrière┃
	// ┢━━━━━┷━┱───┴─┬───┴─┬───┴─┬───┴─┬───┴─┬───┴─┬───┴─┬───┴─┬───┴─┬───┴─┬───┴─┬───┺━┳━━━━━━━┫
	// ┃       ┃ B ¦ │ É ˝ │ P § │ O Œ │ È ` │ !   │ V   │ D Ð │ L   │ J Ĳ │ Z Ə │ W   ┃Entrée ┃
	// ┃Tab ↹  ┃ b | │ é ˊ │ p & │ o œ │ è ` │ ˆ ¡ │ v ˇ │ d ð │ l / │ j ĳ │ z ə │ w ̆ ┃   ⏎   ┃
	// ┣━━━━━━━┻┱────┴┬────┴┬────┴┬────┴┬────┴┬────┴┬────┴┬────┴┬────┴┬────┴┬────┴┬────┺┓      ┃
	// ┃        ┃ A Æ │ U Ù │ I ˙ │ E ¤ │ ; ̛ │ C ſ │ T Þ │ S ẞ  │ R ™ │ N   │ M º │ Ç , ┃      ┃
	// ┃Maj ⇬   ┃ a æ │ u ù │ i ̈  │ e € │ , ’ │ c © │ t þ │ s ß │ r ® │ n ˜ │ m ¯ │ ç ¸ ┃      ┃
	// ┣━━━━━━━┳┹────┬┴────┬┴────┬┴────┬┴────┬┴────┬┴────┬┴────┬┴────┬┴────┬┴────┲┷━━━━━┻━━━━━━┫
	// ┃       ┃ Ê   │ À   │ Y ‘ │ X ’ │ : · │ K   │ ? ̉  │ Q ̣  │ G   │ H ‡ │ F ª ┃             ┃
	// ┃Shift ⇧┃ ê / │ à \ │ y { │ x } │ . … │ k ~ │ ' ¿ │ q ˚ │ g µ │ h † │ f ˛ ┃Shift ⇧      ┃
	// ┣━━━━━━━╋━━━━━┷━┳━━━┷━━━┱─┴─────┴─────┴─────┴─────┴─────┴───┲━┷━━━━━╈━━━━━┻━┳━━━━━━━┳━━━┛
	// ┃       ┃       ┃       ┃ Espace inséc.   Espace inséc. fin ┃       ┃       ┃       ┃
	// ┃Ctrl   ┃Meta   ┃Alt    ┃ ␣ (Espace)      _               ␣ ┃AltGr ⇮┃Menu   ┃Ctrl   ┃
	// ┗━━━━━━━┻━━━━━━━┻━━━━━━━┹───────────────────────────────────┺━━━━━━━┻━━━━━━━┻━━━━━━━┛
	val bepo_layout = List(
		("AD01", "b", "B"), // b B | ¦
		("AD02", "é", "É"), // é É ˊ ˝
		("AD03", "p", "P"), // p P & §
		("AD04", "o", "O"), // o O œ Œ
		("AD05", "è", "È"), // è È ` `
		("AD06", "^", "!"), // ^ ! ¡
		("AD07", "v", "V"), // v V ˇ
		("AD08", "d", "D"), // d D ð Ð
		("AD09", "l", "L"), // l L /
		("AD10", "j", "J"), // j J ĳ Ĳ
		("AD11", "z", "Z"), // z Z ə Ə
		("AD12", "w", "W"), // w W ̆

		// Third row
		("AC01", "a", "A"), // a A æ Æ
		("AC02", "u", "U"), // u U ù Ù
		("AC03", "i", "I"), // i I ̈ ˙
		("AC04", "e", "E"), // e E € ¤
		("AC05", ",", ";"), // , ; ’ ̛
		("AC06", "c", "C"), // c C © ſ
		("AC07", "t", "T"), // t T þ Þ
		("AC08", "s", "S"), // s S ß ẞ
		("AC09", "r", "R"), // r R ® ™
		("AC10", "n", "N"), // n N ~
		("AC11", "m", "M"), // m M ̄ º
		("BKSL", "ç", "Ç"), // ç Ç ¸ ,

		// Fourth row
		("LSGT", "ê", "Ê"), // ê Ê /
		("AB01", "à", "À"), // à À \
		("AB02", "y", "Y"), // y Y { ‘
		("AB03", "x", "X"), // x X } ’
		("AB04", ".", ":"), // . : … ·
		("AB05", "k", "K"), // k K ~
		("AB06", "'", "?"), // ' ? ¿ ̉
		("AB07", "q", "Q"), // q Q ˚ ̣
		("AB08", "g", "G"), // g G µ
		("AB09", "h", "H"), // h H † ‡
		("AB10", "f", "F"), // f F ̨ ª
		// SPCE
		("SPCE", " ", " ") // ␣ (espace insécable) _ (espace insécable fin)
		)

	/* La liste suivante représente le coût musculaire de chaque touche
 * on considérera que :
 *  - activer la touche shift en même temps qu'une
 *    autre touche coûte 1.2 de plus que le coût de la touche;
 *  - taper sur entrée coûte 1.3.
 * Il s'agit d'un exercice, les valeurs sont totalement arbitraires.
 * Aucun doigt n'a été maltraité pour établir ces valeurs.
 */

	val cout = List(
		("AE01", 1.9),
		("AE02", 1.9),
		("AE03", 1.7),
		("AE04", 1.5),
		("AE05", 1.5),
		("AE06", 1.5),
		("AE07", 1.5),
		("AE08", 1.5),
		("AE09", 1.5),
		("AE10", 1.7),
		("AE11", 1.9),
		("AE12", 1.9),

		// Second row
		("AD01", 1.3),
		("AD02", 1.1),
		("AD03", 1.0),
		("AD04", 1.0),
		("AD05", 1.0),
		("AD06", 1.1),
		("AD07", 1.0),
		("AD08", 1.0),
		("AD09", 1.1),
		("AD10", 1.3),
		("AD11", 1.3),
		("AD12", 1.3),

		// Third row
		("AC01", 0.9),
		("AC02", 0.85),
		("AC03", 0.8),
		("AC04", 0.8),
		("AC05", 1.0),
		("AC06", 1.0),
		("AC07", 0.8),
		("AC08", 0.8),
		("AC09", 0.85),
		("AC10", 0.9),
		("AC11", 1.1),
		("BKSL", 1.2),

		// Fourth row
		("LSGT", 1.3),
		("AB01", 1.3),
		("AB02", 1.3),
		("AB03", 1.1),
		("AB04", 1.1),
		("AB05", 1.2),
		("AB06", 1.1),
		("AB07", 1.3),
		("AB08", 1.3),
		("AB09", 1.3),
		("AB10", 1.3),
		// SPCE
		("SPCE", 0.5))

	/* TODO Écrire une fonction qui prend en entrée un layout clavier et
   un texte et calcule et retourne une paire de flottants représentant:
    - le coût musculaire total du texte pour ce layout
    - la proportion de caractères non reconnus parmi tous les
      caractères */

	def coutTexte(layout: List[(String, String, String)], text: String): (Double, Double) = {
		val res = text.foldRight(0.0, 0.0) {
			case (c, (total, fail)) =>
				layout.find { // On cherche la touche correspondente au caractere
					case (_, normal, shift) =>
						normal == c.toString() || shift == c.toString()
				} match {
					case Some((nomTouche, _, shift)) =>
						cout.find { // Si la touche existe on cherche son cout
							touche => touche._1 == nomTouche
						} match {
							case Some((_, coutTouche)) => // Si son cout existe on l'ajoute en verifiant si c'etait un shift ou pas
								if (shift == c.toString()) // version shift
									((1.2 + coutTouche + total), fail)
								else // version normal
									(coutTouche + total, fail)
							case None => (total, fail + 1) // Sinon le cout de la touche inexistante
						}
					case None => // Si la touche n'existe pas, c'est peut etre entrer ou elle n'existe pas
						if (c == '\n') // version saut de ligne
							(total + 1.3, fail)
						else
							(total, fail + 1) // touche inexistante
				}
		}
		return (res._1, res._2 / text.length());
	}

	// Voila le cout du code que j'ai ecrit
	val code = "	def coutTexte(layout: List[(String, String, String)], text: String): (Double, Double) = {\n		val res = text.foldRight(0.0, 0.0) {\n			case (c, (total, fail)) =>\n" +
		"				layout.find { // On cherche la touche correspondente au caractere\n					case (_, normal, shift) =>\n" +
		"						normal == c.toString() || shift == c.toString()\n				} match {\n					case Some((nomTouche, _, shift)) =>\n" +
		"						cout.find { // Si la touche existe on cherche son cout\n							touche => touche._1 == nomTouche\n" +
		"						} match {\n							case Some((_, coutTouche)) => // Si son cout existe on l'ajoute en verifiant si c'etait un shift ou pas\n" +
		"								if (shift == c.toString()) // version shift\n									((1.2 + coutTouche + total), fail)\n" +
		"								else // version normal\n									(coutTouche + total, fail)\n" +
		"							case None => (total, fail + 1) // Sinon le cout de la touche inexistante\n						}\n" +
		"					case None => // Si la touche n'existe pas, c'est peut etre entrer ou elle n'existe pas\n						if (c == '\n') // version saut de ligne\n" +
		"							(total + 1.3, fail)\n						else\n							(total, fail + 1) // touche inexistante\n				}\n" +
		"		}\n		return (res._1, res._2 / text.length());\n	}"
	println("fr_layout : " + coutTexte(fr_layout, code));
	println("bepo_layout :" + coutTexte(bepo_layout, code));

	/* TODO Tester votre fonction sur des titres de flux RSS en anglais et
 * en français. */

}
