<%--
    Document   : islogged
    Created on : 23 nov. 2014, 12:36:30
    Author     : Jones Magloire
--%>

<%@page language="java" pageEncoding="UTF-8"%>

<%@include file="menus/adminHeader.jsp" %>
<% if (!Authentification.contains(request)) {%>
<jsp:forward page="/Admin"/>
<%}%>
