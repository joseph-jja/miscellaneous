<%@ include file="headers/htmlhead.jsp" %>

<%@ include file="headers/menubar.jsp" %>

<table><tr><td>
</td><td>&nbsp;</td></tr><tr><td>&nbsp;</td><td>

<html:form method="post" action="/sendmail">
<table><tr><td>
<bean:message key="compose.from.email"/>
</td><td>
<html:text size="60" property="fromwhom" value="<%= new String(popserver.getUsername() + "@" + jwmail.HTMLReformatter.removePOPfromEmail(inboxmgr.getMailServer()) ) %>"/>
</td></tr><tr><td>
<bean:message key="compose.to.email"/> 
</td><td>
<html:text size="60" property="towhom"/>
</td></tr><tr><td>
<bean:message key="compose.cc.email"/>
</td><td><html:text size="60" property="ccwhom"/>

</td></tr><tr><td>
<bean:message key="compose.subject"/> 
</td><td>
<html:text size="60" property="subject"/>

</td></tr><tr><td>
<bean:message key="compose.message"/>
<P>&nbsp;<P>&nbsp;<P>&nbsp;<P>&nbsp;<P>&nbsp;</td><td>

<html:textarea property="textsent" rows="10" cols="60" />

</td></tr><tr><td>&nbsp</td><td>
<BR>
<html:submit property="submit">
<bean:message key="compose.submit"/>
</html:submit>
<html:reset property="reset">
<bean:message key="compose.reset"/>
</html:reset>
</td></tr></table>

</html:form>

</td></tr></table>

<%@ include file="footers/footer.html" %>
