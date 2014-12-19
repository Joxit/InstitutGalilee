<%--
    Document   : adminaffect
    Created on : 23 nov. 2014, 22:32:18
    Author     : joxit
--%>
<%@page import="Administration.Affectations"%>
<%@page import="java.util.List"%>
<%@page import="entity.Bureaux"%>
<%@page import="entity.Personnes"%>
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
				<p>Vous pouvez affecter un bureau à une personne avec cette page.
					Un mail devrait être envoyé lors de l'affectation mais cela a été desactivé.</p>
				<h2>Affecter un bureau à une personne</h2>
				<form method='POST'>
					<table>
						<tr><td>Personne:</td>
							<td>
								<select name="<%=Affectations.txtPers%>">
									<% Integer persId = (Integer) request.getAttribute("txtPers");
										for (Personnes p : (List< Personnes>) request.getAttribute("personnes")) {
											String selected = (p.getPersonneId().equals(persId) ? "selected" : "");%>
									<option value='<%=p.getPersonneId()%>' <%=selected%>><%=p.toNomPrenomIdString()%></option>
									<%}%>
								</select>
							</td>
						</tr>
						<tr><td>Bureau:</td>
							<td>
								<table>
									<tr>
										<td><select name="<%=Affectations.txtDesk%>">
												<%for (Bureaux b : (List< Bureaux>) request.getAttribute("bureaux")) {%>
												<option value='<%=b.getBureauId()%>'><%=b.toFormatString()%></option>
												<%}%>
											</select>
										</td>
										<td>

										</td>
									</tr>
									<tr>
										<td>
											<input type="hidden" value="${gen}" name="<%=Affectations.subAffect%>">
											<input type='submit' value='Affecter' name='<%=Affectations.subAffect%>'>
										</td>
										<td>
											<input type='submit' value='${subGen}' name='<%=Affectations.subGen%>'>
										</td>
									</tr>
								</table>

							</td>
						</tr>
						<tr>
							<td></td>
							<td></td>
						</tr>
					</table>
				</form>
			</div>
		</div>
    </body>
</html>
