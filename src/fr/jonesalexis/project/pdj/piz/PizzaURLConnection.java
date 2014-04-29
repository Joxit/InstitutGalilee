package fr.jonesalexis.project.pdj.piz;

import java.io.IOException;
import java.io.InputStream;
import java.net.MalformedURLException;
import java.net.URL;
import java.net.URLConnection;

public class PizzaURLConnection extends URLConnection {

	public PizzaURLConnection(URL u) throws MalformedURLException {
		super(u);
		setContentHandlerFactory(new PizzaContentFactory());
	}

	@Override
	public InputStream getInputStream() {
		return null;
	}

	@Override
	public String getHeaderField(String name) {
		if (name.equals("content-type")) {
			return "piz";
		}
		return null;
	}

	@Override
	public void connect() throws IOException {
		// TODO Auto-generated method stub

	}

}