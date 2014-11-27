<%--
    Document   : adminaffect
    Created on : 23 nov. 2014, 22:32:18
    Author     : joxit
--%>
<%@page import="Administration.Affectations"%>
<%@page import="java.util.List"%>
<%@page import="entity.Bureaux"%>
<%@page import="web.HtmlWriter"%>
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
				<h2>Affecter un bureau à une personne</h2>
				<form method='POST'>
					<table>
						<tr><td>Personne:</td>
							<td>
								<select name="<%=Affectations.txtPers%>">
									<%for (Personnes p : (List< Personnes>) request.getAttribute("personnes")) {%>
									<option value='<%=p.getPersonneId()%>'><%=HtmlWriter.personne(p)%></option>
									<%}%>
								</select>
							</td>
						</tr>
						<tr><td>Bureau:</td>
							<td>
								<select name="<%=Affectations.txtDesk%>">
									<%for (Bureaux b : (List< Bureaux>) request.getAttribute("bureaux")) {%>
									<option value='<%=b.getBureauId()%>'><%=HtmlWriter.bureau(b)%></option>
									<%}%>
								</select>
							</td>
						</tr>
						<tr>
							<td></td>
							<td><input type='submit' value='Affecter' name='<%=Affectations.subAffect%>'></td>
						</tr>
					</table>
				</form>
			</div>
		</div>
    </body>
</html>
