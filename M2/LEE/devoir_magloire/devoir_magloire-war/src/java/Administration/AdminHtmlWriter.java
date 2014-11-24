/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Administration;

import entity.Bureaux;
import entity.Messages;
import entity.Personnes;
import java.io.PrintWriter;
import java.text.DateFormat;
import java.util.List;
import static utils.Utils.toThreeDigits;
import web.HtmlWriter;

/**
 *
 * @author joxit
 */
public class AdminHtmlWriter {

	/**
	 * Identifiant du bouton pour ajouter une liste de bureaux
	 */
	protected static final String subAddDesks = "subAddDesks";
	/**
	 * Identifiant de la zone de texte pour ajouter une liste de bureaux
	 */
	protected static final String txtAddDesks = "txtAddDesks";
	/**
	 * Identifiant du bouton pour ajouter une liste de personnes
	 */
	protected static final String subAddPers = "subAddPers";
	/**
	 * Identifiant de la zone de texte pour ajouter une liste de personnes
	 */
	protected static final String txtAddPers = "txtAddPers";

	protected static final String subAddDeskToPers = "subAddDeskToPers";
	protected static final String txtAddDeskOfPers = "txtAddDeskOfPers";
	protected static final String txtAddPersOfDesk = "txtAddPersOfDesk";

	protected static final String subLogin = "subLogin";
	protected static final String txtLogin = "txtLogin";
	protected static final String txtPassword = "txtPassword";

	protected static final String subMessageReaded = "subMessageReaded";

	/**
	 * @param out ou l'on envoie le code HTML pour le formulaire de connexion
	 */
	protected static void printLogin(PrintWriter out) {
		out.println("<form method='POST'>");
		out.println("<table>");
		out.println("<tr><td>Login: </td><td><input type='text' name='" + txtLogin + "'></td></tr><br/>");
		out.println("<tr><td>Mot de passe: </td><td><input type='password' name='" + txtPassword + "'></td></tr><br/>");
		out.println("</table>");
		out.println("<input type='submit' name='" + subLogin + "'><br/>");
		out.println("</form>");
	}

	/**
	 * @param out ou l'on envoie la liste au format HTML
	 * @param lb  liste des bureaux a afficher dans un tableau HTML
	 */
	protected static void printDesk(PrintWriter out, List<Bureaux> lb) {
		out.println("<h1>Liste des bureaux</h1>");
		out.println("<table class=\"list\">");
		out.println("<tr><td>ID</td><td>Batiment</td><td>Etage</td>"
				+ "<td>Numero</td><td>Limite</td></tr>");
		lb.stream().forEach(b -> {
			out.println("<tr><td>" + b.getBureauId() + "</td>");
			out.println("<td>" + b.getBatiment() + "</td>");
			out.println("<td>" + b.getEtage() + "</td>");
			out.println("<td>"
					+ utils.Utils.toThreeDigits(b.getNumero()) + "</td>");
			out.println("<td>" + b.getLimite() + "</td></tr>");
		});
		out.println("</table>");
	}

	/**
	 * @param out ou l'on envoie la liste au format HTML
	 * @param lp  liste des personnes a afficher dans un tableau HTML
	 */
	protected static void printPersonnes(PrintWriter out, List<Personnes> lp) {
		out.println("<h1>Liste des personnes</h1>");
		out.println("<table class=\"list\">");
		out.println("<tr><td>ID</td><td>Nom</td><td>Prenom</td>"
				+ "<td>Bureau (ID)</td><td>Mail</td><td>Equipe</td><td>Droits</td></tr>");
		lp.stream().forEach(p -> {
			out.println("<tr><td>" + p.getPersonneId() + "</td>");
			out.println("<td>" + p.getNom() + "</td>");
			out.println("<td>" + p.getPrenom() + "</td>");
			Bureaux b = p.getBureau();
			out.println("<td>"
					+ (b != null ? (HtmlWriter.bureau(b)
							+ " (" + b.getBureauId() + ")") : "") + "</td>");
			out.println("<td>" + (p.getMail() != null ? p.getMail() : "") + "</td>");
			out.println("<td>" + (p.getEquipe() != null ? p.getEquipe().getEquipeId() : "") + "</td>");
			out.println("<td>"
					+ (p.getResponsablesCollection().isEmpty() ? "" : "Admin")
					+ "</td></tr>");
		});
		out.println("</table>");
	}

