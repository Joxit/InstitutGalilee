package fr.jonesalexis.project.pdj.xml;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStream;
import java.util.ArrayList;

import fr.jonesalexis.project.pdj.Pizza;

public class PizzaHTMLPrinter {
	private FileReader is;
	private int index;
	private final String lesPizzas;

	public PizzaHTMLPrinter(ArrayList<Pizza> pizzas) {
		try {
			is = new FileReader("www" + File.separator + "pizzas.html");
		} catch (FileNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		index = 0;
		lesPizzas = pizzaListHTMLCreator(pizzas);
		System.out.print(lesPizzas);
	}

	public PizzaHTMLPrinter(Pizza pizzas) {
		try {
			is = new FileReader("www" + File.separator + "pizzas.html");
		} catch (FileNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		index = 0;
		lesPizzas = pizzaInfoHTMLCreator(pizzas);
		System.out.print(lesPizzas);
	}

	private String pizzaInfoHTMLCreator(Pizza p) {
		String res = "<h1>" + p.getNom() + " " + p.getPrix() + " euros</h1></ br>";
		res += "<p>" + p.getDescription() + "</p></ br>";

		return res;
	}

	private String pizzaListHTMLCreator(ArrayList<Pizza> pizzas) {
		String res = "<h1>Nos Pizzas</h1>";
		for (Pizza p : pizzas) {
			res += pizzaListHTMLCreator(p);
		}
		return res;
	}

	private String pizzaListHTMLCreator(Pizza p) {
		String res = "<a href=\"lespizzas/" + p.toLink() + "\"><h2>" + p.getNom() + "</h2></ br>";
		res += "<p>" + p.getDescription() + "</p></a></ br>";
		return res;
	}

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

	public boolean ready() {
		try {
			if (is != null) {
				return is.ready() || (index < lesPizzas.length());
			}
		} catch (IOException e) {
		}
		return index < lesPizzas.length();
	}

	private int getPizzaHTML() {
		if (index < lesPizzas.length()) {
			int res = lesPizzas.charAt(index);
			index++;
			return res;
		} else {
			try {
				is = new FileReader("www" + File.separator + "pizzas_end.html");
				return is.read();
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			return -1;
		}
	}
}
