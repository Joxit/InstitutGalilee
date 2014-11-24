<%--
    Document   : message
    Created on : 20 nov. 2014, 23:16:32
    Author     : joxit
--%>

<%@page import="Client.ClientHtmlWriter"%>
<%@page import="javax.ejb.EJB"%>
<%@page import="entity.MessagesFacadeLocal"%>
<%@page import="javax.naming.InitialContext"%>
<%@page import="javax.naming.Context"%>
<%@page import="javax.naming.NamingException"%>
<%! @EJB
	private MessagesFacadeLocal messagesFacade;
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
				messagesFacade = (MessagesFacadeLocal) c.lookup("java:app/devoir_magloire-ejb/MessagesFacade!entity.MessagesFacadeLocal");
			} catch (NamingException ne) {
				throw new RuntimeException(ne);
			}
			final String subSendMsg = "subSendMsg";
			final String txtPersSendMsg = "txtPersSendMsg";
			final String txtTxtSendMsg = "txtTxtSendMsg";
		%>
    </head>
    <body>
		<div class="container">
			<%@include file="WEB-INF/menus/clientHeader.jsp" %>
			<div id="body">

				<%if (request.getParameter(subSendMsg) != null) {
						try {
							int persId = Integer.parseInt(request.getParameter(txtPersSendMsg));
							messagesFacade.create(persId, request.getParameter(txtTxtSendMsg));%>
				<h3 class='success'>Message envoyé</h3>
				<%} catch (Exception e) {%>
				<h3 class='error'>Une erreur est survenue lors de l'envoie de votre message</h3>
				<%}
					}%>

				<h2>Quel est votre message ?</h2>
				<form method='POST'>
					<input type="text" value="votre identifiant" name="<%=txtPersSendMsg%>"><br/>
					<textarea rows="10" cols="75" name="<%= txtTxtSendMsg%>"></textarea><br/>
					<input type="submit" value="Envoyer" name="<%=subSendMsg%>"><br/>
				</form>
			</div>
		</div>
    </body>
</html>
