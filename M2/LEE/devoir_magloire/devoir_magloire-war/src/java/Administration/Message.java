/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Administration;

import entity.Messages;
import entity.MessagesFacadeLocal;
import entity.Personnes;
import entity.ResponsablesFacadeLocal;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.List;
import javax.ejb.EJB;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.Cookie;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import web.HtmlWriter;

/**
 *
 * @author joxit
 */
@WebServlet(name = "Admin.Message", urlPatterns = {"/Admin.Message"})
public class Message extends HttpServlet {

	@EJB
	private MessagesFacadeLocal messagesFacade;
	private final String subMessageReaded = "subMessageReaded";

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
				m.setEtat(Boolean.TRUE);
				messagesFacade.edit(m);
				Personnes p = m.getAuteur();
				request.setAttribute("success", "Message de de " + p.getNom() + " " + p.getPrenom()
						+ "(" + p.getPersonneId() + ") lu");
			} catch (Exception e) {
				request.setAttribute("error", "Une erreur est survenue");

			}

		}
		List<Messages> readed = new ArrayList<>();
		List<Messages> toRead = new ArrayList<>();
		/* on veut les vieux messages tout en bas de la liste */
		messagesFacade.findAll().stream().sorted((m1, m2) -> {
			return m2.getEnvoie().compareTo(m1.getEnvoie());
		}).forEach(m -> {
			if (m.getEtat()) {
				readed.add(m);
			} else {
				toRead.add(m);
			}
		});
		request.setAttribute("readed", readed);
		request.setAttribute("toRead", toRead);
		request.setAttribute(subMessageReaded, subMessageReaded);
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
