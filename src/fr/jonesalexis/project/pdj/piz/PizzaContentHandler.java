package fr.jonesalexis.project.pdj.piz;

import java.io.IOException;
import java.net.ContentHandler;
import java.net.URL;
import java.net.URLConnection;

public class PizzaContentHandler extends ContentHandler {

	@Override
	public Object getContent(URLConnection urlc) throws IOException {

		// DnsURLConnection url = urlc;
		URL url = urlc.getURL();
		String requete = url.getQuery();
		String queryValue;
		String resultValue;

		queryValue = url.getHost();

		switch (requete) {
			case "IPtoH":
				resultValue = requestIPtoH(queryValue);
				return new PizzaEntry(requete, queryValue, resultValue);
			case "HtoIP":
				resultValue = requestHtoIP(queryValue);
				return new PizzaEntry(requete, queryValue, resultValue);
			case "DtoMX":
				resultValue = requestDtoMX(queryValue);
				return new PizzaEntry(requete, queryValue, resultValue);
			default:
				return null;
		}
	}

	private String requestHtoIP(String queryValue) {
		String command = "dig +short " + queryValue;
		return executer(command);
	}

	private String requestIPtoH(String queryValue) {
		String command = "dig +short -x " + queryValue;
		return executer(command);
	}

	private String requestDtoMX(String queryValue) {
		String command = "dig +short -t " + queryValue;

		return executer(command);
	}

	private String executer(String command) {
		String res = "";
		try {
			Process p = Runtime.getRuntime().exec(command);
			int c;
			while ((c = p.getInputStream().read()) != -1) {
				res += (char) c;
			}
		} catch (IOException e) {
			e.printStackTrace();
		}
		return res;
	}
}
