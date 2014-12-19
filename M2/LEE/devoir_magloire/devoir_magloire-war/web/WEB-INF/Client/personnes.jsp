<%--
    Document   : personnes
    Created on : 15 nov. 2014, 11:06:31
    Author     : Jones Magloire
--%>

<%@page import="java.util.List"%>
<%@page import="entity.Personnes"%>
<%@page import="entity.Bureaux"%>
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
			<div id="body">
				<%@include file="../menus/clientHeader.jsp" %>
				<p>Voici la liste de toutes les personnes inscrites rangé par nom.</p>
				<h1>Liste des personnes</h1>
				<table class="list">
					<tr><td>ID</td><td>Nom</td><td>Prenom</td><td>Bureau</td><td>Mail</td><td>Equipe</td></tr>
					<% for (Personnes p : (List<Personnes>) request.getAttribute("personnes")) {%>
					<tr><td> <%=p.getPersonneId()%></td>
						<td><%=p.getNom()%></td>
						<td><%=p.getPrenom()%></td>
						<td><%=(p.getBureau() != null ? p.getBureau().toFormatString() : "")%></td>
						<td><%=(p.getMail() != null ? p.getMail() : "")%></td>
						<td><%=(p.getEquipe() != null ? p.getEquipe().getEquipeId() : "")%></td>
					</tr>
					<%}%>
				</table>
			</div>
		</div>
	</body>
</html>
