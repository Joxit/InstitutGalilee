package fr.jonesalexis.project.pdj.proto;

import java.io.IOException;
import java.io.InputStream;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.ArrayList;

public class ServerPizMaitre extends Thread {
	private ArrayList<Socket> sockets;
	private ServerSocket serverSocket;

	public ServerPizMaitre(ServerSocket serverSocket) {
		this.serverSocket = serverSocket;
		sockets = new ArrayList<Socket>();
	}

	public void run() {
		while (true) {
			Socket socket = null;
			try {
				socket = serverSocket.accept();
				addIS(socket);
				synchronized (this) {
					notifyAll();
				}
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			} /*
			 * finally {
			 * 
			 * try { if (socket != null) { socket.close(); } } catch
			 * (IOException e) { System.out.println(e); } }
			 */
		}
	}

	public synchronized void addIS(Socket is) {
		sockets.add(is);
	}

	public synchronized void removeIS(Socket is) {
		sockets.remove(is);
	}

	public synchronized Socket getFirstIS() {
		if (!isEmptyIS()) {
			Socket is = sockets.get(0);
			sockets.remove(0);
			return is;
		}
		return null;
	}

	public synchronized boolean isEmptyIS() {
		return sockets.isEmpty();
	}
}
