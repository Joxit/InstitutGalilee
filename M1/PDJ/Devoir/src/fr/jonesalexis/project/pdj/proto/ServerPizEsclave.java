package fr.jonesalexis.project.pdj.proto;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStreamWriter;
import java.net.Socket;
import java.net.URL;

import fr.jonesalexis.project.pdj.Main;
import fr.jonesalexis.project.pdj.proto.piz.PizzaEntry;

/**
 * Thread esclave. Quand il est notifie par le serveur maitre, il traite la
 * commande des nouveaux clients
 * @author Jones Magloire
 * 
 */
public class ServerPizEsclave extends Thread {
	private final ServerPizMaitre server;

	public ServerPizEsclave(ServerPizMaitre server) {
		this.server = server;
	}

	@Override
	public void run() {
		Socket s = null;
		while (true) {
			if (s != null) {
				try {
					final InputStream is = s.getInputStream();
					String requete = "";
					int b;
					while ((b = is.read()) != -1) {
						if ((b == '\r') || (b == '\n')) {
							break;
						}
						requete += (char) b;
					}
					URL url = new URL(requete);
					PizzaEntry content = ((PizzaEntry) url.getContent());
					if (Main.debug) {
						System.out.println(content);
					}
					if (content != null) {
						final OutputStreamWriter os = new OutputStreamWriter(s.getOutputStream());
						os.write(content.getResultValue() + "\r\n");
						os.flush();
					}

				} catch (IOException e) {
					e.printStackTrace();
				}
				try {
					if (s != null) {
						s.close();
					}
					s = null;
				} catch (IOException e) {
					e.printStackTrace();
				}

			} else {
				try {
					s = server.getFirstIS();
					if (s == null) {
						synchronized (server) {
							server.wait();
						}
						s = server.getFirstIS();
					}
				} catch (InterruptedException e) {
					e.printStackTrace();
				}
			}
		}

	}
}
