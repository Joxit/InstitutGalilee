/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Administration;

import entity.Equipes;
import entity.EquipesFacadeLocal;
import entity.Personnes;
import entity.PersonnesFacadeLocal;
import java.io.IOException;
import java.text.ParseException;
import java.util.Date;
import javax.ejb.EJB;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

/**
 *
 * @author joxit
 */
@WebServlet(name = "Admin.Utilisateurs", urlPatterns = {"/Admin.Utilisateurs"})
public class Utilisateurs extends HttpServlet {

	@EJB
	private EquipesFacadeLocal equipesFacade;

	@EJB
	private PersonnesFacadeLocal personnesFacade;

	final static public String txtNom = "txtNom";
	final static public String txtPrenom = "txtPrenom";
	final static public String txtMail = "txtMail";
	final static public String txtDebut = "txtDebut";
	final static public String txtFin = "txtFin";
	final static public String txtEquipe = "txtEquipe";
	final static public String subPers = "subPers";
	final static public String delPers = "delPers";

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
		if (request.getParameter(subPers) != null) {
			processSubmitPers(request, response);
		}
		if (request.getParameter(delPers) != null) {
			processDelPers(request, response);
		}
		request.setAttribute("personnes", personnesFacade.findAll());
		request.setAttribute("equipes", equipesFacade.findAll());

		getServletContext().getRequestDispatcher("/WEB-INF/Administration/utilisateurs.jsp").forward(request, response);
	}

	private void processDelPers(HttpServletRequest request, HttpServletResponse response) {
		try {
			int id = utils.Utils.getFirstNumeric(request.getParameterValues(delPers));
			Personnes p = personnesFacade.find(id);
			personnesFacade.remove(p);
			request.setAttribute("success", p.getPrenom() + " " + p.getNom() + " a bien été supprimé");
		} catch (IllegalArgumentException e) {
			request.setAttribute("error", "Une erreur est survenue");
		} catch (javax.ejb.EJBException e) {
			request.setAttribute("error", "Cette personne n'existe pas");
		}
	}

	private void processSubmitPers(HttpServletRequest request, HttpServletResponse response) {
		request.getParameter(subPers);
		String nom = request.getParameter(txtNom);
		String prenom = request.getParameter(txtPrenom);
		String mail = request.getParameter(txtMail);
		String debut = request.getParameter(txtDebut);
		String fin = request.getParameter(txtFin);
		String equipe = request.getParameter(txtEquipe);
		request.setAttribute("nom", nom);
		request.setAttribute("prenom", prenom);
		request.setAttribute("mail", mail);
		request.setAttribute("debut", debut);
		request.setAttribute("fin", fin);
		request.setAttribute("equipe", equipe);

		if (utils.Utils.isNullOrEmpty(nom) || utils.Utils.isNullOrEmpty(prenom)
				|| utils.Utils.isNullOrEmpty(mail) || utils.Utils.isNullOrEmpty(debut)
				|| utils.Utils.isNullOrEmpty(equipe)) {
			request.setAttribute("error", "Les champs nom, prenom, mail, debut et equipe sont obligatoires");
			return;
		}

		if (!utils.Utils.isMail(mail)) {
			request.setAttribute("error", "Le mail n'est pas correct");
			return;
		}
		Date d;
		try {
			d = utils.Utils.getDate(debut);
		} catch (ParseException ex) {
			request.setAttribute("error", "La date de début est incorrecte. " + ex.getMessage());
			return;
		}
		Date f = null;
		if (!utils.Utils.isNullOrEmpty(fin)) {
			try {
				f = utils.Utils.getDate(fin);
			} catch (ParseException ex) {
				request.setAttribute("error", "La date de fin est incorrecte. " + ex.getMessage());
				return;
			}
		}

		Equipes eq = equipesFacade.find(equipe);

		Personnes p = new Personnes();
		p.setNom(nom);
		p.setPrenom(prenom);
		p.setMail(mail);
		p.setDebut(d);
		p.setFin(f);
		p.setEquipe(eq);
		try {
			personnesFacade.create(p);
			request.setAttribute("success", p.getPrenom() + " " + p.getNom() + " a bien été créé");
		} catch (javax.ejb.EJBException e) {
			request.setAttribute("error", "Erreur lors de la création : " + e.getCausedByException().getMessage());
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
