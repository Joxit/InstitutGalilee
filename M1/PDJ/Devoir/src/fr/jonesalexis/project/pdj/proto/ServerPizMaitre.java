package fr.jonesalexis.project.pdj.proto;

import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.ArrayList;

/**
 * Thread du serveur maitre. Le serveur accepte les connexions, quand il en a
 * une nouvelle il l'ajoute a sa liste et notifie ses esclaves pour qu'ils
 * puissent traiter la demande.
 * @author Jones Magloire
 * 
 */
public class ServerPizMaitre extends Thread {
	private final ArrayList<Socket> sockets;
	private final ServerSocket serverSocket;

	public ServerPizMaitre(ServerSocket serverSocket) {
		this.serverSocket = serverSocket;
		sockets = new ArrayList<Socket>();
	}

	public synchronized void addIS(Socket is) {
		sockets.add(is);
	}

	public synchronized Socket getFirstIS() {
		if (!sockets.isEmpty()) {
			Socket is = sockets.get(0);
			sockets.remove(0);
			return is;
		}
		return null;
	}

	@Override
	public void run() {
		while (true) {
			Socket socket = null;
			try {
				socket = serverSocket.accept();
				addIS(socket);
				synchronized (this) {
					notify();
				}
			} catch (IOException e) {
				e.printStackTrace();
			}
		}
	}
}
