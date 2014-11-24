<%--
    Document   : index
    Created on : 20 nov. 2014, 23:43:09
    Author     : joxit
--%>

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
		<%
			final String txtLogin = "txtLogin";
			final String txtPassword = "txtPassword";
			final String subLogin = "subLogin";
		%>
    </head>
    <body>
        <div class="container">
            <div id="body">
				<%if (request.getParameter(subLogin) != null) {
						List<Responsables> lr = responsablesFacade.findAll();
						String login = request.getParameter(txtLogin);
						String password = request.getParameter(txtPassword);
						for (Responsables r : lr) {
							if (r.getIdentifiant().equals(login)
									&& r.getMotDePasse().equals(password)) {
								isLogged = true;
								Cookie log = new Cookie("login", login);
								Cookie psw = new Cookie("password", password);
								response.addCookie(log);
								response.addCookie(psw);
								break;
							}
						}
					}%>
				<%@include file="WEB-INF/menus/adminHeader.jsp" %>
				<%if (!isLogged) {%>
				<form method="POST">
					<table>
						<tr><td>Login: </td><td><input type="text" name="<%=txtLogin%>"></td></tr>
						<tr><td>Mot de passe: </td><td><input type="password" name="<%=txtPassword%>"></td></tr>
					</table>
					<input type="submit" name="<%=subLogin%>"><br/>
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