	protected static void printAddPersonne(PrintWriter out) {
		out.println("<h1>Ajouter une personnes</h1>");
		out.println("<form method='POST'>");
		out.println("Nom: <input type='text' name='" + "'>");
		out.println("Prenom: <input type='text' name='" + "'>");
		out.println("Mail: <input type='text' name='" + "'>");
		out.println("Equipe: <input type='text' name='" + "'>");
		out.println("<input type='submit' name='"
				+ subAddPers + "'><br/>");
		out.println("</form>");
	}

	/**
	 * Les messages non lus pourront etre selectionnés pour etre affiché comme
	 * lu grace a un bouton submit
	 *
	 * @param out ou l'on envoie la liste au format HTML
	 * @param lm  liste des messages a afficher, on separe les messages lus des
	 *            messages non lus
	 */
	protected static void printMessages(PrintWriter out, List<Messages> lm) {
		out.println("<h2>Les messages non lus</h2>");
		lm.stream().filter(m -> {
			return !m.getEtat();
		}).forEach(m -> {
			Personnes p = m.getAuteur();
			String df = DateFormat.getInstance().format(m.getEnvoie());
			out.println("<h3>Message de " + p.getNom() + " " + p.getPrenom()
					+ " (" + p.getPersonneId() + ") envoyé le " + df + "</h3>");
			out.println("<p>" + m.getMessage().replace("\n", "<br/>\n") + "</p>");
			out.println("<form method='POST'>");
			out.println("Afficher comme lu <input type='submit' name='"
					+ subMessageReaded + "' value='Lire_" + m.getMessageId() + "'><br/>");
			out.println("</form>");
		});
		out.println("<h2>Les messages lus</h2>");
		lm.stream().filter(m -> {
			return m.getEtat();
		}).forEach(m -> {
			Personnes p = m.getAuteur();
			String df = DateFormat.getInstance().format(m.getEnvoie());
			out.println("<h3>Message de " + p.getNom() + " " + p.getPrenom()
					+ " (" + p.getPersonneId() + ") envoyé le " + df + "</h3>");
			out.println("<p>" + m.getMessage().replace("\n", "<br/>\n") + "</p>");
		});
	}

	/**
	 * @param out ou l'on envoie le formulaire d'affectation au format HTML
	 * @param lb  liste des bueaux
	 */
	protected static void printDeskToPers(PrintWriter out, List<Bureaux> lb) {
		out.println("<h2>Affecter un bureau à une personne</h2>");
		out.println("<form method='POST'>");
		out.println("ID bureau: <select name='" + txtAddDeskOfPers + "'>");
		lb.stream().forEach(b -> {
			out.println("<option value='" + b.getBureauId() + "'>" + HtmlWriter.bureau(b) + "</option>");
		});
		out.println("</select><br/>");
		out.println("ID personne: <input type='text' name='" + txtAddPersOfDesk + "'><br/>");
		out.println("<input type='submit' value='Affecter' name='" + subAddDeskToPers + "'><br/>");
		out.println("</form>");
	}

	protected static void printAddPers(PrintWriter out) {
		out.println("<h2>Ajouter une personne</h2>");
		out.println("<form method='POST'>");
		out.println("Nom: <input type='text' name='" + txtAddPersOfDesk + "'><br/>");
		out.println("Prenom: <input type='text' name='" + txtAddPersOfDesk + "'><br/>");
		out.println("E-mail: <input type='text' name='" + txtAddPersOfDesk + "'><br/>");
		out.println("Equipe: <input type='text' name='" + txtAddPersOfDesk + "'><br/>");
		out.println("<input type='submit' value='Affecter' name='" + subAddDeskToPers + "'><br/>");
		out.println("</form>");
	}
}
