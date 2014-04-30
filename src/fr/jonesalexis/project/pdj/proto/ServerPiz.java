package fr.jonesalexis.project.pdj.proto;

import java.io.IOException;
import java.net.ServerSocket;
import java.net.URLConnection;
import java.util.ArrayList;
import java.util.HashMap;

import fr.jonesalexis.project.pdj.Pizza;
import fr.jonesalexis.project.pdj.Server;
import fr.jonesalexis.project.pdj.proto.piz.PizzaContentFactory;

/**
 * Classe pour demarrer le serveur PIZ. Les requetes qu'il connait sont :
 * piz://pizza?list piz://type?list piz://prix?list piz://[Lien pizza]?prix
 * piz://[nom pizza]?desc. Les requetes doivent toujours se terminier par \r\n
 * Il y a un nombre preci de Threads à lancer qu'on doit modifier ici.
 * @author Jones Magloire
 */
public class ServerPiz extends Server {
	private final int port;
	private final static int nbThreads = 5;

	public ServerPiz(int port, ArrayList<Pizza> p, HashMap<String, String> lesTypes) {
		super(p, lesTypes);
		this.port = port;
		URLConnection.setContentHandlerFactory(new PizzaContentFactory());

	}

	@Override
	public void start() {
		try {
			ServerSocket serverSocket = new ServerSocket(port, 1);
			ServerPizMaitre spm = new ServerPizMaitre(serverSocket);
			for (int i = 0; i < nbThreads; i++) {
				ServerPizEsclave spe = new ServerPizEsclave(spm);
				Thread t = new Thread(spe);
				t.start();
			}
			System.out.println("Le serveur Piz ecoute sur le port " + serverSocket.getLocalPort());
			Thread t = new Thread(spm);
			t.start();
			try {
				t.join();
			} catch (InterruptedException e) {
				System.err.println(e);
			}
		} catch (IOException e) {
			e.printStackTrace();
			System.exit(0);
		}

	}

}
