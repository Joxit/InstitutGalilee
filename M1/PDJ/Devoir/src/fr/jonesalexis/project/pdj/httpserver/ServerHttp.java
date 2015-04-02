package fr.jonesalexis.project.pdj.httpserver;

import java.io.IOException;
import java.net.InetSocketAddress;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.concurrent.Executors;

import com.sun.net.httpserver.HttpServer;

import fr.jonesalexis.project.pdj.Pizza;
import fr.jonesalexis.project.pdj.Server;

/**
 * Classe pour demarrer le serveur HTTP. Il connait que les requetes GET
 * @author Jones Magloire
 * 
 */
public class ServerHttp extends Server {
	final private static int _portDeflaut = 1900;
	final private static String _webPathDefault = "www/";
	private final int port;
	private static String webPath;
	private static String error404 = "404.html";

	public ServerHttp(ArrayList<Pizza> lesPizzas, HashMap<String, String> lesTypes) {
		this(_portDeflaut, _webPathDefault, lesPizzas, lesTypes);
	}

	public ServerHttp(int port, ArrayList<Pizza> lesPizzas, HashMap<String, String> lesTypes) {
		this(port, _webPathDefault, lesPizzas, lesTypes);
	}

	public ServerHttp(int port, String webPath, ArrayList<Pizza> lesPizzas,
			HashMap<String, String> types) {
		super(lesPizzas, types);
		this.port = port;
		ServerHttp.webPath = webPath;
	}

	public ServerHttp(String webPath, ArrayList<Pizza> lesPizzas, HashMap<String, String> lesTypes) {
		this(_portDeflaut, webPath + "/", lesPizzas, lesTypes);
	}

	/**
	 * @return chemin du fichier de l'erreur 404
	 */
	public static String getError404() {
		return error404;
	}

	/**
	 * @return chemin du dossier des pages web
	 */
	public static String getWebPath() {
		return webPath;
	}

	/**
	 * Le fichier doit etre dans le dossier www
	 * @param error404 chemin du fichier pour l'erreur 404
	 */
	public static void setError404(String error404) {
		ServerHttp.error404 = error404;
	}

	@Override
	public void start() {
		try {
			InetSocketAddress addr = new InetSocketAddress(port);
			HttpServer server;
			server = HttpServer.create(addr, 0);

			server.createContext("/", new Handler());
			server.setExecutor(Executors.newCachedThreadPool());
			server.start();
			System.out.println("Le serveur http en ecoute sur le port : " + addr.getPort());
			System.out.println("Le serveur http a comme dossier web : " + webPath);
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

}