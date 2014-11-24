<%--
    Document   : affectations
    Created on : 20 nov. 2014, 22:47:49
    Author     : joxit
--%>

<%@page import="entity.Bureaux"%>
<%@page import="entity.Personnes"%>
<%@page import="java.util.List"%>
<%@page import="web.HtmlWriter"%>
<%@page import="entity.BureauxFacadeLocal"%>
<%@page import="javax.naming.InitialContext"%>
<%@page import="javax.ejb.EJB"%>
<%@page import="entity.PersonnesFacadeLocal"%>
<%@page import="javax.naming.NamingException"%>
<%@page import="javax.naming.Context"%>
<%! @EJB
	private PersonnesFacadeLocal personnesFacade;
	private BureauxFacadeLocal bureauxFacade;
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
				bureauxFacade = (BureauxFacadeLocal) c.lookup("java:app/devoir_magloire-ejb/BureauxFacade!entity.BureauxFacadeLocal");

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
				<%  for (Bureaux b : bureauxFacade.findAll()) {
						List<Personnes> lp = personnesFacade.findByBureau(b);
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
