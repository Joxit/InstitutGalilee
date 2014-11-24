<%--
    Document   : personnes
    Created on : 15 nov. 2014, 11:06:31
    Author     : joxit
--%>

<%@page import="javax.ejb.EJB"%>
<%@page import="java.util.ArrayList"%>
<%@page import="entity.PersonnesFacade"%>
<%@page import="javax.naming.InitialContext"%>
<%@page import="javax.naming.NamingException"%>
<%@page import="javax.naming.Context"%>
<%@page import="entity.PersonnesFacadeLocal"%>
<%@page import="entity.Personnes"%>
<%@page import="entity.Bureaux"%>
<%! @EJB
	private PersonnesFacadeLocal personnesFacade;
%>
<%@page contentType="text/html" pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
	<head>
		<title>Gestion des bureaux</title>
		<meta charset="UTF-8">
		<link media="all" type="text/css" href="style.css" rel="stylesheet" />
		<meta name="viewport" content="width=device-width, initial-scale=1.0">
		<% try {
				Context c = new InitialContext();
				personnesFacade = (PersonnesFacadeLocal) c.lookup("java:app/devoir_magloire-ejb/PersonnesFacade!entity.PersonnesFacadeLocal");
			} catch (NamingException ne) {
				throw new RuntimeException(ne);
			}
		%>
	</head>
	<body>
		<div class="container">
			<%@include file="WEB-INF/menus/clientHeader.jsp" %>
			<div id="body">
				<h1>Liste des personnes</h1>
				<table class="list">
					<tr><td>ID</td><td>Nom</td><td>Prenom</td><td>Bureau</td><td>Mail</td><td>Equipe</td></tr>
					<% for (Personnes p : personnesFacade.findAll()) {%>
					<tr><td> <%=p.getPersonneId()%></td>
						<td><%=p.getNom()%></td>
						<td><%=p.getPrenom()%></td>
						<td><%=web.HtmlWriter.bureau(p.getBureau())%></td>
						<td><%=(p.getMail() != null ? p.getMail() : "")%></td>
						<td><%=(p.getEquipe() != null ? p.getEquipe().getEquipeId() : "")%></td>
					</tr>
					<%}%>
				</table>
			</div>
		</div>
	</body>
</html>
