package fr.jonesalexis.project.pdj.httpserver;

import java.io.IOException;
import java.net.InetSocketAddress;
import java.util.concurrent.Executors;

import com.sun.net.httpserver.HttpServer;

public class Server {
	final private static int _portDeflaut = 1900;
	final private static String _webPathDefault = "www/";
	private static String webPath;
	private static String error404 = "404.html";

	public Server() {
		this(_portDeflaut, _webPathDefault);
	}

	public Server(String webPath) {
		this(_portDeflaut, webPath + "/");
	}

	public Server(int port) {
		this(port, _webPathDefault);
	}

	public Server(int port, String webPath) {
		try {
			InetSocketAddress addr = new InetSocketAddress(port);
			HttpServer server;
			server = HttpServer.create(addr, 0);

			server.createContext("/", new Handler());
			server.setExecutor(Executors.newCachedThreadPool());
			server.start();
			System.out.println("Le serveur en ecoute sur le port: "
					+ addr.getPort());
			System.out.println("Le serveur a comme dossier web : " + webPath);
		} catch (IOException e) {
			e.printStackTrace();
		}
		Server.webPath = webPath;
	}

	public static String getWebPath() {
		return webPath;
	}

	public static String getError404() {
		return error404;
	}

	public static void setError404(String error404) {
		Server.error404 = error404;
	}
}