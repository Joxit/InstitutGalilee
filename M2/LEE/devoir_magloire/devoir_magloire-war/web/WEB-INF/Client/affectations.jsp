<%--
    Document   : affectations
    Created on : 20 nov. 2014, 22:47:49
    Author     : joxit
--%>

<%@page import="java.util.HashMap"%>
<%@page import="java.util.Map"%>
<%@page import="entity.Bureaux"%>
<%@page import="entity.Personnes"%>
<%@page import="java.util.List"%>
<%@page import="web.HtmlWriter"%>
<%@page import="entity.BureauxFacadeLocal"%>
<%@page import="entity.PersonnesFacadeLocal"%>
<%@page contentType="text/html" pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
	<head>
		<title>Gestion des bureaux</title>
		<meta charset="UTF-8">
		<link media="all" type="text/css" href="style.css" rel="stylesheet" />
		<meta name="viewport" content="width=device-width, initial-scale=1.0">
	</head>
    <body>
		<div class="container">
			<%@include file="../menus/clientHeader.jsp" %>
			<div id="body">
				<h1>Liste des personnes</h1>
				<%
					HashMap<Bureaux, List<Personnes>> hm = (HashMap<Bureaux, List<Personnes>>) request.getAttribute("bureaux");
					for (Bureaux b : hm.keySet()) {
						List<Personnes> lp = hm.get(b);
						if (lp != null && !lp.isEmpty()) {%>
				<h3>Bureau: <%=HtmlWriter.bureau(b)%></h3>

				<table class="list">
					<tr><td>Nom</td><td>Prenom</td><td>Equipe</td></tr>
					<%for (Personnes p : lp) {%>
					<tr><td><%=p.getNom()%></td>
						<td><%=p.getPrenom()%></td>

						<td><%=(p.getEquipe() != null ? p.getEquipe().getEquipeId() : "")%></td>
					</tr>
					<%}%>
				</table>
				<%} else {%>
				<h3>Bureau: <%=web.HtmlWriter.bureau(b)%> vide</h3>
				<%}
					}%>
			</div>
		</div>
    </body>
</html>
