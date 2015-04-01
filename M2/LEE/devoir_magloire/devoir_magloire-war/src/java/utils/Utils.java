/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package utils;

import java.text.ParseException;
import java.util.Calendar;
import java.util.Comparator;
import java.util.Date;

/**
 * Fonctions statiques que je peux utiliser partout
 *
 * @author Jones Magloire
 */
public class Utils {

	/**
	 * @param s
	 *
	 * @return true si s est un entier positif, false sinon
	 */
	public static boolean isNumeric(String s) {
		return s.matches("\\d+");
	}

	/**
	 * @param t tableau de string contenant un nombre
	 *
	 * @return le premier nombre de t
	 *
	 * @throws IllegalArgumentException
	 */
	public static int getFirstNumeric(String[] t) throws IllegalArgumentException {
		for (String s : t) {
			if (isNumeric(s)) {
				return Integer.parseInt(s);
			}
		}
		throw new IllegalArgumentException();
	}

	/**
	 * @param n
	 *
	 * @return n formaté avec des '0' devant pour qu'on ai 3 digits
	 */
	public static String toThreeDigits(int n) {
		return (n < 10 ? "00" + n : n < 100 ? "0" + n : n) + "";
	}

	/**
	 * @param mail chaine correspondant a une adresse mail
	 *
	 * @return true si mail est une adresse mail, false sinon
	 */
	public static boolean isMail(String mail) {
		return mail.matches("[\\w.+-]+@[a-zA-Z0-9.-]+\\..*");
	}

	/**
	 * @param s string a verifier
	 *
	 * @return true si s est null ou vide, false sinon
	 */
	public static boolean isNullOrEmpty(String s) {
		return s == null || s.isEmpty();
	}

	/**
	 * @param s chaine au format date JJ/MM/AAAA
	 *
	 * @return la date correspondant a s
	 *
	 * @throws ParseException
	 */
	public static Date getDate(String s) throws ParseException {
		if (!isDate(s)) {
			throw new ParseException("Le format est : JJ/MM/AAAA ou JJ-MM-AAAA", 0);
		}
		Calendar c = Calendar.getInstance();
		String[] split = s.split("-|/");
		c.set(Integer.parseInt(split[2]), Integer.parseInt(split[1]), Integer.parseInt(split[0]));

		return c.getTime();
	}

	/**
	 * @param s chaine qu'on veut verifier
	 *
	 * @return true si s est au format date JJ/MM/AAAA false sinon
	 */
	public static boolean isDate(String s) {
		return s.matches("\\d{1,2}[/-]\\d{1,2}[/-]\\d{4}");
	}

	/**
	 * @return un comparateur de bureaux
	 */
	public static Comparator<entity.Bureaux> getBureauxComparator() {
		return (b1, b2) -> {
			int cmp = b1.getBatiment().compareTo(b2.getBatiment());
			if (cmp != 0) {
				return cmp;
			}
			cmp = Integer.compare(b1.getEtage(), b2.getEtage());
			if (cmp != 0) {
				return cmp;
			}
			return Integer.compare(b1.getNumero(), b2.getNumero());
		};
	}
}
