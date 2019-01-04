<%@ taglib uri="/WEB-INF/struts-bean.tld" prefix="bean" %>
<%@ taglib uri="/WEB-INF/struts-html.tld" prefix="html" %>
<%@ taglib uri="/WEB-INF/struts-logic.tld" prefix="logic" %>
<%@ taglib uri="/WEB-INF/struts-tiles.tld" prefix="tiles" %>

<jsp:directive.page import="com.ja.jwmail.common.DateUtility"/>
<jsp:useBean id="clock" class="com.ja.jwmail.common.DateUtility" />

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
<title><bean:message key="jwmailapp.title"/></title>
<link rel="stylesheet" href="css/styles.css"> 
<link rel="stylesheet" href="css/custom-theme/jquery-ui-1.7.2.custom.css"> 
<script type="text/javascript" src="<%=request.getContextPath()%>/js/jquery-1.3.2.min.js"></script>
<script type="text/javascript" src="<%=request.getContextPath()%>/js/jquery-ui-1.7.2.custom.min.js"></script>
</head>
<body>

<div class="header">
	<bean:message key="jwmailapp.title"/>
	<span>
		<bean:message key="jwmailapp.clock.prefix"/> <%= clock.toString() %>
	</span>
</div>

<div id="container">
	<tiles:insert attribute="page.body"/>
</div>

</body>
</html>
