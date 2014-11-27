/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Administration;

import entity.BureauxFacadeLocal;
import entity.Personnes;
import entity.PersonnesFacadeLocal;
import java.io.IOException;
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
@WebServlet(name = "Admin.Affectations", urlPatterns = {"/Admin.Affectations"})
public class Affectations extends HttpServlet {

	public static final String subAffect = "subAddDeskToPers";
	public static final String txtPers = "txtAddPersOfDesk";
	public static final String txtDesk = "txtAddDeskOfPers";

	@EJB
	private BureauxFacadeLocal bureauxFacade;
	@EJB
	private PersonnesFacadeLocal personnesFacade;

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
		if (request.getParameter(subAffect) != null) {
			String desk = request.getParameter(txtDesk);
			entity.Bureaux b = bureauxFacade.find(Integer.parseInt(desk));
			if (b != null) {
				String pers = request.getParameter(txtPers);
				Personnes p = personnesFacade.find(Integer.parseInt(pers));
				if (p != null) {
					if (b.getLimite() > personnesFacade.findByBureau(b).size()) {
						p.setBureau(b);
						personnesFacade.edit(p);
						request.setAttribute("success", p.getNom() + " " + p.getPrenom()
								+ " (" + p.getPersonneId() + ") ajouté au bureau " + HtmlWriter.bureau(b));
					} else {
						request.setAttribute("error", "Ce bureau est plein");
					}
				} else {
					request.setAttribute("error", "Cette personne n'existe pas");
				}
			} else {
				request.setAttribute("error", "Ce bureau n'existe pas");
			}
		}
		request.setAttribute("personnes", personnesFacade.findAllSortedByName());
		request.setAttribute("bureaux", bureauxFacade.findAll());
		getServletContext().getRequestDispatcher("/WEB-INF/Administration/affectations.jsp").forward(request, response);
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
