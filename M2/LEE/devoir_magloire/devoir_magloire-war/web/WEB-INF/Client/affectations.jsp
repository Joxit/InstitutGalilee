<%--
    Document   : affectations
    Created on : 20 nov. 2014, 22:47:49
    Author     : Jones Magloire
--%>

<%@page import="java.util.Map"%>
<%@page import="entity.Bureaux"%>
<%@page import="entity.Personnes"%>
<%@page import="java.util.List"%>
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
				<p>Vous pouvez voir ici la liste des salles avec les personnes qui y sont affectés.</p>
				<h1>Liste des personnes</h1>
				<%for (Map.Entry<Bureaux, List<Personnes>> entry
							: ((Map<Bureaux, List<Personnes>>) request.getAttribute("bureaux")).entrySet()) {
						if (entry.getValue() != null && !entry.getValue().isEmpty()) {%>
				<h3>Bureau: <%=entry.getKey().toFormatString()%></h3>

				<table class="list">
					<tr><td>Nom</td><td>Prenom</td><td>Equipe</td></tr>
					<%for (Personnes p : entry.getValue()) {%>
					<tr><td><%=p.getNom()%></td>
						<td><%=p.getPrenom()%></td>
						<td><%=(p.getEquipe() != null ? p.getEquipe().getEquipeId() : "")%></td>
					</tr>
					<%}%>
				</table>
				<%} else {%>
				<h3>Bureau: <%=entry.getKey().toFormatString()%> vide</h3>
				<%}
					}%>
			</div>
		</div>
    </body>
</html>
