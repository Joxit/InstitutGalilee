/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Client;

import entity.Bureaux;
import entity.Personnes;
import entity.PersonnesFacadeLocal;
import java.io.PrintWriter;
import java.util.List;
import web.HtmlWriter;

/**
 *
 * @author joxit
 */
public class ClientHtmlWriter {

	protected static final String subShowSendMsg = "subShowSendMsg";
	protected static final String subSendMsg = "subSendMsg";
	protected static final String txtTxtSendMsg = "txtSendMsg";
	protected static final String txtPersSendMsg = "txtPersSendMsg";

	protected static void printOptions(PrintWriter out) {
		out.println("<h2>Que voulez vous faire ?</h2>");
		out.println("<form method='POST'>");
		out.println("<input type='submit' value='Envoyer message' name='" + subShowSendMsg + "'><br/>");
		out.println("<input type='submit' value='Les personnes' name='" + "" + "'><br/>");
		out.println("<input type='submit' value='Les affectations' name='" + "" + "'><br/>");
		out.println("</form>");
	}

	protected static void printSendMsg(PrintWriter out) {
		out.println("<h2>Quel est votre message ?</h2>");
		out.println("<form method='POST'>");
		out.println("<input type'text' value='votre identifiant' name='" + txtPersSendMsg + "'><br/>");
		out.println("<textarea rows=\"10\" cols=\"75\" name='" + txtTxtSendMsg + "'></textarea><br/>");
		out.println("<input type='submit' value='Envoyer' name='" + subSendMsg + "'><br/>");
		out.println("</form>");
	}

	protected static void printSendMsg(PrintWriter out, int auteur, String msg) {
		out.println("<h2>Quel est votre message ?</h2>");
		out.println("<form method='POST'>");
		out.println("<input type'text' value='" + auteur + "' name='" + txtPersSendMsg + "'><br/>");
		out.println("<textarea rows=\"10\" cols=\"75\" value='" + msg + "' name='" + txtTxtSendMsg + "'></textarea><br/>");
		out.println("<input type='submit' value='Envoyer' name='" + subSendMsg + "'><br/>");
		out.println("</form>");
	}

	protected static void printPersonnes(PrintWriter out, List<entity.Personnes> lp) {
		out.println("<h1>Liste des personnes</h1>");
		out.println("<table class=\"list\">");
		out.println("<tr><td>ID</td><td>Nom</td><td>Prenom</td>"
				+ "<td>Bureau</td><td>Mail</td><td>Equipe</td></tr>");
		lp.stream().forEach(p -> {
			out.println("<tr><td>" + p.getPersonneId() + "</td>");
			out.println("<td>" + p.getNom() + "</td>");
			out.println("<td>" + p.getPrenom() + "</td>");
			Bureaux b = p.getBureau();
			out.println("<td>"
					+ (b != null ? (String.valueOf(b.getBatiment())
							+ String.valueOf(b.getEtage()) + " " + b.getNumero()) : "") + "</td>");
			out.println("<td>" + (p.getMail() != null ? p.getMail() : "") + "</td>");
			out.println("<td>" + (p.getEquipe() != null ? p.getEquipe().getEquipeId() : "")
					+ "</td></tr>");
		});
		out.println("</table>");
	}

	protected static void printBureaux(PrintWriter out, List<entity.Bureaux> lb, PersonnesFacadeLocal personnesFacade) {
		out.println("<h1>Liste des personnes</h1>");
		lb.stream().forEach(b -> {
			List<entity.Personnes> lp = personnesFacade.findByBureau(b);
			if (lp != null && !lp.isEmpty()) {
				out.println("<h3>Bureau: " + HtmlWriter.bureau(b) + "</h3>");

				out.println("<table class=\"list\">");
				out.println("<tr><td>Nom</td><td>Prenom</td><td>Equipe</td></tr>");
				for (Personnes p : lp) {
					out.println("<tr><td>" + p.getNom() + "</td>");
					out.println("<td>" + p.getPrenom() + "</td>");

					out.println("<td>" + (p.getEquipe() != null ? p.getEquipe().getEquipeId() : "")
							+ "</td></tr>");
				}
				out.println("</table>");
			} else {
				out.println("<h3>Bureau: " + (String.valueOf(b.getBatiment())
						+ String.valueOf(b.getEtage()) + " " + b.getNumero()) + " vide</h3>");
			}
		});

	}
}
