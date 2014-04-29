package fr.jonesalexis.project.pdj;

import java.io.File;
import java.io.IOException;

import org.xml.sax.SAXException;

import fr.jonesalexis.project.pdj.httpserver.Server;
import fr.jonesalexis.project.pdj.xml.PizzaXMLReader;

public class Main {
	public static void main(String[] args) throws IOException {
		PizzaXMLReader pxr = new PizzaXMLReader();
		String db = "db" + File.separator + "pizzas.xml";
		String www = null;
		String port = null;

		for (int i = 0; i < args.length; i++) {
			if (args[i].equals("-w")) {
				if ((i + 1) < args.length) {
					www = args[i + 1];
					i++;
				} else {
					usage();
				}
			} else if (args[i].equals("-p")) {
				if ((i + 1) < args.length) {
					port = args[i + 1];
					i++;
				} else {
					usage();
				}
			} else if (args[i].equals("-db")) {
				if ((i + 1) < args.length) {
					db = args[i + 1];
					i++;
				} else {
					usage();
				}
			} else if (args[i].equals("-h")) {
				usage();
			}
		}

		try {
			pxr.parse(db);
		} catch (SAXException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		Server s = null;
		if ((www == null) && (port == null)) {
			usage();
			s = new Server(pxr.getLesPizzas());
		} else if (www == null) {
			try {
				s = new Server(Integer.parseInt(port), pxr.getLesPizzas());
			} catch (NumberFormatException e) {
				usage();
			}
		} else if (port == null) {
			s = new Server(www, pxr.getLesPizzas());
		} else {
			try {
				s = new Server(Integer.parseInt(port), www, pxr.getLesPizzas());
			} catch (NumberFormatException e) {
				usage();
			}
		}
	}

	public static void usage() {
		System.out.println("Utilisation de l'application :");
		System.out.println("java Main [Options]");
		System.out.println("Les options : ");
		System.out.println("-h affiche ce message");
		System.out.println("-p [port]\n\tPort par defaut : 1900");
		System.out.println("-w [dossier web]\n\tDossier web par defaut : www");
		System.out
				.println("-db [fichier BdD pizzas]\n\tDossier Base de Donnees des pizzas par defaut : db/pizzas.xml");
	}
}
