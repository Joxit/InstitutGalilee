/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package web;

import entity.Bureaux;
import java.io.PrintWriter;

/**
 *
 * @author joxit
 */
public class HtmlWriter {

	public static void printHead(PrintWriter out) {
		out.println("<head>");
		out.println("<title>Gestion des bureaux</title>");
		out.println("<meta charset=\"UTF-8\">");
		out.println("<link media=\"all\" type=\"text/css\" href=\"style.css\" rel=\"stylesheet\" />");
		out.println("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">");
		out.println("</head>");
	}

	public static void printHeaderMenuHome(PrintWriter out) {
		printHeaderMenu(out, 0);
	}

	public static void printHeaderMenuClient(PrintWriter out) {
		printHeaderMenu(out, 1);
	}

	public static void printHeaderMenuAdmin(PrintWriter out) {
		printHeaderMenu(out, 2);
	}

	public static void printHeaderMenuAdminLogged(PrintWriter out) {
		printHeaderMenu(out, 3);
	}

	private static void printHeaderMenu(PrintWriter out, int menu) {
		out.println("<div id=\"header\">");
		out.println("<div id=\"header-content\">");
		out.println("<div id=\"header-name\">Gestion des bureaux<br />");
		out.println("<span>Projet de Master 2 Informatique</span><br />");
		out.println("</div>");
		out.println("<div id=\"header-menu\">");
		out.println("<ul>");
		printHomeSubMenu(out, menu == 0);
		printClientSubMenu(out, menu == 1);
		if (menu == 3) {
			printAdminSubMenu(out);
		} else {
			printAdminSubMenu(out, menu == 2);
		}
		out.println("</ul>");
		out.println("</div>");
		out.println("</div>");
		out.println("</div>");
	}

	private static void printClientSubMenu(PrintWriter out, boolean focus) {
		out.println("<li class=\"border-bottom-" + (focus ? "line" : "transition")
				+ "\"><a href=\"Client\">Client</a>");
		out.println("<ul>");
		out.println("<li><a href=\"Utilisateurs\">Les personnes</a></li>");
		out.println("<li><a href=\"Affectations\">Les Affectations</a></li>");
		out.println("<li><a href=\"Message\">Envoyer Message</a></li>");
		out.println("</ul>");
		out.println("</li>");
	}

	private static void printAdminSubMenu(PrintWriter out, boolean focus) {
		out.println("<li class=\"border-bottom-" + (focus ? "line" : "transition")
				+ "\">" + (!focus ? "<a href=\"Admin\">" : "")
				+ "Administrateur" + (!focus ? "</a>" : "") + "</li>");
	}

	private static void printAdminSubMenu(PrintWriter out) {
		out.println("<li class=\"border-bottom-line\"><a href=\"Admin\">Administrateur</a>");
		out.println("<ul>");
		out.println("<li><a href=\"Admin.Utilisateurs\">Ajouter personne</a></li>");
		out.println("<li><a href=\"Admin.Bureaux\">Ajouter Bureau</a></li>");
		out.println("<li><a href=\"Admin.Affectations\">Affecter Bureau</a></li>");
		out.println("<li><a href=\"Admin.Message\">Lire Messages</a></li>");
		out.println("</ul>");
		out.println("</li>");
	}

	private static void printHomeSubMenu(PrintWriter out, boolean focus) {
		out.println("<li class=\"border-bottom-" + (focus ? "line" : "transition")
				+ "\">" + (!focus ? "<a href=\"index.html\">" : "")
				+ "Home" + (!focus ? "</a>" : "") + "</li>");
	}

	public static String bureau(Bureaux b) {
		if (b != null) {
			int n = b.getNumero();
			return (String.valueOf(b.getBatiment())
					+ String.valueOf(b.getEtage()) + " "
					+ (n < 10 ? "00" + n : n < 100 ? "0" + n : n));
		} else {
			return "";
		}
	}

	public static void printH2Success(PrintWriter out, String s) {
		out.println("<h2 class='success'>" + s + "</h2>");

	}

	public static void printH2Error(PrintWriter out, String s) {
		out.println("<h2 class='error'>" + s + "</h2>");

	}
}
