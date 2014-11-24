<%--
    Document   : islogged
    Created on : 23 nov. 2014, 12:36:30
    Author     : joxit
--%>

<%@page language="java" pageEncoding="UTF-8"%>

<%@include file="menus/adminHeader.jsp" %>
<% if (!isLogged) {%>
<jsp:forward page="adminlogin.jsp"/>
<%}%>
