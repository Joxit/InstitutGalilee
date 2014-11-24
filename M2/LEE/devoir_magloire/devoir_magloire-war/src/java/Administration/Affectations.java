/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Administration;

import entity.BureauxFacadeLocal;
import entity.Personnes;
import entity.PersonnesFacadeLocal;
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
@WebServlet(name = "Admin.Affectations", urlPatterns = {"/Admin.Affectations"})
public class Affectations extends HttpServlet {

	@EJB
	private BureauxFacadeLocal bureauxFacade;

	@EJB
	private PersonnesFacadeLocal personnesFacade;

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
				if (request.getParameter(AdminHtmlWriter.subAddDeskToPers) != null) {
					String pers = request.getParameter(AdminHtmlWriter.txtAddPersOfDesk);
					String desk = request.getParameter(AdminHtmlWriter.txtAddDeskOfPers);
					Personnes p = personnesFacade.find(Integer.parseInt(pers));
					entity.Bureaux b = bureauxFacade.find(Integer.parseInt(desk));
					if (b != null && p != null) {
						if (b.getLimite() < personnesFacade.findByBureau(b).size()) {
							p.setBureau(b);
							personnesFacade.edit(p);
							HtmlWriter.printH2Success(out, p.getNom() + " " + p.getPrenom()
									+ " (" + p.getPersonneId() + ") ajouté au bureau " + HtmlWriter.bureau(b));
						} else {
							HtmlWriter.printH2Error(out, "Ce bureau est plein");
						}
					} else {
						HtmlWriter.printH2Error(out, "Identifiants incorrects");
					}
				}
				AdminHtmlWriter.printDeskToPers(out, bureauxFacade.findAll());
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
