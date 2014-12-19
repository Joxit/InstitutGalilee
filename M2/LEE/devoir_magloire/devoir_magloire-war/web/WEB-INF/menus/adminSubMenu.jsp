<%--
    Document   : adminSubMenu
    Created on : 20 nov. 2014, 22:03:07
    Author     : Jones Magloire
--%>

<%@page import="Administration.Authentification"%>
<%@page contentType="text/html" pageEncoding="UTF-8"%>
<%if (Authentification.contains(request)) {%>
<ul>
	<li><a href="Admin.Utilisateurs">Ajouter personne</a></li>
	<li><a href="Admin.Bureaux">Ajouter Bureau</a></li>
	<li><a href="Admin.Affectations">Affecter Bureau</a></li>
	<li><a href="Admin.Message">Lire Messages</a></li>
	<li><a href="Admin.Deconnexion">Deconnexion</a></li>
</ul>
<%}%>
