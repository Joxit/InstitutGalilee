<%--
    Document   : adminaffect
    Created on : 23 nov. 2014, 22:32:18
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
			String txtAddDeskOfPers = "txtAddDeskOfPers";
			String txtAddPersOfDesk = "txtAddPersOfDesk";
			String subAddDeskToPers = "subAddDeskToPers";%>
    </head>
    <body>
		<div class="container">
            <div id="body">
				<%@include file="WEB-INF/islogged.jsp" %>
				<%if (request.getParameter(subAddDeskToPers) != null) {
						String pers = request.getParameter(txtAddPersOfDesk);
						String desk = request.getParameter(txtAddDeskOfPers);
						Personnes p = personnesFacade.find(Integer.parseInt(pers));
						entity.Bureaux b = bureauxFacade.find(Integer.parseInt(desk));
						if (b != null && p != null) {
							if (b.getLimite() < personnesFacade.findByBureau(b).size()) {
								p.setBureau(b);
								personnesFacade.edit(p);%>
				<h2 class="success"><%=p.getNom()%> <%=p.getPrenom()%> (<%=p.getPersonneId()%>) ajouté au bureau <%=HtmlWriter.bureau(b)%></h2>
				<%} else {%>
				<h2 class="error">Ce bureau est plein</h2>
				<%}
				} else {%>
				<h2 class="error">Identifiants incorrects</h2>
				<%}
					}%>
				<h2>Affecter un bureau à une personne</h2>
				<form method='POST'>
					ID personne: <input type='text' name='<%=txtAddPersOfDesk%>'><br/>
					ID bureau: <select name="<%=txtAddDeskOfPers%>">
						<%for (Bureaux b : bureauxFacade.findAll()) {%>
						<option value='<%=b.getBureauId()%>'>HtmlWriter.bureau(b)</option>
						<%}%>
					</select><br/>
					<input type='submit' value='Affecter' name='<%=subAddDeskToPers%>'><br/>
				</form>

			</div>
		</div>
    </body>
</html>
