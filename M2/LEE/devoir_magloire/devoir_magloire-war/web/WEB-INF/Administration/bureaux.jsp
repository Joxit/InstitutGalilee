<%--
    Document   : adminadddesk
    Created on : 23 nov. 2014, 23:04:43
    Author     : joxit
--%>

<%@page import="Administration.Desktops"%>
<%@page import="java.util.Map"%>
<%@page import="entity.Bureaux"%>
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
				<p>Vous pouvez ajouter et supprimer des bureaux. Les batiments sont prédéfinis il y a que A ou B
					pareil pour les étages, il y en a que 3</p>
				<form method='POST'>
					<table>
						<tr>
							<td>Batiment:</td>
							<td>
								<select name='<%=Desktops.txtBat%>'>
									<%String bat = (String) request.getAttribute("bat");%>
									<option value="A"
											<%=(bat != null && bat.equals("A") ? "selected" : "")%>>A</option>
									<option value="B"
											<%=(bat != null && bat.equals("B") ? "selected" : "")%>>B</option>
								</select>
							</td>
						</tr>
						<tr>
							<td>Etage:</td>
							<td>
								<select name='<%=Desktops.txtEtage%>'>
									<%String etage = (String) request.getAttribute("etage");%>
									<option value="1" <%=(etage != null && etage.equals("1") ? "selected" : "")%>>1</option>
									<option value="2" <%=(etage != null && etage.equals("2") ? "selected" : "")%>>2</option>
									<option value="3" <%=(etage != null && etage.equals("3") ? "selected" : "")%>>3</option>
								</select>
							</td>
						</tr>
						<tr>
							<td>3 Digits:</td>
							<td><input type='number' min='1' max="999" name='<%=Desktops.txtDigits%>'></td>
						</tr>
						<tr>
							<td>Places:</td>
							<td><input type='number' min="1" name='<%=Desktops.txtPlaces%>'></td>
						</tr>
						<tr>
							<td></td>
							<td><input type='submit' value='Ajouter' name='<%=Desktops.subDesk%>'></td>
						</tr>

					</table>
				</form>
				<h1>Liste des bureaux</h1>
				<table class="list">
					<tr>
						<td>ID</td><td>Batiment</td><td>Etage</td>
						<td>Numero</td><td>Limite</td><td></td>
					</tr>
					<% for (Map.Entry<Bureaux, Integer> entry
								: ((Map<Bureaux, Integer>) request.getAttribute("bureauxhash")).entrySet()) {%>
					<tr>
						<td><%=entry.getKey().getBureauId()%></td>
						<td><%=entry.getKey().getBatiment()%></td>
						<td><%=entry.getKey().getEtage()%></td>
						<td><%=utils.Utils.toThreeDigits(entry.getKey().getNumero())%></td>
						<td><%=entry.getValue()%>/<%=entry.getKey().getLimite()%></td>
						<td><form method="POST">
								<input type="submit" value="x" name="<%=Desktops.subDelDesk%>">
								<input type="hidden" value="<%=entry.getKey().getBureauId()%>" name="<%=Desktops.subDelDesk%>">

							</form></td>
					</tr>
					<%}%>
				</table>
			</div>
		</div>
    </body>
</html>
