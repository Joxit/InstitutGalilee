package fr.jonesalexis.project.pdj;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStreamWriter;
import java.net.Socket;

public class ClientExample {

	public ClientExample(String url, int port) {

	}

	public static void sendRequest(String request, String addr, int port) {
		Socket socket = null;
		try {
			socket = new Socket(addr, port);
			final OutputStreamWriter os = new OutputStreamWriter(socket.getOutputStream());
			final InputStream is = socket.getInputStream();

			os.write(request);
			os.flush();
			int c;
			String reponse = "";
			while ((c = is.read()) != -1) {
				if ((c == '\r') || (c == '\n')) {
					break;
				}
				reponse += (char) c;
			}

			System.out.println(request + "\t" + reponse);

		} catch (IOException e) {
			e.printStackTrace();
		} finally {
			try {
				if (socket != null) {
					socket.close();
				}
			} catch (IOException e) {
				e.printStackTrace();
			}
		}

	}

	public static void main(String args[]) {
		sendRequest("piz://pizza?list\r\n", "127.0.0.1", 2000);
		sendRequest("piz://type?list\r\n", "127.0.0.1", 2000);
		sendRequest("piz://prix?list\r\n", "127.0.0.1", 2000);
		sendRequest("piz://Margherita?prix\r\n", "127.0.0.1", 2000);
		sendRequest("piz://Margherita?desc\r\n", "127.0.0.1", 2000);
	}
}
