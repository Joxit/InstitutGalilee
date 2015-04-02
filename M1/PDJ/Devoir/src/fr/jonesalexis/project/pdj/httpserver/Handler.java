package fr.jonesalexis.project.pdj.httpserver;

import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.OutputStream;

import com.sun.net.httpserver.Headers;
import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;

import fr.jonesalexis.project.pdj.Main;
import fr.jonesalexis.project.pdj.Pizza;
import fr.jonesalexis.project.pdj.xml.PizzaHTMLPrinter;

/**
 * Classe pour gerer les requetes HTTP.
 * @author Jones Magloire
 */
public class Handler implements HttpHandler {

	public static String getMIMEType(String path) {
		if (path.endsWith(".css")) {
			return "text/css";
		} else if (path.endsWith(".html") || path.endsWith(".htm") || path.endsWith(".php")) {
			return "text/html";
		} else if (path.endsWith(".png")) {
			return "image/png";
		} else if (path.endsWith(".jpg")) {
			return "image/jpg";
		} else if (path.endsWith(".bmp")) {
			return "image/bmp";
		} else {
			return "text/html";
		}
	}

	@Override
	public void handle(HttpExchange exchange) throws IOException {
		String methodeRequete = exchange.getRequestMethod();
		if (methodeRequete.equalsIgnoreCase("GET")) {
			if (Main.debug) {
				printExchange(exchange);
			}
			sendExchange(exchange);
		}
	}

	private void printExchange(HttpExchange exchange) {
		System.out.println("getHttpContext.getPath : " + exchange.getHttpContext().getPath());
		System.out.println("getRequestHeaders : " + exchange.getRequestHeaders().values());
		System.out.println("getRequestMethod : " + exchange.getRequestMethod());
		System.out.println("getProtocol : " + exchange.getProtocol());
		System.out.println("getLocalAddress : " + exchange.getLocalAddress());
		System.out.println("getRequestURI.getPath : " + exchange.getRequestURI().getPath());

	}

	/**
	 * Renvoie la reponse de la requete
	 * @param exchange requete d'un client
	 */
	private void sendExchange(HttpExchange exchange) {

		try {
			Headers reponseEntete = exchange.getResponseHeaders();
			OutputStream reponse = exchange.getResponseBody();
			String path = exchange.getRequestURI().getPath();
			if (path.endsWith("/")) {
				path += "index.html";
			}
			String type = getMIMEType(path);
			if (Main.debug) {
				System.out.println("type : " + type);
			}
			reponseEntete.set("Content-Type", type);
			exchange.sendResponseHeaders(200, 0);

			/* On regarde si on est sur la page des pizzas */
			if (path.contains("lespizzas")) {
				String[] split = path.split("lespizzas/");
				PizzaHTMLPrinter php = null;
				if (split.length == 1) {
					php = new PizzaHTMLPrinter(ServerHttp.lesPizzas);
				} else {
					Pizza p = ServerHttp.getPizza(split[split.length - 1]);
					if (p != null) {
						php = new PizzaHTMLPrinter(p, ServerHttp.lesTypes);
					}
				}
				if (php != null) {
					while (php.ready()) {
						reponse.write(php.read());
					}
					reponse.flush();
					reponse.close();
					return;
				}
			}
			/* Si ce n'est pas la page des pizzas, c'est une page normale et on
			 * cherche le fichier correspondant a la demande */
			FileReader f = null;
			try {
				f = new FileReader(ServerHttp.getWebPath() + path);
				if (Main.debug) {
					System.out.println("encoding : " + f.getEncoding());
				}
			} catch (FileNotFoundException e) {
				System.out.println("404 File not Found : " + ServerHttp.getWebPath() + path);
				try {
					f = new FileReader(ServerHttp.getWebPath() + ServerHttp.getError404());
				} catch (FileNotFoundException e2) {
					System.out.println("404 File not Found : " + ServerHttp.getWebPath()
							+ ServerHttp.getError404());
				}
			}
			if (f != null) {
				while (f.ready()) {
					reponse.write(f.read());
				}
				reponse.flush();
			}
			reponse.close();
		} catch (IOException e) {

		}

	}

}
