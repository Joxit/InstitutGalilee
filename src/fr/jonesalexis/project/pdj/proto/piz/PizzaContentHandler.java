package fr.jonesalexis.project.pdj.proto.piz;

import java.io.IOException;
import java.net.ContentHandler;
import java.net.URL;
import java.net.URLConnection;

import fr.jonesalexis.project.pdj.httpserver.ServerHttp;

public class PizzaContentHandler extends ContentHandler {

	@Override
	public Object getContent(URLConnection urlc) throws IOException {
		URL url = urlc.getURL();
		String requete = url.getQuery();
		String queryValue;
		String resultValue;

		queryValue = url.getHost();

		switch (requete) {
			case "desc":
				resultValue = ServerHttp.getPizza(queryValue).getDescription();
				return new PizzaEntry(requete, queryValue, resultValue);
			case "list":
				resultValue = "pizza/type/prix";
				if (queryValue.equals("pizza")) {
					resultValue = ServerHttp.getAllPizzaLink();
				} else if (queryValue.equals("type")) {
					resultValue = ServerHttp.getAllTypes();
				} else if (queryValue.equals("prix")) {
					resultValue = ServerHttp.getAllPrices();
				}
				return new PizzaEntry(requete, queryValue, resultValue);
			case "prix":
				resultValue = ServerHttp.lesTypes.get(ServerHttp.getPizza(queryValue).getType());
				return new PizzaEntry(requete, queryValue, resultValue);
			default:
				return null;
		}
	}
}
