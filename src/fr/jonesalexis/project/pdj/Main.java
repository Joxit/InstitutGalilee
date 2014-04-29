package fr.jonesalexis.project.pdj;

import java.io.File;
import java.io.IOException;
import java.net.URL;

import org.xml.sax.SAXException;

import fr.jonesalexis.project.pdj.httpserver.ServerHttp;
import fr.jonesalexis.project.pdj.proto.ServerPiz;
import fr.jonesalexis.project.pdj.xml.PizzaXMLReader;
import fr.jonesalexis.project.pdj.xml.TypeXMLReader;

public class Main {
	private String[] args;
	private String db = "db" + File.separator + "pizzas.xml";
	private String dt = "db" + File.separator + "types.xml";
	private String www = null;
	private String port = null;
	private PizzaXMLReader pxr = new PizzaXMLReader();
	private TypeXMLReader txr = new TypeXMLReader();

	public Main(String[] args) {
		this.args = args;
	}

	public static void main(String[] args) {
		Main m = new Main(args);
		m.start();
	}

	public void start() {
		System.getProperties().put("java.protocol.handler.pkgs",
				"fr.jonesalexis.project.pdj.proto");

		analyseArgs();
		parseXML();
		startHttpServer();
		startPizServer();

	}

	private void startPizServer() {
		ServerPiz s = new ServerPiz(2000);
		s.start();
	}

	private void parseXML() {
		try {
			System.out.println("Chargement de " + db);
			pxr.parse(db);
			System.out.println("Chargement de " + dt);
			txr.parse(dt);
		} catch (SAXException | IOException e) {
			e.printStackTrace();
		}
	}

	private void startHttpServer() {
		ServerHttp s = null;
		if ((www == null) && (port == null)) {
			s = new ServerHttp(pxr.getLesPizzas(), txr.getLesTypes());
		} else if (www == null) {
			try {
				s = new ServerHttp(Integer.parseInt(port), pxr.getLesPizzas(),
						txr.getLesTypes());
			} catch (NumberFormatException e) {
				usage();
			}
		} else if (port == null) {
			s = new ServerHttp(www, pxr.getLesPizzas(), txr.getLesTypes());
		} else {
			try {
				s = new ServerHttp(Integer.parseInt(port), www,
						pxr.getLesPizzas(), txr.getLesTypes());
			} catch (NumberFormatException e) {
				usage();
				s = null;
			}
		}
		if (s != null) {
			s.start();
		}
	}

	private void analyseArgs() {
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
	}

	private void usage() {
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
