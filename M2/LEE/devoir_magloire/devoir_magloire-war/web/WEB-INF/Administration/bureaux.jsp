<%--
    Document   : adminadddesk
    Created on : 23 nov. 2014, 23:04:43
    Author     : joxit
--%>

<%@page import="java.util.List"%>
<%@page import="entity.Bureaux"%>
<%@page import="web.HtmlWriter"%>
<%@page contentType="text/html" pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
    <head>
        <title>Administration des bureaux</title>
        <meta charset="UTF-8">
        <link media="all" type="text/css" href="style.css" rel="stylesheet" />
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
    </head>
    <body>
		<div class="container">
            <div id="body">
				<%@include file="../islogged.jsp" %>
				<h3 class='success'>${success}</h3>
				<h3 class='error'>${error}</h3>
				<form method='POST'>
					<table>
						<tr>
							<td>Batiment:</td>
							<td>
								<select name='<%=Administration.Bureaux.txtBat%>'>
									<option value="A">A</option>
									<option value="B">B</option>
								</select>
							</td>
						</tr>
						<tr>
							<td>Etage:</td>
							<td>
								<select name='<%=Administration.Bureaux.txtEtage%>'>
									<option value="1">1</option>
									<option value="2">2</option>
									<option value="3">3</option>
								</select>
							</td>
						</tr>
						<tr>
							<td>3 Digits:</td>
							<td><input type='number' min='1' max="999" name='<%=Administration.Bureaux.txtDigits%>'></td>
						</tr>
						<tr>
							<td>Places:</td>
							<td><input type='number' min="1" name='<%=Administration.Bureaux.txtPlaces%>'></td>
						</tr>
						<tr>
							<td></td>
							<td><input type='submit' value='Ajouter' name='<%=Administration.Bureaux.subDesk%>'></td>
						</tr>
					</table>
				</form>
				<h1>Liste des bureaux</h1>
				<table class="list">
					<tr>
						<td>ID</td><td>Batiment</td><td>Etage</td>
						<td>Numero</td><td>Limite</td>
					</tr>
					<% for (Bureaux b : (List<entity.Bureaux>) request.getAttribute("bureaux")) {%>
					<tr>
						<td><%=b.getBureauId()%></td>
						<td><%=b.getBatiment()%></td>
						<td><%=b.getEtage()%></td>
						<td><%=utils.Utils.toThreeDigits(b.getNumero())%></td>
						<td><%=b.getLimite()%></td>
					</tr>
					<%}%>
				</table>
			</div>
		</div>
    </body>
</html>
