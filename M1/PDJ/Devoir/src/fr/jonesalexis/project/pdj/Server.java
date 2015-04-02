package fr.jonesalexis.project.pdj;

import java.util.ArrayList;
import java.util.HashMap;

/**
 * Classe abstraite des serveurs.
 * @author Jones Magloire
 */
public abstract class Server {
	public static ArrayList<Pizza> lesPizzas;
	public static HashMap<String, String> lesTypes;

	public Server(ArrayList<Pizza> lesPizzas, HashMap<String, String> lesTypes) {
		Server.lesPizzas = lesPizzas;
		Server.lesTypes = lesTypes;
	}

	/**
	 * @return tous les prix sous la forme prix1;prix2;prix3...
	 */
	public static String getAllPrices() {
		String res = "";
		for (String s : lesTypes.values()) {
			res += s + ";";
		}
		return res;
	}

	/**
	 * @return tous les types sous la forme type1;type2;type3...
	 */
	public static String getAllTypes() {
		String res = "";
		for (String s : lesTypes.keySet()) {
			res += s + ";";
		}
		return res;
	}

	/**
	 * @param link d'une pizza
	 * @return la pizza correspondant au link
	 */
	public static Pizza getPizza(String link) {
		for (Pizza p : lesPizzas) {
			if (p.toLink().equals(link)) {
				return p;
			}
		}
		return null;
	}

	/**
	 * Renvoie tous les liens des pizzas sous la forme link1;link2;link3...
	 * @return
	 */
	public static String getAllPizzaLink() {
		String res = "";
		for (Pizza p : lesPizzas) {
			res += p.toLink() + ";";
		}
		return res;
	}

	/**
	 * Demarre le serveur
	 */
	public abstract void start();
}
