<%--
    Document   : messagesFacade
    Created on : 23 nov. 2014, 22:24:12
    Author     : joxit
--%>

<%@page import="javax.ejb.EJB"%>
<%@page import="javax.naming.NamingException"%>
<%@page import="entity.MessagesFacadeLocal"%>
<%@page import="javax.naming.InitialContext"%>
<%@page import="javax.naming.Context"%>
<%! @EJB
	private MessagesFacadeLocal messagesFacade;
%>
<%@page contentType="text/html" pageEncoding="UTF-8"%>
<%  try {
		Context c = new InitialContext();
		messagesFacade = (MessagesFacadeLocal) c.lookup("java:app/devoir_magloire-ejb/MessagesFacade!entity.MessagesFacadeLocal");
	} catch (NamingException ne) {
		throw new RuntimeException(ne);
	}
%>
