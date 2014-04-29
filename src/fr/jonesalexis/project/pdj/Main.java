package fr.jonesalexis.project.pdj;

import java.io.File;
import java.io.IOException;

import org.xml.sax.SAXException;

import fr.jonesalexis.project.pdj.httpserver.Server;
import fr.jonesalexis.project.pdj.xml.PizzaXMLReader;
import fr.jonesalexis.project.pdj.xml.TypeXMLReader;

public class Main {
	public static void main(String[] args) throws IOException {
		PizzaXMLReader pxr = new PizzaXMLReader();
		TypeXMLReader txr = new TypeXMLReader();
		String db = "db" + File.separator + "pizzas.xml";
		String dt = "db" + File.separator + "types.xml";
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
			} else if (args[i].equals("-dp")) {
				if ((i + 1) < args.length) {
					db = args[i + 1];
					i++;
				} else {
					usage();
				}
			} else if (args[i].equals("-dt")) {
				if ((i + 1) < args.length) {
					dt = args[i + 1];
					i++;
				} else {
					usage();
				}
			} else if (args[i].equals("-h")) {
				usage();
				System.exit(0);
			}
		}

		try {
			System.out.println("Chargement de " + db);
			pxr.parse(db);
			System.out.println("Chargement de " + dt);
			txr.parse(dt);
		} catch (SAXException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		Server s = null;
		if ((www == null) && (port == null)) {
			s = new Server(pxr.getLesPizzas(), txr.getLesTypes());
		} else if (www == null) {
			try {
				s = new Server(Integer.parseInt(port), pxr.getLesPizzas(),
						txr.getLesTypes());
			} catch (NumberFormatException e) {
				usage();
			}
		} else if (port == null) {
			s = new Server(www, pxr.getLesPizzas(), txr.getLesTypes());
		} else {
			try {
				s = new Server(Integer.parseInt(port), www, pxr.getLesPizzas(),
						txr.getLesTypes());
			} catch (NumberFormatException e) {
				usage();
			}
		}
	}

	public static void usage() {
		System.out.println("Utilisation de l'application :");
		System.out.println("java fr.jonesalexi.project.pdj.Main [Options]");
		System.out.println("Les options : ");
		System.out.println("-h affiche ce message");
		System.out.println("-p [port]\n\tNumero de port; par defaut : 1900");
		System.out.println("-w [dossier web]\n\tDossier web; par defaut : www");
		System.out
				.println("-dp [fichier BdD pizzas]\n\tFichier Base de Donnees des pizzas; par defaut : db/pizzas.xml");
		System.out
				.println("-dt [fichier BdD types]\n\tFichier Base de Donnees des types; par defaut : db/types.xml");
	}
}
