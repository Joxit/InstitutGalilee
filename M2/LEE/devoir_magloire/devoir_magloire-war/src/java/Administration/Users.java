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
 * Servlet controlant la page de l'administration des personnes. Permet aux
 * responsables de créer de nouvelles personnes ainsi que de voir les
 * informations de celles qui existent déjà. La jsp associé à cette servlet est
 * /WEB-INF/Administration/utilisateurs.jsp
 *
 * Les attributs final public static de cette classe sont référencés dans la jsp
 * pour avoir une armonie dans les identifiants des parametres.
 *
 * @author Jones Magloire
 * @version 2 (2/12/14)
 */
@WebServlet(name = "Admin.Utilisateurs", urlPatterns = {"/Admin.Utilisateurs"})
public class Users extends HttpServlet {

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
			processSubmitPers(request);
		}
		if (request.getParameter(delPers) != null) {
			processDelPers(request);
		}
		request.setAttribute("personnes", personnesFacade.findAll());
		request.setAttribute("equipes", equipesFacade.findAll());

		getServletContext().getRequestDispatcher("/WEB-INF/Administration/utilisateurs.jsp").forward(request, response);
	}

	/**
	 * Precessus pour la requete HTTP <code>POST</code> pour la suppression
	 * d'une personne. Récupère l'identifiant de la personnes concerné et la
	 * supprimer de la base de données. Affiche un message de reussite a
	 * l'utilisateur si tout ce passe bien ou une erreur sinon.
	 *
	 * @param request servlet request où l'on mettra le message dans l'attribut
	 *                success si tout ce passe bien ou un dans error s'il y a un
	 *                probleme
	 */
	private void processDelPers(HttpServletRequest request) {
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

	/**
	 * Precessus pour la requete HTTP <code>POST</code> pour l'ajout d'une
	 * personnes. Verifie les champs obligatoires comme le nom, prenom, mail,
	 * l'eqiope et la date de début avant d'ajouter la personne dans la base de
	 * donnée. Si une erreur survient, l'utilisateur sera informé via les
	 * attributs error et success de la jsp
	 *
	 *
	 * @param request servlet request où l'on mettra le message dans l'attribut
	 *                success si tout ce passe bien ou un dans error s'il y a un
	 *                probleme
	 */
	private void processSubmitPers(HttpServletRequest request) {
		String nom = request.getParameter(txtNom);
		String prenom = request.getParameter(txtPrenom);
		String mail = request.getParameter(txtMail);
		String debut = request.getParameter(txtDebut);
		String fin = request.getParameter(txtFin);
		String equipe = request.getParameter(txtEquipe);
		// on remet en état la page pour ne pas que l'utilisateur rentre a nouveau les memes infos
		request.setAttribute("nom", nom);
		request.setAttribute("prenom", prenom);
		request.setAttribute("mail", mail);
		request.setAttribute("debut", debut);
		request.setAttribute("fin", fin);
		request.setAttribute("equipe", equipe);

		// Gestion des erreurs
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

		// creation de la personnes
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
