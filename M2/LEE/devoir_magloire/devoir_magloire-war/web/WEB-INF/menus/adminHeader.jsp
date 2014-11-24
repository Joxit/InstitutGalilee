<%--
    Document   : adminHeader
    Created on : 20 nov. 2014, 22:13:17
    Author     : joxit
--%>

<%@page contentType="text/html" pageEncoding="UTF-8"%>
<div id="header">
	<div id="header-content">
		<div id="header-name">Gestion des bureaux<br />
			<span>Projet de Master 2 Informatique</span><br />
		</div>
		<div id="header-menu">
			<ul><li class="border-bottom-transition">Home</li>
					<%@include file="clientMenu.jsp" %>
					<%@include file="adminMenuLined.jsp" %>
			</ul>
		</div>
	</div>
</div>
