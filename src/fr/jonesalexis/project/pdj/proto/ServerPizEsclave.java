package fr.jonesalexis.project.pdj.proto;

import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.net.Socket;
import java.net.URL;
import java.security.DigestInputStream;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;

public class ServerPizEsclave extends Thread {
	private ServerPizMaitre server;

	public ServerPizEsclave(ServerPizMaitre server) {
		this.server = server;
	}

	public void run() {
		Socket s = null;
		InputStream is = null;
		while (true) {
			if (s != null) {
				try {
					is = s.getInputStream();
					String requete = "";
					while (is.available() > 0) {
						requete += (char) is.read();
					}
					System.out.println(requete);
					URL url = new URL(requete);
					System.out.println(url.getContent());
				} catch (IOException e) {
					System.err.println(e);
				} finally {
					try {
						System.out.println(toString());
						is = null;
						s.close();
						s = null;
					} catch (IOException e) {
						e.printStackTrace();
					}
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
