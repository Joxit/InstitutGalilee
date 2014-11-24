/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Administration;

import entity.BureauxFacadeLocal;
import entity.MessagesFacadeLocal;
import entity.PersonnesFacadeLocal;
import entity.Responsables;
import entity.ResponsablesFacadeLocal;
import java.io.IOException;
import java.io.PrintWriter;
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
 * @author 11000369
 */
@WebServlet(name = "Admin", urlPatterns = {"/Admin"})
public class Admin extends HttpServlet {

	@EJB
	private ResponsablesFacadeLocal responsablesFacade;

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
		response.setContentType("text/html;charset=UTF-8");
		try (PrintWriter out = response.getWriter()) {
			/* TODO output your page here. You may use following sample code. */
			out.println("<!DOCTYPE html>");
			out.println("<html>");
			HtmlWriter.printHead(out);
			out.println("<body>");
			out.println("<div class=\"container\">");
			if (request.getParameter(AdminHtmlWriter.subLogin) != null) {
				boolean isLogged = false;
				List<Responsables> lr = responsablesFacade.findAll();
				String login = request.getParameter(AdminHtmlWriter.txtLogin);
				String password = request.getParameter(AdminHtmlWriter.txtPassword);
				for (Responsables r : lr) {
					if (r.getIdentifiant().equals(login)
							&& r.getMotDePasse().equals(password)) {
						isLogged = true;
						Cookie log = new Cookie("login", login);
						Cookie psw = new Cookie("password", password);
						response.addCookie(log);
						response.addCookie(psw);
						break;
					}
				}
				if (!isLogged) {
					HtmlWriter.printHeaderMenuAdmin(out);
					AdminHtmlWriter.printLogin(out);
				} else {
					HtmlWriter.printHeaderMenuAdminLogged(out);
					printBody(out);
				}
			} else {
				Cookie[] cookies = Authentification.getLoginAndPasswordCookie(request.getCookies());
				if (Authentification.hasCorrectPassword(cookies, responsablesFacade.findAll())) {
					HtmlWriter.printHeaderMenuAdminLogged(out);
					printBody(out);
				} else {
					HtmlWriter.printHeaderMenuAdmin(out);
					AdminHtmlWriter.printLogin(out);
				}
			}
			out.println("</div>");
			out.println("</body>");
			out.println("</html>");
		}
	}

	private void printBody(PrintWriter out) {
		out.println("<h1>Bienvenue dans la partie Administration du logiciel</h1>");
		out.println("<h2>Que souhaitez vous faire ?</h2>");
		out.println("<p>Vous pouvez choisir les actions que vous souhaitez "
				+ "via le menu en survolant 'Administrateur'. Vous pouvez voir la liste"
				+ " et ajouter des personnes qui sont dans nos locaux, les bureaux,"
				+ " affecter un bureau à une personne et lire les messages des utilisateurs.</p>");
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
