/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Administration;

import entity.BureauxFacadeLocal;
import java.io.IOException;
import javax.ejb.EJB;
import javax.ejb.EJBException;
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
@WebServlet(name = "Admin.Bureaux", urlPatterns = {"/Admin.Bureaux"})
public class Bureaux extends HttpServlet {

	@EJB
	private BureauxFacadeLocal bureauxFacade;

	final static public String txtBat = "txtBat";
	final static public String txtEtage = "txtEtage";
	final static public String txtDigits = "txtDigits";
	final static public String txtPlaces = "txtPlaces";
	final static public String subDesk = "subDesk";
	final static public String subDeskEdit = "subDeskEdit";

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
		if (request.getParameter(subDesk) != null) {
			processSubmitDesk(request, response);
		}
		request.setAttribute("bureaux", bureauxFacade.findAll());
		getServletContext().getRequestDispatcher("/WEB-INF/Administration/bureaux.jsp").forward(request, response);
	}

	private void processSubmitDesk(HttpServletRequest request, HttpServletResponse response) {
		String bat = request.getParameter(txtBat);
		String etage = request.getParameter(txtEtage);
		String digits = request.getParameter(txtDigits);
		String places = request.getParameter(txtPlaces);

		if (utils.Utils.isNullOrEmpty(txtBat) || utils.Utils.isNullOrEmpty(txtBat)
				|| utils.Utils.isNullOrEmpty(txtBat) || utils.Utils.isNullOrEmpty(txtBat)) {
			request.setAttribute("error", "Remplissez tous les champs");
			return;
		}

		if (!utils.Utils.isNumeric(etage)) {
			request.setAttribute("error", "L'etage doit etre un nombre");
			return;
		}
		if (!utils.Utils.isNumeric(digits)) {
			request.setAttribute("error", "Le digit doit etre un nombre");
			return;
		}
		if (!utils.Utils.isNumeric(places)) {
			request.setAttribute("error", "Le nombre de place doit etre un nombre");
			return;
		}
		entity.Bureaux b = new entity.Bureaux();
		b.setBatiment(bat.charAt(0));
		b.setEtage(Integer.parseInt(etage));
		b.setNumero(Integer.parseInt(digits));
		b.setLimite(Integer.parseInt(places));
		try {
			bureauxFacade.create(b);
			request.setAttribute("success", "Bureau " + HtmlWriter.bureau(b) + " créé");
		} catch (EJBException e) {
			request.setAttribute("error", "Erreur lors de la creation du bureau : "
					+ e.getCausedByException().getMessage());
		}

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
