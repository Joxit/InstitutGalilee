<%--
    Document   : afminreadmsg
    Created on : 23 nov. 2014, 12:35:52
    Author     : joxit
--%>

<%@page import="java.util.Arrays"%>
<%@page import="java.text.DateFormat"%>
<%@page import="entity.Personnes"%>
<%@page import="entity.Messages"%>
<%@page import="entity.MessagesFacadeLocal"%>
<%@page import="javax.naming.NamingException"%>
<%@page import="javax.naming.Context"%>
<%@page import="javax.naming.InitialContext"%>
<%@page import="javax.ejb.EJB"%>
<%! @EJB
	private MessagesFacadeLocal messagesFacade;
	private final String subMessageReaded = "subMessageReaded";
%>
<%@page contentType="text/html" pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
    <head>
        <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
		<link media="all" type="text/css" href="style.css" rel="stylesheet" />
		<meta name="viewport" content="width=device-width, initial-scale=1.0">
        <title>Administration des bureaux</title>
		<%  try {
				Context c = new InitialContext();
				messagesFacade = (MessagesFacadeLocal) c.lookup("java:app/devoir_magloire-ejb/MessagesFacade!entity.MessagesFacadeLocal");
			} catch (NamingException ne) {
				throw new RuntimeException(ne);
			}
		%>
    </head>
    <body>
		<div class="container">
			<%@include file="WEB-INF/islogged.jsp" %>
			<div id="body">
				<% String[] txt = request.getParameterValues(subMessageReaded);
					if (txt != null) {
						try {
							int id = utils.Utils.getFirstNumeric(txt);
							Messages m = messagesFacade.find(id);
							m.setEtat(Boolean.TRUE);
							messagesFacade.edit(m);
							Personnes p = m.getAuteur();%>
				<h2 class="success" >Message de de <%=p.getNom()%> <%=p.getPrenom()%>
					(<%=p.getPersonneId()%>) lu</h2>
					<%} catch (Exception e) {%>
				<h2 class="error" >Une erreur est survenue</h2>
				<%}

					}%>
				<h2>Les messages non lus</h2>
				<%for (Messages m : messagesFacade.findAll()) {
						if (!m.getEtat()) {
							Personnes p = m.getAuteur();
							String df = DateFormat.getInstance().format(m.getEnvoie());%>
				<h3>Message de <%=p.getNom()%> <%=p.getPrenom()%>
					(<%=p.getPersonneId()%>) envoyé le <%=df%></h3>
				<p><%=m.getMessage().replace("\n", "<br/>\n")%></p>
				<form method='POST'>
					Afficher comme lu <input type='submit' name='<%=subMessageReaded%>' value='Lire'>
					<input type='hidden' name='<%=subMessageReaded%>' value='<%=m.getMessageId()%>'><br/>
				</form>
				<%}
					}%>
				<h2>Les messages lus</h2>
				<%for (Messages m : messagesFacade.findAll()) {
						if (m.getEtat()) {
							Personnes p = m.getAuteur();
							String df = DateFormat.getInstance().format(m.getEnvoie());%>
				<h3>Message de <%=p.getNom()%> <%=p.getPrenom()%>
					(<%=p.getPersonneId()%>) envoyé le <%=df%></h3>
				<p><%=m.getMessage().replace("\n", "<br/>\n")%></p>
				<%}
					}%>
			</div>
		</div>
    </body>
</html>
