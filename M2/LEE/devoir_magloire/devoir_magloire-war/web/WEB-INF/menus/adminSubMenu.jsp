<%--
    Document   : adminSubMenu
    Created on : 20 nov. 2014, 22:03:07
    Author     : joxit
--%>

<%@page import="javax.naming.InitialContext"%>
<%@page import="javax.naming.NamingException"%>
<%@page import="javax.naming.Context"%>
<%@page import="Administration.Authentification"%>
<%@page import="entity.ResponsablesFacadeLocal"%>
<%@page import="javax.ejb.EJB"%>
<%! @EJB
	private ResponsablesFacadeLocal responsablesFacade;
	private boolean isLogged = false;
%>
<%@page contentType="text/html" pageEncoding="UTF-8"%>
<%  try {
		Context c = new InitialContext();
		responsablesFacade = (ResponsablesFacadeLocal) c.lookup("java:app/devoir_magloire-ejb/ResponsablesFacade!entity.ResponsablesFacadeLocal");
	} catch (NamingException ne) {
		throw new RuntimeException(ne);
	}
	Cookie[] c = Authentification.getLoginAndPasswordCookie(request.getCookies());
	if (Authentification.hasCorrectPassword(c, responsablesFacade.findAll())) {
		isLogged = true;%>
<ul>
	<li><a href="adminadduser.jsp">Ajouter personne</a></li>
	<li><a href="adminadddesk.jsp">Ajouter Bureau</a></li>
	<li><a href="adminaffect.jsp">Affecter Bureau</a></li>
	<li><a href="adminreadmsg.jsp">Lire Messages</a></li>
</ul>
<%}%>
