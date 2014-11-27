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
import javax.servlet.http.Cookie;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

/**
 *
 * @author 11000369
 */
@WebServlet(name = "Admin", urlPatterns = {"/Admin"})
public class Admin extends HttpServlet {

	@EJB
	private ResponsablesFacadeLocal responsablesFacade;

	final private String txtLogin = "txtLogin";
	final private String txtPassword = "txtPassword";
	final private String subLogin = "subLogin";

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
			List<Responsables> lr = responsablesFacade.findAll();
			String login = request.getParameter(txtLogin);
			String password = request.getParameter(txtPassword);
			for (Responsables r : lr) {
				if (r.getIdentifiant().equals(login)
						&& r.getMotDePasse().equals(password)) {
					Boolean isLogged = true;
					Cookie log = new Cookie("login", login);
					Cookie psw = new Cookie("password", password);
					response.addCookie(log);
					response.addCookie(psw);
					request.setAttribute("isLogged", isLogged);
					break;
				}
			}
		}
		request.setAttribute("txtLogin", txtLogin);
		request.setAttribute("txtPassword", txtPassword);
		request.setAttribute("subLogin", subLogin);
		getServletContext().getRequestDispatcher("/WEB-INF/adminlogin.jsp").forward(request, response);
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
