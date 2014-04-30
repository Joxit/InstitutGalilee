package fr.jonesalexis.project.pdj.proto.piz;

/**
 * Classe pour avoir le contenue des requetes.
 * @author Jones Magloire
 */
public class PizzaEntry {
	private String type;
	private String queryValue;
	private String resultValue;

	public PizzaEntry(String type, String queryValue, String resultValue) {
		setType(type);
		setQueryValue(queryValue);
		setResultValue(resultValue);
	}

	public String getQueryValue() {
		return queryValue;
	}

	public String getResultValue() {
		return resultValue;
	}

	public String getType() {
		return type;
	}

	protected void setQueryValue(String queryValue) {
		this.queryValue = queryValue;
	}

	protected void setResultValue(String resultValue) {
		this.resultValue = resultValue;
	}

	protected void setType(String type) {
		this.type = type;
	}

	@Override
	public String toString() {
		return "PizzaEntry [type=" + type + ", queryValue=" + queryValue + ", resultValue="
				+ resultValue + "]";
	}
}
