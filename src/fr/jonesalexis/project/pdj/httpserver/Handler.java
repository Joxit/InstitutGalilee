package fr.jonesalexis.project.pdj.httpserver;

import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.OutputStream;
import com.sun.net.httpserver.Headers;
import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;

public class Handler implements HttpHandler {

	@Override
	public void handle(HttpExchange exchange) throws IOException {
		String methodeRequete = exchange.getRequestMethod();
		if (methodeRequete.equalsIgnoreCase("GET")) {
			printExchange(exchange);
			sendExchange(exchange);
		}
	}

	public void printExchange(HttpExchange exchange) {
		System.out.println("getHttpContext.getPath : "
				+ exchange.getHttpContext().getPath());
		System.out.println("getRequestHeaders : "
				+ exchange.getRequestHeaders());
		System.out.println("getRequestMethod : " + exchange.getRequestMethod());
		System.out.println("getProtocol : " + exchange.getProtocol());
		System.out.println("getLocalAddress : " + exchange.getLocalAddress());
		System.out.println("getRequestURI.getPath : "
				+ exchange.getRequestURI().getPath());

	}

	@SuppressWarnings("resource")
	private void sendExchange(HttpExchange exchange) {

		try {
			Headers reponseEntete = exchange.getResponseHeaders();
			reponseEntete.set("Content-Type", "text/html");
			exchange.sendResponseHeaders(200, 0);

			OutputStream reponse = exchange.getResponseBody();
			String path = exchange.getRequestURI().getPath();
			if (path.endsWith("/")) {
				path += "index.html";
			}
			FileReader f = null;
			try {
				f = new FileReader(Server.getWebPath() + path);
			} catch (FileNotFoundException e) {
				System.out.println("404 File not Found : "
						+ Server.getWebPath() + path);
				try {
					f = new FileReader(Server.getWebPath()
							+ Server.getError404());
				} catch (FileNotFoundException e2) {
					System.out.println("404 File not Found : "
							+ Server.getWebPath() + Server.getError404());
				}
			}
			if (f != null) {
				while (f.ready()) {
					reponse.write(f.read());
				}
			}
			reponse.close();
		} catch (IOException e) {

		}

	}
}
