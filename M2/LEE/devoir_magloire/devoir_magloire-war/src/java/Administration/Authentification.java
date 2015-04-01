/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Administration;

import java.util.ArrayList;
import javax.servlet.http.HttpServletRequest;

/**
 * Classe gerant l'authentification des responsables. On stoque les identifiants
 * des sessions dans la liste ici.
 *
 * @author Jones Magloire
 * @version 2 (2/12/14)
 */
public class Authentification {

	private static final ArrayList<String> lesSessions = new ArrayList<>();

	/**
	 * @param request On ajoute la session de cette requete a la liste
	 */
	public static void add(HttpServletRequest request) {
		lesSessions.add(request.getSession().getId());
	}

	/**
	 * @param request
	 *
	 * @return true si l'id de sessions de cette requete est dans la liste.
	 */
	public static boolean contains(HttpServletRequest request) {
		return lesSessions.contains(request.getSession().getId());
	}

	/**
	 * @param request supprimme cette session ID
	 */
	public static void remove(HttpServletRequest request) {
		lesSessions.remove(request.getSession().getId());
	}
}
