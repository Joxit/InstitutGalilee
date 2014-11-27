/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Client;

import entity.Messages;
import entity.MessagesFacadeLocal;
import java.io.IOException;
import java.io.PrintWriter;
import javax.ejb.EJB;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import web.HtmlWriter;

/**
 *
 * @author joxit
 */
@WebServlet(name = "Message", urlPatterns = {"/Message"})
public class Message extends HttpServlet {

	@EJB
	private MessagesFacadeLocal messagesFacade;
	final private String subSendMsg = "subSendMsg";
	final private String txtPersSendMsg = "txtPersSendMsg";
	final private String txtTxtSendMsg = "txtTxtSendMsg";

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
		request.setAttribute("subSendMsg", "subSendMsg");
		request.setAttribute("txtPersSendMsg", "txtPersSendMsg");
		request.setAttribute("txtTxtSendMsg", "txtTxtSendMsg");
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
