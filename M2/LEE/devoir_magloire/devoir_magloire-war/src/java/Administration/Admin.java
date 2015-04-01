/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Administration;

import entity.Responsables;
import entity.ResponsablesFacadeLocal;
import java.io.IOException;
import java.util.List;
import javax.ejb.EJB;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

/**
 * Servlet controlant la page de connexion administrateur du site. Quand on veut
 * acceder a une partie du site demandant l'acces des responsables, on sera
 * renvoyé ici. Elle controle les requetes HTTP de la page adminlogin.jsp. La
 * jsp associée a cette servmet est /WEB-INF/adminlogin.jsp
 *
 * Les attributs final public static de cette classe sont référencés dans la jsp
 * pour avoir une armonie dans les identifiants des parametres.
 *
 * @author Jones Magloire
 * @version 2
 */
@WebServlet(name = "Admin", urlPatterns = {"/Admin"})
public class Admin extends HttpServlet {

	@EJB
	private ResponsablesFacadeLocal responsablesFacade;

	/**
	 * Identifiant de la zone de texte pour le login de connexion
	 */
	final public static String txtLogin = "txtLogin";

	/**
	 * Identifiant de la zone de texte pour le password de connexion
	 */
	final public static String txtPassword = "txtPassword";

	/**
	 * Identifiant du bouton submit pour le login de connexion
	 */
	final public static String subLogin = "subLogin";

	/**
	 * Processes requests for both HTTP <code>GET</code> and <code>POST</code>
	 * methods.
	 *
	 * @param request  servlet request
	 * @param response servlet response
	 *
	 * @throws ServletException if a servlet-specific error occurs
	 * @throws IOException      if an I/O error occurs
	 */
	protected void processRequest(HttpServletRequest request,
			HttpServletResponse response)
			throws ServletException, IOException {
		if (request.getParameter(subLogin) != null) {
			processLogin(request);
		}
		getServletContext().getRequestDispatcher("/WEB-INF/Administration/index.jsp").forward(request, response);
	}

	/**
	 * Processus pour la requete HTTP <code>POST</code> du login. Verifie si
	 * l'utilisateur a entré un login qui est dans notre base, ensuite on
	 * regarde si le password de ce login est correct, dans le cas contraire, on
	 * affiche une erreur chez le client. Quand la connexion réussie, on ajoute
	 * des cookies dnas le navigateur client pour qu'on sache qu'il est connecté
	 *
	 * @param request  servlet request où l'on mettra le message dans l'attribut
	 *                 success si tout ce passe bien ou un dans error s'il y a
	 *                 un probleme
	 * @param response servlet response où l'on mettra les cookies de connexion
	 */
	private void processLogin(HttpServletRequest request) {
		List<Responsables> lr = responsablesFacade.findAll();
		String login = request.getParameter(txtLogin);
		String password = request.getParameter(txtPassword);

		for (Responsables r : lr) {
			if (r.getIdentifiant().equals(login)) {
				if (r.getMotDePasse().equals(password)) {
					Authentification.add(request);
					request.setAttribute("isLogged", true);
					request.setAttribute("success", "Connexion réussie");
					return;
				}
				break;
			}
		}
		request.setAttribute("error", "Mauvais identifiants");
	}

	// <editor-fold defaultstate="collapsed" desc="HttpServlet methods. Click on the + sign on the left to edit the code.">
	/**
	 * Handles the HTTP <code>GET</code> method.
	 *
	 * @param request  servlet request
	 * @param response servlet response
	 *
	 * @throws ServletException if a servlet-specific error occurs
	 * @throws IOException      if an I/O error occurs
	 */
	@Override
	protected void doGet(HttpServletRequest request,
			HttpServletResponse response)
			throws ServletException, IOException {
		processRequest(request, response);
	}

	/**
	 * Handles the HTTP <code>POST</code> method.
	 *
	 * @param request  servlet request
	 * @param response servlet response
	 *
	 * @throws ServletException if a servlet-specific error occurs
	 * @throws IOException      if an I/O error occurs
	 */
	@Override
	protected void doPost(HttpServletRequest request,
			HttpServletResponse response)
			throws ServletException, IOException {
		processRequest(request, response);
	}

	/**
	 * Returns a short description of the servlet.
	 *
	 * @return a String containing servlet description
	 */
	@Override
	public String getServletInfo() {
		return "Short description";
	}// </editor-fold>

}
