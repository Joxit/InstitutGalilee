<%--
    Document   : message
    Created on : 20 nov. 2014, 23:16:32
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
				<h3 class='success'>${success}</h3>
				<h3 class='error'>${error}</h3>

				<h2>Quel est votre message ?</h2>
				<form method='POST'>
					<input type="text" value="votre identifiant" name="${txtPersSendMsg}"><br/>
					<textarea rows="10" cols="75" name="${txtTxtSendMsg}"></textarea><br/>
					<input type="submit" value="Envoyer" name="${subSendMsg}"><br/>
				</form>
			</div>
		</div>
    </body>
</html>
