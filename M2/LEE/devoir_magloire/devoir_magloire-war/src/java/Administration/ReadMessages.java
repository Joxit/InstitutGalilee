/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Administration;

import entity.Messages;
import entity.MessagesFacadeLocal;
import entity.Personnes;
import java.io.IOException;
import javax.ejb.EJB;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

/**
 * Servlet pour la lecture des messages par l'admin. Les messages peuvent etre
 * lus et supprimés
 *
 * Les attributs final public static de cette classe sont référencés dans la jsp
 * pour avoir une armonie dans les identifiants des parametres.
 *
 * @author Jones Magloire
 * @version 2 (2/12/14)
 */
@WebServlet(name = "Admin.Message", urlPatterns = {"/Admin.Message"})
public class ReadMessages extends HttpServlet {

	@EJB
	private MessagesFacadeLocal messagesFacade;
	/**
	 * Identifiant du bouton submit pour la lecture et suppression de mssages
	 */
	public static final String subMessageReaded = "subMessageReaded";

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
	protected void processRequest(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {
		String[] txt = request.getParameterValues(subMessageReaded);
		if (txt != null) {
			try {
				int id = utils.Utils.getFirstNumeric(txt);
				Messages m = messagesFacade.find(id);
				Personnes p = m.getAuteur();
				String action;
				if (!m.getEtat()) {
					m.setEtat(Boolean.TRUE);
					messagesFacade.edit(m);
					action = "lu";
				} else {
					messagesFacade.remove(m);
					action = "supprimé";
				}
				request.setAttribute("success", "Message de de " + p.getNom() + " " + p.getPrenom()
						+ "(" + p.getPersonneId() + ") " + action);
			} catch (Exception e) {
				request.setAttribute("error", "Une erreur est survenue");
			}
		}

		request.setAttribute("readed", messagesFacade.findByEtatSorted(Boolean.TRUE));
		request.setAttribute("toRead", messagesFacade.findByEtatSorted(Boolean.FALSE));
		getServletContext().getRequestDispatcher("/WEB-INF/Administration/message.jsp").forward(request, response);
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
	protected void doGet(HttpServletRequest request, HttpServletResponse response)
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
	protected void doPost(HttpServletRequest request, HttpServletResponse response)
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
