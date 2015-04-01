/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Client;

import entity.MessagesFacadeLocal;
import java.io.IOException;
import javax.ejb.EJB;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

/**
 * Servlet controlant la page d'envoie de message aux responsables du site.
 * L'utilisateur devra mettre son identifiant et son message dans les champs. On
 * verifie si l'identifiant est correct pui on créer le message. Il sera
 * informer si une erreur arrive.
 *
 * Les attributs final public static de cette classe sont référencés dans la jsp
 * pour avoir une armonie dans les identifiants des parametres.
 *
 * @author Jones Magloire
 * @version 2 (2/12/14)
 */
@WebServlet(name = "Message", urlPatterns = {"/Message"})
public class WriteMessages extends HttpServlet {

	@EJB
	private MessagesFacadeLocal messagesFacade;
	/**
	 * Identifiant du bouton submit pour l'envoie de message
	 */
	final public static String subSendMsg = "subSendMsg";
	/**
	 * Identifiant de la zone de texte contenant l'identifiant de l'utilisateur
	 */
	final public static String txtPersSendMsg = "txtPersSendMsg";
	/**
	 * Identifiant de la zone de texte contenant le corps du message
	 */
	final public static String txtTxtSendMsg = "txtTxtSendMsg";

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

		if (request.getParameter(subSendMsg) != null) {
			try {
				int persId = Integer.parseInt(request.getParameter(txtPersSendMsg));
				messagesFacade.create(persId, request.getParameter(txtTxtSendMsg));
				request.setAttribute("success", "Message envoyé");
			} catch (Exception e) {
				request.setAttribute("error", "Une erreur est survenue lors de l'envoie de votre message");
			}
		}
		getServletContext().getRequestDispatcher("/WEB-INF/Client/message.jsp").forward(request, response);
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
