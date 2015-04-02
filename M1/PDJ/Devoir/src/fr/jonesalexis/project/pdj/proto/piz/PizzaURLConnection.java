package fr.jonesalexis.project.pdj.proto.piz;

import java.io.IOException;
import java.io.InputStream;
import java.net.MalformedURLException;
import java.net.URL;
import java.net.URLConnection;

public class PizzaURLConnection extends URLConnection {

	public PizzaURLConnection(URL u) throws MalformedURLException {
		super(u);
	}

	@Override
	public void connect() throws IOException {
		// TODO Auto-generated method stub

	}

	@Override
	public String getHeaderField(String name) {
		if (name.equals("content-type")) {
			return "piz";
		}
		return null;
	}

	@Override
	public InputStream getInputStream() {
		return null;
	}

}
