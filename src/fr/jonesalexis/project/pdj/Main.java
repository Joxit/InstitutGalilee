package fr.jonesalexis.project.pdj;

import java.io.File;
import java.io.IOException;

import org.xml.sax.SAXException;

import fr.jonesalexis.project.pdj.httpserver.ServerHttp;
import fr.jonesalexis.project.pdj.proto.ServerPiz;
import fr.jonesalexis.project.pdj.xml.PizzaXMLReader;
import fr.jonesalexis.project.pdj.xml.TypeXMLReader;

/**
 * Classe contenant un main. Lance les serveurs HTTP et PIZ.
 * @author Jones Magloire
 * 
 */
public class Main {

	public static void main(String[] args) {
		Main m = new Main(args);
		m.start();
	}

	public static boolean debug = false;
	private final String[] args;
	private final String pizPort = "2000";
	private final PizzaXMLReader pxr = new PizzaXMLReader();
	private final TypeXMLReader txr = new TypeXMLReader();
	private String db = "db" + File.separator + "pizzas.xml";
	private String dt = "db" + File.separator + "types.xml";
	private String www = null;
	private String httpPort = null;

	public Main(String[] args) {
		this.args = args;
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
			} else if (args[i].equals("-ph")) {
				if ((i + 1) < args.length) {
					httpPort = args[i + 1];
					i++;
				} else {
					usage();
				}
			} else if (args[i].equals("-pp")) {
				if ((i + 1) < args.length) {
					httpPort = args[i + 1];
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
			} else if (args[i].equals("-debug")) {
				debug = true;
			}
		}
	}

	/**
	 * Parse les deux fichiers XML, la BD pizza et la BD types.
	 */
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

	/**
	 * Initialise le protocole piz, analyse les arguments, parse les XML et
	 * lance les serveurs.
	 */
	public void start() {
		System.getProperties()
				.put("java.protocol.handler.pkgs", "fr.jonesalexis.project.pdj.proto");

		analyseArgs();
		parseXML();
		startHttpServer();
		startPizServer();

	}

	private void startHttpServer() {
		ServerHttp s = null;
		if ((www == null) && (httpPort == null)) {
			s = new ServerHttp(pxr.getLesPizzas(), txr.getLesTypes());
		} else if (www == null) {
			try {
				s = new ServerHttp(Integer.parseInt(httpPort), pxr.getLesPizzas(),
						txr.getLesTypes());
			} catch (NumberFormatException e) {
				usage();
			}
		} else if (httpPort == null) {
			s = new ServerHttp(www, pxr.getLesPizzas(), txr.getLesTypes());
		} else {
			try {
				s = new ServerHttp(Integer.parseInt(httpPort), www, pxr.getLesPizzas(),
						txr.getLesTypes());
			} catch (NumberFormatException e) {
				usage();
				s = null;
			}
		}
		if (s != null) {
			s.start();
		}
	}

	private void startPizServer() {
		try {
			ServerPiz s = new ServerPiz(Integer.parseInt(pizPort), pxr.getLesPizzas(),
					txr.getLesTypes());
			s.start();
		} catch (NumberFormatException e) {
			usage();
		}
	}

	private void usage() {
		System.out.println("Utilisation de l'application :");
		System.out.println("java fr.jonesalexi.project.pdj.Main [Options]");
		System.out.println("Les options : ");
		System.out.println("-h affiche ce message");
		System.out
				.println("-ph [port]\n\tNumero de port pour le serveur de requetes http; par defaut : 1900");
		System.out
				.println("-pp [port]\n\tNumero de port pour le serveur de requetes piz; par defaut : 2000");
		System.out.println("-w [dossier web]\n\tDossier web; par defaut : www");
		System.out
				.println("-dp [fichier BdD pizzas]\n\tFichier Base de Donnees des pizzas; par defaut : db/pizzas.xml");
		System.out
				.println("-dt [fichier BdD types]\n\tFichier Base de Donnees des types; par defaut : db/types.xml");
		System.out.println("-debug\n\tAfficher des message pour le debug");
		System.exit(0);
	}
}
