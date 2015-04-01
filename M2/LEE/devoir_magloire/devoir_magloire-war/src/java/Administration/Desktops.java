/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Administration;

import entity.Bureaux;
import entity.BureauxFacadeLocal;
import entity.PersonnesFacadeLocal;
import java.io.IOException;
import java.util.HashMap;
import javax.ejb.EJB;
import javax.ejb.EJBException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

/**
 * Servlet controlant la page de l'administration des bureaux. Permet aux
 * responsables de créer de nouveaux bureaux ainsi que voir les informations les
 * concernants comme leur limite et le nombre de personnes y étant. La jsp
 * associée à cette servlet est /WEB-INF/Administration/bureaux.jsp
 *
 * Les attributs final public static de cette classe sont référencés dans la jsp
 * pour avoir une armonie dans les identifiants des parametres.
 *
 * @author Jones Magloire
 * @version 2 (2/12/14)
 */
@WebServlet(name = "Admin.Bureaux", urlPatterns = {"/Admin.Bureaux"})
public class Desktops extends HttpServlet {

	@EJB
	private PersonnesFacadeLocal personnesFacade;

	@EJB
	private BureauxFacadeLocal bureauxFacade;
	/**
	 * Identifiant de la zone de texte pour le batiment du bureau
	 */
	final static public String txtBat = "txtBat";
	/**
	 * Identifiant de la zone de texte pour l'étage du bureau
	 */
	final static public String txtEtage = "txtEtage";
	/**
	 * Identifiant de la zone de texte pour les digits du bureau
	 */
	final static public String txtDigits = "txtDigits";
	/**
	 * Identifiant de la zone de texte pour le nombre de place possible dans le
	 * bureau
	 */
	final static public String txtPlaces = "txtPlaces";

	/**
	 * Identifiant du bouton pour ajouter une liste de bureaux
	 */
	final static public String subDesk = "subDesk";
	/**
	 * Identifiant du bouton pour supprimer un bureau
	 */
	final static public String subDelDesk = "subDelDesk";

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
			processSubmitDesk(request);
		} else {
			// Suppression de bureau
			String[] txt = request.getParameterValues(subDelDesk);
			if (txt != null) {
				try {
					int res = utils.Utils.getFirstNumeric(txt);
					Bureaux b = bureauxFacade.find(res);
					bureauxFacade.remove(b);
					request.setAttribute("success", b.toFormatString() + " a bien été supprimé");
				} catch (IllegalArgumentException e) {
					request.setAttribute("error", "Une erreur est survenue");
				} catch (javax.ejb.EJBException e) {
					request.setAttribute("error", "Cette bureau n'existe pas");
				}
			}
		}
		HashMap<entity.Bureaux, Integer> hm = new HashMap<>();
		bureauxFacade.findAll().stream().forEach(b -> {
			hm.put(b, personnesFacade.findByBureau(b).size());
		});

		request.setAttribute("bureauxhash", hm);
		getServletContext().getRequestDispatcher("/WEB-INF/Administration/bureaux.jsp").forward(request, response);
	}

	/**
	 * Processus pour la requete HTTP <code>POST</code> de l'ajout d'un bureau
	 * par un responsable. Verifie l'exactitude des champs (si on a bien des
	 * nombres/lettres au bon endroit) et envoie un message de confirmation au
	 * client si tout se passe bien.
	 *
	 * @param request servlet request où l'on mettra le message dans l'attribut
	 *                success si tout ce passe bien ou un dans error s'il y a un
	 *                probleme
	 */
	private void processSubmitDesk(HttpServletRequest request) {
		String bat = request.getParameter(txtBat);
		String etage = request.getParameter(txtEtage);
		String digits = request.getParameter(txtDigits);
		String places = request.getParameter(txtPlaces);

		// pour remettre en etat
		request.setAttribute("bat", bat);
		request.setAttribute("etage", etage);

		// Gestion des erreurs
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

		// Creation du bureau
		entity.Bureaux b = new entity.Bureaux();
		b.setBatiment(bat.charAt(0));
		b.setEtage(Integer.parseInt(etage));
		b.setNumero(Integer.parseInt(digits));
		b.setLimite(Integer.parseInt(places));
		try {
			bureauxFacade.create(b);
			request.setAttribute("success", "Bureau " + b.toFormatString() + " créé");
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
