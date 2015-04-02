package fr.jonesalexis.project.pdj.proto.piz;

import java.io.IOException;
import java.net.ContentHandler;
import java.net.URL;
import java.net.URLConnection;

import fr.jonesalexis.project.pdj.proto.ServerPiz;

/**
 * Classe pour recuperer le contenue d'une requete. Les requetes sont :
 * piz://pizza?list piz://type?list piz://prix?list piz://[Lien pizza]?prix
 * piz://[nom pizza]?desc
 * @author Jones Magloire
 */
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
				resultValue = ServerPiz.getPizza(queryValue).getDescription();
				return new PizzaEntry(requete, queryValue, resultValue);
			case "list":
				resultValue = "pizza/type/prix";
				if (queryValue.equals("pizza")) {
					resultValue = ServerPiz.getAllPizzaLink();
				} else if (queryValue.equals("type")) {
					resultValue = ServerPiz.getAllTypes();
				} else if (queryValue.equals("prix")) {
					resultValue = ServerPiz.getAllPrices();
				}
				return new PizzaEntry(requete, queryValue, resultValue);
			case "prix":
				resultValue = ServerPiz.lesTypes.get(ServerPiz.getPizza(queryValue).getType());
				return new PizzaEntry(requete, queryValue, resultValue);
			default:
				return null;
		}
	}
}
