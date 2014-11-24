/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Administration;

import entity.Messages;
import entity.MessagesFacadeLocal;
import entity.ResponsablesFacadeLocal;
import java.io.IOException;
import java.io.PrintWriter;
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
	@EJB
	private ResponsablesFacadeLocal responsablesFacade;

	/**
	 * Processes requests for both HTTP <code>GET</code> and <code>POST</code>
	 * methods.
	 *
	 * @param request servlet request
	 * @param response servlet response
	 * @throws ServletException if a servlet-specific error occurs
	 * @throws IOException if an I/O error occurs
	 */
	protected void processRequest(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {
		response.setContentType("text/html;charset=UTF-8");
		try (PrintWriter out = response.getWriter()) {
			out.println("<!DOCTYPE html>");
			out.println("<html>");
			HtmlWriter.printHead(out);
			out.println("<body>");
			out.println("<div class=\"container\">");
			Cookie[] cookies = Authentification.getLoginAndPasswordCookie(request.getCookies());
			if (Authentification.hasCorrectPassword(cookies, responsablesFacade.findAll())) {
				HtmlWriter.printHeaderMenuAdminLogged(out);
				String txt = request.getParameter(AdminHtmlWriter.subMessageReaded);
				if (txt != null) {
					try {
						String[] split = txt.split("_");
						int id = Integer.parseInt(split[1]);
						Messages m = messagesFacade.find(id);
						m.setEtat(Boolean.TRUE);
						messagesFacade.edit(m);
					} catch (Exception e) {
						HtmlWriter.printH2Error(out, "Une erreur est survenue");
					}

				}
				AdminHtmlWriter.printMessages(out, messagesFacade.findAll());
			} else {
				response.sendRedirect(getServletContext().getContextPath() + "/Admin");
			}
			out.println("</div>");
			out.println("</body>");
			out.println("</html>");
		}
	}

	// <editor-fold defaultstate="collapsed" desc="HttpServlet methods. Click on the + sign on the left to edit the code.">
	/**
	 * Handles the HTTP <code>GET</code> method.
	 *
	 * @param request servlet request
	 * @param response servlet response
	 * @throws ServletException if a servlet-specific error occurs
	 * @throws IOException if an I/O error occurs
	 */
	@Override
	protected void doGet(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {
		processRequest(request, response);
	}

	/**
	 * Handles the HTTP <code>POST</code> method.
	 *
	 * @param request servlet request
	 * @param response servlet response
	 * @throws ServletException if a servlet-specific error occurs
	 * @throws IOException if an I/O error occurs
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
