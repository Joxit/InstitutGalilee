package fr.jonesalexis.project.pdj.xml;

import java.io.FileReader;
import java.io.IOException;
import java.util.HashMap;

import org.xml.sax.Attributes;
import org.xml.sax.ContentHandler;
import org.xml.sax.InputSource;
import org.xml.sax.Locator;
import org.xml.sax.SAXException;
import org.xml.sax.XMLReader;
import org.xml.sax.helpers.XMLReaderFactory;

/**
 * Lit un fichier XML pour les types et permet le renvoie de toutes les
 * informations sous forme de HashMap (id type, prix)
 * @author Jones Magloire
 */
public class TypeXMLReader implements ContentHandler {
	private enum Balises {
		TYPE, PRIX
	}

	private Balises balise;
	private final HashMap<String, String> lesTypes;
	private String nom;

	private String prix;

	public TypeXMLReader() {
		lesTypes = new HashMap<String, String>();
	}

	@Override
	public void characters(char[] ch, int start, int length) throws SAXException {
		if (balise == Balises.TYPE) {
			balise = null;
		} else if (balise == Balises.PRIX) {
			String prix = new String(ch, start, length);
			this.prix = prix;
			balise = null;
		}
	}

	@Override
	public void endDocument() throws SAXException {
		// TODO Auto-generated method stub

	}

	@Override
	public void endElement(String uri, String localName, String qName) throws SAXException {
		if (localName.equalsIgnoreCase("type")) {
			lesTypes.put(nom, prix);
			nom = null;
			prix = null;
		}

	}

	@Override
	public void endPrefixMapping(String prefix) throws SAXException {
		// TODO Auto-generated method stub

	}

	public HashMap<String, String> getLesTypes() {
		return lesTypes;
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
		if (localName.equalsIgnoreCase("type")) {
			balise = Balises.TYPE;
			nom = atts.getValue("id");
		} else if (localName.equalsIgnoreCase("prix")) {
			balise = Balises.PRIX;
		}
	}

	@Override
	public void startPrefixMapping(String prefix, String uri) throws SAXException {
		// TODO Auto-generated method stub

	}

}
