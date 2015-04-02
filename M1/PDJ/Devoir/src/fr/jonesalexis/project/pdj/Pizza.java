package fr.jonesalexis.project.pdj;

/**
 * Classe des pizzas, elles ont un nom, une description et un type.s
 * @author Jones Magloire
 */
public class Pizza {
	private String nom;
	private String description;
	private String type;

	public Pizza() {
		setNom("");
		setDescription("");
	}

	public String getDescription() {
		return description;
	}

	public String getNom() {
		return nom;
	}

	public String getType() {
		return type;
	}

	public void setDescription(String description) {
		this.description = description;
	}

	public void setNom(String nom) {
		this.nom = nom;
	}

	public void setType(String type) {
		this.type = type;
	}

	/**
	 * @return nom de la pizza avec uniquement ses chiffres et ses lettres
	 */
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

	@Override
	public String toString() {
		return "Pizza [nom=" + nom + ", description=" + description + ", type=" + type + "]";
	}
}
