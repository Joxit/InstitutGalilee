<%--
    Document   : adminadduser
    Created on : 23 nov. 2014, 23:03:23
    Author     : joxit
--%>

<%@page import="entity.Equipes"%>
<%@page import="Administration.Users"%>
<%@page import="java.util.List"%>
<%@page import="entity.Bureaux"%>
<%@page import="entity.Personnes"%>
<%@page contentType="text/html" pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
    <head>
        <title>Administration des bureaux</title>
        <meta charset="UTF-8">
        <link media="all" type="text/css" href="style.css" rel="stylesheet" />
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
    </head>
    <body>
		<div class="container">
            <div id="body">
				<%@include file="../islogged.jsp" %>
				<h3 class='success'>${success}</h3>
				<h3 class='error'>${error}</h3>
				<p>Vous pouvez ajouter ici des personnes, les erreurs de saisie que vous allez commetres seront gérés.
					Il y a ensuite la liste des personnes de la base de donnée rangé par ID.
					Vous pouvez également supprimer des personnes. Si vous voulez affecter un bureau a la personne que
					vous venez de créer, il faut aller dans le menu affecter bureau, cela se fait donc en 2 etapes.
				</p>
				<form method='POST'>
					<table>
						<tr>
							<td>Nom</td>
							<td><input type='text' value="${nom}" name='<%=Users.txtNom%>'></td>
						</tr>
						<tr>
							<td>Prenom</td>
							<td><input type='text' value="${prenom}" name='<%=Users.txtPrenom%>'></td>
						</tr>
						<tr>
							<td>Mail</td>
							<td><input type='text' value="${mail}" name='<%=Users.txtMail%>'></td>
						</tr>
						<tr>
							<td>Debut</td>
							<td><input type='text' value="${debut}" name='<%=Users.txtDebut%>'></td>
						</tr>
						<tr>
							<td>Fin</td>
							<td><input type='text' value="${fin}" name='<%=Users.txtFin%>'></td>
						</tr>
						<tr>
							<td>Equipe</td>
							<td>
								<select name='<%=Users.txtEquipe%>'>
									<% for (Equipes e : (List<entity.Equipes>) request.getAttribute("equipes")) {
											String selected = (String) request.getAttribute("equipe");
											if (selected != null && selected.equals(e.getEquipeId())) {
												selected = "selected";
											} else {
												selected = "";
											}%>
									<option value="<%=e.getEquipeId()%>" <%=selected%>><%=e.getEquipeId()%></option>
									<%}%>
								</select>
							</td>
						</tr>
						<tr>
							<td></td>
							<td><input type='submit' value='Ajouter' name='<%=Users.subPers%>'></td>
						</tr>
					</table>
				</form>

				<h1>Liste des personnes</h1>
				<table class="list">
					<tr><td>ID</td><td>Nom</td><td>Prenom</td><td>Bureau</td>
						<td>Mail</td><td>Equipe</td><td></td></tr>
						<% for (Personnes p : (List<Personnes>) request.getAttribute("personnes")) {%>
						<% boolean isAdmin = !p.getResponsablesCollection().isEmpty();%>
					<tr><td> <%=p.getPersonneId()%></td>
						<td><%=p.getNom()%></td>
						<td><%=p.getPrenom()%></td>
						<td><%=(p.getBureau() != null ? p.getBureau().toFormatString() : "")%></td>
						<td><%=(p.getMail() != null ? p.getMail() : "")%></td>
						<td><%=(p.getEquipe() != null ? p.getEquipe().getEquipeId() : "")%></td>
						<td><form method="POST">
								<% if (!isAdmin) {%>
								<input type="submit" value="x" name="<%=Users.delPers%>">
								<input type="hidden" value="<%=p.getPersonneId()%>" name="<%=Users.delPers%>">
								<%} else {%>Admin<%}%>
							</form></td>
					</tr>
					<%}%>
				</table>
			</div>
		</div>
    </body>
</html>
