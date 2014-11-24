<%--
    Document   : adminadduser
    Created on : 23 nov. 2014, 23:03:23
    Author     : joxit
--%>

<%@page import="entity.Bureaux"%>
<%@page import="web.HtmlWriter"%>
<%@page import="entity.Personnes"%>
<%@page import="javax.ejb.EJB"%>
<%@page import="entity.PersonnesFacadeLocal"%>
<%@page import="entity.BureauxFacadeLocal"%>
<%!
	@EJB
	private BureauxFacadeLocal bureauxFacade;
	@EJB
	private PersonnesFacadeLocal personnesFacade;
%>
<%@page contentType="text/html" pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
    <head>
        <title>Administration des bureaux</title>
        <meta charset="UTF-8">
        <link media="all" type="text/css" href="style.css" rel="stylesheet" />
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
		<% try {
				Context c = new InitialContext();
				bureauxFacade = (BureauxFacadeLocal) c.lookup("java:app/devoir_magloire-ejb/BureauxFacade!entity.BureauxFacadeLocal");
				personnesFacade = (PersonnesFacadeLocal) c.lookup("java:app/devoir_magloire-ejb/PersonnesFacade!entity.PersonnesFacadeLocal");
			} catch (NamingException ne) {
				throw new RuntimeException(ne);
			}
		%>
    </head>
    <body>
		<div class="container">
            <div id="body">
				<%@include file="WEB-INF/islogged.jsp" %>

			</div>
		</div>
    </body>
</html>
