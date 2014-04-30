package fr.jonesalexis.project.pdj.xml;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.HashMap;

import fr.jonesalexis.project.pdj.Pizza;
import fr.jonesalexis.project.pdj.httpserver.ServerHttp;

/**
 * Lit une page HTML avec du contenue JAVA. Se comporte comme un FileReader.
 * Quand on commence, la classe lit tout le fichier pizzas.html, quand il a fini
 * il lit son buffer {@link #lesPizzas} qui contient du code HTML a afficher a
 * la suite du fichier pizzas.html. Le buffer peut etre different, soit il
 * contient toutes les pizzas soit il contient uniquement la description d'une
 * seule pizza.
 * @author Jones Magloire
 */
public class PizzaHTMLPrinter {
	private FileReader is;
	private final String htmlBegin = "pizzas.html";
	private final String htmlEnd = "pizzas_end.html";
	private int index;
	private final String lesPizzas;
	private HashMap<String, String> lesTypes;

	/**
	 * Initialise pour afficher toutes les pizzas dans une page HTML.
	 * @param pizzas a afficher
	 */
	public PizzaHTMLPrinter(ArrayList<Pizza> pizzas) {
		try {
			is = new FileReader(ServerHttp.getWebPath() + File.separator + htmlBegin);
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		}
		index = 0;
		lesPizzas = pizzaListHTMLCreator(pizzas);
	}

	/**
	 * Initialise pour afficher une unique pizza dans la page HTML
	 * @param pizza la pizza a afficher
	 * @param lesTypes
	 */
	public PizzaHTMLPrinter(Pizza pizza, HashMap<String, String> lesTypes) {
		try {
			is = new FileReader(ServerHttp.getWebPath() + File.separator + htmlBegin);
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		}
		index = 0;
		this.lesTypes = lesTypes;
		lesPizzas = pizzaInfoHTMLCreator(pizza);
	}

	/**
	 * @return prochain caractere du buffeur s'il n'est pas fini ou le prochain
	 *         caractere du fichier de fin si on vient de finir le buffeur ou -1
	 *         si erreur
	 */
	private int getPizzaHTML() {
		if (index < lesPizzas.length()) {
			int res = lesPizzas.charAt(index);
			index++;
			return res;
		} else {
			try {
				is = new FileReader(ServerHttp.getWebPath() + File.separator + htmlEnd);
				return is.read();
			} catch (IOException e) {
				e.printStackTrace();
			}
			return -1;
		}
	}

	/**
	 * @param p a afficher en HTML
	 * @return code HTML pour une pizza
	 */
	private String pizzaInfoHTMLCreator(Pizza p) {
		String res = "<h1>" + p.getNom() + " " + lesTypes.get(p.getType()) + " euros</h1></ br>";
		res += "<p>" + p.getDescription() + "</p></ br>";

		return res;
	}

	/**
	 * @param pizzas a afficher en HTML
	 * @return code HTML pour les pizzas
	 */
	private String pizzaListHTMLCreator(ArrayList<Pizza> pizzas) {
		String res = "<h1>Nos Pizzas</h1>";
		for (Pizza p : pizzas) {
			res += pizzaListHTMLCreator(p);
		}
		return res;
	}

	/**
	 * @param p a afficher en HTML avec un lien vers sa propre page
	 * @return code HTML de la pizza
	 */
	private String pizzaListHTMLCreator(Pizza p) {
		String res = "<a href=\"lespizzas/" + p.toLink() + "\"><h2>" + p.getNom() + "</h2></ br>";
		res += "<p>" + p.getDescription() + "</p></a></ br>";
		return res;
	}

	/**
	 * Lit les fichiers pizzas.html puis buffer puis pizzas_end.html
	 * @return prochain caractere ou -1 si fini
	 * @throws IOException
	 */
	public int read() throws IOException {
		if (is != null) {
			if (is.ready()) {
				return is.read();
			} else if (index == 0) {
				is.close();
				is = null;
				return getPizzaHTML();
			} else {
				return -1;
			}
		}
		return getPizzaHTML();
	}

	/**
	 * @return true s'il reste des caracteres a lire
	 */
	public boolean ready() {
		try {
			if (is != null) {
				return is.ready() || (index < lesPizzas.length());
			}
		} catch (IOException e) {
		}
		return index < lesPizzas.length();
	}

	@Override
	public String toString() {
		return "PizzaHTMLPrinter [is=" + is + ", htmlBegin=" + htmlBegin + ", htmlEnd=" + htmlEnd
				+ ", index=" + index + ", lesPizzas=" + lesPizzas + ", lesTypes=" + lesTypes + "]";
	}

}
