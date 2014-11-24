/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package utils;

import entity.Bureaux;

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
}
