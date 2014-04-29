package fr.jonesalexis.project.pdj.proto;

import java.io.IOException;
import java.net.ServerSocket;

public class ServerPiz {
	ServerSocket serverSocket = null;
	private final static int nbThreads = 2;

	public ServerPiz(int port) {
		try {
			serverSocket = new ServerSocket(port, 1);
		} catch (IOException e) {
			e.printStackTrace();
		}

	}

	public void start() {
		ServerPizMaitre spm = new ServerPizMaitre(serverSocket);
		for (int i = 0; i < nbThreads; i++) {
			ServerPizEsclave spe = new ServerPizEsclave(spm);
			Thread t = new Thread(spe);
			t.start();
		}
		Thread t = new Thread(spm);
		t.start();
		try {
			t.join();
		} catch (Exception e) {
			System.err.println(e);
		}
	}
}
