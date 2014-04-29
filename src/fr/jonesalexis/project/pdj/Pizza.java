package fr.jonesalexis.project.pdj;

public class Pizza {
	private String nom;
	private String description;
	private int type;

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
		return "Pizza [nom=" + nom + ", description=" + description + ", type=" + type + "]";
	}

	public int getType() {
		return type;
	}

	public double getPrix() {
		switch (type) {
			case 1:
				return 12;
			case 2:
				return 13;
			case 3:
				return 14;
			default:
				return 16;
		}
	}

	public void setType(int type) {
		this.type = type;
	}

	public String toLink() {
		String res = "";
		for (char c : nom.toCharArray()) {
			if (((c >= 'a') && (c <= 'z')) || ((c >= 'A') && (c <= 'Z'))) {
				res += c;
			}
		}
		return res;
	}
}
