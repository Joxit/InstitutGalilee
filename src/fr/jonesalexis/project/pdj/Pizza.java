package fr.jonesalexis.project.pdj;

public class Pizza {
	private String nom;
	private String description;
	private String type;

	public Pizza() {
		setNom("");
		setDescription("");
	}

	public String getNom() {
		return nom;
	}

	public void setNom(String nom) {
		this.nom = nom;
	}

	public String getDescription() {
		return description;
	}

	public void setDescription(String description) {
		this.description = description;
	}

	@Override
	public String toString() {
		return "Pizza [nom=" + nom + ", description=" + description + ", type="
				+ type + "]";
	}

	public String getType() {
		return type;
	}

	public void setType(String type) {
		this.type = type;
	}

	public String toLink() {
		String res = "";
		for (char c : nom.toCharArray()) {
			if (((c >= 'a') && (c <= 'z')) || ((c >= 'A') && (c <= 'Z'))
					|| ((c >= '0') && (c <= '9'))) {
				res += c;
			}
		}
		return res;
	}
}
