<%--
    Document   : clientHeader
    Created on : 20 nov. 2014, 22:13:07
    Author     : Jones Magloire
--%>

<%@page contentType="text/html" pageEncoding="UTF-8"%>

<div id="header">
	<div id="header-content">
		<div id="header-name">Gestion des bureaux<br />
			<span>Projet de Master 2 Informatique</span><br />
		</div>
		<div id="header-menu">
			<ul><li class="border-bottom-transition"><a href="index.jsp">Home</a></li>
					<%@include file="clientMenuLined.jsp" %>
					<%@include file="adminMenu.jsp" %>
			</ul>
		</div>
	</div>
</div>
