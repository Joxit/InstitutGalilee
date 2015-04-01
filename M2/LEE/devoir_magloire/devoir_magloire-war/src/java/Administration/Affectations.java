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
import java.util.List;
import java.util.stream.Collectors;
import javax.ejb.EJB;
import javax.mail.MessagingException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

/**
 * Servlet controlant l'administration des affectations. La jsp associée est
 * /WEB-INF/Administration/affectations.jsp
 *
 * Les attributs final public static de cette classe sont référencés dans la jsp
 * pour avoir une armonie dans les identifiants des parametres.
 *
 * @author Jones Magloire
 * @version 2 (2/12/14)
 */
@WebServlet(name = "Admin.Affectations", urlPatterns = {"/Admin.Affectations"})
public class Affectations extends HttpServlet {

	@EJB
	private BureauxFacadeLocal bureauxFacade;
	@EJB
	private PersonnesFacadeLocal personnesFacade;

	/**
	 * Identifiant du bonton submit pour affecter un bureau a une personne
	 */
	public static final String subAffect = "subAddDeskToPers";

	/**
	 * Identifiant du bouton submit pour activer ou desactiver la generation des
	 * bureaux en fonction de l'equipe
	 */
	public static final String subGen = "subGenDeskToPers";

	/**
	 * Identifiant de la zone de texte/select pour la personne a affecter
	 */
	public static final String txtPers = "txtAddPersOfDesk";

	/**
	 * Identifiant de la zone de texte/select pour le bureau a affecter
	 */
	public static final String txtDesk = "txtAddDeskOfPers";

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
		boolean isGen = false;
		if (request.getParameter(subAffect) != null) {
			for (String s : request.getParameterValues(subAffect)) {
				switch (s) {
					case "true":
						isGen = true;
						break;
					case "Affecter":
						processAffect(request);
						break;
				}
			}
		}
		String s = request.getParameter(subGen);
		if ((isGen && s == null) || (s != null && s.equals("Generer"))) {
			processGen(request);
			request.setAttribute("subGen", "Defaut");
		} else {
			processDefaut(request);
			request.setAttribute("subGen", "Generer");
		}
		request.setAttribute("personnes", personnesFacade.findAllSortedByName());
		getServletContext()
				.getRequestDispatcher("/WEB-INF/Administration/affectations.jsp")
				.forward(request, response);
	}

	/**
	 * Processus pour la requete HTTP par defaut, il sauvegarde l'état de la
	 * zone de texte de l'identifiant de la personne et donne la liste de tous
	 * les bureaux existant sans verifier s'ils sont vides ou pas.
	 *
	 * @param request servlet request où l'on mettra le message dans l'attribut
	 *                success si tout ce passe bien ou un dans error s'il y a un
	 *                probleme
	 */
	private void processDefaut(HttpServletRequest request) {
		try {
			int persId;
			String pers = request.getParameter(txtPers);
			persId = Integer.parseInt(pers);
			request.setAttribute("txtPers", persId);
		} catch (IllegalArgumentException e) {
		}

		List<entity.Bureaux> lb = bureauxFacade.findAll().stream()
				.sorted(utils.Utils.getBureauxComparator())
				.collect(Collectors.toList());
		request.setAttribute("bureaux", lb);
	}

	/**
	 * Processus pour la requete <code>POST</code> de l'affectation d'une
	 * personne a un bureau. Verifie si l'identifiant de la personne est du
	 * bureaux sont corrects. S'ils sont corrects, on ajoute la personne dans le
	 * bureau selectionné. Dans le cas contraire ou si le bureau est deja plein
	 * on renvoie une erreur au client.
	 *
	 * @param request servlet request où l'on mettra le message dans l'attribut
	 *                success si tout ce passe bien ou un dans error s'il y a un
	 *                probleme
	 */
	private void processAffect(HttpServletRequest request) {
		int deskId;
		int persId;
		try {
			String desk = request.getParameter(txtDesk);
			deskId = Integer.parseInt(desk);
			String pers = request.getParameter(txtPers);
			persId = Integer.parseInt(pers);
		} catch (IllegalArgumentException e) {
			request.setAttribute("error", "Vous voulez dejouer mon select ? Mauvais identifiants.");
			return;
		}

		request.setAttribute("txtPers", persId);
		entity.Bureaux b = bureauxFacade.find(deskId);
		if (b == null) {
			request.setAttribute("error", "Ce bureau n'existe pas");
			return;
		}
		Personnes p = personnesFacade.find(persId);
		if (p == null) {
			request.setAttribute("error", "Cette personne n'existe pas");
			return;
		}

		if (b.getLimite() > personnesFacade.findByBureau(b).size()) {
			p.setBureau(b);
			personnesFacade.edit(p);

			try {
				mail.SendMail.send(p.getMail(), "Changement d'affectation", "Vous avez été affecté au bureau " + b.toFormatString());
			} catch (MessagingException ex) {
				request.setAttribute("error", "Le mail n'a pas été envoyé.</br>" + ex.getMessage());
			}
			request.setAttribute("success", p.toNomPrenomIdString() + " ajouté au bureau " + b.toFormatString());
		} else {
			request.setAttribute("error", "Ce bureau est plein");
		}
	}

	/**
	 * Precessus pour la requete <code>POST</code> pour la demande de generation
	 * des bureaux en fonction des equipes de la personne selectionné. On
	 * verifie si l'identifiant de la personne est correct, puis on recupère
	 * tous les bureaux des personnes qui sont dans son équipe.
	 *
	 * @param request servlet request où l'on mettra le message dans l'attribut
	 *                success si tout ce passe bien ou un dans error s'il y a un
	 *                probleme
	 */
	private void processGen(HttpServletRequest request) {
		int persId;
		try {
			String pers = request.getParameter(txtPers);
			persId = Integer.parseInt(pers);
		} catch (IllegalArgumentException e) {
			request.setAttribute("error", "Vous voulez dejouer mon select ? Mauvais identifiants.");
			return;
		}

		Personnes pers = personnesFacade.find(persId);
		if (pers == null) {
			request.setAttribute("error", "Cette personne n'existe pas");
			return;
		}

		List<entity.Bureaux> lb = bureauxFacade.findByEquipe(pers.getEquipe()).stream()
				.sorted(utils.Utils.getBureauxComparator())
				.collect(Collectors.toList());
		// attribut pour attester qu'on est en mode generation
		request.setAttribute("gen", "true");
		request.setAttribute("txtPers", persId);
		request.setAttribute("bureaux", lb);
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
