<%--
    Document   : responsablesFacade
    Created on : 23 nov. 2014, 22:25:33
    Author     : joxit
--%>

<%@page import="javax.ejb.EJB"%>
<%@page import="javax.naming.NamingException"%>
<%@page import="entity.MessagesFacadeLocal"%>
<%@page import="javax.naming.InitialContext"%>
<%@page import="javax.naming.Context"%>
<%@page import="entity.ResponsablesFacadeLocal"%>
<%! @EJB
	private ResponsablesFacadeLocal responsablesFacade;
%>
<%@page contentType="text/html" pageEncoding="UTF-8"%>
<%  try {
		Context c = new InitialContext();
		responsablesFacade = (ResponsablesFacadeLocal) c.lookup("java:app/devoir_magloire-ejb/ResponsablesFacade!entity.ResponsablesFacadeLocal");
	} catch (NamingException ne) {
		throw new RuntimeException(ne);
	}
%>
