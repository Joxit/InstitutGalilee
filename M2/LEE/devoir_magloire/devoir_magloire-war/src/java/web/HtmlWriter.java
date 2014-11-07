/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package web;

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

    public static void printHeaderMenu(PrintWriter out) {
        out.println("<div id=\"header\">");
        out.println("<div id=\"header-content\">");
        out.println("<div id=\"header-name\">Gestion des bureaux<br />");
        out.println("<span>Projet de Master 2 Informatique</span><br />");
        out.println("</div>");
        out.println("<div id=\"header-menu\">");
        out.println("<ul><li class=\"border-bottom-line\">Home</li>");
        out.println("<li class=\"border-bottom-transition\"><a href=\"Client\">Client</a></li>");
        out.println("<li class=\"border-bottom-transition\"><a href=\"Admin\">Administrateur</a></li>");
        out.println("</ul>");
        out.println("</div>");
        out.println("</div>");
        out.println("</div>");
    }
}
