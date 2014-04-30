package fr.jonesalexis.project.pdj.xml;

import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;

import org.xml.sax.Attributes;
import org.xml.sax.ContentHandler;
import org.xml.sax.InputSource;
import org.xml.sax.Locator;
import org.xml.sax.SAXException;
import org.xml.sax.XMLReader;
import org.xml.sax.helpers.XMLReaderFactory;

import fr.jonesalexis.project.pdj.Pizza;

/**
 * Lit un fichier XML pour les pizzas et permet le renvoie de toutes les
 * informations sous forme de ArrayList
 * @author Jones Magloire
 */
public class PizzaXMLReader implements ContentHandler {
	private enum Balises {
		PIZZA, NOM, DESC
	}

	private Balises balise;
	private final ArrayList<Pizza> lesPizzas;
	private Pizza current;

	public PizzaXMLReader() {
		lesPizzas = new ArrayList<Pizza>();
	}

	@Override
	public void characters(char[] ch, int start, int length) throws SAXException {
		if (balise == Balises.PIZZA) {
			balise = null;
		} else if (balise == Balises.NOM) {
			String nom = new String(ch, start, length);
			current.setNom(nom);
			balise = null;
		} else if (balise == Balises.DESC) {
			String desc = new String(ch, start, length);
			current.setDescription(desc);
		}

	}

	@Override
	public void endDocument() throws SAXException {
		// TODO Auto-generated method stub

	}

	@Override
	public void endElement(String uri, String localName, String qName) throws SAXException {
		// TODO Auto-generated method stub
		if (localName.equalsIgnoreCase("description")) {
			lesPizzas.add(current);
			current = null;
			balise = null;
		}
	}

	@Override
	public void endPrefixMapping(String prefix) throws SAXException {
		// TODO Auto-generated method stub

	}

	public ArrayList<Pizza> getLesPizzas() {
		return lesPizzas;
	}

	@Override
	public void ignorableWhitespace(char[] ch, int start, int length) throws SAXException {
		// TODO Auto-generated method stub

	}

	public void parse(String fichier) throws IOException, SAXException {
		FileReader f = new FileReader(fichier);
		XMLReader saxReader = XMLReaderFactory.createXMLReader();
		saxReader.setContentHandler(this);
		saxReader.parse(new InputSource(f));
	}

	@Override
	public void processingInstruction(String target, String data) throws SAXException {
		// TODO Auto-generated method stub

	}

	@Override
	public void setDocumentLocator(Locator locator) {
		// TODO Auto-generated method stub

	}

	@Override
	public void skippedEntity(String name) throws SAXException {
		// TODO Auto-generated method stub

	}

	@Override
	public void startDocument() throws SAXException {
		// TODO Auto-generated method stub

	}

	@Override
	public void startElement(String uri, String localName, String qName, Attributes atts)
			throws SAXException {
		if (localName.equalsIgnoreCase("pizza")) {
			balise = Balises.PIZZA;
			current = new Pizza();
			current.setType(atts.getValue("type"));
		} else if (localName.equalsIgnoreCase("nom")) {
			balise = Balises.NOM;
		} else if (localName.equalsIgnoreCase("description")) {
			balise = Balises.DESC;
		}
	}

	@Override
	public void startPrefixMapping(String prefix, String uri) throws SAXException {
		// TODO Auto-generated method stub

	}

	@Override
	public String toString() {
		return "PizzaXMLReader [balise=" + balise + ", lesPizzas=" + lesPizzas + ", current="
				+ current + "]";
	}

}
