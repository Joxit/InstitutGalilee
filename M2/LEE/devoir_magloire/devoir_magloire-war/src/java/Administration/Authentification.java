/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Administration;

import entity.Responsables;
import java.util.List;
import javax.servlet.http.Cookie;

/**
 *
 * @author joxit
 */
public class Authentification {

	protected static final String cookieLogin = "login";
	protected static final String cookiePassword = "password";

	protected static boolean hasLoginAndPasswordCookie(Cookie[] cookies) {
		boolean log = false;
		boolean pwd = false;
		if (cookies != null) {
			for (Cookie c : cookies) {
				switch (c.getName()) {
					case cookieLogin:
						log = true;
						break;
					case cookiePassword:
						pwd = true;
						break;
				}
			}
		}
		return log && pwd;
	}

	public static Cookie[] getLoginAndPasswordCookie(Cookie[] cookies) {
		Cookie[] res = new Cookie[2];
		if (cookies != null) {
			for (Cookie c : cookies) {
				switch (c.getName()) {
					case cookieLogin:
						res[0] = c;
						break;
					case cookiePassword:
						res[1] = c;
						break;
				}
			}
		}
		return res;
	}

	public static boolean hasCorrectPassword(Cookie[] cookies, List<Responsables> lr) {
		if (cookies != null && cookies[0] != null && cookies[1] != null) {
			for (Responsables r : lr) {
				if (r.getIdentifiant().equals(cookies[0].getValue())
						&& r.getMotDePasse().equals(cookies[1].getValue())) {
					return true;
				}
			}
		}
		return false;
	}
}
