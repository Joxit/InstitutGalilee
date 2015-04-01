<%--
    Document   : index
    Created on : 2 déc. 2014, 16:15:05
    Author     : Jones Magloire
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
			<%@include file="WEB-INF/menus/homeHeader.jsp" %>
			<div id="body">
				<h1>Accueil</h1>
				<p>Bienvenue sur le site de gestion des bureaux du LIPN.
					Nous avons la liste de tous les enseignants du LIPN ainsi que leurs affectations.</p>

				<h1>Fonctionalités pour un utilisateur lambda</h1>
				<ul>
					<li>Voir tous les enseignants</li>
					<li>Voir toutes les affectations</li>
					<li>Envoyer un message aux responsables (vous devez vous munir de votre identifiant)</li>
                </ul>
				<h1>Fonctionalités pour un responsable</h1>
				<ul>
					<li>Se connecter/deconnecter</li>
					<li>Ajouter/supprimer un enseignant et tous les voir</li>
					<li>Ajouter/supprimer un bureau et tous les voir</li>
					<li>Affecter un bureau à un enseignant. On peut choisir les bureaux de son equipe ou un quelconque</li>
					<li>Lire les messages des utilisateurs et les marquer en vu puis supprimer</li>
                </ul>
			</div>
		</div>
    </body>
</html>
