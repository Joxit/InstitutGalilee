package fr.jonesalexis.project.pdj.proto;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.OutputStreamWriter;
import java.io.Reader;
import java.net.Socket;
import java.net.URL;
import java.security.DigestInputStream;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;

import fr.jonesalexis.project.pdj.proto.piz.PizzaEntry;

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
					System.out.println(content);
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
