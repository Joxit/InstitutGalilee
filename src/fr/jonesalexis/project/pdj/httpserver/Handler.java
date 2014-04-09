package fr.jonesalexis.project.pdj.httpserver;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.OutputStream;
import java.net.MalformedURLException;
import java.net.URL;
import java.net.URLConnection;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

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
		System.out.println("getHttpContext.getPath : " + exchange.getHttpContext().getPath());
		System.out.println("getRequestHeaders : " + exchange.getRequestHeaders());
		System.out.println("getRequestMethod : " + exchange.getRequestMethod());
		System.out.println("getProtocol : " + exchange.getProtocol());
		System.out.println("getLocalAddress : " + exchange.getLocalAddress());
		System.out.println("getRequestURI.getPath : " + exchange.getRequestURI().getPath());

	}

	private void sendExchange(HttpExchange exchange) {

		try {
			Headers reponseEntete = exchange.getResponseHeaders();
			OutputStream reponse = exchange.getResponseBody();
			String path = exchange.getRequestURI().getPath();
			if (path.endsWith("/")) {
				path += "index.html";
			}
			String type = getMIMEType(path);
			System.out.println("type : " + type);
			reponseEntete.set("Content-Type", type);
			exchange.sendResponseHeaders(200, 0);

			FileReader f = null;
			try {
				f = new FileReader(Server.getWebPath() + path);
				System.out.println("encoding : " + f.getEncoding());
			} catch (FileNotFoundException e) {
				System.out.println("404 File not Found : " + Server.getWebPath() + path);
				try {
					f = new FileReader(Server.getWebPath() + Server.getError404());
				} catch (FileNotFoundException e2) {
					System.out.println("404 File not Found : " + Server.getWebPath()
							+ Server.getError404());
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

}
