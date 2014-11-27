/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package utils;

import entity.Bureaux;
import java.text.ParseException;
import java.util.Calendar;
import java.util.Date;

/**
 *
 * @author joxit
 */
public class Utils {

	public static boolean isNumeric(String s) {
		return s.matches("[-+]?\\d*\\.?\\d+");
	}

	public static int getFirstNumeric(String[] t) throws IllegalArgumentException {
		for (String s : t) {
			if (isNumeric(s)) {
				return Integer.parseInt(s);
			}
		}
		throw new IllegalArgumentException();
	}

	public static String bureauFormat(Bureaux b) {
		if (b != null) {
			return (String.valueOf(b.getBatiment())
					+ String.valueOf(b.getEtage()) + " "
					+ toThreeDigits(b.getNumero()));
		} else {
			return "";
		}
	}

	public static String toThreeDigits(int n) {
		return (n < 10 ? "00" + n : n < 100 ? "0" + n : n) + "";
	}

	public static boolean isMail(String mail) {
		return mail.matches("[\\w.+-]+@[a-zA-Z0-9.-]+\\..*");
	}

	public static boolean isNullOrEmpty(String s) {
		return s == null || s.isEmpty();
	}

	public static Date getDate(String s) throws ParseException {
		if (!isDate(s)) {
			throw new ParseException("Le format est : JJ/MM/YYYY ou JJ-MM-YYY", 0);
		}
		Calendar c = Calendar.getInstance();
		String[] split = s.split("-|/");
		c.set(Integer.parseInt(split[2]), Integer.parseInt(split[1]), Integer.parseInt(split[0]));

		return c.getTime();
	}

	public static boolean isDate(String s) {
		return s.matches("\\d{1,2}[/-]\\d{1,2}[/-]\\d{4}");
	}
}
