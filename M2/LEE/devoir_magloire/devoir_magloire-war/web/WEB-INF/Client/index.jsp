<%--
    Document   : newjsp
    Created on : 15 nov. 2014, 10:46:10
    Author     : joxit
--%>

<%@page contentType="text/html" pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
    <head>
        <title>Gestion des bureaux</title>
        <meta charset="UTF-8">
        <link media="all" type="text/css" href="style.css" rel="stylesheet" />
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
    </head>
    <body>
        <div class="container">
			<%@include file="../menus/clientHeader.jsp" %>
            <div id="body">
                <h1>Bienvenue dans la partie client du logiciel</h1>
				<h2>Que souhaitez vous faire ?</h2>
				<p>Vous pouvez choisir les actions que vous souhaitez
					via le menu en survolant 'Client'. Vous pouvez voir la liste
					des personnes qui sont dans nos locaux et leurs affectations</p>
            </div>
        </div>
    </body>
</html>
