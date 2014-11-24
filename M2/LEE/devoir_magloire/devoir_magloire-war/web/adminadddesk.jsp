<%--
    Document   : adminadddesk
    Created on : 23 nov. 2014, 23:04:43
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
			final String txtBat = "txtBat";
			final String txtEtage = "txtEtage";
			final String txtDigits = "txtDigits";
			final String txtPlaces = "txtPlaces";
			final String subDesk = "subDesk";
		%>
    </head>
    <body>
		<div class="container">
            <div id="body">
				<%@include file="WEB-INF/islogged.jsp" %>
				<% if (request.getParameter(subDesk) != null) {
						Bureaux b = new Bureaux();
						try {
							b.setBatiment(request.getParameter(txtBat).charAt(0));
							b.setEtage(Integer.parseInt(request.getParameter(txtEtage)));
							b.setNumero(Integer.parseInt(request.getParameter(txtDigits)));
							b.setLimite(Integer.parseInt(request.getParameter(txtPlaces)));
							bureauxFacade.create(b);
						} catch (NumberFormatException e) {
				%>
				<h2 class='error'>Un nombre était atendu</h2>
				<%} catch (NullPointerException | StringIndexOutOfBoundsException e) {%>
				<h2 class='error'>Remplissez tous les champs</h2>
				<%} catch (Exception e) {%>
				<h2 class='error'>Une erreur est survenue</h2>
				<%
							e.printStackTrace();
						}
					}
				%>
				<form method='POST'>
					<table>
						<tr>
							<td>Batiment (A ou B):</td>
							<td><input type='text' name='<%=txtBat%>'></td>
						</tr>
						<tr>
							<td>Etage:</td>
							<td><input type='text' name='<%=txtEtage%>'></td>
						</tr>
						<tr>
							<td>3 Digits:</td>
							<td><input type='text' name='<%=txtDigits%>'></td>
						</tr>
						<tr>
							<td>Places:</td>
							<td><input type='text' name='<%=txtPlaces%>'></td>
						</tr>
						<tr>
							<td></td>
							<td><input type='submit' value='Ajouter' name='<%=subDesk%>'></td>
						</tr>
					</table>
				</form>
				<h1>Liste des bureaux</h1>
				<table class="list">
					<tr>
						<td>ID</td><td>Batiment</td><td>Etage</td>
						<td>Numero</td><td>Limite</td>
					</tr>
					<% for (Bureaux b : bureauxFacade.findAll()) {%>
					<tr>
						<td><%=b.getBureauId()%></td>
						<td><%=b.getBatiment()%></td>
						<td><%=b.getEtage()%></td>
						<td><%=utils.Utils.toThreeDigits(b.getNumero())%></td>
						<td><%=b.getLimite()%></td>
					</tr>
					<%}%>
				</table>
			</div>
		</div>
    </body>
</html>
