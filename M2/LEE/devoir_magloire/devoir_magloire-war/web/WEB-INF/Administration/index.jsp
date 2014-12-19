<%--
    Document   : index
    Created on : 20 nov. 2014, 23:43:09
    Author     : Jones Magloire
--%>

<%@page import="Administration.Admin"%>
<%@page import="entity.Responsables"%>
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
        <title>Administration des bureaux</title>
        <meta charset="UTF-8">
        <link media="all" type="text/css" href="style.css" rel="stylesheet" />
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
    </head>
    <body>
        <div class="container">
            <div id="body">
				<%@include file="../menus/adminHeader.jsp" %>
				<h3 class='success'>${success}</h3>
				<h3 class='error'>${error}</h3>
				<%if (!Authentification.contains(request)) {%>
				<h1>Connexion pour les responsables</h1>
				<form method="POST">
					<table>
						<tr>
							<td>Login: </td>
							<td><input type="text" name="<%=Admin.txtLogin%>"></td>
						</tr>
						<tr>
							<td>Mot de passe: </td>
							<td><input type="password" name="<%=Admin.txtPassword%>" autocomplete="off"></td>
						</tr>
					</table>
					<input type="submit" name="<%=Admin.subLogin%>"><br/>
				</form>
				<%} else {%>
				<h1>Bienvenue dans la partie Administration du logiciel</h1>
				<h2>Que souhaitez vous faire ?</h2>
				<p>Vous pouvez choisir les actions que vous souhaitez
					via le menu en survolant 'Administrateur'. Vous pouvez voir la liste
					et ajouter des personnes qui sont dans nos locaux, les bureaux,
					affecter un bureau à une personne et lire les messages des utilisateurs.</p>
					<%}%>
            </div>
        </div>
    </body>
</html>
