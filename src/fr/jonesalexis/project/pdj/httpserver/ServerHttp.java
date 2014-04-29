package fr.jonesalexis.project.pdj.httpserver;

import java.io.IOException;
import java.net.InetSocketAddress;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.concurrent.Executors;

import com.sun.net.httpserver.HttpServer;

import fr.jonesalexis.project.pdj.Pizza;

public class ServerHttp {
	final private static int _portDeflaut = 1900;
	final private static String _webPathDefault = "www/";
	private final int port;
	private static String webPath;
	private static String error404 = "404.html";
	public static ArrayList<Pizza> lesPizzas;
	public static HashMap<String, String> lesTypes;

	public ServerHttp(ArrayList<Pizza> p, HashMap<String, String> lesTypes) {
		this(_portDeflaut, _webPathDefault, p, lesTypes);
	}

	public ServerHttp(String webPath, ArrayList<Pizza> p, HashMap<String, String> lesTypes) {
		this(_portDeflaut, webPath + "/", p, lesTypes);
	}

	public ServerHttp(int port, ArrayList<Pizza> p, HashMap<String, String> lesTypes) {
		this(port, _webPathDefault, p, lesTypes);
	}

	public ServerHttp(int port, String webPath, ArrayList<Pizza> p, HashMap<String, String> types) {
		lesPizzas = p;
		lesTypes = types;
		this.port = port;
		ServerHttp.webPath = webPath;
	}

	public void start() {
		try {
			InetSocketAddress addr = new InetSocketAddress(port);
			HttpServer server;
			server = HttpServer.create(addr, 0);

			server.createContext("/", new Handler());
			server.setExecutor(Executors.newCachedThreadPool());
			server.start();
			System.out.println("Le serveur en ecoute sur le port: " + addr.getPort());
			System.out.println("Le serveur a comme dossier web : " + webPath);
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

	public static String getWebPath() {
		return webPath;
	}

	public static String getError404() {
		return error404;
	}

	public static void setError404(String error404) {
		ServerHttp.error404 = error404;
	}

	public static Pizza getPizza(String link) {
		for (Pizza p : lesPizzas) {
			if (p.toLink().equals(link)) {
				return p;
			}
		}
		return null;
	}

	public static String getAllPizzaLink() {
		String res = "";
		for (Pizza p : lesPizzas) {
			res += p.toLink() + ";";
		}
		return res;
	}

	public static String getAllTypes() {
		String res = "";
		for (String s : lesTypes.keySet()) {
			res += s + ";";
		}
		return res;
	}

	public static String getAllPrices() {
		String res = "";
		for (String s : lesTypes.values()) {
			res += s + ";";
		}
		return res;
	}

}