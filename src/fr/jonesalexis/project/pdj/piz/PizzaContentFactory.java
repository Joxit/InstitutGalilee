package fr.jonesalexis.project.pdj.piz;

import java.net.ContentHandler;
import java.net.ContentHandlerFactory;

public class PizzaContentFactory implements ContentHandlerFactory {

	public PizzaContentFactory() {

	}

	@Override
	public ContentHandler createContentHandler(String mimetype) {
		return new PizzaContentHandler();
	}

}
