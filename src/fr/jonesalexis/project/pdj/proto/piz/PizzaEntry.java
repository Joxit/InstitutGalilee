package fr.jonesalexis.project.pdj.proto.piz;

import java.io.IOException;
import java.net.MalformedURLException;
import java.net.URL;

public class PizzaEntry {

	private String type = "A";
	private String queryValue;
	private String resultValue;

	public PizzaEntry() {

	}

	public PizzaEntry(String type, String queryValue, String resultValue) {
		setType(type);
		setQueryValue(queryValue);
		setResultValue(resultValue);
	}

	public String getType() {
		return type;
	}

	protected void setType(String type) {
		this.type = type;
	}

	public String getQueryValue() {

		return queryValue;
	}

	protected void setQueryValue(String queryValue) {
		this.queryValue = queryValue;
	}

	public String getResultValue() {
		return resultValue;
	}

	protected void setResultValue(String resultValue) {
		this.resultValue = resultValue;
	}

	@Override
	public String toString() {
		return "PizzaEntry [type=" + type + ", queryValue=" + queryValue + ", resultValue="
				+ resultValue + "]";
	}
}
