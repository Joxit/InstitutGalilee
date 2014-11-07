/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Administration;

import java.io.PrintWriter;

/**
 *
 * @author joxit
 */
public class AdminHtmlWriter {

    /**
     * Identifiant du bouton pour afficher la liste des bureaux
     */
    protected static final String subShowDesks = "subShowDesks";
    /**
     * Identifiant du bouton pour ajouter une liste de bureaux
     */
    protected static final String subAddDesks = "subAddDesks";
    /**
     * Identifiant de la zone de texte pour ajouter une liste de bureaux
     */
    protected static final String txtAddDesks = "txtAddDesks";

    /**
     * Identifiant du bouton pour afficher la liste des personnes
     */
    protected static final String subShowPers = "subShowPers";
    /**
     * Identifiant du bouton pour ajouter une liste de personnes
     */
    protected static final String subAddPers = "subAddPers";
    /**
     * Identifiant de la zone de texte pour ajouter une liste de personnes
     */
    protected static final String txtAddPers = "txtAddPers";

    protected static final String subShowDeskToPers = "subShowDeskToPers";
    protected static final String subAddDeskToPers = "subAddDeskToPers";
    protected static final String txtAddDeskOfPers = "txtAddDeskOfPers";
    protected static final String txtAddPersOfDesk = "txtAddPersOfDesk";

    protected static final String subLogin = "subLogin";
    protected static final String txtLogin = "txtLogin";
    protected static final String txtPassword = "txtPassword";

    protected static void printOptions(PrintWriter out) {
        out.println("<h1>Que voulez vous faire ?</h1>");
        out.println("<form method='POST'>");
        out.println("<input type='submit' name='" + subShowDesks + "'><br/>");
        out.println("<input type='submit' name='" + subShowPers + "'><br/>");
        out.println("<input type='submit' name='" + subShowDeskToPers + "'><br/>");
        out.println("</form>");

    }

    protected static void printLogin(PrintWriter out) {
        out.println("<form method='POST'>");
        out.println("<table>");
        out.println("<tr><td>Login: </td><td><input type='text' name='" + txtLogin + "'></td></tr><br/>");
        out.println("<tr><td>Mot de passe: </td><td><input type='password' name='" + txtPassword + "'></td></tr><br/>");
        out.println("</table>");
        out.println("<input type='submit' name='" + subLogin + "'><br/>");
        out.println("</form>");
    }
}
