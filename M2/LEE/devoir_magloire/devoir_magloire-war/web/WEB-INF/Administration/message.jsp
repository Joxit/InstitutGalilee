<%--
    Document   : afminreadmsg
    Created on : 23 nov. 2014, 12:35:52
    Author     : joxit
--%>

<%@page import="Administration.ReadMessages"%>
<%@page import="java.util.List"%>
<%@page import="java.util.Arrays"%>
<%@page import="java.text.DateFormat"%>
<%@page import="entity.Personnes"%>
<%@page import="entity.Messages"%>
<%@page import="entity.MessagesFacadeLocal"%>
<%@page contentType="text/html" pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
    <head>
        <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
		<link media="all" type="text/css" href="style.css" rel="stylesheet" />
		<meta name="viewport" content="width=device-width, initial-scale=1.0">
        <title>Administration des bureaux</title>
    </head>
    <body>
		<div class="container">
			<%@include file="../islogged.jsp" %>
			<div id="body">
				<h3 class='success'>${success}</h3>
				<h3 class='error'>${error}</h3>
				<p>Vous pouvez lire ici les messages des utilisateurs, ainsi que marquer les messages lus et le supprimer par la suite.</p>
				<h2>Les messages non lus</h2>
				<%for (Messages m : (List<Messages>) request.getAttribute("toRead")) {
						Personnes p = m.getAuteur();
						String df = DateFormat.getInstance().format(m.getEnvoie());%>
				<h3>Message de <%=p.toNomPrenomIdString()%> envoyé le <%=df%></h3>
				<p><%=m.getMessage().replace("\n", "<br/>\n")%></p>
				<form method='POST'>
					Afficher comme lu <input type='submit' name='<%=ReadMessages.subMessageReaded%>' value='Lire'>
					<input type='hidden' name='<%=ReadMessages.subMessageReaded%>' value='<%=m.getMessageId()%>'><br/>
				</form>
				<%}%>
				<h2>Les messages lus</h2>
				<%for (Messages m : (List<Messages>) request.getAttribute("readed")) {
						Personnes p = m.getAuteur();
						String df = DateFormat.getInstance().format(m.getEnvoie());%>
				<h3>Message de <%=p.toNomPrenomIdString()%> envoyé le <%=df%></h3>
				<p><%=m.getMessage().replace("\n", "<br/>\n")%></p>
				<form method='POST'>
					Supprimer définitivement <input type='submit' name='<%=ReadMessages.subMessageReaded%>' value='X'>
					<input type='hidden' name='<%=ReadMessages.subMessageReaded%>' value='<%=m.getMessageId()%>'><br/>
				</form>
				<%}%>
			</div>
		</div>
    </body>
</html>
